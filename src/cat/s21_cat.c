#include "s21_cat.h"

void reader(char *argv[],flags ) {
  char buf[4096];
  int read_bytes;
  read_bytes = read(fd, buf, 4096);
  while (read_bytes > 0) {
    printf("%.*s", read_bytes, buf);
    read_bytes = read(fd, buf, 4096);
  }
}
void read_flags(flags *info, int argc, char *argv) {
  flags info = {0};
  static const struct option longFlags[] = {{"number-nonblank", 0, NULL, 'b'},
                                            {"number", 0, NULL, 'n'},
                                            {"squeeze-blank", 0, NULL, 's'},
                                            {NULL, 0, NULL, 0}};
  int true_flags = getopt_long(argc, argv, "bevEnstT", longFlags, NULL);
  for (; true_flags != -1;
       true_flags = getopt_long(argc, argv, "bevEnstT", longFlags, NULL)) {
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
        fprintf(stderr,"flag not found\n");
        exit(1);
    }
  }
}

/*bool args(int argc, char *argv[]){
    flags info = {0};
    for (int i = 1; i != argc ; ++i){
        if (*argv[i] == '-'){
           if (!read_flags(&info, argv[i]))
            return false;
        }
    }

    no_args(open(argv[1], O_RDONLY));
}*/

int main(int argc, char *argv[]) {
  if (argc == 1)
    no_args(STDIN_FILENO);
  else {
    if (args(argc, argv)) return 1;
  }
  return 0;
}