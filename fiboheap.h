/* 
 * File:   fiboheap.h
 * Author: srinivas balaji ramesh
 * UFID : 94217395
 * email : rsbalaji@ufl.edu
 * Created on March 11, 2014, ;1:53 AM
 */

#pragma once
#ifndef FIBOHEAP_H
#define FIBOHEAP_H

#include<queue>
#include<iostream>
#include<vector>

using namespace std;

template<class T>

class fiboheap {

    /**
     * Node structure to store data in the Fibonacci heap.
     */
    struct fibnode {
        int degree;
        fibnode* child;
        fibnode* left;
        fibnode* right;
        fibnode* parent;
        bool childcut;
        T data;
    };
    vector<queue<fibnode *> > nodeDegree;
    fibnode* minRoot;
    fibnode* root;
    fibnode** ref;

public:
    /**
     * Constructor to initialize all the private member variables.
     * @param numNodes
     */
    fiboheap(const int numNodes) {
        ref = new fibnode*[numNodes];
        for (int i = 0; i < numNodes; i++) {
            ref[i] = NULL;
        }
        nodeDegree.resize(1000);
        minRoot = 0;
        root = 0;
    }

    /**
     * insert data into Fibonacci heap.Maintains rootList(root) and minimum Root(minRoot) values. 
     * @param val
     */
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
        /*Set the newly created node as minRoot when fibonacci heap is empty */
        if (minRoot == 0) {
            root = newNode;
            minRoot = newNode;
        } else {
            minRoot = (minRoot->data.dist > newNode->data.dist) ? newNode : minRoot;
            addSibling(root, newNode);
        }
    }
    
    /**
     * Check if the reference table that keeps track of every node in Fibonacci heap is not NULL.
     * @param node
     * @return 
     */
    bool isRefNull(T node) {
        if (ref[node.destination] == NULL)
            return true;
        return false;
    }
    
    /**
     * Merges 2 root nodes of equal degree by attaching the node with the smaller value 
     * to the larger one. 
     * @param h1
     * @param h2
     * @return 
     */
    fibnode* merge(fibnode* h1, fibnode* h2) {
        //checks the lesser of the two trees
        if (h1->data.dist >= h2->data.dist) {
            if (h2->child != 0)
                /* Adds h1 as sibling to h2*/
                h2->child = addSibling(h2->child, h1);
            else {
                h2->degree = h2->degree + 1;
                h2->child = h1;
                h1->left->right = h1->right;
                h1->right->left = h1->left;
                h1->left = h1;
                h1->right = h1;               
            }
            h1->left->right = h1->right;
            h1->right->left = h1->left;
            root = (h1 == root) ? h2 : root;
            return h2;
        } else {
            if (h1->child != 0)
                /* Adds h2 as sibling to h1*/
                h1->child = addSibling(h1->child, h2);
            else {
                h1->degree = h1->degree + 1;
                h1->child = h2;
                h2->left->right = h2->right;
                h2->right->left = h2->left;
                h2->left = h2;
                h2->right = h2;
            }
            
            root = (h2 == root) ? h1 : root;
            return h1;
        }
    }
    
    /**
     * checks if the heap is empty. 
     */ 
    bool isEmpty()
    {
        if(minRoot==NULL) return true;
        return false;
    }
    /**
     * Adds sibling to the child nodes (also performs the task of adding a node to the root list.
     * @param h1
     * @param h2
     * @return 
     */
    fibnode* addSibling(fibnode* h1, fibnode* h2) {
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
            // instead of creating a separate function for node addition to root included it here with the below condition
            root = h2;
        }
        return h1;
    }

    /** removes the minimum element from the heap and performs pair wise consolidation of 
     * the nodes with equal degrees
     */
    void removeMin() {
        if (minRoot == NULL) return;
        fibnode* firstChild = 0;
        firstChild = minRoot->child;
        fibnode* temp = 0;
        temp = firstChild;
        //set the parents of all the child nodes of minRoot to NULL
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
        //adjust the root node if minRoot was referenced  by root node
        root = (minRoot == root && root->right != root) ? minRoot->right : (minRoot != root) ? root : NULL;
        ref[minRoot->data.destination] = NULL;
        minRoot = NULL;

        fibnode* firstNode = root;
        temp = root;
        if (temp != NULL)
            nodeDegree[temp->degree].push(temp);
        /**
         * iterate through each element in the root node and perform pair wise consolidation.
         */
        while (root != NULL && temp != firstNode) {
            firstNode = root;
            minRoot = (minRoot != NULL && temp->data.dist < minRoot->data.dist) ? temp : minRoot;
            if (minRoot == NULL) minRoot = temp;
            if (!nodeDegree[temp->degree].empty()) {
                fibnode* mergeTree = merge(nodeDegree[temp->degree].front(), temp);
                nodeDegree[temp->degree].pop();
                while(!nodeDegree[mergeTree->degree].empty())
                {
                	int degree = mergeTree->degree;
                	mergeTree =  merge(nodeDegree[mergeTree->degree].front(), mergeTree);
                	nodeDegree[degree].pop();
                }
                //nodeDegree maintains vector of queues that aids in pairwise consolidation of Fibonacci heap. 
                nodeDegree[mergeTree->degree].push(mergeTree);
                temp = mergeTree;
                
            } else {
                nodeDegree[temp->degree].push(temp);
            }
            
            temp = temp->right;
        }
        //set the new minRoot
        if (root != NULL) {
            temp = root;
            minRoot = temp;
            temp = temp->right;
            while (temp != root) {
                minRoot = (temp->data.dist < minRoot->data.dist) ? temp : minRoot;
                temp = temp->right;
            }
        }
        root = minRoot;
    }
    
    /**
     * decreases the node value if it is lesser that the initial value
     * @param nodeVal
     */
    void decreaseKey(T nodeVal) {
        fibnode* referredNode = ref[nodeVal.destination];
        if (referredNode->data.dist > nodeVal.dist) {
            referredNode->data.dist = nodeVal.dist;
            root = cascadingCut(referredNode);
        }

    }
    
    /**
     * returns the minimum value(minRoot)
     * @return 
     */
    T getMin() {
        return minRoot->data;
    }
    
    /**
     * performs cascading cut on the Fibonacci heap depending on whether the parent node has already lost 
     * a child i.e. the childCut value was earlier true. 
     * @param cutNode
     * @return 
     */ 
    fibnode* cascadingCut(fibnode* cutNode) {
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
        return root;


    }
/**
 * Cuts the node from its parent and adds it to the
 * root list 
 * @param cutNode
 */
    void cut(fibnode* cutNode) {
        if(cutNode->parent!=NULL)
        {
            fibnode* parent = cutNode->parent; 
            parent->child = NULL;
            parent->degree = parent->degree-1;
            root = addSibling(root, cutNode);
            parent;
        }
        root = addSibling(root, cutNode);
        
        
        

    }
};

#endif


