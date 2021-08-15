#ifndef TREAPHEADER
#define TREAPHEADER

#include <iostream>
#include <random>
using namespace std;


template <class T>
class treapNode{
    T data;
    long long priority;
    treapNode* left;
    treapNode* right;


public:

    treapNode(){
        left = 0;
        right = 0;
        priority = rand() %10000;
    }

    treapNode(T& data){
        this->data = data;
        left = 0;
        right = 0;
    }

    treapNode(T& data, long long priority){
        this->data = data;
        left = 0;
        right = 0;
        this->priority = priority;
    }

    treapNode(T& data, treapNode* left, treapNode* right){
        this->data = &data;
        this->left = left;
        this->right = right;
    }

    T& getData(){
        return data;
    }

    treapNode* getLeft(){
        return left;
    }

    treapNode* getRight(){
        return right;
    }

    long long getPriority(){
        return priority;
    }

    void setData(T& data){
        this->data = &data;
    }

    void setLeft(treapNode* left){
        this->left = left;
    }

    void setRight(treapNode* right){
        this->right = right;
    }

    void displayNodeInfo(){
        cout<<data<<endl;
    }


};

template <class T>
class Treap{

    treapNode<T>* root;

    void inOrderTraversal(treapNode<T>* curr){
        if(!curr)
            return;
        inOrderTraversal(curr->getLeft());
        curr->displayNodeInfo();
        inOrderTraversal(curr->getRight());
    }

    void preOrderTraversal(treapNode<T>* curr){
        if(!curr)
            return;
        curr->displayNodeInfo();
        inOrderTraversal(curr->getLeft());
        inOrderTraversal(curr->getRight());
    }

    treapNode<T>* rotateRight(treapNode<T>* curr){
        treapNode<T>* leftChild = curr->getLeft();
        treapNode<T>* leftRightGC = leftChild->getRight();

        leftChild->setRight(curr);
        curr->setLeft(leftRightGC);

        return leftChild;
    }

    treapNode<T>* rotateLeft(treapNode<T>* curr){
        treapNode<T>* rightChild = curr->getRight();
        treapNode<T>* rightLeftGC = rightChild->getLeft();

        rightChild->setLeft(curr);
        curr->setRight(rightLeftGC);

        return rightChild;

    }

    treapNode<T>* add(treapNode<T>* curr,T& data){

        if(curr == 0)
            return new treapNode<T>(data);

        if(data > curr->getData())
            curr->setRight(add(curr->getRight(), data));
        else if(data < curr->getData())
            curr->setLeft(add(curr->getLeft(), data));
        else
            return curr;

        if(curr->getLeft() != 0){
            if(curr->getLeft()->getPriority() < curr->getPriority()){
                curr = rotateRight(curr);
            }
        }

        if(curr->getRight() != 0){
            if(curr->getRight()->getPriority() < curr->getPriority()){
                curr = rotateLeft(curr);
            }
        }

        return curr;
    }

    treapNode<T>* add(treapNode<T>* curr,T& data, long long prio){

        if(curr == 0)
            return new treapNode<T>(data, prio);

        if(data > curr->getData())
            curr->setRight(add(curr->getRight(), data, prio));
        else if(data < curr->getData())
            curr->setLeft(add(curr->getLeft(), data, prio));
        else
            return curr;

        if(curr->getLeft() != 0){
            if( (curr->getLeft()->getPriority()) < curr->getPriority()){
                curr = rotateRight(curr);
            }
        }

        if(curr->getRight() != 0){
            if(curr->getRight()->getPriority() < curr->getPriority()){
                curr = rotateLeft(curr);
            }
        }

        return curr;
    }

    treapNode<T>* removeThisNode(treapNode<T>* curr){
        treapNode<T>* left = curr->getLeft();
        treapNode<T>* right = curr->getRight();
        if(left == 0 && right == 0){
            return 0;
        }

        //danger: cannot replace curr->getLeft() with left because curr is updated
        else if(left == 0 && right != 0){
            curr = rotateLeft(curr);
            curr->setLeft( removeThisNode(curr->getLeft()) );
        }

        //danger: cannot replace curr->getRight() with right because curr is updated
        else if(left != 0 && right == 0){
            curr = rotateRight(curr);
            curr->setRight( removeThisNode(curr->getRight()) );
        }

        //danger: same warning as above
        else{
            if( (left->getPriority() ) < (right->getPriority()) ){
                curr = rotateRight(curr);
                curr->setRight( removeThisNode(curr->getRight()) );
            }
            else{
                curr = rotateLeft(curr);
                curr->setLeft( removeThisNode(curr->getLeft()) );
            }
        }

        return curr;

    }

    //recursive implementation is a must
    treapNode<T>* remove(treapNode<T>* curr, T& data){
        T currData = curr->getData();
        if(currData == data){
            curr = removeThisNode(curr);
        }
        if(data > currData){
            curr->setRight(remove(curr->getRight(), data));
        }
        if(data < currData){
            curr->setLeft(remove(curr->getLeft(), data));
        }
        return curr;
    }

public:
    Treap(){
        root = 0;
    }

    Treap(T& data){
        root = new treapNode<T>(data, 0, 0);
    }

    //returns a pointer to the node if found, null if not found
    treapNode<T>* find(T& d){
        treapNode<T>* curr = root;

        while(curr != 0){
            T currentData = curr->getData();

            if(currentData == d)
                return curr;
            if(d > currentData)
                curr = curr->getRight();
            else
                curr = curr->getLeft();
        }

        return 0;

    }

    T* findData(T& d){
        treapNode<T>* curr = root;

        while(curr != 0){
            T currentData = curr->getData();

            if(currentData == d)
                return &curr->getData();
            if(d > currentData)
                curr = curr->getRight();
            else
                curr = curr->getLeft();
        }

        return 0;

    }

     treapNode<T>* find(string str){
        treapNode<T>* curr = root;
        T d(str);
        while(curr != 0){
            T currentData = curr->getData();

            if(currentData == d)
                return curr;
            if(d > currentData)
                curr = curr->getRight();
            else
                curr = curr->getLeft();
        }

        return 0;

    }

    void add(T& d){
        root = add(root, d);
    }

    void add(T& d, long long prio){
        root = add(root, d, prio);
    }

    //this is the only way to implement remove because
    //the only way to alter any node in the tree is to alter the root
    void remove(T& data){
        root = remove(root, data);
    }


    void inOrderTraversal(){
        inOrderTraversal(root);
    }

    void preOrderTraversal(){
        preOrderTraversal(root);
    }

};

#endif // TREAPHEADER


