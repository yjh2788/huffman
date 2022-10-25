#define _CRT_SECURE_NO_WARNINGS
#include"heap.h"
#include"list.h"
void putListToHeap(LinkedList_h* L, heap* h);
//void insertTreeNode(heap* Heap, element tmp1, element tmp2);
element* MakeTreeNode(element tmp1, element tmp2);
int encoding(element* el, char x, int* code);
void main()
{
    int i = 0;
    int count_enter = 0;
    int code = 0;
    heap* Heap = createheap();
    element* root=NULL;
    element tmp1, tmp2,dumy;

    LinkedList_h* leafNode = createLinkedList_h();

    FILE* fp = fopen("tmp.TXT", "r");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    char* str=(char*)malloc(sizeof(char) * size);
    
    fseek(fp, 0, SEEK_SET);

    while (!feof(fp))
    { 
       
        if (fscanf(fp, "%c", &str[i]))
        {
            if (str[i] == '\n') count_enter++;
            i++;
        }
        else
        {
            printf("fail");
            break;
        }
        
    }
 

    for (i = 0; i < size-count_enter; i++)
    {
        if (i == 0)
        {
            insertFirstnode(leafNode, str[0]);
            leafNode->head->node.num = 1;
        }
        else if (checkNode(leafNode, str[i]))
        {
            
            searchNode(leafNode, str[i])->node.num++;

        }
        else
        {
            insertLastNode(leafNode, str[i]);
            searchNode(leafNode, str[i])->node.num++;
        }
        leafNode->head->node.left = NULL;
        leafNode->head->node.right = NULL;
    }
    

   
    printList(leafNode);
    fclose(fp);

    putListToHeap(leafNode, Heap);
    printheap(Heap);

    //code = Heap->heap_size;
    //for (i = 1; i <= code; i++)
    //{
     //   tmp1 = deletHeap(Heap);
     //   printf("\n delete : [%c][%d]",tmp1.data, tmp1.num);
    //}
     //getchar();
    
  
    while (Heap->heap_size > 1)
    {       
        tmp1 = deletHeap(Heap);
        tmp2 = deletHeap(Heap); 
        root=MakeTreeNode(tmp1, tmp2);
        insertTreeNode(Heap, tmp1, tmp2);
    }
    printheap(Heap);

   
    i=encoding(Heap->heap, '5',&code);


    printf("%d", i);

    freeLinkedList_h(leafNode);
   
    getchar();
}


element* MakeTreeNode(element tmp1,element tmp2)
{
    element* newNode = (element*)malloc(sizeof(element));
    
    newNode->num = tmp1.num + tmp2.num;
    newNode->data = NULL;


    newNode->right = &tmp1;
    newNode->left = &tmp2;
    return newNode;
}

void putListToHeap(LinkedList_h* L,heap* h)
{
    listnode* p;
   
    p = L->head;
    while (p != NULL)
    {
        insertheap(h, &p->node);
        p = p->link;
       
    }
    

}



int encoding(element*el,char x, int*code)
{
    
    if (!(el->left==NULL)&& !(el->right))
    {
        
        if (el->data == x) return *code;
        else
        {
            *code = *code << 1;
            encoding(el->left, x,code);
            *code = *code >> 1;
            code++;
            encoding(el->right, x,code);
        }
        
    }
    return *code;
}