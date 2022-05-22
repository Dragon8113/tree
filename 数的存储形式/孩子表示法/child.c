#include<stdio.h>
#include<stdlib.h>

#define MAX_TREE_SIZE 15
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int ElemType;

typedef struct NodePtr{     //孩子节点
    int cIndex;  //孩子位置
    struct NodePtr *SubSib; //孩子节点的下一个兄弟节点
} Node,*NodePtr;

typedef struct          //双亲节点
{   
    ElemType data;      //节点存储的元素数据
    NodePtr child;      //第一个孩子节点（从左往右）
} CNode;

typedef struct      //树
{
    CNode Nodes[MAX_TREE_SIZE];
    int r;  //根节点位置
    int n;  //当前树的节点数目
} CTree;

/* 测试用的树（层次表示法）: 5 1 3 4 8 9 7 6 2 10
                5
        1        3         4
      8   9        7     6
            2          10   
 */
void InitCTree(CTree *tree){    //初始化（测试）
    ElemType data[] = { 5, 1, 3, 4, 8, 9, 7, 6, 2, 10};
    int length = sizeof(data) / sizeof(data[0]);

    for(int i = 0; i < length; i++){
        tree->Nodes[i].data = data[i];
    }

    tree->n = length;
    tree->r = 0;

    Node (*child)[length-1] = (NodePtr)malloc( length * sizeof(Node));    //数组指针: 总共需要 存储孩子节点的位置的 节点（除了根节点即可）
    for(int i=0; i < length-1; i++){
        child[i]->cIndex = i+1;  //储存所有孩子节点的位置（除根节点）
    }    

    //根节点
    tree->Nodes[0].child = child[0];
    child[0]->SubSib = child[1];
    child[1]->SubSib = child[2];
    child[2]->SubSib = NULL;
    
    //节点元素 1 的节点
    tree->Nodes[1].child = child[3];
    child[3]->SubSib = child[4];
    child[4]->SubSib = NULL;

    //节点元素 3 的节点
    tree->Nodes[2].child = child[5];
    child[5]->SubSib = NULL;

    //节点元素 4 的节点
    tree->Nodes[3].child = child[6];
    child[6]->SubSib = NULL;

    //节点元素 9 的节点
    tree->Nodes[5].child = child[7];
    child[7]->SubSib = NULL;

    //节点元素 6 的节点
    tree->Nodes[7].child = child[8];
    child[8]->SubSib = NULL;

    //叶节点（即没有孩子的节点）: 8 7 2 10
    tree->Nodes[4].child = tree->Nodes[6].child = tree->Nodes[8].child = tree->Nodes[9].child = NULL;
}

int main(void){
    CTree tree;
    int length;

    printf("\n\n");
    InitCTree(&tree);
    length = tree.n;

    printf(" 储存的元素: ");
    for( int i = 0; i < length; i++){
        printf(" %d ", tree.Nodes[i].data);
    }


    int i = 0;
    int n = tree.n;
    NodePtr child;
    while( i < n ){
        printf("\n\n 节点元素 %d 的孩子节点: ", tree.Nodes[i].data);
        child = tree.Nodes[i].child;
        if(child != NULL){
           while(child != NULL){
                printf(" %d ", tree.Nodes[child->cIndex].data);
                child = child->SubSib;
            }
        } else{
            printf(" 此节点无孩子节点");
        }
        i++;
    }


    printf("\n\n");
    return 0;
}
