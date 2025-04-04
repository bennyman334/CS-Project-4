#ifndef BSTSET
#define BSTSET

#include <iostream>
using namespace std;

template <typename T>
class BSTSet {
    
private:
    struct Node {
        Node(T val): value(val), left(nullptr), right(nullptr) {}
        Node* left;
        Node* right;
        //Node* parent;
        T value;
    };
    Node* m_root;
    int m_size;
    
    void destroyBST (Node* head);
    
public:
    //Node* m_root;
    BSTSet(): m_root(nullptr), m_size(0) {}
    ~BSTSet();
    
    void printSize() const {
        cout << "Size: " << m_size << endl;
    }
    
    T smallestValue () const {
        Node* cur = m_root;
        while(cur->left != nullptr) {
            cur = cur->left;
        }
        return cur;
    }
    
    class SetIterator{
    public:
        SetIterator(Node* n, Node* root);
        //~SetIterator();
        const T* get_and_advance();
    private:
        Node* m_cur;
        Node* m_setRoot;
    };
    
    void insert(const T& value);
    SetIterator find(const T& value) const;
    SetIterator find_first_not_smaller(const T& value) const;
    
};

template<typename T>
BSTSet<T>::~BSTSet<T>() {
    destroyBST(m_root);
}

template<typename T>
void BSTSet<T>::destroyBST(Node* head) {
    if(head == nullptr) {
        return;
    }
    destroyBST(head->left);
    destroyBST(head->right);
    delete head;
}

template<typename T>
BSTSet<T>::SetIterator::SetIterator(Node *n, Node* root) {
    m_cur = n;
    m_setRoot = root;
}


template<typename T>
void BSTSet<T>::insert(const T &value) {
    m_size ++;
    if(m_root == nullptr) { //
        m_root = new Node(value);
        //cout << "inserted at root" << endl;
        return;
    }
    Node* trav = m_root;
    while(trav != nullptr) {
        if(value < trav->value) {
            if(trav->left == nullptr){
                trav->left = new Node(value);
                //cerr << "inserted left" << endl;
                break;
            }
            trav = trav->left;
        } else if (trav->value < value) {
            if(trav->right == nullptr){
                trav->right = new Node(value);
                //cerr << "inserted right" << endl;
                break;
            }
            trav = trav->right;
        } else if (trav->value == value) { //equality DO WE NEED TO DO SOMETHING???
            trav->value = value;
            break;
        } else { //same departure BUT NOT same flight
            if(trav->left == nullptr){
                trav->left = new Node(value);
                //cerr << "inserted left" << endl;
                break;
            }
            trav = trav->left;
        }
    }
    
}

template<typename T>
typename BSTSet<T>::SetIterator BSTSet<T>::find(const T& value) const {
    Node* trav = m_root;
    while(trav != nullptr) {
        if(value < trav->value) {
            trav = trav->left;
        } else if (trav->value < value) {
            trav = trav->right;
        } else if (trav->value == value){ //equality
            break;
        } else {
            trav = trav->left;
        }
    }
    return SetIterator(trav, m_root); //if trav == nullptr, will return an invalid SetIterator
}

template<typename T>
typename BSTSet<T>::SetIterator BSTSet<T>::find_first_not_smaller(const T& value) const {
    Node* trav = m_root;
    Node* notSmaller = nullptr;
    while(trav != nullptr) {
        if(value < trav->value) {
            notSmaller = trav;
            trav = trav->left;
            //notSmaller = trav;
        } else if (trav->value < value) {
            trav = trav->right;
        } else { //equality
            notSmaller = trav;
            break;
        }
    }
    //cout << notSmaller->value << endl;
    return SetIterator(notSmaller, m_root); //if notSmaller == nullptr, returns an invalid SetIterator
}


template<typename T>
const T* BSTSet<T>::SetIterator::get_and_advance (){
    
    if(m_cur == nullptr) {
        return nullptr;
    }
    
    T* curVal = &m_cur->value;
    
    
    if(m_cur->right != nullptr) { //if current node has a right branch
        m_cur = m_cur->right;
        //cout << "has a right branch" << endl;
        while(m_cur->left != nullptr) { //move m_cur as far left in the right branch as possible
            m_cur = m_cur->left;
        }
    } else {
        Node* trav = m_setRoot; //used to traverse from
        Node* next = nullptr;
        
        while(trav != nullptr) {
            if(m_cur->value < trav->value) { //if
                next = trav;
                trav = trav->left;
            } else if (trav->value < m_cur->value) {
                trav = trav->right;
            } else {
                break;
            }
            //cout << "has a left branch" << endl;
        }
        m_cur = next;
    }
    //return &m_cur->value;
    return curVal;
    //return nullptr;
    
}

//template<typename T>
//BSTSet<T>::Node* BSTSet<T>::SetIterator::findAncestor(Node *cur) {
//    if(
//}

//template<typename T>
//BSTSet<T>::Node* BSTSet<T>::SetIterator::findNext(Node* head, T x) {
//    if(head == nullptr){
//        return nullptr;
//    }
//    if(head->value < x) {
//        Node* next = findNext(head->right, x);
//    } else {
//        
//    }
//    //
//}


#endif
