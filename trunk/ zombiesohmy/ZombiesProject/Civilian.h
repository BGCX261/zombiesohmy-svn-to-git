#ifndef CIVILIAN_H
#define CIVILIAN_H
//------------------------------------------------------------------------
//
//  Name:   Civilian.h
//
//  Desc:   A class defining a civilian.
//
//  Author: Original Code: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
//#include "MovingEntity.h"
#include "misc/ConsoleUtils.h"
#include "CivilianOwnedStates.h"
#include "fsm/StateMachine.h"


template <class entity_type> class State;

//the amount of protection the civilian needs before feeling safe
const int ProtectionLevel       = 8;
//the amount of items the civilian needs before seeking protection
const int ItemsForTrip         = 3;
//above this value a civilian will flee hysterically from a zombie
const int Flee        = 5;
//above this value a civilian perishes from a zombie bite
const int BiteInfectionTolerance = 6;



class Civilian : public BaseGameEntity
{
private:

  StateMachine <Civilian>*      m_pStateMachine;

  //how many items the civilian has
  int                   m_iItemsCarried;

  int                   m_iItemsAtBase;

  //the higher the value, the closer the civilian is to fleeing
  int                   m_iZombieSpotted;

  //the higher the value, the worse the infection
  int                   m_iBiteInfection;

  //the higher the value, the safer the civilian feels
  int					m_iProtected;
  //health for the civilian
  int					m_iHealth;

public:

	Civilian():m_iItemsCarried(2),
                     m_iItemsAtBase(0),
                     m_iZombieSpotted(0),
                     m_iBiteInfection(0),
					 m_iProtected(0),
					 BaseGameEntity(ent_Stan)
  {
    //set up state machine
    m_pStateMachine = new StateMachine<Civilian>(this);
    
    m_pStateMachine->SetCurrentState(Spawn::Instance());

	m_pStateMachine->SetGlobalState(CivilianGlobal::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
  };

  //this must be implemented
  void Update();
  void Render();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  StateMachine<Civilian>* GetFSM()const{return m_pStateMachine;}
    
  int           ItemsCarried()const{return m_iItemsCarried;}
  void          SetItemsCarried(const int val){m_iItemsCarried = val;}
  void          AddToItemsCarried(const int val);
  bool          FullyLoaded()const{return m_iItemsCarried >= ItemsForTrip;}

  int           ItemsAtBase()const{return m_iItemsAtBase;}
  void          SetItems(const int val){m_iItemsAtBase = val;}
  void          AddToItems(const int val);

  bool			IsProtected()const;
  void			DecreaseProtection(){m_iProtected -=1;}
  void			IncreaseProtection(){m_iProtected +=1;}

  int			CivilianHealth()const{return m_iHealth;}
  void			setHealth(int);
  void			IncreaseHealth(int);

  //void			Render(void);

};


#endif