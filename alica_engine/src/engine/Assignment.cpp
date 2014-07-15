/*
 * Assignment.cpp
 *
 *  Created on: Jun 27, 2014
 *      Author: Stefan Jakob
 */

#include "engine/Assignment.h"
#include "engine/collections/AssignmentCollection.h"
#include "engine/model/Plan.h"
#include "engine/collections/StateCollection.h"
#include "engine/collections/SuccessCollection.h"
#include "engine/model/EntryPoint.h"
#include "engine/planselector/PartialAssignment.h"
#include "engine/containers/AllocationAuthorityInfo.h"
#include "engine/containers/EntryPointRobots.h"
#include "engine/model/Task.h"

namespace alica
{

	Assignment::~Assignment()
	{
	}
	Assignment::Assignment(Plan* p)
	{
		this->plan = p;
		this->max = 0.0;
		this->min = 0.0;
		this->allowIdling = (*supplementary::SystemConfig::getInstance())["Alica"]->get<bool>("Alica.AllowIdling",
		NULL);

		this->epRobotsMapping = new AssignmentCollection(this->plan->getEntryPoints().size());

		list<EntryPoint*> l;
		transform(plan->getEntryPoints().begin(), plan->getEntryPoints().end(), back_inserter(l),
					[](map<long, EntryPoint*>::value_type& val)
					{	return val.second;});
		l.sort();
		copy(l.begin(), l.end(), back_inserter(epRobotsMapping->getEntryPoints()));
		this->robotStateMapping = new StateCollection(this->epRobotsMapping);
		this->epSucMapping = new SuccessCollection(p);
	}

	Plan* Assignment::getPlan()
	{
		return plan;
	}

	void Assignment::setPlan(Plan* plan)
	{
		this->plan = plan;
	}
	StateCollection* Assignment::getRobotStateMapping()
	{
		return robotStateMapping;
	}

	shared_ptr<vector<int> > Assignment::getAllRobotsSorted()
	{
		shared_ptr<vector<int> > ret = shared_ptr<vector<int> >();
		for (int i = 0; i < this->getEpRobotsMapping()->getCount(); i++)
		{
			for (int j = 0; j < this->getEpRobotsMapping()->getRobots()[i]->size(); j++)
			{
				ret->push_back(this->getEpRobotsMapping()->getRobots()[i]->at(j));
			}
		}
		sort(ret->begin(), ret->end());
		return ret;
	}

	AssignmentCollection* Assignment::getEpRobotsMapping()
	{
		return epRobotsMapping;
	}

	shared_ptr<vector<int> > Assignment::getRobotsWorking(long epid)
	{
		return this->getEpRobotsMapping()->getRobotsById(epid);
	}

	shared_ptr<vector<int> > Assignment::getRobotsWorkingSorted(EntryPoint* ep)
	{
		shared_ptr<vector<int> > ret = getRobotsWorking(ep);
		sort(ret->begin(), ret->end());
		return ret;
	}

	Assignment::Assignment(PartialAssignment* pa)
	{
		this->max = pa->getMax();
		this->min = max;
		this->plan = pa->getPlan();
		this->allowIdling = (*supplementary::SystemConfig::getInstance())["Alica"]->get<bool>("Alica.AllowIdling",
		NULL);
		auto assCol = pa->getEpRobotsMapping();
		vector<shared_ptr<vector<int> > > robots;
		if (allowIdling)
		{
			robots = vector<shared_ptr<vector<int> > >(assCol->getCount() - 1);
		}
		else
		{
			robots = vector<shared_ptr<vector<int> > >(assCol->getCount());
		}
		for (int i = 0; i < robots.size(); ++i)
		{
			robots[i] = assCol->getRobots().at(i);
		}
		vector<EntryPoint*> newEps = vector<EntryPoint*>(robots.size());
		copy(assCol->getEntryPoints().begin(), assCol->getEntryPoints().end(), newEps.begin());
		this->epRobotsMapping = new AssignmentCollection(newEps, robots);
		this->robotStateMapping = new StateCollection(this->epRobotsMapping);
		this->epSucMapping = pa->getEpSuccessMapping();
	}

