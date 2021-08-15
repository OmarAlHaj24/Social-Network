#include <iostream>
#include <string.h>
using namespace std;

template <class Type>
class FriendLink{
    public:
        string friendUserName = "";
        Type* link = 0;
    public:

        FriendLink(){
        }

        FriendLink(string userName, Type& newFriend){
            link = &newFriend;
            friendUserName = userName;
        }

        FriendLink(string userName){
            friendUserName = userName;
        }

        Type* getType(){
            return link;
        }

        bool operator > (FriendLink obj){
            return (this->friendUserName.compare(obj.friendUserName) > 0);
        }

        bool operator < (FriendLink obj){
            return (this->friendUserName.compare(obj.friendUserName) < 0);
        }

        bool operator <= (FriendLink obj){
            return (this->friendUserName.compare(obj.friendUserName) <= 0);
        }

        bool operator >= (FriendLink obj){
            return (this->friendUserName.compare(obj.friendUserName) >= 0);
        }

        bool operator == (FriendLink obj){
            return (this->friendUserName.compare(obj.friendUserName) == 0);
        }

        friend ostream& operator << (ostream& out, FriendLink<Type> &b){
            out<<b.friendUserName<<", "<<b.link->getName();
            return out;
        }

};



