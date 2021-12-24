/**
 * LINKED LIST
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct listnode {
    char* data;
    struct listnode* next;
};

struct linkedlist {
    struct listnode* head;
    struct listnode* tail;
};

struct linkedlist listcreate() {
    struct linkedlist newlist;

    newlist.head = NULL;
    newlist.tail = NULL;

    return newlist;
}

void listadd(struct linkedlist** list, char* data) {
    struct listnode* newnode;
    char* newdata;
    int datasize = 0;

    datasize = strnlen(data, 255);
    if (datasize == 255) newdata[255] = '\0';

    newnode = (struct listnode*) malloc(sizeof(struct listnode));
    newdata = (char*) malloc(sizeof(char) * datasize);
    strncpy(newdata, data, datasize);
    newnode->data = newdata;
    newnode->next = NULL;

    if ((*list)->tail == NULL) {
        (*list)->head = newnode;
        (*list)->tail = newnode;
    } else {
        ((*list)->tail)->next = newnode;
        (*list)->tail = newnode;
    }
}

void listremove(struct linkedlist** list, struct listnode** beforerm, struct listnode** remove) {
    // First node in the list
    if ((*list)->head == *remove) {
        (*list)->head = (*remove)->next;
    } else {
        // If not, then it must have a node before
        (*beforerm)->next = (*remove)->next;
    }

    // Readjust tail if needed
    if (*remove == (*list)->tail) {
        (*list)->tail = (*beforerm);
    }

    free(*remove);
    *remove = NULL;
}

void listprint(struct linkedlist* list, char* comment) {
    struct listnode* lptr;

    printf("%s\nLIST %p\n", comment, list);

    lptr = list->head;
    while (lptr !=NULL) {
        printf("  |-- NODE (%p) = %s\n", lptr, lptr->data);
        lptr = lptr->next;
    }
}

int main() {
    struct linkedlist list = listcreate();
    struct linkedlist* listptr = &list;

    listadd(&listptr, "ELEMENT 1");
    listadd(&listptr, "ELEMENT 2");
    listadd(&listptr, "ELEMENT 3");
    listadd(&listptr, "ELEMENT 4");

    listprint(listptr, "");
}
