/*
 * File name - LinkList
 * Author - Dormy.X.Cui
 * Date - 2012.11.13
 * Desc -
 * 
 * To make a template queue.
 *
 */

#ifndef _MY_QUEUE_H_
#define _MY_QUEUE_H_

#include <iostream>
#include <stdlib.h>
#include "MyList.h"
#include "MyVector.h"

using namespace std;

/*
 * Class name - MySqQueue
 * Author - CuiXue
 * Updated date - 2012.11.13
 * Desc
 *
 */
template <class Type>
class MySqQueue
{	
private:	// Member vars
	MyVector<Type> m_vec_queue;

	int m_len_of_queue;
	int m_num_of_elem;

	int m_front;
	int m_rear;
	bool isMaxon;

private:	// Kernel
	bool	_destroy();
	bool	_enqueued(Type& elem);
	bool	_dequeue(Type& _out);
	/*
	 * Function name - _isFull()
	 * Param -
	 * Return value - bool
	 * Author - CuiXue
	 * Updated date - 2012.11.13
	 * Desc
	 *
	 * Tools function for :
	 */
	inline bool _isFull()
	{
		if( this->m_front == (this->m_rear + 1) % this->m_len_of_queue &&
			this->m_len_of_queue == this->m_num_of_elem )
			return true;

		return false;
	}

	/*
	 * Function name - _isEmpty()
	 * Param -
	 * Return value - bool
	 * Author - CuiXue
	 * Updated date - 2012.11.13
	 * Desc
	 *
	 * Tools function for :
	 */
	inline bool _isEmpty()
	{
		if( 0 == this->m_num_of_elem )
			return true;

		return false;
	}

	bool	_getFront(Type& _out);
	bool	_getRear(Type& _out);
	bool	_copy(const MySqQueue<Type>& source);

public:		// Interface
	MySqQueue():m_len_of_queue(0), m_num_of_elem(0),
		m_front(-1), m_rear(-1), isMaxon(false){}
	
	MySqQueue(int len, bool is_MAX_switch_on);
	MySqQueue(int len);
	MySqQueue(const MySqQueue<Type>& source);
	MySqQueue<Type>& operator=(const MySqQueue<Type>& source);
	~MySqQueue(){ this->_destroy(); }

	// Operations
	bool	Enqueued(Type& elem);
	Type&	Dequeue();
	bool	IsEmpty();
	bool	IsFull();
	Type&	GetFront();
	Type&	GetRear();

public:	/*********** Access Funcs ***********/	
	inline int GetLength(){ return this->m_len_of_queue; }
};


/*
 * Class name - MySqQueue
 * Author - CuiXue
 * Updated date - 2012.11.13
 * Desc
 *
 */
template <class Type>
class MyListQueue
{
private:	// Member vars
	MyLinkList<Type> m_list_queue;

	int m_len_of_queue;
	int m_num_of_elem;

	int m_front;
	int m_rear;
	bool m_isMaxon;

private:	// Kernel
	bool	_destroy();
	bool	_enqueued(const Type& elem);
	bool	_dequeue(Type& _out);
	bool	_isFull();
	bool	_isEmpty();
	bool	_getFront(Type& _out);
	bool	_getRear(Type& _out);

public:		// Interface
	MyListQueue():m_len_of_queue(0), m_num_of_elem(0),
		m_front(-1), m_rear(-1), m_isMaxon(false){}
	
	MyListQueue(const int& len):m_list_queue(len), m_isMaxon(false){}
	MyListQueue(const int& len, bool _maxon = false):m_list_queue(len), m_isMaxon(_maxon){}
	MyListQueue(const MyListQueue<Type>& source);
	MyListQueue<Type>& operator=(const MyListQueue<Type>& source);
	~MyListQueue(){ this->_destroy(); }

	// Operations
	bool	Enqueued(const Type& elem);
	Type&	Dequeue();
	bool	IsEmpty();
	bool	IsFull();
	Type&	GetFront();
	Type&	GetRear();
};

/*
***********************************************************************
************************* Functions definition*************************/
/*
 * Function name - IsFull()
 * Param -
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc -
 */
template <class Type>
inline bool MySqQueue<Type>::IsFull()
{
	if( !this->_isFull() )
		return false;

	return true;
}

/*
 * Function name - IsEmpty()
 * Param -
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc -
 */
