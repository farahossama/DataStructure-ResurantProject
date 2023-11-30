#ifndef  _LISTBAG
#define  _LISTBAG

#include "Node.h"
template <typename T>
class ListBag
{
	Node<T>* Head;	//Pointer to the head of the list
public:

	ListBag()  //constructor
	{
		Head = nullptr;
	}

	~ListBag()  //destructor
	{
		DeleteAll();
	}

	void DeleteAll()        // delete all items in the bag
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}


	void AddNode(T it)   // Add item in the bag
	{
		Node<T>* nptr = new Node <T>(it);
		//nptr->setItem(it);
		if (Head == nullptr)
			Head = nptr;
		else
		{
			nptr->setNext(Head);
			Head = nptr;
		}
		return ;
	}


	bool RemoveNode(T it)   //Remove item from the bag
	{
		Node<T>* ptr = Head;
		while (ptr)
		{
			if (ptr->getItem() == it)
			{
				ptr->setItem(Head->getItem());
				Node<T>* temp = Head;
				Head = Head->getNext();
				delete temp;
				return true;
			}
			else
				ptr = ptr->getNext();
		}
		return false;
	}

	bool IsEmpty()  // check if the bag id empty or not
	{
		if (Head == nullptr)
			return true;
		else
			return false;

	}


	T Find(T Key)   //search for a certain item in the bag
	{
		Node<T>* P = Head;
		while (P)
		{
			if (P == Key)
			{
				return P;
			}
			P = P->getNext();
		}
		return;

	}


	T* ListBag<T>::toArray(int& count) 
	{
		count = 0;

		if (!Head)
			return nullptr;
		//counting the no. of items in the list
		Node<T>* p = Head;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = Head;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

	Node<T>* FromInService_to_Finished()   //this function return a pointer to the first node in the In serv bag
	{
		Node<T>* ptr = Head;
		
		return (ptr);
	}


	bool GetfirstNode(T& order)/// removes the first item in the bag and returns it by reference
	{
		if (Head == nullptr)
			return false;
		else
		{
			Node<T>* tempPtr = Head;
			order = Head->getItem();
			Head = Head->getNext();
			delete tempPtr;
			tempPtr = nullptr;
			return true;
		}


	}

	bool ViewfirstNode(T& order)/// removes the first item in the bag and returns it by reference
	{
		if (Head == nullptr)
			return false;
		else
		{
			
			order = Head->getItem();
			
			return true;
		}


	}
};




#endif
