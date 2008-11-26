/*
    Rose Online Server Emulator
    Copyright (C) 2006,2007 OSRose Team http://www.dev-osrose.com

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

    depeloped with Main erose/hrose source server + some change from the original eich source
*/

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #include <cstdio>
#endif
#include <cstdio>
#include <string>
#include <time.h>
#include "log.h"

// Basic colors
typedef enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;

// Our base colors
static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

// Change console text color
void textcolor(int color)
{
    #ifdef _WIN32
    __FOREGROUND = color;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
    #else

    #endif
}

// This function logs based on flags
void Log( enum msg_type flag, char *Format, ... )
{
	va_list ap;	      // For arguments
    va_start( ap, Format );

    // Timestamp
    time_t rtime;
    time(&rtime);
    char *timestamp = ctime(&rtime);
    timestamp[ strlen(timestamp)-1 ] = ' ';

    //no timestamp for the log either.
    if(flag!=MSG_QUERY&&flag!=MSG_LOAD)
    {
        textcolor(WHITE);
        if(PRINT_LOG)
            printf("%s", timestamp );
    }
	if(PRINT_LOG)
	{
        switch (flag) {
		case MSG_NONE: // direct printf replacement
			textcolor(WHITE);
			vprintf( Format, ap );
			break;
		case MSG_STATUS:
			textcolor(GREEN);
			printf("[STATUS]: ");
			break;
		case MSG_SQL:
			textcolor(CYAN);
			printf("[SQL]: ");
			break;
		case MSG_INFO:
			textcolor(LIGHTGREEN);
			printf("[INFO]: ");
			break;
		case MSG_NOTICE:
			textcolor(LIGHTCYAN);
			printf("[NOTICE]: ");
			break;
		case MSG_WARNING:
			textcolor(YELLOW);
			printf("[WARNING]: ");
			break;
		case MSG_DEBUG:
			textcolor(LIGHTBLUE);
			printf("[DEBUG]: ");
			break;
		case MSG_ERROR:
			textcolor(RED);
			printf("[ERROR]: ");
			break;
		case MSG_FATALERROR:
			textcolor(LIGHTRED);
			printf("[FATAL ERROR]: ");
			break;
		case MSG_HACK:
			textcolor(LIGHTRED);
			printf("[HACK]: ");
			break;
		case MSG_LOAD:
			textcolor(BROWN);
			printf("[LOADING]: ");
			break;
		case MSG_GMACTION:
			textcolor(MAGENTA);
			printf("[GM ACTION]: ");
			break;
        case MSG_START:
            textcolor(MAGENTA);
            vprintf( Format, ap );
            printf( "\r\n" );
            break;
	   }
    }
    else
    {
        if(flag==MSG_CONSOLE)
        {
			textcolor(LIGHTRED);
			printf("[CONSOLE]: ");
        }
    }
	if(PRINT_LOG || flag==MSG_CONSOLE)
    	textcolor(LIGHTGRAY);
	if(flag!=MSG_QUERY && (PRINT_LOG || flag==MSG_CONSOLE))
	{
    	vprintf( Format, ap );
    	printf( (flag==MSG_LOAD) ? "\r" : "\n" );
    }
	FILE *fh = NULL;
    switch(LOG_THISSERVER)
    {
        case LOG_LOGIN_SERVER:
            fh = fopen(LOG_DIRECTORY LOG_FILENAME_LOGINFILE, "a+" );
        break;
        case LOG_CHARACTER_SERVER:
            fh = fopen(LOG_DIRECTORY LOG_FILENAME_CHARFILE, "a+" );
        break;
        case LOG_WORLD_SERVER:
            fh = fopen(LOG_DIRECTORY LOG_FILENAME_WORLDFILE, "a+" );
        break;
        case LOG_SAME_FILE:
            fh = fopen(LOG_DIRECTORY LOG_DEFAULT_FILE, "a+" );
        break;
    }
    if(flag==MSG_QUERY)
    {
        if(fh!=NULL)
            fclose(fh);
        fh = fopen(LOG_DIRECTORY "queries.txt", "a+" );
    }
    if ( fh != NULL )
    {
        fprintf( fh, "%s- ", timestamp );
        vfprintf( fh, Format, ap );
        fputc( '\n', fh );
        fclose( fh );
    }
    va_end  ( ap );
    fflush( stdout );
}
