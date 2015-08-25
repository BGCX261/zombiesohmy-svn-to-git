#include "ZombieOwnedStates.h"
#include "State.h"
#include "Zombie.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"

#include <iostream>
using std::cout;

//define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------------------------------------------------
//Global:  This is the Global State.  The Zombie is always in this state
//------------------------------------------------------------------------

ZombieGlobal* ZombieGlobal::Instance()
{
  static ZombieGlobal instance;

  return &instance;
}

void ZombieGlobal::Enter(Zombie* pZombie)
{
}

void ZombieGlobal::Execute(Zombie* pZombie)
{  
}

void ZombieGlobal::Exit(Zombie* pZombie)
{
}

bool ZombieGlobal::OnMessage(Zombie* pZombie, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_AttackingYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			//tells the zombie to change his pursue target to the guy shooting him
			pZombie->GetFSM()->ChangeState(Persue::Instance());               
		}
		return true;
	case Msg_HitYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			//tells the zombie he got shot
			pZombie->AddHealth(-(int)rand() % 100);

			SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pZombie->ID()) << ":  " << "I got hit.  (" << pZombie->ZombieHealth() << ")";
			if(pZombie->ZombieHealth() <= 0)
				pZombie->GetFSM()->ChangeState(ZombieDie::Instance());
		}
		return true;
	case Msg_KilledMe:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			//receives the message that he killed his target
			pZombie->GetFSM()->ChangeState(Search::Instance());      
		}
		return true;

	case Msg_Escaped:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			//receives the message that his target escaped.  (Reverts to previous state).
			pZombie->GetFSM()->ChangeState(Search::Instance()); 
		}
		return true;
	case Msg_DidNotEscape:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time: " << Clock->GetCurrentTime();
			//receives message that civilian didn't escape
			pZombie->GetFSM()->ChangeState(Attack::Instance());	
		}
		return true;
	}
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------
//Spawn:  In this state, the zombies values are reset to default starting values.
//		  It immediately exits into the search state.
//Entrances:  Die
//Exits:  Search
//
//------------------------------------------------------------------------

ZombieSpawn* ZombieSpawn::Instance()
{
  static ZombieSpawn instance;

  return &instance;
}

void ZombieSpawn::Enter(Zombie* pZombie)
{
	SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "I have risen from the dead once more!";

  SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "That dirt nap felt great! (HP:  " << pZombie->ZombieHealth() << ")";
}


void ZombieSpawn::Execute(Zombie* pZombie)
{  
  //Immediatley Start Searching for target.
  pZombie->GetFSM()->ChangeState(Search::Instance());
}


void ZombieSpawn::Exit(Zombie* pZombie)
{
  SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "I'm hungry...I guess I'll go looking for brains...";
}

bool ZombieSpawn::OnMessage(Zombie* pZombie, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------
//	Search:	In this state, the zombie wanders untill it sees a human.  It will then persue it.
//
//  Entrances:  Spawn, Persue, Attack
//
//  Exits:  Persue, Die
//  
//------------------------------------------------------------------------

Search* Search::Instance()
{
  static Search instance;

  return &instance;
}


void Search::Enter(Zombie* pZombie)
{  
    SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "Now where could I find some brains?";
}


void Search::Execute(Zombie* pZombie)
{
  SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " 
       << "Still searching...";

  if ((rand() % 2) == 0)
  {
	SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pZombie->ID()) << ":  " << "I think I found some!";
	pZombie->GetFSM()->ChangeState(Persue::Instance());
  }

  pZombie->Wander();
}


void Search::Exit(Zombie* pZombie)
{

}