template <class Type>
inline bool MySqQueue<Type>::IsEmpty()
{
	if( !this->_isEmpty() )
		return false;

	return true;
}

/*
 * Function name - _destroy()
 * Param -
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.13
 * Desc
 *
 * Tools function for :
 * 1.Destructor
 * 2.Reset obj
 */
template <class Type>
bool MySqQueue<Type>::_destroy()
{
	if( !this->m_vec_queue.GetFirstPointerAddr() )
	{
		this->m_front = -1;
		this->m_len_of_queue = 0;
		this->m_rear = -1;
		this->m_num_of_elem = 0;
		return true;
	}

	this->m_vec_queue.Reset();
	this->m_front = -1;
	this->m_len_of_queue = 0;
	this->m_rear = -1;
	this->m_num_of_elem = 0;
	this->isMaxon = false;

	return true;
}

/*
 * Function name - _copy
 * Param - const MySqQueue<Type>&
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.13
 * Desc
 *
 * Tools function for :
 * 1.Constructor with copy source
 * 2.Some functions with it by hiding.
 */
template <class Type>
bool MySqQueue<Type>::_copy(const MySqQueue<Type>& source)
{
	/*
	 * Modifying...
	 * this指针转换问题？
	 */
	this->m_front = source.m_front;
	this->m_rear = source.m_rear;
	this->m_len_of_queue = source.m_len_of_queue;
	this->m_num_of_elem = source.m_num_of_elem;
	this->m_vec_queue.Copy(source.m_vec_queue);		// Data copy
	this->isMaxon = source.isMaxon;

	return true;
}

/*
 * Function name - MySqQueue
 * Param - const int&
 * Return value - 
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
MySqQueue<Type>::MySqQueue(int len, bool is_MAX_switch_on = false):m_vec_queue(len)
{
	this->m_len_of_queue = len;
	this->m_num_of_elem = 0;
	this->m_front = -1;
	this->m_rear = -1;

	this->isMaxon = is_MAX_switch_on;
}

/*
 * Function name - MySqQueue
 * Param - int(len)
 * Return value - 
 * Author - CuiXue
 * Updated date - 2012.11.18
 * Desc
 *
 * Tools function for :
 */
template <class Type>
MySqQueue<Type>::MySqQueue(int len):m_vec_queue(len)
{
	this->m_len_of_queue = len;
	this->m_num_of_elem = 0;
	this->m_front = -1;
	this->m_rear = -1;

	this->isMaxon = false;
}

/*
 * Function name - MySqQueue
 * Param - const MySqQueue<Type>&
 * Return value - 
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
MySqQueue<Type>::MySqQueue(const MySqQueue<Type>& source)
{
	this->m_front = -1;
	this->m_rear = -1;

	if( !this->_copy(source) )
	{
		throw exception("An error");
		exit(0);
	}
}

/*
 * Function name - operator=
 * Param - const MySqQueue<Type>&
 * Return value - MySqQueue
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
MySqQueue<Type>& MySqQueue<Type>::operator=(const MySqQueue<Type>& source)
{
	if( !this->_copy(source) )
	{
		throw exception("An error");
		exit(0);
	}
}

/*
 * Function name - _enqueued
 * Param - const Type&(elem)
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
bool MySqQueue<Type>::_enqueued(Type& elem)
{
	if( this->isMaxon )
	{
		if( this->IsFull() )
		{
			throw out_of_range("Out of range");
			return false;
		}

		if( -1 == this->m_front )
			this->m_front = 0;

		this->m_rear = (this->m_rear + 1) % this->m_len_of_queue;
		this->m_vec_queue[this->m_rear] = elem;
		this->m_num_of_elem++;

		return true;
	}

	if( -1 == this->m_front )
		this->m_front = 0;

	if( this->m_num_of_elem == this->m_len_of_queue )
	{
		this->m_len_of_queue++;
		this->m_num_of_elem++;
		this->m_rear = (this->m_rear + 1) % this->m_len_of_queue;
		this->m_vec_queue.Insert(this->m_vec_queue.GetMyVectorLength(), elem);
		return true;
	}

	else
	{
		this->m_vec_queue[this->m_num_of_elem] = elem;
		this->m_num_of_elem++;
		this->m_rear++;
	}

	return true;
}

/*
 * Function name - Enqueued
 * Param - const Type&(elem)
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
bool MySqQueue<Type>::Enqueued(Type& elem)
{
	if( !this->_enqueued(elem) )
		return false;

	return true;
}

/*
 * Function name - _dequeue
 * Param - Type& _out
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
bool MySqQueue<Type>::_dequeue(Type& _out)
{
	if( this->IsEmpty() )
		return false;

	if( this->isMaxon )
	{
		_out = this->m_vec_queue[this->m_front];
		this->m_front = (this->m_front + 1) % this->m_len_of_queue;
		this->m_num_of_elem--;
		return true;
	}

	_out = this->m_vec_queue[0];
	this->m_vec_queue.Remove(0);
	this->m_len_of_queue--;
	this->m_num_of_elem--;
	return true;
}

/*
 * Function name -Dequeue
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
Type& MySqQueue<Type>::Dequeue()
{
	static Type _return;
	if( !this->_dequeue(_return) )
		throw exception("An error");

	return _return;
}

/*
 * Function name - _getFront
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
inline bool MySqQueue<Type>::_getFront( Type& _out )
{
	if( !this->m_len_of_queue ||
		!this->m_num_of_elem )
		return false;

	if( this->isMaxon )
	{
		_out = this->m_vec_queue[this->m_front];
		return true;
	}

	_out = this->m_vec_queue[0];
	return true;
}

/*
 * Function name - GetFront
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Interface - get first element of queue.
 */
