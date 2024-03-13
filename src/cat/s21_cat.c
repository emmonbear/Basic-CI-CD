#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flag_t flags = parcer(argc, argv);
  const char *table[256];
  set_table(table);

  if (flags.mark_end) {
    cat_flag_e(table);
  }

  if (flags.tab) {
    cat_flag_t(table);
  }

  if (flags.print_non_printable) {
    cat_flag_v(table);
  }

  open_file(argc, argv, flags, table);
}

/**
 * @brief Return values of command line flags
 *
 * @param[in] argc number of command line arguments
 * @param[in] argv command line argument
 * @return flag_t - structure with flag fields
 */
flag_t parcer(int argc, char *argv[]) {
  struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                  {"number", 0, NULL, 'n'},
                                  {"squeeze-blank", 0, NULL, 's'},
                                  {NULL, 0, NULL, 0}};
  int c = getopt_long(argc, argv, "bevEnstT", long_options, NULL);
  flag_t flags = {0};

  for (; c != -1; c = getopt_long(argc, argv, "bevEnstT", long_options, NULL)) {
    flags = process_flag(c, flags);
  }

  return flags;
}

/**
 * @brief Processing the current flag
 *
 * @param[in] c current flag
 * @param[in] flags structure with flag fields
 * @return flag_t
 */
flag_t process_flag(int c, flag_t flags) {
  switch (c) {
    case 'b':
      flags.number_non_blank = true;
      break;
    case 'e':
      flags.mark_end = true;
      flags.print_non_printable = true;
      break;
    case 'v':
      flags.print_non_printable = true;
      break;
    case 'E':
      flags.mark_end = true;
      break;
    case 'n':
      flags.number_all = true;
      break;
    case 's':
      flags.squeeze = true;
      break;
    case 't':
      flags.tab = true;
      flags.print_non_printable = true;
      break;
    case 'T':
      flags.tab = true;
      break;
    default:
      break;
  }

  return flags;
}

/**
 * @brief Return ASCII table
 *
 * @param[out] table
 */
void set_table(const char *table[static 256]) {
  const char *raw_table[] = {
      "\00",  "\01",  "\02",  "\03",  "\04",  "\05",  "\06",  "\07",  "\b",
      "\t",   "\n",   "\v",   "\014", "\r",   "\016", "\017", "\020", "\021",
      "\022", "\023", "\024", "\025", "\026", "\027", "\030", "\031", "\032",
      "\033", "\034", "\035", "\036", "\037", " ",    "!",    "\"",   "#",
      "$",    "%",    "&",    "\'",   "(",    ")",    "*",    "+",    ",",
      "-",    ".",    "/",    "0",    "1",    "2",    "3",    "4",    "5",
      "6",    "7",    "8",    "9",    ":",    ";",    "<",    "=",    ">",
      "?",    "@",    "A",    "B",    "C",    "D",    "E",    "F",    "G",
      "H",    "I",    "J",    "K",    "L",    "M",    "N",    "O",    "P",
      "Q",    "R",    "S",    "T",    "U",    "V",    "W",    "X",    "Y",
      "Z",    "[",    "\\",   "]",    "^",    "_",    "`",    "a",    "b",
      "c",    "d",    "e",    "f",    "g",    "h",    "i",    "j",    "k",
      "l",    "m",    "n",    "o",    "p",    "q",    "r",    "s",    "t",
      "u",    "v",    "w",    "x",    "y",    "z",    "{",    "|",    "}",
      "~",    "\x7f", "\x80", "\x81", "\x82", "\x83", "\x84", "\x85", "\x86",
      "\x87", "\x88", "\x89", "\x8a", "\x8b", "\x8c", "\x8d", "\x8e", "\x8f",
      "\x90", "\x91", "\x92", "\x93", "\x94", "\x95", "\x96", "\x97", "\x98",
      "\x99", "\x9a", "\x9b", "\x9c", "\x9d", "\x9e", "\x9f", "\xa0", "\xa1",
      "\xa2", "\xa3", "\xa4", "\xa5", "\xa6", "\xa7", "\xa8", "\xa9", "\xaa",
      "\xab", "\xac", "\xad", "\xae", "\xaf", "\xb0", "\xb1", "\xb2", "\xb3",
      "\xb4", "\xb5", "\xb6", "\xb7", "\xb8", "\xb9", "\xba", "\xbb", "\xbc",
      "\xbd", "\xbe", "\xbf", "\xc0", "\xc1", "\xc2", "\xc3", "\xc4", "\xc5",
      "\xc6", "\xc7", "\xc8", "\xc9", "\xca", "\xcb", "\xcc", "\xcd", "\xce",
      "\xcf", "\xd0", "\xd1", "\xd2", "\xd3", "\xd4", "\xd5", "\xd6", "\xd7",
      "\xd8", "\xd9", "\xda", "\xdb", "\xdc", "\xdd", "\xde", "\xdf", "\xe0",
      "\xe1", "\xe2", "\xe3", "\xe4", "\xe5", "\xe6", "\xe7", "\xe8", "\xe9",
      "\xea", "\xeb", "\xec", "\xed", "\xee", "\xef", "\xf0", "\xf1", "\xf2",
      "\xf3", "\xf4", "\xf5", "\xf6", "\xf7", "\xf8", "\xf9", "\xfa", "\xfb",
      "\xfc", "\xfd", "\xfe", "\xff",
  };

  memcpy(table, raw_table, sizeof raw_table);
}

