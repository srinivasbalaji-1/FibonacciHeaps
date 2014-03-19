#pragma once
#ifndef FIBOHEAP_H
#define FIBOHEAP_H

#include"fqueue.h"

using namespace std;

template<class T>

class fiboheap{
		
		fqueue<fibnode*> nodeDegree[5000];		
    struct fibnode{
      int degree;
      fibnode* child;
      fibnode* left;
      fibnode* right;
      fibnode* parent;
      bool childcut;
      T data;
      }
    
    public void insert(T val){
			fibnode* newNode = new fibnode;
			fibnode->left = NULL;
			fibnode->right = NULL;
			fibnode->parent = NULL;
			fibnode->childcut = false;
			fibnode->degree = 0;
			h1->data = val; 
 			if(root==NULL)
			{
				root = newNode;
				minRoot = newNode;
			}
			else
			{
				minRoot = (minroot->data > newNode->data) ? newNode:minRoot;
				addSibling(root,newNode);				
			}
    }

    public void merge(fibnode* h1,fibnode* h2){
    	if(h1->data >= h2->data)
    	{
    		addSibling(h2,h1);
    	}
    	else{
    		addSibling(h1,h2);
    	}
    }
    
    public void addSibling(fibnode** h1, fibnode** h2)
    {
    	
    	h2->left = h1->child->left->right;
    	h2->right = h1->child;
    	h1->child->left->right = h2;
			h1->degree = h1->degree +1;    	
    }
    
    

    public void removeMin(){
    	fibnode* firstChild = minroot->child;
    	if(root!=empty)
    	{
    		fibnode* temp = firstChild;
    		while(temp->right=firstChild){
    			temp->parent = NULL;
    			temp = temp->right
    		}
    		temp->parent = NULL;
    		addSibling(root,temp);
    	}
    	
    	minRoot->left->right = minRoot->right->left;
    	minRoot->left = NULL;
    	minRoot->right = NULL;
    	fibnode* firstNode = root;
    	fibnode* temp = root;
    	while(temp->next!=root)
    	{
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

    public void descreaseKey(fibnode* h,T key,T val){

    }

    public void delete(fibnode* h,T key){

    }

    public void cascadingCut(fibnode* h,T key){

    }

    public void cut(fibnode* h){

    }


   
}

#endif
