/**
* @author - Hugh Hui
* @file doubly_linked_list.h -  This header file declares the methods which are coded in the doubly_linked_list.cpp file.
* 12/30/2024 - H. Hui created file and added comments.
* 2/28/2025 - PDavis imported doubly linked list class.
*
*/

#include "doubly_linked_list.h"
#include "dll_node.h"
extern std::ofstream& getOutFile();

DoublyLinkedList::DoublyLinkedList(){  // Constructor: Initializes the list to be empty
    head = nullptr;
    tail = nullptr;
    size = 0;
}//end Destructor

DoublyLinkedList::~DoublyLinkedList(){
    clear();
} // Destructor: Clears the list

/**
    *
    * getSize
    *
    * Method to check if the list is empty
    *
    * @param    nothing
    *
    * @return   int size of linked list
    */

    int DoublyLinkedList::getSize(){
        return size;
    }

 /**
    *
    * isEmpty
    *
    * Method to check if the list is empty
    *
    * @param    nothing
    *
    * @return   true if head pointer is nullptr, otherwise return false
    */
    bool DoublyLinkedList::isEmpty(){
        //If there is no head there is no data
        if(head == nullptr){
            return true;
        }
        else{
            return false;
        }//end if
    }//end isEmpty


    /**
    *
    * insertAtHead
    *
    * Method to insert a new node at the head of the list
    *
    * @param key    key for node to insert
    *
    * @return       nothing; updates doubly linked list and size
    */
    void DoublyLinkedList::insertAtHead(int key,DllNode* newNode){

        //if list is empty the head and tail will be the same node
        if(head == nullptr){
            head=tail=newNode;
        }else{
        //links the new head to the current head and sets the new node as the head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            
        }// end if
        size++;
    }//end insertAtHead


    /**
    *
    * insertAtTail
    *
    * Method to insert a new node at the tail of the list
    *
    * @param key    key for node to insert
    *
    * @return       nothing; updates doubly linked list and size
    */
    void DoublyLinkedList::insertAtTail(int key, DllNode*){
        //creates new tail node
        DllNode* newTail= new DllNode(key);
        //for an empty list the head and tail will both be the new node
        if(tail==nullptr){
            head =tail = newTail;
        }else{ 
            //Links the new tail to the end of the list and sets the new tail
            tail->next = newTail;
            newTail->prev = tail;
            tail = tail->next;
        }//end if
        size++;
    }//end insertAtTail


    /**
    *
    * remove
    *
    * Method to remove a node with a specific value from the list
    *
    * @param key    key for node to remove
    *
    * @return       nothing; updates doubly linked list
    */
    void DoublyLinkedList::remove(int key){
        if(isEmpty()){
            return;
        }
        //if the head matches remove it
        else if (head->key == key){
            removeHeaderNode();
        }
        //if the tail matches remove it
        else if(tail->key ==key){
            removeTailNode();
        }       
        else{
            //Iterate through the list until the key is found
            DllNode* temp = head->next;
            while(temp!=nullptr){
                if(temp->key==key){
                    //Set the next and prev pointers of the surrounding nodes to bypass the key node then delete the key node
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    size--;

                    delete temp;
                    return;
                }
                else{//Iterates through the Linked List
                    temp=temp->next;
                }
            }
        }//end if
        

    }// end remove


    /**
    *
    * removeHeaderNode
    *
    * Method to remove the header node (first node)
    *
    * @param        none
    *
    * @return       nothing; updates doubly linked list
    */
    void DoublyLinkedList::removeHeaderNode(){
        //check if list is empty
        if(isEmpty()){
            return;
        }
        DllNode* temp = head;
        //if the head and tail pointer are the same thers one node in the list and it can be deleted
        if(head==tail){
    
            head= tail = nullptr;     
        }
        else{
            //move the head pointer to the next node and set prev to nullptr then deletes the old head
            head =head->next;
            head->prev = nullptr;
        }//end if
        size--;
        delete temp;

    }//end removeHeaderNode


    /**
    *
    * removeTailNode
    *
    * Method to remove the tail node (last node)
    *
    * @param        none
    *
    * @return       nothing; updates doubly linked list
    */
    void DoublyLinkedList::removeTailNode(){
        //if list is empty nothing to remove
        if(isEmpty()){
            return;
        }
        DllNode* temp= tail;
        //if the head and tail pointer are the same there is one node and it can be deleted.
        if(head==tail){
            head=tail=nullptr;
        }
        else{
            //move tail pointer to previous node, set that nodes next to nullptr then delete old node
            tail = tail->prev;
            tail->next = nullptr;
        }//end if
        size--;
        delete temp;
        
    }//end removeTail Node


    /**
    *
    * moveNodeToHead
    *
    * Method to move a specific node to the head of the list
    *
    * @param key    key for node to move
    *
    * @return       nothing; updates doubly linked list
    */
    void DoublyLinkedList::moveNodeToHead(int key){
        //Check if the list is empty or the key is already at head
        if(isEmpty()||head->key == key){
            return;
        }else if(tail->key == key){
            //if node is at the tail disconnects it
            DllNode* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;

            //reconnects tail node to the front
            temp->next = head;
            temp->prev = nullptr;
            head->prev = temp;
            head = temp;
        }else{
            DllNode* temp = head->next;
            //search list for key
            while(temp!=nullptr){
                //When the key is found disconnect it from the list
                if(temp->key == key){
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;

                    //Then reconnects it at the head
                    temp->next = head;
                    head->prev = temp;
                    head = temp;
                    head->prev = nullptr;

                    
                    return;
                }
                else{//iterates through linked list
                    temp=temp->next;
                }//end if

            }//end while

        }//end if

    }//end moveNodeToHead

    /**
    *
    * moveNodeToHead
    *
    * Method to remove a node with a specific value from the list
    *
    * @param DllNode*   pointer for node to remove
    *
    * @return       nothing; updates doubly linked list
    */

    void DoublyLinkedList::moveNodeToHead(DllNode* move){
        if(move == nullptr||move == head){
            return;
        }
        else if(move==tail){
            tail = move->prev;
            tail->next = nullptr;
            move->next = head;
            move->prev = nullptr;
            head->prev = move;
            head = move;
        }
        else{
            move->next->prev = move->prev;
            move->prev->next = move->next;
            

            move->next = head;
            head->prev = move;
            head = move;
            head->prev = nullptr;
        }

    }


    /**
    *
    * moveNodeToTail
    *
    * Method to move a specific node to the tail of the list
    *
    * @param key    key for node to move
    *
    * @return       nothing; updates doubly linked list
    */
    void DoublyLinkedList::moveNodeToTail(int key){
        //check if list is empty or already at the tail
        if(isEmpty()||tail->key == key){
            return;
        }else if(head->key ==key){
            //if node to move is at the head disconnect and assign new head
            DllNode* temp = head;
            head = head->next;
            head->prev = nullptr;

            //reconnects the node at the tail
            tail->next = temp;
            temp->prev  = tail;
            tail = tail->next;
        }else{

            DllNode* temp = head;

        
            //runs list traversal
            while(temp!= nullptr){
                if(temp->key==key){
                    //Once key is found disconnects it from the list
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;

                    //reconnects it at the tail
                    tail->next = temp;
                    temp->prev = tail;
                    tail = temp;
                    tail->next =nullptr;

                    return;

                }//iterates through list
                else{
                    temp=temp->next;
                    }//end if

            }//end while
        
        }//end if

    }//end moveNodeToTail


    /**
    *
    * clear
    *
    * Method to clear the list by deleting all nodes
    *
    * @param        none
    *
    * @return       nothing; reset size to 0
    */
    void DoublyLinkedList::clear(){
        //while there are still nodes in the list remove the head node
        while(!isEmpty()){

            removeHeaderNode();
            
        }//end while

    }//end clear

    void DoublyLinkedList::printList(){
        DllNode* temp = head;
        std::ofstream& file = getOutFile();

        while(temp!= nullptr)
        {
            temp->printNode();
            temp=temp->next;

        }
    }