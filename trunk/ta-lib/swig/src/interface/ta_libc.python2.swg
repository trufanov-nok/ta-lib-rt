/* 
 * Not standard extension.
 * Difference from original lib:
 * - In Python we can use exception handling instead TA_RetCode. 
 */

%typemap(out) TA_RetCode
{
	if( $1 != TA_SUCCESS )
	{
	 	TA_RetCodeInfo info;
		char text[200];
		TA_SetRetCodeInfo( $1, &info );
		snprintf(text, sizeof(text)-1, "Error %d (%s): %s\n", $1, info.enumStr, info.infoStr );
		PyErr_SetString(PyExc_Exception, text);
		goto fail;
	} 
	Py_INCREF(Py_None); $result = Py_None;
	//$result = SWIG_From_int($1);
}

%include "ta_libc.swg"