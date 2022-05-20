//
// Created by ariel on 26/11/2021.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "AVLTreeNode.h"
#include <iostream>
#include <cassert>

template <class T, class S>
class AVLTree{
    AVLTreeNode<T,S>* root;
    int size;
public:
    AVLTree() : root(nullptr), size(0) {}
    ~AVLTree();
    AVLTree(const AVLTree& tree);
    void removeNodeByKey(const T& key);
    void removeNodeByPointer(const AVLTreeNode<T,S>* node_to_remove);
    void setRoot(AVLTreeNode<T,S>* new_root);
    S* inOrderTraverse() const;
    S* limitedInOrderTraverse(int limit) const;
    S* inOrderReverseTraverse() const;
    S* limitedInOrderReverseTraverse(int limit) const;
    AVLTreeNode<T,S>& insert(const T& key, const S& data);
    AVLTreeNode<T,S>& insertAndGet(const T& key, const S& data, AVLTreeNode<T,S>*& new_node);
    const AVLTreeNode<T,S>& getRoot() const;
    AVLTreeNode<T,S>* findNode(const T& key);
    AVLTreeNode<T,S>& getMax() const;
    int getSize() const;
    static AVLTreeNode<T,S>* buildTreeFromSortedArr(T* key_arr, S* data_arr, int start, int end, int global_end, AVLTreeNode<T,S>*& max);
    void setTreeNewMembers(AVLTreeNode<T,S>* root, int size);
private:
    //================ utility functions =====================
    AVLTreeNode<T,S>* findNodeUtils(AVLTreeNode<T,S>* node, const T& key);
    AVLTreeNode<T,S>* removeNodeByKeyUtility(AVLTreeNode<T,S>* node, const T& key);
    AVLTreeNode<T,S>* insertUtility(AVLTreeNode<T,S>* node, const T& key, const S& data, AVLTreeNode<T,S>*& new_node);
    void deleteTreeUtility(AVLTreeNode<T,S>* node);
    void copyTreeUtility(AVLTreeNode<T,S>* node);
    void inOrderTraverseUtility(const AVLTreeNode<T,S>* node, S* data_array, int& counter) const;
    void limitedInOrderTraverseUtility(const AVLTreeNode<T,S>* node, int& limit, S* data_array, int& counter) const;
    void inOrderReverseTraverseUtility(const AVLTreeNode<T,S>* node, S* data_array, int& counter) const;
    void limitedInOrderReverseTraverseUtility(const AVLTreeNode<T,S>* node, int& limit, S* data_array, int& counter) const;

    AVLTreeNode<T,S>& getMaxUtility(AVLTreeNode<T, S>* node) const;
    AVLTreeNode<T,S>* balanceTree(AVLTreeNode<T,S>* node);
    AVLTreeNode<T,S>* rotateRR(AVLTreeNode<T,S>* node);
    AVLTreeNode<T,S>* rotateLR(AVLTreeNode<T,S>* node);
    AVLTreeNode<T,S>* rotateRL(AVLTreeNode<T,S>* node);
    AVLTreeNode<T,S>* rotateLL(AVLTreeNode<T,S>* node);
    AVLTreeNode<T,S>* minimalNode(AVLTreeNode<T,S>* node, AVLTreeNode<T,S>*& parent);
    int getBalanceFactor(AVLTreeNode<T,S>* node);
    void updateHeight(AVLTreeNode<T,S>* node);

};

template <class T, class S>
AVLTree<T,S>::~AVLTree() {
    deleteTreeUtility(root);
    this->root = nullptr;
}

template<class T, class S>
AVLTree<T,S>::AVLTree(const AVLTree& tree){
    size = 0; //in copy tree there's insert, increases size
    root = nullptr;
    copyTreeUtility(tree.root);
}

template <class T, class S>
void AVLTree<T,S>::copyTreeUtility(AVLTreeNode<T,S>* node) {
    if (node == nullptr)
        return;
    if(node->getRight())
        copyTreeUtility(node->getRight());
    if(node->getLeft())
        copyTreeUtility(node->getLeft());
    insert(node->getKey(), node->getData());
}

