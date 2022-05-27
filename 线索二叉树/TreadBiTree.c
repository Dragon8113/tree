#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef char ElemType;

typedef enum {Link, Thread}  PointTag;  //枚举，Link表示此时孩子存在，Thread表示此时孩子为线索

typedef struct ThreadBiNode
{
    ElemType data;
    struct ThreadBiNode *lChild, *rChild;   //创建 节点的 左右孩子
    PointTag lTag, rTag;        //创建此时 左右孩子的tag，用于判断 此时孩子为 Link 还是 Thread
} ThreadBiNode, *ThreadBiTree;

/* 测试二叉树 
             A
       B          C    
    D     E           F  
 G   
 */

void createThreadBiTree(ThreadBiTree *T){   //以先序遍历创建二叉树(以空格作为空孩子): A B D G E C F
    char c;
    scanf("%c", &c);        //在控制台中输入: ABDG///E//C/F//

    if(c == '/'){       //输入 ‘/’:表示上个节点为 叶节点
        (*T) = NULL;
    } else{
        (*T) = (ThreadBiNode *)malloc(sizeof(ThreadBiNode));
        (*T)->data = c;
        (*T)->lTag = Link;
        (*T)->rTag = Link;
        createThreadBiTree(&((*T)->lChild));    //进入此时节点的 左节点
        createThreadBiTree(&((*T)->rChild));    //进入此时节点的 右节点
    }
}

ThreadBiTree pre;   //全局变量，记录遍历节点时的上一个节点：pre 默认指向 P 节点，额外创建的一个节点
void InThreading(ThreadBiTree T){   //以中序遍历将该二叉树转化为 线索二叉树: G D B E A C F

    if(T != NULL){
        InThreading(T->lChild);     //进入到 中序遍历的 第一节点（即最左边的那个节点)

        if(T->lChild == NULL){      //若此时节点的 左子树为空，则将其作为线索，指向上一个节点
            T->lTag = Thread;
            T->lChild = pre;
        }

        if(pre->rChild == NULL){    //因为要判断此时节点的右节点是否为 NULL，但我们刚开始不知道 此时节点的下一个节点
            pre->rTag = Thread;     //所以 进入下一轮，使用 pre（就是此时判断的节点）来判断，
            pre->rChild = T;        //此时的 T 其实是 此时节点的 右子树， 则 此时节点的右子树指向下一个节点
        }
        pre = T;    //pre 指向此时的节点

        InThreading(T->rChild);     //进入此时节点的右字数
    }

}

void InOrderThreading(ThreadBiTree T, ThreadBiTree *p){     //新建此时pre指向的 额外节点
    (*p) = (ThreadBiNode *)malloc(sizeof(ThreadBiNode));
    (*p)->lTag = Link;      //左子树指向树
    (*p)->rTag = Thread;    //右子树指向 下一个节点（中序遍历）
    (*p)->rChild = *p;      //右孩子默认指向自身

    if(T == NULL){      //若为空树
        (*p)->lChild = *p;  //左孩子也指向自身
    } else {    //若不为空
        (*p)->lChild = T;   //左子树 置为 根节点

        pre = *p;   
        InThreading(T);     //将 二叉树 线索化

        pre->rChild = *p;   //最后将 最后一个节点（中序遍历）的右孩子 也置为 p（额外节点）
        (*p)->rChild = pre; //p 的右孩子 也置为 最后一个节点（中序遍历）
    }
}

void InOrderTraverse(ThreadBiTree p){  //将线索化的二叉树遍历（非递归）:中序遍历
    ThreadBiTree temp;
    temp = p->lChild;   //不为空树，则 temp 指向 根节点

    while (temp != p)   //通过temp 看判断此时是否到达最后
    {
        while (temp->lTag == Link)  //遍历到 第一个节点 （中序遍历）: 即最左边那个节点
        {
            temp = temp->lChild;
        }
        printf(" %c ", temp->data);     //对第一个节点的数据进行操作

        while (temp->rTag == Thread && temp->rChild != p)   //判断 此时节点的右孩子为 线索，且不为 最后一个节点，
        {                                                   //即可直接通过 此时节点的右孩子 进行访问 下一个节点    
            temp = temp->rChild;
            printf(" %c ", temp->data);    //对获得的下一个节点的数据进行操作
        }
        temp = temp->rChild;    //若 右孩子 不为 线索，则表明 此时节点的右孩子存在，则访问此时节点的右子树
                                //然后 将此时的 右子树 作为根，进入循环。
    }
}

int main(void){
    ThreadBiTree T;
    ThreadBiNode *p;

    createThreadBiTree(&T); //创建新二叉树

    InOrderThreading(T, &p);    //将二叉树线索化

    printf("\n\n中序遍历: ");    //通过用线索化二叉树 ，可不用递归方法， 就可实现中序遍历
    InOrderTraverse(p);    //传入 额外创建的节点，可通过 temp == p 来判断遍历完成
    printf("\n\n");

    return 0;
}