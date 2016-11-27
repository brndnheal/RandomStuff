#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 132
#define MAX_LINES 500


int LW = 0;
int LM = 0;
int FT = 0;  
/* 0 for 'off' mode, 1 for 'on' mode */
int LS = 0;
char output[66000];

void reformating();



int main(int argc, char *argv []){

	FILE *infile;
	infile = fopen(argv[1],"r");
	reformating(infile);
	fclose(infile);

	return 0;
}


int process_command(char *new_line){
	char word[MAX_CHAR+1];
	char cmd[4];
	int pc = 1;
/* dealing with the command things*/
	if (new_line[0] == '.'){
		sscanf(new_line, "%s %s", cmd, word); 

		if(strcmp(cmd,".LW") == 0) {
			LW = atoi(word);
			FT = 1;
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
		
	return pc;
}

/*preparing a new line for out put*/
void make_new_line(char *reformat_line){
	reformat_line[0] = '\0';
	while(strlen(reformat_line) < LM){ /*deal with left margin */
		strcat(reformat_line, " ");
	}

}

void reformating(FILE *infile){
	
	char new_line[MAX_CHAR+1];
	char *w;
	int first; /* the first word of the output line, dealing with LM and no space before it*/
	int ls;
	int is_cmd; /* reconginze command */
	
	char reformat_line[MAX_CHAR+2]; /*  1 for \n, 1 for \0 */
	make_new_line(reformat_line);
	first = 1;


	while(fgets(new_line, 132, infile)){
		/* if the line is a command line, the process_command() will take the information */
		is_cmd = process_command(new_line);
		if(!is_cmd){
			/*if it is the text need to process, then check if it needs formating */
			if(FT){
				w = strtok(new_line, "\r\n\t ");

				/* dealing the blank line*/
				if(w == NULL){ 
					if(strlen(reformat_line) > LM){ /* if exceed space of LM, start next line */
						printf("%s\n",reformat_line);
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

				}
				/* processing normally: only one space after each word */
				while(w != NULL){
					if(strlen(reformat_line) + strlen(w) + 1 > LW){  /* add an extra 1: \0 */
						printf("%s\n", reformat_line);
						for(ls = LS; ls > 0; ls --){

							printf( "\n");
						}
						make_new_line(reformat_line);
						first = 1;
					}
					if(!first){
						strncat(reformat_line, " "); /* add space after word but not the first one */
					}
					strncat(reformat_line, w); /*add words one by one*/
					w = strtok(NULL, "\r\n\t ");
					first = 0;
				}

			}
			else{
				printf("%s", new_line);  /* IF FT is off, just print the unformated file   */
			}
			
		}
		/*if there is a command, might need to reindent*/
		else{
			
			make_new_line(reformat_line);
		}


	}
	if(strlen(reformat_line) > LM) 
		printf("%s\n",reformat_line);
	
}



