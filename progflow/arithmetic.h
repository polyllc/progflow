#pragma once
//oh no
#include "util.h"
#include "variable.h"
#include "comparator.h" //for anyVar


namespace util { 

	enum operation {ADD, SUB, MULTI, DIV, MOD};
	//its a string of operations, parentheses will be handled by other function, and whats inside those parentheses? arithmeticStrings
	class arithmeticString { //a different approach is needed, there are no longer left hand and right hand values, but we can have infinite values on either side (plus there are no sides)
	private:
		Variable<anyVar> lhv; //we literally copy and paste most things from comparator
		Variable<anyVar> rhv;
		operation symbol;
		bool nestedExpression = false;
	public:
		arithmeticString(Variable<anyVar> lefthand, Variable<anyVar> righthand, operation op) : symbol(op) {
			lhv = lefthand;
			rhv = righthand;
		}

		anyVar evaluate() {

		}

	};
}


