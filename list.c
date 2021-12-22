#include <stdlib.h>

/** LINKED LIST
 * =============
 */

typedef struct {
    int data;
    struct listnode *next;
} listnode;


struct listnode *listcreate(int data) {
    listnode *newnode;

    newnode = (listnode *) malloc(sizeof(listnode));
    if (newnode == NULL) return NULL;

    newnode->data = data;
    newnode->next = NULL

    return newnode;
}