/**
 * @brief Flag 'e' processing: replace the character '\n' with "$\n"
 *
 * @param[out] table modified ASCII character table
 */
void cat_flag_e(const char *table[static 256]) { table['\n'] = "$\n"; }

/**
 * @brief Flag 't' processing: replace the character '\t' with "^I"
 *
 * @param[out] table modified ASCII character table
 */
void cat_flag_t(const char *table[static 256]) { table['\t'] = "^I"; }

/**
 * @brief Flag 'v' processing: replace unreadable characters
 *
 * @param[out] table modified ASCII character table
 */
void cat_flag_v(const char *table[static 256]) {
  const char *mini_1[] = {"^@", "^A", "^B", "^C", "^D", "^E", "^F", "^G", "^H"};
  const char *mini_2[] = {"^K", "^L", "^M", "^N",  "^O", "^P", "^Q",
                          "^R", "^S", "^T", "^U",  "^V", "^W", "^X",
                          "^Y", "^Z", "^[", "^\\", "^]", "^^", "^_"};
  const char *mini_3[] = {
      "^?",   "M-^@", "M-^A",  "M-^B", "M-^C", "M-^D", "M-^E", "M-^F", "M-^G",
      "M-^H", "M-^I", "M-^J",  "M-^K", "M-^L", "M-^M", "M-^N", "M-^O", "M-^P",
      "M-^Q", "M-^R", "M-^S",  "M-^T", "M-^U", "M-^V", "M-^W", "M-^X", "M-^Y",
      "M-^Z", "M-^[", "M-^\\", "M-^]", "M-^^", "M-^_", "M- ",  "M-!",  "M-\"",
      "M-#",  "M-$",  "M-%",   "M-&",  "M-'",  "M-(",  "M-)",  "M-*",  "M-+",
      "M-,",  "M--",  "M-.",   "M-/",  "M-0",  "M-1",  "M-2",  "M-3",  "M-4",
      "M-5",  "M-6",  "M-7",   "M-8",  "M-9",  "M-:",  "M-;",  "M-<",  "M-=",
      "M->",  "M-?",  "M-@",   "M-A",  "M-B",  "M-C",  "M-D",  "M-E",  "M-F",
      "M-G",  "M-H",  "M-I",   "M-J",  "M-K",  "M-L",  "M-M",  "M-N",  "M-O",
      "M-P",  "M-Q",  "M-R",   "M-S",  "M-T",  "M-U",  "M-V",  "M-W",  "M-X",
      "M-Y",  "M-Z",  "M-[",   "M-\\", "M-]",  "M-^",  "M-_",  "M-`",  "M-a",
      "M-b",  "M-c",  "M-d",   "M-e",  "M-f",  "M-g",  "M-h",  "M-i",  "M-j",
      "M-k",  "M-l",  "M-m",   "M-n",  "M-o",  "M-p",  "M-q",  "M-r",  "M-s",
      "M-t",  "M-u",  "M-v",   "M-w",  "M-x",  "M-y",  "M-z",  "M-{",  "M-|",
      "M-}",  "M-~",  "M-^?"};
  memcpy(table, mini_1, sizeof mini_1);
  memcpy(&table[9 + 2], mini_2, sizeof mini_2);
  memcpy(&table['~' + 1], mini_3, sizeof mini_3);
}

void open_file(int argc, char *argv[], flag_t flags,
               const char *table[static 256]) {
  flags.is_first_file = true;
  char last_symbol = 0;

  for (char **filename = &argv[0], **lastname = &argv[argc];
       filename != lastname; ++filename) {
    if (**filename == '-' || *filename == argv[0]) {
      continue;
    }

    FILE *file = fopen(*filename, "rb");

    if (errno) {
      fprintf(stderr, "%s: ", argv[0]);
      perror(*filename);
      continue;
    }

    last_symbol = read_file(file, &flags, last_symbol, table);
    fclose(file);
    flags.is_first_file = false;
  }
}

char read_file(FILE *file, flag_t *flags, char last_symbol,
               const char *table[static 256]) {
  int c = 0;
  flags->is_line_break = false;
  flags->symbol_is_read = false;
  int last = '\n';

  while (fread(&c, 1, 1, file) > 0) {
    if (last == '\n') {
      if (flags->squeeze && c == '\n') {
        if (flags->is_line_break) {
          continue;
        }

        flags->is_line_break = true;

        if (flags->mark_end && !flags->symbol_is_read &&
            !flags->is_first_file && !flags->is_line_break) {
          printf("%c", '$');
        }

      } else {
        flags->is_line_break = false;
      }

      if (flags->number_all && !flags->number_non_blank) {
        if (flags->is_first_file) {
          printf("%6i\t", ++flags->line_cnt);
        }

        if (!flags->is_first_file && !flags->symbol_is_read && c == '\n' &&
            last_symbol == '\n') {
          printf("%6i\t", ++flags->line_cnt);
        }

        if (!flags->is_first_file && flags->symbol_is_read) {
          printf("%6i\t", ++flags->line_cnt);
        }
      } else if (flags->number_non_blank && c != '\n') {
        if (flags->is_first_file) {
          printf("%6i\t", ++flags->line_cnt);
        }

        if (!flags->is_first_file && flags->symbol_is_read) {
          printf("%6i\t", ++flags->line_cnt);
        }
      }
    }

    if (c == '\0' && !flags->print_non_printable) {
      printf("%c", c);
    }

    printf("%s", table[c]);
    last = c;
    flags->symbol_is_read = true;
  }
  return last;
}
