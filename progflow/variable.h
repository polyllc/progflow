#pragma once
#include "util.h"
#include "command.h"
#include "comparator.h"

template <class T>
class Variable { 
private:
	Type type; //we reuse Type from command.h
	T data; //technically we can have any data type, but we stick with the 4

public:
	Variable<T>(Type variableType, T value) : type(variableType), data(value)  {}
	Variable<T>() { type = INT; data = 1; }
	~Variable<T>() {}
	
	void setValue(T value);
	T readValue();
	Type getType();

	void operator= (Variable<T> other) {
		this->type = other.getType();
		this->data = other.readValue();
	}
	//honestly, I have no idea how this works, maybe std::variant really is that good
	bool operator== (Variable other) {
		return other.readValue() == this->readValue();
	}
	bool operator!= (Variable other) {
		return other.readValue() != this->readValue();
	}
	bool operator> (Variable other) { //too lazy to swap other.readValue() 
		return other.readValue() < this->readValue();
	}
	bool operator< (Variable other) {
		return other.readValue() > this->readValue();
	}
	bool operator>= (Variable other) {
		return other.readValue() <= this->readValue();
	}
	bool operator<= (Variable other) {
		return other.readValue() >= this->readValue();
	}

	T operator+ (Variable other) {
		return other.readValue() + this->readValue();
	}
	T operator- (Variable other) {
		return this->readValue() - other.readValue();
	}
	T operator* (Variable other) {
		return this->readValue() * other.readValue();
	}
	T operator/ (Variable other) {
		return this->readValue() / other.readValue();
	}
	T operator% (Variable other) {
		return this->readValue() % other.readValue();
	}

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

