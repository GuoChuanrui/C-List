#include<stdio.h>
#include<assert.h>
#include<malloc.h>

typedef int DataType;
//定义单链表
typedef struct ListNode
{
	DataType _data;    //数据
	struct ListNode * _next;   //指向下一个节点的指针
}ListNode;

//初始化
void InitList(ListNode * &pHead)
{
	pHead = NULL;
}

//创建节点
ListNode * BuyNode(DataType x)
{
	ListNode * tmp = (ListNode *)malloc(sizeof(ListNode));
	assert(tmp);
	tmp->_data = x;
	tmp->_next = NULL;
	return tmp;
}

//尾插
void PushBack(ListNode * &pHead, DataType x)
{
	if (NULL == pHead)      //为空时，表示没有节点，创建新节点
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode * tail = pHead;
		while (tail->_next != NULL)
		{
			tail = tail->_next;     //令tail指向最后一个节点
		}
		tail->_next = BuyNode(x);
	}
}

//头插
void PushFront(ListNode * &pHead, DataType x)
{
	if (NULL == pHead)
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode * tmp = BuyNode(x);
		tmp->_next = pHead;
		pHead = tmp;
	}
}

//尾删
void PopBack(ListNode * &pHead)    //1.为空  2.一个节点  3，多个节点
{
	if (NULL == pHead)
	{
		printf("List is empty!\n");
		return;
	}
	else if (NULL == pHead->_next)
	{
		free(pHead);
		pHead = NULL;
	}
	else
	{
		ListNode * prevtail = NULL, *tail = pHead;
		while (tail->_next != NULL)
		{
			prevtail = tail;         //令tail指向尾部，prevtail指向倒数第二个
			tail = tail->_next;
		}
		prevtail->_next = NULL;
		free(tail);
	}
}

//头删
void PopFront(ListNode * &pHead)
{
	if (NULL == pHead)
	{
		printf("List is empty!\n");
		return;
	}
	else
	{
		ListNode* cur = pHead;
		pHead = pHead->_next;
		free(cur);
	}
}

