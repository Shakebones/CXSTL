/*
 * File name - LinkList
 * Author - Dormy.X.Cui
 * Date - 2012.11.19
 * Desc -
 * 
 * To make a template linklist.
 *
 * MODIFYING...
 * WARNING : Any function should use temp-ptr for protecting 
 * original ptr(head & tail)
 *
 * Here is something to explain, that is according to C++ STL
 * features, we must define all the template member functions
 * all in one file (this file), which all declaration is also
 * in this file.
 */
#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include <iostream>
#include <stdlib.h>

using namespace std;

/*
 * Class - MyLinkList
 * Author - CuiXue
 * Date - 2012.10.29
 * Desc - Template link container.
 */
template <class Type>
class MyLinkList
{
private:
	/*
	 * Class - Node
	 * Author - CuiXue
	 * Date - 2012.10.29
	 * Desc - Node for link-list
	 * MODIFYING...
	 */
	template <class Type> 
	class Node
	{
	public:
		Type data;
		Node *pNext;
		Node *pFront;

		Node(const Node &T):Data(T), pNext(0), pFront(0){}
		Node():pNext(0), pFront(0){}
		~Node(void)
		{			
			this->pFront = NULL;
			this->pNext = NULL;
		}
	};

public:
	MyLinkList();
	MyLinkList(int len);
	MyLinkList(const MyLinkList &t);

	/*
	 * Function name - operator=
	 * Param - const Type &t
	 * Return value - MyLinkList&
	 * Author - CuiXue
	 * Date - 2012.10.28
	 * Desc - Redefine '=' operator.
	 */
	MyLinkList& operator=(const MyLinkList& T)
	{
		MyLinkList<Type>* temp = NULL;
		if( !T.head || (0 == T.length) )
			return *temp;

		if( T.length > this->length )
		{
			this->_destroy();
			this->_resize(T.length);
		}

		Node<Type>* temp1 = T.head;
		Node<Type>* temp2 = this->head;
		this->length = T.length;	

		while( NULL != temp2 )
		{
			/*
			 * Descriptoin : 
			 * 这里要求用户自定义类型必须重载 ‘=’ 运算符才能
			 * 使用MyLinkList类的复制构造函数，修改中………………
			 */
			temp2->data = temp1->data;
			temp2 = temp2->pNext;
			temp1 = temp1->pNext;
		}

		return *this;
	}

	~MyLinkList();

	/******** Functions ********/
	inline Type& operator[](int pos){

		if( pos >= this->length )
			exit(0);

		Node<Type>* temp = this->head;
		int i = 0;

		while( i != pos )
		{
			temp = temp->pNext;
			i++;
		}

		return temp->data;
	}

	bool Insert(int pos, const Type& data);
	bool Remove(int pos);
	bool Join(const MyLinkList<Type>& tar, MyLinkList<Type>& out);
	bool Pushback(const Type& data);
	bool Copy(const MyLinkList<Type>& source);
	void Reset();

	// BAN
	void TestPrint();

	/******** Access-Functions & Tools ********/
	inline int _getlength(){ return this->length; }
	inline Node<Type>* _gethead() { return this->head; }
	inline Node<Type>* _gettail() { return this->tail; }
	bool _resize(int);

private:
	Node<Type>* head;
	Node<Type>* tail;
	int length;

	void _destroy();
	bool _push_back(const Type& data);
	bool _insert(int pos, const Type& elem);
	bool _delete(int pos);
	bool _join(const MyLinkList<Type>& tar, 
					 MyLinkList<Type>& out);
	bool _reset();
	bool _copy_data(const MyLinkList<Type>&);
};

// TEST FUNC
template <class Type>
void MyLinkList<Type>::TestPrint()
{
	Node<Type>* temp1 = this->head;
	Node<Type>* temp2 = this->tail;
	cout << "\n测试指向下一节点指针" << endl;
	while( NULL != temp1 )
	{
		cout << "\nData -- " << temp1->data << endl;
		temp1 = temp1->pNext;
	}

	cout << "\n测试指向上一节点指针" << endl;
	while( NULL != temp2 )
	{
		cout << "\nData -- " << temp2->data << endl;
		temp2 = temp2->pFront;
	}
}

/*
 * Function name - _reset()
 * Param - 
 * Author - CuiXue
 * Date - 2012.11.2
 * Desc - Tools for interface 'Reset()'
 *
 * 1. Destroy all the list
 * 2. Create new head
 * 3. Length = 1
 */
