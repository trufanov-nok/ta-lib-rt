/* TA-MySQL, Copyright (C) 2003, Pawel Konieczny
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the 
 *   Free Software Foundation, Inc., 
 *	 59 Temple Place, Suite 330,
 *	 Boston, MA 02111-1307 USA
 *
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  PK       Pawel Konieczny
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  110103 PK   First version.
 *  110103 PK   Minidriver architecture
 *
 */

/* Description:
 *    This file implements the SQL minidriver using the MyQSL++ library
 *    It is build in the project only when TA_SUPPORT_MYSQL is enabled
 */

/**** Headers ****/
extern "C" {
#include <stdio.h>
#include <string.h>
#include "ta_system.h"
#include "ta_trace.h"
#include "ta_sql_minidriver.h"
#include "ta_mysql.h"
}

#if defined(_MSC_VER)
/* disable some C++ warnings in MySQL++ for Microsoft compiler */
#pragma warning( disable: 4800 4355 )
#endif
#include <mysql++>

/**** External functions declarations. ****/
/* None */

/**** External variables declarations. ****/
/* None */

/**** Global variables definitions.    ****/
/* None */

/**** Local declarations.              ****/

typedef struct
{
   Result *res;
   int rownum;
   Row row;
   
} TA_MYSQL_QueryResult;

typedef struct
{
#if !defined( TA_SINGLE_THREAD )
   TA_Sema sema;
#endif
   Connection *con;

} TA_MYSQL_Connection;


/**** Local functions declarations.    ****/
extern "C" 
{
   static TA_RetCode TA_MYSQL_OpenConnection(const char database[], 
                                             const char host[], 
                                             const char username[], 
                                             const char password[],
                                             unsigned int port,
                                             void **connection);
   static TA_RetCode TA_MYSQL_ExecuteQuery(void *connection, 
                                           const char sql_query[], 
                                           void **query_result);
   static TA_RetCode TA_MYSQL_GetNumColumns(void *query_result, int *num);
   static TA_RetCode TA_MYSQL_GetNumRows(void *query_result, int *num);
   static TA_RetCode TA_MYSQL_GetColumnName(void *query_result, int column, const char **name);
   static TA_RetCode TA_MYSQL_GetRowString(void *query_reslut, int row, int column, const char **value);
   static TA_RetCode TA_MYSQL_GetRowReal(void *query_reslut, int row, int column, TA_Real *value);
   static TA_RetCode TA_MYSQL_GetRowInteger(void *query_reslut, int row, int column, TA_Integer *value);
   static TA_RetCode TA_MYSQL_ReleaseQuery(void *query_result);
   static TA_RetCode TA_MYSQL_CloseConnection(void *connection);
}

/**** Local variables definitions.     ****/
TA_FILE_INFO;

extern "C" const TA_SQL_Minidriver localMySQLMinidriver =
{
      TA_MYSQL_OpenConnection,
      TA_MYSQL_ExecuteQuery,
      TA_MYSQL_GetNumColumns,
      TA_MYSQL_GetNumRows,
      TA_MYSQL_GetColumnName,
      TA_MYSQL_GetRowString,
      TA_MYSQL_GetRowReal,
      TA_MYSQL_GetRowInteger,
      TA_MYSQL_ReleaseQuery,
      TA_MYSQL_CloseConnection
};

/**** Global functions definitions.    ****/

TA_RetCode TA_MYSQL_Initialize(void)
{
   TA_PROLOG
   TA_TRACE_BEGIN( TA_MYSQL_Initialize );

   TA_TRACE_RETURN( TA_SQL_AddMinidriver( "mysql", &localMySQLMinidriver ) );
}


