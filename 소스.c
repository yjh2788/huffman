#define _CRT_SECURE_NO_WARNINGS
#include"heap.h"
#include"list.h"


LinkedList_h* read_save_file(FILE* fp, char* str, int size);
void Make_huffmanTree(heap* h);
element* MakeTreeNode(element tmp1, element tmp2);
void putListToHeap(LinkedList_h* L, heap* h);
int encoding(element* el, char x, int* code);
void decimalToBinary(element* el, char x, FILE* fp, int* tmp);

void main()
{
    FILE* fp = fopen("tmp.TXT", "r");
    FILE* save = fopen("save.TXT", "wb");
    heap* huffmanTree = createheap();
    int zipfile_size;
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    char* str = (char*)malloc(sizeof(char) * size);
    fseek(fp, 0, SEEK_SET);
    
    LinkedList_h* leafNode=read_save_file(fp,str,size);
   
    printList(leafNode);
    

    putListToHeap(leafNode, huffmanTree);
    printheap(huffmanTree);
 
    Make_huffmanTree(huffmanTree);
    printheap(huffmanTree);

    unsigned int output=0;
    int i;
    printf("\n압축 바이트 :");
    for ( i = 0; i < size; i++)
    {
        decimalToBinary(&huffmanTree->heap[1], str[i], save,&output);
       /* if (output > (output << 1))
        {
            fwrite(&output, 1, 1, save);
            output = 0;
        }
        else if((size-1)==i)fwrite(&output, 1, 1, save);*/
        if ((size - 1) == i)
        {
            if (output < 0x00000100)fwrite(&output, 1, 1, save);
            else if ((output >= 0x00000100) && (output < 0x00010000)) fwrite(&output,2,1,save);
            else if ((output >= 0x00010000) && (output < 0x01000000)) fwrite(&output,3,1,save);
            else fwrite(&output,4,1,save);
        }
    }
    printf("\n");
    
    fseek(save, 0, SEEK_END);
    zipfile_size = ftell(save);

    printf("\n원본파일 사이즈 : %d byte",size);
    printf("\n압축파일 사이즈 : %d byte", zipfile_size);
    printf("\n파일 압축률 : %lf", ((double)zipfile_size / (double)size) * 100);

    freeLinkedList_h(leafNode);
    free(huffmanTree);   
    free(str);
    fclose(save);
    fclose(fp);
    getchar();
}




LinkedList_h* read_save_file(FILE* fp, char*str, int size)
{
    LinkedList_h* leafNode = createLinkedList_h();
    int i = 0;
    int count_enter = 0;

    while (!feof(fp))
    {
        if (fscanf(fp, "%c", &str[i]))
        {
            if (str[i] == '\n') count_enter++;
            i++;
        }
    }
  
    for (i = 0; i < size - count_enter; i++)
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
   
    return leafNode;
}

void Make_huffmanTree(heap* h)
{
    element* root;
    int i;
    while (h->heap_size > 1)
    {
        root = MakeTreeNode(deletHeap(h), deletHeap(h));
        insertheap(h, root);
        free(root);
    }
}

element* MakeTreeNode(element tmp1, element tmp2)
{
    element* newNode = (element*)malloc(sizeof(element));
    element* Tmp1 = (element*)malloc(sizeof(element));
    element* Tmp2 = (element*)malloc(sizeof(element));
    *Tmp1 = tmp1;
    *Tmp2 = tmp2;
    newNode->num = tmp1.num + tmp2.num;
    newNode->data = NULL;
    newNode->right = Tmp1;
    newNode->left = Tmp2;
    return newNode;
}

void putListToHeap(LinkedList_h* L, heap* h)
{
    listnode* p;
    p = L->head;
    while (p != NULL)
    {
        insertheap(h, &p->node);
        p = p->link;
    }
}

int encoding(element* el, char x, int* code)
{
    if (!(el->left == NULL) && !(el->right == NULL))
    {
        if (el->data == x) return 1;
        else
        {
            *code = *code << 1;
            if (encoding(el->left, x, code)) return 1;
            (*code)++;
            if (encoding(el->right, x, code)) return 1;
        }

    }
    else if (el->data == x)    return 1;
    else return 0;
}

void decimalToBinary(element* el, char x,FILE* fp, int* tmp)
{
    // 동적 배열 생성 
    int code=0;
    encoding(el, x, &code);
    int n=code;
    int size = 1;
    char* a = (char*)calloc(size ,sizeof(char));    
    // 배열에 원소 넣기 
    for (int i = 0; n != 0; i++) {
        a[i] = n % 2;
        n /= 2;
        if (n != 0) {
            size++;
            a = realloc(a, sizeof(char) * size);
        }
    }

    // 배열 원소 거꾸로 출력 
    
    for (int i = size - 1; i >= 0; i--) {
        //fwrite(&a[i], 1, 1, fp);
        if (a[i])
        {
            *tmp=*tmp << 1;
            (*tmp)++;
        }
        else
        {
            *tmp=*tmp << 1;
        }
        if (*tmp > (*tmp << 1))
        {
            fwrite(tmp, 1, 1, fp);
            *tmp = 0;
        }
        
        
        printf("%d", a[i]);
    }
 
    free(a);
  
}
