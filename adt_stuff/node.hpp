#pragma once
template<class T>
class node{
public:
	node<T>* next;
	T dat;
	node();
	~node();
};

template<class T>
node<T>::node(){}

template<class T>
node<T>::~node(){}