/**** Local functions definitions.     ****/
extern "C" static TA_RetCode TA_MYSQL_OpenConnection(const char database[], 
                                       const char host[], 
                                       const char username[], 
                                       const char password[],
                                       unsigned int port,
                                       void **connection)
{
   TA_PROLOG
   TA_MYSQL_Connection *privConnection;
   TA_RetCode retCode = TA_SUCCESS;

   TA_TRACE_BEGIN( TA_MYSQL_OpenConnection );

   privConnection = (TA_MYSQL_Connection*)TA_Malloc( sizeof(TA_MYSQL_Connection) );
   if( privConnection == NULL )
   {
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }
   memset(privConnection, 0, sizeof(TA_MYSQL_Connection) );

#if !defined( TA_SINGLE_THREAD )
   retCode = TA_SemaInit( &privConnection->sema, 1);
   if( retCode != TA_SUCCESS )
   {
      TA_Free( privConnection );
      TA_TRACE_RETURN( retCode );
   }
#endif

   /* Establish the connection with the MySQL server */
   try 
   {
      privConnection->con = new Connection(
         database, 
         host, 
         username, 
         password, 
         port);
   }
   catch (...)
   {
#if !defined( TA_SINGLE_THREAD )
      TA_SemaDestroy( &privConnection->sema );
#endif
      TA_Free( privConnection );
      TA_TRACE_RETURN( TA_ACCESS_FAILED );
   }

   *connection = privConnection;

   TA_TRACE_RETURN( retCode );
}



extern "C" static TA_RetCode TA_MYSQL_ExecuteQuery(void *connection, 
                           const char sql_query[], 
                           void **query_result)
{
   TA_PROLOG
   TA_MYSQL_Connection *privConnection;
   TA_MYSQL_QueryResult *privResult = NULL;
   TA_RetCode retCode = TA_SUCCESS;

   TA_TRACE_BEGIN( TA_MYSQL_ExecuteQuery );
   
   TA_ASSERT( connection != NULL );
   TA_ASSERT( query_result != NULL );

   privConnection = (TA_MYSQL_Connection*)connection;

#if !defined( TA_SINGLE_THREAD )
   retCode = TA_SemaWait( &privConnection->sema );
   if( retCode != TA_SUCCESS )
   {
      TA_TRACE_RETURN( retCode );
   }
#endif

   try 
   {

      privResult = new TA_MYSQL_QueryResult;
      if( privResult == NULL )
      {
         retCode = TA_ALLOC_ERR;
         throw retCode;
      }
      privResult->res = NULL;

      // This creates a query object that is bound to con.
      Query query = privConnection->con->query();

      // You can write to the query object like you would any other ostrem
      query << sql_query;

      // Query::store() executes the query and returns the results
      privResult->res = new Result(query.store());
      privResult->rownum = -1; // no row fetched
   }
   catch (...)
   {                    
      // handle any connection or query errors that may come up
      if( privResult && privResult->res )
      {
         delete privResult->res;
      }
      delete privResult;
      privResult = NULL;
      if( retCode == TA_SUCCESS )
      {
         retCode = TA_BAD_QUERY;
      }
   } 

#if !defined( TA_SINGLE_THREAD )
   TA_SemaPost( &privConnection->sema );
#endif

   *query_result = privResult;
   TA_TRACE_RETURN( retCode );
}



