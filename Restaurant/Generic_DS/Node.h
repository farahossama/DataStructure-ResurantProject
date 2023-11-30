
#ifndef __NODE_H_
#define __NODE_H_
#include"..\Rest\Order.h"
//class Order;

template < typename T>
class Node
{
private :
	T item; // A data item
	Node<T>* next; // Pointer to next node
	int Priority;
public :
	Node();
	Node( const T & r_Item);	//passing by const ref.
	Node( const T & r_Item, Node<T>* nextNodePtr);
	//Node(const T& r_Item, const int& pr);
	void setItem( const T & r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const ;
	Node<T>* getNext() const ;
	void setPriority();
	int getPriority() const;
	void Get_next_of();
}; // end Node


template < typename T>
Node<T>::Node() 
{
	next = nullptr;
} 

template < typename T>
Node<T>::Node( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}


template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T Node<T>::getItem() const
{
	return item;
} 

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
} 

//template < typename T>
/*void Node<Order*>::setPriority()
{
	//Priority = (rand()%15+1);
	//Priority = o->gettotalmoney() / ( o->getSize() * o->getArrTime() );
	Priority = getItem()->gettotalmoney() / ((getItem()->getSize()) * (getItem()->getArrTime()));
}
*/
template < typename T>
void Node<T>::setPriority()
{
	Priority = getItem()->Calculate_Priority();
	return;
	//Priority = (rand()%15+1);
	//if (dynamic_cast<Order*>(getItem()))
	//{
	//	Priority =( getItem()->gettotalmoney() / (getItem()->getSize()) )* (getItem()->getArrTime()); // (totalmoney/size)* arrivaltime 
	//}
	////Priority = o->gettotalmoney() / ( o->getSize() * o->getArrTime() );
	//if (dynamic_cast<Cook*>(getItem()))
	//{
	//	Priority = ((getItem()->GetSpeed()) * 10) - (getItem()->GetInbreak());
	//	// speed multiplied by 10 to maximize its load in setting the priority then we substract from it the break period
	//}
	//if (is_same<T, Order*>())
	//{
	//	Priority = (getItem()->gettotalmoney() / (getItem()->getSize())) * (getItem()->getArrTime()); // (totalmoney/size)* arrivaltime
	//	return;
	//}
	//if (is_same<T, Cook*>())
	//{
	//	Priority = ((getItem()->GetSpeed()) * 10) - (getItem()->GetInbreak());
	//	//	// speed multiplied by 10 to maximize its load in setting the priority then we substract from it the break period
	//	return;
	//}
}
//template<>
//void Node<Order*>::setPriority()
//{
//	Priority = (getItem()->gettotalmoney() / (getItem()->getSize())) * (getItem()->getArrTime()); // (totalmoney/size)* arrivaltime 
//}
//template<>
//void Node<Cook*>::setPriority()
//{
//	Priority = ((getItem()->GetSpeed()) * 10) - (getItem()->GetInbreak());
//	//	// speed multiplied by 10 to maximize its load in setting the priority then we substract from it the break period
//}


template < typename T>
int Node<T>::getPriority() const
{
	return Priority;
}
/*template < typename T>
void Node<T>::Get_next_of()
{
	if (this)
	{
		this = this->getNext();
	}
}*/

#endif