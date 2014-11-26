/*
 * ConstraintTestPlan1414068524245Constraint.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: Philipp
 */

#include <ConstraintTestPlan1414068524245Constraint.h>

#include "engine/constraintmodul/ConstraintDescriptor.h"
#include "engine/RunningPlan.h"

#include <iostream>

namespace alicaAutogenerated
{
	int Constraint1414068566297::callCounter = 0;

	void Constraint1414068566297::getConstraint(shared_ptr<ConstraintDescriptor> c, shared_ptr<RunningPlan> rp)
	{
		callCounter++;
		std::cout << "Constraint1414068566297::getConstraint() is called " << callCounter << " times!" << std::endl;
	}

	int Constraint1414068566297::getCallCounter()
	{
		return callCounter;
	}
} /* namespace alica */