#include<iostream>
using namespace std;

class Sorting
{
	public:
		int iSize;
		int *arr = NULL;
	
		Sorting(int size)
		{
			iSize = size;
			arr = new int[iSize];
		}
				
		void Accept()
		{
			cout<<"Enter Array Elements\n";
			for(int i = 0; i<iSize; i++)
			{
				cin>>arr[i];
			}
		}
		
		void Display()
		{	
			cout<<"Array elements are\n";
			for(int i = 0; i<iSize; i++)
			{
				cout<<arr[i]<<" ";
			}
		}
		
		void BubbleSort(char type)
		{
			int i = 0, j = 0, temp = 0;
			
			int Swap = 0;
			
			if(type == 'I' || type == 'i')
			{
				for(i = 0; i<iSize; i++)
				{
					Swap = 0;
					for(j = 0; j < iSize-i-1 ; j++)
					{
						if(arr[j] > arr[j+1])
						{
							temp = arr[j];
							arr[j] = arr[j+1];
							arr[j+1] = temp;
							Swap = 1;
						}
					}
					cout<<"\nPass : "<<i+1<<endl;
					Display();
					if(Swap == 0)
					{
						break;
					}
				}
			}
			else if(type == 'd' || type == 'D')
			{
				for(i = 0; i<iSize; i++)
				{
					Swap = 0;
					for(j = 0; j < iSize-i-1 ; j++)
					{
						if(arr[j] < arr[j+1])
						{
							temp = arr[j];
							arr[j] = arr[j+1];
							arr[j+1] = temp;
							Swap = 1;
						}
					}
					cout<<"\nPass : "<<i+1<<endl;
					Display();
					if(Swap == 0)
					{
						break;
					}
				}
			}
		}	
};

int main()
{
	int size = 0;
	
	cout<<"Enter the size of array\n";
	cin>>size;
	
	Sorting aobj(size);
	aobj.Accept();
	aobj.Display();
	
	aobj.BubbleSort('I');
	cout<<"\nData after sorting\n";
	aobj.Display();
	
	cout<<"\n------------------------------------------------\n";
	
	aobj.BubbleSort('d');
	cout<<"\nData after sorting\n";
	aobj.Display();
	
	return 0;
}
