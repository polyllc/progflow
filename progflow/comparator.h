#pragma once
#include <iostream>
#include <variant>
#include "variable.h"

namespace util {
	enum comparator { AND, OR, NOTEQUAL, EQUAL, GTHAN, LTHAN, GETHAN, LETHAN };
	using anyVar = std::variant<int, float, double, std::string>; //nvm i figured out how to use variants

	
	//-------------------------------------
	//		comparatorExpression
	// compares a right hand side and
	// left hand side with comparators.
	// Also compares comparatorExpressions
	// infintely nested.
	//
	//            notes
	// this class is not very self checking
	// so be careful when setting values 
	// manually (checking values is completely
	// fine and safe).
	//-------------------------------------
	class comparatorExpression {
	private:
		Variable<anyVar> lhv; //bruh variants are actually great
		Variable<anyVar> rhv;
		comparator symbol;
		bool nestedExpression = false;

		comparatorExpression* left; //if this weren't a pointer, I would be so much happier
		comparatorExpression* right;

	public:
		//we like not initiallizing all the types, right? well they should never be used wrong then (pretty hard to fuck up with this)
		comparatorExpression(Variable<anyVar> lefthand, Variable<anyVar> righthand, comparator sym) : symbol(sym) { //sadly, we cant do lhv(lefthand) as that calls the constructor :(
			lhv = lefthand;
			rhv = righthand;
		}
		comparatorExpression() {} //this is for those empty comparatorExpressions up there
		comparatorExpression(comparatorExpression& lefthand, comparatorExpression& righthand, comparator sym) : symbol(sym) { left = &lefthand; right = &righthand; nestedExpression = true; } //this is for nested comparators
		~comparatorExpression() {}

		bool evaluate() {
			
			switch (symbol) {
			case NOTEQUAL: return lhv != rhv; break;
			case EQUAL: return lhv == rhv; break;
			case GTHAN: return lhv > rhv; break; 
			case LTHAN: return lhv < rhv; break;
			case GETHAN: return lhv >= rhv; break;
			case LETHAN: return lhv <= rhv; break;
			}

			if (nestedExpression == true) {
				comparatorExpression l;
				comparatorExpression r;

				if (left->getType() == true) { //nested expression
					l.setSymbol(left->getSymbol());
					l.setExpValues(left->getLeft(), left->getRight());
					l.setType(left->getType());

					r.setSymbol(right->getSymbol());
					r.setExpValues(right->getLeft(), right->getRight());
					r.setType(right->getType());
				}
				else { //lowest tier expression i.e. 1 > 2
					l.setSymbol(left->getSymbol());
					l.setValues(left->getValues()[0], left->getValues()[1]);
					l.setType(left->getType());

					r.setSymbol(right->getSymbol());
					r.setValues(right->getValues()[0], right->getValues()[1]);
					r.setType(right->getType());
				}
				if (symbol == OR) {
					return l || r;
				}
				else if (symbol == AND) {
					return r && l;
				}
			}

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

		bool setExpValues(comparatorExpression* l, comparatorExpression* r) {
			left = l;
			right = r;
			return true;
		}

		comparator getSymbol() {
			return symbol;
		}

		void setSymbol(comparator sym) {
			symbol = sym;
		}

		bool getType() {
			return nestedExpression;
		}

		comparatorExpression* getLeft() {
			return left;
		}

		comparatorExpression* getRight() {
			return right;
		}

		void setType(bool nested) {
			nestedExpression = nested;
		}

		std::vector<Variable<anyVar>> getValues() {
			std::vector<Variable<anyVar>> values;
			if (nestedExpression == false) {
				values.push_back(lhv);
				values.push_back(rhv);
			}
			return values;
		}

		std::vector<comparatorExpression*> getExValues() {
			std::vector<comparatorExpression*> values;
			if (nestedExpression == true) {
				values.push_back(left);
				values.push_back(right);
			}
			return values;
		}

		bool operator&& (comparatorExpression& other) {
			return (this->evaluate() && other.evaluate());
		}

		bool operator|| (comparatorExpression& other) {
			return (this->evaluate() || other.evaluate());
		}

		void operator= (comparatorExpression& other) {
			this->setValues(other.getValues());
			this->symbol = other.getSymbol();
		}
	};

}