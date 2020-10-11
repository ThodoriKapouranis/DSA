//THODORI KAPOURANIS
//11 24 2019
// DSA 1 STACKS AND QUEUES

// i've left my testing comments in my code

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

template <class T>
class simpleList{
protected: //because subclasses need to access this
	class node{
	public:
		node(T insertValue);
		T nodeData;
		node *nextNode; //pointer to type Node. Singly linked so only next required
	};


//ALL LISTS DERIVED FROM THIS CLASS WILL HAVE THESE ATTRIBUTES:
	string name;          
	int length;           
	node *firstNode, *lastNode;

public:
	simpleList(string insertName);
	int getLength();   // to check if empty for pop() error case
	string getName(); // to check if already exist and to locate what to push/pop to
	virtual void push(T pushedData) = 0;
	T pop(); 
};

//Definitions of base functions/constructors

template <class T>
simpleList<T>::simpleList(string insertName){
	this->name = insertName;
	this->length = 0;
	this->firstNode = this->lastNode = NULL; //NULL, not 0.
};

template <class T>
int simpleList<T>::getLength(){
	return this->length;
};

template <class T>
string simpleList<T>::getName(){
	return this->name;
};

template<class T>
simpleList<T>::node::node(T insertValue){//constructor for node
	this->nodeData = insertValue;
	this->nextNode = NULL; //NULL, not 0.
}

template<class T>
T simpleList<T>::pop(){
		T popValue = this->firstNode->nodeData; //or else cant access
		typename simpleList<T>::node *temp = this->firstNode; 
		this->firstNode = temp->nextNode;
		delete(temp);
		this->length--;
		//cout << "Value popped: " << popValue << endl << endl;
		return popValue;
}

template <class T>
class Stack: public simpleList<T>{
public:
		Stack(string insertName): simpleList<T>::simpleList(insertName){}; //constructor still applies
		void push(T insertValue);
};

template <class T>
void Stack<T>::push(T insertValue){
	typename simpleList<T>::node *temp = new typename simpleList<T>::node(insertValue);
	if(this->length==0){
		this->firstNode = this->lastNode = temp;
		temp->nextNode = NULL;
	}
	else{
		//append node to the start of the list
		temp->nextNode=this->firstNode;
		this->firstNode = temp;
	}
	this->length++;	
	//cout<< "Value pushed: " << insertValue << endl << endl;
};

template <class T>
class Queue: public simpleList<T>{
public:
	Queue(string insertName): simpleList<T>::simpleList(insertName){}; //constructor still applies
	void push(T insertValue);
};

template <class T>
void Queue<T>::push(T insertValue){
	typename simpleList<T>::node *temp = new typename simpleList<T>::node(insertValue);
	if(this->length==0){
		this->lastNode = this->firstNode = temp;
		temp->nextNode = NULL;
	}
	else{
		//append node to the end of the list
		this->lastNode->nextNode = temp;
		this->lastNode=temp;
	}
	this->length++;
	//cout<< "Value pushed: " << insertValue << endl << endl;
};


/* The classes have been made
Now must implement these features to meet the requirements of the word DOC:
	- createList (and appends it to a vector so we can easily manage our lists)
	- findList (look thru the list vector to check if name already exists or doesnt exist)
*/


template <class T> //
simpleList<T>* findList(vector<simpleList<T>*> *vectorOfLists, string searchQuery){  //We want it to return a pointer to the list we searched for 
	vector<simpleList<T>*> tempList = *vectorOfLists;
	/*
	cout << "searching for: " << searchQuery << endl;
	cout << "list size: " << tempList.size() << endl ;
	cout << "array address: "<< vectorOfLists << endl;
	*/
	simpleList<T> *returnList = NULL;
	for(int i=0; ((returnList==NULL)&&(i < tempList.size())); i++){ //continue this loop until find MATCH or go thru whole list
		//cout << "Current item: "<< tempList[i] << endl;
		if(searchQuery.compare(tempList[i]->getName())==0){
			returnList = tempList[i];
		};
	};
	return returnList; //if NULL then we never found matching list...
};  

