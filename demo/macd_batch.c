
#include <stdio.h>
#include <stdlib.h>
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
    // TA_MACD_Lookback retuns number of elements used to initialize moving average (33 in this case)
    // 12, 26, 9 - are default MACD specific periods
    int res_size = data_size - TA_MACD_Lookback(12, 26, 9);
    // res_size is 17 - MACD can't be calculated for first 33 values as they're used for its initialization

    // dynamically allocate output arrays
    double* outMACD = malloc(res_size * sizeof(double));
    double* outMACDSignal = malloc(res_size *sizeof(double));
    double* outMACDHist = malloc(res_size * sizeof(double));

    int outBegIdx= 0;
    int outNbElement = 0;

    // get TA_MACD results
    res = TA_MACD(0, data_size-1,                       // data range
                  data,                                 // data pointer
                  12, 26, 9,                            // TA Func specific args
                  &outBegIdx, &outNbElement,            // relative index and size of results
                  outMACD, outMACDSignal, outMACDHist); // arrays of results

    if (res == TA_SUCCESS) {
        for (int i = 0; i < outNbElement; i++){
            printf("Result for day #%d outMACD: %f outMACDSignal: %f outMACDHist: %f\n",
                   outBegIdx+i, *(outMACD+i), *(outMACDSignal+i), *(outMACDHist+i));
        }
    } else
        fprintf( stderr, "Error TA_MACD: %d", res);

    free(outMACD);
    free(outMACDSignal);
    free(outMACDHist);

    res = TA_Shutdown();
    if(res != TA_SUCCESS)
    {
        fprintf( stderr, "Error TA_Shutdown: %d", res);
        return -1;
    }
}
