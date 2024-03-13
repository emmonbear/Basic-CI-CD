#include "s21_grep.h"

int main(int argc, char *argv[]) {
  options opt = {0};
  char *pattern_filename = NULL;
  char **pattern = NULL;
  char **filename = NULL;
  int pattern_count = 0, file_count = 0;
  FILE *file = NULL;
  FILE *pattern_file = NULL;

  parcer(argc, argv, &pattern, &pattern_filename, &pattern_count);
  opt = grep_options(argc, argv);
  find_pattern(argc, argv, opt, &pattern, pattern_filename, &pattern_count,
               &filename, &file_count);
  for (int count = 0; count < file_count; count++) {
    file = fopen(filename[count], "rb");
    if (opt.f) {
      pattern_file = fopen(pattern_filename, "rb");
    }
    if (opt.f && pattern_file != NULL) {
      fclose(pattern_file);
    }
    if (file == NULL || (pattern_file == NULL && opt.f)) {
      if (!opt.s || (opt.f && pattern_file == NULL)) {
        fprintf(stderr, "Ошибка открытия файла: %s\n", argv[0]);
        if (opt.f && pattern_file == NULL) {
          perror(pattern_filename);
        } else if (!opt.f) {
          perror(filename[count]);
        }
      }
      continue;
    }
    grep(filename, file_count, count, pattern, pattern_filename, pattern_count,
         file, opt);
    fclose(file);
  }
  free_mem(&pattern, &pattern_filename, pattern_count, &filename, file_count);
}

options grep_options(int argc, char *argv[]) {
  int c = 0;
  options opt = {false, false, false, false, false,
                 false, false, false, false, false};
  while ((c = getopt(argc, argv, "e:ivclnhof:s")) != -1) {
    switch (c) {
      case 'e':
        opt.e = true;
        break;
      case 'i':
        opt.i = true;
        break;
      case 'v':
        opt.v = true;
        break;
      case 'c':
        opt.c = true;
        break;
      case 'l':
        opt.l = true;
        break;
      case 'n':
        opt.n = true;
        break;
      case 'h':
        opt.h = true;
        break;
      case 'o':
        opt.o = true;
        break;
      case 'f':
        opt.f = true;
        break;
      case 's':
        opt.s = true;
        break;
    }
  }
  return opt;
}

void parcer(int argc, char *argv[], char ***pattern, char **pattern_file,
            int *pattern_count) {
  for (int i = 0; i < argc; i++) {
    if (strstr(argv[i], "-f") != NULL) {
      *pattern_file = (char *)malloc((strlen(argv[i + 1]) + 1) * sizeof(char));
      if (pattern_file == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для pattern_file\n");
        exit(1);
      }
      strcpy(*pattern_file, argv[i + 1]);
      continue;
    }
    if ((strstr(argv[i], "-e") != NULL) ||
        ((argv[i][0] == '-') && (argv[i][strlen(argv[i]) - 1] == 'e'))) {
      char **buffer =
          (char **)realloc(*pattern, ((*pattern_count) + 1) * sizeof(char *));
      if (pattern == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для patterns\n");
        exit(1);
      }
      if (buffer != NULL) {
        *pattern = buffer;
      }
      (*pattern)[*pattern_count] =
          (char *)malloc((strlen(argv[i + 1]) + 1) * sizeof(char));
      if ((*pattern)[(*pattern_count)] == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для patterns[]\n");
        exit(1);
      }
      strcpy((*pattern)[(*pattern_count)++], argv[i + 1]);
      continue;
    }
  }
}

void free_mem(char ***pattern, char **pattern_filename, int pattern_count,
              char ***filename, int file_count) {
  for (int i = 0; i < pattern_count; i++) {
    if ((*pattern)[i] != NULL) {
      free((*pattern)[i]);
      (*pattern)[i] = NULL;
    }
  }
  if (*pattern != NULL) {
    free(*pattern);
    *pattern = NULL;
  }
  if (*pattern_filename != NULL) {
    free(*pattern_filename);
    *pattern_filename = NULL;
  }
  for (int i = 0; i < file_count; i++) {
    if ((*filename)[i] != NULL) {
      free((*filename)[i]);
      (*filename)[i] = NULL;
    }
  }
  if (*filename != NULL) {
    free(*filename);
    *filename = NULL;
  }
}