template <class Type>
inline Type& MySqQueue<Type>::GetFront()
{
	static Type _return;
	if( !this->_getFront(_return) )
		throw exception("An error");

	return _return;
}

/*
 * Function name - _getRear
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Tools function for :
 */
template <class Type>
inline bool MySqQueue<Type>::_getRear(Type& _out)
{
	if( !this->m_len_of_queue ||
		!this->m_num_of_elem )
		return false;

	if( this->isMaxon )
	{
		_out = this->m_vec_queue[this->m_rear];
		return true;
	}

	_out = this->m_vec_queue[this->m_num_of_elem - 1];
	return true;
}

/*
 * Function name - GetRear
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.14
 * Desc
 *
 * Interface - Get last element of queue.
 */
template <class Type>
inline Type& MySqQueue<Type>::GetRear()
{
	static Type _return;
	if( !this->_getRear(_return) )
		throw exception("An error");

	return _return;
}

/*
 **********************************************************************
 ***************************** List Queue *****************************/
/*
 * Function name - _isEmpty()
 * Param - 
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Tools for interface -
 */
template <class Type>
inline bool MyListQueue<Type>::_isEmpty()
{
	if( 0 == this->m_num_of_elem )
		return true;

	return false;
}

/*
 * Function name - _isFull()
 * Param - 
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Tools for interface -
 */
template <class Type>
bool MyListQueue<Type>::_isFull()
{
	if( this->m_isMaxon )
		if( this->m_num_of_elem == this->m_len_of_queue )
			return true;

	return false;
}

/*
 * Function name - MyListQueue
 * Param - const MyListQueue&(source)
 * Return value - 
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Construtor with copy source
 */
template <class Type>
MyListQueue<Type>::MyListQueue(const MyListQueue<Type>& source):
	m_list_queue(source.m_list_queue)
{
	if( !source.m_list_queue._getlength() )
	{
		throw exception("An error");
		exit(0);
	}
	
	this->m_front = source.m_front;
	this->m_rear = source.m_rear;
	this->m_len_of_queue = source.m_len_of_queue;
	this->m_num_of_elem = source.m_num_of_elem;
}

/*
 * Function name - operator=
 * Param - const MyListQueue&(source)
 * Return value - MyListQueue<Type>&
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Overload operator '='
 */
template <class Type>
MyListQueue<Type>& MyListQueue<Type>::operator=(const MyListQueue<Type>& source)
{
	if( !source.m_list_queue._getlength() )
	{
		throw exception("An error");
		exit(0);
	}

	this->m_front = source.m_front;
	this->m_rear = source.m_rear;
	this->m_len_of_queue = source.m_len_of_queue;
	this->m_num_of_elem = source.m_num_of_elem;
	
	if( !this->m_list_queue.Copy(source.m_list_queue))
	{
		throw exception("An error");
		exit(0);
	}

	return *this;
}

