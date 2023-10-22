#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// should have the functions to:
//   [x] append text
//   [x] clear the buffer
//   [x] search words
//   [x] replace words
//   [x] handle files
//   DONE

const char *DELIM = " ,.!:;?\n\t\r";

typedef struct buffer {
  size_t size;
  size_t pos;
  char *dat;

} buffer;

void realloc_buff(buffer *buff, float scale) {
  char *tmp;
  buff->size *= scale;
  tmp = realloc(buff->dat, sizeof(char) * buff->size);
  if (tmp)
    buff->dat = tmp;
  else {
    printf("not all text was read, realloc error\n");
    return;
  }
}

void clear_buff(buffer *buff) {
  free(buff->dat);
  buff->size = 2;
  buff->pos = 0;
  buff->dat = malloc(buff->size * sizeof(char));
}

void display_buff(buffer *buff) {
  if (buff->pos > 0)
    printf("%s\n", buff->dat);
  else
    printf("buffer is empty!\n");
}

int search_n_count(char *word, buffer *buff) {
  int n = 0;
  char newstr[buff->size];
  strcpy(newstr, buff->dat);
  char *token = strtok(newstr, DELIM);
  while (token) {
    if (strcmp(token, word) == 0) {
      n++;
    }
    token = strtok(NULL, DELIM);
  }
  return n;
}

int has_delim(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    for (int j = 0; DELIM[j] != '\0'; j++) {
      if (str[i] == DELIM[j]) {
        return 1;
      }
    }
  }
  return 0;
}

void substitute_word_in_buff(char *in, char *re, buffer *buff) {
  char *token = strdup("");
  char *str = strdup(buff->dat);
  buffer newbuff;
  newbuff.size = buff->size;
  newbuff.dat = calloc(buff->size, sizeof(char));
  // realloc_buff(&newbuff, 1.5);

  int n = 0;
  // str[n] != '\0'
  while (n <= strlen(str)) {
    // printf("n: %i\n", n);
    // if (n == strlen(str))
    //   printf("could handle: %s\n", token);
    if (NULL != strchr(DELIM, str[n])) {
      if (token[0] != '\0') {
        if (strcmp(token, in) == 0) {
          if (sizeof(re) >= sizeof(in)) {
            realloc_buff(&newbuff, 1.5);
          }
          strcat(newbuff.dat, re);
        } else
          strcat(newbuff.dat, token);
        // printf("%s\n", token);
        token = strdup("");
      }
      strncat(newbuff.dat, &str[n], 1);
      // printf("delim->%i\n", n);
    } else
      strncat(token, &str[n], 1);
    n++;
  }
  // strncat(newstr, "", 1);
  // printf("newbuff-> %s\n", newbuff.dat);
  // printf("str-> %s\n", str);
  // printf("loose token-> %s\n", token);
  // printf("n: %i, str: %i\n", n, (int)strlen(str));
  buff->dat = newbuff.dat;
  buff->size = newbuff.size;
  buff->pos = strlen(newbuff.dat);
  free(token);
  free(str);
}

void read_to_buff(buffer *buff, FILE *fd) {
  char c;

  int i = buff->pos;

  while ((c = getc(fd)) != EOF) {
    if (buff->size == i) {
      realloc_buff(buff, 1.5);
    }
    if (i != 0 || c != '\n') {
      buff->dat[i] = c;
      i++;
    }
  }
  if (buff->dat[i - 1] == '\n')
    i--;

  buff->dat[i] = '\0';
  buff->pos = i;
}

void read_from_file_to_buff(char *path, buffer *buff) {
  FILE *f = fopen(path, "r");
  if (f && !ferror(f)) {
    read_to_buff(buff, f);
    fclose(f);
  } else {
    perror("Error");
  }
}

void write_from_buff_to_file(char *path, buffer *buff) {
  FILE *f = fopen(path, "w");
  if (f && !ferror(f)) {
    fwrite(buff->dat, 1, (strlen(buff->dat)), f);
    fclose(f);
  } else
    perror("Error");
}

void repl(buffer *buff) {
  char opt;
  printf("type `h` for help message\n");
  while (1) {
    if (feof(stdin)) {
      printf("\n");
      ungetc(' ', stdin);
      opt = getc(stdin);
    } else {
      printf("-> ");
      scanf("%s", &opt);
    }
    // opt = getc(stdin);
    switch (opt) {
    case 'h': {
      printf("h - prints this message\n"
             "l - clear console\n"
             "d - display text in buffer\n"
             "i - insert text and append to buffer\n"
             "s - substitute all occurrences of a word\n"
             "c - count all occurances of a word\n"
             "w - write from buffer to file\n"
             "r - read from file and append to buffer\n"
             "z - clear buffer\n"
             "! - end session\n");
      break;
    }
    case 'l': {
      printf("\e[1;1H\e[2J");
      break;
    }
    case 'd': {
      display_buff(buff);
      break;
    }
    case 'i': {
      printf("insert text to append:\n");
      read_to_buff(buff, stdin);
      break;
    }
    case 's': {
      char in[256];
      char re[256];
      printf("insert word to substitute as `old <space> new`: ");
      scanf("%s", in);
      scanf("%s", re);
      if (has_delim(in) || has_delim(re)) {
        printf("one or both words are invalid\n");
        break;
      }
      substitute_word_in_buff(in, re, buff);
      break;
    }
    case 'c': {
      printf("search term: ");
      char word[256];
      scanf("%s", word);
      int n = search_n_count(word, buff);
      printf("%i occurances of %s\n", n, word);
      break;
    }
    case 'w': {
      char p[256];
      printf("file to write to: ");
      scanf("%s", p);
      write_from_buff_to_file(p, buff);
      break;
    }
    case 'r': {
      char p[256];
      printf("file to read from: ");
      scanf("%s", p);
      read_from_file_to_buff(p, buff);
      break;
    }
    case 'z': {
      clear_buff(buff);
      printf("buffer cleared!\n");
      break;
    }
    case '!': {
      char o;
      printf("are you sure? it is recommended to save the buffer to a file "
             "before exiting (y/n): ");
      scanf("%s", &o);
      switch (o) {
      case 'y':
        exit(EXIT_SUCCESS);
      default:
        break;
      }
    }
    }
  }
}
int main() {

  buffer buff;
  buff.size = 2;
  buff.pos = 0;
  buff.dat = malloc(sizeof(char) * buff.size);

  repl(&buff);

  free(buff.dat);
  return 0;
}
