/*
Program Assignment: Program 1
Name:				Jorge René García Rosado
Date:				17/02/2020
Description:		This program calculates the mean and standandard deviation of a set of 10 values 
					by reading them and putting them in a Linked List, and finally retrieving them to do the calculation
*/

/*
Listing contents:
	Program descriptions
	Listing contents
	Includes
	Struct declarations:
		Struct node
	Class declarations:
		linked_list
	Source code in 1.cpp
		int main()
*/

#include <iostream>
#include <cmath>
using namespace std;

//ERASED >
/*
//data
int proxys[10] = {160, 591, 114, 229, 230, 270, 128, 1657, 624, 1503};
double hours[10] = {15.0, 69.9, 6.5, 22.4, 28.4, 65.9, 19.4, 198.7, 38.8, 138.2};
*/
//< ERASED

//Node struct
//MODIFIED >
struct node
{
//< MODIFIED
	//ERASED >
	/*
	int proxy;
	*/
	//< ERASED
	//MODIFIED >
	double data;
	//< MODIFIED
	struct node *next;
};

//Linked list class
class linked_list
{
	private: 
		node *head, *tail;
	public:
		//MODIFIED >
		linked_list()
		{
		//< MODIFIED
			head = NULL;
			tail = NULL;
		}
		
		//method for adding to linked list
		//MODIFIED >
		void addNode(double value)
		{
		//< MODIFIED
			node *tmp = new node;
			//MODIFIED >
			tmp ->data = value;
			//< MODIFIED
			//ERASED >
			/*
			tmp ->hours = hour;
			*/
			//< ERASED
			tmp ->next = NULL;
			//MODIFIED >
			if(head == NULL)
			{
			//< MODIFIED
				head = tmp;
				tail = tmp;
			}
			//MODIFIED >
			else
			{
			//< MODIFIED
				tail->next = tmp;
				tail = tail->next;
			}
		}
		
		node* getHead()
		{
			return head;
		}
			
		//ERASED >
		/*
		int getNodeProxy(node *curr){
			return curr->proxy;
		}
		
		double getNodeHours(node *curr){
			return curr->hours;
		}
		*/
		//< ERASED
		
		//NEW >
		double getData(node *curr)
		{
			return curr->data;
		}
		//< NEW
		//MODIFIED >
		void removeHead()
		{
		//< MODIFIED
			node *temp = head;
			head =head->next;
			delete temp;
		}
};

int main(int argc, char *argv[])
{
	//Create instance
	linked_list list;
	
	//put data in addNode method
	//ERASED >
	/*
	for(int i=0;i<10;i++){
		list.addNode(proxys[i],hours[i]);
	}
	*/
	//< ERASED
	
	//NEW >
	bool flag = true;
	char answer;
	
	double tempValue;
	double acumulatedData = 0;
	int numberOfItems = 0;
	
	while(flag){
		cout<<"Add a number? (y/n)"<<endl;
		cin>>answer;
		if(answer=='y')
		{
			cout<<"Enter the number"<<endl;
			cin>>tempValue;
			acumulatedData += tempValue;
			numberOfItems++;
			list.addNode(tempValue);
		}
		else
		{
			flag=false;
		}
		
	}
	
	double mean = acumulatedData/numberOfItems;
	//< NEW
	
	//ERASED >
	/*
	int tmpProxy = 0;
	double tmpHours = 0.0;
	int acum=0;
	
	double proxysData[10];
	double hoursData[10];
	*/
	//< ERASED
	
	//MODIFIED >
	struct node* temporalNode;
	temporalNode = list.getHead();
	//< MODIFIED
	
	//ERASED >
	/*
	while(temporalNode!=NULL){
		//Incrementing value of acum
		acum++;
		//Getting values
		tmpProxy += list.getNodeProxy(tmp);
		tmpHours += list.getNodeHours(tmp);
		proxysData[acum-1]= (double)list.getNodeProxy(tmp);
		hoursData[acum-1] = list.getNodeHours(tmp);
		//Removing head
		list.removeHead();
		tmp = list.getHead();
	}
	*/
	//< ERASED
	
	//NEW >
	
	double currentData;
	double standardDeviation = 0;
	
	while(temporalNode!=NULL)
	{
		currentData = list.getData(temporalNode);
		standardDeviation += pow(currentData - mean, 2.0);
		//Moving to next node
		list.removeHead();
		temporalNode = list.getHead();
	}
	
	standardDeviation = sqrt(standardDeviation/(numberOfItems-1));
	
	cout<<"Mean: "<<mean<<endl;
	cout<<"Standard Deviation: "<<standardDeviation<<endl;
	
	//< NEW
	
	//ERASED >
	/*
	double meanProxy = (double)tmpProxy/10;
	double meanHours = tmpHours/10;
	
	double stdDevProxy = 0.0;
	double stdDevHours = 0.0;
	
	for(int i=0;i<10;i++)
	{
		stdDevProxy += pow(proxysData[i] - meanProxy, 2.0);
		stdDevHours += pow(hoursData[i] - meanHours, 2.0);
	}

	stdDevProxy = sqrt(stdDevProxy/9);
	stdDevHours = sqrt(stdDevHours/9);
	
	cout <<"Mean for Estimate Proxy Size: "<<meanProxy << endl;
	cout <<"Standard Deviation for Estimate Proxy Size: "<<stdDevProxy << endl;
	cout <<"Mean for Development Hours: "<<meanHours << endl;
	cout <<"Standard Deviation for Development Hours: "<<stdDevHours << endl;
	*/
	//< ERASED
	return 0;
}

