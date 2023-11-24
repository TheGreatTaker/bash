#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct flags {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
  bool err;
} flags;

void print_symb(int c, int *prev, flags *info, int *index, bool *eline_printed);
int reader(char *name, flags info);
void read_flags(flags *info, int argc, char *argv[]);

#endif