#include<bits/stdc++.h>
using namespace std;

//structure of a Node
template <class Type>
struct nodeType
{
    Type info;
    nodeType * link;
};

/*
----------------------------------Class Iteraators to a linked list------------------------
*/
template <class Type>
class linkedListIterator{
    nodeType<Type> * current;
    public:
    linkedListIterator(){current = NULL;}
    linkedListIterator(nodeType<Type> *ptr);
    Type operator*();
    linkedListIterator<Type> operator++(){
        current = current->link;
        return *this;}
    bool operator==( linkedListIterator <Type> &);
    bool operator!=( linkeListIterator <Type> &){return (current != right.current;)};
};//class ends here

/*//default constructor
template <class Type>
linkedListIterator<Type> :: linkedlistIterator(){
    current = NULL;
}*/

//constructor with a parameter
template <class Type>
linkedListIterator<Type> :: linkedListIterator(nodeType<Type> *ptr){
    current = ptr;
}

//function for overloading the derefencing operator
template <class Type>
Type linkedListIterator<Type> ::  operator*(){
    return current->info;
}

//function for overloading the increment operator
/*template <class Type>
linkedListIterator<Type> linkedListIterator<Type> ::operator++{
    current = current->link;
    return *this;
}*/

//function for overloading the == operator
template <class Type>
bool linkedListIterator<Type> :: operator==(linkedListIterator<Type>& right){
    return(current == right.current);
}

/*//function for overloading the != operator
template <class Type>
bool linkedListIterator<Type> :: operator != (linkedListIterator<Type> &right){
    return (current != right.current;)
}*/
/*
--------------------------------Iterator Class Ends Here---------------------------------------------
*/

//Abstract class to implement the basic properties of a linked list

template <class Type>
class linkedListType{
    void copyList(linkedListType<Type> &otherList);
    protected:
    int count;//for storing number of elements
    nodeType<Type> *first;//pointer to the node of a list
    nodeType<Type> *last;//pointer to last node of a list
    public:
    void initializeList();
    bool isEmptyList();
    void print();
    int length();
    void destroyList();
    Type front();
    Type back();
    bool search(Type &) = 0;
    void insertFirst(Type &) = 0;
    void insertLast(Type &) = 0;
    void deleteNode(Type &) = 0;
    linkedListIterator<Type> begin();
    linkedListIterator<Type> end();
    linkedListType();
    linkedListType(linkedListType<Type> &Type);
    ~linkedListType(); 
    linkedListType<Type>& operator=(linkedListType<Type> &Type);
};

//function to check if list is empty
template <class Type>
bool linkedListType<Type> :: isEmptyList(){
    return (first == NULL;)
}

//default constructor
template <class Type>
linkedListType<Type> ::linkedListType(){
    count = 0;
    first = NULL;
    last = NULL;
}

//destroy the list
template<class Type>
void linkedListType<Type> :: destroyList(){
    nodeType<Type> *temp;
    while (first != NULL)
    {
        temp = first;
        first = first->link;
        delete temp;
    }

    last = null;
    count = 0;
}

//initialize the list
template <class Type>
void linkedListType<Type>:: initializeList(){
    destroyList();//it initializes the list to an empty state
}       

//print the list
template<class Type>
void linkedListType<Type> :: print(){
    nodeType<Type> *current;
    current = first;
    while(current != NULL){
        cout<<current->info<<" ";
        current = current->link;
    }
}

//function to return the length of the list
template <class Type>
int linkedListType<Type> :: length(){
    return count;
}

//reterive the data of the first node
template <class Type>
Type linkedListType<Type> :: front(){
    assert(first != NULL);//assertions are usually used to check the logicallyimpossible situations
    return first->info;
}

//reterive the data of last node
template <class Type>
Type linkedListType<Type> :: back(){
    assert(last != NULL);
    return last->info;
}

