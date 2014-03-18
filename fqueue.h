#pragma once
#ifndef FQUEUE_H
#define FQUEUE_H
#include<iostream>
using namespace std;
template <class T>

class fqueue{
    struct node{
        T data;
        node *next;
    };
    node* prev;
    node *top;
    node *last;
    int count;
    public:

    fqueue(){
        prev = NULL;
        top = NULL;
        last = NULL;
    }

    void pop(){
        if(top==NULL) cout<<"empty";
        top = (prev!=NULL)?prev:NULL;
        if(top==NULL) last = NULL;
        prev = (top!=NULL&&top->next!=NULL)?top->next:NULL; 
    }

    void push(T val){
        node *temp = new node;
        temp->data = val; 
        temp->next = NULL;
        if(top!=NULL && top->next!=NULL){
            prev = top->next;
        }   
        if(last!=NULL){
        last->next = temp;
        last = temp;
        }
        else{
            last = temp;
            top = last;
            prev = NULL;
        }
    }

    T front()
    {
        if(top!=NULL) return top->data;
        else return NULL;
    }

    void print()
    {
        node * temp=top;
        while(temp!=NULL){
            cout<<temp->data<<"\t";
            temp = temp->next;
        }
        cout<<last->data<<"\t"<<prev->data;
    }

    bool isEmpty()
    {
        bool empty = (top==NULL) ? true:false;
        return empty; 
    }
};

#endif