bool Search::OnMessage(Zombie* pZombie, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------
//	Persue:  In this state, the zombie attempts to close distance with its target.
//
//	Entrances:  Search, Attack
//
//	Exits:  Search, Attack, Die
//  
//------------------------------------------------------------------------

Persue* Persue::Instance()
{
  static Persue instance;

  return &instance;
}

void Persue::Enter(Zombie* pZombie)
{
    SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "Time to close the distance!";

	pZombie->SetTarget(); 
	if (pZombie->GetTarget() == 0)
		Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, pZombie->ID(), ent_Soldier, Msg_AttackingYou, NO_ADDITIONAL_INFO);
	else
		Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, pZombie->ID(), ent_Stan, Msg_AttackingYou, NO_ADDITIONAL_INFO);
}

void Persue::Execute(Zombie* pZombie)
{ 
    SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY); 
    cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " 
          << "Getting closer...";

	if((rand() % 2) == 0)
	{
		SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pZombie->ID()) << ":  " << "Close enough...Get ready to die, sucker!";
		pZombie->GetFSM()->ChangeState(Attack::Instance());
	}
}

void Persue::Exit(Zombie* pZombie)
{ 

}

bool Persue::OnMessage(Zombie* pZombie, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_AttackingYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			//tells the zombie to change his pursue target to the guy shootin him
			SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pZombie->ID()) << ":  " << "I'm already pursuing that guy...";
		}
		return true;
		
	case Msg_Escaped:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time:  " << Clock->GetCurrentTime();

			pZombie->GetFSM()->ChangeState(Search::Instance());
		}
		return true;
	}
  return false;
}


//------------------------------------------------------------------------
//	Attack:  The zombie is within range of its target, and is attempting to kill it.
//
//	Entrances:  Persue
//
//	Exits:  Search, Persue, Die
//------------------------------------------------------------------------

Attack* Attack::Instance()
{
  static Attack instance;

  return &instance;
}

void Attack::Enter(Zombie* pZombie)
{
    SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "Finally!  It's dinner time!";
}

void Attack::Execute(Zombie* pZombie)
{
     SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
     cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "BRAAAAAINSSSSSSS!!!!1!!!ONE!";

	 if (pZombie->GetTarget() == 0)
		Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, pZombie->ID(), ent_Soldier, Msg_HitYou, NO_ADDITIONAL_INFO);
}

void Attack::Exit(Zombie* pZombie)
{ 

}

bool Attack::OnMessage(Zombie* pZombie, const Telegram& msg)
{
  switch (msg.Msg)
  {
  	case Msg_Escaped:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			//receives the message that his target escaped.  (Reverts to previous state).
			pZombie->GetFSM()->ChangeState(Search::Instance()); 
		}
		return true;

	case Msg_DidNotEscape:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pZombie->ID()) <<
				" at time:  " << Clock->GetCurrentTime();

			Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, pZombie->ID(), ent_Stan, Msg_HitYou, NO_ADDITIONAL_INFO);
		}
		return true;

	case Msg_KilledMe:
		{
			pZombie->GetFSM()->ChangeState(Search::Instance());
		}
		return true;
  }
  
  //send msg to global message handler
  return false;
}


//-------------------------------------------------------------------------
//	Die:  The Zombie has Died
//
//	Entrances:  Persue, Attack, Search
//
//	Exits:  Spawn
//----------------------------------------------------------------
ZombieDie* ZombieDie::Instance()
{
  static ZombieDie instance;

  return &instance;
}

void ZombieDie::Enter(Zombie* pZombie)
{
    SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "Well I died...";

	//tell the soldier he killed the zombie so he can do somethin else
	Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, pZombie->ID(), ent_Soldier, Msg_KilledMe, NO_ADDITIONAL_INFO);
}

void ZombieDie::Execute(Zombie* pZombie)
{
     SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
     cout << "\n" << GetNameOfEntity(pZombie->ID()) << ": " << "Not like it's anything new...";


     pZombie->GetFSM()->ChangeState(ZombieSpawn::Instance());
}

void ZombieDie::Exit(Zombie* pZombie)
{
	pZombie->setHealth(100);
}

bool ZombieDie::OnMessage(Zombie* pZombie, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}