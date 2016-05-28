#include<iostream>
#include<assert.h>
using namespace std;
typedef int DataType;
struct SlistNode
{
	DataType _data;
	SlistNode* _next;

	SlistNode(const DataType&x)
		:_data(x)
		,_next(NULL)
	{}
};

struct Slist
{
	SlistNode* _head;
	SlistNode* _tail;

	Slist()     //构造函数
		:_head(NULL)
		,_tail(NULL)
	{}

	~Slist()   //析构函数
	{ 
		Destroy();
	}

	void Destroy()
	{
		SlistNode* begin = _head;
		while(begin)
		{
			SlistNode* del = begin;
			begin = begin->_next;
			delete del;
		}
		_head = NULL;
		_tail = NULL;
	}

	Slist(const Slist& s)   //拷贝构造
		:_head(NULL)
		,_tail(NULL)
	{
		SlistNode* cur = s._head;
		while(cur)
		{
			if(_tail)
			{
				_tail->_next = new SlistNode(cur->_data);
				_tail = _tail->_next;
			}
			else        //头尾指针为空
			{
				_tail = new SlistNode((cur->_data));
				_head = _tail;
			}
			cur = cur->_next;
		}
	}

	Slist& operator= (Slist s)    //重载=
	{
		_Swap(s);
		return *this;
	}

	void PushBack(const DataType& x)     //尾插
	{
		if(_head == NULL)
		{
			_head = new SlistNode(x);
			_tail = _head;
		}
		else
		{
			_tail->_next = new SlistNode(x);
			_tail = _tail->_next;
		}
	}

	void PopBack()      //尾删
	{
		if(_head == NULL || _tail == NULL)
		{
			return;
		}
		else if(_head->_next == NULL)
		{
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			SlistNode* begin = _head;
			while(begin->_next)
			{
				_tail = begin;
				begin = begin->_next;
			}
			delete _tail->_next;
			_tail->_next = NULL;
		}
	}

	SlistNode* Find(const DataType& x)    //查找
	{
		SlistNode* begin = _head;
		while(begin)
		{
			if(begin->_data == x)
			{
				return begin;
				break;
			}
			begin = begin->_next;
		}
		return NULL;
	}

	void Insert(SlistNode * &pos,const DataType& x)    //在pos节点后插入
	{
		assert(pos);
		SlistNode* next = pos->_next;
		SlistNode* tmp = new SlistNode(x);
		pos->_next = tmp;
		tmp->_next = next;
	}

	void Erase(size_t pos)     //清除某位置数据
	{
		if(pos >= _Size())
		{
			cout<<"要清除的位置有误！"<<endl;
			return;
		}
		SlistNode* cur = _head;
		SlistNode* pre = _head;
		if(_head == NULL)
		{
			cout<<"链表为空！"<<endl;
		}
		else if(_head->_next == NULL)
		{
			SlistNode* tmp = _head;
			delete tmp;
			_head = NULL;
			_tail = NULL;
		}
		else if(pos == 0)
		{
			cur = cur->_next;
			delete _head;
			_head = cur;
		}
		else
		{
			while(pos-- > 0)
			{
				pre = cur;
				cur = cur->_next;
			}
			pre->_next = cur->_next;
			delete cur;
		}
	}


	void Clear()      //清空数据但不释放空间
	{
		SlistNode* cur = _head;
		while(cur)
		{
			cur->_data = NULL;
			cur = cur->_next;
		}

	}


	void _Swap(Slist& s)      //交换
	{
		swap(_head,s._head);
		swap(_tail,s._tail);
	}

	int _Size()
	{
		int count = 0;
		SlistNode* cur = _head;
		while(cur)
		{
			cur = cur->_next;
			count ++;
		}
		return count;
	}

	void Print()         //打印输出
	{
		SlistNode* begin = _head;
		while(begin)
		{
			cout<<begin->_data<<"->";
			begin = begin->_next;
		}
		cout<<"NULL"<<endl;
	}
};
int main()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.Print();
	s1.PopBack();
	s1.Print();


	SlistNode* f1 = s1.Find(3);
	s1.Insert(f1,0);
	s1.Print();
	Slist s2;
	s2.PushBack(1);
	s2.PushBack(2);
	s2.PushBack(3);
	s2.PushBack(4);
	s2.Print();
	
	s2.Erase(0);
	s2.Print();


	return 0;
}