template <class T, class S>
void AVLTree<T,S>::deleteTreeUtility(AVLTreeNode<T,S>* node) {
    if (node == nullptr)
        return;
    if(node->getRight()){
        deleteTreeUtility(node->getRight());;
        node ->setRight(nullptr);
    }
    if(node->getLeft()){
        deleteTreeUtility(node->getLeft());
        node ->setLeft(nullptr);
    }
    delete node;
}

template <class T, class S>
void AVLTree<T,S>::updateHeight(AVLTreeNode<T,S>* node) {
    node->setHeight( 1 + std::max(node->getLeft()?node->getLeft()->getHeight():-1, node->getRight()?node->getRight()->getHeight():-1));
}

template <class T, class S>
int AVLTree<T,S>::getBalanceFactor(AVLTreeNode<T,S>* node) {
    int left_height = node->getLeft()?node->getLeft()->getHeight():-1;
    int right_height = node->getRight()?node->getRight()->getHeight():-1;
    return left_height - right_height;
}

template <class T , class S>
AVLTreeNode<T,S>* AVLTree<T,S>::balanceTree(AVLTreeNode<T,S> *node) {
    if(!node)
        return nullptr;
    int balance_factor = getBalanceFactor(node);
    if (balance_factor > 1)
    {
        if(getBalanceFactor(node->getLeft()) == -1)
            node = rotateLR(node);
        else
            node = rotateLL(node);
    }
    else if (balance_factor < -1)
    {
        if(getBalanceFactor(node->getRight()) == 1)
            node = rotateRL(node);
        else
            node = rotateRR(node);
    }
    return node;
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::rotateLL(AVLTreeNode<T,S> *node) {
    AVLTreeNode<T,S>* node_a = node->getLeft();
    node->setLeft(node_a->getRight());
    node_a->setRight(node);
    updateHeight(node);
    updateHeight(node_a);
    return node_a;
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::rotateRR(AVLTreeNode<T,S> *node) {
    AVLTreeNode<T,S>* node_a = node->getRight();
    node->setRight(node_a->getLeft());
    node_a->setLeft(node);
    updateHeight(node);
    updateHeight(node_a);
    return node_a;
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::rotateLR(AVLTreeNode<T,S> *node) {
    AVLTreeNode<T,S>* node_a = node->getLeft();
    AVLTreeNode<T,S>* node_b = node_a->getRight();
    node_a->setRight(node_b->getLeft());
    node->setLeft(node_b->getRight());
    node_b->setLeft(node_a);
    node_b->setRight(node);
    updateHeight(node);
    updateHeight(node_a);
    updateHeight(node_b);
    return node_b;
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::rotateRL(AVLTreeNode<T,S> *node) {
    AVLTreeNode<T,S>* node_a = node->getRight();
    AVLTreeNode<T,S>* node_b = node_a->getLeft();
    node_a->setLeft(node_b->getRight());
    node->setRight(node_b->getLeft());
    node_b->setRight(node_a);
    node_b->setLeft(node);
    updateHeight(node);
    updateHeight(node_a);
    updateHeight(node_b);
    return node_b;
}

template <class T, class S>
AVLTreeNode<T,S>& AVLTree<T,S>::insert(const T& key, const S& data) {
    AVLTreeNode<T,S>* dummy_new_node;
    this->setRoot(insertUtility(root, key, data, dummy_new_node));
    size++;
    return *(this->root);
}

template <class T, class S>
AVLTreeNode<T,S>& AVLTree<T,S>::insertAndGet(const T& key, const S& data, AVLTreeNode<T,S>*& new_node) {
    this->setRoot(insertUtility(root, key, data, new_node));
    size++;
    return *(this->root);
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::insertUtility(AVLTreeNode<T,S>* node, const T& key, const S& data, AVLTreeNode<T,S>*& new_node){
    if (node == nullptr){
        node = new AVLTreeNode<T,S>(key,data);
        //node->setHeight(0);
        node->setLeft(nullptr);
        node->setRight(nullptr);
        new_node = node;
        return node;
    }
    // insert node
    T node_key = node->getKey();
    if (key < node_key) {
        node->setLeft(insertUtility(node->getLeft(), key, data, new_node));
    }
    else if (key > node_key) {
        node->setRight(insertUtility(node->getRight(), key, data, new_node));
    }
    else {
        return node;
    }

    //update heights
    updateHeight(node);

    //check if tree remains balanced, if not balanced- fix it
    int balance_factor = getBalanceFactor(node);
    if (balance_factor < -1 || balance_factor > 1)
        node = balanceTree(node);
    return node;
}

//gets minimal valued node in the subtree of the given node
template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::minimalNode(AVLTreeNode<T,S>* node, AVLTreeNode<T,S>*& parent){
    AVLTreeNode<T,S>* current_node = node;
    parent = nullptr;
    while(current_node->getLeft()) {
        parent = current_node;
        current_node = current_node->getLeft();
    }
    return current_node;
}

template <class T, class S>
void AVLTree<T,S>::removeNodeByKey(const T& key) {
    this->setRoot(removeNodeByKeyUtility(root, key));
    size--;
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::removeNodeByKeyUtility(AVLTreeNode<T,S>* node, const T& key) {
    if (node == nullptr)
        return node;
    T node_key = node->getKey();
    if(key < node_key)
        node->setLeft(removeNodeByKeyUtility(node->getLeft(), key));
    else if (key > node_key)
        node->setRight(removeNodeByKeyUtility(node->getRight(), key));

    //node have two children
    else if (node->getRight() && node->getLeft()){
        AVLTreeNode<T,S>* min_node_parent;
        AVLTreeNode<T,S>* min_node = minimalNode(node->getRight(), min_node_parent);
        AVLTreeNode<T,S>* old_node = node;
        node = min_node;
        AVLTreeNode<T,S>* min_node_right = nullptr;
        if (node->getRight()){
            min_node_right = node->getRight();
        }
        if (min_node_parent){
            min_node_parent->setLeft(min_node_right);
            node->setRight(old_node->getRight());
        }
        node->setLeft(old_node->getLeft());
        delete old_node;
    }
    //one or zero children
    else {
        AVLTreeNode<T,S> *temp = (node->getRight()) ? node->getRight() : node->getLeft();
        if (temp == nullptr) { //zero children
            temp = node;
            node = nullptr;
        } else { //one child
            AVLTreeNode<T,S> *temp2 = node;
            node = temp;
            temp = temp2;
        }
        delete temp;
        if (node == nullptr)
            return node;
        }
        //update height and re-balance the tree if needed
        updateHeight(node);
        int balance_factor = getBalanceFactor(node);
        if (balance_factor < -1 || balance_factor > 1 )
            node = balanceTree(node);
        return node;
}

template <class T, class S>
void AVLTree<T,S>::removeNodeByPointer(const AVLTreeNode<T,S>* node_to_remove){
    if(!node_to_remove)
        return;
    removeNodeByKey(node_to_remove->getKey());
}

//full traverse inOrder from smallest element to largest
template <class T, class S>
S* AVLTree<T,S>::inOrderTraverse() const{
    S* data_array = (S*)malloc(sizeof(S)*this->getSize());
    int counter = 0;
    inOrderTraverseUtility(&(this->getRoot()), data_array, counter);
    return data_array;
}

template <class T, class S>
void AVLTree<T,S>::inOrderTraverseUtility(const AVLTreeNode<T,S>* node, S* data_array, int& counter) const{
    if(!node)
        return;
    inOrderTraverseUtility(node->getLeft(), data_array, counter);
    *(data_array+counter) = node->getData();
    counter++;
    inOrderTraverseUtility(node->getRight(),data_array, counter);
}

// limited traverse inOrder from smallest element to largest
template <class T, class S>
S* AVLTree<T,S>::limitedInOrderTraverse(int limit) const{
    S* data_array = (S*)malloc(sizeof (S) * limit);
    int counter = 0;
    limitedInOrderTraverseUtility(&(this->getRoot()), limit, data_array, counter);
    return data_array;
}

template <class T, class S>
void AVLTree<T,S>::limitedInOrderTraverseUtility(const AVLTreeNode<T,S>* node, int& limit, S* data_array, int& counter) const{
    if(!node || limit == 0 )
        return;
    limitedInOrderTraverseUtility(node->getLeft(), limit, data_array, counter);
    if(limit == 0)
        return;
    *(data_array+counter) = node->getData();
    --limit;
    ++counter;
    limitedInOrderTraverseUtility(node->getRight(),limit,data_array, counter);
}

//full traverse inOrder from largest element to smallest
template <class T, class S>
S* AVLTree<T,S>::inOrderReverseTraverse() const{
    S* data_array = (S*)malloc(sizeof(S)* this->getSize());
    int counter = 0;
    inOrderReverseTraverseUtility(&(this->getRoot()), data_array, counter);
    return data_array;
}

template <class T, class S>
void AVLTree<T,S>::inOrderReverseTraverseUtility(const AVLTreeNode<T,S>* node, S* data_array, int& counter) const{
    if(!node)
        return;
    inOrderReverseTraverseUtility(node->getRight(), data_array, counter);
    *(data_array+counter) = node->getData();
    ++counter;
    inOrderReverseTraverseUtility(node->getLeft(), data_array, counter);
}

//limited traverse inOrder from largest element to smallest
template <class T, class S>
S* AVLTree<T,S>::limitedInOrderReverseTraverse(int limit) const{
    S* data_array = (S*)malloc(sizeof (S)* limit);
    int counter = 0;
    limitedInOrderReverseTraverseUtility(&(this->getRoot()), limit, data_array, counter);
    return data_array;
}

template <class T, class S>
void AVLTree<T,S>::limitedInOrderReverseTraverseUtility(const AVLTreeNode<T,S>* node, int& limit, S* data_array, int& counter) const{
    if(!node || limit ==0)
        return;
    limitedInOrderReverseTraverseUtility(node->getRight(), limit, data_array, counter);
    if(limit == 0)
        return;
    *(data_array+counter) = node->getData();
    --limit;
    ++counter;
    limitedInOrderReverseTraverseUtility(node->getLeft(), limit, data_array, counter);
}

template<class T, class S>
AVLTreeNode<T,S>& AVLTree<T,S>::getMax() const{
    if (root == nullptr){
        return *root;
    }
    return getMaxUtility(root);
}

template<class T, class S>
AVLTreeNode<T,S>& AVLTree<T,S>::getMaxUtility(AVLTreeNode<T, S>* node) const{
    if (node->getRight() == nullptr){
        return *node;
    }
    return getMaxUtility(node->getRight());
}

template <class T, class S>
const AVLTreeNode<T,S>& AVLTree<T,S>::getRoot() const{
    return *(this->root);
}

template <class T, class S>
void AVLTree<T,S>::setRoot(AVLTreeNode<T,S> *new_root) {
    this->root = new_root;
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::findNode(const T& key) {
    return findNodeUtils(this->root, key);
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::findNodeUtils(AVLTreeNode<T,S>* node,const T& key) {
    if (node == nullptr){
        return nullptr;
    }
    T node_key = node->getKey();
    if(key == node_key)
        return node;
    else if(key < node_key)
        return findNodeUtils(node->getLeft(), key);
    else if (key > node_key)
        return findNodeUtils(node->getRight(),key);
    return nullptr;

}

template<class T, class S>
int AVLTree<T, S>::getSize() const {
    return size;
}

template<class T, class S>
AVLTreeNode<T,S>* AVLTree<T,S>::buildTreeFromSortedArr(T* key_arr, S* data_arr, int start, int end, int global_end, AVLTreeNode<T,S>*& max) {
    if (start>end){
        return nullptr;
    }
    int middle = (end+start)/2;
    AVLTreeNode<T,S>* node = new AVLTreeNode<T,S>(key_arr[middle], data_arr[middle]);
    assert(data_arr[middle] == node->getData());
    if (middle == global_end){
        max = node;
    }
    node->setRight(buildTreeFromSortedArr(key_arr, data_arr, middle+1, end, global_end, max));
    node->setLeft(buildTreeFromSortedArr(key_arr, data_arr, start, middle-1, global_end, max));
    return node;
}

template<class T, class S>
void AVLTree<T, S>::setTreeNewMembers(AVLTreeNode<T, S> *root, int size) {
    AVLTreeNode<T, S> * temp = this->root;
    this->root = root;
    delete temp;
    this->size = size;
}


#endif //WET1_AVLTREE_H
