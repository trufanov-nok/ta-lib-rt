/* TA-LIB Copyright (c) 1999-2008, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*********************************************************************
 * This file contains only TA functions starting with the letter 'T' *
 *********************************************************************/
#include <stddef.h>
#include "ta_abstract.h"
#include "ta_def_ui.h"

/* Follow the 3 steps defined below for adding a new TA Function to this
 * file.
 */

/****************************************************************************
 * Step 1 - Define here the interface to your TA functions with
 *          the macro DEF_FUNCTION.
 *
 ****************************************************************************/

/* T3 BEGIN */
static const TA_OptInputParameterInfo TA_DEF_UI_VFactor =
{
   TA_OptInput_RealRange, /* type */
   "optInVFactor", /* paramName */
   0,                  /* flags */

   "Volume Factor",          /* displayName */
   (const void *)&TA_DEF_ZeroToOne, /* dataSet */
   0.7, /* defaultValue */
   "Volume Factor", /* hint */
   NULL /* CamelCase name */
};

static const TA_InputParameterInfo    *TA_T3_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo   *TA_T3_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_T3_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_5_MINIMUM2,
  &TA_DEF_UI_VFactor,
  NULL
};

const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_1 =
                                  { TA_Input_Real, "k", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_2 =
                                  { TA_Input_Real, "one_minus_k", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_3 =
                                  { TA_Input_Real, "e1", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_4 =
                                  { TA_Input_Real, "e2", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_5 =
                                  { TA_Input_Real, "e3", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_6 =
                                  { TA_Input_Real, "e4", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_7 =
                                  { TA_Input_Real, "e5", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_8 =
                                  { TA_Input_Real, "e6", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_9 =
                                  { TA_Input_Real, "c1", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_10 =
                                  { TA_Input_Real, "c2", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_11 =
                                  { TA_Input_Real, "c3", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_12 =
                                  { TA_Input_Real, "c4", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_13 =
                                  { TA_Input_Real, "tempReal", 0 };
const TA_InputParameterInfo TA_T3_DEF_UI_STRUCT_PARAM_14 =
                                  { TA_Input_Integer, "firstOutput", 0 };

static const TA_InputParameterInfo *TA_T3_StructParams[] = {
    &TA_T3_DEF_UI_STRUCT_PARAM_1,
    &TA_T3_DEF_UI_STRUCT_PARAM_2,
    &TA_T3_DEF_UI_STRUCT_PARAM_3,
    &TA_T3_DEF_UI_STRUCT_PARAM_4,
    &TA_T3_DEF_UI_STRUCT_PARAM_5,
    &TA_T3_DEF_UI_STRUCT_PARAM_6,
    &TA_T3_DEF_UI_STRUCT_PARAM_7,
    &TA_T3_DEF_UI_STRUCT_PARAM_8,
    &TA_T3_DEF_UI_STRUCT_PARAM_9,
    &TA_T3_DEF_UI_STRUCT_PARAM_10,
    &TA_T3_DEF_UI_STRUCT_PARAM_11,
    &TA_T3_DEF_UI_STRUCT_PARAM_12,
    &TA_T3_DEF_UI_STRUCT_PARAM_13,
    &TA_T3_DEF_UI_STRUCT_PARAM_14,
    NULL };

DEF_FUNCTION( T3,                         /* name */
              TA_GroupId_OverlapStudies,  /* groupId */
              "Triple Exponential Moving Average (T3)", /* hint */
              "T3",                       /* CamelCase name */
              TA_FUNC_FLG_OVERLAP|TA_FUNC_FLG_UNST_PER /* flags */
             );
/* T3 END */

/* TAN BEGIN */
DEF_MATH_UNARY_OPERATOR( TAN, "Vector Trigonometric Tan", "Tan" )
/* TAN END */

/* TANH BEGIN */
DEF_MATH_UNARY_OPERATOR( TANH, "Vector Trigonometric Tanh", "Tanh" )
/* TANH END */

/* TEMA BEGIN */
static const TA_InputParameterInfo    *TA_TEMA_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo   *TA_TEMA_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_TEMA_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_30_MINIMUM2,
  NULL
};

const TA_InputParameterInfo TA_TEMA_DEF_UI_STRUCT_PARAM_1 =
                                  { TA_Input_Pointer, "state_EMA", 0 };
const TA_InputParameterInfo TA_TEMA_DEF_UI_STRUCT_PARAM_2 =
                                  { TA_Input_Pointer, "state_EMA2", 0 };
const TA_InputParameterInfo TA_TEMA_DEF_UI_STRUCT_PARAM_3 =
                                  { TA_Input_Pointer, "state_EMA3", 0 };

static const TA_InputParameterInfo *TA_TEMA_StructParams[] = {
    &TA_TEMA_DEF_UI_STRUCT_PARAM_1,
    &TA_TEMA_DEF_UI_STRUCT_PARAM_2,
    &TA_TEMA_DEF_UI_STRUCT_PARAM_3,
    NULL };

DEF_FUNCTION( TEMA,                         /* name */
              TA_GroupId_OverlapStudies,  /* groupId */
              "Triple Exponential Moving Average", /* hint */
              "Tema",                     /* CamelCase name */
              TA_FUNC_FLG_OVERLAP         /* flags */
             );
/* TEMA END */

/* TRANGE BEGIN */
static const TA_InputParameterInfo    *TA_TRANGE_Inputs[]    =
{
  &TA_DEF_UI_Input_Price_HLC,
  NULL
};

static const TA_OutputParameterInfo   *TA_TRANGE_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_TRANGE_OptInputs[] = { NULL };

static const TA_InputParameterInfo *TA_TRANGE_StructParams[] = { NULL }; 

DEF_FUNCTION( TRANGE,                         /* name */
              TA_GroupId_VolatilityIndicators,  /* groupId */
              "True Range",               /* hint */
              "TrueRange",                /* CamelCase name */
              0                           /* flags */
             );
/* TRANGE END */

/* TRIMA BEGIN */
static const TA_InputParameterInfo    *TA_TRIMA_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo   *TA_TRIMA_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_TRIMA_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_30_MINIMUM2,
  NULL
};



const TA_InputParameterInfo TA_TRIMA_DEF_UI_STRUCT_PARAM_1 =
                                  { TA_Input_Real, "numerator", 0 };
const TA_InputParameterInfo TA_TRIMA_DEF_UI_STRUCT_PARAM_2 =
                                  { TA_Input_Real, "numeratorSub", 0 };
const TA_InputParameterInfo TA_TRIMA_DEF_UI_STRUCT_PARAM_3 =
                                  { TA_Input_Real, "numeratorAdd", 0 };
const TA_InputParameterInfo TA_TRIMA_DEF_UI_STRUCT_PARAM_4 =
                                  { TA_Input_Real, "factor", 0 };
const TA_InputParameterInfo TA_TRIMA_DEF_UI_STRUCT_PARAM_5 =
                                  { TA_Input_Integer, "middleIdx", 0 };

static const TA_InputParameterInfo *TA_TRIMA_StructParams[] = {
    &TA_TRIMA_DEF_UI_STRUCT_PARAM_1,
    &TA_TRIMA_DEF_UI_STRUCT_PARAM_2,
    &TA_TRIMA_DEF_UI_STRUCT_PARAM_3,
    &TA_TRIMA_DEF_UI_STRUCT_PARAM_4,
    &TA_TRIMA_DEF_UI_STRUCT_PARAM_5,
    NULL };

DEF_FUNCTION( TRIMA,                         /* name */
              TA_GroupId_OverlapStudies,   /* groupId */
              "Triangular Moving Average", /* hint */
              "Trima",                     /* CamelCase name */
              TA_FUNC_FLG_OVERLAP          /* flags */
             );
/* TRIMA END */

/* TRIX BEGIN */
static const TA_InputParameterInfo    *TA_TRIX_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo   *TA_TRIX_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_TRIX_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_30,
  NULL
};

const TA_InputParameterInfo TA_TRIX_DEF_UI_STRUCT_PARAM_1 =
                                  { TA_Input_Pointer, "stateEMA1", 0 };
const TA_InputParameterInfo TA_TRIX_DEF_UI_STRUCT_PARAM_2 =
                                  { TA_Input_Pointer, "stateEMA2", 0 };
const TA_InputParameterInfo TA_TRIX_DEF_UI_STRUCT_PARAM_3 =
                                  { TA_Input_Pointer, "stateEMA3", 0 };
const TA_InputParameterInfo TA_TRIX_DEF_UI_STRUCT_PARAM_4 =
                                  { TA_Input_Pointer, "stateROC", 0 };

static const TA_InputParameterInfo *TA_TRIX_StructParams[] = {
    &TA_TRIX_DEF_UI_STRUCT_PARAM_1,
    &TA_TRIX_DEF_UI_STRUCT_PARAM_2,
    &TA_TRIX_DEF_UI_STRUCT_PARAM_3,
    &TA_TRIX_DEF_UI_STRUCT_PARAM_4,
    NULL };

DEF_FUNCTION( TRIX,                         /* name */
              TA_GroupId_MomentumIndicators,  /* groupId */
              "1-day Rate-Of-Change (ROC) of a Triple Smooth EMA", /* hint */
              "Trix",                     /* CamelCase name */
              0                           /* flags */
             );
/* TRIX END */

/* TSF BEGIN */
static const TA_InputParameterInfo *TA_TSF_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo *TA_TSF_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_TSF_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_14_MINIMUM2,
  NULL
};

const TA_InputParameterInfo TA_TSF_DEF_UI_STRUCT_PARAM_1 =
                                  { TA_Input_Real, "SumX", 0 };
const TA_InputParameterInfo TA_TSF_DEF_UI_STRUCT_PARAM_2 =
                                  { TA_Input_Real, "SumXY", 0 };
const TA_InputParameterInfo TA_TSF_DEF_UI_STRUCT_PARAM_3 =
                                  { TA_Input_Real, "SumY", 0 };
const TA_InputParameterInfo TA_TSF_DEF_UI_STRUCT_PARAM_4 =
                                  { TA_Input_Real, "SumXSqr", 0 };
const TA_InputParameterInfo TA_TSF_DEF_UI_STRUCT_PARAM_5 =
                                  { TA_Input_Real, "Divisor", 0 };

static const TA_InputParameterInfo *TA_TSF_StructParams[] = {
    &TA_TSF_DEF_UI_STRUCT_PARAM_1,
    &TA_TSF_DEF_UI_STRUCT_PARAM_2,
    &TA_TSF_DEF_UI_STRUCT_PARAM_3,
    &TA_TSF_DEF_UI_STRUCT_PARAM_4,
    &TA_TSF_DEF_UI_STRUCT_PARAM_5,
    NULL };

DEF_FUNCTION( TSF,                         /* name */
              TA_GroupId_Statistic,  /* groupId */
              "Time Series Forecast",/* hint */
              "Tsf",                 /* CamelCase name */
              TA_FUNC_FLG_OVERLAP    /* flags */
             );
/* TSF END */

/* TYPPRICE BEGIN */
static const TA_InputParameterInfo    *TA_TYPPRICE_Inputs[]    =
{
  &TA_DEF_UI_Input_Price_HLC,
  NULL
};

static const TA_OutputParameterInfo   *TA_TYPPRICE_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_TYPPRICE_OptInputs[] = { NULL };

static const TA_InputParameterInfo *TA_TYPPRICE_StructParams[] = { NULL }; 

DEF_FUNCTION( TYPPRICE,                         /* name */
              TA_GroupId_PriceTransform,  /* groupId */
              "Typical Price",            /* hint */
              "TypPrice",                 /* CamelCase name */
              TA_FUNC_FLG_OVERLAP         /* flags */
             );
/* TYPPRICE END */

/****************************************************************************
 * Step 2 - Add your TA function to the table.
 *          Keep in alphabetical order. Must be NULL terminated.
 ****************************************************************************/
const TA_FuncDef *TA_DEF_TableT[] =
{
   ADD_TO_TABLE(T3),
   ADD_TO_TABLE(TAN),
   ADD_TO_TABLE(TANH),
   ADD_TO_TABLE(TEMA),
   ADD_TO_TABLE(TRANGE),
   ADD_TO_TABLE(TRIMA),
   ADD_TO_TABLE(TRIX),
   ADD_TO_TABLE(TSF),
   ADD_TO_TABLE(TYPPRICE),
   NULL
};


/* Do not modify the following line. */
const unsigned int TA_DEF_TableTSize =
              ((sizeof(TA_DEF_TableT)/sizeof(TA_FuncDef *))-1);


/****************************************************************************
 * Step 3 - Make sure "gen_code" is executed for generating all other
 *          source files derived from this one.
 *          You can then re-compile the library as usual and you are done!
 ****************************************************************************/
