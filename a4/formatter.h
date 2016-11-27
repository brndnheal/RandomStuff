#ifndef FORMATTER_H
#define FORMATTER_H_
#endif

char **format_file(FILE *infile);
int read_lines(FILE* file, char **lines);
int read_stdin(char ** lines);
char **format_lines(char **lines, int num_lines);
