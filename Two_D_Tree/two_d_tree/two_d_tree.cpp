#include "stdafx.h"
#include "two_d_tree.h"


/*function declaration*/
static QueueNode * makeNode_Q(Node * const pn, const int index);
static Node * makeNode_T(const Item * const pi);
static void release_T(Node * const pn);
/*****************************/



/******************** *******Queue **************************************/
BOOL Initialize_Q(Queue * const pq)
{
	*pq = (struct queue *) malloc(sizeof (struct queue));
	if (NULL == *pq)
		return FALSE;
	(*pq)->front = (*pq)->rear = NULL;
	(*pq)->current = 0;
	return TRUE;
}

BOOL IsEmpty_Q(const Queue * const pq)
{
	switch ((*pq)->current)
	{
	case 0:	return TRUE;
	default:	return FALSE;
	}
}

BOOL EnQueue_Q(const Queue * const pq, Node * const pn, const int index)
{
	QueueNode * newQNode;

	newQNode = makeNode_Q(pn, index);
	if (NULL == newQNode)
		return FALSE;
	if (IsEmpty_Q(pq))
		(*pq)->front = (*pq)->rear = newQNode;
	else
	{
		(*pq)->rear->next = newQNode;
		(*pq)->rear = newQNode;
	}
	(*pq)->current++;

	return TRUE;
}

BOOL DeQueue_Q(const Queue * const pq, QueueNode * const pqn)
{
	QueueNode * record;

	if (IsEmpty_Q(pq))
		return FALSE;
	record = (*pq)->front;
	*pqn = *record;
	(*pq)->front = record->next;
	if (NULL == (*pq)->front)
		(*pq)->rear = NULL;
	free(record);
	(*pq)->current--;

	return TRUE;
}

void Release_Q(const Queue * const pq)
{
	QueueNode * record, *scan;

	scan = (*pq)->front;
	while (scan != NULL)
	{
		record = scan;
		scan = scan->next;
		free(record);
	}
	free(*pq);
}

/********************************* 2-d Tree ***********************************/
BOOL Initialize_T(TwoDTree * const pt)
{
	*pt = (struct twoDTree *) malloc(sizeof (struct twoDTree));
	if (NULL == *pt)
		return FALSE;
	(*pt)->root = NULL;
	(*pt)->current = 0;

	return TRUE;
}

BOOL IsEmpty_T(const TwoDTree * const pt)
{
	switch ((*pt)->current)
	{
	case 0:	return TRUE;
	default:	return FALSE;
	}
}

