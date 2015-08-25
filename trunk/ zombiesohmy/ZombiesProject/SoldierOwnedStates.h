#ifndef SOLDIER_OWNED_STATES_H
#define SOLDIER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   SoldierOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Soldier class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class Soldier;
struct Telegram;
//------------------------------------------------------------------------
//Global State
//------------------------------------------------------------------------
class SoldierGlobal : public State<Soldier>
{
private:
  
  SoldierGlobal(){}

  //copy ctor and assignment should be private
  SoldierGlobal(const SoldierGlobal&);
  SoldierGlobal& operator=(const SoldierGlobal&);
 
public:

  //this is a singleton
  static SoldierGlobal* Instance();

  virtual void Enter(Soldier* soldier);
  virtual void Execute(Soldier* soldier);
  virtual void Exit(Soldier* soldier);

  virtual bool OnMessage(Soldier* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
//	soldier will idle at the base, doing nothing until asked to go
//	on an escort with a civilian or gets bored and patrols
//------------------------------------------------------------------------
class Idle : public State<Soldier>
{
private:
  
  Idle(){}

  //copy ctor and assignment should be private
  Idle(const Idle&);
  Idle& operator=(const Idle&);
 
public:

  //this is a singleton
  static Idle* Instance();

  virtual void Enter(Soldier* soldier);
  virtual void Execute(Soldier* soldier);
  virtual void Exit(Soldier* soldier);

  virtual bool OnMessage(Soldier* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
//	soldier will go out on patrol to several random points, then return
//	after a few seconds
//------------------------------------------------------------------------
class Patrol : public State<Soldier>
{
private:
  
  Patrol(){}

  //copy ctor and assignment should be private
  Patrol(const Patrol&);
  Patrol& operator=(const Patrol&);
 
public:

  //this is a singleton
  static Patrol* Instance();

  virtual void Enter(Soldier* soldier);
  virtual void Execute(Soldier* soldier);
  virtual void Exit(Soldier* soldier);

  virtual bool OnMessage(Soldier* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
//	soldier will then begin to shoot at that zombie until it dies
//	after killing a zombie the soldier will reload his clip to full(12)
//------------------------------------------------------------------------
class ShootZombie : public State<Soldier>
{
private:
  
  ShootZombie(){}

  //copy ctor and assignment should be private
  ShootZombie(const ShootZombie&);
  ShootZombie& operator=(const ShootZombie&);
 
public:

  //this is a singleton
  static ShootZombie* Instance();

  virtual void Enter(Soldier* soldier);
  virtual void Execute(Soldier* soldier);
  virtual void Exit(Soldier* soldier);

  virtual bool OnMessage(Soldier* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
//	soldier will go out to get supplies with a civilian
//	civilian and soldier will work together to reach their destination
//	then return to the base as fast as possible
//------------------------------------------------------------------------
class EscortCiv : public State<Soldier>
{
private:
  
  EscortCiv(){}

  //copy ctor and assignment should be private
  EscortCiv(const EscortCiv&);
  EscortCiv& operator=(const EscortCiv&);
 
public:

  //this is a singleton
  static EscortCiv* Instance();

  virtual void Enter(Soldier* soldier);
  virtual void Execute(Soldier* soldier);
  virtual void Exit(Soldier* soldier);

  virtual bool OnMessage(Soldier* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
//	soldier will abandon his current objective and beeline for the base
//	soldier will still shoot zombies along the way
//------------------------------------------------------------------------
class BackToBase : public State<Soldier>
{
private:
  
  BackToBase(){}

  //copy ctor and assignment should be private
  BackToBase(const BackToBase&);
  BackToBase& operator=(const BackToBase&);
 
public:

  //this is a singleton
  static BackToBase* Instance();

  virtual void Enter(Soldier* soldier);
  virtual void Execute(Soldier* soldier);
  virtual void Exit(Soldier* soldier);

  virtual bool OnMessage(Soldier* agent, const Telegram& msg);
};
//------------------------------------------------------------------------
//	soldier dies. reset attributes
//------------------------------------------------------------------------
class Die : public State<Soldier>
{
private:
  
  Die(){}

  //copy ctor and assignment should be private
  Die(const Die&);
  Die& operator=(const Die&);
 
public:

  //this is a singleton
  static Die* Instance();

  virtual void Enter(Soldier* soldier);
  virtual void Execute(Soldier* soldier);
  virtual void Exit(Soldier* soldier);

  virtual bool OnMessage(Soldier* agent, const Telegram& msg);
};
#endif