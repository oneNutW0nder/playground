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

// Destroys the entire 'list' given the 'Entry'; free all memory for each node
// and set all pointers to NULL
//
// @parma list -> The 'Entry' for a given list that needs to be destoryed
void destroy_list(Entry *list) {
  if (!list) {
    printf("[+] Nothing to cleanup!");
    return;
  }
  // List nodes do not exist
  if (!list->next) {
    free(list);
  }

  // 'victim' will be the currently selected node
  Node* victim = list->next;

  // Now that we have entered the 'list', we can free it
  list->next = NULL;
  free(list);

  // Traverse and free along the way
  while (victim->next != NULL){
    // Use 'tmp' to cleanup current node and walk 'victim' forward
    Node* tmp = victim;
    victim = victim->next;    

    // Free 'data' and set pointer to NULL then free the 'Node'
    // free(tmp->data);
    tmp->next = NULL;
    tmp->data = NULL;
    free(tmp);
  }

  // Do the final node
  // free(victim->data);
  victim->next = NULL;
  victim->data = NULL;
  free(victim);

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

  // Link the 'Entry'
  list->next = one;

  return list;
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

// Simple test to check structures, data, memory management, and printing
void test_simple() {
  printf("============================\n");
  printf("[+] Creating, printing, and destorying...\n");
  Entry *list = make_simple_list();
  print_list(list);
  destroy_list(list);
  printf("============================\n");
}

// Test appending a new node to the list
void test_append() {
  printf("============================\n");
  printf("[+] Appending from an 'Entry'...\n");

  Entry* list_one = make_simple_list();
  Node* new_one = make_new_node("I am the new node!");
  append((Node*)list_one, new_one);

  print_list(list_one);
  destroy_list(list_one);
  printf("[+] Appending from an 'Entry' complete!\n");
  printf("============================\n");


  printf("============================\n");
  printf("[+] Appending to list with starting point in the middle...\n");
  Entry* list_two = make_simple_list();
  Node* new_two = make_new_node("I am the new node!");
  append(list_two->next->next, new_two);

  print_list(list_two);
  destroy_list(list_two);

  printf("[+] Appending from starting point in the middle complete!\n");
  printf("============================\n");

}

// Basic test to append a new node to the end of an existing list
void append_test() {}

int main(int argc, char *argv[]) {
  test_simple();
  test_append();

  return 0;
}
