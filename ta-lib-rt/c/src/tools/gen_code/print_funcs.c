#include "print_funcs.h"

TA_RetCode listInputParameters(char* buf, const TA_FuncInfo *funcInfo, char* separator, char* postfix)
{
 unsigned int i, buf_idx = 0;
 buf[0] = '\0';
 const TA_InputParameterInfo *inputParamInfo;
 const char *paramName;
 TA_RetCode retCode;

 for ( i = 0; i < funcInfo->nbInput; ++i )
 {
    retCode = TA_GetInputParameterInfo( funcInfo->handle,
                                        i, &inputParamInfo );

    if( retCode != TA_SUCCESS )
    {
       printf( "[%s] invalid 'input' information (%d,%d)\n", funcInfo->name, i, funcInfo->nbInput );
       return retCode;
    }

    paramName = inputParamInfo->paramName;

    switch( inputParamInfo->type )
    {
    case TA_Input_Price:
        if( inputParamInfo->flags & TA_IN_PRICE_OPEN ) {
            paramName = "inOpen";
            buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx; }
        if( inputParamInfo->flags & TA_IN_PRICE_HIGH ) {
            paramName = "inHigh";
            buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx; }
        if( inputParamInfo->flags & TA_IN_PRICE_LOW ) {
            paramName = "inLow";
            buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx; }
        if( inputParamInfo->flags & TA_IN_PRICE_CLOSE ) {
            paramName = "inClose";
            buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx; }
         if( inputParamInfo->flags & TA_IN_PRICE_VOLUME ) {
            paramName = "inVolume";
            buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx; }
        if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST ) {
            paramName = "inOpenInterest";
            buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx; }
        break;
    case TA_Input_Real:
    case TA_Input_Integer:
    case TA_Input_Pointer:
    default:
       if( !paramName )
          paramName = "inParam";
    }

  if (inputParamInfo->type != TA_Input_Price)
  buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx;
 }

 return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}


#include "print_funcs.h"

TA_RetCode listOptInputParameters(char* buf, const TA_FuncInfo *funcInfo, char* separator, char* postfix)
{
 unsigned int i, buf_idx = 0;
 buf[0] = '\0';
 const TA_OptInputParameterInfo *optInputParamInfo;
 const char *paramName;
 const char *defaultParamName;

 TA_RetCode retCode;

 for ( i = 0; i < funcInfo->nbOptInput; ++i )
 {
    retCode = TA_GetOptInputParameterInfo( funcInfo->handle,
                                        i, &optInputParamInfo );

    if( retCode != TA_SUCCESS )
    {
       printf( "[%s] invalid 'input' information (%d,%d)\n", funcInfo->name, i, funcInfo->nbInput );
       return retCode;
    }

    paramName = optInputParamInfo->paramName;

    switch( optInputParamInfo->type )
    {
    case TA_OptInput_RealRange:
    case TA_OptInput_RealList:
       defaultParamName = "optInReal";
       break;
    case TA_OptInput_IntegerRange:
       defaultParamName = "optInInteger";
       break;
    case TA_OptInput_IntegerList:
       if( optInputParamInfo->dataSet == TA_DEF_UI_MA_Method.dataSet )
          defaultParamName = "optInMAType";
       else
          defaultParamName = "optInInteger";
       break;
    }

  if( !paramName )
       paramName = defaultParamName;

  buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s", (buf_idx)?separator:"", paramName, (postfix)?postfix:"") + buf_idx;
 }

 return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}


#include "print_funcs.h"

TA_RetCode listOutputParameters(char* buf, const TA_FuncInfo *funcInfo, char* separator, char* postfix, char* prefix, int with_type)
{
 unsigned int i, buf_idx = 0;
 buf[0] = '\0';
 const TA_OutputParameterInfo *outputParamInfo;
 const char *paramName;
 const char *typeName;
 const char *defaultParamName;
 TA_RetCode retCode;

 for ( i = 0; i < funcInfo->nbOutput; ++i )
 {
    retCode = TA_GetOutputParameterInfo( funcInfo->handle,
                                        i, &outputParamInfo );

    if( retCode != TA_SUCCESS )
    {
       printf( "[%s] invalid 'input' information (%d,%d)\n", funcInfo->name, i, funcInfo->nbInput );
       return retCode;
    }

    paramName = outputParamInfo->paramName;

    switch( outputParamInfo->type )
    {
    case TA_Output_Real:
       defaultParamName = "outReal";
       typeName = "double ";
       break;
    case TA_Output_Integer:
       defaultParamName = "outInteger";
       typeName = "int ";
       break;
    default:
       if( !paramName )
          paramName = "outParam";
    }

    if( !paramName )
         paramName = defaultParamName;

  buf_idx = sprintf(((char *)buf)+buf_idx, "%s%s%s%s%s", (with_type)?typeName:"", (buf_idx)?separator:"", (prefix)?prefix:"", paramName, (postfix)?postfix:"") + buf_idx;
 }

 return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}


