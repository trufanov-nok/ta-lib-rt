#!/usr/bin/python
"""
Run all regression tests of Python wrapper to ta_defs
""" 

import unittest
import ta_defs
import ta_common
import ta_func


class AllTests(
        ta_defs.ta_defs_test, 
        ta_common.ta_common_test,
        ta_func.ta_func_test
        ):
    None

if __name__ == '__main__':
    unittest.main()
