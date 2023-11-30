#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* P = Head;
		Node<T>* R = new Node<T>(data);

		if (Head == nullptr)
		{
			Head = R;
			return;
		}



		while (P->getNext())
			P = P->getNext();

		P->setNext(R);

		return;
	}



	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	T Find(T Key)
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
		return ;

	}


	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int Count = 0;
		Node<T>* P = Head;
		while (P)
		{
			if (P->getItem() == value)
			{
				Count++;

			}
			P = P->getNext();
		}


		return Count;
	}



	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		Node<T>* P = Head;

		if (Head)
		{
			Head = P->getNext();
			delete P;
			return;
		}

		cout << "List is empty" << endl;
		return;

	}



	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* P = Head;
		if (!P)
		{
			cout << "List is Empty" << endl;
			return;
		}
		while (P->getNext())
		{
			if ((P->getNext()->getNext()) == nullptr)
			{
				Node <T>* R = P->getNext();
				P->setNext(nullptr);
				delete R;
				return;
			}
			P = P->getNext();
		}
		Head = nullptr;
		delete P;
		return;


	}


	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{
		Node<T>* P = Head;


		while (P)
		{
			/*if (P->getItem()==value && (P->getNext()->getItem()==nullptr))
			{
				Head=nullptr;
				delete P;
				cout << "Now the list is empty"<<endl;
				return true;
			}*/
			if (P->getItem() == value)
			{
				Head = P->getNext();
				delete P;
				//cout << "Now the list is empty" << endl;
				return true;
			}
			if (P->getNext()->getItem() == value)
			{
				Node <T>* R = P->getNext();
				P->setNext(R->getNext());
				delete R;
				return true;
			}
			P = P->getNext();
		}

		return false;

	}


	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		Node<T>* P = Head;


		while (P)
		{
			/*if (P->getItem()==value && (P->getNext()->getItem()==nullptr))
			{
				Head=nullptr;
				delete P;
				cout << "Now the list is empty"<<endl;
				return true;
			}*/
			if (P->getItem() == value)
			{
				Head = P->getNext();
				delete P;
				cout << "Now the list is empty" << endl;

			}
			if (P->getNext()->getItem() == value)
			{
				Node <T>* R = P->getNext();
				P->setNext(R->getNext());
				delete R;

			}
			P = P->getNext();
		}

		return false;
	}



	//[8] GetOrderFromID
	//Returns the order from its ID
	Order* GetOrderFromID(int ID)
	{
		Node<T>* SearchOrder = Head;

		while (SearchOrder)
		{
			if (SearchOrder->getItem()->GetID() == ID)
			{
				return SearchOrder->getItem();
			}
			SearchOrder = SearchOrder->getNext();
		}
		return nullptr;
	}


	//[9] IsEmpty

	bool IsEmpty()
	{
		if (Head == nullptr)
			return true;
		else
			return false;

	}

	//[10] get first node in the List 
	bool GetfirstNode(T& order)
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


	//[11] to array ..linked list edition
	T* LinkedList<T>::toArray(int& count)
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

	//[12] Sort ..to sort according to  service time
	void SortServicetime()
	{
		if (Head == nullptr)
			return ;
		else
		{
			
			Node<T>* Ptr = Head;
			
			while (Ptr &&Ptr->getNext() && Ptr->getNext()->getNext())
			{
				
				Node<T>* Beg = nullptr;    // Find orders with same finish time and mark their Beginning & End 
				if (Ptr->getNext()->getItem()->getFinishTime() == Ptr->getNext()->getNext()->getItem()->getFinishTime())
					Beg = Ptr;
				while (Ptr->getNext()->getNext() &&(Ptr->getNext()->getItem()->getFinishTime() == Ptr->getNext()->getNext()->getItem()->getFinishTime()))
					Ptr = Ptr->getNext();
				Node<T>* End = Ptr;
					
				if (Beg != nullptr)					// if there is orders with the same finish time sort them  
				{									// Sorting sequence (like Selection sort)
					Node<T>* Min = nullptr;							// to catch the min Serving time
					Node<T>* Jumper = nullptr;						// to loop on the orders with similer finish time
					Node <T>* NearEnd = nullptr;                    //  to capture the value before end

					while (End && End->getNext() != Beg)
					{

						Min = Beg;

						Jumper = Min->getNext();

						while (Jumper != End->getNext())			// locate the node with min serving time
						{
							if (Jumper->getNext()->getItem()->GetServTime() < Min->getNext()->getItem()->GetServTime())
								Min = Jumper;

							if (Jumper->getNext() == End)
								NearEnd = Jumper;

							Jumper = Jumper->getNext();
						}

						// in case we're at thr last 2 values and the last is the min 
						if (Beg == End && Jumper->getItem()->GetServTime() < Min->getItem()->GetServTime())
						{
							Min->setNext(Jumper->getNext());
							Jumper->setNext(Min);
							NearEnd->setNext(Jumper); // Min will remain with the beg
						}

						if (Min != Beg)
						{

							if (Min->getNext() == End)			// check if it's the before the end of numbers
								End = Min;

							if (Min = End)				// if it's the end of the numbers
								End = NearEnd;

							////////////////// reallocating the min node (by placing it at the beg)/////////////////////////////
							Jumper = Min->getNext();
							Min->setNext(Jumper->getNext());
							Jumper->setNext(Beg->getNext());
							Beg->setNext(Jumper);
						}
						Beg = Beg->getNext();

					}
				}
					
				Ptr = Ptr->getNext();
			}
		}
	}




	//[13]... view first node only but do not delete it

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

	//[14]..sort by finish time
	void SortFinishTime()
	{
		if (Head == nullptr)
			return;
		//Node<T>* Ptr = Head;
		Node<T>* Min = Head;							// to catch the min Serving time
		Node<T>* Jumper = nullptr;						// to loop on the orders with similer finish time
		Node <T>* Beg = Head;                    //  to capture the value before end

		while (Beg&& Beg->getNext())
		{
			Min = Beg;
			Jumper = Min->getNext();
			while (Jumper && Jumper->getNext())			// locate the node with min serving time
			{
				if (Jumper->getNext()->getItem()->getFinishTime() < Min->getNext()->getItem()->getFinishTime())
					Min = Jumper;


				Jumper = Jumper->getNext();
			}
			if (Head->getItem()->getFinishTime() > Min->getNext()->getItem()->getFinishTime())
			{
				Jumper = Min->getNext();
				Min->setNext(Jumper->getNext());
				Jumper->setNext(Head);
				Head = Jumper;
				Beg = Head;
				continue;
			}
			else if (Min != Beg)
			{
				Jumper = Min->getNext();
				Min->setNext(Jumper->getNext());
				Jumper->setNext(Beg->getNext());
				Beg->setNext(Jumper);

				
			}

			Beg = Beg->getNext();
		}
	}
};

#endif	
