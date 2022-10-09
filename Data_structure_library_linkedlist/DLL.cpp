#include<iostream>
using namespace std;

template<class T>
struct node
{
	T Data;
	node *Next;
	node *Prev;
};

template<class T>
class Doubly_linkedList
{
	public:
		struct node<T> *Head;
		
		Doubly_linkedList();
		~Doubly_linkedList();
		void InsertFirst(T);
		void InsertLast(T);
		void InsertAtPosition(T, int);
		void Display();
		int Count();
		void DeleteFirst();
		void DeleteLast();
		void DeleteAtPosition(int);
};

template<class T>
Doubly_linkedList<T>::Doubly_linkedList()
{
	Head = NULL;
}

template<class T>
Doubly_linkedList<T>::~Doubly_linkedList()
{
	struct node<T> *Temp = Head;
	
	if(Head != NULL)
	{
		while(Head != NULL)
		{
			Head = Head->Next;
			delete Temp;
			Temp = Head;
		}
	}
}

template<class T>
void Doubly_linkedList<T>::InsertFirst(T no)
{
	struct node<T> *newn = NULL;
	newn = new node<T>;
	
	if(newn == NULL)
	{
		return;
	}
	
	newn->Next = NULL;
	newn->Prev = NULL;
	newn->Data = no;
	
	if(Head == NULL)
	{
		Head = newn;
	}
	else
	{
		newn->Next = Head;
		Head->Prev = newn;
		Head = newn;
	}
}

template<class T>
void Doubly_linkedList<T>::InsertLast(T no)
{
	struct node<T> *newn = NULL;
	newn = new node<T>;
	
	if(newn == NULL)
	{
		return;
	}
	
	newn->Next = NULL;
	newn->Prev = NULL;
	newn->Data = no;
	
	if(Head == NULL)
	{
		Head = newn;
	}
	else
	{
		struct node<T> *temp = Head;
		
		while(temp->Next != NULL)
		{
			temp = temp->Next;
		} 
		temp->Next = newn; 
		newn->Prev = temp;
	}
}

template<class T>
void Doubly_linkedList<T>::InsertAtPosition(T no, int pos)
{
	if( Head==NULL || pos>(Count()+1) || pos<=0)
	{
		return;
	}	
	
	if(pos==1)
	{
		return(InsertFirst(no));
	}
	else if(pos == Count()+1)
	{
		return(InsertLast(no));
	}
	else
	{
		struct node<T> * newn = NULL;
		struct node<T> *temp = Head;
		
		newn = new node<T>;
		if(newn == NULL)
		{
			return;
		}
		
		newn->Next = NULL;
		newn->Prev = NULL;
		newn->Data = no;
		
		for(int i = 1; i<= (pos-2); i++)
		{
			temp = temp->Next;
		}
		
		newn->Next = temp->Next;
		newn->Prev = temp;
		temp->Next->Prev = newn;
		temp->Next = newn;
	}
}

template<class T>
void Doubly_linkedList<T>::DeleteFirst()
{
	struct node<T> *temp = Head;
	
	if(Head == NULL)
	{
		return;
	}
	else
	{
		Head = Head->Next;
		Head->Prev = NULL;
		
		delete temp;
	}
}

template<class T>
void Doubly_linkedList<T>::DeleteLast()
{
	if(Head == NULL)
	{
		return;
	}
	else if( Head->Next == NULL)
	{
		delete Head;
		Head = NULL;
	}
	else
	{
		struct node<T> *temp = Head;
		
		while(temp->Next != NULL)
		{
			temp = temp->Next;
		}
		
		temp->Prev->Next = NULL;
		delete temp;
	}	
}

template<class T>
void Doubly_linkedList<T>::DeleteAtPosition(int pos)
{
	if( Head==NULL || pos>(Count()) || pos<=0)
	{
		return;
	}	
	
	if(pos==1)
	{
		return(DeleteFirst());
	}
	else if(pos == Count())
	{
		return(DeleteLast());
	}
	else
	{
		struct node<T> *temp = Head;
		
		for(int i = 1; i<=(pos-2); i++)
		{
			temp = temp->Next;
		}
		
		temp->Next = temp->Next->Next;
		delete temp->Next->Prev;
		temp->Next->Prev = temp;
	}
}

template<class T>
void Doubly_linkedList<T>::Display()
{
	struct node<T> *temp = Head;
	
	while(temp != NULL)
	{
		cout<<temp->Data<<"->";
		temp = temp->Next;
	}
	cout<<endl;
}

template<class T>
int Doubly_linkedList<T>::Count()
{
	struct node<T> *temp = Head;
	int iCnt = 0;
	
	while(temp != NULL)
	{
		iCnt++;
		temp = temp->Next;
	}
	return iCnt;
}

int main()
{
	Doubly_linkedList <int>obj1;
	Doubly_linkedList <float>obj2;
	
	obj1.InsertFirst(101);
	obj1.InsertFirst(51);
	obj1.InsertFirst(21);
	obj1.InsertFirst(11);
	obj1.InsertAtPosition(31,2);
	obj1.DeleteAtPosition(2);

	obj1.InsertLast(111);
	obj1.InsertLast(121);
	
	obj1.Display();
	cout<<"Number of node are : " <<obj1.Count()<<endl;
	
	
	obj1.DeleteFirst();
	obj1.DeleteLast();
	obj1.Display();
	cout<<"Number of node are : " <<obj1.Count()<<endl;
	//------------------------------------------------------------
	
	obj2.InsertFirst(21.11);
	obj2.InsertFirst(21.11);
	
	obj2.InsertLast(51.11);
	obj2.InsertLast(101.11);
	
	obj2.Display();
	cout<<"Number of node are : " <<obj2.Count()<<endl;
	
	
	return 0;
}




























