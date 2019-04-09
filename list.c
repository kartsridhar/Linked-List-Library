// Program to create a reusable library module for doubly linked lists
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef int item;

// The list type is opaque (declared here, and defined in list.c).
struct list;
typedef struct list list;

// Creating a new structure node
struct node {
  item val;
  struct node *next;
  struct node *prev;
};

typedef struct node node;

// Creating a new structure list
struct list {
  node *left;
  node *current;
  node *right;
};
//-------------------------------------FUNCTIONS-------------------------------------------------

// The fail function. To return an error message when the operation performed is illegal
void fail(char *message){
  printf("%s\n", message);
  exit(1);
}

// Initializing a new empty list
list *newList() {
  list *l = malloc(sizeof(list));
  l->left = malloc(sizeof(node));
  l->right = malloc(sizeof(node));
  l->left->next = l->right;
  l->right->prev = l->left;

  l->current = l->left->next;

  return l;
}

// To set the current position to the first item
void start(list *l){
  l->current = l->left->next;
}

// To set the current position to the last item
void end(list *l){
  l->current = l->right;
}

// To check whether the current position is at the beginningcom
bool atStart(list *l){
  return (l->current == l->left->next);
}

// To check whether the current position is at the end
bool atEnd(list *l){
  return (l->current == l->right);
}

// To move the current position forward by 1
void forward(list *l){
  if(atEnd(l))
    fail("Error! You can't move the last position forward! \n");
  else
    l->current = l->current->next;
}

// To move the current position backward by 1
void backward(list *l){
  if(atStart(l))
    fail("Error! You can't move the first position backward! \n");
  else
    l->current = l->current->prev;
}

// To insert an item before the current position
void insertBefore(list *l, item x){
  node *insert_new = malloc(sizeof(node));
  *insert_new = (node) { l->current->prev, x, l->current };
  l->current->prev->next = insert_new;
  l->current->prev = insert_new;
}

// To insert an item after the current position
void insertAfter(list *l, item x){
  insertBefore(l, x);
  l->current->prev = l->current->prev;
}

// To get the item before the current position
item getBefore(list *l){
  if(atStart(l))
    fail("Error! You can't get the item before the first position! \n");
  return l->current->prev->val;
}

// To get the item after the current position
item getAfter(list *l){
  if(atEnd(l))
    fail("Error! You can't get the item after the last position! \n");
  return l->current->val;
}

// To set the item value before the current position
void setBefore(list *l, item x){
  if(!atStart(l))
     l->current->prev->val = x;
  else
    fail("Error! You can't set the item before the first position! \n");
}

// To set the item value after the current position
void setAfter(list *l, item x){
  if(!atEnd(l))
     l->current->val = x;
  else
    fail("Error! You can't set the item after the last position! \n");
}

// To delete an item before the current position
void deleteBefore(list *l){
  if(atStart(l))
    fail("Error! You can't delete the item before the first position! \n");
  l->current->prev->prev->next = l->current;
  node *save = l->current->prev;
  l->current->prev = l->current->prev->prev;
  free(save);
}

// To delete an item after the current position
void deleteAfter(list *l){
  if(atEnd(l))
    fail("Error! You can't delete the item after the last position! \n");
  l->current->prev->next = l->current->next;
  l->current->next->prev = l->current->prev;
  node *save = l->current;
  l->current = l->current->next;
  free(save);
}

// ----------------------------------------TESTING------------------------------------------

// Check the entire structure of the list.
static bool test(list *l, char *pic) {
    node *pos = l->left->next;
    if (pos->prev != l->left) return false;
    for (int i = 0; i < strlen(pic); i++) {
        char ch = pic[i];
        if (ch == '|') {
            if (l->current != pos) return false;
        }
        else {
            if (pos->val != (ch - '0')) return false;
            if (pos->next->prev != pos) return false;
            pos = pos->next;
        }
    }
    if (pos != l->right) return false;
    return true;
}

int main() {
    list *l = newList();
    assert(test(l, "|"));
    insertBefore(l, 3);
    assert(test(l, "3|"));
    insertAfter(l, 7);
    assert(test(l, "3|7"));
    deleteBefore(l);
    assert(test(l, "|7"));
    printf("All tests pass\n");
    return 0;
}
