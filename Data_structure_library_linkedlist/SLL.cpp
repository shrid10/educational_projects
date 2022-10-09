#include<iostream>
#define FALSE 0
#define TRUE 1

using namespace std;

template<class T>
struct node
{
	T data;
	struct node *next;
};

template<class T>
class SinglyLL
{
	public:
		struct node<T> *Head;
		int Count;
		
		SinglyLL();
		void InsertFirst(T);
		void InsertLast(T);
		void DeleteFirst();
		void DeleteLast();
		void InsertAtPos(T, int);
		void DeleteAtPos(int iPos);
		void Display();
		int CountNode();
};

template<class T>
SinglyLL<T>::SinglyLL()
{
	Head = NULL;
	Count = 0;
}

template<class T>
void SinglyLL<T>::InsertFirst(T value)
{
	struct node<T> *newn = NULL;
	newn = new node<T>;
	
	newn->data = value;
	newn->next = NULL;
	
	if(Head == NULL)
	{
		Head = newn;
	}
	else
	{
		newn->next = Head;
		Head = newn;
	}
	Count++;
}

template<class T>
void SinglyLL<T>::InsertLast(T value)
{
	struct node<T> *newn = NULL;
	newn = new node<T>;
	
	newn->data = value;
	newn->next = NULL;
	
	if(Head == NULL)
	{
		Head = newn;
	}
	else
	{
		struct node<T> *temp = Head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		
		temp->next = newn;
	}
	Count++;
}

template<class T>
void SinglyLL<T>::DeleteFirst()
{
	if(Head == NULL)
	{
		return;
	}
	
	struct node<T> *temp = Head;
	
	Head = Head->next;
	delete temp;
	Count--;
}

template<class T>
void SinglyLL<T>::DeleteLast()
{
	if(Head == NULL)
	{
		return;
	}
	else if(Head->next == NULL)
	{
		delete Head;
		Head = NULL;
	}
	else
	{
		struct node<T> *temp = Head;
		struct node<T> *temp2 = NULL;
		
		while(temp->next->next != NULL)
		{
			temp = temp->next;
		}
		temp2 = temp->next;
		delete temp2;
		temp->next = NULL;
		Count--;
	}
}

template<class T>
void SinglyLL<T>::InsertAtPos(T value,int iPos)
{
	if(iPos<1 || iPos > Count+1)
	{
		return;
	}
	
	if(iPos == 1)
	{
		InsertFirst(value);
	}
	else if(iPos == Count+1)
	{
		InsertLast(value);
	}
	else
	{
		struct node<T> *temp = Head;
		struct node<T> *newn = NULL;
		newn = new node<T>;
		
		newn->data = value;
		newn->next = NULL;
		
		for(int i = 0; i<iPos-1; i++)
		{
			temp = temp->next;
		}
		
		newn->next = temp->next;
		temp->next = newn;
		
		Count++;
	}
}

template<class T>
void SinglyLL<T>::DeleteAtPos(int iPos)
{
	if(Head == NULL || iPos<1 || iPos > Count)
	{
		return;
	}
	
	if(iPos == 1)
	{
		DeleteFirst();
	}
	else if(iPos == Count)
	{
		DeleteLast();
	}
	else
	{		
		struct node<T> *temp = Head;
		struct node<T> *temp2 = NULL;
		for(int i = 0; i<iPos-1; i++)
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
void SinglyLL<T>::Display()
{
	cout<<"Elements form Linked list are : "<<endl;
	struct node<T> *temp = Head;
	
	while(temp != NULL)
	{
		cout<<temp->data<<" ";
		temp = temp->next;
	}
	cout<<endl;
}

template<class T>
int SinglyLL<T>::CountNode()
{
	/*
	struct node<T> *temp = NULL;
	while(temp != NULL)
	{
		Count++;
		temp = temp->next;
	}
	*/
	return Count;
}

int main()
{
	SinglyLL <int>obj1;
	SinglyLL <float>obj2;
	
	obj1.InsertFirst(21);
	obj1.InsertFirst(21);
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
