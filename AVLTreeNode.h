//
// Created by ariel on 26/11/2021.
//

#ifndef WET1_AVLTREENODE_H
#define WET1_AVLTREENODE_H

#include <iostream>

template <class T, class S>
class AVLTreeNode {
    T key;
    S data;
    int height;
    AVLTreeNode<T,S>* right;
    AVLTreeNode<T,S>* left;
public:
    AVLTreeNode(const T& key, const S& data): key(key), data(data), height(0), right(nullptr), left(nullptr) {};
    ~AVLTreeNode() = default;
    AVLTreeNode(const AVLTreeNode<T,S>& node) = default;
    void setRight(AVLTreeNode<T,S>* node);
    void setLeft(AVLTreeNode<T,S>* node);
    void setHeight(int height);
    void updateHeight();
    void setData(const S& data);
    void setKey(const T& key);
    AVLTreeNode<T,S>* getRight() const;
    AVLTreeNode<T,S>* getLeft() const;
    int getHeight() const;
    const S& getData() const;
    S& changeData();
    T& changeKey();
    S copyData();
    const T& getKey() const;
    void printNode() const;

};

template <class T, class S>
void AVLTreeNode<T, S>::setLeft(AVLTreeNode<T, S>* node) {
    this->left = node;
    this->updateHeight();
}

template <class T, class S>
void AVLTreeNode<T, S>::setRight(AVLTreeNode<T,S>* node) {
    this->right = node;
    this->updateHeight();
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTreeNode<T, S>::getLeft() const {
    return this->left;
}

template <class T, class S>
AVLTreeNode<T,S>* AVLTreeNode<T,S>::getRight() const {
    return this->right;
}

template <class T, class S>
const S& AVLTreeNode<T,S>::getData() const {
    return this->data;
}

template <class T, class S>
S& AVLTreeNode<T,S>::changeData() {
    return this->data;
}

template <class T, class S>
T& AVLTreeNode<T,S>::changeKey() {
    return this->key;
}

template <class T, class S>
S AVLTreeNode<T,S>::copyData() {
    return this->data;
}

template <class T, class S>
const T& AVLTreeNode<T,S>::getKey() const {
    return this->key;
}

template <class T, class S>
int AVLTreeNode<T,S>::getHeight() const {
    return this->height;
}

template <class T, class S>
void AVLTreeNode<T,S>::updateHeight() {
    this->height = 1 + std::max(this->left?this->left->getHeight():-1, this->right?this->right->getHeight():-1);
}

template <class T, class S>
void AVLTreeNode<T,S>::printNode() const {
    if(!this)
        return;
    std::cout<<this->data << ", ";
}

template <class T, class S>
void AVLTreeNode<T,S>::setHeight(int new_height) {
    this->height = new_height;
}

template <class T, class S>
void AVLTreeNode<T,S>::setData(const S& new_data) {
    this->data = new_data;
}

template <class T, class S>
void AVLTreeNode<T,S>::setKey(const T& new_key) {
    this->key = new_key;
}



#endif //WET1_AVLTREENODE_H
