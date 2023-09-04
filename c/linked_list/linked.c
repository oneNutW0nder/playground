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

// Helper error function to keep 'if' checks shorter
//
// @param msg -> Error message to display
// @param code -> Exit code that should be used
void fail(char *msg, int code) {
  printf("%s\n", msg);
  exit(code);
}

// Appends a given 'victim' to the end of the list starting at 'node'
//
// @param node -> Pointer to any node in the linked list
// @param victim -> The node to be appended
void append(Node *node, Node *victim) {
  if (!node) {
    fail("[!] Node passed to 'append()' was null\n", 1);
  }
  if (!victim) {
    fail("[!] Victim passed to 'append()' was null\n", 1);
  }

  // Traverse list
  while (node->next != NULL) {
    node = node->next;
  }

  // Append 'victim'
  node->next = victim;
}

// Prints the list along with identifying information given a valid 'Entry'
//
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

// Create a new node containing 'data' and return the pointer to it
//
// @param data -> A pointer to the data to contain in the 'Node'
Node *make_new_node(void *data) {
  Node *node = malloc(sizeof(Node));
  node->next = NULL;
  node->data = data;

  return node;
}

//
// Return a pointer to an 'Entry' which gives access to a list with 4 nodes
Entry *make_simple_list() {
  // Create the 'Entry' for our list
  Entry *list = malloc(sizeof(Entry));
  list->next = NULL;
  list->listid = 1;

  // Create nodes
  Node *one = make_new_node("I am node 1");
  Node *two = make_new_node("I am node 2");
  Node *three = make_new_node("I am node 3");
  Node *four = make_new_node("I am node 4");

  // Link the list
  one->next = two;
  two->next = three;
  three->next = four;
  four->next = NULL;

  return list;
}

// Simple test to check structure integrity and printing
void simple_test() {
  // Make my list
  Entry list = {NULL, 1};

  // Construct some nodes
  Node one = {NULL, "I am node 1"};
  Node two = {NULL, "I am node 2"};
  Node three = {NULL, "I am node 3"};
  Node four = {NULL, "I am node 4"};

  // link the list
  one.next = &two;
  two.next = &three;
  three.next = &four;

  // Setup entry
  list.next = &one;

  // Test!
  print_list(&list);
}

// Basic test to append a new node to the end of an existing list
void append_test() {}

int main(int argc, char *argv[]) {
  simple_test();
  return 0;
}
