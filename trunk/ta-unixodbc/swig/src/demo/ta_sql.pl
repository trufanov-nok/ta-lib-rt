#!/usr/bin/perl
#
# Simple application for accessing an SQL database using TA-LIB using the SWIG wrapper
#

use Data::Dumper;
use Finance::TA;
use strict;


my %tableAction = (
    -c  => [ "DISPLAY_CATEGORIES",     $TA_DAILY     ],
    -s  => [ "DISPLAY_SYMBOLS",        $TA_DAILY     ],
    -d  => [ "DISPLAY_HISTORIC_DATA",  $TA_DAILY     ],
    -dd => [ "DISPLAY_HISTORIC_DATA",  $TA_DAILY     ],
    -dw => [ "DISPLAY_HISTORIC_DATA",  $TA_WEEKLY    ],
    -dm => [ "DISPLAY_HISTORIC_DATA",  $TA_MONTHLY   ],
    -dq => [ "DISPLAY_HISTORIC_DATA",  $TA_QUARTERLY ],
    -dy => [ "DISPLAY_HISTORIC_DATA",  $TA_YEARLY    ],
);


my %tableOption = (
    -z => [ $TA_REPLACE_ZERO_PRICE_BAR, 0 ],
    -t => [ 0, $TA_USE_TOTAL_VOLUME ],
    -i => [ 0, $TA_ALLOW_INCOMPLETE_PRICE_BARS ],
);


sub print_usage {
    my $ta_ver = TA_GetVersionString();

    print <<"EOS";
ta_sql V$ta_ver - SQL for market data

Usage: ta_sql -c    <opt> <loc> <catsql>
       ta_sql -s    <opt> <loc> <catsql> <cat> <symsql>
       ta_sql -d<p> <opt> <loc> <catsql> <cat> <symsql> <sym> <infosql>

    Specify one of the following action switch:
      -c     Display all supported categories
      -s     Display all symbols for a given category
      -d<p>  Display market data for the specified <p> period. Use
             \"d,w,m,q,y\" for \"daily,weekly,monthly,quarterly,yearly\"

    <opt> are optional switches:
      -z TA_REPLACE_ZERO_PRICE_BAR flag for TA_AddDataSource.
      -t TA_USE_TOTAL_VOLUME flag for TA_HistoryAlloc.
      -i TA_ALLOW_INCOMPLETE_PRICE_BARS flag for TA_AddDataSource.

      -u=<str>  Specify the username for TA_AddDataSource.
      -p=<str>  Specify the password for TA_AddDataSource.

    <loc>     is the TA_AddDataSource location parameter.
    <catsql>  is the TA_AddDataSource category parameter.
    <cat>     is a string of a given category.
    <symsql>  is the TA_AddDataSource symbol parameter.
    <sym>     is a string of a given symbol.
    <infosql> is the TA_AddDataSource info parameter.

  Market data output is \"Date,Open,High,Low,Close,Volume\"

  Check http://ta-lib.org/d_source/d_sql.html for usage examples.\"

  For help, try the mailing list at http://ta-lib.org

EOS
    print "Error: [@_]\n" if @_;

    return 1;
}


sub print_error {
    my ($retCode) = @_;

    my $retCodeInfo = new TA_RetCodeInfo($retCode);
    printf "\nError %d=%s:[%s]\n", $retCode, 
        $retCodeInfo->{enumStr}, 
        $retCodeInfo->{infoStr};
}



