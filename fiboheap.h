#pragma once
#ifndef FIBOHEAP_H
#define FIBOHEAP_H

using namespace std;

template<class T>

class fiboheap{
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

    }

    public void removeMin(){

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