	Assignment::Assignment(Plan* p, AllocationAuthorityInfo* aai)
	{
		this->plan = p;
		this->max = 1;
		this->min = 1;
		this->allowIdling = (*supplementary::SystemConfig::getInstance())["Alica"]->get<bool>("Alica.AllowIdling",
		NULL);
		vector<EntryPoint*> eps = vector<EntryPoint*>(p->getEntryPoints().size());
		vector<shared_ptr<vector<int> > > robots = vector<shared_ptr<vector<int> > >(p->getEntryPoints().size());
		int k = 0;
		for (auto iter : p->getEntryPoints())
		{
			eps[k] = iter.second;
			robots[k] = make_shared<vector<int> >(vector<int>());
			for (int i = 0; i < aai->entryPointRobots.size(); i++)
			{
				if (iter.second->getId() == aai->entryPointRobots[i].entrypoint)
				{
					for (int rob : aai->entryPointRobots[i].robots)
					{
						robots[k]->push_back(rob);
					}
				}
			}
			k++;
		}
		this->epRobotsMapping = new AssignmentCollection(eps, robots);
		this->epSucMapping = new SuccessCollection(p);
		this->robotStateMapping = new StateCollection(this->epRobotsMapping);
	}

	shared_ptr<vector<int> > Assignment::getRobotsWorking(EntryPoint* ep)
	{
		return this->getEpRobotsMapping()->getRobots(ep);
	}

	int Assignment::totalRobotCount()
	{
		int c = 0;
		for (int i = 0; i < this->epRobotsMapping->getRobots().size(); i++)
		{
			c += this->epRobotsMapping->getRobots()[i]->size();
		}
		return this->numUnAssignedRobots + c;
	}

	vector<EntryPoint*> Assignment::getEntryPoints()
	{
		return this->epRobotsMapping->getEntryPoints();
	}

	int Assignment::getEntryPointCount()
	{
		return this->epRobotsMapping->getCount();
	}

	shared_ptr<list<int> > Assignment::getRobotsWorkingAndFinished(EntryPoint* ep)
	{
		shared_ptr<list<int> > ret = make_shared<list<int> >(list<int>());
		auto robots = this->epRobotsMapping->getRobots(ep);
		if (robots != nullptr)
		{
			for (int i = 0; i < robots->size(); i++)
			{
				ret->push_back(robots->at(i));
			}
		}

		auto robotsSucc = this->epSucMapping->getRobots(ep);
		if (robotsSucc != nullptr)
		{
			for (int i = 0; i < robotsSucc->size(); i++)
			{
				auto iter = robotsSucc->begin();
				advance(iter, i);
				ret->push_back((*iter));
			}
		}

		return ret;
	}

	shared_ptr<list<int> > Assignment::getUniqueRobotsWorkingAndFinished(EntryPoint* ep)
	{
		shared_ptr<list<int> > ret = make_shared<list<int> >(list<int>());
		auto robots = this->epRobotsMapping->getRobots(ep);
		for (int i = 0; i < robots->size(); i++)
		{
			ret->push_back(robots->at(i));
		}
		for (auto r : (*this->epSucMapping->getRobots(ep)))
		{
			if (find(ret->begin(), ret->end(), r) == ret->end())
			{
				ret->push_back(r);
			}
		}
		return ret;
	}

	shared_ptr<list<int> > Assignment::getRobotsWorkingAndFinished(long epid)
	{
		shared_ptr<list<int> > ret = make_shared<list<int> >(list<int>());
		auto robots = this->epRobotsMapping->getRobotsById(epid);
		if (robots != nullptr)
		{
			for (int i = 0; i < robots->size(); i++)
			{
				ret->push_back(robots->at(i));
			}
		}

		auto robotsSucc = this->epSucMapping->getRobotsById(epid);
		if (robotsSucc != nullptr)
		{
			for (int i = 0; i < robotsSucc->size(); i++)
			{
				auto iter = robotsSucc->begin();
				advance(iter, i);
				ret->push_back((*iter));
			}
		}

		return ret;
	}

	SuccessCollection* Assignment::getEpSuccessMapping()
	{
		return this->epSucMapping;
	}

	void Assignment::setAllToInitialState(unique_ptr<list<int> > robots, EntryPoint* defep)
	{
		auto rlist = this->epRobotsMapping->getRobots(defep);
		for (int r : (*robots))
		{
			rlist->push_back(r);
		}
		for (int r : (*robots))
		{
			this->robotStateMapping->setState(r, defep->getState());
		}
	}

	bool Assignment::removeRobot(int robotId)
	{
		this->robotStateMapping->removeRobot(robotId);
		for (int i = 0; i < this->epRobotsMapping->getCount(); i++)
		{
			auto iter = find(this->epRobotsMapping->getRobots()[i]->begin(),
								this->epRobotsMapping->getRobots()[i]->end(), robotId);
			if (iter != this->epRobotsMapping->getRobots()[i]->end())
			{
				this->epRobotsMapping->getRobots()[i]->erase(iter);
				return true;
			}
		}
		return false;
	}

