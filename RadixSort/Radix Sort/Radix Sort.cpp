
#include "stdafx.h"
#define SUCCESS (0)
#define FAILURE (-1)
#define NUM_ENTRIES(a) ((sizeof (a)) / (sizeof (a[0])))
#define DEBUG
	
typedef struct NODE
{
		int data;
		struct NODE *next;
	} NODE;
  typedef struct	BUCKET
  {
	  NODE *head;
	  NODE *rear;
  } BUCKET;
  
  /*bucket初始化*/
  static int bucket_init(int radix, BUCKET **bucket);
  /*桶式排序*/
  static int bucket_sort(int a[], int n, int k, int radix, BUCKET *bucket);
  /*释放空间*/
  static int bucket_free(BUCKET *bucket);
  /*基于桶式排序的基数排序*/
  static int radix_sort(int a[], int n, int radix);
  
  static int bucket_init(int radix, BUCKET **bucket)
  {
	  if (radix < 1)
	  {
		  printf("invalid radix %d, should be greater than 0\n", radix);
		  return (FAILURE);
	  }
	  *bucket = (BUCKET *)malloc(sizeof (BUCKET)* radix);
	  if (*bucket == NULL)
	  {
		  printf("malloc () failed\n");
		  return (FAILURE);
	  }
	  /*****************************************************************/
	  memset((char *)*bucket, 0, sizeof (BUCKET)* radix);
  
	  return (SUCCESS);
  }
  
  static int bucket_free(BUCKET *bucket)
  {
	  free(bucket);
	  return (SUCCESS);
  }
  
  /*基于桶式排序的基数排序
  radix------------------基数
  bucket----------------桶
  a[]---------------------排序数组
  n-----------------------
  k-----------------------
  */
  static int bucket_sort(int a[], int n, int k, int radix, BUCKET *bucket)
  {
	  int i, j, key;
	  NODE *node;
	  for (i = 0; i < n; i++)
	  {
		  for (j = 0, key = a[i]; j < k; j++)
		  {
			  key = key / radix;
		  }
		  key = key % radix;
		  node = (NODE *)malloc(sizeof (NODE));
		  if (node == NULL)
		  {
			  printf("malloc () failed, bucket_sort () aborted\n");
			  return (FAILURE);
		  }
		  node->data = a[i];
		  node->next = NULL;
		  /*按顺序入桶*/
		  if (bucket[key].head == NULL)
		  {
			  bucket[key].head = node;
			  bucket[key].rear = node;
		  }
		  else
		  {
			  bucket[key].rear->next = node;
			  bucket[key].rear = node;
		  }
	  }
	  /*按顺序出桶*/
	  for (i = 0, j = 0; i < radix; i++)
	  {
		  while (bucket[i].head != NULL)
		  {
			  a[j++] = bucket[i].head->data;
			  node = bucket[i].head;
			  bucket[i].head = bucket[i].head->next;
			  free(node);
		  }
	  }
#ifdef DEBUG
	  for (i = 0; i < n; i++)
	   {
		  printf("%d, ", a[i]);
	  }
	  printf("\n");
#endif
	  return (SUCCESS);
  }
  
  static int radix_sort(int a[], int n, int radix)
  {
	  BUCKET *bucket;
	  int i, j, k, m;
	  if (bucket_init(radix, &bucket) != SUCCESS)
	  {
		  printf("bucket_init () failed\n");
		  return (FAILURE);
	  }
#ifdef DEBUG
	  printf("original array is: ");
	  for (i = 0; i < n; i++)
	  {
		  printf("%d, ", a[i]);
	  }
	  printf("\n");
#endif
	  for (i = 0, j = 0, k = 0, m = 0; i < n; i++)
	  {
		  /*统计每个数的位数*/
		  for (j = 0, k = a[i]; k > 0; j++)
		  {
			  k /= radix;
		  }
		  /*将最大数存入m中*/
		  if (j > m)
			  m = j;
	  }
#ifdef DEBUG
	  printf("need %d rounds of bucket sort\n", m);
#endif
	  for (i = 0; i < m; i++)
	  {
		  /*桶式排序m次*/
		  if (bucket_sort(a, n, i, radix, bucket) != SUCCESS)
		  {
			  printf("bucket_sort () failed\n");
			  return (FAILURE);
		  }
	  }
	  bucket_free(bucket);
	  return (SUCCESS);
  }
  /******************************************************************************
  */
  int main()
  {
	  static int a[] = { 1,2,3,4,5,6 ,0,12,23,65,456,560000,560001};
	  radix_sort(a, NUM_ENTRIES(a), 10);
	  
	  return (SUCCESS);
  }
