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
  list->current = list->head;
  return list->current;
}

void * nextList(List * list) 
{
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) 
{
  Node* elemento = firstList(list);

  while(elemento != NULL)
    {
      list->current = nextList(list);
    }
  return list->current->data;
}

void * prevList(List * list) 
{
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) 
{
  Node* newNode = (Node*)malloc(sizeof(Node*));
  newNode->data = data;
  newNode->next = list->head;
  list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
  Node* newNode = (Node*)malloc(sizeof(Node*));
  newNode->data = data;
  newNode->next = list->current->next;
  list->current->next = newNode;
  newNode->prev = list->current;
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
  Node* elemento = firstList(list);
  void* dato = list->current->data;

  while(elemento != NULL)
    {
      if(elemento->data == list->current->data)
      {
        elemento->prev->next = elemento->next;
        break;
      }
      elemento = nextList(list);
    }
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}