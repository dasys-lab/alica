#include "Plans/ProblemModule/ProblemBuildingMaster1479556022226.h"
using namespace alica;
/*PROTECTED REGION ID(eph1479556022226) ENABLED START*/  // Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated {
// Plan:ProblemBuildingMaster

/* generated comment

 Task: DefaultTask  -> EntryPoint-ID: 1479556022228

 */
shared_ptr<UtilityFunction> UtilityFunction1479556022226::getUtilityFunction(Plan* plan) {
    /*PROTECTED REGION ID(1479556022226) ENABLED START*/

    shared_ptr<UtilityFunction> defaultFunction = make_shared<DefaultUtilityFunction>(plan);
    return defaultFunction;

    /*PROTECTED REGION END*/
}

// State: State1 in Plan: ProblemBuildingMaster

/*
 *
 * Transition:
 *   - Name: MISSING_NAME, ConditionString: , Comment :
 *
 * Plans in State:
 *   - Plan - (Name): ProbBuildingLevel1, (PlanID): 1479557378264
 *
 * Tasks:
 *   - DefaultTask (1225112227903) (Entrypoint: 1479556022228)
 *
 * States:
 *   - State1 (1479556022227)
 *   - State2 (1479557585252)
 *
 * Vars:
 *	- PBMX (1479557337956)
 *	- PBMY (1479557345903)
 */
bool TransitionCondition1479557592662::evaluate(shared_ptr<RunningPlan> rp) {
    /*PROTECTED REGION ID(1479557591331) ENABLED START*/
    return false;
    /*PROTECTED REGION END*/
}

// State: State2 in Plan: ProblemBuildingMaster

}  // namespace alicaAutogenerated
