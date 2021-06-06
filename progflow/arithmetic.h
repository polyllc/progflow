#pragma once
//oh no
#include "util.h"
#include "variable.h"
#include "comparator.h" //for anyVar


namespace util { 

	enum operation {ADD, SUB, MULTI, DIV, MOD};
	//its literally just a left hand value and a right hand value with an operator in between, and this thing solves it for me
	class arithmetic {
	private:
		Variable<anyVar> lhv; //we literally copy and paste most things from comparator
		Variable<anyVar> rhv;

		arithmetic* left;
		arithmetic* right;

		operation symbol;
		bool nestedExpression = false;
	public:
		arithmetic(Variable<anyVar> lefthand, Variable<anyVar> righthand, operation op) : symbol(op) {
			lhv = lefthand;
			rhv = righthand;
		}


		anyVar evaluate() {
			switch (symbol) {
			case ADD: return lhv + rhv;
			case SUB: return lhv - rhv;
			case MULTI: return lhv * rhv;
			case DIV: return lhv / rhv;
			case MOD: return lhv % rhv;
			}
		}

		void setSymbol(operation op) {
			symbol = op;
		}

		arithmetic* getLeft() {
			return left;
		}

		arithmetic* getRight() {
			return right;
		}

		void setType(bool nested) {
			nestedExpression = nested;
		}

		operation getSymbol() {
			return symbol;
		}

		bool getType() {
			return nestedExpression;
		}

		bool setValues(Variable<anyVar> lefthand, Variable<anyVar> righthand) {
			if (lefthand.getType() != lhv.getType() || righthand.getType() != rhv.getType()) {
				return false;
			}
			else {
				lhv = lefthand;
				rhv = righthand;
			}
			return true;
		}

		bool setValues(std::vector<Variable<anyVar>> values) {
			if (values.size() == 2) {
				if (values[0].getType() != lhv.getType() || values[1].getType() != rhv.getType()) {
					return false;
				}
				else {
					lhv = values[0];
					rhv = values[1];
				}
				return true;
			}
		}

		std::vector<Variable<anyVar>> getValues() {
			std::vector<Variable<anyVar>> values;
			if (nestedExpression == false) {
				values.push_back(lhv);
				values.push_back(rhv);
			}
			return values;
		}

		bool setExpValues(arithmetic* l, arithmetic* r) {
			left = l;
			right = r;
			return true;
		}

		void operator= (arithmetic& other) {
			this->setValues(other.getValues());
			this->symbol = other.getSymbol();
		}
	};
}


