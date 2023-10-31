#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

//////
// To have:
// - node struct
// - datatype selection method
// - func menu
// - func pop
// - func push
// - func peek
// - func is empty
// - func is full
// ------------------
// requirements:
// - (malloc & free) allocate * free the list
// - any datatype in list
// - push/pop: manage memmory
// - manage errors (ex. pop on empty stack)
// - testing. handle various cases gracefully
//////

typedef enum type_t { of_int, of_float, of_char, of_string } type_t;

typedef struct node_t {
  type_t type;
  void *data;
  struct node_t *next;
} node_t;

typedef struct stack_t {
  node_t *node;
  uint size;
  uint nnum;
} stack_t;

void print_node(node_t *node) {
  void *p = node->data;

  printf("p->data: ");
  switch (node->type) {
  case of_int: {
    printf("%i\n", *(int *)p);
    break;
  }
  case of_float: {
    printf("%f\n", *(float *)p);
    break;
  }
  case of_char: {
    printf("%c\n", *(char *)p);
    break;
  }
  case of_string: {
    printf("%s\n", (char *)p);
    break;
  }
  }
}

void free_node(node_t *node) {
  if (node != NULL)
    free(node);
}

void *alloc_data_of(type_t type) {
  switch (type) {
  case of_int:
    return malloc(sizeof(int));
  case of_float:
    return malloc(sizeof(float));
  case of_char:
    return malloc(sizeof(char));
  case of_string:
    return malloc(sizeof(char) * 256);
  }
}

node_t *init_node(type_t type) {
  node_t *node;

  node = malloc(sizeof(node_t));
  if (node == NULL)
    return NULL;
  node->type = type;
  node->data = alloc_data_of(type);
  node->next = NULL;
  return node;
}

void copy_data(void *dest, void *source, type_t type) {
  ulong size;
  switch (type) {
  case of_int: {
    size = sizeof(int);
    break;
  }
  case of_float: {
    size = sizeof(float);
    break;
  }
  case of_char: {
    size = sizeof(char);
    break;
  }
  case of_string: {
    size = sizeof(char) * 256;
    break;
  }
  }
  memcpy(dest, source, size);
}

void stack_status(stack_t *stack) {
  printf("---------------\n"
         "stack size: %u\n"
         "used: %u\n"
         "free: %u\n"
         "---------------\n",
         stack->size, stack->nnum, stack->size - stack->nnum);
}

int push(stack_t *stack, void *data, type_t type) {
  node_t *to_add = init_node(type);
  if (to_add == NULL) {
    free(to_add);
    printf("no space left for allocating\n");
    return 0;
  }
  if (stack->size == stack->nnum) {
    printf("stack is full\n");
    return 0;
  }
  //// to_add->data = data;
  copy_data(to_add->data, data, type);
  to_add->next = stack->node;
  stack->node = to_add;
  stack->nnum++;
  return 1;
}

int readln(char *data) {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
  putc(c, stdin);
  fgets(data, 256, stdin);
  if (strlen(data) == 1)
    return 0;
  data[strlen(data) - 1] = '\0';
  return 1;
}

node_t *pop(stack_t *stack) {
  node_t *to_remove = stack->node;
  if (stack->node == NULL)
    return NULL;
  stack->node = stack->node->next;
  return to_remove;
}

void handle_push(stack_t *stack) {
  char t;
  char buff[256];
  int r;

  if (stack->size == stack->nnum) {
    printf("stack is full\n");
    return;
  }
  printf("choose type:\n"
         "(i)nteger\n"
         "(f)loat\n"
         "(c)har\n"
         "(s)tring\n"
         "type: ");
  scanf("%s", &t);
  printf("data: ");
  readln(buff);
  if (buff[0] == '\n')
    r = 0;
  else
    switch (t) {
    case 'i': {
      int data;
      // scanf("%i", &data);
      r = sscanf(buff, "%i", &data);
      if (r)
        r = push(stack, &data, of_int);
      break;
    }
    case 'f': {
      float data;
      r = sscanf(buff, "%f", &data);
      if (r)
        r = push(stack, &data, of_float);
      break;
    }
    case 'c': {
      char data;
      r = sscanf(buff, "%s", &data);
      if (r)
        r = push(stack, &data, of_char);
      break;
    }
    case 's': {
      if (r)
        r = push(stack, buff, of_string);
      break;
    }
    }

  if (r)
    printf("pushed element successfully\n");
  else
    printf("failed to push\n");
}

void handle_pop(stack_t *stack) {
  node_t *n = pop(stack);
  if (n != NULL) {
    printf("popped element successfully\n");
    print_node(n);
    free(n->data);
    free(n);
  } else
    printf("stack is empty\n");
}

void repl(stack_t *stack) {
  char o;
  int sz;
  while (stack->size <= 0) {
    printf("enter size of stack: ");
    scanf("%u", &sz);
    if (sz <= 0)
      printf("size should be positive\n");
    else
      stack->size = sz;
  }
  printf("type `h` for help\n");
  while (1) {
    printf("-> ");
    scanf("%s", &o);
    switch (o) {
    case 'h': {
      printf("`h`: display this message\n"
             "`+`: push an item\n"
             "`-`: pop and display the top item\n"
             "`p`: peek at the top item\n"
             "`e`: check if empty\n"
             "`f`: check if full\n"
             "`!`: exit\n");
      break;
    }
    case '+': {
      handle_push(stack);
      stack_status(stack);
      break;
    }
    case '-': {
      handle_pop(stack);
      stack_status(stack);
      break;
    }
    case 'p': {
      if (stack->node == NULL)
        printf("stack is empty\n");
      else
        print_node(stack->node);
      break;
    }
    case 'e': {
      printf("stack is ");
      if (stack->node == NULL)
        printf("empty\n");
      else
        printf("not empty\n");
      break;
    }
    case 'f': {
      printf("stack is ");
      if (stack->size == stack->nnum)
        printf("full\n");
      else
        printf("not full\n");
      break;
    }
    case '!':
      return;
    }
  }
}

int main() {

  stack_t *stack;
  stack = malloc(sizeof(stack_t));
  stack->node = NULL;

  stack->size = 0;

  repl(stack);

  node_t *n;
  while ((n = pop(stack)) != NULL) {
    // print_node(n);
    free(n->data);
    free(n);
  }

  // free(n->data);
  free(n);
  free(stack);

  return EXIT_SUCCESS;
}
