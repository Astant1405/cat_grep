#ifndef GREP_H
#define GREP_H
#define _POSIX_C_SOURCE 200809L

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flags {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
} Flags;

void add_pattern(Flags *flag, char *pattern);
void add_reg_from_file(Flags *flag, char *filepath);
Flags arg_parser(int argc, char **argv);
void output_text(char *line, int n);
void processFile(Flags flag, char *path, regex_t *reg, int file_count);
void output(Flags flag, int argc, char *argv[]);

#endif