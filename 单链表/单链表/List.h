#include<stdio.h>
#include<assert.h>
#include<malloc.h>

typedef int DataType;
//���嵥����
typedef struct ListNode
{
	DataType _data;    //����
	struct ListNode * _next;   //ָ����һ���ڵ��ָ��
}ListNode;

//��ʼ��
void InitList(ListNode * &pHead)
{
	pHead = NULL;
}

//�����ڵ�
ListNode * BuyNode(DataType x)
{
	ListNode * tmp = (ListNode *)malloc(sizeof(ListNode));
	assert(tmp);
	tmp->_data = x;
	tmp->_next = NULL;
	return tmp;
}

//β��
void PushBack(ListNode * &pHead, DataType x)
{
	if (NULL == pHead)      //Ϊ��ʱ����ʾû�нڵ㣬�����½ڵ�
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode * tail = pHead;
		while (tail->_next != NULL)
		{
			tail = tail->_next;     //��tailָ�����һ���ڵ�
		}
		tail->_next = BuyNode(x);
	}
}

//ͷ��
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

//βɾ
void PopBack(ListNode * &pHead)    //1.Ϊ��  2.һ���ڵ�  3������ڵ�
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
			prevtail = tail;         //��tailָ��β����prevtailָ�����ڶ���
			tail = tail->_next;
		}
		prevtail->_next = NULL;
		free(tail);
	}
}

//ͷɾ
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

//����
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

//����
void Insert(ListNode * &pos, DataType x)    //��pos�ڵ�����
{
	assert(pos);
	ListNode * tmp = BuyNode(x);
	tmp->_next = pos->_next;
	pos->_next = tmp;
}

