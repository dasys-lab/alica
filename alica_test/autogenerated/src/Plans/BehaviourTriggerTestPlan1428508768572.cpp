#include "Plans/BehaviourTriggerTestPlan1428508768572.h"
using namespace alica;
/*PROTECTED REGION ID(eph1428508768572) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:BehaviourTriggerTestPlan

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1428508768574

     */
    shared_ptr<UtilityFunction> UtilityFunction1428508768572::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1428508768572) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: NewState in Plan: BehaviourTriggerTestPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): TriggerA, (PlanID): 1428508312886 				
     *   - Plan - (Name): TriggerB, (PlanID): 1428508331620 				
     *   - Plan - (Name): TriggerC, (PlanID): 1428508367402 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1428508768574)
     *
     * States:
     *   - NewState (1428508768573)
     *   - NewState (1429017227839)
     *
     * Vars:
     */
    bool TransitionCondition1429017236633::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1429017235181) ENABLED START*/
        return false;
        /*PROTECTED REGION END*/

    }

//State: NewState in Plan: BehaviourTriggerTestPlan

}
