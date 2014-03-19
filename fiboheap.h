/* 
 * File:   fiboheap.h
 * Author: srinivas
 *
 * Created on March 19, 2014, 4:33 PM
 */

#pragma once
#ifndef FIBOHEAP_H
#define FIBOHEAP_H

#include"fqueue.h"

using namespace std;

template<class T>

class fiboheap{	
    	
    
    struct fibnode
    {
      int degree;
      fibnode* child;
      fibnode* left;
      fibnode* right;
      fibnode* parent;
      bool childcut;
      T data;
      };
      fqueue<fibnode *> nodeDegree[5000]; 
      fibnode* minRoot;
      fibnode* root;
      
    public:
    
    void insert(T val)
    {
	fibnode* newNode = new fibnode;
        newNode->left = NULL;
        newNode->right = NULL;
	newNode->parent = NULL;
	newNode->childcut = false;
	newNode->degree = 0;
	newNode->data = val; 
 	if(minRoot==NULL)
	{
  	minRoot = newNode;
	}
	else
	{
		minRoot = (minRoot->data > newNode->data) ? newNode:minRoot;
		addSibling(root,newNode);				
	}
    }

    void merge(fibnode* h1,fibnode* h2)
    {
    	if(h1->data >= h2->data)
    	{
        	if(h2->child!=NULL) 
                    addSibling(h2->child,h1);
    		else
    		{
    			h2->degree = h2->degree+1;
    			h2->child = h1;
    		}
    	}
    	else
        {
    		if(h1->child!=NULL) 
                    addSibling(h1->child,h1);
    		else
    		{
    			h1->degree = h1->degree +1;
    			h1->child = h2;
    		}
    		
    	}
    }
    
    void addSibling(fibnode* h1, fibnode* h2)
    {
    	
    	h2->left = h1->left;
    	h2->right = h1;
    	h2->parent = h1->parent;
    	h1->parent->degree = h1->parent->degree +1;
    	h1->->left->right = h2;    	
    }
    
    

    void removeMin(){
    	fibnode* firstChild = minRoot->child;
    	if(root!=NULL)
    	{
    		fibnode* temp = firstChild;
    		while(temp->right=firstChild)
    		{
    			temp->parent = NULL;
    			temp = temp->right;
    		}
    		temp->parent = NULL;
    		addSibling(root,temp);
    	}
    	
    	minRoot->left->right = minRoot->right;
    	minRoot->right->left = minRoot->left;
    	minRoot = NULL;
    	fibnode* firstNode = root;
    	fibnode* temp = root;
    	while(temp->right!=root)
    	{
    		minRoot = (minRoot!=NULL && temp->data < minRoot->data) ? temp:minRoot;
    		if(minRoot==NULL) minRoot = temp;
    		if(!nodeDegree[temp->degree].isEmpty())
    		{
    			 merge(nodeDegree[temp->degree].front(),temp);
    			 nodeDegree[temp->degree].pop();
    		}
    		else{
    			nodeDegree[temp->degree].push(temp);
    		}
    	}
    		
    	
    	

    }

    void descreaseKey(fibnode* h,T key,T val){

    }

    

    void cascadingCut(fibnode* h,T key){

    }

    void cut(fibnode* h){

    }


   
}

#endif


