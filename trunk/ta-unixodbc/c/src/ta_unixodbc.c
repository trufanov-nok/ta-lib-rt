/* TA-unixODBC, Copyright (C) 2003, Pawel Konieczny
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the 
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
 *  110903 PK   First version.
 *
 */

/* Description:
 *    This file implements the SQL minidriver using the ODBC library.
 *    This version is build only on a non-WIN32 platform and is
 *    intended to be used with unixODBC ( http://www.unixodbc.org ).
 */


/**** Headers ****/
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>

#include "ta_system.h"
#include "ta_trace.h"
#include "ta_sql_handle.h"
#include "ta_sql_minidriver.h"
#include "ta_unixodbc.h"

/**** External functions declarations. ****/
/* None */

/**** External variables declarations. ****/
/* None */

/**** Global variables definitions.    ****/
/* None */

/**** Local declarations.              ****/

typedef struct 
{
   SQLCHAR name[TA_SQL_MAX_COLUMN_NAME_SIZE];
   SQLSMALLINT datatype;
   SQLSMALLINT ctype;
   SQLUINTEGER size;

} TA_UNIXODBC_ColumnDef;



typedef struct
{
   SQLHSTMT hstmt;  /* statement handle */

   SQLINTEGER  numRows;
   SQLSMALLINT numCols;

   TA_UNIXODBC_ColumnDef *columns;

   int curRow;
   char **rowData;  /* fields to be bound to columns */
   SQLINTEGER *rowIndicator;  /* NULL data indicator array for bound fields */

} TA_UNIXODBC_Statement;


typedef struct
{
   SQLHENV henv;  /* environment handle */
   SQLHDBC hdbc;  /* connection handle */
   
} TA_UNIXODBC_Connection;



/**** Local functions declarations.    ****/

/* functions for allocating and freeing rowData field in TA_UNIXODBC_Statement
 * making use of information in columns array
 */
static TA_RetCode allocRowData( TA_UNIXODBC_Statement *statement );
static TA_RetCode freeRowData( TA_UNIXODBC_Statement *statement );


static TA_RetCode TA_UNIXODBC_OpenConnection(const char database[], 
                                      const char host[], 
                                      const char username[], 
                                      const char password[],
                                      unsigned int port,
                                      void **connection);
static TA_RetCode TA_UNIXODBC_ExecuteQuery(void *connection, 
                                    const char sql_query[], 
                                    void **query_result);
static TA_RetCode TA_UNIXODBC_GetNumColumns(void *query_result, int *num);
static TA_RetCode TA_UNIXODBC_GetNumRows(void *query_result, int *num);
static TA_RetCode TA_UNIXODBC_GetColumnName(void *query_result, int column, const char **name);
static TA_RetCode TA_UNIXODBC_GetRowString(void *query_result, int row, int column, const char **value);
static TA_RetCode TA_UNIXODBC_GetRowReal(void *query_result, int row, int column, TA_Real *value);
static TA_RetCode TA_UNIXODBC_GetRowInteger(void *query_result, int row, int column, TA_Integer *value);
static TA_RetCode TA_UNIXODBC_ReleaseQuery(void *query_result);
static TA_RetCode TA_UNIXODBC_CloseConnection(void *connection);

/**** Local variables definitions.     ****/
TA_FILE_INFO;

static const TA_SQL_Minidriver localUNIXODBCSQLMinidriver =
{
      TA_UNIXODBC_OpenConnection,
      TA_UNIXODBC_ExecuteQuery,
      TA_UNIXODBC_GetNumColumns,
      TA_UNIXODBC_GetNumRows,
      TA_UNIXODBC_GetColumnName,
      TA_UNIXODBC_GetRowString,
      TA_UNIXODBC_GetRowReal,
      TA_UNIXODBC_GetRowInteger,
      TA_UNIXODBC_ReleaseQuery,
      TA_UNIXODBC_CloseConnection
};

/**** Global functions definitions.    ****/

TA_RetCode TA_UNIXODBC_Initialize(void)
{
   TA_PROLOG
   TA_TRACE_BEGIN( TA_UNIXODBC_Initialize );

   TA_TRACE_RETURN( TA_SQL_AddMinidriver( "odbc", &localUNIXODBCSQLMinidriver ) );
}

/**** Local functions definitions.     ****/

