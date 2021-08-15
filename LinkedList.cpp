#ifndef MAINHEADER

#define MAINHEADER
#include <iostream>

#ifndef user
#define user
#include "User.h"
#endif // user
using namespace std;


#endif // MAINHEADER

///node of the linked list
struct Node{
    User* data = 0;
    Node* next = 0;
    Node* prv = 0;
};

class LinkedList{
    private:
        ///initializing the head and tail to nullptr
        Node* head = 0;
        Node* tail = 0;

    public:

        ///function to add new Item to the list(add from head)
        void add(User& newData){
            Node* newNode = new Node;
            newNode->data = &newData;
            if(head == 0){
                head = tail = newNode;
            }else{
                newNode->next = head;
                head->prv = newNode;
                head = newNode;
            }
        }

        Node* getHead(){
            return head;
        }

        ///function to return a user given it's userName
        User* getUser(string userName){
            ///handle if empty linkedList
            if(head == 0){
                return 0;
            }

            ///point to head
            Node* temp = head;

            ///searching for the user
            while(temp != 0){
                if(temp->data->getUserName() == userName){
                    return temp->data;
                }
                temp = temp->next;
            }

            ///not exists return nullptr
            return 0;
        }

        void removeUser(string userName){
            ///handle if empty linkedList
            if(head == 0){
                return;
            }

            Node* toDel = 0;

            ///handle if there is only one node in the linkedlist
            if(head == tail && head->data->getUserName() == userName){
                toDel = head;
                head = tail = 0;
                delete toDel;
                return;
            }

            ///delete the node if exists
            if(head->data->getUserName() == userName){
                toDel = head;
                head->next->prv = 0;
                head = head->next;
                delete toDel;
            }else if(tail->data->getUserName() == userName){
                toDel = tail;
                tail->prv->next = 0;
                tail = tail->prv;
                delete toDel;
            }else{
                ///point to head
                toDel = head;

                while(toDel != 0 && toDel->data->getUserName() != userName){
                    toDel = toDel->next;
                }

                ///this user exist
                if(toDel != 0){
                    ///delete without memory leak
                    toDel->prv->next = toDel->next;
                    toDel->next->prv = toDel->prv;
                    delete toDel;
                }
            }
        }

        void searchAllUsers(){
            if(head != 0){
                Node* temp = head;
                while(temp != tail){
                    cout<<temp->data->getUserName()<<"->";
                    temp = temp->next;
                }
                cout<<tail->data->getUserName()<<endl;
            }
        }

        ///destructor to free up the reserved space
        ~LinkedList(){
            Node* temp = head;
            while(temp != 0){
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }

};
