#include<iostream>
using namespace std;

template<class T>
struct node
{
	T data;
	struct node *prev;
	struct node *next;
};

template<class T>
class Doubly_CLL
{
	public:
		struct node<T> *head;
		struct node<T> *tail;
		
		Doubly_CLL();
		void InsertFirst(T no);
		void InsertLast(T no);
		void InsertAtPosition(T no, int pos);
		void DeleteFirst();
		void DeleteLast();
		void DeleteAtPosition(int pos);		
		void Display();
		int Count();
};

template<class T>
Doubly_CLL<T>::Doubly_CLL()
{
	head = NULL;
	tail = NULL;
}

template<class T>
void Doubly_CLL<T>::InsertFirst(int no)
{
	struct node<T> *newn = NULL;
	
	newn = new node<T>;
	
	newn->data = no;
	newn->prev = NULL;
	newn->next = NULL;
	
	if(head == NULL && tail==NULL)		//if LL is empty
	{
		head = newn;
		tail = newn;
	}
	else
	{
		newn->next = head;
		head->prev = newn;
		
		newn->prev = tail;
				
		head = newn;
	}
	tail->next = head;
}
		
template<class T>
void Doubly_CLL<T>::InsertLast(int no)
{
	struct node<T> *newn = NULL;
	
	newn = new node<T>;
	
	newn->data = no;
	newn->prev = NULL;
	newn->next = NULL;
	
	if(head == NULL && tail==NULL)
	{
		head = newn;
		tail = newn;
	}
	else
	{
		tail->next = newn;
		newn->prev = tail;
		
		tail = newn;
	}
	tail->next = head;
}

template<class T>
void Doubly_CLL<T>::InsertAtPosition(int no, int pos)
{
	struct node<T> *newn = NULL;
	struct node<T> *temp = head;
	
	newn = new node<T>;
	
	newn->data = no;
	newn->prev = NULL;
	newn->next = NULL;
		
	if(head == NULL && tail==NULL)
	{
		head = newn;
		tail = newn;
	}
	else if( pos > (Count()+1) || pos<=0)
	{
		return;
	}
	
	if(pos == 1)
	{
		InsertFirst(no);
	}
	else if(pos == Count()+1)
	{
		InsertLast(no);
	}
	else
	{
		for(int i = 1; i < (pos-1); i++)
		{
			temp = temp->next;
		}
		
		newn->next = temp->next;
		temp->next->prev = newn;
		
		newn->prev = temp;
		temp->next = newn;
	}
}

template<class T>
void Doubly_CLL<T>::DeleteFirst()
{
	if(head == NULL && tail == NULL)
	{
		return;
	}
	else if(head == tail)
	{
		delete head;
		head = NULL;
		tail = NULL;
	}
	else
	{
		head = head->next; 
		head->prev = tail;
		
		delete tail->next;
		
		tail->next = head;
	}
}

template<class T>
void Doubly_CLL<T>::DeleteLast()
{
	if(head == NULL && tail == NULL)
	{
		return;
	}
	else if(head == tail)
	{
		delete head;
		head = NULL;
		tail = NULL;
	}
	else
	{
		tail = tail->prev;
		delete head->prev;
		
		tail->next = head;
	}
}

template<class T>
void Doubly_CLL<T>::DeleteAtPosition(int pos)
{
	if((head == NULL && tail == NULL) || pos>(Count()) || pos <= 0)
	{
		return;
	}
	
	if(pos == 1)
	{
		DeleteFirst();
	}
	else if(pos == Count())
	{
		DeleteLast();
	}
	else
	{
		struct node<T> *temp = head;
		
		for(int i = 1; i < (pos-1); i++)
		{
			temp = temp->next;
		}
		
		temp->next = temp->next->next;
		delete temp->next->prev;
		temp->next->prev = temp;
	}
}

template<class T>	
void Doubly_CLL<T>::Display()
{
	struct node<T> *temp = head;
	
	if(head == NULL && tail == NULL)		//if LL is empty....he asa filter lihil nahi tr khali do-while loop la segmentation fault yeil.
	{
		cout<<"inside if\n";
		return;
	}
	
	do
	{		
		cout<<"|"<<temp->data<<"| -> ";
		temp = temp->next;
	}while(temp != tail->next);   //while(temp != Head);
	
	cout<<endl;
}

template<class T>
int Doubly_CLL<T>::Count()
{
	struct node<T> *temp = head;
	int iCnt = 0;
	if(head == NULL && tail == NULL)		//if LL is empty....he asa filter lihil nahi tr khali do-while loop la segmentation fault yeil.
	{
		return 0;
	}
	
	do
	{		
		iCnt++;
		temp = temp->next;
	}while(temp != tail->next);   //while(temp != Head);
		
	return iCnt;
}	

int main()
{
	int iRet = 0;
	Doubly_CLL obj;
	
	obj.InsertFirst(111);
	obj.InsertFirst(51);
	obj.InsertFirst(21);
	obj.InsertFirst(11);
	
	obj.Display();
	iRet = obj.Count();
	
	cout<<"Number of nodes are: "<<iRet<<endl;
	
	obj.InsertLast(121);
	obj.InsertLast(151);
	
	obj.Display();
	iRet = obj.Count();
	cout<<"Number of nodes are: "<<iRet<<endl;
	
	obj.InsertAtPosition(75,4);
	obj.Display();
	iRet = obj.Count();
	cout<<"Number of nodes are: "<<iRet<<endl;
	
	obj.DeleteFirst();
	obj.Display();
	iRet = obj.Count();
	cout<<"Number of nodes are: "<<iRet<<endl;
	
	obj.DeleteLast();
	obj.Display();
	iRet = obj.Count();
	cout<<"Number of nodes are: "<<iRet<<endl;
	
	obj.DeleteAtPosition(3);
	obj.Display();
	iRet = obj.Count();
	cout<<"Number of nodes are: "<<iRet<<endl;
	
	return 0;
}