static TA_RetCode TA_UNIXODBC_OpenConnection(const char database[], 
                                      const char host[], 
                                      const char username[], 
                                      const char password[],
                                      unsigned int port,
                                      void **connection)
{
   TA_PROLOG
   TA_UNIXODBC_Connection *privConnection;
   SQLRETURN sqlRetCode;

   TA_TRACE_BEGIN( TA_UNIXODBC_OpenConnection );

   TA_ASSERT( connection != NULL );
   
   /* unused parameters */
   (void)port;
   (void)host;

   privConnection = (TA_UNIXODBC_Connection*)TA_Malloc( sizeof(TA_UNIXODBC_Connection) );
   if( privConnection == NULL )
   {
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }
   memset(privConnection, 0, sizeof(TA_UNIXODBC_Connection) );


   /* load the Driver Manager and allocate the environment handle */
   sqlRetCode = SQLAllocHandle( SQL_HANDLE_ENV, 
                                SQL_NULL_HANDLE, 
                                &privConnection->henv);
   if( ! SQL_SUCCEEDED(sqlRetCode) )
   {
      TA_Free( privConnection );
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   /* register the version of ODBC to which the driver conforms */
   sqlRetCode = SQLSetEnvAttr( privConnection->henv, 
                               SQL_ATTR_ODBC_VERSION, 
                               (SQLPOINTER)SQL_OV_ODBC3, 0);
   if( ! SQL_SUCCEEDED(sqlRetCode) )
   {
      SQLFreeHandle( SQL_HANDLE_ENV, privConnection->henv );
      TA_Free( privConnection );
      TA_TRACE_RETURN( TA_INTERNAL_ERR );
   }

   /* allocate a connection handle */
   sqlRetCode = SQLAllocHandle( SQL_HANDLE_DBC, 
                                privConnection->henv, 
                                &privConnection->hdbc);
   if( ! SQL_SUCCEEDED(sqlRetCode) )
   {
      SQLFreeHandle( SQL_HANDLE_ENV, privConnection->henv );
      TA_Free( privConnection );
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

   /* set any connection attributes */
   sqlRetCode = SQLSetConnectAttr( privConnection->hdbc, 
                                   SQL_ATTR_ACCESS_MODE, 
                                   (SQLPOINTER)SQL_MODE_READ_ONLY, 0);
   if( ! SQL_SUCCEEDED(sqlRetCode) )
   {
      SQLFreeHandle( SQL_HANDLE_DBC, privConnection->hdbc );
      SQLFreeHandle( SQL_HANDLE_ENV, privConnection->henv );
      TA_Free( privConnection );
      TA_TRACE_RETURN( TA_INTERNAL_ERR );
   }
   
   /* connects to the data source */
   sqlRetCode = SQLConnect( privConnection->hdbc, 
                            (SQLCHAR*)database, SQL_NTS,
                            (SQLCHAR*)username, SQL_NTS,
                            (SQLCHAR*)password, SQL_NTS);
   
   if( ! SQL_SUCCEEDED(sqlRetCode) )
   {
      SQLFreeHandle( SQL_HANDLE_DBC, privConnection->hdbc );
      SQLFreeHandle( SQL_HANDLE_ENV, privConnection->henv );
      TA_Free( privConnection );
      TA_TRACE_RETURN( TA_ACCESS_FAILED );
   }

   *connection = privConnection;

   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_ExecuteQuery(void *connection, 
                                    const char sql_query[], 
                                    void **query_result)
{
   TA_PROLOG
   TA_UNIXODBC_Connection *privConnection;
   TA_UNIXODBC_Statement *privStatement;
   int col;
   SQLRETURN sqlRetCode;

   TA_TRACE_BEGIN( TA_UNIXODBC_ExecuteQuery );

   
   TA_ASSERT( connection != NULL );
   TA_ASSERT( query_result != NULL );

   privConnection = (TA_UNIXODBC_Connection*)connection;

   privStatement = TA_Malloc( sizeof(TA_UNIXODBC_Statement) );
   if( privStatement == NULL )
   {
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }
   memset(privStatement, 0, sizeof(TA_UNIXODBC_Statement) );

   sqlRetCode = SQLAllocHandle( SQL_HANDLE_STMT, 
                                privConnection->hdbc, 
                                &privStatement->hstmt );
   if( ! SQL_SUCCEEDED(sqlRetCode) )
   {
      TA_Free(privStatement);
      TA_TRACE_RETURN( TA_ALLOC_ERR );
   }

#define RETURN_ON_ERROR( errcode )                              \
   if( ! SQL_SUCCEEDED( sqlRetCode ) )                          \
   {                                                            \
      SQLFreeHandle( SQL_HANDLE_STMT, privStatement->hstmt );   \
      freeRowData( privStatement );                             \
      if( privStatement->columns )                              \
         TA_Free( privStatement->columns );                     \
      TA_Free(privStatement);                                   \
      TA_TRACE_RETURN( errcode );                               \
   }

   sqlRetCode = SQLSetStmtAttr( privStatement->hstmt, 
                                SQL_ATTR_CONCURRENCY, 
                                (SQLPOINTER)SQL_CONCUR_READ_ONLY, 0 );
   RETURN_ON_ERROR( TA_INTERNAL_ERR );
   
   sqlRetCode = SQLExecDirect( privStatement->hstmt, (SQLCHAR*)sql_query, SQL_NTS );
   RETURN_ON_ERROR( TA_BAD_QUERY );

   sqlRetCode = SQLNumResultCols( privStatement->hstmt, &privStatement->numCols );
   RETURN_ON_ERROR( TA_BAD_QUERY );

   /* Officially, SQLRowCount may not be supported for SELECT queries,
    * but many ODBC drivers support it anyway, and it is very handy here to get it
    * to allocate proper size arrays in the upper part of the ta_sql driver 
    */
   sqlRetCode = SQLRowCount( privStatement->hstmt, &privStatement->numRows );
   if( ! SQL_SUCCEEDED(sqlRetCode) || privStatement->numRows <= 0 )
   {
      privStatement->numRows = -1;
   }
   /* collect information about the columns */
   privStatement->columns = TA_Malloc( privStatement->numCols * sizeof(TA_UNIXODBC_ColumnDef) );
   if ( privStatement->columns == NULL ) {
      sqlRetCode = SQL_ERROR; /* to force RETURN_ON_ERROR to return */
      RETURN_ON_ERROR( TA_ALLOC_ERR );
   }
   memset( privStatement->columns, 0, privStatement->numCols * sizeof(TA_UNIXODBC_ColumnDef) );

   for( col = 0;  col < privStatement->numCols;  col++)
   {
      sqlRetCode = SQLDescribeCol( privStatement->hstmt,
                                   (SQLSMALLINT)(col + 1),  /* ODBC counts columns starting at 1 */
                                   privStatement->columns[col].name,
                                   TA_SQL_MAX_COLUMN_NAME_SIZE,
                                   NULL,  /* actual name length is not interesting */
                                   &privStatement->columns[col].datatype,
                                   &privStatement->columns[col].size,
                                   /* other fields are not interesting */
                                   NULL, NULL );
      RETURN_ON_ERROR( TA_INTERNAL_ERR );
   }

   /* prepare buffers for row data */
   allocRowData( privStatement );
   if( privStatement->rowData == NULL || privStatement->rowIndicator == NULL ) 
   {
      sqlRetCode = SQL_ERROR; /* to force RETURN_ON_ERROR to return */
      RETURN_ON_ERROR( TA_ALLOC_ERR );
   }

   for( col = 0;  col < privStatement->numCols;  col++)
   {
      if( privStatement->rowData[col] )
      {
         sqlRetCode = SQLBindCol( privStatement->hstmt,
            (SQLSMALLINT)(col + 1),                /* ODBC counts columns starting at 1 */
            privStatement->columns[col].ctype,
            privStatement->rowData[col],
            privStatement->columns[col].size + 1,  /* relevant (used) only for SQL_C_CHAR columns */
            &privStatement->rowIndicator[col]);    /* to recognize NULL fields */
         RETURN_ON_ERROR( TA_INTERNAL_ERR );
      }
   }
   privStatement->curRow = -1;  /* no rows fetched yet */

#undef RETURN_ON_ERROR

   *query_result = privStatement;
   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_GetNumColumns(void *query_result, int *num)
{
   TA_PROLOG
   TA_UNIXODBC_Statement *privStatement;
    
   TA_TRACE_BEGIN( TA_UNIXODBC_GetNumColumns );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( num != NULL );

   privStatement = (TA_UNIXODBC_Statement*)query_result;
   
   *num = privStatement->numCols;
   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_GetNumRows(void *query_result, int *num)
{
   TA_PROLOG
   TA_UNIXODBC_Statement *privStatement;

   TA_TRACE_BEGIN( TA_UNIXODBC_GetNumRows );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( num != NULL );
   
   privStatement = (TA_UNIXODBC_Statement*)query_result;
   
   *num = privStatement->numRows;
   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_GetColumnName(void *query_result, int column, const char **name)
{
   TA_PROLOG
   TA_UNIXODBC_Statement *privStatement;

   TA_TRACE_BEGIN( TA_UNIXODBC_GetColumnName );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( name != NULL );

   privStatement = (TA_UNIXODBC_Statement*)query_result;
   TA_ASSERT( column < privStatement->numCols );

   *name = privStatement->columns[column].name;
   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_GetRowString(void *query_result, int row, int column, const char **value)
{
   TA_PROLOG
   TA_UNIXODBC_Statement *privStatement;
   SQLRETURN sqlRetCode;

   TA_TRACE_BEGIN( TA_UNIXODBC_GetRowString );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( value != NULL );
   TA_ASSERT_RET( row >= 0, TA_BAD_PARAM );

   privStatement = (TA_UNIXODBC_Statement*)query_result;
   TA_ASSERT( row >= privStatement->curRow );
 
   while( row > privStatement->curRow )
   {
      sqlRetCode = SQLFetch( privStatement->hstmt );
      if( sqlRetCode == SQL_NO_DATA )
      {
         TA_TRACE_RETURN( TA_END_OF_INDEX );
      }
      if( ! SQL_SUCCEEDED(sqlRetCode) )
      {
         TA_TRACE_RETURN( TA_BAD_QUERY );
      }
      privStatement->curRow++;
   }

   if( privStatement->columns[column].ctype != SQL_C_CHAR )
   {
      TA_TRACE_RETURN( TA_NOT_SUPPORTED );
   }

   if( privStatement->rowIndicator[column] == SQL_NULL_DATA )
   {
      *value = "";
   }
   else
   {
      *value = privStatement->rowData[column];
   }
   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_GetRowReal(void *query_result, int row, int column, TA_Real *value)
{
   TA_PROLOG
   TA_UNIXODBC_Statement *privStatement;
   SQLRETURN sqlRetCode;

   TA_TRACE_BEGIN( TA_UNIXODBC_GetRowReal );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( value != NULL );
   TA_ASSERT_RET( row >= 0, TA_BAD_PARAM );
   
   privStatement = (TA_UNIXODBC_Statement*)query_result;
   TA_ASSERT( row >= privStatement->curRow );
   
   while( row > privStatement->curRow )
   {
      sqlRetCode = SQLFetch( privStatement->hstmt );
      if( sqlRetCode == SQL_NO_DATA )
      {
         TA_TRACE_RETURN( TA_END_OF_INDEX );
      }
      if( ! SQL_SUCCEEDED(sqlRetCode) )
      {
         TA_TRACE_RETURN( TA_BAD_QUERY );
      }
      privStatement->curRow++;
   }
   
   if( privStatement->columns[column].ctype != SQL_C_DOUBLE )
   {
      TA_TRACE_RETURN( TA_NOT_SUPPORTED );
   }
   
   if( privStatement->rowIndicator[column] == SQL_NULL_DATA )
   {
      *value = 0.0;
   }
   else
   {
      *value = *(double*)privStatement->rowData[column];
   }
   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_GetRowInteger(void *query_result, int row, int column, TA_Integer *value)
{
   TA_PROLOG
   TA_UNIXODBC_Statement *privStatement;
   SQLRETURN sqlRetCode;

   TA_TRACE_BEGIN( TA_UNIXODBC_GetRowInteger );

   TA_ASSERT( query_result != NULL );
   TA_ASSERT( value != NULL );
   TA_ASSERT_RET( row >= 0, TA_BAD_PARAM );
   
   privStatement = (TA_UNIXODBC_Statement*)query_result;
   TA_ASSERT( row >= privStatement->curRow );
   
   while( row > privStatement->curRow )
   {
      sqlRetCode = SQLFetch( privStatement->hstmt );
      if( sqlRetCode == SQL_NO_DATA )
      {
         TA_TRACE_RETURN( TA_END_OF_INDEX );
      }
      if( ! SQL_SUCCEEDED(sqlRetCode) )
      {
         TA_TRACE_RETURN( TA_BAD_QUERY );
      }
      privStatement->curRow++;
   }
   
   if( privStatement->columns[column].ctype != SQL_C_SLONG )
   {
      TA_TRACE_RETURN( TA_NOT_SUPPORTED );
   }
   
   if( privStatement->rowIndicator[column] == SQL_NULL_DATA )
   {
      *value = 0;
   }
   else
   {
      *value = *(long*)privStatement->rowData[column];
   }
   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_ReleaseQuery(void *query_result)
{
   TA_PROLOG
   TA_UNIXODBC_Statement *privStatement;
   SQLRETURN sqlRetCode;

   TA_TRACE_BEGIN( TA_UNIXODBC_ReleaseQuery );

   TA_ASSERT( query_result != NULL );

   privStatement = (TA_UNIXODBC_Statement*)query_result;

   sqlRetCode = SQLFreeHandle( SQL_HANDLE_STMT, privStatement->hstmt );
   freeRowData( privStatement );
   if( privStatement->columns )
   {
      TA_Free( privStatement->columns );
   }
   TA_Free(privStatement);

   if( ! SQL_SUCCEEDED(sqlRetCode) )
   {
      TA_TRACE_RETURN( TA_INVALID_HANDLE );
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}



static TA_RetCode TA_UNIXODBC_CloseConnection(void *connection)
{
   TA_PROLOG
   TA_UNIXODBC_Connection *privConnection;
   SQLRETURN sqlRetCode;

   TA_TRACE_BEGIN( TA_UNIXODBC_CloseConnection );

   privConnection = (TA_UNIXODBC_Connection*)connection;
   if ( privConnection )
   {
      sqlRetCode = SQLDisconnect( privConnection->hdbc );
      if( ! SQL_SUCCEEDED(sqlRetCode) )
      {
         TA_TRACE_RETURN( TA_INTERNAL_ERR );
      }

      sqlRetCode = SQLFreeHandle( SQL_HANDLE_DBC, privConnection->hdbc );
      if( ! SQL_SUCCEEDED(sqlRetCode) )
      {
         TA_TRACE_RETURN( TA_INVALID_HANDLE );
      }
      
      sqlRetCode = SQLFreeHandle( SQL_HANDLE_ENV, privConnection->henv );
      if( ! SQL_SUCCEEDED(sqlRetCode) )
      {
         TA_TRACE_RETURN( TA_INVALID_HANDLE );
      }
      
      TA_Free( privConnection );
   }

   TA_TRACE_RETURN( TA_SUCCESS );
}

static TA_RetCode allocRowData( TA_UNIXODBC_Statement *statement )
{
   int col;

   statement->rowData = TA_Malloc( statement->numCols * sizeof(char*) );
   if( statement->rowData == NULL )
   {
      return TA_ALLOC_ERR;
   }
   memset( statement->rowData, 0, statement->numCols * sizeof(char*) );

   statement->rowIndicator = TA_Malloc( statement->numCols * sizeof(SQLINTEGER) );
   if( statement->rowIndicator == NULL )
   {
      return TA_ALLOC_ERR;
   }
   memset( statement->rowIndicator, 0, statement->numCols * sizeof(SQLINTEGER) );
   
   for( col = 0;  col < statement->numCols;  col++)
   {
      int size = 0;
      SQLSMALLINT ctype;

      switch( statement->columns[col].datatype ) 
      {
         case SQL_CHAR:
         case SQL_VARCHAR:
         case SQL_DATETIME:
         case SQL_TYPE_TIME:
         case SQL_TYPE_DATE:
         case SQL_TYPE_TIMESTAMP:
            size = statement->columns[col].size + 1;  /* add 1 for terminating '\0' */
            ctype = SQL_C_CHAR;
         	break;

         case SQL_NUMERIC:
         case SQL_DECIMAL:
         case SQL_FLOAT:
         case SQL_REAL:
         case SQL_DOUBLE:
            size = sizeof( double );
            ctype = SQL_C_DOUBLE;
            break;

         case SQL_SMALLINT:
         case SQL_INTEGER:
            size = sizeof( long );
            ctype = SQL_C_SLONG;
            break;

         default:
            ; /* ignore other column types */
      }
      if( size > 0 )
      {
         statement->rowData[col] = TA_Malloc(size);
         if( statement->rowData[col] == NULL )
         {
            freeRowData( statement );
            return TA_ALLOC_ERR;
         }
         statement->columns[col].ctype = ctype;
      }
   }
   
   return TA_SUCCESS;
}



static TA_RetCode freeRowData( TA_UNIXODBC_Statement *statement )
{
   int col;

   if( statement->rowData != NULL )
   {
      for( col = 0;  col < statement->numCols;  col++)
      {
         if( statement->rowData[col] != NULL )
         {
            TA_Free( statement->rowData[col] );
         }
      }
      TA_Free( statement->rowData );
      statement->rowData = NULL;
   }

   if( statement->rowIndicator != NULL)
   {
      TA_Free( statement->rowIndicator );
      statement->rowIndicator = NULL;
   }

   return TA_SUCCESS;
}
