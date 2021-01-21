#include "print_funcs_xml.h"

#include "ta_abstract.h"
#include "ta_def_ui.h"

#include "print_utils.h"


extern const TA_OptInputParameterInfo TA_DEF_UI_MA_Method;

char tempString[8*1024];
#define tabs5 '\t','\t','\t','\t','\t'
#define tabs10 tabs5, tabs5
#define tabs20 tabs10, tabs10
char t[20] = {tabs20};

void print_input_arg(FILE *file, int indent, const TA_InputParameterInfo *inputInfo, const char* field_name, int is_array)
{

    if(inputInfo->type == TA_Input_Price)
    {
        if(inputInfo->flags & TA_IN_PRICE_OPEN)
        {
            fprintf(file, "%.*s<%s>\n",  indent+1, t, field_name);
            fprintf(file, "%.*s<Type>Double</Type>\n", indent+2, t);
            fprintf(file, "%.*s<Name>Open</Name>\n",   indent+2, t);
            fprintf(file, "%.*s</%s>\n", indent+1, t, field_name);
        }
        if(inputInfo->flags & TA_IN_PRICE_HIGH)
        {
            fprintf(file, "%.*s<%s>\n",  indent+1, t, field_name);
            fprintf(file, "%.*s<Type>Double</Type>\n", indent+2, t);
            fprintf(file, "%.*s<Name>High</Name>\n",   indent+2, t);
            fprintf(file, "%.*s</%s>\n", indent+1, t, field_name);
        }
        if(inputInfo->flags & TA_IN_PRICE_LOW)
        {
            fprintf(file, "%.*s<%s>\n",  indent+1, t, field_name);
            fprintf(file, "%.*s<Type>Double</Type>\n", indent+2, t);
            fprintf(file, "%.*s<Name>Low</Name>\n",    indent+2, t);
            fprintf(file, "%.*s</%s>\n", indent+1, t, field_name);
        }
        if(inputInfo->flags & TA_IN_PRICE_CLOSE)
        {
            fprintf(file, "%.*s<%s>\n",  indent+1, t, field_name);
            fprintf(file, "%.*s<Type>Double</Type>\n", indent+2, t);
            fprintf(file, "%.*s<Name>Close</Name>\n",  indent+2, t);
            fprintf(file, "%.*s</%s>\n", indent+1, t, field_name);
        }
        if(inputInfo->flags & TA_IN_PRICE_VOLUME)
        {
            fprintf(file, "%.*s<%s>\n",  indent+1, t, field_name);
            fprintf(file, "%.*s<Type>Double</Type>\n", indent+2, t);
            fprintf(file, "%.*s<Name>Volume</Name>\n", indent+2, t);
            fprintf(file, "%.*s</%s>\n", indent+1, t, field_name);
        }
        if(inputInfo->flags & TA_IN_PRICE_OPENINTEREST)
        {
            fprintf(file, "%.*s<%s>\n",          indent+1, t, field_name);
            fprintf(file, "%.*s<Type>Double</Type>\n",         indent+2, t);
            fprintf(file, "%.*s<Name>Open Interest</Name>\n",  indent+2, t);
            fprintf(file, "%.*s</%s>\n",         indent+1, t, field_name);
        }
        if(inputInfo->flags & TA_IN_PRICE_TIMESTAMP)
        {
            fprintf(file, "%.*s<%s>\n",      indent+1, t, field_name);
            fprintf(file, "%.*s<Type>Long</Type>\n",       indent+2, t);
            fprintf(file, "%.*s<Name>Timestamp</Name>\n",  indent+2, t);
            fprintf(file, "%.*s</%s>\n",     indent+1, t, field_name);
        }
    }
    else
    {
        fprintf(file, "%.*s<%s>\n", indent+1, t, field_name);
        if(inputInfo->type == TA_Input_Real)
        {
            fprintf(file, "%.*s<Type>Double%s</Type>\n", indent+2, t, is_array ? " Array" : "");
        }
        else if(inputInfo->type == TA_Input_Integer)
        {
            fprintf(file, "%.*s<Type>Integer%s</Type>\n", indent+2, t, is_array ? " Array" : "");
        }
        else if(inputInfo->type == TA_Input_Pointer)
        {
            fprintf(file, "%.*s<Type>Pointer</Type>\n", indent+2, t);
        }
        else
        {
            printf("Error: Unknown state memory field detected.\n");
        }
        fprintf(file, "%.*s<Name>%s</Name>\n", indent+2, t, inputInfo->paramName);
        fprintf(file, "%.*s</%s>\n", indent+1, t, field_name);
    }

}


