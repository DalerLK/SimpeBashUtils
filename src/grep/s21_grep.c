#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

int main(int argc, char *argv[]) {
  struct flags flag = {0};
  char *line = 0;
  char f_buffer[BUFSIZ] = {0}, e_buffer[BUFSIZ] = {0},
       regular_buffer[BUFSIZ] = {0}, f_var[] = "0";
  int c = 0, f_counter = 0, e_counter = 0, c_counter = 0, l_counter = 0,
      n_counter = 0, index_option = 0, regflags = REG_EXTENDED, line_check = 0,
      match_check = REG_NOMATCH;
  size_t n_getline = 0;
  regex_t regular;
  regmatch_t regmat[1];
  while ((c = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, &index_option)) !=
         -1) {
    switch (c) {
      case 'e':
        if (e_counter > 0) {
          strcat(e_buffer, "|");
        }
        e_counter++;
        strcat(e_buffer, optarg);
        flag.e = 1;
        break;
      case 'i':
        flag.i = 1;
        regflags |= REG_ICASE;
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
        if (f_counter > 0) {
          strcat(f_buffer, "|");
        }
        FILE *f_file = fopen(optarg, "r");
        while ((f_var[0] = getc(f_file)) != EOF) {
          if (f_var[0] == '\n') {
            strcat(f_buffer, "|");
          }
          strcat(f_buffer, f_var);
        }
        f_counter++;
        fclose(f_file);
        flag.f = 1;
        break;
      case 'o':
        flag.o = 1;
        break;

      default:
        break;
    }
  }
  if (flag.s) {
    int file_check = ++optind;
    FILE *s_file = fopen(argv[file_check], "r");
    while (argc >= file_check) {
      if (s_file == NULL) {
        exit(0);
      } else {
        fclose(s_file);
      }
    }
  }
  strcat(regular_buffer, argv[optind]);
  if (flag.f || flag.e) {
    memset(regular_buffer, 0, BUFSIZ);
  }
  if (!flag.f && !flag.e) {
    optind++;
  }
  if (flag.f) {
    strcat(regular_buffer, f_buffer);
  }
  if (flag.e) {
    if (flag.f) {
      strcat(regular_buffer, "|");
      strcat(regular_buffer, e_buffer);
    } else {
      strcat(regular_buffer, e_buffer);
    }
  }

  regcomp(&regular, regular_buffer, regflags);
  int name_print = argc - optind;
  while (argc > optind) {
    FILE *main_file = fopen(argv[optind], "r");
    while ((line_check = (getline(&line, &n_getline, main_file)) != -1)) {
      n_counter++;
      match_check = regexec(&regular, line, 1, regmat, 0);
      if (match_check != REG_NOMATCH) l_counter = 1;
      if (match_check != REG_NOMATCH && !flag.v && !flag.l) {
        if (flag.c) {
          c_counter++;
          continue;
        }
        if (name_print > 1 && !flag.h) printf("%s:", argv[optind]);
        if (flag.n) printf("%d:", n_counter);
        if (strchr(line, '\n') == NULL) strcat(line, "\n");
        if (flag.o) {
          size_t len_buff = regmat->rm_eo - regmat->rm_so;
          while (len_buff) {
            printf("%c", line[regmat->rm_so++]);
            len_buff--;
          }
          printf("\n");
          continue;
        }
        printf("%s", line);
      }
      if (match_check == REG_NOMATCH && flag.v && !flag.l) {
        if (flag.c) {
          c_counter++;
          continue;
        }
        if (name_print > 1 && !flag.h) printf("%s:", argv[optind]);
        if (flag.n) printf("%d:", n_counter);
        if (strchr(line, '\n') == NULL) strcat(line, "\n");
        printf("%s", line);
      }
    }
    if (flag.c) {
      if (name_print > 1 && !flag.h) printf("%s:", argv[optind]);
      if (flag.l) {
        c_counter > 0 ? printf("%d\n", l_counter) : printf("%d\n", l_counter);
      } else {
        printf("%d\n", c_counter);
      }
      c_counter = 0;
    }
    if (flag.l) {
      if (l_counter) printf("%s\n", argv[optind]);
      l_counter = 0;
    }
    fclose(main_file);
    optind++;
    n_counter = 0;
  }
  free(line);
  regfree(&regular);
  return 0;
}
