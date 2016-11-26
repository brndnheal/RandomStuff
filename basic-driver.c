#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CUR_BASE 50;




char** process_lines(FILE* file){

	int CUR_MAX = CUR_BASE;
	int CUR_LINES = CUR_BASE;
	int length = 0;
	int line_count=0;
	int ch = 1;

	char *buffer = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.
	char** lines = (char**) malloc(sizeof(char *) * CUR_LINES);

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
	return lines;
}


