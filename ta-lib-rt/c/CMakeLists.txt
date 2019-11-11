
#SET(TA_LIB_RT_FLAGS "")
#SET(TA_LIB_RT_INCLUDE_DIRS "")
#SET(TA_LIB_RT_LIBRARY_DIRS "")
#SET(TA_LIB_RT_LIBRARIES "")

SET(LIBRARY_OUTPUT_PATH ${ta-lib-rt_BINARY_DIR}/lib/ CACHE PATH "Single out dir for all libs" FORCE)
SET(TA_LIB_RT_LIBRARY_DIRS lib)
LINK_DIRECTORIES(${ta-lib-rt_BINARY_DIR}/lib)

#SET(priv_HEADERS
#	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/ta_frame_priv.h
#	${ta-lib-rt_SOURCE_DIR}/c/src/ta_common/ta_global.h
#	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_utility.h
#	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/ta_def_ui.h
#	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/frames/ta_frame.h
#	${ta-lib-rt_SOURCE_DIR}/c/src/ta_common/ta_magic_nb.h
#	${ta-lib-rt_SOURCE_DIR}/c/src/ta_common/ta_memory.h
#)

SET(ta-lib-rt_HEADERS
	${ta-lib-rt_SOURCE_DIR}/c/include/ta_abstract.h
	${ta-lib-rt_SOURCE_DIR}/c/include/ta_common.h
	${ta-lib-rt_SOURCE_DIR}/c/include/ta_defs.h
	${ta-lib-rt_SOURCE_DIR}/c/include/ta_func.h
	${ta-lib-rt_SOURCE_DIR}/c/include/ta_libc.h
)

INCLUDE_DIRECTORIES(${ta-lib-rt_SOURCE_DIR}/c/include
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract 
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/frames
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_common
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func
)

SET(ta-lib-rt_CSOURCES
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_LINEARREG.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MAX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHAMMER.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLDRAGONFLYDOJI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLGRAVESTONEDOJI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLABANDONEDBABY.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MAVP.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLCONCEALBABYSWALL.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_HT_TRENDMODE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_IMI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLADVANCEBLOCK.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_AROONOSC.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLLONGLINE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MIDPOINT.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_PPO.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_WMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_HT_DCPHASE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLSPINNINGTOP.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ACCBANDS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLIDENTICAL3CROWS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_LINEARREG_ANGLE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ADOSC.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDL3OUTSIDE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CORREL.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ULTOSC.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_AD.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLUPSIDEGAP2CROWS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLUNIQUE3RIVER.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLRISEFALL3METHODS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLLADDERBOTTOM.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_PLUS_DM.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ADD.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_STOCHRSI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHANGINGMAN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_NVI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_T3.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_HT_PHASOR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLTASUKIGAP.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_DEMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_RSI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MIN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLSTICKSANDWICH.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MINMAX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLENGULFING.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLDOJI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ACOS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLINNECK.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_STOCH.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLPIERCING.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ASIN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MACD.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_KAMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ATR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ADXR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLCLOSINGMARUBOZU.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLDARKCLOUDCOVER.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TRIX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_HT_TRENDLINE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ROCP.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLMORNINGSTAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MIDPRICE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_LOG10.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLGAPSIDESIDEWHITE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SIN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TSF.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_STOCHF.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CMO.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDL3STARSINSOUTH.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_AROON.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TAN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SINH.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_utility.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TYPPRICE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_NATR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDL3BLACKCROWS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_HT_DCPERIOD.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLBREAKAWAY.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_PLUS_DI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_STDDEV.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDL2CROWS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MOM.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TRIMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TRANGE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHIKKAKE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLEVENINGDOJISTAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MAXINDEX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_FLOOR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ROCR100.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLSEPARATINGLINES.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHARAMICROSS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_WCLPRICE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_BBANDS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLLONGLEGGEDDOJI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CEIL.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_AVGDEV.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLCOUNTERATTACK.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_EXP.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLONNECK.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLINVERTEDHAMMER.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLXSIDEGAP3METHODS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLMARUBOZU.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CCI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MACDEXT.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLTHRUSTING.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLMATHOLD.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHIKKAKEMOD.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLKICKINGBYLENGTH.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_LINEARREG_INTERCEPT.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLKICKING.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SUB.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_LINEARREG_SLOPE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_HT_SINE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_COSH.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLDOJISTAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHOMINGPIGEON.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_EMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_COS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SAREXT.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_LN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TANH.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MACDFIX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_OBV.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SUM.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_DX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_TEMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MININDEX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MULT.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_APO.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_DIV.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_WILLR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLSHORTLINE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLRICKSHAWMAN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MEDPRICE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLMATCHINGLOW.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ROCR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLBELTHOLD.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLTAKURI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLTRISTAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHARAMI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_PVI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_PVT.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ATAN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLHIGHWAVE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLSTALLEDPATTERN.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_VAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLEVENINGSTAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MAMA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDL3LINESTRIKE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDL3WHITESOLDIERS.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLSHOOTINGSTAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_BOP.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MINUS_DM.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ROC.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDLMORNINGDOJISTAR.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_AVGPRICE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MFI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MINMAXINDEX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_MINUS_DI.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_SQRT.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_BETA.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_CDL3INSIDE.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_func/ta_ADX.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_common/ta_version.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_common/ta_retcode.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_common/ta_global.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/frames/ta_frame.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/ta_abstract.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/ta_func_api.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/ta_def_ui.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/ta_group_idx.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_t.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_p.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_a.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_l.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_r.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_s.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_c.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_g.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_f.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_e.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_o.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_x.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_q.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_b.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_n.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_v.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_y.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_d.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_i.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_h.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_z.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_j.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_k.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_w.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_u.c
	${ta-lib-rt_SOURCE_DIR}/c/src/ta_abstract/tables/table_m.c
)

IF(UNIX)
	ADD_LIBRARY(ta_lib_rt SHARED ${ta-lib-rt_CSOURCES})
	SET_TARGET_PROPERTIES(ta_lib_rt PROPERTIES SOVERSION ${TA_LIB_RT_VERSION_FULL} DEFINE_SYMBOL TA_LIB_RT_SHARED)
	ADD_LIBRARY(ta_lib_rt_static STATIC ${ta-lib-rt_CSOURCES})
	SET_TARGET_PROPERTIES(ta_lib_rt_static PROPERTIES OUTPUT_NAME ta_lib_rt)
ENDIF(UNIX)

IF(WIN32)
	INCLUDE(GenerateExportHeader)
	ADD_LIBRARY(ta_lib_rt SHARED ${ta-lib-rt_CSOURCES})
	SET_TARGET_PROPERTIES(ta_lib_rt PROPERTIES DEFINE_SYMBOL TA_LIB_RT_SHARED)
	ADD_LIBRARY(ta_lib_rt_static STATIC ${ta-lib-rt_CSOURCES})
	SET_TARGET_PROPERTIES(ta_lib_rt_static PROPERTIES OUTPUT_NAME ta_lib_rt_a)
ENDIF(WIN32)

SET_TARGET_PROPERTIES(ta_lib_rt PROPERTIES SOVERSION ${TA_LIB_RT_VERSION_FULL})

INSTALL(FILES ${ta-lib-rt_HEADERS} DESTINATION include/ta-lib-rt)
INSTALL(TARGETS ta_lib_rt ta_lib_rt_static DESTINATION lib)

