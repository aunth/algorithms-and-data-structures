
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char *value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    unsigned int length;
} LinkedList;

LinkedList *get_list()
{
    LinkedList *lst = (LinkedList *) malloc(sizeof(LinkedList));
    lst->head = NULL;
    lst->length = 0;
    lst->tail = NULL;
    return lst;
}

Node *get_node(char *value)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void print_linked_list(LinkedList *lst)
{
    Node *ptr = lst->head;
    while (ptr->next != NULL)
    {
        printf("%s -> ", ptr->value);
        ptr = ptr->next;
    }
    printf("%s -> NULL\n", ptr->value);
}

void append_node(LinkedList *lst, Node *node)
{
    if (lst->head == NULL)
    {
        node->prev = NULL;
        lst->head = node;
        lst->tail = lst->head;
    }
    else
    {
        node->prev = lst->tail;
        lst->tail->next = node;
        lst->tail = node;
    }
    lst->length++;
}

Node *find_node(LinkedList *lst, int index)
{
    if (index >= lst->length || index < 0)
        return NULL;
    int i = 0;
    Node *current = lst->head;
    while (i != index)
    {
        i++;
        current = current->next;
    }
    return current;
}

void insert(LinkedList *lst, Node *node, int index)
{
    int i = 1;
    if (index == 0)
    {
        node->prev = NULL;
        node->next = lst->head;
        lst->head->prev = node;
        lst->head = node;
        lst->length++;
        return ;
    }
    else if (index >= lst->length)
    {
        append_node(lst, node);
        return ;
    }    
    Node *ptr = lst->head;
    while (i < index)
    {
        ptr = ptr->next;
        i++;
    }
    node->next = ptr->next; // current element with index - index(ptr->next) should be after node which we want to add
    node->prev = ptr; 
    ptr->next = node;
    node->next->prev = node; // element which was on posision index(ptr->next) should have prev field as a node which we want to add
    lst->length++;
}

void delete_node(LinkedList *lst, int index)
{
    if (lst->head == NULL)
        return ;
    else if (index >= lst->length || index < 0)
        return ;
    else if (index == 0)
    {
        Node *current_head = lst->head->next;
        lst->head = current_head;
        current_head->prev->next = NULL;
        return ;
    }
    else if (index == lst->length-1)
    {
        lst->tail->prev->next = NULL;
        lst->tail = lst->tail->prev;
        lst->length--;
        return ;        
    }
    int i = 1;
    Node *prev = lst->head;
    Node *curr = lst->head->next;
    while (i < index)
    {
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (i == lst->length - 2) 
        lst->tail = prev;
    curr->next->prev = curr->prev;
    prev->next = curr->next;
    lst->length--;
}

void free_list(LinkedList *lst) {
    Node *current = lst->head;
    Node *next;
    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(lst);
}

int main(void)
{
    LinkedList *lst = get_list();
    Node *a = get_node("Hello");
    Node *b = get_node("World");
    Node *k = get_node("H");
    append_node(lst, a);
    append_node(lst, b);
    Node *c = get_node("A");
    append_node(lst, c);
    print_linked_list(lst);
    Node d = {"B", NULL, NULL};   
    insert(lst, &d, 1);
    print_linked_list(lst);
    int i = 0;
    print_linked_list(lst);
    insert(lst, k, 2);
    print_linked_list(lst);
    while (i < lst->length)
    {
        printf("%d\n", i);
        Node *current = find_node(lst, i);
        if (current->prev != NULL)
            printf("Prev : %s\n", current->prev->value);
        else
            printf("Prev is NULL\n");
        if (current->next != NULL)
            printf("Next : %s\n", current->next->value);
        else
            printf("Next is NULL\n");
        i++;
    }
}