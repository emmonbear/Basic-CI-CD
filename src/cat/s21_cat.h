#ifndef CATFLAGS_H
#define CATFLAGS_H
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  bool number_non_blank;     ///< numbers only non-empty lines
  bool mark_end;             ///< but also display end-of-line characters as $
  bool number_all;           ///< number all output lines
  bool squeeze;              ///< squeeze multiple adjacent blank lines
  bool tab;                  ///< 	but also display tabs as ^I
  bool print_non_printable;  ///< print non printable
  int line_cnt;              ///< line counter
  bool is_first_file;        ///< check if the file being processed is the first
  bool is_line_break;   ///< check if the current character is a '\n' character
  bool symbol_is_read;  ///< check if the current character has been read
} flag_t;

flag_t parcer(int argc, char *argv[]);
flag_t process_flag(int c, flag_t flags);
void set_table(const char *table[static 256]);
void open_file(int argc, char *argv[], flag_t flags,
               const char *table[static 256]);
char read_file(FILE *file, flag_t *flags, char last_symbol,
               const char *table[static 256]);
void cat_flag_e(const char *table[static 256]);
void cat_flag_t(const char *table[static 256]);
void cat_flag_v(const char *table[static 256]);

#endif