#ifndef FORMATTER_H
#define FORMATTER_H_
#endif

int process_command(char *new_line);
void make_new_line(char* format_line);
void reformating(char** lines,int num_lines);
char **format_file(FILE *infile);
int read_lines(FILE* file, char **lines);
int read_stdin(char ** lines);
char **format_lines(char **lines, int num_lines);
