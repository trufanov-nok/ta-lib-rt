
#include <stdio.h>
#include "ta_func.h"

int main(int argc, char *argv[])
{

    TA_RetCode res = TA_Initialize();
    if(res != TA_SUCCESS)
    {
        fprintf( stderr, "Error TA_Initialize: %d", res);
        return -1;
    }


    const double data[50] = {105.68, 93.74, 92.72, 90.52, 95.22, 100.35, 97.92, 98.83, 95.33,
                             93.4, 95.89, 96.68, 98.78, 98.66, 104.21, 107.48, 108.18, 109.36,
                             106.94, 107.73, 103.13, 114.92, 112.71, 113.05, 114.06, 117.63,
                             116.6, 113.72, 108.84, 108.43, 110.06, 111.79, 109.9, 113.95,
                             115.97, 116.52, 115.82, 117.91, 119.04, 120, 121.95, 129.08,
                             132.12, 135.72, 136.66, 139.78, 139.14, 139.99, 140.64, 143.66};
    const int data_size = sizeof(data) / sizeof(double);

    struct TA_MACD_State *state = NULL;

    // allocate new function state object
    res = TA_MACD_StateInit(&state, 12, 26, 9);

    if(res != TA_SUCCESS)
    {
        fprintf( stderr, "Error TA_MACD_StateInit: %d", res);
        return -1;
    }

    double outMACD;
    double outMACDSignal;
    double outMACDHist;

    for (int i = 0; i < data_size; i++)
    {
        // get TA_MACD results
        res = TA_MACD_State(
                    state,                                   // function state object
                    data[i],                                 // data value
                    &outMACD, &outMACDSignal, &outMACDHist); // results

        // in this case for i in [0;32] function will return TA_NEED_MORE_DATA
        // as values passed to it are used for MACD initialization

        if (res == TA_SUCCESS) {
            printf("Result for day #%d outMACD: %f outMACDSignal: %f outMACDHist: %f\n",
                   i, outMACD, outMACDSignal, outMACDHist);
        }
        else if (res != TA_NEED_MORE_DATA) {
            fprintf( stderr, "Error TA_MACD_State: %d", res);
            break;
        }
    }

    res = TA_MACD_StateFree(&state);
    if(res != TA_SUCCESS)
    {
        fprintf( stderr, "Error TA_MACD_StateFree: %d", res);
    }

    res = TA_Shutdown();
    if(res != TA_SUCCESS)
    {
        fprintf( stderr, "Error TA_Shutdown: %d", res);
        return -1;
    }
}