BOOL Insert_T(const TwoDTree * const pt, const Item * const pi)
{
	Node * newNode, *parent, *scan;
	int index;
	parent = (*pt)->root;
	//cout << pi[0] << endl;
	//cout << pi[1] << endl;
	newNode = makeNode_T(pi);
	if (NULL == newNode)
		return FALSE;
	if (IsEmpty_T(pt))
	{
		(*pt)->root = newNode;
	}
	else
	{
		scan = (*pt)->root;
		/*	item[0] is odd number level.	
		*while item[1] is even number level*/
		index = 0;
		while (scan != NULL)
		{
			parent = scan;
			//cout << scan->item[index] << endl;
			if (pi[index] < scan->item[index])
				scan = scan->left;
			/*	Duplicate will be added to right subtree.	*/
			else
				scan = scan->right;
			index ^= MASK;
			//cout << index << endl;
		}
		/*	Duplicate will be added to right subtree.	*/
		index ^= MASK;
		if (pi[index] < parent->item[index])
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	(*pt)->current++;

	return TRUE;
}

int Find_T(const TwoDTree * const pt, const Item * const low, const Item * const high)
{
	Queue queue;
	QueueNode * qNode;
	Node * scan;
	int count, index;

	if (IsEmpty_T(pt))
		return 0;
	Initialize_Q(&queue);
	if (FALSE == Initialize_Q(&queue))
	{
		puts("ERROR:Out of space!");
		return 0;
	}
	qNode = (QueueNode *)malloc(sizeof (QueueNode));
	if (NULL == qNode)
	{
		Release_Q(&queue);
		puts("ERROR:Out of space!");
		return 0;
	}
	count = 0;
	EnQueue_Q(&queue, (*pt)->root, 0);
	while (!IsEmpty_Q(&queue))
	{
		DeQueue_Q(&queue, qNode);
		scan = qNode->node;
		index = qNode->index;
		/*Here is the key to solve the problem in textbook page 107-c*/
		if (low[0] <= scan->item[0] && scan->item[0] <= high[0] &&
			low[1] <= scan->item[1] && scan->item[1] <= high[1] &&
			FALSE == scan->deleted)
		{
			cout << "record found! it is:"<<endl;
			cout <<"key1:"<<scan->item[0] << endl;
			cout <<"key2:"<< scan->item[1] << endl;
			count++;
		}

		if (low[index] <= scan->item[index] && scan->left != NULL)
			EnQueue_Q(&queue, scan->left, index ^ MASK);
		if (scan->item[index] <= high[index] && scan->right != NULL)
			EnQueue_Q(&queue, scan->right, index ^ MASK);
	}
	
	Release_Q(&queue);
	free(qNode);

	return count;
}

int Delete_T(const TwoDTree * const pt, const Item * const pi)
{
	Node * scan;
	int count, index;
	scan = (*pt)->root;
	count = 0;
	index = 0;
	while (scan != NULL)
	{
		if (pi[index] < scan->item[index])
			scan = scan->left;
		else if (scan->item[index] < pi[index])
			scan = scan->right;
		else
		{
			if (pi[index ^ MASK] == scan->item[index ^ MASK] &&
				FALSE == scan->deleted)
			{
				scan->deleted = TRUE;
				count++;
			}
			/*	Because duplicate has been added to right subtree.	*/
			scan = scan->right;
		}
		index ^= MASK;
	}
	(*pt)->current -= count;

	return count;
}

void Release_T(const TwoDTree * const pt)
{
	release_T((*pt)->root);
	free(*pt);
}

/**************************Some auxiliary functions**************************/
static QueueNode * makeNode_Q(Node * const pn, const int index)
{
	QueueNode * newQNode;

	newQNode = (struct queueNode *) malloc(sizeof (struct queueNode));
	if (NULL == newQNode)
		return NULL;
	newQNode->node = pn;
	newQNode->next = NULL;
	newQNode->index = index;

	return newQNode;
}


static Node * makeNode_T(const Item * const pi)
{
	Node * newNode;

	newNode = (Node *)malloc(sizeof (Node));
	if (NULL == newNode)
		return NULL;
	newNode->item[0] = pi[0];
	newNode->item[1] = pi[1];
	newNode->deleted = FALSE;
	newNode->left = newNode->right = NULL;

	return newNode;
}

static void release_T(Node * const pn)
{
	if (pn != NULL)
	{
		release_T(pn->left);
		release_T(pn->right);
		free(pn);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	//TO DO test
	static Item ItemList[][2] = { { 2, 11 }, { 1, 10 }, { 3, 12 }, { 4, 13 }, { 5, 14 }, {6,15} };
	/*for (int i = 0; i < 3; i++){
		cout << *(*(ItemList + i))<<"   ";
		cout << *(*(ItemList + i)+1) << endl;
	}*/
	TwoDTree * p = new TwoDTree;
	
	int flag_1 = Initialize_T(p);
	//int flag_2= Insert_T(p, *(ItemList+2));
	for (int i = 0; i < 6; i++)
		Insert_T(p, *(ItemList + i));
	//cout << flag_1 << endl;
	
	Item low[] = { 2, 12};
	Item high[] = { 4, 15 };
	Find_T(p, low, high);

	return 0;
}

