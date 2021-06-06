#pragma once
#include "util.h"
#include "command.h"
#include "comparator.h"
using anyVar = std::variant<int, float, double, std::string>;
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
		switch (type) {
		case STRING: return anyVar (std::get<std::string>(this->readValue()) + std::get<std::string>(other.readValue()));
		case FLOAT: return anyVar (std::get<float>(this->readValue()) + std::get<float>(other.readValue()));
		case DOUBLE: return anyVar (std::get<double>(this->readValue()) + std::get<double>(other.readValue()));
		case INT: return anyVar (std::get<int>(this->readValue()) + std::get<int>(other.readValue()));
		default: std::cout << "FATAL ERROR: Unknown type to add (types were not a string, float, double or int)"; exit(0);
		}
	}
	T operator- (Variable other) {
		switch (type) {
		case STRING: std::cout << "FATAL ERROR: Cannot subtract a string from another"; exit(0);
		case FLOAT: return anyVar(std::get<float>(this->readValue()) - std::get<float>(other.readValue()));
		case DOUBLE: return anyVar(std::get<double>(this->readValue()) - std::get<double>(other.readValue()));
		case INT: return anyVar(std::get<int>(this->readValue()) - std::get<int>(other.readValue()));
		default: std::cout << "FATAL ERROR: Unknown type to subtract (types were not a string, float, double or int)"; exit(0);
		}
	}
	T operator* (Variable other) {
		switch (type) {
		case STRING: std::cout << "FATAL ERROR: Cannot multiply strings with each other"; exit(0);
		case FLOAT: return anyVar(std::get<float>(this->readValue()) * std::get<float>(other.readValue()));
		case DOUBLE: return anyVar(std::get<double>(this->readValue()) * std::get<double>(other.readValue()));
		case INT: return anyVar(std::get<int>(this->readValue()) * std::get<int>(other.readValue()));
		default: std::cout << "FATAL ERROR: Unknown type to multiply (types were not a string, float, double or int)"; exit(0);
		}
	}
	T operator/ (Variable other) {
		switch (type) {
		case STRING: std::cout << "FATAL ERROR: Cannot divide strings with each other"; exit(0);
		case FLOAT: return anyVar(std::get<float>(this->readValue()) / std::get<float>(other.readValue()));
		case DOUBLE: return anyVar(std::get<double>(this->readValue()) / std::get<double>(other.readValue()));
		case INT: return anyVar(std::get<int>(this->readValue()) / std::get<int>(other.readValue()));
		default: std::cout << "FATAL ERROR: Unknown type to divide (types were not a string, float, double or int)"; exit(0);
		}
	}
	T operator% (Variable other) {
		switch (type) {
		case STRING: std::cout << "FATAL ERROR: Cannot modulate 2 strings"; exit(0);
		case FLOAT: std::cout << "FATAL ERROR: Cannot modulate 2 floats"; exit(0);
		case DOUBLE: std::cout << "FATAL ERROR: Cannot modulate 2 doubles"; exit(0);
		case INT: return anyVar(std::get<int>(this->readValue()) % std::get<int>(other.readValue()));
		default: std::cout << "FATAL ERROR: Unknown type to modulate (types were not a string, float, double or int)"; exit(0);
		}
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

