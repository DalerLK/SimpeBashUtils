#include <getopt.h>
#include <stdio.h>

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

int main(int argc, char *argv[]) {
  struct flags flag = {0};
  int option_index = 0;
  int c = 0;
  int counter = 0, new_line = 0, previous_c = 1, test = 0, test2 = 0,
      allright = 1;
  static struct option long_flags[] = {{"--number-nonblank", 0, 0, 'b'},
                                       {"--number", 0, 0, 'n'},
                                       {"--squeeze-blank", 0, 0, 's'},
                                       {0, 0, 0, 0}};

  while ((c = getopt_long(argc, argv, "benstvET", long_flags, &option_index)) !=
         -1) {
    test++;
    switch (c) {
      case 'E':
        flag.e = 1;
        break;
      case 'T':
        flag.t = 1;
        break;
      case 'b':
        flag.b = 1;
        break;
      case 'e':
        flag.e = 1;
        flag.v = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 't':
        flag.t = 1;
        flag.v = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      default:
        break;
    }
  }
  if (flag.b == 1) {
    flag.n = 0;
  }
  while (*argv[1] == '-') {
    test2++;
    argv++;
  }

  argv++;
  argc--;

  while (argc > test2) {
    FILE *test1 = fopen(*argv, "r");
    while ((c = getc(test1)) != EOF) {
      if (flag.s == 1) {
        if (c == '\n') {
          previous_c++;
          if (previous_c == 3) {
            previous_c--;
            continue;
          }
        } else {
          previous_c = 0;
        }
      }
      if (flag.b == 1) {
        if (c != '\n') {
          if (new_line == 0) {
            printf("%6d\t", ++counter);
            new_line = 1;
          }
        } else {
          new_line = 0;
        }
      }
      if (flag.n == 1) {
        if (new_line == 0) {
          printf("%6d\t", ++counter);
          new_line = 1;
        }
        if (c == '\n') {
          new_line = 0;
        }
      }
      if (flag.e == 1) {
        if (c == '\n') {
          printf("%c", '$');
        }
      }
      if (flag.t == 1) {
        if (c == '\t') {
          printf("^I");
          allright = 0;
        }
      }
      if (flag.v == 1) {
        if (c <= 31 && c != 9 && c != 10) {
          printf("^%c", c + 64);
          allright = 0;
        }
      }
      if (allright == 1) {
        printf("%c", c);
      }
      allright = 1;
    }
    argc--;
    argv++;
    counter = 0;
    previous_c = 1;
    fclose(test1);
  }
  return 0;
}
