

#include "stdafx.h"
typedef  struct treeNode *Node;

struct treeNode{
	int element;
	treeNode *left;
	treeNode *right;
};

struct Queue{
	int size;
	int front;
	int rear;
	treeNode *que;
};
//初始化队列
Queue * initQueue(int qSize)
{
	Queue *Q;
	Q = (Queue *)malloc(sizeof(Queue));
	Q->size = qSize;
	Q->que = (treeNode *)malloc(sizeof(treeNode)*qSize);
	Q->front = qSize;
	Q->rear = 0;
	return Q;
}

//判断队列是否为空  
int isEmpty(Queue *Q)
{
	return Q->front % (Q->size) == Q->rear;
}
//Enqueue
void Enqueue(Queue *Q, treeNode *p)
{
	*(Q->que + Q->rear++) = *p;
	Q->rear %= Q->size;//rear+1 and make it circular
}
//Dequeue  
treeNode * Dequeue(Queue *Q)
{
	Q->front %= Q->size;
	return Q->que + (Q->front++);//front+1 and make it circular
}
//层序遍历  
void traverse(treeNode *tree)
{
	Queue  *Q = NULL;
	treeNode *p;
	Q = initQueue(20);
	Enqueue(Q, tree);
	printf(" [");
	while (!isEmpty(Q))
	{
		p = Dequeue(Q);
		printf("%d,", p->element);
		if (p->left != NULL)
			Enqueue(Q, p->left);
		if (p->right != NULL)
			Enqueue(Q, p->right);
	}
	printf("]\n");
}
//插入节点  
treeNode *insert(treeNode *tree, int element)
{
	if (tree == NULL)
	{
		treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
		if (newNode == NULL)
			return newNode;
		newNode->element = element;
		newNode->left = NULL;
		newNode->right = NULL;
		tree = newNode;
		return tree;
	}
	if (tree->element >= element)
		tree->left = insert(tree->left, element);
	else
		tree->right = insert(tree->right, element);
	return tree;
}

treeNode * creatTree(int amount)
{
	treeNode *tree = NULL;
	srand((unsigned)time(NULL));
	for (int i = 0; i<amount; i++)
	{
		tree = insert(tree, rand() % 50);
	}
	return tree;
}
//output Preorder
void outputPre(treeNode * tree)
{
	if (tree == NULL)
		printf("Empty tree!");
	else
	{
		printf("%d,", tree->element);
		if (tree->left != NULL)
			outputPre(tree->left);
		if (tree->right != NULL)
			outputPre(tree->right);
	}
}
//output Inorder 
void outputMid(treeNode *tree)
{
	if (tree == NULL)
		printf("Empty tree!");
	else
	{
		if (tree->left != NULL)
			outputMid(tree->left);
		printf("%d,", tree->element);
		if (tree->right != NULL)
			outputMid(tree->right);
	}
}

void main()
{
	treeNode *tree = creatTree(10);
	if (tree == NULL)
		return;
	printf("Preorder:  \n");
	printf(" [");
	outputPre(tree);
	printf("]\n");
	printf("Inorder：\n");
	printf(" [");
	outputMid(tree);
	printf("]\n");
	printf("Sequence traversal ：\n");
	traverse(tree);
}