template <class Type>
bool MyLinkList<Type>::_reset()
{
	this->_destroy();

	Node<Type>* temp = new Node<Type>;
	if( !temp )
	{
		throw out_of_range("No more space to supply");
		exit(0);
	}

	temp->pFront = NULL;
	temp->pNext = NULL;
	this->head = temp;
	this->tail = temp;
	temp = NULL;

	this->length = 1;

	return true;
}

/*
 * Function name - Reset
 * Param - 
 * Return type - 
 * Author - CuiXue
 * Date - 2012.11.2
 * Desc - Interface - Reset
 *
 * 1. Destroy all the list
 * 2. Create new head
 * 3. Length = 1
 */
template <class Type>
void MyLinkList<Type>::Reset()
{
	if( !this->_reset() )
		throw exception("Error ");
}

/*
 * Function name - _copy_data
 * Param - const MyLinkList<Type>&
 * Author - CuiXue
 * Date - 2012.11.2
 * Desc - Copy data from a nother linklist
 */
template <class Type>
bool MyLinkList<Type>::_copy_data(const MyLinkList<Type>& source)
{
	/*
	* Warning...
	* Memory copy !
	*/
	MyLinkList<Type>* temp = NULL;
	if( !source.head || (0 == source.length) )
		return false;

	if( source.length > this->length )
	{
		this->_destroy();
		this->_resize(source.length);
	}

	Node<Type>* temp1 = source.head;
	Node<Type>* temp2 = this->head;
	this->length = source.length;	

	while( NULL != temp2 )
	{
		/*
		* Descriptoin : 
		* 这里要求用户自定义类型必须重载 ‘=’ 运算符才能
		* 使用MyLinkList类的复制构造函数，修改中………………
		*/
		temp2->data = temp1->data;
		temp2 = temp2->pNext;
		temp1 = temp1->pNext;
	}

	return true;
}

/*
 * Function name - MyLinkList
 * Param - 
 * Return value -
 * Author - CuiXue
 * Date - 2012.10.28
 * Desc - Initialize member vars.
 */
template <class Type>
MyLinkList<Type>::MyLinkList()
{
	this->head = NULL;
	this->tail = NULL;

	this->length = 0;
}

/*
 * Function name - MyLinkList
 * Param - int(len)
 * Return value -
 * Author - CuiXue
 * Date - 2012.10.28
 * Desc - According to param initialize member vars.
 */
template <class Type>
MyLinkList<Type>::MyLinkList(int len)
{
	if( 0 >= len )
		exit(0);

	this->length = len;
	Node<Type>* ptr1 = NULL;	// Note the node before ptr2
	Node<Type>* ptr2 = NULL;	// Note tail & now node

	for( int i = 0; i < this->length; i++ )
	{
		if( NULL != ptr1 )
		{
			ptr2 = new Node<Type>;
			if( !ptr2 )
				exit(0);
			ptr2->pFront = ptr1;
			ptr1->pNext = ptr2;
			ptr2->pNext = NULL;
			ptr1 = ptr2;
			this->tail = ptr2;
			ptr2 = NULL;
		}

		else
		{
			ptr2 = new Node<Type>;
			if( !ptr2 )
				exit(0);

			this->head = ptr2;
			ptr1 = ptr2;
			ptr2->pNext = NULL;
			ptr2->pFront = NULL;
			ptr2 = NULL;
		}
	}

	ptr1 = NULL;
}

/*
 * Function name - _resize
 * Param - const int &
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.10.29
 * Desc - Copy constructor
 */
template <class Type>
bool MyLinkList<Type>::_resize(int len)
{
	if( NULL != this->head )
		this->_destroy();

	if( 0 >= len )
		exit(0);

	this->length = len;
	Node<Type>* ptr1 = NULL;	// Note the node before ptr2
	Node<Type>* ptr2 = NULL;	// Note tail & now node

	for( int i = 0; i < this->length; i++ )
	{
		if( NULL != ptr1 )
		{
			ptr2 = new Node<Type>;
			if( !ptr2 )
				return false;

			ptr2->pFront = ptr1;
			ptr1->pNext = ptr2;
			ptr2->pNext = NULL;
			ptr1 = ptr2;
			this->tail = ptr2;
			ptr2 = NULL;
		}

		else
		{
			this->head = new Node<Type>;
			if( !this->head )
				return false;

			ptr2 = this->head;
			ptr1 = ptr2;
			ptr2->pNext = NULL;
			ptr2->pFront = NULL;
		}
	}

	return true;
}