TA_RetCode printStateTestFunc(FILE* out, const TA_FuncInfo *funcInfo)
{
    print(out, "#ifdef TEST_STATE_FUNCS\n");
    printFunc(out, "", funcInfo, pfs_prototype | pfs_stateTestSignature);
    print(out, "{\n");

    char inputArgs[500];
    char optInputArgs[500];
    char outputArgs[500];

    listInputParameters(inputArgs, funcInfo, ", ", NULL);
    listOptInputParameters(optInputArgs, funcInfo, ", ", NULL);
    listOutputParameters(outputArgs, funcInfo, ", ", NULL, NULL, 0);

    print(out, " TA_RetCode res = TA_%s(startIdx, endIdx, %s, %s%soutBegIdx, outNBElement, %s );\n", funcInfo->name, inputArgs, optInputArgs, strlen(optInputArgs)?", ":"", outputArgs);
    print(out, " if (res != ENUM_VALUE(RetCode,TA_SUCCESS,Success)) return ENUM_VALUE(RetCode,TA_SUCCESS,Success); //Din't compare exceptional cases\n");
    print(out, " struct TA_%s_State* state;\n", funcInfo->name);
    print(out, " res = TA_%s_StateInit(&state%s%s);\n", funcInfo->name, strlen(optInputArgs)?", ":"", optInputArgs);
    print(out, " if (res != ENUM_VALUE(RetCode,TA_SUCCESS,Success)) return res;\n");
    print(out, " int i, lookback;\n");
    print(out, " lookback = TA_%s_Lookback(%s);\n", funcInfo->name, optInputArgs);
    print(out, " int res_start = 0;\n");
    print(out, " i = ( startIdx <= lookback )? lookback: startIdx;\n");
    print(out, " if (i <= endIdx) {\n");
    print(out, " i -= lookback;\n");
    print(out, " #ifdef TEST_WHOLE_DATA_%s\n", funcInfo->name);
    print(out, "   i = 0;\n");
    print(out, " #endif\n");
    print(out, " int first_iteration;\n");
    print(out, " first_iteration = 1;\n");
    print(out, " while (i <= endIdx)\n");
    print(out, "   {\n");

    // to test save/loade state
    print(out, "    if (_file != NULL && !first_iteration ) {\n");
    print(out, "     first_iteration = 0;\n");
    print(out, "     if (fseek(_file, 0, SEEK_SET) != 0) return ENUM_VALUE(RetCode,TA_IO_FAILED, IOFailed);\n");
    print(out, "     res = TA_%s_StateFree(&state);\n", funcInfo->name);
    print(out, "     if (res != ENUM_VALUE(RetCode,TA_SUCCESS,Success)) return res;\n");
    print(out, "     state = NULL;\n");
    print(out, "     res = TA_%s_StateLoad(&state, _file);\n", funcInfo->name);
    print(out, "     if (res != ENUM_VALUE(RetCode,TA_SUCCESS,Success)) return res;\n");
    print(out, "    }\n");

    listInputParameters(inputArgs, funcInfo, ", ", "[i]");
    listOutputParameters(outputArgs, funcInfo, " ", "_local;", NULL, 1);
    print(out, "    %s\n", outputArgs);
    listOutputParameters(outputArgs, funcInfo, ", ", "_local", "&", 0);
    print(out, "    res = TA_%s_State(state, %s, %s);\n", funcInfo->name, inputArgs, outputArgs);

    // to test save/loade state
    print(out, "    if (_file != NULL) {\n");
    print(out, "        if (fseek(_file, 0, SEEK_SET) != 0) return ENUM_VALUE(RetCode,TA_IO_FAILED, IOFailed);\n");
    print(out, "        int io_res;\n");
    print(out, "        io_res = TA_%s_StateSave(state, _file);\n", funcInfo->name);
    print(out, "        if (io_res != ENUM_VALUE(RetCode,TA_SUCCESS,Success)) return io_res;\n");
    print(out, "    }\n");

    print(out, "    if (i++ < startIdx) continue;\n");
    print(out, "    if (res != ENUM_VALUE(RetCode,TA_SUCCESS,Success)) {\n");
    print(out, "      if (res == ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData) ) continue;\n");
    print(out, "         else break; }\n");


    listOutputParameters(outputArgs, funcInfo, ",", NULL, NULL, 0);
    int word_idx = 0;
    char word[500];
    int i = 0;
    while (1)
    {
        char c = outputArgs[i++];

        if ((c == ',') || ( c == '\0'))
        {
            word[word_idx] = '\0';
            if (word_idx > 0)
            {
             print( out, "    if(fabs(%s[res_start] - %s_local) > 1e-6) {res = ENUM_VALUE(RetCode,TA_INTERNAL_ERROR, InternalError); break;}\n", word, word);
            }
            word_idx = 0;
            if (c == '\0') break;
        } else
            if (c != ' ')
            word[word_idx++] = c;
    }

    print(out, "++res_start;\n");
    print(out, "   }\n");
    print(out, " }\n");

    print(out, " TA_RetCode r = TA_%s_StateFree(&state);\n", funcInfo->name);

    print(out, "return (res != ENUM_VALUE(RetCode,TA_SUCCESS,Success))?res:r;\n");
    print(out, "}\n");
    print(out, "#endif\n");

    return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}
