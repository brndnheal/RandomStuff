/*
 * UVic SENG 265, Fall 2016,  A#4
 *
 * This will contain the bulk of the work for the fourth assignment. It
 * provide similar functionality to the class written in Python for
 * assignment #3.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"
#define CUR_BASE 128

int LW = 0;
int LM = 0;
int FT = 0;  
/* 0 for 'off' mode, 1 for 'on' mode */
int LS = 0;

char **format_file(FILE *infile) {
	char **lines = (char**) malloc(sizeof(char *) * CUR_BASE);
	int line_count = (int)read_lines(infile,lines);
	
	format_lines(lines,line_count);
	
	free(lines);
}


int read_lines(FILE* file,char **lines){
	int CUR_MAX = CUR_BASE;
	int CUR_LINES = CUR_BASE;
	int length = 0;
	int line_count=0;
	int ch = 1;

	char *buffer = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.

	while(ch != EOF){
		while  (ch != '\n'&&ch != EOF && ch !='\r')  {
			if(length==CUR_MAX) { // time to expand ?
			      CUR_MAX *= 2; // expand to double the current size of anything similar.
			      buffer = realloc(buffer, sizeof(char) * CUR_MAX); // re allocate memory.
			}
			ch = fgetc(file); // read from stream.
			buffer[length] = (char)ch; // stuff in buffer.
			length++;
		}
		buffer[length-1]='\0';
		printf("%s\n",buffer);
		lines[line_count]=buffer;
		line_count++;
		if(line_count==CUR_LINES){
			CUR_LINES*=2;
			lines = realloc(lines, sizeof(char *) * CUR_LINES);
		}
		CUR_MAX=CUR_BASE;
		buffer = (char*) malloc(sizeof(char) * CUR_MAX);
		length =0;
		if(ch!=EOF){
			ch=1;
		}
	}
	return line_count;
}

int read_stdin(char **lines){
	int CUR_MAX = CUR_BASE;
	int CUR_LINES = CUR_BASE;
	int length = 0;
	int line_count=0;
	int ch = 1;

	char *buffer = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.

	while(ch != EOF){
		while  (ch != '\n'&&ch != EOF && ch !='\r')  {
			if(length==CUR_MAX) { // time to expand ?
			      CUR_MAX *= 2; // expand to double the current size of anything similar.
			      buffer = realloc(buffer, sizeof(char) * CUR_MAX); // re allocate memory.
			}
			ch = getchar(); // read from stdin
			buffer[length] = (char)ch; // stuff in buffer.
			length++;
		}
		buffer[length-1]='\0';
		printf("%s\n",buffer);
		lines[line_count]=buffer;
		CUR_MAX=CUR_BASE;
		buffer = (char*) malloc(sizeof(char) * CUR_MAX);
		length =0;
		if(ch!=EOF){
			ch=1;
			line_count++;
			if(line_count==CUR_LINES){
				CUR_LINES*=2;
				lines = realloc(lines, sizeof(char *) * CUR_LINES);
			}
		}
	}
	return line_count;
}

char **format_lines(char **lines, int num_lines) {
	char **result = NULL;

#ifdef DEBUG
	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL) {
		return NULL;
	}

	result[0] = (char *)malloc(sizeof(char) * 80);
	if (result[0] == NULL) {
		return NULL;
	}
	strncpy(result[0], "(machine-like voice) EXTERMINATE THEM!", 79);

	result[1] = (char *)malloc(sizeof(char) * 2);
	if (result[1] == NULL) {
		return NULL;
	}
	result[1][0] = '\0';
#endif

	return result;
}
