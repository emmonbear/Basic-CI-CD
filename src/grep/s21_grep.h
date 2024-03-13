#ifndef S21_GREP_H
#define S21_GREP_H

#define _GNU_SOURCE

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATCHES 256

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool o;
  bool f;
  bool s;
} options;

options grep_options(int argc, char *argv[]);
void parcer(int argc, char *argv[], char ***patterns, char **pattern_filename,
            int *pattern_count);
void free_mem(char ***pattern, char **pattern_filename, int pattern_count,
              char ***filename, int file_count);
void find_pattern(int argc, char *argv[], options opt, char ***pattern,
                  char *pattern_filename, int *pattern_count, char ***filename,
                  int *file_count);
void grep(char **filename, int file_count, int count, char **pattern,
          char *pattern_filename, int pattern_count, FILE *file, options opt);
void grep_flags(char *line, char **pattern, int pattern_count, char **filename,
                char *pattern_filename, int count, int file_count,
                int numeration, int *sum, int end, FILE *file, options opt);
void multiple_files(char **filename, int count, int file_count, options opt);
bool grep_search(char *line, char *search, int c_flag, char **filename,
                 int count, int file_count, int numeration, int end, FILE *file,
                 regex_t preg, regmatch_t match, options opt);
void grep_print(char *line, char **filename, int count, int file_count,
                int numeration, int end, regmatch_t match, FILE *file,
                options opt);

#endif