include(CTest)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/c/src/tools/ta_regtest/
	../../ta_abstract
	../../ta_common
	../../ta_func
)

SET(ta_regtest_CSOURCES
	ta_regtest.c
	test_data.c
	test_util.c
	test_abstract.c
	ta_test_func/test_adx.c
	ta_test_func/test_avgdev.c
	ta_test_func/test_mom.c
	ta_test_func/test_sar.c
	ta_test_func/test_rsi.c
	ta_test_func/test_candlestick.c
	ta_test_func/test_per_ema.c
	ta_test_func/test_per_hlc.c
	ta_test_func/test_stoch.c
	ta_test_func/test_macd.c
	ta_test_func/test_minmax.c
	ta_test_func/test_per_hlcv.c
	ta_test_func/test_1in_1out.c
	ta_test_func/test_1in_2out.c
	ta_test_func/test_per_ohlc.c
	ta_test_func/test_stddev.c
	ta_test_func/test_bbands.c
	ta_test_func/test_ma.c
	ta_test_func/test_po.c
	ta_test_func/test_per_hl.c
	ta_test_func/test_trange.c
	ta_test_func/test_imi.c
	test_internals.c
)

ADD_EXECUTABLE(ta_regtest  ${ta_regtest_CSOURCES})
add_dependencies(ta_regtest ta-lib-rt)
target_link_libraries(ta_regtest ta-lib-rt m)
link_directories(ta_regtest ${ta-lib-rt_BINARY_DIR}/lib)

ADD_TEST(NAME "regtest" COMMAND ta_regtest)
