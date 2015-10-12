#include <stdio.h>
#include <string.h>

#include "wavfile.c"

const int DURATION_PER_CODE = WAVFILE_SAMPLES_PER_SECOND/4;

void SetWaveform(short wf[], char code )
{
    switch (code)
    {
        case '.': // level 1
        {
            memset( &wf, 32000*1, DURATION_PER_CODE );
        }
        case '-': // level 2
        {
            memset( &wf, 32000*2, DURATION_PER_CODE );
        }
        case 'x':
        {
            memset( &wf, 0, DURATION_PER_CODE );
        }
    }
}

char Codes[][7] =
{		
	".-",
	"-...",
	"-.-.",
	"-..",
	".",
	"..-.",
	"--.",
	"....",
	"..",
	".---",
	"-.-",
	".-..",
	"--",
	"-.",
	"---",
	".--.",
	"--.-",
	".-.",
	"...",
	"-",
	"..-",
	"...-",
	".--",
	"-..-",
	"-.--",
	"--..",

	/*"-----",
	".----",
	"..---",
	"...--",
	"....-",
	".....",
	"-....",
	"--...",
	"---..",
	"----.",
	"/"*/};

int main()
{

	char ch;	
    char *str = (char *)malloc(sizeof(char));
	
    int i = 0;
	
    printf( "Text : " );
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
	
	int len = i;
	int templen = 0;

    for( i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
    }

    //printf( "|%s| %c %s", str, str[0], Codes[(int)str[0]-'a'] );
	//system( "pause" );

    int OutputBufferLen = 1;

    for( i = 0; i < len; i++ )
    {
		str[i] -= 'a';
        if( (str[i]+'a') == ' ' )
        {
            OutputBufferLen += 2;
            continue;
        }
        OutputBufferLen += strlen(Codes[str[i]])+1;
    }

	char *Output = (char *)malloc(OutputBufferLen*sizeof(char));
	char *temp = Output;
    const char* letterDelimiter = "x";
    const char* wordDelimiter = "x";// i know ITs "xx" but just use "x" and see the magic happen XD


	for( i = 0; i < len; i++ )
	{
        if( (str[i]+'a') == (' ') )
        {
            memcpy( temp, wordDelimiter, 1 );
            temp += 1;
            continue;
        }

		templen = strlen(Codes[str[i]]);
        //printf( "|%d| |%s| |%d|\n", str[i], Codes[(int)str[i]], templen );

		memcpy( temp, Codes[str[i]], templen );
		temp += templen;
		memcpy( temp, letterDelimiter, 1 );
		temp += 1;
	}
	*temp = '\0';
	short waveform[DURATION_PER_CODE];

    if( !waveform )
    {
        printf( "Waveform memory allocation failed !\n" );
        //system( "pause" );
        return 0;
    }

	int volume = 32000;

    FILE *f = wavfile_open("resultSound.wav");

	if(!f)
    {
		printf("Couldn't open sound.wav for writing: %s",strerror(errno));
		return 0;
	}

    for( i = 0; i < OutputBufferLen; i++ )
    {
        SetWaveform(waveform, Output[i]);
	    wavfile_write(f, waveform, DURATION_PER_CODE);
    }

	printf( "%s", Output );
	wavfile_close(f);
	//system( "pause" );
	return 0;
}
