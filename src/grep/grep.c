#include "grep.h"

void add_pattern(Flags *flag, char *pattern) {
  if (flag->len_pattern != 0) {
    strcat(flag->pattern + flag->len_pattern, "|");
    flag->len_pattern += 1;
  }
  flag->len_pattern +=
      sprintf(flag->pattern + flag->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(Flags *flag, char *filepath) {
  FILE *myfile = fopen(filepath, "r");
  if (myfile == NULL && !flag->s) {
    perror(filepath);
    exit(1);
  }
  char *line = NULL;
  size_t memline = 0;
  int read = getline(&line, &memline, myfile);
  while (read != -1) {
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }
    add_pattern(flag, line);
    read = getline(&line, &memline, myfile);
  }
  free(line);
  fclose(myfile);
}

Flags arg_parser(int argc, char **argv) {
  Flags flag = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flag.e = 1;
        add_pattern(&flag, optarg);
        break;
      case 'i':
        flag.i = REG_ICASE;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'f':
        flag.f = 1;
        add_reg_from_file(&flag, optarg);
        break;
      case 'o':
        flag.o = 1;
        break;
      default:
        break;
    }
  }
  if (flag.len_pattern == 0 && optind < argc) {
    add_pattern(&flag, argv[optind]);
    optind += 1;
  }
  return flag;
}

void output_text(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') {
    putchar('\n');
  }
}

void print_match(regex_t *re, char *line) {
  regmatch_t math;
  int move = 0;
  while (1) {
    int result = regexec(re, line + move, 1, &math, 0);
    if (result != 0) {
      break;
    }
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    move += math.rm_eo;
  }
}

void processFile(Flags flag, char *path, regex_t *reg, int file_count) {
  FILE *myfile = fopen(path, "r");
  if (myfile == NULL && flag.s) {
    exit(1);
  }
  char *line = NULL;
  size_t memline = 0;
  int read = 0;
  int count_string = 1;
  int count_coincidences = 0;
  read = getline(&line, &memline, myfile);
  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !flag.v) || (flag.v && result != 0)) {
      if (file_count > 1 && !flag.h && !flag.l) {
        printf("%s:", path);
      }
      if (flag.n) {
        printf("%d:", count_string);
      }
      if (flag.o) {
        print_match(reg, line);
      }
      if (!flag.c && !flag.l && !flag.o) {
        output_text(line, read);
      }
      count_coincidences += 1;
    }
    read = getline(&line, &memline, myfile);
    count_string += 1;
  }
  free(line);
  if (flag.c && !flag.l) {
    printf("%d\n", count_coincidences);
  }
  if (flag.l) {
    printf("%s\n", path);
  }
  fclose(myfile);
}

void output(Flags flag, int argc, char *argv[]) {
  regex_t re;
  int error = regcomp(&re, flag.pattern, REG_EXTENDED | flag.i);
  if (error) perror("Error");
  int file_count = 0;
  if (argc - optind > 1) {
    file_count = 1;
  }
  for (int i = optind; i < argc; i++) {
    file_count++;
    processFile(flag, argv[i], &re, file_count);
  }
  regfree(&re);
}

int main(int argc, char **argv) {
  Flags flag = arg_parser(argc, argv);
  output(flag, argc, argv);
  return 0;
}