/*
 * Function name - MyLinkList
 * Param - const Type &t
 * Return value -
 * Author - CuiXue
 * Date - 2012.10.28
 * Desc - Copy constructor
 */
template <class Type>
MyLinkList<Type>::MyLinkList(const MyLinkList &t)
{
	this->head = NULL;
	this->length = 0;

	this->_resize(t.length);

	Node<Type>* temp1 = t.head;
	Node<Type>* temp2 = this->head;
	this->length = t.length;	

	while( NULL != temp2 )
	{
		/*
		 * Descriptoin : 
		 * 这里要求用户自定义类型必须重载 ‘=’ 运算符才能
		 * 使用MyLinkList类的复制构造函数，修改中………………
		 */
		temp2->data = temp1->data;
		temp2 = temp2->pNext;
		temp1 = temp1->pNext;
	}
}

/*
 * Function name - ~MyLinkList
 * Param - 
 * Return value -
 * Author - CuiXue
 * Date - 2012.10.28
 * Desc - Destructor
 */
template <class Type>
MyLinkList<Type>::~MyLinkList()
{
	this->_destroy();
}

/*
 * Function name - _destroy()
 * Param - 
 * Return value - void
 * Author - CuiXue
 * Date - 2012.10.29
 * Desc - Called in destructor
 */
template <class Type>
void MyLinkList<Type>::_destroy()
{
	if( NULL == this->head )
		return;

	Node<Type>* temp = this->head;
	Node<Type>* beforeTemp = NULL;

	while( temp != NULL )
	{
		beforeTemp = temp;
		temp = temp->pNext;
		delete beforeTemp;
		beforeTemp = NULL;
	}

	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}

/*
 * Function name - _insert()
 * Param - int pos
 * Return value - void
 * Author - CuiXue
 * Date - 2012.10.31
 * Desc - Tools for interface 'Insert()'
 */
template <class Type>
bool MyLinkList<Type>::_insert(int pos, const Type& elem)
{
	if( pos < 0 ||
		pos > this->length)
		return false;

	if( !this->head )
	{
		Node<Type>* temp = new Node<Type>;
		if( !temp )
		{
			throw exception("No more space");
			return false;
		}

		temp->data = elem;
		temp->pNext = NULL;
		temp->pFront = NULL;
		this->head = temp;
		this->tail = temp;
		temp = NULL;

		this->length++;
		return true;
	}

	Node<Type>* temp1 = this->head;			// Move to pos
	Node<Type>* temp2 = NULL;				// New node

	if( 0 == pos )
	{
		temp2 = new Node<Type>;
		if( !temp2 )
		{
			throw exception("No more space");
			return false;
		}

		temp2->data = elem;
		temp2->pNext = temp1;
		temp2->pFront = temp1->pFront;
		temp1->pFront = temp2;
		this->head = temp2;
		this->length++;
		temp1 = NULL;
		temp2 = NULL;
		return true;
	}

	if( pos == this->length )
	{
		temp2 = new Node<Type>;
		if( !temp2 )
		{
			throw exception("No more space");
			return false;
		}

		temp2->pNext = NULL;
		temp2->pFront = this->tail;
		this->tail->pNext = temp2;
		this->tail = temp2;
		this->length++;
		return true;
	}

	int i = 0;
	while(i <= pos)
	{
		if( i == pos )
		{
			temp2 = new Node<Type>;
			if( !temp2 )
				return false;

			temp2->data = elem;
			temp2->pFront = temp1->pFront;
			temp1->pFront->pNext = temp2;
			temp2->pNext = temp1;
			temp1->pFront = temp2;
			this->length++;

			temp2 = NULL;
			temp1 = NULL;
			break;
		}

		i++;
		temp1 = temp1->pNext;
	}

	return true;
}

/*
 * Function name - Insert
 * Param - int pos
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.10.31
 * Desc - Interface - Insert()
 */
template <class Type>
bool MyLinkList<Type>::Insert(int pos, const Type& data)
{
	if( !this->_insert(pos, data) )
		return false;

	return true;
}

/*
 * Function name - _delete
 * Param - int pos
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.11.1
 * Desc - Tools for interface 'Remove()'.
 */
