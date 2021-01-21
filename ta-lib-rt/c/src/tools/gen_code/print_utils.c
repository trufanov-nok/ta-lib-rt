#include "print_utils.h"
#include <stdio.h>
#include <ctype.h>

char gTempDoubleToStr[200];

const char *doubleToStr( double value )
{
   int length;
   int i, outIdx;
   sprintf( gTempDoubleToStr, "%e", value );

   /* Remove extra "0" added by Microsoft in the
    * exponential part.
    */
   length = (int)strlen( gTempDoubleToStr );
   outIdx = 0;
   for( i=0; i < length; i++ )
   {
      /* Will skip two leading zero in the exponent */
      if( (i >= 2) &&
          (toupper(gTempDoubleToStr[i-2]) == 'E') &&
          ((gTempDoubleToStr[i-1] == '+')||(gTempDoubleToStr[i-1] == '-')) &&
          (gTempDoubleToStr[i] == '0') &&
          (gTempDoubleToStr[i+1] == '0') &&
          (isdigit(gTempDoubleToStr[i+2])) )
      {
         i++;
         continue;
      }

      /* Will skip one leading zero in the exponent */
      if( (i >= 2) &&
          (toupper(gTempDoubleToStr[i-2]) == 'E') &&
          ((gTempDoubleToStr[i-1] == '+')||(gTempDoubleToStr[i-1] == '-')) &&
          (gTempDoubleToStr[i] == '0') &&
          (isdigit(gTempDoubleToStr[i+1])))
      {
         continue;
      }

      gTempDoubleToStr[outIdx++] = gTempDoubleToStr[i];
   }
   gTempDoubleToStr[outIdx] = '\0';

   return gTempDoubleToStr;
}

void cnvtToUpperCase( char *str )
{
   char c;

   if( !str ) return;

   c = *str;
   while( c != '\0' )
   {
      *str = (char)toupper(c);
      str++;
      c = *str;
   }
}

char *trimWhitespace( char *str )
{
   int i;

   if( !str ) return str;

   while( isspace(*str) ) str++;
   if( *str == '\0' ) return str;

   for( i=(int)strlen(str)-1; i >= 0; i-- )
   {
      if( !isspace(str[i]) )
         return str;
      str[i] = '\0';
   }

   return str;
}

void cnvtChar( char *str, char from, char to )
{
   char c;

   if( !str ) return;

   c = *str;
   while( c != '\0' )
   {
      if( c == from ) *str = to;
      str++;
      c = *str;
   }
}


/* Replaces reserved xml characters with the appropriate escape sequence. */
void ReplaceReservedXmlCharacters(const char *input, char *output )
{
    char *currentPosition;
    char tempString[8*1024];

    if((input == NULL) || (output == NULL))
    {
        return;
    }

    strcpy(output, input);

    /*Replace '&' with "&amp;"
     *Note1: '&' has to be processed first as otherwise we replace the
     *       '&' in the escaped characters.
     *Note2: We assume that the input string does not have any escaped
     *       characters already.
     */
    currentPosition = output;
    while((currentPosition = strchr(currentPosition, '&')) != NULL)
    {
        tempString[0] = '\0';
        if(strlen(currentPosition) > 1)
        {
            strcpy(tempString, currentPosition+1);
        }
        sprintf(currentPosition, "&amp;%s", tempString);
    }

    /* Replace '<' with "&lt;" */
    currentPosition = output;
    while((currentPosition = strchr(currentPosition, '<')) != NULL)
    {
        tempString[0] = '\0';
        if(strlen(currentPosition) > 1)
        {
            strcpy(tempString, currentPosition+1);
        }
        sprintf(currentPosition, "&lt;%s", tempString);
    }

    /* Replace '>' with "&gt;" */
    currentPosition = output;
    while((currentPosition = strchr(currentPosition, '>')) != NULL)
    {
        tempString[0] = '\0';
        if(strlen(currentPosition) > 1)
        {
            strcpy(tempString, currentPosition+1);
        }
        sprintf(currentPosition, "&gt;%s", tempString);
    }

    /* Replace ''' with "&apos;" */
    currentPosition = output;
    while((currentPosition = strchr(currentPosition, '\'')) != NULL)
    {
        tempString[0] = '\0';
        if(strlen(currentPosition) > 1)
        {
            strcpy(tempString, currentPosition+1);
        }
        sprintf(currentPosition, "&apos;%s", tempString);
    }

    /* Replace '"' with "&quot;" */
    currentPosition = output;
    while((currentPosition = strchr(currentPosition, '"')) != NULL)
    {
        tempString[0] = '\0';
        if(strlen(currentPosition) > 1)
        {
            strcpy(tempString, currentPosition+1);
        }
        sprintf(currentPosition, "&quot;%s", tempString);
    }
}

