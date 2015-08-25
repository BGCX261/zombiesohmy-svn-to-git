#ifndef ZOMBIE_H
#define ZOMBIE_H
//------------------------------------------------------------------------
//
//  Name:   Zombie.h
//
//  Desc:   A class defining a zombie.
//
//  Author: Original Code: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "misc/ConsoleUtils.h"
#include "ZombieOwnedStates.h"
#include "fsm/StateMachine.h"
#include "Soldier.h"
#include "Civilian.h"


template <class entity_type> class State;

//The maximum health of a zombie.
const int MaxHealth       = 100;

class Zombie : public BaseGameEntity
{
private:

	int							m_iAttackRoll;		//A roll that holds the zombies selected target.

	StateMachine <Zombie>*      m_pStateMachine;	//A pointer to the zombies state machine

	
	int							m_iHealth;			//health for the zombie

	//BaseGameEntity*			m_pTarget;			//A pointer to the Zombie's current target
	Soldier*					m_pSoldier;			//A pointer to a soldier that the zombie sees

	Civilian*					m_pCivilian;		//A pointer to a civilian that the zombie sees

public:	

	Zombie():	 m_iHealth(MaxHealth),
				 BaseGameEntity(ent_Zombie),
				 m_pSoldier(NULL),
				 m_pCivilian(NULL)
	{
		//Set Starting Position
		SetPosition((rand() % 100) - 50, (rand() % 100) - 50);

		//set up state machine
		m_pStateMachine = new StateMachine<Zombie>(this);
		m_pStateMachine->SetCurrentState(ZombieSpawn::Instance());
		m_pStateMachine->SetGlobalState(ZombieGlobal::Instance());
		m_pStateMachine->SetPreviousState(ZombieSpawn::Instance());
	};

	//this must be implemented
	void Update();
	void Render();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Zombie>* GetFSM()const{return m_pStateMachine;}

	void			SetTarget(void){m_iAttackRoll = rand() % 2;}
	int				GetTarget(void){return m_iAttackRoll;}

	int				ZombieHealth()const{return m_iHealth;}
	void			AddHealth(int val);
	void			SubHealth(int val);
	void			setHealth(int val);

	void			SeeSoldier(Soldier* pSoldier){m_pSoldier = pSoldier;}
	void			SeeCivilian(Civilian* pCivilian){m_pCivilian = pCivilian;}

};


#endif
