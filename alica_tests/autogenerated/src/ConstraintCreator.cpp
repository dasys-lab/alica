#include "ConstraintCreator.h"
#include <iostream>

#include  "Plans/constraints/PlanOne1407153611768Constraints.h"

#include  "Plans/ProblemModule/constraints/ProbBuildingLevel1_11479557664989Constraints.h"

#include  "Plans/constraints/PlanFour1407153683051Constraints.h"

#include  "Plans/constraints/RealMasterPlanForSyncTest1418902217839Constraints.h"

#include  "Plans/constraints/Defend1402488893641Constraints.h"

#include  "Plans/GSolver/constraints/GSolverTestPlan1417423757243Constraints.h"

#include  "Plans/Authority/constraints/AuthorityTestMaster1414403396328Constraints.h"

#include  "Plans/constraints/GoalPlan1402488870347Constraints.h"

#include  "Plans/constraints/MasterPlan1402488437260Constraints.h"

#include  "Plans/ProblemModule/constraints/QueryPlan11479556074049Constraints.h"

#include  "Plans/constraints/MasterPlanTestConditionPlanType1418042656594Constraints.h"

#include  "Plans/constraints/AttackPlan1402488634525Constraints.h"

#include  "Plans/constraints/PlanFive1407153703092Constraints.h"

#include  "Plans/Authority/constraints/AuthorityTest1414403413451Constraints.h"

#include  "Plans/constraints/SimpleTestPlan1412252439925Constraints.h"

#include  "Plans/ProblemModule/constraints/QueryPlan21479718449392Constraints.h"

#include  "Plans/constraints/RuntimeConditionPlan1418042806575Constraints.h"

#include  "Plans/constraints/PlanThree1407153663917Constraints.h"

#include  "Plans/constraints/MidFieldPlayPlan1402488770050Constraints.h"

#include  "Plans/constraints/Tackle1402489318663Constraints.h"

#include  "Plans/constraints/MasterSyncTransition1418825395939Constraints.h"

#include  "Plans/constraints/MasterPlanTaskAssignment1407152758497Constraints.h"

#include  "Plans/constraints/PlanTwo1407153645238Constraints.h"

#include  "Plans/constraints/BehaviorSuccessSpamMaster1522377375148Constraints.h"

#include  "Plans/ProblemModule/constraints/ProblemBuildingMaster1479556022226Constraints.h"

#include  "Plans/constraints/MultiAgentTestPlan1413200862180Constraints.h"

#include  "Plans/constraints/ConstraintTestPlan1414068524245Constraints.h"

#include  "Plans/constraints/PreConditionPlan1418042796751Constraints.h"

#include  "Plans/GSolver/constraints/GSolverMaster1417423751087Constraints.h"

#include  "Plans/constraints/ConstraintTestMaster1414068495566Constraints.h"

#include  "Plans/ProblemModule/constraints/ProbBuildingLevel11479557378264Constraints.h"

#include  "Plans/constraints/OtherPlan1418042819203Constraints.h"

#include  "Plans/constraints/MultiAgentTestMaster1413200842973Constraints.h"

#include  "Plans/constraints/BehaviourTriggerTestPlan1428508768572Constraints.h"

using namespace std;
using namespace alicaAutogenerated;

namespace alica
{

    ConstraintCreator::ConstraintCreator()
    {
    }

    ConstraintCreator::~ConstraintCreator()
    {
    }

    shared_ptr<BasicConstraint> ConstraintCreator::createConstraint(long constraintConfId)
    {
        switch (constraintConfId)
        {

            case 1417424512343:
                return make_shared<Constraint1417424512343>();
                break;

            case 1403773741874:
                return make_shared<Constraint1403773741874>();
                break;

            case 1479556084493:
                return make_shared<Constraint1479556084493>();
                break;

            case 1402489460549:
                return make_shared<Constraint1402489460549>();
                break;

            case 1402489462088:
                return make_shared<Constraint1402489462088>();
                break;

            case 1479557592662:
                return make_shared<Constraint1479557592662>();
                break;

            case 1414068566297:
                return make_shared<Constraint1414068566297>();
                break;

            default:
                cerr << "ConstraintCreator: Unknown constraint requested: " << constraintConfId << endl;
                throw new exception();
                break;
        }
    }

}