	void Assignment::addRobot(int id, EntryPoint* e, State* s)
	{
		if (e == nullptr)
		{
			return;
		}
		this->robotStateMapping->setState(id, s);
		this->epRobotsMapping->getRobots(e)->push_back(id);
		return;
	}

	bool Assignment::isValid()
	{
		auto robots = this->epRobotsMapping->getRobots();
		auto eps = this->epRobotsMapping->getEntryPoints();
		auto success = this->epSucMapping->getRobots();
		for (int i = 0; i < robots.size(); ++i)
		{
			int c = robots[i]->size() + success[i]->size();
			if (c > eps[i]->getMaxCardinality() || c < eps[i]->getMinCardinality())
			{
				return false;
			}
		}
		return true;
	}

	bool Assignment::isSuccessfull()
	{
		for (int i = 0; i < this->epSucMapping->getCount(); i++)
		{
			if (this->epSucMapping->getEntryPoints()[i]->getSuccessRequired())
			{
				if (!(this->epSucMapping->getRobots()[i]->size() > 0
						&& this->epSucMapping->getRobots()[i]->size()
								>= this->epSucMapping->getEntryPoints()[i]->getMinCardinality()))
				{
					return false;
				}
			}

		}
		return true;
	}

	bool Assignment::isEqual(Assignment* otherAssignment)
	{
		if(otherAssignment == nullptr)
		{
			return false;
		}
		if(this->epRobotsMapping->getCount() != otherAssignment->epRobotsMapping->getCount())
		{
			return false;
		}
		auto ownEps = this->epRobotsMapping->getEntryPoints();
		auto otherEps = otherAssignment->epRobotsMapping->getEntryPoints();
		for(int i = 0; i < ownEps.size(); ++i)
		{
			if(ownEps[i]->getId() != otherEps[i]->getId())
			{
				return false;
			}
		}
		auto ownRobots = this->epRobotsMapping->getRobots();
		auto otherRobots = otherAssignment->epRobotsMapping->getRobots();
		for(int i = 0; i < ownRobots.size(); ++i)
		{
			if(ownRobots[i]->size() != otherRobots[i]->size())
			{
				return false;
			}

			for(int robot : (*ownRobots[i]))
			{
				auto iter = find(otherRobots[i]->begin(), otherRobots[i]->end(), robot);
				if(iter == otherRobots[i]->end())
				{
					return false;
				}
			}
		}
		return true;
	}

	bool Assignment::isEntryPointNonEmpty(EntryPoint* ep)
	{
		auto r = this->epRobotsMapping->getRobots(ep);
		if (r != nullptr && r->size() > 0)
		{
			return true;
		}
		auto epSuc = this->epSucMapping->getRobots(ep);
		return (epSuc != nullptr && epSuc->size() > 0);
	}

	bool Assignment::updateRobot(int robot, EntryPoint* ep, State* s)
	{
		this->robotStateMapping->setState(robot, s);
		bool ret = false;
		for (int i = 0; i < this->epRobotsMapping->getCount(); i++)
		{
			if (this->epRobotsMapping->getEntryPoints()[i] == ep)
			{
				if (find(this->epRobotsMapping->getRobots()[i]->begin(), this->epRobotsMapping->getRobots()[i]->end(),
							robot) != this->epRobotsMapping->getRobots()[i]->end())
				{
					return false;
				}
				else
				{
					this->epRobotsMapping->getRobots()[i]->push_back(robot);
					ret = true;
				}
			}
			else
			{
				auto iter = find(this->epRobotsMapping->getRobots()[i]->begin(),
									this->epRobotsMapping->getRobots()[i]->end(), robot);
				if (iter != this->epRobotsMapping->getRobots()[i]->end())
				{
					this->epRobotsMapping->getRobots()[i]->erase(iter);
					ret = true;
				}
			}
		}
		return ret;
	}

