/*
 * UVic SENG 265, Fall 2016, A#4
 *
 * This will contain a solution to format265alt.c. In order to complete the
 * task of formatting a file, it must open the file and pass the result
 * to a routine in formatter.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include "formatter.h"
#define CUR_BASE 128

int main(int argc, char *argv[]) {

	if(argc == 1){
		
		char **lines = (char**) malloc(sizeof(char *) * CUR_BASE);
		int num_lines= read_stdin(lines);
		format_lines(lines,num_lines);
	}
	else{
		FILE* file = fopen(argv[1],"r");
		if( file==NULL ){
			printf("Invalid File Name");
		}
		else{
			format_file(file);
		}
	}
	exit(0);
}
