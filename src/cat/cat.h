#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flags {
  int b, v, n, s, T, E;
} Flags;

Flags arg_parser(int argc, char **argv);
char v_flag(char ch);
void output_text(Flags *flag, char *line, int n);
void output(Flags *flag, char *argv[]);

#endif