//ɾ��ĳ�ڵ�
void Erase(ListNode * &pHead, ListNode * pos)
{
	assert(pos);

	if (pos == pHead)    //��Ҫɾ���Ľڵ���ǵ�һ��ʱ��ֱ��ɾ
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

//ɾ������Ϊx�Ľڵ�
void Remove(ListNode * &pHead, DataType x)
{
	if (NULL == pHead)
	{
		printf("List is empty!\n");
		return;
	}
	else
	{
		ListNode * ret = Find(pHead, x);    //��ret����ָ��x���ڽڵ�
		if (ret)
		{
			Erase(pHead, ret);		//ɾ���˽ڵ�
		}
	}
}

//�ͷ�
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

//��ӡ���
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
//////////������������//////////
////////////////////////////////

/*
1.�Ƚ�˳���͵��������ȱ��
   1��˳���֧��������ʣ�������֧�֡�
   2��˳������ / ɾ������Ч�ʺܵͣ�ʱ�临�Ӷ�ΪO(N)����β�塢βɾ��
	   ��������� / ɾ������Ч�ʸߣ�ʱ�临�Ӷ�ΪO(1)��
   3��˳����CPU���ٻ���Ч�ʸ��ߣ��������CPU���ٻ���Ч�ʸ��͡�
*/

//2.��β��ͷ��ӡ������
void PrintTailToHead(ListNode * pHead)
{
	if (pHead)
	{
		PrintTailToHead(pHead->_next);
		printf("%d  <- ", pHead->_data);
	}
}

//3.ɾ��һ����ͷ������ķ�β�ڵ�
void DelNonTailNode(ListNode * pos)
{
	assert(pos && pos->_next);
	pos->_data = pos->_next->_data;
	ListNode * next = pos->_next->_next;
	free(pos->_next);
	pos->_next = next;
}

//�����ڵ�
ListNode * BuyNode(DataType x)
{
	ListNode * tmp = (ListNode *)malloc(sizeof(ListNode));
	assert(tmp);
	tmp->_data = x;
	tmp->_next = NULL;
	return tmp;
}

//4.����ͷ�������һ����ͷ���ǰ����һ���ڵ�
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

//5.������ʵ��Լɪ��
void JosephCycle(ListNode * &pHead, int m)
{
	ListNode* cur = pHead;
	if (cur == NULL)
	{
		return ;
	}
	while (1)
	{
		if (cur == cur->_next)   //ֻʣ��һ���ڵ�
		{
			return ;
		}
		int x = m;
		while (--x)
		{
			cur = cur->_next;
			//�滻������ɾ��
			cur->_data = cur->_next->_data;
			ListNode* del = cur->_next;
			cur->_next = del->_next;
			free(del);
		}
	}
}

//6.����/��ת������
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

//7.����������(ð��)
void SortList(ListNode *pHead)
{
	if (pHead == NULL || pHead->_next == NULL)   //Ϊ�ջ���һ���ڵ�
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
			if (prev->_data > cur->_data)  //ǰ������ݴ��ں�������ݣ�����ֵ
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


//7.����������(ѡ��)
void SelectSort(ListNode * pHead)
{
	ListNode * cur = pHead;
	while (cur)
	{
		ListNode * tmp = cur->_next;
		while (tmp)
		{
			if (cur->_data > tmp->_data)  //��ǰ���ݴ��ں�������ݣ�����ֵ
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

//8.�ϲ��������������ϲ�����Ȼ����
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


//9.���ҵ�������м�ڵ㣬Ҫ��ֻ����һ��
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

//10.���ҵ�����ĵ�����K���ڵ㣬Ҫ��ֻ�ܱ���һ��
ListNode * FindKTailNode(ListNode * pHead, int k)
{
	ListNode * slow = pHead, *fast = pHead;
	while (k--)
	{
		if (fast == NULL)    //û��k��ô��,���ؿ�
		{
			return NULL;
		}
		fast = fast->_next;    //fast����k��
	}
	while (fast)
	{
		slow = slow->_next;
		fast = fast->_next;
	}
	return slow;
}

//11.�жϵ������Ƿ�������󳤶ȡ���ڵ�
bool HasCycle(ListNode * pHead)   //���Ƿ����
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
ListNode * MeetNode(ListNode * pHead)    //�ҵ�����ָ���������
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

int GetCycleLength(ListNode * meetNode)    //�󻷵ĳ���
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

ListNode * GetEntryNode(ListNode * pHead, ListNode * meetNode)    //����ڵ�
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

//12.�ж����������Ƿ��ཻ���󽻵㣨��������������
bool CheckCross(ListNode * l1, ListNode * l2)   //��β�ڵ㣬���Ƿ�һ��
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
ListNode *CrossNode(ListNode * l1, ListNode * l2)   //�󽻵�
{
	ListNode * cur1 = l1, *cur2 = l2;
	ListNode * tail1 = l1, *tail2 = l2;
	int len1 = 0, len2 = 0;
	while (tail1->_next != NULL)       //�ֱ������������
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
	if (len1 > len2)     //��l1��������x��
	{
		x = len1 - len2;
		while (x--)
		{
			cur1 = cur1->_next;
		}
	}
	else              //��l2��������x��
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
//13.�ж����������Ƿ��ཻ���󽻵㣨�������������
bool CheckCross1(ListNode * l1, ListNode * l2)
{
	ListNode * meetNode1 = MeetNode(l1);
	ListNode * meetNode2 = MeetNode(l2);
	if (meetNode1 == NULL && meetNode2 == NULL)       //������
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
	if (meetNode1 && meetNode2)         //����
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
ListNode * CrossNode1(ListNode * l1, ListNode * l2)   //�󽻵�
{
	ListNode * meetNode1 = MeetNode(l1);
	ListNode * meetNode2 = MeetNode(l2);
	ListNode * entryNode1 = GetEntryNode(l1, meetNode1);
	ListNode * entryNode2 = GetEntryNode(l2, meetNode2);
	if (entryNode1 == entryNode2)      //��ڵ�һ����˵�����뻷֮ǰ���ཻ
	{
		entryNode1 = NULL;
		ListNode * crossNode = CrossNode(l1, l2);
		return crossNode;
	}
	else         //��ڵ㲻ͬ��˵���ڻ����ཻ(Ӧ���������㣬���ڼ���l2��l1)
	{
		return entryNode2;
	}
}

//14.��������������������ͬ������
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
