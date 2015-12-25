// polynomiallist.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define     LIST_OK		0
#define     LIST_ERROR	-1
typedef struct polynomiallist
{
	int factor;//系数
	int power;//幂
	struct polynomiallist* next;//下一节点
}List;

//初始化链表，第一个节点不用来存储数据
int init_list(List** list)
{
	if (NULL != *list)
	{
		printf("链表初始化失败！/n");
		return LIST_ERROR;
	}
	*list = (List*)malloc(sizeof(List));
	if (NULL == *list)
	{
		printf("分配内存出错！\n");
		return LIST_ERROR;
	}
	(*list)->next = NULL;
	return LIST_OK;
}
//向链表中输入节点
int insert_node(List* list, List* node)
{
	if (NULL == list)
	{
		printf("链表还没有初始化，无法插入节点！\n");
		return LIST_ERROR;
	}
	while (NULL != list->next)
	{
		list = list->next;
	}
	list->next = (List*)malloc(sizeof(List));
	if (NULL == list)
	{
		printf("分配内存出错！\n");
		return LIST_ERROR;
	}
	list = list->next;
	list->factor = node->factor;
	list->power = node->power;
	list->next = NULL;
	return LIST_OK;
}
//从链表中删除节点
int delete_node(List* list, List* node)
{
	List* tmp = NULL;
	if (NULL == list)
	{
		printf("链表还没有初始化，无法删除节点！\n");
		return LIST_ERROR;
	}
	while (NULL != list->next)
	{
		if ((node->factor == list->next->factor) && (node->power == list->next->power))
		{
			tmp = list->next;
			list->next = list->next->next;
			free(tmp);
			return LIST_OK;
		}
		list = list->next;
	}
	printf("没有找到你要删除的节点！\n");
	return LIST_ERROR;
}
//删除链表
int delete_list(List** list)
{
	List* tmp = NULL;
	while (NULL != *list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	return LIST_OK;
}

//求链表元素个数
int list_cnt(List* list)
{
	int i = 0;
	if (NULL == list)
	{
		return 0;
	}
	while (NULL != list)
	{
		i++;
		list = list->next;
	}
	return i - 1;
}

//链表排序，幂数相同的项，系数合并
int sort_list(List* list)
{
	//标记元素是否排序
	int sorted = 0;
	List* node;
	List*tmp;
	List* const head = list;
	if (NULL == list)
	{
		printf("链表没有初始化，无法排序！\n");
		return LIST_ERROR;
	}

	//如果链表中的元素个数小于2个，就不需要排序
	if (list_cnt(list)<2)
	{
		return LIST_OK;
	}

	node = head->next;
	head->next = NULL;
	while (NULL != node)
	{
		sorted = 0;
		list = head;
		while (NULL != list->next)
		{
			//如果是幂数相同，则合并系数
			if (node->power == list->next->power)
			{
				list->next->factor += node->factor;
				node = node->next;
				sorted = 1;
				break;
			}
			else if (node->power>list->next->power)
			{
				tmp = node;
				node = node->next;
				tmp->next = list->next;
				list->next = tmp;
				sorted = 1;
				break;
			}
			list = list->next;
		}

		//如果node的幂数最小，插入链表最后
		if (0 == sorted)
		{
			tmp = node;
			node = node->next;
			list->next = tmp;
			tmp->next = NULL;
		}
	}
	return LIST_OK;
}

//多项式相乘运算，结果保存在dest链表中。
int mul_poly(List** dest, List** src)
{
	List data;
	//构造新链表存储乘法运算结果
	List* pNew = NULL;
	List* head1 = *dest;
	List* head2 = *src;
	init_list(&pNew);
	if (0 == list_cnt(*dest) || 0 == list_cnt(*src))
	{
		printf("无法进行多项式的乘法运算！\n");
		return LIST_ERROR;
	}
	while (NULL != (*dest)->next)
	{
		while (NULL != (*src)->next)
		{
			data.factor = ((*dest)->next->factor)*((*src)->next->factor);
			data.power = ((*dest)->next->power) + ((*src)->next->power);
			data.next = NULL;
			insert_node(pNew, &data);
			*src = (*src)->next;
		}
		*src = head2;
		*dest = (*dest)->next;
	}
	sort_list(pNew);
	delete_list(&head1);
	delete_list(&head2);
	*dest = pNew;
	return LIST_OK;

}
int display_poly(List* list)
{
	if (0 == list_cnt(list))
	{
		printf("链表中没有元素，无法输出！\n");
		return LIST_ERROR;
	}
	if (0 != list->next->power)
	{
		printf("%dX^%d", list->next->factor, list->next->power);
	}
	else
	{
		printf("%d", list->next->factor);
	}
	list = list->next;
	while (NULL != list->next)
	{
		if (list->next->factor>0)
		{
			if (0 == list->next->power)
			{
				printf("+%d", list->next->factor);
			}
			else
			{
				printf("+%dX^%d", list->next->factor, list->next->power);
			}
		}
		else if (list->next->factor<0)
		{
			if (0 == list->next->power)
			{
				if (0 != list->next->factor)
				{
					printf("%d", list->next->factor);
				}
			}
			else
			{
				printf("%dX^%d", list->next->factor, list->next->power);
			}
		}
		list = list->next;
	}
	return LIST_OK;
}
int main(int argc, char *argv[])
{
	int i;
	int n;
	List data;
	List* dest = NULL;
	List* src = NULL;
	init_list(&dest);
	init_list(&src);
	printf("多项式1有多少项：\n");
	scanf("%d", &n);
	printf("请分别输入多项式1的系数和幂数，中间用空格隔开：\n");
	for (i = 0; i<n; i++)
	{
		scanf("%d%d", &data.factor, &data.power);
		insert_node(dest, &data);
	}
	printf("多项式2有多少项：\n");
	scanf("%d", &n);
	printf("请分别输入多项式2的系数和幂数，中间用空格隔开：\n");
	for (i = 0; i<n; i++)
	{
		scanf("%d%d", &data.factor, &data.power);
		insert_node(src, &data);
	}
	printf("(");
	display_poly(dest);
	printf(")*(");
	display_poly(src);
	printf(")=");
	mul_poly(&dest, &src);
	display_poly(dest);
	printf("\n");
	delete_list(&dest);
	return 0;
}




