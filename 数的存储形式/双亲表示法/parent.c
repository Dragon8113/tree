#include<stdio.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAX_TREE_SIZE 10  
typedef int ElemType;
typedef int Status;

typedef struct{     //节点
    ElemType data;  
    int parent;     //双亲节点位置
    /*  扩展用 
    int Child1; //孩子节点位置
    int Child2;
    int Child3;
    int RigSib; //兄弟节点位置
     */
} PTNode;

typedef struct{     //树
    PTNode Nodes[MAX_TREE_SIZE];
    int r;  //根节点位置
    int n;  //当前树的节点数目
} PTree;

/* 测试用的树
            1
    4      5      6
  7  8       2   3   9   
 */
Status InitTree(PTree *tree){       //层次表示法: 1 4 5 6 7 8 2 3 9（测试）
    ElemType data[] = { 1, 4, 5, 6, 7, 8, 2, 3, 9};
    int length = sizeof(data)/ sizeof(data[0]);

    for(int i = 0; i < length; i++){
        tree->Nodes[i].data = data[i];
    }
    tree->r = 0;
    tree->n = length;

    tree->Nodes[0].parent = -1;
    tree->Nodes[1].parent = 0;
    tree->Nodes[2].parent = 0;
    tree->Nodes[3].parent = 0;
    tree->Nodes[4].parent = 1;
    tree->Nodes[5].parent = 1;
    tree->Nodes[6].parent = 2;
    tree->Nodes[7].parent = 3;
    tree->Nodes[8].parent = 3;
    
    return OK;
}

/* 测试用的树
            1
    4      5      6
  7  8       2   3   9   
 */
int main(void){     //测试(树表示方法为：层次表法式)
    PTree tree; 
    int length;
    printf("\n\n");

    InitTree(&tree);        //初始化    
    length = tree.n;

    PTNode node;
    PTNode parent;
    for(int i=0; i < length; i++){
        node = tree.Nodes[i];       //此时的节点
        if(node.parent != -1){
            parent = tree.Nodes[node.parent];   //此时节点的双亲节点
            printf( "\n节点 %d 的双亲节点为： %d \n", node.data, parent.data);
        } else{
            printf(" \n节点 %d 为根节点, 没有双亲节点\n", node.data);
        }
    }

    return 0;
}