void print_arguments_input_required(FILE *file, int indent, const struct TA_FuncInfo *funcInfo, int is_array)
{
    TA_RetCode retCode;
    const TA_InputParameterInfo *inputInfo;
    unsigned int i;

    /* Required input arguments */
    fprintf(file, "%.*s<RequiredInputArguments>\n", indent, t);

    if (is_array) {
        fprintf(file, "%.*s<RequiredInputArgument>\n",  indent+1, t);
        fprintf(file, "%.*s<Type>Integer</Type>\n",     indent+2, t);
        fprintf(file, "%.*s<Name>startIdx</Name>\n",    indent+2, t);
        fprintf(file, "%.*s</RequiredInputArgument>\n", indent+1, t);

        fprintf(file, "%.*s<RequiredInputArgument>\n",  indent+1, t);
        fprintf(file, "%.*s<Type>Integer</Type>\n",     indent+2, t);
        fprintf(file, "%.*s<Name>endIdx</Name>\n",      indent+2, t);
        fprintf(file, "%.*s</RequiredInputArgument>\n", indent+1, t);
    }

    for(i=0; i<funcInfo->nbInput; i++)
    {
        retCode = TA_GetInputParameterInfo( funcInfo->handle, i, &inputInfo);

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetInputParameterInfo (%d)\n", retCode );
           return;
        }

        print_input_arg(file, indent, inputInfo, "RequiredInputArgument", is_array);
    }
    fprintf(file, "%.*s</RequiredInputArguments>\n", indent, t);
}