//查找
ListNode * Find(ListNode * pHead, DataType x)
{
	ListNode * cur = pHead;
	while (cur)
	{
		if (cur->_data == x)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

//插入
void Insert(ListNode * &pos, DataType x)    //在pos节点后插入
{
	assert(pos);
	ListNode * tmp = BuyNode(x);
	tmp->_next = pos->_next;
	pos->_next = tmp;
}

//删除某节点
void Erase(ListNode * &pHead, ListNode * pos)
{
	assert(pos);

	if (pos == pHead)    //当要删除的节点就是第一个时，直接删
	{
		pHead = pHead->_next;
		free(pos);
	}
	else
	{
		ListNode * cur = pHead;
		while (cur)
		{
			if (cur->_next == pos)
			{
				cur->_next = pos->_next;
				free(pos);
				break;
			}
			cur = cur->_next;
		}
	}
}

//删除数据为x的节点
void Remove(ListNode * &pHead, DataType x)
{
	if (NULL == pHead)
	{
		printf("List is empty!\n");
		return;
	}
	else
	{
		ListNode * ret = Find(pHead, x);    //用ret变量指向x所在节点
		if (ret)
		{
			Erase(pHead, ret);		//删除此节点
		}
	}
}

//释放
void DestroyList(ListNode* & pHead)
{
	ListNode* cur = pHead;
	while (cur)
	{
		ListNode* tmp = cur;
		cur = cur->_next;
		free(tmp);
	}
	pHead = NULL;
}

//打印输出
void PrintList(ListNode * pHead)
{
	ListNode * cur = pHead;
	while (cur != NULL)
	{
		printf("%d -> ", cur->_data);
		cur = cur->_next;
	}
	printf("NULL\n");
}


////////////////////////////////
//////////单链表面试题//////////
////////////////////////////////

/*
1.比较顺序表和单链表的优缺点
   1）顺序表支持随机访问，单链表不支持。
   2）顺序表插入 / 删除数据效率很低，时间复杂度为O(N)（除尾插、尾删）
	   单链表插入 / 删除数据效率高，时间复杂度为O(1)。
   3）顺序表的CPU高速缓存效率更高，单链表的CPU高速缓存效率更低。
*/

//2.从尾到头打印单链表
void PrintTailToHead(ListNode * pHead)
{
	if (pHead)
	{
		PrintTailToHead(pHead->_next);
		printf("%d  <- ", pHead->_data);
	}
}

//3.删除一个无头单链表的非尾节点
void DelNonTailNode(ListNode * pos)
{
	assert(pos && pos->_next);
	pos->_data = pos->_next->_data;
	ListNode * next = pos->_next->_next;
	free(pos->_next);
	pos->_next = next;
}

//创建节点
ListNode * BuyNode(DataType x)
{
	ListNode * tmp = (ListNode *)malloc(sizeof(ListNode));
	assert(tmp);
	tmp->_data = x;
	tmp->_next = NULL;
	return tmp;
}

//4.在无头单链表的一个非头结点前插入一个节点
void InsertFrontNode(ListNode * pos, DataType x)
{
	assert(pos);
	ListNode * tmp = BuyNode(x);
	tmp->_next = pos->_next;
	pos->_next = tmp;
	DataType tmpData = tmp->_data;
	tmp->_data = pos->_data;
	pos->_data = tmpData;
}

//5.单链表实现约瑟夫环
void JosephCycle(ListNode * &pHead, int m)
{
	ListNode* cur = pHead;
	if (cur == NULL)
	{
		return ;
	}
	while (1)
	{
		if (cur == cur->_next)   //只剩下一个节点
		{
			return ;
		}
		int x = m;
		while (--x)
		{
			cur = cur->_next;
			//替换法进行删除
			cur->_data = cur->_next->_data;
			ListNode* del = cur->_next;
			cur->_next = del->_next;
			free(del);
		}
	}
}

//6.逆置/反转单链表
void Reverse(ListNode * &pHead)
{
	ListNode * cur = pHead;
	ListNode * newHead = NULL;
	while (cur)
	{
		ListNode * tmp = cur;
		cur = cur->_next;
		tmp->_next = newHead;
		newHead = tmp;
	}
	pHead = newHead;
}

//7.单链表排序(冒泡)
void SortList(ListNode *pHead)
{
	if (pHead == NULL || pHead->_next == NULL)   //为空或有一个节点
	{
		return;
	}

	ListNode * cur = pHead->_next;
	ListNode * prev = pHead;
	ListNode * tail = NULL;

	while (tail != pHead)
	{
		prev = pHead;
		cur = pHead->_next;
		int exchange = 0;
		while (cur != tail)
		{
			if (prev->_data > cur->_data)  //前面的数据大于后面的数据，交换值
			{
				DataType tmp = prev->_data;
				prev->_data = cur->_data;
				cur->_data = tmp;
				exchange = 1;
			}
			prev = cur;
			cur = cur->_next;
		}
		if (exchange == 0)
		{
			return;
		}
		tail = prev;
	}
}


//7.单链表排序(选择)
void SelectSort(ListNode * pHead)
{
	ListNode * cur = pHead;
	while (cur)
	{
		ListNode * tmp = cur->_next;
		while (tmp)
		{
			if (cur->_data > tmp->_data)  //当前数据大于后面的数据，交换值
			{
				DataType tmpData = tmp->_data;
				tmp->_data = cur->_data;
				cur->_data = tmpData;
			}
			tmp = tmp->_next;
		}
		cur = cur->_next;
	}
}

//8.合并两个有序链表，合并后依然有序
ListNode * MergeList(ListNode * pHead1, ListNode * pHead2)
{
	if (pHead1 == NULL)
	{
		return pHead2;
	}
	if (pHead2 == NULL)
	{
		return pHead1;
	}
	ListNode* newHead;
	ListNode* tail;
	ListNode* cur1 = pHead1;
	ListNode* cur2 = pHead2;

	if (cur1->_data < cur2->_data)
	{
		newHead = cur1;
		cur1 = cur1->_next;
	}
	else
	{
		newHead = cur2;
		cur2 = cur2->_next;
	}

	tail = newHead;
	while (cur1 && cur2)
	{
		if (cur1->_data < cur2->_data)
		{
			tail->_next = cur1;
			cur1 = cur1->_next;
		}
		else
		{
			tail->_next = cur2;
			cur1 = cur2->_next;
		}
		tail = tail->_next;
	}
	if (cur1)
	{
		tail->_next = cur1;
	}
	if (cur2)
	{
		tail->_next = cur2;
	}
	return newHead;
}


//9.查找单链表的中间节点，要求只遍历一次
ListNode * FindMid(ListNode * pHead)
{
	ListNode * slow = pHead, *fast = pHead;
	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
	}
	return slow;
}

//10.查找单链表的倒数第K个节点，要求只能遍历一次
ListNode * FindKTailNode(ListNode * pHead, int k)
{
	ListNode * slow = pHead, *fast = pHead;
	while (k--)
	{
		if (fast == NULL)    //没有k这么长,返回空
		{
			return NULL;
		}
		fast = fast->_next;    //fast先走k步
	}
	while (fast)
	{
		slow = slow->_next;
		fast = fast->_next;
	}
	return slow;
}

//11.判断单链表是否带环，求长度、入口点
bool HasCycle(ListNode * pHead)   //求是否带环
{
	ListNode * slow = pHead, *fast = pHead;
	while (fast && fast->_next)
	{
		fast = fast->_next->_next;
		slow = slow->_next;
		if (slow == fast)
		{
			return true;
		}
	}
	return false;
}
ListNode * MeetNode(ListNode * pHead)    //找到快慢指针的相遇点
{
	ListNode * slow = pHead, *fast = pHead;
	while (fast && fast->_next)
	{
		fast = fast->_next->_next;
		slow = slow->_next;
		if (slow == fast)
		{
			return slow;
		}			
	}
	return NULL;
}

int GetCycleLength(ListNode * meetNode)    //求环的长度
{
	ListNode * slow = meetNode->_next, *fast = meetNode->_next->_next;
	int count = 1;
	while (slow != fast)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
		count++;
	}
	return count;
}

