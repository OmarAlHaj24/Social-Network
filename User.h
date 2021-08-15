#include <iostream>
#include "Treap.cpp"
#include "FriendLink.cpp"
using namespace std;

class User
{
    private:
        string userName, name, email;
        Treap<FriendLink<User>> friends;
    public:
        User();
        User(string userName, string name, string email);
        void setUserName(string);
        void setName(string);
        void setEmail(string);
        void addFriend(string userName, User& friendPtr);
        void printfriends();
        string getUserName();
        string getName();
        string getEmail();
        bool isFriend(User& user);
        FriendLink<User>* getFriend(string userName);
        bool removeFriend(string userName);

};

