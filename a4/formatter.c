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

int process_command(char *new_line){
	char* word=(char*)malloc(sizeof(char)*strlen(new_line));
	char cmd[4];
	int pc = 1;
/* dealing with the command things*/
	if (new_line[0] == '.'){
		sscanf(new_line, "%s %s", cmd, word); 

		if(strcmp(cmd,".LW") == 0) {
			LW = atoi(word);
			FT = 1;
			return 2;
		}
		else if(strcmp(cmd,".LM") == 0) LM = atoi(word);
		else if(strcmp(cmd,".LS") == 0) LS = atoi(word);
		else if(strcmp(cmd, ".FT") == 0){
			if(strcmp(word,"off") == 0) FT=0;  
			else FT=1;
		}
		else pc = 0;
	}
	else 
		pc = 0;
	free(word);
	return pc;
}

void make_new_line(char * format_line){
	//format_line=(char*)realloc(format_line,sizeof(char)*LW); 
	int i=0;
	while(i < LW){ /*deal with left margin */
		format_line[i]=' ';
		i++;
	}
	//printf("format : %s\n",format_line);

}

void reformating(char** lines,int num_lines){
	
	char* new_line;
	char *w;
	int first; /* the first word of the output line, dealing with LM and no space before it*/
	int ls;
	int is_cmd; /* reconginze command */
	
	char* reformat_line = (char*)malloc(sizeof(char)*LW);
	make_new_line(reformat_line);
	first = 1;
	int counter=LM;
	for(int i =0;i<num_lines;i++){

		new_line=lines[i];
		/* if the line is a command line, the process_command() will take the information */
		is_cmd = process_command(new_line);
	
		if(!is_cmd){
			/*if it is the text need to process, then check if it needs formating */
			if(FT){
				w = strtok(new_line, "\r\n\t ");

				/* dealing the blank line*/
				if(w == NULL){ 
					if(counter > LM){ /* if exceed space of LM, start next line */
						printf("%s",reformat_line);
						if(i!=num_lines-1){
							printf("\n");
						}
					}
					
					for(ls = LS; ls > 0; ls --){  /* dealing with Line Space */
							printf( "\n");
					}

					printf("\n"); /* "blank line" text */

					for(ls = LS; ls > 0; ls --){
							printf( "\n");
					}
					/* The next paragraph */
					make_new_line(reformat_line);
					first = 1;
					counter=LM;

				}
				/* processing normally: only one space after each word */
				while(w != NULL){
					if(counter + 1 +strlen(w) > LW){  /* add an extra 1: \0 */
						printf("%s", reformat_line);
						if(i!=num_lines-1){
							printf("\n");
						}
						for(ls = LS; ls > 0; ls --){

							printf( "\n");
						}
						make_new_line(reformat_line);
						first = 1;
						counter=LM;
					}
					if(!first){
					    	/* add space after word but not the first one */
						reformat_line[counter]=' ';
						counter++;
					}
					for(int j=0;j<strlen(w);j++){
						reformat_line[counter+j]=w[j];
					}
					counter+=strlen(w);
					w = strtok(NULL, "\r\n\t ");
					first = 0;
				}

			}
			else{
				printf("%s", new_line);
				if(i!=num_lines-1){
					printf("\n");
				}
			}
			
		}
		/*if there is a command, might need to reindent*/
		else{
			if(is_cmd==2){
				reformat_line=(char*)realloc(reformat_line,sizeof(char)*LW); 
			}
			make_new_line(reformat_line);
			counter=LM;
		}

		free(lines[i]);

	}
	if(counter > LM) 
		printf("%s",reformat_line);
	free(reformat_line);

}

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
	
	reformating(lines,num_lines);


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
