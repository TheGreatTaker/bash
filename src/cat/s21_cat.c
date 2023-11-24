#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flags info = {0};
  read_flags(&info, argc, argv);
  // Обрабатываем каждый файл, переданный в аргументах командной строки
  if (!info.err) {
    for (int i = 1; i < argc; i++) {
      if ((!reader(argv[i], info) && i == argc)) {
        fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
      }
    }
  } else
    fprintf(stderr, "usage: s21_cat [-benstv] [file ...]\n");

  return 0;
}

void read_flags(flags *info, int argc, char *argv[]) {
  static const struct option longFlags[] = {{"number-nonblank", 0, NULL, 'b'},
                                            {"number", 0, NULL, 'n'},
                                            {"squeeze-blank", 0, NULL, 's'},
                                            {NULL, 0, NULL, 0}};
  int true_flags;
  while ((true_flags = getopt_long(argc, argv, "+bevEnstT", longFlags, NULL)) !=
         -1) {
    switch (true_flags) {
    case 'b':
      info->b = true;
      break;
    case 'e':
      info->e = true;
      info->v = true;
      break;
    case 'E':
      info->e = true;
      break;
    case 'n':
      info->n = true;
      break;
    case 's':
      info->s = true;
      break;
    case 't':
      info->t = true;
      info->v = true;
      break;
    case 'T':
      info->t = true;
      break;
    case 'v':
      info->v = true;
      break;
    default:
      info->err = true;
    }
  }
}

void print_symb(int c, int *prev, flags *info, int *index, bool *eline_printed) {
  bool ret = false;
  if (info->s && *prev == '\n' && c == '\n' && *eline_printed) {
    ret = true;
  }
  if (!ret){
  if (*prev == '\n' && c == '\n') {
    *eline_printed = true;
  } else {
    *eline_printed = false;
  }
  if (((info->n && !info->b) || (info->b && c != '\n')) && *prev == '\n') {
    *index += 1;
    printf("%6d\t", *index);
  }
  if (info->e && c == '\n') {
    printf("$");
  }
  if (info->t && c == '\t') {
    printf("^");
    c = '\t' + 64;
  }
  if (info->v && c >= 0 && c <= 31 && c != '\n' && c != '\t') {
    printf("^");
    c = c + 64;
  }
  if (info->v && c == 127) {
    if ((c = '?')) printf("^");
  }
  fputc(c, stdout);
  // Обновляем предыдущий символ
  *prev = c;
  }
}

int reader(char *name, flags info) {
  int err_code = 0;
  FILE *f = fopen(name, "rt");
  if (f != NULL) {
    int index = 0;
    bool eline_printed = false;
    int c = fgetc(f), prev = '\n';
    while (c != EOF) {
      print_symb(c, &prev, &info, &index, &eline_printed);
      c = fgetc(f);
    }
    fclose(f);
  } else {
    err_code = 1;
  }
  return err_code;
}