void find_pattern(int argc, char *argv[], options opt, char ***pattern,
                  char *pattern_filename, int *pattern_count, char ***filename,
                  int *file_count) {
  bool pattern_check = false;
  for (int i = 0; i < argc; ++i) {
    if (*argv[i] == '-' || argv[i] == argv[0]) {
      continue;
    }
    if (opt.f && strcmp(argv[i], pattern_filename) == 0) {
      continue;
    }
    for (int j = 0; j < *pattern_count; j++) {
      if (opt.e && strcmp(argv[i], (*pattern)[j]) == 0) {
        pattern_check = true;
        break;
      }
    }
    if (pattern_check) {
      pattern_check = false;
      continue;
    }
    if (!opt.e && !opt.f && *pattern_count == 0) {
      *pattern =
          (char **)realloc(*pattern, (*pattern_count + 1) * sizeof(char *));
      if (*pattern == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для pattern\n");
        exit(1);
      }
      (*pattern)[*pattern_count] =
          (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
      if ((*pattern)[(*pattern_count)] == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для patterns[]\n");
        exit(1);
      }
      strcpy((*pattern)[(*pattern_count)++], argv[i]);
      continue;
    }
    char **buffer =
        (char **)realloc((*filename), ((*file_count) + 1) * sizeof(char *));
    if (buffer == NULL) {
      fprintf(stderr, "Ошибка выделения памяти для filename1\n");
      exit(1);
    }
    if (buffer != NULL) {
      *filename = buffer;
      (*filename)[*file_count] =
          (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
      if ((*filename)[(*file_count)] == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для filename[]\n");
        exit(1);
      }
      strcpy((*filename)[(*file_count)++], argv[i]);
    }
  }
}

void grep(char **filename, int file_count, int count, char **pattern,
          char *pattern_filename, int pattern_count, FILE *file, options opt) {
  char *line = NULL;
  size_t buffer = 0;
  ssize_t read = 0;
  int sum = 0, numeration = 0, end = 0;

  fseek(file, 0, 2);
  end = ftell(file);
  fseek(file, 0, 0);
  while ((read = getline(&line, &buffer, file)) != -1) {
    numeration++;
    grep_flags(line, pattern, pattern_count, filename, pattern_filename, count,
               file_count, numeration, &sum, end, file, opt);
  }
  if (sum > 0 && opt.l) {
    multiple_files(filename, count, file_count, opt);
  }
  if (opt.c && !opt.l) {
    multiple_files(filename, count, file_count, opt);
    printf("%d\n", sum);
  }
  free(line);
}
void grep_flags(char *line, char **pattern, int pattern_count, char **filename,
                char *pattern_filename, int count, int file_count,
                int numeration, int *sum, int end, FILE *file, options opt) {
  regex_t preg = {0};
  regmatch_t match = {0};
  size_t buffer_size = 0;
  bool trigger = false;
  int c_flag = REG_NEWLINE;
  if (opt.i) {
    c_flag = REG_ICASE;
  }
  if (opt.f) {
    FILE *file_1 = NULL;
    file_1 = fopen(pattern_filename, "rb");
    if (file_1 != NULL) {
      char *line_1 = NULL;
      ssize_t read_1 = 0;
      while ((read_1 = getline(&line_1, &buffer_size, file_1)) != -1) {
        for (size_t i = 0; i < strlen(line_1); i++) {
          if (line_1[i] == '\n') {
            line_1[i] = '\0';
          }
          if (grep_search(line, line_1, c_flag, filename, count, file_count,
                          numeration, end, file, preg, match, opt)) {
            trigger = true;
          }
        }
      }
      free(line_1);
      fclose(file_1);
    }
  }
  if (!opt.f) {
    for (int i = 0; i < pattern_count; i++) {
      if (grep_search(line, pattern[i], c_flag, filename, count, file_count,
                      numeration, end, file, preg, match, opt)) {
        trigger = true;
      }
    }
  }
  if (opt.f && opt.e) {
    for (int i = 0; i < pattern_count; i++) {
      if (grep_search(line, pattern[i], c_flag, filename, count, pattern_count,
                      numeration, end, file, preg, match, opt)) {
        trigger = true;
      }
    }
  }
  if ((trigger && !opt.v) || (!trigger && opt.v)) {
    if (!opt.c && !opt.l && !opt.o) {
      grep_print(line, filename, count, file_count, numeration, end, match,
                 file, opt);
    }
    ++(*sum);
  }
}
bool grep_search(char *line, char *search, int c_flag, char **filename,
                 int count, int file_count, int numeration, int end, FILE *file,
                 regex_t preg, regmatch_t match, options opt) {
  bool trigger = false;
  char *temp = line;
  regcomp(&preg, search, c_flag);
  while (!regexec(&preg, temp, 1, &match, 0)) {
    trigger = true;
    if (opt.o && !opt.l && !opt.v && !opt.c) {
      grep_print(temp, filename, count, file_count, numeration, end, match,
                 file, opt);
    }
    if (strlen(temp) == strlen(search)) {
      break;
    } else {
      temp += match.rm_eo + 1;
    }
  }
  regfree(&preg);
  return trigger;
}
void grep_print(char *line, char **filename, int count, int file_count,
                int numeration, int end, regmatch_t match, FILE *file,
                options opt) {
  multiple_files(filename, count, file_count, opt);
  if (opt.n) {
    printf("%d:", numeration);
  }
  for (size_t i = 0; i < strlen(line); i++) {
    if (!opt.o) {
      printf("%c", line[i]);
    } else {
      if ((int)i >= match.rm_so && (int)i < match.rm_eo) {
        printf("%c", line[i]);
      }
    }
  }
  if (opt.o) {
    printf("\n");
  }
  if (ftell(file) == end && line[strlen(line) - 1] != '\n' && !opt.o) {
    printf("\n");
  }
}

void multiple_files(char **filename, int count, int file_count, options opt) {
  if (opt.l) {
    printf("%s\n", filename[count]);
  }
  if (file_count > 1 && !opt.l && !opt.h) {
    printf("%s:", filename[count]);
  }
}
