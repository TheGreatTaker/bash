#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct flags{
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
} flags;

static const struct option longFlags[] = {{"number-nonblank", 0, NULL, 'b'},
                                            {"number", 0, NULL, 'n'},
                                            {"squeeze-blank", 0, NULL, 's'},
                                            {NULL, 0, NULL, 0}};