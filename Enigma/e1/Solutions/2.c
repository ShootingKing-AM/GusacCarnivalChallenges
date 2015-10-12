#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *str, ch;

    str = (char *)malloc(sizeof(char));
    int i = 0;
    int offset;
    printf( "Cipher : " );
    while( (ch = fgetc( stdin )) != '\n' )
    {
        str = (char *)realloc(str, (i+1)*sizeof(char));
        str[i] = ch;

        if( !str )
        {
            printf( "Memory Re-Allocation Failed !! at %c[%d]\n", ch, i );
            //system( "pause" );
            return 0;
        }
        i++;
    }

    str[i] = '\0';

    printf( "Offset : " );
    scanf( "%d", &offset );

    int len = i;
    //offset *= -1;
    for( i = 0; i < len; i++ )
    {
        if( str[i] == ' ' ) continue;
        if( (str[i]-offset > 'z' && offset<0) || (str[i]-offset < 'a' && offset>0))
        {
            str[i] = ('z'-'a')+str[i]-offset;
        }
        else if( (str[i]-offset < 'a' && offset<0) || (str[i]-offset > 'z' && offset>0) )
        {
            str[i] = str[i]-offset-('z'-'a');
        }
        else
        {
            str[i] = str[i]-offset;
        }
    }

    printf( "Text : %s\n", str );
    //system("pause");
    return 0;
}

