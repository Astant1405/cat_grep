#include "cat.h"

Flags arg_parser(int argc, char **argv) {
  Flags flag = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bnsTEetv", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        flag.b = 1;
        flag.n = 0;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'T':
        flag.T = 1;
        break;
      case 'E':
        flag.E = 1;
        break;
      case 't':
        flag.T = 1;
        flag.v = 1;
        break;
      case 'e':
        flag.E = 1;
        flag.v = 1;
        break;
      default:
        break;
    }
  }
  return flag;
}

char v_flag(char ch) {
  unsigned char c = ch;
  if (c > 127 && c < 160) printf("M-^");
  if ((c < 32 && c != '\n' && c != '\t') || c == 127) printf("^");
  if ((c < 32 || (c > 126 && c < 160)) && c != '\n' && c != '\t')
    c = c > 126 ? c - 128 + 64 : c + 64;
  return ch;
}

void output_text(Flags *flag, char *line, int n) {
  for (int i = 0; i < n; i++) {
    if (flag->T && line[i] == '\t') {
      printf("^I");
    } else {
      if (flag->E && line[i] == '\n') {
        printf("$");
      }
      if (flag->v) {
        line[i] = v_flag(line[i]);
      }
      putchar(line[i]);
    }
  }
}

void output(Flags *flag, char *argv[]) {
  FILE *myfile = fopen(argv[optind], "r");
  char *line = NULL;
  size_t memline = 0;
  int read = 0;
  int line_count = 1;
  int empty_count = 0;
  read = getline(&line, &memline, myfile);
  while (read != -1) {
    if (flag->n && flag->b) {
      flag->n = 0;
    }
    if (line[0] == '\n') {
      empty_count += 1;
    } else
      empty_count = 0;
    if (flag->s && empty_count > 1) {
    } else {
      if (flag->n || flag->b) {
        if (flag->n) {
          printf("%6d\t", line_count);
          line_count += 1;
        } else if (flag->b && line[0] != '\n') {
          printf("%6d\t", line_count);
          line_count += 1;
        } else if (flag->b && flag->E && line[0] == '\n') {
          printf("        $");
        }
      }
      output_text(flag, line, read);
    }
    read = getline(&line, &memline, myfile);
  }
  free(line);
  fclose(myfile);
}

int main(int argc, char *argv[]) {
  Flags flag = arg_parser(argc, argv);
  output(&flag, argv);

  return 0;
}