template <class Type>
bool MyLinkList<Type>::_delete(int pos)
{
	if( pos >= this->length ||
		pos < 0 )
		return false;

	Node<Type>* temp1 = this->head;
	Node<Type>* temp2 = NULL;
	int i = 0; 

	while( i != pos )
	{
		temp1 = temp1->pNext;
		i++;
	}

	if( 0 == pos )
	{
		// When this position's element is last one.
		if( NULL == temp1->pNext )
		{
			delete temp1;
			temp1 = NULL;
			this->head = temp1;
			this->length--;
			return true;
		}

		this->head = temp1->pNext;
		temp1->pNext->pFront = NULL;
		delete temp1;
		temp1 = NULL;
		this->length--;
		return true;
	}

	if( pos == this->length - 1 )
	{
		// When this position's element is last one.
		if( NULL == temp1->pFront )
		{
			delete temp1;
			temp1 = NULL;
			this->length--;
			return true;
		}

		temp1->pFront->pNext = NULL;
		this->tail = temp1->pFront;
		delete temp1;
		temp1 = NULL;
		this->length--;
		return true;
	}

	temp1->pFront->pNext = temp1->pNext;
	temp1->pNext->pFront = temp1->pFront;
	delete temp1;
	temp1 = NULL;

	return true;
}

/*
 * Function name - Remove
 * Param - int pos
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.11.1
 * Desc - Interface - Remove()
 */
template <class Type>
bool MyLinkList<Type>::Remove(int pos)
{
	if( !this->_delete(pos) )
		return false;

	return true;
}

/*
 * Function name - Join
 * Param - const MyLinkList&
 * Return value - MyLinkList&
 * Author - CuiXue
 * Date - 2012.11.1
 * Desc - Tools for interface 'Join()'
 */
template <class Type>
bool MyLinkList<Type>::_join(const MyLinkList<Type>& tar,
								   MyLinkList<Type>& out)
{
	if( !tar.head ||
		!tar.length )
		return false;

	MyLinkList<Type> temp(this->length + tar.length);
	Node<Type>* tempHead = temp.head;
	Node<Type>* tempThisHead = this->head;
	Node<Type>* tempTarHead = tar.head;

	for(int i = 0; i < temp._getlength(); i++)
	{
		if( i < this->length )
		{
			tempHead->data = tempThisHead->data;
			tempHead = tempHead->pNext;
			tempThisHead = tempThisHead->pNext;
		}

		else
		{
			tempHead->data = tempTarHead->data;
			tempTarHead = tempTarHead->pNext;
			tempHead = tempHead->pNext;
		}
	}

	out._destroy();
	out = temp;
	temp.head = NULL;

	return true;
}

/*
 * Function name - Join
 * Param - const MyLinkList<Type>&
		   (out param) MyLinkList<Type>&
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.11.2
 * Desc - Interface - Join()
 */
template <class Type>
bool MyLinkList<Type>::Join(const MyLinkList<Type>& tar,
								  MyLinkList<Type>& out)
{
	if( !this->_join(tar, out) )
		return false;

	return true;
}

/*
 * Function name - _push_back
 * Param - const Type&(data)
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.11.18
 * Desc - Tools for interface - Pushback()
 */
template <class Type>
bool MyLinkList<Type>::_push_back(const Type& data)
{
	if( !this->head )
	{
		Node<Type>* temp = new Node<Type>;
		if( !temp )
		{
			throw exception("No more space");
			return false;
		}

		temp->data = data;
		temp->pNext = NULL;
		temp->pFront = NULL;
		this->head = temp;
		this->tail = temp;
		temp = NULL;

		this->length++;
		return true;
	}

	Node<Type>* temp1;
	temp1 = new Node<Type>;
	if( !temp1 )
	{
		throw exception("No more space");
		exit(0);
	}

	temp1->data = data;
	temp1->pFront = this->tail;
	this->tail->pNext = temp1;
	this->length++;
	this->tail = temp1;

	temp1 = NULL;
	return true;
}

/*
 * Function name - Pushback
 * Param - const Type&(data)
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.11.18
 * Desc - Interface - Pushback()
 */
template <class Type>
bool MyLinkList<Type>::Pushback(const Type& data)
{
	if( !this->_push_back(data) )
		return false;

	return true;
}

/*
 * Function name - Copy
 * Param - const Type&(data)
 * Return value - bool
 * Author - CuiXue
 * Date - 2012.11.19
 * Desc - Interface - Copy
 */
template <class Type>
bool MyLinkList<Type>::Copy(const MyLinkList<Type>& source)
{
	if( !this->_copy_data(source) )
		return false;

	return true;
}
#endif