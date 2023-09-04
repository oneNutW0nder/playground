#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

typedef struct Entry {
  Node *next;
  int listid;
} Entry;

void fail(char *msg, int code) {
  printf("%s\n", msg);
  exit(code);
}

// @param node -> Pointer to any node in the linked list
// @param victim -> The node to be appended
void append(Node *node, Node *victim) {
  if (!node) {
    fail("[!] Node passed to 'append()' was null\n", 1);
  }

  // Traverse list
  while (node->next != NULL) {
    node = node->next;
  }

  // Append 'victim'
  node->next = victim;
}

// Node *pop(Node *node) {}
// void cleanup() {}

// @param entry -> Entry point to the list so we can print everything
void print_list(Entry *entry) {
  // Sanity checks
  if (!entry && !entry->next) {
    fail("[!] Node passed to 'print_list()' was null\n", 1);
  }

  // If we have at least 1 entry "enter" the list
  Node *node = entry->next;

  // Iterate and print with some subpar formatting
  int count = 0;
  while (node->next != NULL) {
    count += 1;
    printf("#%d\t &%p\t&%p\t%s\n", count, node, node->next, (char *)node->data);
    node = node->next;
  }

  // Final print for last node
  count += 1;
  printf("#%d\t &%p\t&%p\t%s\n", count, node, node->next, (char *)node->data);
}

// Simple test to check structure integrity and printing
void simple_test() {
  // Make my list
  Entry list;
  list.next = NULL;
  list.listid = 1;

  // Construct some nodes
  Node one = {NULL, "I am node 1"};
  Node two = {NULL, "I am node 2"};
  Node three = {NULL, "I am node 3"};
  Node four = {NULL, "I am node 4"};

  // Create proper list
  one.next = &two;
  two.next = &three;
  three.next = &four;

  // Setup entry
  list.next = &one;

  // Test!
  print_list(&list);
}

int main(int argc, char *argv[]) {
  simple_test();
  return 0;
}