template <class T>
void createList(vector<simpleList<T>*> *vectorOfLists, string listType, string listName, ofstream* output){

	if (findList(vectorOfLists,listName)){
		(*output) << "ERROR: This name already exists!" << endl;
		//cout << "duplicate found" << endl;
	}

	else{
		simpleList<T> *tempList;
		
		if(!listType.compare("queue")){
			tempList = new Queue<T>(listName);
			//cout << "pushed queue named:  " << listName << endl;
		}
		
		else{
			tempList = new Stack<T>(listName);
			//cout << "pushed stack named:  " << listName << endl;
		}
		//cout << "size before: " << vectorOfLists->size() << endl;
		vectorOfLists->push_back(tempList);
		//cout << "size after: " << vectorOfLists->size() << endl;

	}
};

// i realize i need to create functions to add and remove from lists given a list name because of how file reading will work
template <class T>
void searchToPop(vector<simpleList<T>*> *vectorOfLists, string listName, ofstream *output){
	simpleList<T> *temp = findList<T>(vectorOfLists,listName);
	if(!temp){
		(*output) << "ERROR: This name does not exist!" << endl;
		return;
	}

	else if(temp->getLength()==0){
		(*output) << "ERROR: This list is empty!" << endl;
		return;
	}
	(*output) << "Value popped: " << temp->pop() << endl;
};

template <class T> //need to implement this first before pop cause of testing reasons lol
void searchToPush(vector<simpleList<T>*> *vectorOfLists, string listName, T insertValue, ofstream *output){
	simpleList<T> *temp = findList<T>(vectorOfLists, listName);
	if(!temp){
		(*output) << "ERROR: This name does not exist!" << endl;
		return;
	}
	temp->push(insertValue);
};

readInputCommandFile(string inputFile, string outputFile){
	ifstream inputStream;
	ofstream outputStream;	
	inputStream.open(inputFile.c_str());
	outputStream.open(outputFile.c_str());  //from kirtman class

	if(!inputStream.is_open()){
		cout<<"ERROR: This name does not exist!" << endl;
	}

	string line;

	//To create different vectors of list types
	vector<simpleList<int> *> vectorOfiList;
	vector<simpleList<double> *> vectorOfdList;
	vector<simpleList<string> *> vectorOfsList;

	while(getline(inputStream,line)){

		string operation, name; //to access parts of the line
		stringstream lineSplit; //to split the line

		outputStream << "PROCESSING COMMAND: " << line << endl;
		lineSplit << line;
		lineSplit >> operation;
		lineSplit >> name;


		if(!operation.compare("create")){
		//example:  create i1 queue
			string listType;
			lineSplit >> listType; //stack or queue

		//substr to check first letter of the name. This is the type we're working with
			if(!(name.substr(0,1).compare("i"))){ 
				createList<int>(&vectorOfiList, listType, name, &outputStream);
				//cout << "post-operation list size: " << vectorOfiList.size() <<endl << endl;
			}

			else if(!(name.substr(0,1).compare("d"))){
				createList<double>(&vectorOfdList, listType, name, &outputStream);
				//cout << endl << endl;
			}

			else if(!(name.substr(0,1).compare("s"))){
				createList<string>(&vectorOfsList, listType, name, &outputStream);
				//cout << endl << endl;
			}
		}

		else if(!operation.compare("pop")){
		//example: pop d99
			if(!(name.substr(0,1).compare("i"))){
				searchToPop<int>(&vectorOfiList, name, &outputStream);
			}
			else if(!(name.substr(0,1).compare("d"))){
				searchToPop<double>(&vectorOfdList, name, &outputStream);
			}

			else if(!(name.substr(0,1).compare("s"))){
				searchToPop<string>(&vectorOfsList, name, &outputStream);
			}
			
		}

		else if(!operation.compare("push")){
			//example: push i1 50 
			string insertValue;
			lineSplit >>  insertValue; //third value on line is what we push

			if(!(name.substr(0,1).compare("i"))){
				int converted = atoi(insertValue.c_str());
				searchToPush<int>(&vectorOfiList, name, converted, &outputStream);
			}
			else if(!(name.substr(0,1).compare("d"))){
				double converted = atof(insertValue.c_str());
				searchToPush<double>(&vectorOfdList, name, converted, &outputStream);
			}
			else if(!(name.substr(0,1).compare("s"))){
				string converted = insertValue;
				searchToPush<string>(&vectorOfsList, name, converted, &outputStream);
			}
		}
	}
}

int main(){
	string inputFile;
	string outputFile;

	cout <<"Enter name of input file: " <<endl;
	getline(cin, inputFile);
	cout <<"Enter name of output file: " <<endl;
	getline(cin, outputFile);
	cout << endl << endl;


	readInputCommandFile(inputFile, outputFile);
};
