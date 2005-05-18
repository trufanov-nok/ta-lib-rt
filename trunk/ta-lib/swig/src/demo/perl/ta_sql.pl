#!/usr/bin/perl
#
# Simple application for accessing an SQL database using TA-LIB 
# using the SWIG wrapper
#

use Finance::TA;
use strict;


my %tableAction = (
    -c   => [ "DISPLAY_CATEGORIES",     $TA_DAILY     ],
    -s   => [ "DISPLAY_SYMBOLS",        $TA_DAILY     ],
    -d   => [ "DISPLAY_HISTORIC_DATA",  $TA_DAILY     ],
    -dd  => [ "DISPLAY_HISTORIC_DATA",  $TA_DAILY     ],
    -dw  => [ "DISPLAY_HISTORIC_DATA",  $TA_WEEKLY    ],
    -dm  => [ "DISPLAY_HISTORIC_DATA",  $TA_MONTHLY   ],
    -dq  => [ "DISPLAY_HISTORIC_DATA",  $TA_QUARTERLY ],
    -dy  => [ "DISPLAY_HISTORIC_DATA",  $TA_YEARLY    ],
    -d1  => [ "DISPLAY_HISTORIC_DATA",  $TA_1MIN      ],
    -d5  => [ "DISPLAY_HISTORIC_DATA",  $TA_5MINS     ],
    -d10 => [ "DISPLAY_HISTORIC_DATA",  $TA_10MINS    ],
    -d15 => [ "DISPLAY_HISTORIC_DATA",  $TA_15MINS    ],
    -d30 => [ "DISPLAY_HISTORIC_DATA",  $TA_30MINS    ],
    -d1H => [ "DISPLAY_HISTORIC_DATA",  $TA_1HOUR     ],
);


my %tableOption = (
    -z => [ $TA_REPLACE_ZERO_PRICE_BAR, 0 ],
    -t => [ 0, $TA_USE_TOTAL_VOLUME | $TA_USE_TOTAL_OPENINTEREST ],
    -i => [ 0, $TA_ALLOW_INCOMPLETE_PRICE_BARS ],
    -f => [ 0, $TA_DISABLE_PRICE_VALIDATION ],
);


sub print_usage {
    my $ta_ver = TA_GetVersionString();

    print <<"EOS";
ta_sql V$ta_ver - SQL for market data

Usage: ta_sql -c    <opt> <loc> <catsql>
       ta_sql -s    <opt> <loc> <catsql> <cat> <symsql>
       ta_sql -d<p> <opt> <loc> <catsql> <cat> <symsql> <sym> <infosql> [period]

    Specify one of the following action switch:
      -c     Display all supported categories
      -s     Display all symbols for a given category
      -d<p>  Display market data for the specified <p> period. Use
             \"d,w,m,q,y\" for \"daily,weekly,monthly,quarterly,yearly,\"
             \"1,5,10,15,30,1H\" for \"1,5,10,15,30mins,1hour\"

    <opt> are optional switches:
      -z TA_REPLACE_ZERO_PRICE_BAR flag for TA_AddDataSource.
      -t TA_USE_TOTAL_VOLUME and OPENINTEREST flag for TA_HistoryAlloc.
      -i TA_ALLOW_INCOMPLETE_PRICE_BARS flag for TA_HistoryAlloc.
      -f TA_DISABLE_PRICE_VALIDATION flag for TA_HistoryAlloc.

      -u=<str>  Specify the username for TA_AddDataSource.
      -p=<str>  Specify the password for TA_AddDataSource.

    <loc>     is the TA_AddDataSource location parameter.
    <catsql>  is the TA_AddDataSource category parameter.
    <cat>     is a string of a given category.
    <symsql>  is the TA_AddDataSource symbol parameter.
    <sym>     is a string of a given symbol.
    <infosql> is the TA_AddDataSource info parameter.
    [period]  optional value in sec specifying the database period.

  Market data output is \"Date,Open,High,Low,Close,Volume\"
  or \"Date,Time,Open,High,Low,Close,Volume\" for intraday data.

  Check http://ta-lib.org/d_source/d_sql.html for usage examples.

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
    my $intraday = ($haParam->{period} < $TA_DAILY);

    my $history = $udb->History($haParam);
    ($history->{retCode} == $TA_SUCCESS) or print_error( $history->{retCode} ) and return -1;

    if ( $history->{nbBars} == 0 ) {
        print "No data available\n";
        return 0;
    }

    # copy data to my variables to speedup the access
    my @timestamp = @{$history->{timestamp}};
    my @open      = @{$history->{open}};
    my @high      = @{$history->{high}};
    my @low       = @{$history->{low}};
    my @close     = @{$history->{close}};
    my @volume    = @{$history->{volume}};
    my $nbBars    = $history->{nbBars};

    for ( my $i = 0; $i < $nbBars; $i++ ) {
        #print $timestamp[$i]->GetStringDate();
        printf "%02u-%02u-%02u", $timestamp[$i]{year},
                                 $timestamp[$i]{month},
                                 $timestamp[$i]{day};

        print ',',$timestamp[$i]->GetStringTime() if $intraday;

        printf ",%.2f", $open[$i]   if defined @open;
        printf ",%.2f", $high[$i]   if defined @high;
        printf ",%.2f", $low[$i]    if defined @low;
        printf ",%.2f", $close[$i]  if defined @close;
        printf ",%d",   $volume[$i] if defined @volume;
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
$dsParam->{period}   = shift;


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
