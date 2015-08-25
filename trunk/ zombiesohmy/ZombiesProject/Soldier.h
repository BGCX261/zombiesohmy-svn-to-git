#ifndef SOLDIER_H
#define SOLDIER_H
//------------------------------------------------------------------------
//
//  Name:   Soldier.h
//
//  Desc:   A class defining a goldsoldier.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
//#include "MovingEntity.h"
#include "misc/ConsoleUtils.h"
#include "SoldierOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

class Soldier : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Soldier>*  m_pStateMachine;

	//how much health the soldier has, cap is 100, regenerates while idle
	int			m_iHealth;
	//the soldiers current field of view (changed when on patrol w/ civ)
	float		m_iViewDistance;
	//int killcount
	int			m_iKillCount;

public:
	Soldier():	  m_iViewDistance(100),
				  m_iHealth(100.0),
				  m_iKillCount(0),
				  BaseGameEntity(ent_Soldier)
	{
		//Set Starting Position
		SetPosition((rand() % 100) - 50, (rand() % 100) - 50);
		
		//set up state machine
		m_pStateMachine = new StateMachine<Soldier>(this);
		m_pStateMachine->SetCurrentState(Idle::Instance());
		m_pStateMachine->SetPreviousState(Idle::Instance());
		m_pStateMachine->SetGlobalState(SoldierGlobal::Instance());
	}

	~Soldier(){delete m_pStateMachine;}

	//this must be implemented
	void Update();
	void Render();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Soldier>* GetFSM()const{return m_pStateMachine;}

	//-------------------------------------------------------------accessors
	float	ViewDistance()const{return m_iViewDistance;}
	void	SetViewDistance(float val){m_iViewDistance = val;}

	int	Health()const{return m_iHealth;}
	void	SetHealth(int val){m_iHealth = val;}
	void	AddToHealth(int val);

};

#endif