void print_opt_input_arg(FILE *file, int indent, const TA_OptInputParameterInfo * optInputInfo, const char* field_name)
{
    fprintf(file, "%.*s<%s>\n", indent, t, field_name);
    fprintf(file, "%.*s<Name>%s</Name>\n", indent+1, t, optInputInfo->displayName);
    ReplaceReservedXmlCharacters(optInputInfo->hint, tempString);
    fprintf(file, "%.*s<ShortDescription>%s</ShortDescription>\n", indent+1, t, (optInputInfo->hint == NULL)? "" : tempString);
    if(optInputInfo->flags != 0)
    {
        fprintf(file, "%.*s<Flags>\n", indent+1, t);

        if(optInputInfo->flags & TA_OPTIN_IS_PERCENT)
        {
            fprintf(file, "%.*s<Flag>Percent</Flag>\n", indent+2, t);
        }
        if(optInputInfo->flags & TA_OPTIN_IS_DEGREE)
        {
            fprintf(file, "%.*s<Flag>Degree</Flag>\n",  indent+2, t);
        }
        if(optInputInfo->flags & TA_OPTIN_IS_CURRENCY)
        {
            fprintf(file, "%.*s<Flag>Currency</Flag>\n", indent+2, t);
        }
        if(optInputInfo->flags & TA_OPTIN_ADVANCED)
        {
            fprintf(file, "%.*s<Flag>Advanced</Flag>\n", indent+2, t);
        }

        fprintf(file, "%.*s</Flags>\n", indent+1, t);
    }

    if(optInputInfo->type == TA_OptInput_RealRange)
    {
        TA_RealRange *doubleRange;

        doubleRange= (TA_RealRange*)optInputInfo->dataSet;
        fprintf(file, "%.*s<Type>Double</Type>\n", indent+1, t);
        fprintf(file, "%.*s<Range>\n", indent+1, t);
        fprintf(file, "%.*s<Minimum>%s</Minimum>\n", indent+2, t, doubleToStr(doubleRange->min));
        fprintf(file, "%.*s<Maximum>%s</Maximum>\n", indent+2, t, doubleToStr(doubleRange->max));
        fprintf(file, "%.*s<Precision>%d</Precision>\n", indent+2, t, doubleRange->precision);
        fprintf(file, "%.*s<SuggestedStart>%s</SuggestedStart>\n", indent+2, t, doubleToStr(doubleRange->suggested_start));
        fprintf(file, "%.*s<SuggestedEnd>%s</SuggestedEnd>\n", indent+2, t, doubleToStr(doubleRange->suggested_end));
        fprintf(file, "%.*s<SuggestedIncrement>%s</SuggestedIncrement>\n", indent+2, t, doubleToStr(doubleRange->suggested_increment));
        fprintf(file, "%.*s</Range>\n", indent+1, t);
        fprintf(file, "%.*s<DefaultValue>%s</DefaultValue>\n", indent+1, t, doubleToStr(optInputInfo->defaultValue));
    }
    else if(optInputInfo->type == TA_OptInput_IntegerRange)
    {
        TA_IntegerRange *integerRange;

        integerRange = (TA_IntegerRange*)optInputInfo->dataSet;
        fprintf(file, "%.*s<Type>Integer</Type>\n", indent+1, t);
        fprintf(file, "%.*s<Range>\n", indent+1, t);
        fprintf(file, "%.*s<Minimum>%d</Minimum>\n", indent+2, t, integerRange->min);
        fprintf(file, "%.*s<Maximum>%d</Maximum>\n", indent+2, t, integerRange->max);
        fprintf(file, "%.*s<SuggestedStart>%d</SuggestedStart>\n", indent+2, t, integerRange->max);
        fprintf(file, "%.*s<SuggestedEnd>%d</SuggestedEnd>\n", indent+2, t, integerRange->max);
        fprintf(file, "%.*s<SuggestedIncrement>%d</SuggestedIncrement>\n", indent+2, t, integerRange->max);
        fprintf(file, "%.*s</Range>\n", indent+1, t);
        fprintf(file, "%.*s<DefaultValue>%d</DefaultValue>\n", indent+1, t, (int)optInputInfo->defaultValue);
    }
    else if(optInputInfo->type == TA_OptInput_IntegerList)
    {
        TA_IntegerList *intList;

        intList = (TA_IntegerList*) optInputInfo->dataSet;
        fprintf(file, "%.*s<Type>MA Type</Type>\n", indent+1, t);
        fprintf(file, "%.*s<DefaultValue>%d</DefaultValue>\n", indent+1, t, (int)optInputInfo->defaultValue);
        if( intList != (TA_IntegerList*) TA_DEF_UI_MA_Method.dataSet )
        {
            printf("Integer lists are not supported.\n");
        }
    }
    else
    {
        printf("Unknown optional input type detected.\n");
    }

    fprintf(file, "%.*s</%s>\n", indent, t, field_name);
}

void print_arguments_input_optional(FILE *file, int indent, const struct TA_FuncInfo *funcInfo)
{
    TA_RetCode retCode;
    const TA_OptInputParameterInfo *optInputInfo;
    unsigned int i;

    /* Optional input arguments */
    if(funcInfo->nbOptInput > 0)
    {

        fprintf(file, "%.*s<OptionalInputArguments>\n", indent, t);
        for(i=0; i<funcInfo->nbOptInput; i++)
        {
            retCode = TA_GetOptInputParameterInfo( funcInfo->handle, i, &optInputInfo );

            if( retCode != TA_SUCCESS )
            {
               printf( "Error in TA_GetOptInputParameterInfo (%d)\n", retCode );
               return;
            }

            print_opt_input_arg(file, indent+1, optInputInfo, "OptionalInputArgument");
        }
        fprintf(file, "%.*s</OptionalInputArguments>\n", indent, t);
    }
}


