#include<iostream>
using namespace std;

template<class T>
struct node
{
	T data;
	struct node *next;
};

template<class T>
class SinglyCLL
{
	public:				//Characteristics
		struct node<T> *Head;
		struct node<T> *Tail;
		int Count;
		
		SinglyCLL();
		void InsertFirst(T);
		void InsertLast(T);
		void InsertAtPos(T , int ipos);
		void DeleteFirst();
		void DeleteLast();
		void DeleteAtPos(int ipos);
		void Display();
		int CountNode();
};

template<class T>
SinglyCLL<T>::SinglyCLL()
{
	Head = NULL;
	Tail = NULL;
	Count = 0;
}
		
template<class T>
void SinglyCLL<T>::InsertFirst(T value)
{
	struct node<T> *newn = NULL;
	
	newn = new node<T>;
	
	newn->data = value;
	newn->next = NULL;
	
	if((Head == NULL) && (Tail == NULL))	//If LL is empty
	{
		Head = newn;
		Tail = newn;
	}
	else		//If LL contains at least one node
	{
		newn->next = Head;
		Head = newn;
	}
	Tail->next = Head;
	Count++;
}

template<class T>
void SinglyCLL<T>::InsertLast(T value)
{
	struct node<T> *newn = NULL;
	
	newn = new node<T>;
	
	newn->data = value;
	newn->next = NULL;
	
	if((Head == NULL) && (Tail == NULL))	//If LL is empty
	{
		Head = newn;
		Tail = newn;
	}
	else		//If LL contains at least one node
	{
		Tail->next = newn;
		Tail = newn;
	}
	Tail->next = Head;
	Count++;
}

template<class T>
void SinglyCLL<T>::InsertAtPos(T value, int ipos)
{
	int iSize = CountNode();
	
	if((ipos < 1) || (ipos> iSize+1))
	{
		cout<<"Invalid position\n";
		return;
	}
	
	if(ipos == 1)
	{
		InsertFirst(value);
	}
	else if(ipos == iSize+1)
	{
		InsertLast(value);
	}
	else
	{
		struct node<T> *newn = NULL;
		
		newn = new node<T>;
		
		newn->data = value;
		newn->next = NULL;
		
		struct node<T> *temp = Head;
		int iCnt = 0;
		
		for(iCnt = 1; iCnt<ipos-1; iCnt++)
		{
			temp = temp->next;
		}
		
		newn->next = temp->next;
		temp->next = newn;		
		
		Count++;
	}
}

template<class T>
void SinglyCLL<T>::DeleteFirst()
{
	if(Head==NULL && Tail==NULL)		//If LL is empty
	{
		return;		
	}
	else if(Head==Tail)		//If LL contains 1 node
	{
		delete Head;
		Head = NULL;
		Tail = NULL;
	}
	else		//If contains more than one node
	{
		Head = Head->next;
		delete Tail->next;
		
		Tail->next = Head;
		Count--;
	}
}

template<class T>
void SinglyCLL<T>::DeleteLast()
{
	if(Head==NULL && Tail==NULL)		//If LL is empty
	{
		return;		
	}
	else if(Head==Tail)		//If LL contains 1 node
	{
		delete Tail;		//delete Head  <--asa pn lihu shakto,sarkhach ahe
		Head = NULL;
		Tail = NULL;
	}
	else		//If contains more than one node
	{
		struct node<T> *temp = Head;
		while(temp->next != Tail)
		{
			temp = temp->next;
		}
		
		delete Tail;
		Tail = temp;
		
		Tail->next = Head;
	}
	Count--;
}

template<class T>
void SinglyCLL<T>::DeleteAtPos(int ipos)
{
	int iSize = CountNode();
	
	if((ipos < 1) || (ipos > iSize))
	{
		cout<<"Invalid position\n";
		return;
	}
	
	if(ipos == 1)
	{
		DeleteFirst();
	}
	else if(ipos == iSize)
	{
		DeleteLast();
	}
	else
	{
		struct node<T> *temp = Head;
		struct node<T> *temp2 = NULL;
		for(int i = 0; i<ipos-1; i++)
		{
			temp = temp->next;
		}
		
		temp2 = temp-next;
		temp->next = temp->next->next;
		delete temp2;
		
		Count--;
	}
}

template<class T>
void SinglyCLL<T>::Display()
{
	struct node<T> *temp = Head;
	
	if(Head == NULL && Tail == NULL)		//if LL is empty....he asa filter lihil nahi tr khali do-while loop la segmentation fault yeil.
	{
		return;
	}
	
	do
	{
		cout<<"|"<<temp->data<<"| -> ";
		temp = temp->next;
	}while(temp != Tail->next);   //while(temp != Head);
	
	cout<<endl;
}

template<class T>
int SinglyCLL<T>::CountNode()
{	
	return Count;
}

int main()
{
	SinglyCLL <int>obj1;
	SinglyCLL <float>obj2;
	
	obj1.InsertFirst(21);
	obj1.InsertFirst(11);
	obj1.InsertLast(51);
	obj1.InsertLast(101);
	
	obj1.Display();
	cout<<"Number of node are : " <<obj1.CountNode()<<endl;
	
	obj1.DeleteFirst();
	obj1.DeleteLast();
	obj1.Display();
	cout<<"Number of node are : " <<obj1.CountNode()<<endl;
	//------------------------------------------------------------
	
	obj2.InsertFirst(21.11);
	obj2.InsertFirst(21.11);
	obj2.InsertLast(51.11);
	obj2.InsertLast(101.11);
	
	obj2.Display();
	cout<<"Number of node are : " <<obj2.CountNode()<<endl;
	
	return 0;
}

































