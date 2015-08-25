#ifndef CIVILIAN_OWNED_STATES_H
#define CIVILIAN_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Civilian;

class CivilianGlobal : public State<Civilian>
{
private:
  
  CivilianGlobal(){}

  //copy ctor and assignment should be private
  CivilianGlobal(const CivilianGlobal&);
  CivilianGlobal& operator=(const CivilianGlobal&);
 
public:

  //this is a singleton
  static CivilianGlobal* Instance();

  virtual void Enter(Civilian* civilian);
  virtual void Execute(Civilian* civilian);
  virtual void Exit(Civilian* civilian);

  virtual bool OnMessage(Civilian* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  In this state the miner will walk to a goldmine and pick up a nugget
//  of gold. If the miner already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class SearchForItems : public State<Civilian>
{
private:

  SearchForItems(){}

  //copy ctor and assignment should be private
  SearchForItems(const SearchForItems&);
  SearchForItems& operator=(const SearchForItems&);

public:

  //this is a singleton
  static SearchForItems* Instance();
  
  virtual void Enter(Civilian* civilian);

  virtual void Execute(Civilian* civilian);

  virtual void Exit(Civilian* civilian);

  virtual bool OnMessage(Civilian* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  miner is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class SearchForBase : public State<Civilian>
{
private:

  SearchForBase(){}

  //copy ctor and assignment should be private
  SearchForBase(const SearchForBase&);
  SearchForBase& operator=(const SearchForBase&);
  
public:

  //this is a singleton
  static SearchForBase* Instance();

  virtual void Enter(Civilian* civilian);

  virtual void Execute(Civilian* civilian);

  virtual void Exit(Civilian* civilian);

  virtual bool OnMessage(Civilian* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  miner will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class CivilianDie : public State<Civilian>
{
private:

 CivilianDie(){}

    //copy ctor and assignment should be private
  CivilianDie(const CivilianDie&);
  CivilianDie& operator=(const CivilianDie&);

public:

  //this is a singleton
  static CivilianDie* Instance();

  virtual void Enter(Civilian* civilian);

  virtual void Execute(Civilian* civilian);

  virtual void Exit(Civilian* civilian);

  virtual bool OnMessage(Civilian* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class FleeFromZombie : public State<Civilian>
{
private:
  
  FleeFromZombie(){}

  //copy ctor and assignment should be private
  FleeFromZombie(const FleeFromZombie&);
  FleeFromZombie& operator=(const FleeFromZombie&);

public:

  //this is a singleton
  static FleeFromZombie* Instance();

  virtual void Enter(Civilian* civilian);

  virtual void Execute(Civilian* civilian);

  virtual void Exit(Civilian* civilian);

  virtual bool OnMessage(Civilian* agent, const Telegram& msg);
};

class SittingAtBase : public State<Civilian>
{
private:
	SittingAtBase(){}

	SittingAtBase(const SittingAtBase&);
	SittingAtBase& operator=(const SittingAtBase&);

public:

	static SittingAtBase* Instance();

	virtual void Enter(Civilian* civilian);

	virtual void Execute(Civilian* civilian);

	virtual void Exit(Civilian* civilian);

	virtual bool OnMessage(Civilian* agent, const Telegram& msg);
};

class Spawn : public State<Civilian>
{
private:
	Spawn(){}

	Spawn(const Spawn&);
	Spawn& operator=(const Spawn&);

public:

	static Spawn* Instance();

	virtual void Enter(Civilian* civilian);

	virtual void Execute(Civilian* civilian);

	virtual void Exit(Civilian* civilian);

	virtual bool OnMessage(Civilian* agent, const Telegram& msg);
};



#endif