ListNode * GetEntryNode(ListNode * pHead, ListNode * meetNode)    //求入口点
{
	while (pHead && meetNode)
	{
		if (pHead == meetNode)
		{
			return pHead;
		}
		pHead = pHead->_next;
		meetNode = meetNode->_next;
	}
	return NULL;
}

//12.判断两个链表是否相交，求交点（假设链表不带环）
bool CheckCross(ListNode * l1, ListNode * l2)   //求尾节点，看是否一样
{
	ListNode * tail1 = l1, *tail2 = l2;
	while (tail1->_next != NULL)
	{
		tail1 = tail1->_next;
	}
	while (tail2->_next != NULL)
	{
		tail2 = tail2->_next;
	}
	if (tail1 == tail2)
	{
		return true;
	}
	return false;
}
ListNode *CrossNode(ListNode * l1, ListNode * l2)   //求交点
{
	ListNode * cur1 = l1, *cur2 = l2;
	ListNode * tail1 = l1, *tail2 = l2;
	int len1 = 0, len2 = 0;
	while (tail1->_next != NULL)       //分别求出单链表长度
	{
		len1++;
		tail1 = tail1->_next;
	}
	while (tail2->_next != NULL)
	{
		len2++;
		tail2 = tail2->_next;
	}
	int x;
	if (len1 > len2)     //若l1长，先走x步
	{
		x = len1 - len2;
		while (x--)
		{
			cur1 = cur1->_next;
		}
	}
	else              //若l2长，先走x步
	{
		x = len2 - len1;
		while (x--)
		{
			cur2 = cur2->_next;
		}
	}
	while (cur1 != cur2)
	{
		cur1 = cur1->_next;
		cur2 = cur2->_next;
	}
	return cur1;
}
//13.判断两个链表是否相交，求交点（假设链表带环）
bool CheckCross1(ListNode * l1, ListNode * l2)
{
	ListNode * meetNode1 = MeetNode(l1);
	ListNode * meetNode2 = MeetNode(l2);
	if (meetNode1 == NULL && meetNode2 == NULL)       //不带环
	{
		ListNode * tail1 = l1, *tail2 = l2;
		while (tail1->_next != NULL)
		{
			tail1 = tail1->_next;
		}
		while (tail2->_next != NULL)
		{
			tail2 = tail2->_next;
		}
		if (tail1 == tail2)
			return true;
		else
			return false;
	}
	if (meetNode1 && meetNode2)         //带环
	{
		ListNode * cur = meetNode1;
		while (cur->_next != meetNode1)
		{
			if (cur == meetNode2)
				return true;
			cur = cur->_next;
		}
		return false;
	}
	return false;
}
ListNode * CrossNode1(ListNode * l1, ListNode * l2)   //求交点
{
	ListNode * meetNode1 = MeetNode(l1);
	ListNode * meetNode2 = MeetNode(l2);
	ListNode * entryNode1 = GetEntryNode(l1, meetNode1);
	ListNode * entryNode2 = GetEntryNode(l2, meetNode2);
	if (entryNode1 == entryNode2)      //入口点一样，说明在入环之前就相交
	{
		entryNode1 = NULL;
		ListNode * crossNode = CrossNode(l1, l2);
		return crossNode;
	}
	else         //入口点不同，说明在环内相交(应有两个交点，现在假设l2交l1)
	{
		return entryNode2;
	}
}

//14.求两个已排序链表中相同的数据
void UnionSet(ListNode* l1, ListNode* l2)
{
	while (l1 && l2)
	{
		if (l1->_data == l2->_data)
		{
			printf("%d  ", l1->_data);
			l1 = l1->_next;
			l2 = l2->_next;		
		}
		else if (l1->_data < l2->_data)
		{
			l1 = l1->_next;
		}
		else
		{
			l2 = l2->_next;
		}
	}
}
