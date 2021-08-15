#include <iostream>
#include <fstream>
#include "LinkedList.cpp"
#ifndef user
#define user
#include "User.h"
#endif // user
using namespace std;

User* currUser = 0;
bool loggedIn = false;
LinkedList linkedList;

void start(){
    ifstream file;
    file.open("all-users.in");
    string data;
    while(getline(file, data)){
        string userName, name, email;
        int temp = 0, len = data.size();
        for(int i = 0; i < len; i++){
            if(data[i] != ','){
                if(temp == 0){
                    userName += data[i];
                }else if(temp == 1){
                    name += data[i];
                }else{
                    email += data[i];
                }
            }else{
                i++;
                temp++;
            }
        }
        User* tempUser = new User(userName, name, email);
        linkedList.add(*tempUser);
    }


    ifstream file2;
    file2.open("all-users-relations.in");
    while(getline(file2, data)){
        string userName1, userName2;
        int temp = 0, len = data.size();
        for(int i = 0; i < len; i++){
            if(data[i] != ','){
                if(temp == 0){
                    userName1 += data[i];
                }else if(temp == 1) {
                    userName2 += data[i];
                }
            }else{
                i++;
                temp++;
            }
        }
        User* temp1 = linkedList.getUser(userName1);
        User* temp2 = linkedList.getUser(userName2);
        temp1->addFriend(temp2->getUserName(), *temp2);
        /**
        //This is for testing
        cout<<"temp1 name = "<<temp1->getName()<<", his friends\n";
        temp1->printfriends();
        cout<<"end temp 1\n";
        cout<<"temp2 name = "<<temp2->getName()<<", his friends\n";
        temp2->printfriends();
        cout<<"end temp 2\n";
        **/
    }
}


void logIn(string userName){
    User* toTest = linkedList.getUser(userName);
    if(toTest != 0){
        currUser = toTest;
        loggedIn = true;
    }else{
        loggedIn = false;
    }
}


void logOut(){
    loggedIn = false;
    currUser = 0;
}


void exit(){
    exit(0);
}


void listAllFriends(){
    currUser->printfriends();
}


void menuOne(){
    while(true){
        string s;
        cout << "<--- Options Menu --->\n";
        cout << "Type 'Username' to be logged in\n";
        cout << "Type 'exit' to exit the program\n>>";
        cin >> s;
        if(s == "exit"){
            exit();
            break;
        }else{
            logIn(s);
            if(loggedIn){
                break;
            }else{
                cout<<"User not found\n";
            }
        }
    }
}


void menuTwo(){
    while(true){
        int input;
        cout << "<--- Options Menu --->\n";
        cout << "1- List all friends\n";
        cout << "2- Search by username\n";
        cout << "3- Add friend\n";
        cout << "4- Remove friend\n";
        cout << "5- People you may know\n";
        cout << "6- logout\n>>";
        cin >> input;
        if(input == 1){
            listAllFriends();
        }else if(input == 2){
            cout<<"username : ";
            string userName;cin>>userName;
            FriendLink<User>* temp = currUser->getFriend(userName);
            if(temp == 0){
                cout<<"not found\n";
            }else{
                cout<<temp->link->getUserName()<<", "<<temp->link->getName()<<", "<<temp->link->getEmail()<<"\n";
            }
        }else if(input == 3){
            cout<<"username : ";
            string userName;cin>>userName;
            User* temp = linkedList.getUser(userName);
            if(temp == 0){
                cout<<"There is no user with this username\n";
                continue;
            }
            if(!currUser->isFriend(*temp)){
                currUser->addFriend(temp->getUserName(), *temp);
                cout<<"You are now friends\n";
            }else{
                cout<<"You are already friends\n";
            }
        }else if(input == 4){
            cout<<"username : ";
            string userName;cin>>userName;
            bool deletedSuccessfully = currUser->removeFriend(userName);
            if(deletedSuccessfully){
                cout<<"Done\n";
            }
        }else if(input == 5){
            ///people you may know
            Node* temp = linkedList.getHead();
            int cnt = 5;
            while(cnt > 0 && temp != 0){
                if(!currUser->isFriend(*temp->data) && currUser->getUserName() != temp->data->getUserName()){
                    cout<<temp->data->getUserName()<<", "<<temp->data->getName()<<endl;
                    cnt--;
                }
                temp = temp->next;
            }
        }else if(input == 6){
            logOut();
            break;
        }else{
            cout << "Please enter a valid option\n";
        }
    }
}

int main(){
    start();
    while(true){
        if(!loggedIn){
            menuOne();
        }
        if(loggedIn){
            menuTwo();
        }
    }
    return 0;
}
