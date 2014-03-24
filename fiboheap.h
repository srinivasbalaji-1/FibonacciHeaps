/* 
 * File:   fiboheap.h
 * Author: srinivas
 *
 * Created on March 19, 2014, 4:33 PM
 */

#pragma once
#ifndef FIBOHEAP_H
#define FIBOHEAP_H

#include<queue>
#include<iostream>

using namespace std;

template<class T>

class fiboheap {

    struct fibnode {
        int degree;
        fibnode* child;
        fibnode* left;
        fibnode* right;
        fibnode* parent;
        bool childcut;
        T data;
    };
    queue<fibnode *> nodeDegree[1000];
    fibnode* minRoot;
    fibnode* root;
    fibnode** ref;

public:

    fiboheap(const int numNodes) {
        ref = new fibnode*[numNodes];
        for (int i = 0; i < numNodes; i++) {
            ref[i] = NULL;
        }
        minRoot = 0;
        root = 0;
    }

    void insert(T val) {
        fibnode* newNode = new fibnode;
        newNode->left = newNode;
        newNode->right = newNode;
        newNode->parent = 0;
        newNode->child = 0;
        newNode->childcut = false;
        newNode->degree = 0;
        newNode->data = val;
        ref[val.destination] = new fibnode;
        ref[val.destination] = newNode;
        if (minRoot == 0) {
            root = newNode;
            minRoot = newNode;
        } else {
            minRoot = (minRoot->data.dist > newNode->data.dist) ? newNode : minRoot;
            addSibling(root, newNode);
        }
    }

    bool isRefNull(T node) {
        if (ref[node.destination] == NULL)
            return true;
        return false;
    }

    void merge(fibnode* h1, fibnode* h2) {
        if (h1->data.dist >= h2->data.dist) {
            if (h2->child != 0)
                addSibling(h2->child, h1);
            else {
                h2->degree = h2->degree + 1;
                h2->child = h1;
            }
            h1->left->right = h1->right;
            h1->right->left = h1->left;
            root = (h1 == root) ? h2 : root;
        } else {
            if (h1->child != 0)
                addSibling(h1->child, h1);
            else {
                h1->degree = h1->degree + 1;
                h1->child = h2;
            }
            h2->left->right = h2->right;
            h2->right->left = h2->left;
            root = (h2 == root) ? h1 : root;
        }
    }
    
    bool isEmpty()
    {
        if(minRoot==NULL) return true;
        return false;
    }

    void addSibling(fibnode* h1, fibnode* h2) {
        if (h1 != 0) {
            fibnode* lastH1 = h1->left;
            fibnode* lastH2 = h2->left;
            lastH1->right = h2;
            h2->left = lastH1;
            h1->left = lastH2;
            lastH2->right = h1;
            if (h1->parent != 0) {
                h2->parent = h1->parent;
                h1->parent->degree = h1->parent->degree + 1;
            }
        } else {
            root = h2;
        }
    }

    void removeMin() {
        if (minRoot == NULL) return;
        fibnode* firstChild = 0;
        firstChild = minRoot->child;
        fibnode* temp = 0;
        temp = firstChild;

        if (temp != NULL) {
            while (temp->right != firstChild) {
                temp->parent = NULL;
                temp = temp->right;
            }
            temp->parent = NULL;
            addSibling(root, firstChild);
        }

        minRoot->left->right = minRoot->right;
        minRoot->right->left = minRoot->left;
        root = (minRoot == root && root->right != root) ? minRoot->right : (minRoot != root) ? root : NULL;
        ref[minRoot->data.destination] = NULL;
        minRoot = NULL;

        fibnode* firstNode = root;
        temp = root;
        if (temp != NULL)
            nodeDegree[temp->degree].push(temp);
        while (root != NULL && temp != firstNode) {
            firstNode = root;
            minRoot = (minRoot != NULL && temp->data.dist < minRoot->data.dist) ? temp : minRoot;
            if (minRoot == NULL) minRoot = temp;
            if (!nodeDegree[temp->degree].empty()) {
                merge(nodeDegree[temp->degree].front(), temp);
                nodeDegree[temp->degree].pop();
            } else {
                nodeDegree[temp->degree].push(temp);
            }
            temp = temp->right;
        }
        if (root != NULL) {
            temp = root;
            minRoot = temp;
            temp = temp->right;
            while (temp != root) {
                minRoot = (temp->data.dist < minRoot->data.dist) ? temp : minRoot;
                temp = temp->right;
            }
        }
    }

    void decreaseKey(T nodeVal) {
        fibnode* referredNode = ref[nodeVal.destination];
        if (referredNode->data.dist > nodeVal.dist) {
            referredNode->data.dist = nodeVal.dist;
            cascadingCut(referredNode);
        }

    }

    T getMin() {
        return minRoot->data;
    }

    void cascadingCut(fibnode* cutNode) {
        if (cutNode->parent != 0) {
            fibnode* parent = cutNode->parent;
            if (cutNode->data.dist < parent->data.dist) {
                cut(cutNode);

            }
            while (parent->parent != NULL && parent->childcut) {
                parent->childcut = false;
                fibnode* temp = parent->parent;
                cut(parent);
                parent = temp;
            }


        } else {
            if (cutNode->data.dist < minRoot->data.dist) {
                minRoot = cutNode;
            }
        }


    }

    void cut(fibnode* cutNode) {
        addSibling(root, cutNode);

    }
};

#endif


