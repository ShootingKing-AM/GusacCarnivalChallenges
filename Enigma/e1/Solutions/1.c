#include <stdio.h>

int main()
{
    char chr1[32], chr2[32];

    printf( "Str 1 : " );
    scanf( "%s", chr1 );
    printf( "Str 2 : " );
    scanf( "%s", chr2 );

    int diff = chr2[0] - chr1[0];
    if( diff > 13 ) diff -= 26;

    printf( "%d\n", diff );
    //system( "pause" );
}
