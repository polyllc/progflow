#pragma once
#include "util.h"
#include "command.h"


template <class T>
class Variable {
private:
	Type type; //we reuse Type from command.h
	T data; //technically we can have any data type, but we stick with the 4

public:
	Variable<T>(Type variableType, T value) : type(variableType), data(value)  {}
	~Variable<T>() {}
	
	void setValue(T value);
	T readValue();
	Type getType();
};

template<class T>
void Variable<T>::setValue(T value) {
	data = value;
}

template<class T>
T Variable<T>::readValue() {
	return data;
}

template<class T>
Type Variable<T>::getType() {
	return type;
}