extern "C" static TA_RetCode TA_MYSQL_GetNumColumns(void *query_result, int *num)
{
   TA_PROLOG

   TA_MYSQL_QueryResult *privResult = (TA_MYSQL_QueryResult*)query_result;
   
   TA_TRACE_BEGIN( TA_MYSQL_GetNumColumns );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( num != NULL );

   try
   {
      *num = privResult->res->columns();
   }
   catch (...)
   {
      TA_TRACE_RETURN( TA_INTERNAL_ERR );  
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



extern "C" static TA_RetCode TA_MYSQL_GetNumRows(void *query_result, int *num)
{
   TA_PROLOG

   TA_MYSQL_QueryResult *privResult = (TA_MYSQL_QueryResult*)query_result;
   
   TA_TRACE_BEGIN( TA_MYSQL_GetNumRows );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( num != NULL );

   try
   {
      *num = privResult->res->rows();
   }
   catch (...)
   {
      TA_TRACE_RETURN( TA_INTERNAL_ERR );  
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



extern "C" static TA_RetCode TA_MYSQL_GetColumnName(void *query_result, int column, const char **name)
{
   TA_PROLOG

   TA_MYSQL_QueryResult *privResult = (TA_MYSQL_QueryResult*)query_result;
   
   TA_TRACE_BEGIN( TA_MYSQL_GetColumnName );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( name != NULL );

   try
   {
      *name = privResult->res->names(column).c_str();
      
   }
   catch (...)
   {
      TA_TRACE_RETURN( TA_INTERNAL_ERR );  
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



extern "C" static TA_RetCode TA_MYSQL_GetRowString(void *query_result, int row, int column, const char **value)
{
   TA_PROLOG

   TA_MYSQL_QueryResult *privResult = (TA_MYSQL_QueryResult*)query_result;
   
   TA_TRACE_BEGIN( TA_MYSQL_GetRowString );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( value != NULL );
   TA_ASSERT_RET( row >= 0, TA_BAD_PARAM );

   try
   {
      if( (unsigned)row >= privResult->res->rows() )
      {
         TA_TRACE_RETURN( TA_END_OF_INDEX );
      }

      if( row != privResult->rownum )
      {
         privResult->row = (*privResult->res)[row];
         privResult->rownum = row;
      }

      *value = privResult->row.raw_data(column);
   }
   catch (...)
   {
      TA_TRACE_RETURN( TA_INTERNAL_ERR );  
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



extern "C" static TA_RetCode TA_MYSQL_GetRowReal(void *query_result, int row, int column, TA_Real *value)
{
   TA_PROLOG

   TA_MYSQL_QueryResult *privResult = (TA_MYSQL_QueryResult*)query_result;
   
   TA_TRACE_BEGIN( TA_MYSQL_GetRowReal );

   TA_ASSERT( query_result!= NULL );
   TA_ASSERT( value != NULL );
   TA_ASSERT_RET( row >= 0, TA_BAD_PARAM );

   try
   {
      if( (unsigned)row >= privResult->res->rows() )
      {
         TA_TRACE_RETURN( TA_END_OF_INDEX );
      }

      if( row != privResult->rownum )
      {
         privResult->row = (*privResult->res)[row];
         privResult->rownum = row;
      }

      *value = privResult->row[column];
   }
   catch (...)
   {
      TA_TRACE_RETURN( TA_INTERNAL_ERR );  
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



extern "C" static TA_RetCode TA_MYSQL_GetRowInteger(void *query_result, int row, int column, TA_Integer *value)
{
   TA_PROLOG

   TA_MYSQL_QueryResult *privResult = (TA_MYSQL_QueryResult*)query_result;
   
   TA_TRACE_BEGIN( TA_MYSQL_GetRowInteger );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( value != NULL );
   TA_ASSERT_RET( row >= 0, TA_BAD_PARAM );

   try
   {
      if( (unsigned)row >= privResult->res->rows() )
      {
         TA_TRACE_RETURN( TA_END_OF_INDEX );
      }

      if( row != privResult->rownum )
      {
         privResult->row = (*privResult->res)[row];
         privResult->rownum = row;
      }
      
      *value = privResult->row[column];
   }
   catch (...)
   {
      TA_TRACE_RETURN( TA_INTERNAL_ERR );  
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



extern "C" static TA_RetCode TA_MYSQL_ReleaseQuery(void *query_result)
{
   TA_PROLOG

   TA_MYSQL_QueryResult *privResult = (TA_MYSQL_QueryResult*)query_result;
   
   TA_TRACE_BEGIN( TA_MYSQL_ReleaseQuery );
   
   if( privResult )
   {
      try
      {
         delete privResult->res;
         delete privResult;
      }
      catch (...)
      {
         TA_TRACE_RETURN( TA_INTERNAL_ERR );  
      }
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



extern "C" static TA_RetCode TA_MYSQL_CloseConnection(void *connection)
{
   TA_PROLOG
   TA_MYSQL_Connection *privConnection;
   TA_RetCode retCode = TA_SUCCESS;

   TA_TRACE_BEGIN( TA_MYSQL_CloseConnection );

   privConnection = (TA_MYSQL_Connection*)connection;
   if ( privConnection )
   {
      try 
      {
         delete privConnection->con;
      }
      catch (...)
      {
         retCode = TA_INVALID_HANDLE;
      }
#if !defined( TA_SINGLE_THREAD )
      TA_SemaDestroy( &privConnection->sema );
#endif
      TA_Free( privConnection );
   }

   TA_TRACE_RETURN( retCode );
}
