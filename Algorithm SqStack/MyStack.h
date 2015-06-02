/*
 * File name - MyStack
 * Author - Dormy.X.Cui
 * Date - 2012.11.4
 * Desc -
 * 
 * To make a template Stack.
 *
 * PS - There will be a 2 typew of stack
 * one is use 'MyLinkList', and another 
 * is by 'MyVector'.
 */
#ifndef _MY_STACK_H_
#define _MY_STACK_H_

#include <iostream>
#include <stdlib.h>
#include "MyVector.h"

/*
 * Class - MySqStack
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - By 'MyVector'.
 */
template <class Type>
class MySqStack
{
private:
	MyVector<Type> _stack_container;
	int _top_ptr;
	int _capacity;
	int _num_of_elem;

	bool _is_max_available;

	/*
	********************************
	************ Kernel ************/
private:
	bool	_push(const Type& data);
	bool	_pop(Type& _out);
	bool	_empty();
	bool	_getTop(Type& _out);
	bool	_get_capacity(int _out);
	bool	_destroy();
	bool	_setMAX(int MAX);

public:
	MySqStack();
	MySqStack(int _capacity);
	MySqStack(const MySqStack<Type>& source);
	MySqStack<Type>& operator=(const MySqStack<Type>& source);
	~MySqStack();

	/*
	***********************
	****** Interface ******/
	void	Push(const Type &data);
	Type&	Pop(void);
	void	Empty(void);
	Type&	GetTop();

	// Modifying
	inline int		GetCapacity(){ return this->_capacity; }

	//该函数已被禁用（待处理）
	//void			SetMAX(int MAX);
};


/*
***********************************************************************
************************* Functions definition*************************/
/*
 * Function name - MySqStack
 * Param - 
 * Return type - 
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Constructor
 */
template <class Type>
MySqStack<Type>::MySqStack()
{
	this->_top_ptr = -1;
	this->_capacity = 0;
	this->_num_of_elem = 0;
	this->_is_max_available = false;
}

/*
 * Function name - MySqStack
 * Param - int(length)
 * Return type - 
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Constructor with param
 */
template <class Type>
MySqStack<Type>::MySqStack(int _capacity)
{
	this->_stack_container.Recreate(_capacity);
	this->_capacity= _capacity;
	this->_is_max_available = true;
	this->_top_ptr = 0;
	this->_num_of_elem = 0;
}

/*
 * Function name - MySqStack
 * Param - const MySqStack<Type>& source
 * Return type - 
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Constructor of copy
 */
template <class Type>
MySqStack<Type>::MySqStack(const MySqStack<Type>& source)
{
	if( this->_capacity < source._capacity )
	{
		this->_stack_container.Recreate(source._capacity);
		this->_stack_container.Copy(source._stack_container);
		this->_capacity = source._capacity;
		this->_num_of_elem = source._num_of_elem;
		this->_top_ptr = source._top_ptr;
	}

	else
	{
		this->_stack_container.Copy(source._stack_container);
		this->_capacity = source._capacity;
		this->_num_of_elem = source._num_of_elem;
		this->_top_ptr = source._top_ptr;
	}
}

/*
 * Function name - operator=
 * Param - const MySqStack<Type>& source
 * Return type - MySqStack<Type>
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Overload operator '='
 */
template <class Type>
MySqStack<Type>& MySqStack<Type>::operator=(const MySqStack<Type>& source)
{
	if( this->_capacity < source._capacity )
	{
		this->_stack_container.Recreate(source._capacity);
		this->_stack_container.Copy(source._stack_container);
		this->_capacity = source._capacity;
		this->_num_of_elem = source._num_of_elem;
		this->_top_ptr = source._top_ptr;
		return *this;
	}

	this->_stack_container.Copy(source._stack_container);
	this->_capacity = source._capacity;
	this->_num_of_elem = source._num_of_elem;
	this->_top_ptr = source._top_ptr;

	return *this;
}

/*
 * Function name - _destroy()
 * Param - 
 * Return type - bool
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Tools for destructor.
 */
template <class Type>
bool MySqStack<Type>::_destroy()
{
	if( NULL != this->_stack_container.GetFirstPointerAddr() )
		this->_stack_container.Reset();

	this->_capacity = 0;
	this->_num_of_elem = 0;
	
	return true;
}

/*
 * Function name - ~MySqStack
 * Param - 
 * Return type - 
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Destructor.
 */
template <class Type>
MySqStack<Type>::~MySqStack()
{
	if( !this->_destroy() )
		throw exception("An error");
}

/*
 * Function name - _push
 * Param - const Type&(data)
 * Return type - bool
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Tools for interface 'Push()'
 */
