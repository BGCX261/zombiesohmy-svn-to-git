#ifndef ZOMBIE_OWNED_STATES_H
#define ZOMBIE_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//  States: Spawn, Search, Persue, Attack, Die
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Zombie;

//------------------------------------------------------------------------
//Global:  The Zombie is always in this state.  
//------------------------------------------------------------------------
class ZombieGlobal : public State<Zombie>
{
private:

  ZombieGlobal(){}

  //copy ctor and assignment should be private
  ZombieGlobal(const ZombieGlobal&);
  ZombieGlobal& operator=(const ZombieGlobal&);

public:

  //this is a singleton
  static ZombieGlobal* Instance();
  
  virtual void Enter(Zombie* zombie);

  virtual void Execute(Zombie* zombie);

  virtual void Exit(Zombie* zombie);

  virtual bool OnMessage(Zombie* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
//Spawn:  In this state, the zombies values are reset to default starting values.
//		  It immediately exits into the search state.
//Entrances:  Die
//Exits:  Search
//
//------------------------------------------------------------------------
class ZombieSpawn : public State<Zombie>
{
private:

  ZombieSpawn(){}

  //copy ctor and assignment should be private
  ZombieSpawn(const ZombieSpawn&);
  ZombieSpawn& operator=(const ZombieSpawn&);

public:

  //this is a singleton
  static ZombieSpawn* Instance();
  
  virtual void Enter(Zombie* zombie);

  virtual void Execute(Zombie* zombie);

  virtual void Exit(Zombie* zombie);

  virtual bool OnMessage(Zombie* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//	Search:	In this state, the zombie wanders untill it sees a human.  It will then persue it.
//
//  Entrances:  Spawn, Persue, Attack
//
//  Exits:  Persue, Die
//  
//------------------------------------------------------------------------
class Search : public State<Zombie>
{
private:

  Search(){}

  //copy ctor and assignment should be private
  Search(const Search&);
  Search& operator=(const Search&);
  
public:

  //this is a singleton
  static Search* Instance();

  virtual void Enter(Zombie* zombie);

  virtual void Execute(Zombie* zombie);

  virtual void Exit(Zombie* zombie);

  virtual bool OnMessage(Zombie* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//	Persue:  In this state, the zombie attempts to close distance with its target.
//
//	Entrances:  Search, Attack
//
//	Exits:  Search, Attack, Die
//  
//------------------------------------------------------------------------
class Persue : public State<Zombie>
{
private:

 Persue(){}

    //copy ctor and assignment should be private
  Persue(const Persue&);
  Persue& operator=(const Persue&);

public:

  //this is a singleton
  static Persue* Instance();

  virtual void Enter(Zombie* zombie);

  virtual void Execute(Zombie* zombie);

  virtual void Exit(Zombie* zombie);

  virtual bool OnMessage(Zombie* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//	Attack:  The zombie is within range of its target, and is attempting to kill it.
//
//	Entrances:  Persue
//
//	Exits:  Search, Persue, Die
//------------------------------------------------------------------------
class Attack : public State<Zombie>
{
private:
  
  Attack(){}

  //copy ctor and assignment should be private
  Attack(const Attack&);
  Attack& operator=(const Attack&);

public:

  //this is a singleton
  static Attack* Instance();

  virtual void Enter(Zombie* zombie);

  virtual void Execute(Zombie* zombie);

  virtual void Exit(Zombie* zombie);

  virtual bool OnMessage(Zombie* agent, const Telegram& msg);
};

//-------------------------------------------------------------------------
//	Die:  The Zombie has Died
//
//	Entrances:  Persue, Attack, Search
//
//	Exits:  Spawn
//-------------------------------------------------------------------------
class ZombieDie : public State<Zombie>
{
private:
	ZombieDie(){}

	ZombieDie(const ZombieDie&);
	ZombieDie& operator=(const ZombieDie&);

public:

	static ZombieDie* Instance();

	virtual void Enter(Zombie* zombie);

	virtual void Execute(Zombie* zombie);

	virtual void Exit(Zombie* zombie);

	virtual bool OnMessage(Zombie* agent, const Telegram& msg);
};


#endif