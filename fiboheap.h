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
    
    public void insert(T val, T key){

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
