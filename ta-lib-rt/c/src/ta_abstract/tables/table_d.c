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
 * This file contains only TA functions starting with the letter 'D' *
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

/* DEMA BEGIN */
static const TA_InputParameterInfo    *TA_DEMA_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo   *TA_DEMA_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_DEMA_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_30_MINIMUM2,
  NULL
};


const TA_InputParameterInfo TA_DEMA_DEF_UI_STRUCT_PARAM_1 =
                                  { TA_Input_Pointer, "state_EMA", 0 };
const TA_InputParameterInfo TA_DEMA_DEF_UI_STRUCT_PARAM_2 =
                                  { TA_Input_Pointer, "state_EMA2", 0 };

static const TA_InputParameterInfo *TA_DEMA_StructParams[] = {
    &TA_DEMA_DEF_UI_STRUCT_PARAM_1,
    &TA_DEMA_DEF_UI_STRUCT_PARAM_2,
    NULL };

DEF_FUNCTION( DEMA,                         /* name */
              TA_GroupId_OverlapStudies,  /* groupId */
              "Double Exponential Moving Average", /* hint */
              "Dema",                     /* CamelCase name */
              TA_FUNC_FLG_OVERLAP         /* flags */
             );
/* DEMA END */

/* DIV BEGIN */
DEF_MATH_BINARY_OPERATOR( DIV, "Vector Arithmetic Div", "Div" )
/* DIV END */

/* DX BEGIN */
static const TA_InputParameterInfo    *TA_DX_Inputs[]    =
{
  &TA_DEF_UI_Input_Price_HLC,
  NULL
};

static const TA_OutputParameterInfo   *TA_DX_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_DX_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_14_MINIMUM2,
  NULL
};


const TA_InputParameterInfo TA_DX_DEF_UI_STRUCT_PARAM_1 =
                                  { TA_Input_Real, "prevHigh", 0 };
const TA_InputParameterInfo TA_DX_DEF_UI_STRUCT_PARAM_2 =
                                  { TA_Input_Real, "prevLow", 0 };
const TA_InputParameterInfo TA_DX_DEF_UI_STRUCT_PARAM_3 =
                                  { TA_Input_Real, "prevClose", 0 };
const TA_InputParameterInfo TA_DX_DEF_UI_STRUCT_PARAM_4 =
                                  { TA_Input_Real, "prevMinusDM", 0 };
const TA_InputParameterInfo TA_DX_DEF_UI_STRUCT_PARAM_5 =
                                  { TA_Input_Real, "prevPlusDM", 0 };
const TA_InputParameterInfo TA_DX_DEF_UI_STRUCT_PARAM_6 =
                                  { TA_Input_Real, "prevTR", 0 };
const TA_InputParameterInfo TA_DX_DEF_UI_STRUCT_PARAM_7 =
                                  { TA_Input_Real, "prevOutReal", 0 };
static const TA_InputParameterInfo *TA_DX_StructParams[] = {
    &TA_DX_DEF_UI_STRUCT_PARAM_1,
    &TA_DX_DEF_UI_STRUCT_PARAM_2,
    &TA_DX_DEF_UI_STRUCT_PARAM_3,
    &TA_DX_DEF_UI_STRUCT_PARAM_4,
    &TA_DX_DEF_UI_STRUCT_PARAM_5,
    &TA_DX_DEF_UI_STRUCT_PARAM_6,
    &TA_DX_DEF_UI_STRUCT_PARAM_7,
    NULL };

DEF_FUNCTION( DX,                         /* name */
              TA_GroupId_MomentumIndicators,   /* groupId */
              "Directional Movement Index", /* hint */
              "Dx",                         /* CamelCase name */
              TA_FUNC_FLG_UNST_PER          /* flags */
             );
/* DX END */

/****************************************************************************
 * Step 2 - Add your TA function to the table.
 *          Keep in alphabetical order. Must be NULL terminated.
 ****************************************************************************/
const TA_FuncDef *TA_DEF_TableD[] =
{
   ADD_TO_TABLE(DEMA),
   ADD_TO_TABLE(DIV),
   ADD_TO_TABLE(DX),
   NULL
};


/* Do not modify the following line. */
const unsigned int TA_DEF_TableDSize =
              ((sizeof(TA_DEF_TableD)/sizeof(TA_FuncDef *))-1);


/****************************************************************************
 * Step 3 - Make sure "gen_code" is executed for generating all other
 *          source files derived from this one.
 *          You can then re-compile the library as usual and you are done!
 ****************************************************************************/