void print_arguments_output(FILE *file, int indent, const struct TA_FuncInfo *funcInfo, int is_array)
{
    TA_RetCode retCode;
    const TA_OutputParameterInfo *outputInfo;
    unsigned int i;

    /* Output arguments */
    fprintf(file, "%.*s<OutputArguments>\n", indent, t);

    if (is_array) {
        fprintf(file, "%.*s<OutputArgument>\n",  indent+1, t);
        fprintf(file, "%.*s<Type>Pointer to Integer</Type>\n",     indent+2, t);
        fprintf(file, "%.*s<Name>outBegIdx</Name>\n",    indent+2, t);
        fprintf(file, "%.*s</OutputArgument>\n", indent+1, t);

        fprintf(file, "%.*s<OutputArgument>\n",  indent+1, t);
        fprintf(file, "%.*s<Type>Pointer to Integer</Type>\n",     indent+2, t);
        fprintf(file, "%.*s<Name>outNBElement</Name>\n",    indent+2, t);
        fprintf(file, "%.*s</OutputArgument>\n", indent+1, t);
    }

    for(i=0; i<funcInfo->nbOutput; i++)
    {
        retCode = TA_GetOutputParameterInfo( funcInfo->handle, i, &outputInfo );

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOutputParameterInfo (%d)\n", retCode );
           return;
        }

        fprintf(file, "%.*s<OutputArgument>\n", indent+1, t);
        if(outputInfo->type == TA_Output_Integer)
        {
            fprintf(file, "%.*s<Type>Integer%s</Type>\n", indent+2, t, is_array ? " Array" : "");
        }
        else if(outputInfo->type == TA_Output_Real)
        {
            fprintf(file, "%.*s<Type>Double%s</Type>\n", indent+2, t, is_array ? " Array" : "");
        }
        else
        {
            printf("Unknown output type detected.\n");
        }
        fprintf(file, "%.*s<Name>%s</Name>\n", indent+2, t, outputInfo->paramName);
        if(outputInfo->flags != 0)
        {
            fprintf(file, "%.*s<Flags>\n", indent+2, t);

            if(outputInfo->flags & TA_OUT_LINE)
            {
                fprintf(file, "%.*s<Flag>Line</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_DOT_LINE)
            {
                fprintf(file, "%.*s<Flag>Dotted Line</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_DASH_LINE)
            {
                fprintf(file, "%.*s<Flag>Dashed Line</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_DOT)
            {
                fprintf(file, "%.*s<Flag>Dots</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_HISTO)
            {
                fprintf(file, "%.*s<Flag>Histogram</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_PATTERN_BOOL)
            {
                fprintf(file, "%.*s<Flag>Pattern Bool</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_PATTERN_BULL_BEAR)
            {
                fprintf(file, "%.*s<Flag>Pattern Bull Bear</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_PATTERN_STRENGTH)
            {
                fprintf(file, "%.*s<Flag>Pattern Strength</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_POSITIVE)
            {
                fprintf(file, "%.*s<Flag>Positive</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_NEGATIVE)
            {
                fprintf(file, "%.*s<Flag>Negative</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_ZERO)
            {
                fprintf(file, "%.*s<Flag>Zero</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_UPPER_LIMIT)
            {
                fprintf(file, "%.*s<Flag>Upper Limit</Flag>\n", indent+3, t);
            }
            if(outputInfo->flags & TA_OUT_LOWER_LIMIT)
            {
                fprintf(file, "%.*s<Flag>Lower Limit</Flag>\n", indent+3, t);
            }

            fprintf(file, "%.*s</Flags>\n", indent+2, t);
        }
        fprintf(file, "%.*s</OutputArgument>\n", indent+1, t);
    }
    fprintf(file, "%.*s</OutputArguments>\n", indent, t);
}


void print_state_memory(FILE *file, int indent, const struct TA_FuncInfo *funcInfo)
{
    TA_RetCode retCode;
    const TA_InputParameterInfo *inputInfo;
    unsigned int i;


    /* State struct memory is the same as state func input arguments */
    fprintf(file, "%.*s<StateMemory>\n", indent, t);
    for(i=0; i<funcInfo->nbInput; i++)
    {
        retCode = TA_GetInputParameterInfo( funcInfo->handle, i, &inputInfo);
        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetInputParameterInfo (%d)\n", retCode );
           return;
        }

        print_input_arg(file, indent, inputInfo, "StateMemoryField", 0);

    }
    fprintf(file, "%.*s</StateMemory>\n", indent, t);
}

void print_state_struct(FILE *file, int indent, const struct TA_FuncInfo *funcInfo)
{
    TA_RetCode retCode;
    const TA_InputParameterInfo *inputInfo;
    unsigned int i;


    fprintf(file, "%.*s<State>\n", indent, t);
    fprintf(file, "%.*s<StateField>\n",  indent+1, t);
    fprintf(file, "%.*s<Type>Integer</Type>\n",  indent+2, t);
    fprintf(file, "%.*s<Name>mem_size</Name>\n", indent+2, t);
    fprintf(file, "%.*s</StateField>\n", indent+1, t);
    fprintf(file, "%.*s<StateField>\n",  indent+1, t);
    fprintf(file, "%.*s<Type>Integer</Type>\n",  indent+2, t);
    fprintf(file, "%.*s<Name>mem_index</Name>\n",indent+2, t);
    fprintf(file, "%.*s</StateField>\n", indent+1, t);
    fprintf(file, "%.*s<StateField>\n",  indent+1, t);
    fprintf(file, "%.*s<Type>Pointer</Type>\n",  indent+2, t);
    fprintf(file, "%.*s<Name>memory</Name>\n",   indent+2, t);
    fprintf(file, "%.*s</StateField>\n", indent+1, t);


    for(i=0; i<funcInfo->nbStructParams; i++)
    {
        retCode = TA_GetStructParameterInfo( funcInfo->handle, i, &inputInfo);

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetStructParameterInfo (%d)\n", retCode );
           return;
        }

        print_input_arg(file, indent, inputInfo, "StateField", 0);
      }

    fprintf(file, "%.*s</State>\n", indent, t);
}

void print_lookback_function(FILE *file, int indent, const struct TA_FuncInfo *funcInfo)
{
    fprintf(file, "%.*s<Function>\n", indent, t);
    fprintf(file, "%.*s<Name>TA_%s_Lookback</Name>\n", indent+1, t, (funcInfo->name == NULL)? "" : funcInfo->name);
    fprintf(file, "%.*s<Type>Lookback</Type>\n", indent+1, t);
    fprintf(file, "%.*s<ReturnValue>Integer</ReturnValue>\n", indent+1, t);

    print_arguments_input_optional(file, indent+1, funcInfo);

    fprintf(file, "%.*s</Function>\n", indent, t);
}

void print_regular_function(FILE *file, int indent, const struct TA_FuncInfo *funcInfo)
{
    fprintf(file, "%.*s<Function>\n", indent, t);
    fprintf(file, "%.*s<Name>TA_%s</Name>\n", indent+1, t, (funcInfo->name == NULL)? "" : funcInfo->name);
    fprintf(file, "%.*s<Type>Regular</Type>\n", indent+1, t);
    fprintf(file, "%.*s<ReturnValue>TA_Result</ReturnValue>\n", indent+1, t);

    print_arguments_input_required(file, indent+1, funcInfo, 1);
    print_arguments_input_optional(file, indent+1, funcInfo);
    print_arguments_output(file, indent+1, funcInfo, 1);

    fprintf(file, "%.*s</Function>\n", indent, t);
}

void print_state_init_or_free_function(FILE *file, int indent, const struct TA_FuncInfo *funcInfo, int is_free)
{
    fprintf(file, "%.*s<Function>\n", indent, t);
    fprintf(file, "%.*s<Name>TA_%s_State%s</Name>\n", indent+1, t, (funcInfo->name == NULL)? "" : funcInfo->name, is_free ? "Free" : "Init");
    fprintf(file, "%.*s<Type>State%s</Type>\n", indent+1, t, is_free ? "Free" : "Init");
    fprintf(file, "%.*s<ReturnValue>TA_Result</ReturnValue>\n", indent+1, t);

    fprintf(file, "%.*s<SpecialInputArguments>\n",  indent+1, t);
    fprintf(file, "%.*s<SpecialInputArgument>\n",  indent+2, t);
    fprintf(file, "%.*s<Type>Pointer to Pointer</Type>\n",     indent+3, t);
    fprintf(file, "%.*s<Name>state</Name>\n",    indent+3, t);
    fprintf(file, "%.*s</SpecialInputArgument>\n", indent+2, t);
    fprintf(file, "%.*s</SpecialInputArguments>\n", indent+1, t);

    if (!is_free) {
        print_arguments_input_optional(file, indent+1, funcInfo);
    }

    fprintf(file, "%.*s</Function>\n", indent, t);
}

void print_state_save_or_load_function(FILE *file, int indent, const struct TA_FuncInfo *funcInfo, int is_save)
{
    fprintf(file, "%.*s<Function>\n", indent, t);
    fprintf(file, "%.*s<Name>TA_%s_State%s</Name>\n", indent+1, t, (funcInfo->name == NULL)? "" : funcInfo->name, is_save ? "Save" : "Load");
    fprintf(file, "%.*s<Type>State%s</Type>\n", indent+1, t, is_save ? "Save" : "Load");
    fprintf(file, "%.*s<ReturnValue>TA_Result</ReturnValue>\n", indent+1, t);

    fprintf(file, "%.*s<SpecialInputArguments>\n",  indent+1, t);
    fprintf(file, "%.*s<SpecialInputArgument>\n",  indent+2, t);
    fprintf(file, "%.*s<Type>Pointer%s</Type>\n",     indent+3, t, is_save ? "" : " to Pointer");
    fprintf(file, "%.*s<Name>state</Name>\n",    indent+3, t);
    fprintf(file, "%.*s</SpecialInputArgument>\n", indent+2, t);

    fprintf(file, "%.*s<SpecialInputArgument>\n",  indent+2, t);
    fprintf(file, "%.*s<Type>Pointer to File</Type>\n",     indent+3, t);
    fprintf(file, "%.*s<Name>file</Name>\n",    indent+3, t);
    fprintf(file, "%.*s</SpecialInputArgument>\n", indent+2, t);

    fprintf(file, "%.*s</SpecialInputArguments>\n", indent+1, t);

    print_arguments_input_optional(file, indent+1, funcInfo);

    fprintf(file, "%.*s</Function>\n", indent, t);
}

void print_state_function(FILE *file, int indent, const struct TA_FuncInfo *funcInfo)
{
    fprintf(file, "%.*s<Function>\n", indent, t);
    fprintf(file, "%.*s<Name>TA_%s_State</Name>\n", indent+1, t, (funcInfo->name == NULL)? "" : funcInfo->name);
    fprintf(file, "%.*s<Type>State</Type>\n", indent+1, t);
    fprintf(file, "%.*s<ReturnValue>TA_Result</ReturnValue>\n", indent+1, t);

    fprintf(file, "%.*s<SpecialInputArguments>\n",  indent+1, t);
    fprintf(file, "%.*s<SpecialInputArgument>\n",  indent+2, t);
    fprintf(file, "%.*s<Type>Pointer</Type>\n",     indent+3, t);
    fprintf(file, "%.*s<Name>state</Name>\n",    indent+3, t);
    fprintf(file, "%.*s</SpecialInputArgument>\n", indent+2, t);
    fprintf(file, "%.*s</SpecialInputArguments>\n", indent+1, t);

    print_arguments_input_required(file, indent+1, funcInfo, 0);
    print_arguments_output(file, indent+1, funcInfo, 0);

    fprintf(file, "%.*s</Function>\n", indent, t);
}

void print_batch_state_function(FILE *file, int indent, const struct TA_FuncInfo *funcInfo)
{
    fprintf(file, "%.*s<Function>\n", indent, t);
    fprintf(file, "%.*s<Name>TA_%s_BatchState</Name>\n", indent+1, t, (funcInfo->name == NULL)? "" : funcInfo->name);
    fprintf(file, "%.*s<Type>BatchState</Type>\n", indent+1, t);
    fprintf(file, "%.*s<ReturnValue>TA_Result</ReturnValue>\n", indent+1, t);

    fprintf(file, "%.*s<SpecialInputArguments>\n",  indent+1, t);
    fprintf(file, "%.*s<SpecialInputArgument>\n",  indent+2, t);
    fprintf(file, "%.*s<Type>Pointer</Type>\n",     indent+3, t);
    fprintf(file, "%.*s<Name>state</Name>\n",    indent+3, t);
    fprintf(file, "%.*s</SpecialInputArgument>\n", indent+2, t);
    fprintf(file, "%.*s</SpecialInputArguments>\n", indent+1, t);

    print_arguments_input_required(file, indent+1, funcInfo, 1);
    print_arguments_output(file, indent+1, funcInfo, 1);

    fprintf(file, "%.*s</Function>\n", indent, t);
}

void print_xml(FILE *file, const struct TA_FuncInfo *funcInfo)
{
    /* General stuff about function */
    fprintf(file, "%.*s<!-- %s -->\n", 1, t, funcInfo->name);
    fprintf(file, "%.*s<FinancialFunctionGroup>\n", 1, t);
    fprintf(file, "%.*s<Abbreviation>%s</Abbreviation>\n", 2, t, (funcInfo->name == NULL)? "" : funcInfo->name);
    fprintf(file, "%.*s<CamelCaseName>%s</CamelCaseName>\n", 2, t, (funcInfo->camelCaseName == NULL)? "" : funcInfo->camelCaseName);
    ReplaceReservedXmlCharacters(funcInfo->hint, tempString);
    fprintf(file, "%.*s<ShortDescription>%s</ShortDescription>\n", 2, t, (funcInfo->hint == NULL)? "" : tempString);
    fprintf(file, "%.*s<GroupId>%s</GroupId>\n", 2, t, funcInfo->group);

    /* Optional function flags */
    if(funcInfo->flags & (TA_FUNC_FLG_OVERLAP | TA_FUNC_FLG_VOLUME | TA_FUNC_FLG_CANDLESTICK | TA_FUNC_FLG_UNST_PER))
    {
        fprintf(file, "%.*s<Flags>\n", 2, t);
        if(funcInfo->flags & TA_FUNC_FLG_OVERLAP)
        {
            fprintf(file, "%.*s<Flag>Overlap</Flag>\n", 3, t);
        }
        if(funcInfo->flags & TA_FUNC_FLG_VOLUME)
        {
            fprintf(file, "%.*s<Flag>Volume</Flag>\n", 3, t);
        }
        if(funcInfo->flags & TA_FUNC_FLG_CANDLESTICK)
        {
            fprintf(file, "%.*s<Flag>Candlestick</Flag>\n", 3, t);
        }
        if(funcInfo->flags & TA_FUNC_FLG_UNST_PER)
        {
            fprintf(file, "%.*s<Flag>Unstable Period</Flag>\n", 3, t);
        }

        fprintf(file, "%.*s</Flags>\n", 2, t);
    }

    print_state_memory(file, 2, funcInfo);
    print_state_struct(file, 2, funcInfo);

    fprintf(file, "%.*s<Functions>\n", 2, t);

    print_lookback_function(file, 3, funcInfo);
    print_regular_function(file, 3, funcInfo);
    print_state_init_or_free_function(file, 3, funcInfo, 0);
    print_state_function(file, 3, funcInfo);
    print_batch_state_function(file, 3, funcInfo);
    print_state_init_or_free_function(file, 3, funcInfo, 1);
    print_state_save_or_load_function(file, 3, funcInfo, 0);
    print_state_save_or_load_function(file, 3, funcInfo, 1);
    fprintf(file, "%.*s</Functions>\n", 2, t);

    fprintf(file, "%.*s</FinancialFunctionGroup>\n", 1, t);
    fprintf(file, "\n");
    fprintf(file, "\n");
}
