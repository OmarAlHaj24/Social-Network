#include "User.h"
#include <iostream>

User::User(){
   userName = "", name = "", email = "";
}

User::User(string userName, string name, string email){
    this->userName = userName;
    this->name = name;
    this->email = email;
}

///setters
void User::setUserName(string userName){
    this->userName = userName;
}

void User::setName(string name){
    this->name = name;
}

void User::setEmail(string email){
    this->email = email;
}


///getters
string User::getUserName(){
    return this->userName;
}

string User::getName(){
    return this->name;
}

string User::getEmail(){
    return this->email;
}

void User::addFriend(string userName, User& friendPtr){
    FriendLink<User> firstLink(userName, friendPtr);
    friends.add(firstLink);
    FriendLink<User> secLink(this->userName, *this);
    friendPtr.friends.add(secLink);
}


///in order traversal of the friends treap
void User::printfriends(){
    friends.inOrderTraversal();
}


///boolean function to test if two objects are friends or not
bool User::isFriend(User& user){
    FriendLink<User> a(user.getUserName(), user);
    return (friends.find(a) == 0) ? 0:1;
}


///function to return a friendLink to a user
FriendLink<User>* User::getFriend(string userName){
    FriendLink<User> temp(userName);
    return friends.findData(temp);
}


///function to remove friend given userName, it maintains the link of the two objects
bool User::removeFriend(string userName){
    FriendLink<User>* removedFriend = this->getFriend(userName);
    if(removedFriend != 0){
        this->friends.remove(*removedFriend);
        removedFriend->link->removeFriend(this->getUserName());
        return true;
    }
    return false;
}

