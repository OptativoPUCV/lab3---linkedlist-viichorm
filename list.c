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


List * createList() {
    List *lista = (List *) malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}


void * firstList(List * list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }

    list->current = list->head;
    return (void *)list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) {
        return NULL;
    }

    list->current = list->current->next;
    return (void *)list->current->data;
}


void * lastList(List * list) {
    if (list == NULL || list->tail == NULL)
    {
        return NULL;
    }
    list->current = list->tail;
    return (void *)list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL){
      return NULL;
    }
    list->current = list->current->prev;
    return (void *)list->current->data;
}


void pushFront(List * list, void * data) {
    Node * newNode = createNode(data);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

void pushCurrent(List * list, void * data) {
    Node * newNode = createNode(data);

    if (list->current == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->current = newNode;
    } else {
        newNode->prev = list->current;
        newNode->next = list->current->next;
        if (list->current->next != NULL) {
            list->current->next->prev = newNode;
        } else {
            list->tail = newNode;
        }
        list->current->next = newNode;
        list->current = newNode;
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
void * popCurrent(List * list) {
    if (list->current == NULL) {
        return NULL;
    }
    void * data = list->current->data;
    Node *nodeToRemove = list->current;
    if (list->current->prev != NULL) {
        list->current->prev->next = list->current->next;
    } else {
        list->head = list->current->next;
    }
    if (list->current->next != NULL) {
        list->current->next->prev = list->current->prev;
    } else {
        list->tail = list->current->prev;
    }
    list->current = list->current->next;
    free(nodeToRemove);

    return data;
}
void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}