	bool Assignment::updateRobot(int robot, EntryPoint* ep)
	{
		bool ret = false;
		for (int i = 0; i < this->epRobotsMapping->getCount(); i++)
		{
			if (this->epRobotsMapping->getEntryPoints()[i] == ep)
			{
				if (find(this->epRobotsMapping->getRobots()[i]->begin(), this->epRobotsMapping->getRobots()[i]->end(),
							robot) != this->epRobotsMapping->getRobots()[i]->end())
				{
					return false;
				}
				else
				{
					this->epRobotsMapping->getRobots()[i]->push_back(robot);
					ret = true;
				}
			}
			else
			{
				auto iter = find(this->epRobotsMapping->getRobots()[i]->begin(),
									this->epRobotsMapping->getRobots()[i]->end(), robot);
				if (iter != this->epRobotsMapping->getRobots()[i]->end())
				{
					this->epRobotsMapping->getRobots()[i]->erase(iter);
					ret = true;
				}
			}
		}
		if (ret)
		{
			this->robotStateMapping->setState(robot, ep->getState());
		}
		return ret;
	}

	bool Assignment::removeRobot(int robot, EntryPoint* ep)
	{
		if (ep == nullptr)
		{
			return false;
		}
		this->robotStateMapping->removeRobot(robot);
		auto iter = find(this->epRobotsMapping->getRobots(ep)->begin(), this->epRobotsMapping->getRobots(ep)->end(),
							robot);
		if (iter != this->epRobotsMapping->getRobots(ep)->end())
		{
			this->epRobotsMapping->getRobots(ep)->erase(iter);
			return true;
		}
		else
		{
			return false;
		}
	}

	string Assignment::assignmentCollectionToString()
	{
		stringstream ss;
		ss << "ASS" << endl;
		ss << this->epRobotsMapping->toString();
		return ss.str();
	}

	void Assignment::addRobot(int id, EntryPoint* e)
	{

		if (e == nullptr)
		{
			return;
		}
		this->epRobotsMapping->getRobots(e)->push_back(id);
		return;
	}

	void Assignment::moveRobots(State* from, State* to)
	{
		auto movingRobots = this->robotStateMapping->getRobotsInState(from);
		for (int r : movingRobots)
		{
			this->robotStateMapping->setState(r, to);
		}
	}

	EntryPoint* Assignment::entryPointOfRobot(int robot)
	{
		for (int i = 0; i < this->epRobotsMapping->getCount(); i++)
		{
			auto iter = find(this->epRobotsMapping->getRobots()[i]->begin(),
								this->epRobotsMapping->getRobots()[i]->end(), robot);
			if (iter != this->epRobotsMapping->getRobots()[i]->end())
			{
				return this->epRobotsMapping->getEntryPoints()[i];
			}
		}
		return nullptr;
	}

	shared_ptr<vector<int> > Assignment::getAllRobots()
	{
		auto ret = make_shared<vector<int> >(vector<int>());
		for (int i = 0; i < this->epRobotsMapping->getCount(); i++)
		{
			for (int j = 0; j < this->epRobotsMapping->getRobots()[i]->size(); j++)
			{
				ret->push_back(this->epRobotsMapping->getRobots()[i]->at(j));
			}
		}
		return ret;
	}

	void Assignment::clear()
	{
		this->robotStateMapping->clear();
		this->epRobotsMapping->clear();
		this->epSucMapping->clear();
	}

	string Assignment::toString()
	{
		stringstream ss;
		ss << endl;
		ss << "Rating: " << this->max << endl;
		auto ownEps = this->epRobotsMapping->getEntryPoints();
		auto ownRobots = this->epRobotsMapping->getRobots();
		for(int i = 0; i < this->epRobotsMapping->getCount(); ++i)
		{
			ss << "EP: " << ownEps[i]->getId() << " Task: " << ownEps[i]->getTask()->getName() << " RobotIDs: ";
			for(int robot : (*ownRobots[i])){
				ss << robot << " ";
			}
			ss << endl;
 		}
		ss << this->robotStateMapping->toString();
		ss << this->epSucMapping->toString();
		return ss.str();
	}

	string Assignment::toHackString()
	{
		stringstream ss;
		ss << "ASS " << this->plan->getId() << " " << this->plan->getName() << ":\t";
		auto eps = this->epRobotsMapping->getEntryPoints();
		auto robots = this->epRobotsMapping->getRobots();
		auto suc = this->epSucMapping->getRobots();
		for (int i = 0; i < eps.size(); i++)
		{
			ss << eps[i]->getTask()->getName() << " ";
			for (int robotID : (*robots[i]))
			{
				ss << robotID + " ";
			}

			if (suc[i]->size() > 0)
			{
				ss << "\t Success: ";
				for (int robotID : (*suc[i]))
				{
					ss << robotID + " ";
				}
			}

		}
		ss << endl;
		return ss.str();
	}

} /* namespace alica */
