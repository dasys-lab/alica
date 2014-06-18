/*
 * BehaviourPool.h
 *
 *  Created on: Jun 13, 2014
 *      Author: Stephan Opfer
 */

#ifndef BEHAVIOURPOOL_H_
#define BEHAVIOURPOOL_H_

using namespace std;

#include <map>
#include <typeindex>
#include <iostream>
#include <memory>

#include <engine/IBehaviourPool.h>

namespace alica
{

	class BasicBehaviour;

	class BehaviourPool : public IBehaviourPool
	{

	public:
		BehaviourPool();
		virtual ~BehaviourPool();
		void stop();
		bool init(IBehaviourCreator* bc);
		bool isBehaviourAvailable(Behaviour* b) const;
		void removeBehaviour(RunningPlan rp);
		void addBehaviour(RunningPlan rp);
	private:
		/**
		 * This map manages behaviours used by the currently running ALICA program.
		 */
		map<Behaviour*, unique_ptr<BasicBehaviour> >* availableBehaviours;

		IBehaviourCreator* behaviourCreator;

	};

} /* namespace alica */

#endif /* BEHAVIOURPOOL_H_ */
