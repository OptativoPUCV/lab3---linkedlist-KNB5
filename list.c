#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List * list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;

  return list;
}

void * firstList(List * list) 
{
  if(list-> head == NULL) return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) 
{
  if(list->current == NULL || list->current->next == NULL) return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) 
{
  if(list->head == NULL) return NULL;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) 
{
  if(list->current == NULL || list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) 
{
  Node* newNode = createNode(data);
  
  if(list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else
  {
    newNode->next = list->head;
    list->head = newNode;
  }
}

void pushBack(List * list, void * data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
  Node* newNode = createNode(data);

  if(list->current != NULL)
  {
    newNode->prev = list->current;
    newNode->next = list->current->next;
    list->current->next = newNode;
  }
  else
  {
    list->head = newNode;
    list->tail = newNode;
  }
  
  if(newNode->next == NULL)
  {
    list->tail = newNode;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
 if(list->current == NULL || (list->current->prev == NULL && list->current->next == NULL)) return NULL;

  Node* aux = list->current;

  if(aux->next == NULL)
  {
    prevList(list);
    list->tail = list->current;
    list->tail->next = NULL;
  }
  else if(aux->prev == NULL)
  {
    nextList(list);
    list->head = list->current;
    list->head->next = list->current->next;
    list->head->prev = NULL;
  }
  else
  {
    prevList(list);
    list->current->next = aux->next;
    nextList(list);
    list->current->prev = aux->prev;
  }
  return aux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}