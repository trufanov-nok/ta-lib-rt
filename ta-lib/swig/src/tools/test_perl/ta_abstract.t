#!perl
#
# Test of ta_abstract
# 

use strict;
use lib "../../../lib/perl";
use Test;
BEGIN { plan tests => 74 }

use Finance::TA;

print "TA-Lib ", TA_GetVersionString(), "\n";
print "Testing ta_abstract...\n";

my @groups = TA_GroupTable();
@groups = sort @groups;
#print "Groups: @groups\n";
ok( shift(@groups), $TA_SUCCESS );
ok( $groups[0], "Cycle Indicators" );
ok( $groups[1], "Math Operators" );
ok( $groups[2], "Math Transform" );
ok( $groups[3], "Momentum Indicators" );

my @functions = TA_FuncTable($groups[0]);
@functions = sort @functions;
#print "Functions: @functions\n";
ok( shift(@functions), $TA_SUCCESS );
ok( $functions[0], "HT_DCPERIOD" );
ok( $functions[1], "HT_DCPHASE" );
ok( $functions[2], "HT_PHASOR" );
ok( $functions[3], "HT_SINE" );

print "Testing func info...\n";
my ($fh, $fi);
ok( TA_GetFuncHandle("BBANDS", \$fh), $TA_SUCCESS );
ok( TA_GetFuncInfo($fh, \$fi), $TA_SUCCESS );
ok( $fi->{name}, "BBANDS" );
ok( $fi->{group}, "Overlap Studies" );
ok( $fi->{hint}, "Bollinger Bands" );
ok( $fi->{helpFile}, undef );
ok( $fi->{flags}, $TA_FUNC_FLG_OVERLAP );
ok( $fi->{nbInput}, 1 );
ok( $fi->{nbOptInput}, 4 );
ok( $fi->{nbOutput}, 3 );

ok( TA_GetFuncInfo($fi->{handle}, \$fi), $TA_SUCCESS );
ok( $fi->{name}, "BBANDS" );

my $info;
ok( TA_SetInputParameterInfoPtr( $fh, 0, \$info), $TA_SUCCESS );
ok( $info->{type}, $TA_Input_Real );
ok( $info->{paramName}, "inReal" );
ok( $info->{flags}, 0);

ok( TA_SetOutputParameterInfoPtr( $fh, 1, \$info), $TA_SUCCESS );
ok( $info->{type}, $TA_Output_Real );
ok( $info->{paramName}, "outRealMiddleBand" );
ok( $info->{flags}, $TA_OUT_LINE );

ok( TA_SetOptInputParameterInfoPtr( $fh, 2, \$info), $TA_SUCCESS );
ok( $info->{type}, $TA_OptInput_RealRange );
ok( $info->{paramName}, "optInNbDevDn" );
ok( $info->{flags}, 0 );
ok( $info->{displayName}, "Deviations down" );
ok( $info->{dataSet}{min}, $TA_REAL_MIN );
ok( $info->{dataSet}{max}, $TA_REAL_MAX );
ok( $info->{dataSet}{precision}, 2 );
ok( $info->{dataSet}{suggested_start}, -2.0 );
ok( $info->{dataSet}{suggested_end}, 2.0 );
ok( $info->{dataSet}{suggested_increment}, 0.2 );
ok( $info->{defaultValue}, 2 );
ok( $info->{hint}, qr/Deviation/ );
ok( $info->{helpFile}, undef );

# The same test as above, but using the object interface
print "Testing func info (object-oriented)...\n";

$fh = new TA_FuncHandle("STOCH");
ok( defined $fh );
$fi = $fh->TA_GetFuncInfo();
ok( defined $fi );
# or:
$fi = new TA_FuncInfo($fh);
ok( defined $fi );
ok( $fi->{name}, "STOCH" );
ok( $fi->{group}, "Momentum Indicators" );
ok( $fi->{hint}, "Stochastic" );
ok( $fi->{helpFile}, undef );
ok( $fi->{flags}, 0 );
ok( $fi->{nbInput}, 1 );
ok( $fi->{nbOptInput}, 5 );
ok( $fi->{nbOutput}, 2 );

$info = $fh->TA_SetInputParameterInfoPtr(0);
ok( defined $info );
ok( $info->{type}, $TA_Input_Price );
ok( $info->{paramName}, "inPriceHLC" );
ok( $info->{flags}, $TA_IN_PRICE_HIGH | $TA_IN_PRICE_LOW | $TA_IN_PRICE_CLOSE );

$info = $fh->TA_SetOutputParameterInfoPtr(1);
ok( defined $info );
ok( $info->{type}, $TA_Output_Real );
ok( $info->{paramName}, "outSlowD" );
ok( $info->{flags}, $TA_OUT_DASH_LINE );

$info = $fh->TA_SetOptInputParameterInfoPtr(2);
ok( defined $info );
ok( $info->{type}, $TA_OptInput_IntegerList );
ok( $info->{paramName}, "optInSlowK_MAType" );
ok( $info->{flags}, 0 );
ok( $info->{displayName}, "Slow-K MA" );
ok( $info->{dataSet}{nbElement}, 9 );
ok( $info->{dataSet}{data}[6]{string}, "KAMA" );
ok( $info->{dataSet}{data}[6]{value}, $TA_MAType_KAMA );
ok( $info->{defaultValue}, $TA_MAType_SMA );
ok( $info->{hint}, qr/Moving Average/ );
ok( $info->{helpFile}, undef );

# No need to deallocate $fh or $fi