template <class Type>
bool MySqStack<Type>::_push(const Type& data)
{
	if( this->_is_max_available )
	{
		bool flag =	(this->_num_of_elem + 1) > this->_capacity;

		if( !this->_stack_container.Pushback(data) || flag )
			return false;

		this->_top_ptr++;
		this->_num_of_elem++;
		return true;
	}

	if( !this->_stack_container.Pushback(data) )
		return false;

	this->_top_ptr++;
	this->_num_of_elem++;
	this->_capacity = this->_stack_container.GetMyVectorCapacity();

	return true;
}

/*
 * Function name - Push
 * Param - const Type&(data)
 * Return type - void
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Interface 'Push()'
 */
template <class Type>
void MySqStack<Type>::Push(const Type& data)
{
	if( !this->_push(data) )
		throw exception("An error");
}

/*
 * Function name - _pop
 * Param - Type& _out
 * Return type - bool
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Tools for interface 'Pop()'
 */
template <class Type>
bool MySqStack<Type>::_pop(Type& _out)
{
	if( this->_top_ptr == -1 )
		return false;

	if( this->_is_max_available )
	{
		_out = this->_stack_container[this->_top_ptr];
		this->_top_ptr--;
		this->_num_of_elem--;
		return true;
	}

	_out = this->_stack_container[this->_top_ptr];
	this->_capacity = this->_stack_container.GetMyVectorCapacity();
	this->_num_of_elem--;
	this->_top_ptr--;

	return true;
}

/*
 * Function name - Pop
 * Param - 
 * Return type - Type&
 * Author - CuiXue
 * Date - 2012.11.6
 * Desc - Interface 'Pop()'
 */
template <class Type>
Type& MySqStack<Type>::Pop()
{
	// 我的顾虑：
	// 1.其他文件中是否可以访问这个全局静态变量？
	// 2.通过这个变量有没有可能破坏到栈中的数据？
	// 3.这个变量的生命期？
	static Type t;
	if( !this->_pop(t) )
		throw out_of_range("An error");

	return t;
}

/*
 * Function name - _empty
 * Param - 
 * Return type - bool
 * Author - CuiXue
 * Date - 2012.11.7
 * Desc - Tools for interface 'Empty()'
 */
template <class Type>
bool MySqStack<Type>::_empty()
{
	if( !this->_stack_container.GetFirstPointerAddr() )
	{
		throw exception("An error");
		return false;
	}

	this->_stack_container.Reset();
	this->_capacity = 0;
	this->_num_of_elem = 0;
	this->_top_ptr = -1;

	return true;
}

/*
 * Function name - Empty
 * Param - 
 * Return type - void
 * Author - CuiXue
 * Date - 2012.11.7
 * Desc - Interface 'Empty()'
 */
template <class Type>
void MySqStack<Type>::Empty()
{
	if( !this->_empty() )
		return;
}

/*
 * Function name - _getTop
 * Param - Type&(_out)
 * Return type - bool
 * Author - CuiXue
 * Date - 2012.11.7
 * Desc - Tools for interface 'GetTop()'
 */
template <class Type>
bool MySqStack<Type>::_getTop(Type& _out)
{
	if( !this->_stack_container.GetFirstPointerAddr() )
		return false;

	_out = this->_stack_container[this->_top_ptr];

	return true;
}

/*
 * Function name - GetTop
 * Param - 
 * Return type - Type&
 * Author - CuiXue
 * Date - 2012.11.7
 * Desc - Interface 'GetTop()'
 */
template <class Type>
Type& MySqStack<Type>::GetTop()
{
	static Type t;
	Type*		error = NULL;
	if( !this->_getTop(t) )
		return *error;

	return t;
}

/*
 * Function name - _setMAX
 * Param - int(MAX)
 * Return type - bool
 * Author - CuiXue
 * Date - 2012.11.7
 * Desc - Tools for interface 'SetMAX()'
 * 
 * 我的顾虑：
 * 1.设置的MAX值小于当前的capacity（需要截断处理）
 * 2.禁止用户设置一个比当前栈容量更小的值是否合理？
 * 3.自己增加vector功能 —— 使用迭代器标记需要被复制
 *   的元素段
 * 
 * PS：该函数被禁用，为完成预期功能尚不开放
 */
//template <class Type>
//bool MySqStack<Type>::_setMAX(int MAX)
//{
//	if( MAX == this->_capacity )
//		return true;
//
//	MyVector<Type> temp;
//	temp.Copy(this->_stack_container);
//	
//	this->_stack_container.Recreate(MAX);
//	this->_stack_container.Copy(temp);
//	temp.Reset();
//
//	return true;
//}
#endif