#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include<stdbool.h>



typedef struct Element{
    char data;
    int num;
    struct Element* left;
    struct Element* right;
}element;



typedef struct ListNode {
    element node;
    struct ListNode* link;
}listnode;

typedef struct {
    listnode* head;
} LinkedList_h;

LinkedList_h* createLinkedList_h(void)
{
    LinkedList_h* L;
    L = (LinkedList_h*)malloc(sizeof(LinkedList_h));
    L->head = NULL;
    return L;
}

void freeLinkedList_h(LinkedList_h* L)
{
    listnode* p;
    while (L->head != NULL)
    {
        p = L->head;
        L->head = L->head->link;
        free(p);
        p = NULL;
    }
}

void printList(LinkedList_h* L)
{
    listnode* p;
    printf("L=<<");
    p = L->head;
    while (p != NULL)
    {
        printf("%c", p->node.data);
        p = p->link;
        if (p != NULL)printf(",");
    }
    printf(">> \n");

}


void insertFirstnode(LinkedList_h* L, char x)
{
    listnode* newNode=(listnode*)malloc(sizeof(listnode));
    newNode->node.data = x;
    newNode->link = L->head;
    L->head = newNode;
    newNode->node.num = 0;
}



void insertMiddleNode(LinkedList_h* L, listnode* pre, char x)
{

    listnode* newNode=NULL;
    newNode = (listnode*)malloc(sizeof(listnode));
    newNode->node.data = x;
    if (L == NULL)
    {
        newNode->link = NULL;
        L->head = newNode;
    }
    else if (pre == NULL)
    {
        L->head = newNode;
    }
    else
    {
        newNode->link = pre->link;
        pre->link = newNode;
    }
    newNode->node.num = 0;
}



void insertLastNode(LinkedList_h* L, char x)
{
    listnode* newNode= (listnode*)malloc(sizeof(listnode));
    listnode* temp=NULL;
    
    newNode->node.data = x;
    newNode->link = NULL;
    if (L->head == NULL)
    {
        newNode->link = NULL;
        return;
    }

    temp = L->head;
    while (temp->link != NULL) temp = temp->link;
    temp->link = newNode;
    newNode->node.num = 0;
    newNode->node.left = NULL;
    newNode->node.right = NULL;
}


void deletNode(LinkedList_h* L, listnode* p)
{
    listnode* pre;
    if (L->head == NULL) return;
    if (L->head->link == NULL)
    {
        free(L->head);
        L->head = NULL;
        return;
    }

    else if (p == NULL) return;
    else
    {
        pre = L->head;
        while (pre->link != p)
        {
            pre = pre->link;
        }
        pre->link = p->link;
        free(p);

    }
}

listnode* searchNode(LinkedList_h* L, char x)
{
    listnode* tmp;
    tmp = L->head;
    while (tmp != NULL)
    {
        //if (strcmp(tmp->data->data, x) == 0)return tmp;
        if (tmp->node.data == x)return tmp;
        else tmp = tmp->link;
    }
    return tmp;
}

int checkNode(LinkedList_h*L, char x)
{
    listnode* tmp;
    tmp = L->head;
    while (tmp != NULL)
    {
        if (tmp->node.data== x)return 1;
        else tmp = tmp->link;
    }
    return 0;
}