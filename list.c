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

int listlen(struct listnode* head) {
    struct listnode* lp;
    int count = 0;

    lp = head;
    while (lp != NULL) {
        count++;
        lp = lp->next;
    }

    return count;
}

void listpush(struct listnode** head, char* data) {
    struct listnode* newnode = (struct listnode*) malloc(sizeof(struct listnode));
    char* newdata;
    int datasize = 0;

    // figure out the len of the data, cap it at 256
    datasize = strnlen(data, 256);
    if (datasize == 256) newdata[255] = '\0';

    newdata = (char*) malloc(sizeof(char) * datasize);
    strncpy(newdata, data, datasize);
    newnode->data = newdata;

    newnode->next = *head;
    *head = newnode;
}

void listappend(struct listnode** tail, char* data) {
    struct listnode* newnode = (struct listnode*) malloc(sizeof(struct listnode));
    char* newdata;
    int datasize = 0;

    // figure out the len of the data, cap it at 256
    datasize = strnlen(data, 256);
    if (datasize == 256) newdata[255] = '\0';

    newdata = (char*) malloc(sizeof(char) * datasize);
    strncpy(newdata, data, datasize);
    newnode->data = newdata;
    newnode->next = NULL;

    if (*tail != NULL) {
        (*tail)->next = newnode;
    }
    *tail = newnode;
}

void listprint(struct listnode* head, char* comment) {
    struct listnode* lptr;
    int index = 0;

    printf("%s\nLINKED LIST %p\n", comment, head);

    lptr = head;
    while (lptr !=NULL) {
        printf("  |-- [%05d] NODE (%p) = %s\n", index, lptr, lptr->data);
        lptr = lptr->next;
        index++;
    }
}