sub print_data {
    my ($udb, $haParam) = @_;

    my $history = $udb->History($haParam);
    ($history->{retCode} == $TA_SUCCESS) or print_error( $history->{retCode} ) and return -1;

    if ( $history->{nbBars} == 0 ) {
        print "No data available\n";
        return 0;
    }

    for ( my $i = 0; $i < $history->{nbBars}; $i++ ) {
        printf "%02u-%02u-%02u", $history->{timestamp}[$i]{year},
                                 $history->{timestamp}[$i]{month},
                                 $history->{timestamp}[$i]{day};

        printf ",%.2f", $history->{open}[$i]   if defined $history->{open};
        printf ",%.2f", $history->{high}[$i]   if defined $history->{high};
        printf ",%.2f", $history->{low}[$i]    if defined $history->{low};
        printf ",%.2f", $history->{close}[$i]  if defined $history->{close};
        printf ",%.2f", $history->{volume}[$i] if defined $history->{volume};
        printf "\n";
    }

    return 0;
}


sub print_categories {
    my ($udb) = @_;

    my @table = TA_CategoryTable( $udb );
    my $retCode = shift @table;
    ($retCode == $TA_SUCCESS) or print_error( $retCode ) and return -1;

    local ($,, $\) = ( "\n", "\n");
    print @table;
    
    return 0;
}



sub print_symbols {
    my ($udb, $category) = @_;

    my @table = TA_SymbolTable( $udb, $category );
    my $retCode = shift @table;
    ($retCode == $TA_SUCCESS) or print_error( $retCode ) and return -1;

    local ($,, $\) = ( "\n", "\n");
    print @table;
    
    return 0;
}



#############################################################

(@ARGV > 1) or print_usage() and exit -1;

my $dsParam = new TA_AddDataSourceParam or die "Cannot create AddDataSourceParam\n";
my $haParam = new TA_HistoryAllocParam  or die "Cannot create HistoryAllocParam\n";

# Check for the action switch and identify what needs to be done.
my $theAction = $tableAction{$ARGV[0]}[0];
$haParam->{period} = $tableAction{$ARGV[0]}[1];
defined($theAction) or print_usage( "Action switch not recognized" ) and exit -1;
shift;

# Handle optional switch.
while ($_ = shift) {
    unshift(@ARGV, $_), last if /^[^-]/;

    /^-u=(.*)/ and $dsParam->{username} = $1 and next;
    /^-p=(.*)/ and $dsParam->{password} = $1 and next;

    if (defined $tableOption{$_}) {
        $dsParam->{flags} |= $tableOption{$_}[0];
        $haParam->{flags} |= $tableOption{$_}[1];
        next;
    }

    print_usage( "Unrecognized optional switch" ) and exit -1;
}



# Check the number of required parameter after the switches.
if ( (($theAction eq 'DISPLAY_CATEGORIES')    && (@ARGV < 2)) ||
     (($theAction eq 'DISPLAY_SYMBOLS')       && (@ARGV < 4)) ||
     (($theAction eq 'DISPLAY_HISTORIC_DATA') && (@ARGV < 6)))
{
    print_usage( "Missing Parameters" );
    exit -1;
}

# Create an unified database.
my $udb = new TA_UDBase or die "Cannot initialize UDBase\n";

# Set the parameters for TA-Lib.
$haParam->{field} = $TA_ALL;
$dsParam->{id} = $TA_SQL;
$dsParam->{location} = shift;
$dsParam->{category} = shift;
$haParam->{category} = shift;
$dsParam->{symbol}   = shift;
$haParam->{symbol}   = shift;
$dsParam->{info}     = shift;
$dsParam->{info}     ||= ""; # info must be set even if not used


# Add the data source.
my $retCode = TA_AddDataSource( $udb, $dsParam );
$retCode == $TA_SUCCESS or print_error( $retCode ) and exit -1;

# Perform the requested action.
my $retValue = -1;
if ($theAction eq 'DISPLAY_CATEGORIES') {
    $retValue = print_categories( $udb );
}
elsif ($theAction eq 'DISPLAY_SYMBOLS') {
    $retValue = print_symbols( $udb, $haParam->{category} );
}
elsif ($theAction eq 'DISPLAY_HISTORIC_DATA') {
    $retValue = print_data( $udb, $haParam );
}

exit $retValue;