/*
 * Function name - _destroy()
 * Param - 
 * Return value - 
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Tools for interface -
 */
template <class Type>
bool MyListQueue<Type>::_destroy()
{
	this->m_list_queue.Reset();
	this->m_len_of_queue = 0;
	this->m_num_of_elem = 0;
	this->m_front = -1;
	this->m_rear = -1;

	return true;
}

/*
 * Function name - _enqueued
 * Param - const Type&(elem)
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Tools for interface -
 */
template <class Type>
bool MyListQueue<Type>::_enqueued(const Type& elem)
{
	if( this->m_isMaxon )
	{
		if( this->_isFull() )
			return false;

		if( -1 == this->m_front )
			this->m_front = 0;

		this->m_num_of_elem++;
		this->m_rear++;
		
		if( !this->m_list_queue.Pushback(elem) )
			return false;

		return true;
	}

	else
	{
		if( -1 == this->m_front )
			this->m_front = 0;

		this->m_list_queue.Pushback(elem);
		this->m_rear++;
		this->m_num_of_elem++;
		this->m_len_of_queue++;

		return true;
	}
}

/*
 * Function name - Enqueued
 * Param - const Type&(elem)
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Interface - Enqueued()
 */
template <class Type>
bool MyListQueue<Type>::Enqueued(const Type& elem)
{
	if( !this->_enqueued(elem) )
		return false;
	
	return true;
}

/*
 * Function name - _dequeue
 * Param - Type&(_out)
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Interface - Enqueued()
 */
template <class Type>
bool MyListQueue<Type>::_dequeue(Type& _out)
{
	if( this->_isEmpty() )
		return false;
	
	_out = this->m_list_queue[0];
	if( !this->m_list_queue.Remove(0) )
		return false;

	if( this->m_isMaxon )
		this->m_num_of_elem--;


	else{
		this->m_num_of_elem--;
		this->m_len_of_queue--;
	}

	return true;
}

/*
 * Function name - Dequeue
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Interface - Dequeue()
 */
template <class Type>
Type& MyListQueue<Type>::Dequeue()
{
	static Type _return;
	if( !this->_dequeue(_return) )
	{
		throw exception("An error");
		exit(0);
	}

	return _return;
}

/*
 * Function name - IsEmpty
 * Param - 
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Interface - IsEmpty()
 */
template <class Type>
bool MyListQueue<Type>::IsEmpty()
{
	if( this->_isEmpty() )
		return true;

	return false;
}

/*
 * Function name - IsFull
 * Param - 
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Interface - IsFull()
 */
template <class Type>
bool MyListQueue<Type>::IsFull()
{
	if( this->_isFull() )
		return true;
	
	return false;
}

/*
 * Function name - _getFront
 * Param - Type&(_out)
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Tools for interface - GetFront()
 */
template <class Type>
bool MyListQueue<Type>::_getFront(Type& _out)
{
	if( this->_isEmpty() )
	{
		throw exception("No elements");
		return false;
	}

	_out = this->m_list_queue[0];
	return true;
}

/*
 * Function name - GetFront
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Interface - GetFront()
 */
template <class Type>
Type& MyListQueue<Type>::GetFront()
{
	static Type _return;
	if( !this->_getFront(_return) )
		return false;

	return true;
}

/*
 * Function name - _getRear
 * Param - Type&(_out)
 * Return value - bool
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Tools for interface - GetRear()
 */
template <class Type>
bool MyListQueue<Type>::_getRear(Type& _out)
{
	if( this->_isEmpty() )
	{
		throw exception("No elements");
		return false;
	}

	_out = this->m_list_queue[this->m_len_of_queue - 1];
	return true;
}

/*
 * Function name - GetRear
 * Param - 
 * Return value - Type&
 * Author - CuiXue
 * Updated date - 2012.11.19
 * Desc
 *
 * Interface - GetRear()
 */
template <class Type>
Type& MyListQueue<Type>::GetRear()
{
	static Type _return;
	if( !this->_getRear(_return) )
	{
		throw exception("An error");
		exit(0);
	}

	return _return;
}
//bool	_destroy();
//bool	_enqueued(const Type& elem);
//bool	_dequeue();
//bool	_isFull();
//bool	_isEmpty();
//bool	_getFront(Type& _out);
//bool	_getRear(Type& _out);


#endif