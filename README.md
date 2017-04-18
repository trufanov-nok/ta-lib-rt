# TA-Lib RT
**TA-Lib RT** (**R**eal **T**ime) is a fork of [TA-Lib](http://ta-lib.org) that provides additional API for incremental calculation of indicators without reprocessing whole data. Binary compatibility with original code is possible but isn't provided in this release.

In a nutshell each indicator function ( for example: `int TA_[MYINDICATOR](indexArguments, dataArguments, optArguments, outArguments);` ) got 5 more additional functions. 3 main functions:

* `int TA_[MYINDICATOR]_StateInit(void** _state, optArguments);` - allocates indicator-dependant object that contains a state of its last calculation.
* `int TA_[MYINDICATOR]_State(void* _state, dataArguments, outArguments);` - calculates indicator based on state given. Note: `dataArguments` here aren't arrays but signle values. This function should be called in a loop for all data values.
* `int TA_[MYINDICATOR]_StateFree( void** _state );` - destroys state object and frees its previously allocated memory.  

And 2 helper functions:

* `int TA_[MYINDICATOR]_StateSave( void* _state, FILE* _file );` - serialize state object to file.
* `int TA_[MYINDICATOR]_StateLoad( void** _state, FILE* _file );` - read state object from file.

There is also support of dynamic indicator functions resolution via `TA_FuncInfo` with help of `TA_GetInitNewStateFuncPtr()`, `TA_GetCallFuncStateFuncPtr()`, `TA_GetFreeStateFuncPtr()`, `TA_GetSaveStateFuncPtr()` and `TA_GetLoadStateFuncPtr()`.

Please refer to wiki and examples for details.

**Current version is alpha and only C++ API is testted**