//begin and end functions
template <class Type>
linkedListIterator<Type> linkedListType <Type>:: begin(){
    linkedListIterator<Type> temp(first);
    return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type> :: end(){
    linkedListIterator<Type> temp(NULL);
    return temp;
}

//copy the list
template <class Type>
void linkedListType<Type> :: copyList(linkedListType <Type> &otherList){
    nodeType<Type> *newNode;
    nodeType<Type> *current;

    if(first != NULL)
        destroyList();

    if(otherList.first == NULL){
        first = NULL;
        last = NULL;
        count = 0;
    }
    else{
        current = otherList.first;
        count = otherList.count;
        first = new nodeType<Type>;//create the node
        first->info = current->info;//copy the info
        first->link = NULL;//first link points to NULL
        last = first;//make last point to the first node
        current = current->link; //current node pointnig to next node

        //copy the remaining the list
        while(current != NULL){
            newNode = new nodeType<Type>;//create a new node
            newNode->info = current->info;//copy the info
            newNode->link = NULL; //new node link points to NULL
            last->link = newNode;//attach new Node after last
            last = newNode;//make new Node as actual last node
            current = current->link;//current pointing to the next node
        }//ends while
    }//end else
}//ending copyList

//Destructor
template <class Type>
linkedListType<Type> :: ~linkedListType(){
    destroyList();
}

//copy consructor
template <class Type>
linkedListType<Type> :: linkedListType(linkedListType<Type> &otherList){
    firdt = NULL;
    copyList(otherList);
}//end copy constructor

//overloading the assignment operator
template <class Type>
linkedListType<Type>& linkedListType<Type> :: operator =(linkedListType<Type>& otherList){
    if(this != &otherList)//for avoiding the self copy
        copyList(otherList);
    return *this;
}
//* ---------------Abstract Class linkedListType Ends Here----------------------------------------*/

/*
------------------- Implementation of unordered linked list--------------------*/
template <class Type>
class unorderedLinkedList: public linkedListType<Type>{
    public :
        bool search(Type & seatchItem);
        void insertFirst(Type &newItem);
        void insertLast(Type &newItem);
        void deleteNode(Type &deleteNode);
};

//function for searching the list
template<class Type>
bool unorderedLinkedList<Type>::search(Type &searchItem){
    nodeType<Type> *current;
    bool found = false;
    current = first;
    while( current != NULL && !found){
        if(current->info == searchItem)
            found == true;
        else
            current = current->link;
        return found;

    }
}//funtion ends here

//inserFirst Function
template <class Type>
void unorderedLinkedList<Type>::insertFirst(Type &newItem){
    nodeType<Type> * newNode = new nodeType<Type>;
    newNode->info = newItem;
    newNode->link = first;
    first = newNode;
    count++;

    if(last == NULL)//if list is empty
        last = newNode;
}//insertFirst ends here

//insertEnd function 
template<class Type>
void unorderedLinkedList<Type>::insertLast(Type &newItem){
    nodeType<Type> *newNode = new nodeType<Type>;
    newNode->info = newItem;
    newNode->link = NULL;

    if(first == NULL){
        first = newNode;
        last = newNode;
        count++;
    }
    else{
        last->link = newNode;
        last = newNode;
        count++;
    }
}//insertEnd ends here

//function for deleting a node
template <class Type>
void unorderedLinkedList<Type>::deleteNode(Type &deleteItem){
    nodeType<Type> *current;
    nodeType<Type> *trialCurrent;//node just before current
    bool found;

    //case 1-> if list is empty
    if(first == NULL)
        cout<<"List is empty , and can not perform delete operation"<<endl;
    else{
        //case 2-> if delete node is first node
        if(first->info == deleteItem){
            current = first;
            first = first->link;
            count--;

            if(last == NULL)//if only one node
                last = NULL;
            delete current;
        }
        else{//search the node in the list for the given info
            found = false;
            trialCurrent = first;
            current = first->link;
            while(current != NULL && !found){
                if(current->info != deleteItem){
                    trialCurrent = current;
                    current = current->link;
                }
                else{
                    found = true;
                }
            }//end while

        if(found){
            trialCurrent->link = current->link;
            count--;

            if(last == current)
                last = trialCurrent;
            delete current;
        }
        else{
            cout<<"Item not found"<<endl;
        }//end else

        }//end else
    }//end else
}//end function


/*
int main(){

return 0;
}
*/