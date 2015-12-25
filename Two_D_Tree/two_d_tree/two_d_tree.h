#include <stdio.h>
#include <stdlib.h>
#define FALSE (0)
#define TRUE (1)
#define TWO (2)
#define MASK (1)

/*	Data Type Definition	*/
typedef int BOOL;

/*	Part:2-d Tree	*/
typedef int Item;
typedef struct node
{
	Item item[TWO];
	int deleted; //A flag shows whether it is deleted
	struct node * left, *right;
} Node;
typedef struct twoDTree
{
	Node * root;
	int current;
} *TwoDTree;

/*Part: queue	*/
typedef struct queueNode
{
	Node * node;
	int index;
	struct queueNode * next;
} QueueNode;
typedef struct queue
{
	QueueNode * front, *rear;
	int current;
} *Queue;

/*Declarations for interface	*/

/************************************
*Initialize a queue
*@param const pq: points to a queue
*************************************/
BOOL Initialize_Q(Queue * const pq);

/*************************************
*judge whether a queue is empty or not /
*@Param pq:points to a queue which has been initialized
*@Return True:if empty
				False:if not
*************************************/
BOOL IsEmpty_Q(const Queue * const pq);

/*****************************************
*operation:Enqueue
*@Param: pq: points to a queue which has been initialized
				pn:data to add
				index:data to add
*@Return:True:if success
				False:if fail
******************************************/
BOOL EnQueue_Q(const Queue * const pq, Node * const pn, const int index);

/****************************************
*operation:Dequeue
*@Param: pq: points to a queue which has been initialized
				pnq:points to a QueueNode,save the deleted head pq
*@Return:True:if success
				False:if fail
*****************************************/
BOOL DeQueue_Q(const Queue * const pq, QueueNode * const pqn);

/****************************************
*operation:Free memory space a queue has occupied
*@Param: pq: points to a queue which has been initialized
*****************************************/
void Release_Q(const Queue * const pq);

/***************************************
*operation:Create and initialize a 2-d tree
*@Param: pt: points to a 2-d tree
*@Return:True:if success
				False:if fail
****************************************/
BOOL Initialize_T(TwoDTree * const pt);

/**************************************
*operation:Judge a 2-d tree whether it is empty
*@Param: pt: points to a 2-d tree
*@Return: True:if success
				 False:if fail
***************************************/
BOOL IsEmpty_T(const TwoDTree * const pt);

/**************************************
*operation:Insert
*@Param: pt: points to a 2-d which has been initialized
				pi: adress:data to add
*@Return:True:if success
				 False:if fail
****************************************/
BOOL Insert_T(const TwoDTree * const pt, const Item * const pi);

/**************************************
*operation:search for result satisfy the search scope in the 2-d tree
*@Param:pt:  pt: points to a 2-d which has been initialized
					 low & high: the search scope
*@Return: count: the number of node found
******************************************/
int Find_T(const TwoDTree * const pt, const Item * const low, const Item * const high);

/**************************************
*operation:lazy deletion
*@Param: pt: points to a 2-d which has been initialized
				pi: points to a pointer to delete 
*@Retuen:count:the number of node deleted
******************************************/
int Delete_T(const TwoDTree * const pt, const Item * const pi);

/**************************************
*operation:Release a 2-d tree 
*@Param:pt: points to a 2-d which has been initialized
***************************************/
void Release_T(const TwoDTree * const pt);