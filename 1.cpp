#include <iostream>
#include <cmath>
using namespace std;

//data
int proxys[10] = {160, 591, 114, 229, 230, 270, 128, 1657, 624, 1503};
double hours[10] = {15.0, 69.9, 6.5, 22.4, 28.4, 65.9, 19.4, 198.7, 38.8, 138.2};

//int proxys[10] = {186, 699, 132, 272, 291, 331, 199, 1890, 788, 1601};

//Node struct
struct node{
	int proxy;
	double hours;
	struct node *next;
};

//Linked list class
class linked_list{
	private: 
		node *head, *tail;
	public:
		linked_list(){
			head = NULL;
			tail = NULL;
		}
		
		//method for adding to linked list
		void addNode(int size, double hour){
			node *tmp = new node;
			tmp ->proxy = size;
			tmp ->hours = hour;
			tmp ->next = NULL;
			
			if(head == NULL){
				head = tmp;
				tail = tmp;
			} else {
				tail->next = tmp;
				tail = tail->next;
			}
		}
		
		node* getHead(){
			return head;
		}
			
			
		int getNodeProxy(node *curr){
			return curr->proxy;
		}
		
		double getNodeHours(node *curr){
			return curr->hours;
		}
		
		void removeHead(){
			node *temp = head;
			head =head->next;
			delete temp;
		}
};

int main(int argc, char *argv[]) {
	//Create instance
	linked_list list;
	
	//put data in addNode method
	for(int i=0;i<10;i++){
		list.addNode(proxys[i],hours[i]);
	}
	
	int tmpProxy = 0;
	double tmpHours = 0.0;
	int acum=0;
	
	double proxysData[10];
	double hoursData[10];
	
	struct node* tmp;
	tmp = list.getHead();
	
	while(tmp!=NULL){
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
	
	double meanProxy = (double)tmpProxy/10;
	double meanHours = tmpHours/10;
	
	double stdDevProxy = 0.0;
	double stdDevHours = 0.0;
	
	for(int i=0;i<10;i++){
		stdDevProxy += pow(proxysData[i] - meanProxy, 2.0);
		stdDevHours += pow(hoursData[i] - meanHours, 2.0);
	}

	stdDevProxy = sqrt(stdDevProxy/9);
	stdDevHours = sqrt(stdDevHours/9);
	
	cout <<"Mean for Estimate Proxy Size: "<<meanProxy << endl;
	cout <<"Standard Deviation for Estimate Proxy Size: "<<stdDevProxy << endl;
	cout <<"Mean for Development Hours: "<<meanHours << endl;
	cout <<"Standard Deviation for Development Hours: "<<stdDevHours << endl;
	
	return 0;
}

