#include "CivilianOwnedStates.h"
#include "State.h"
#include "Civilian.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include <time.h>

#include <iostream>
using std::cout;

//define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


CivilianGlobal* CivilianGlobal::Instance()
{
	static CivilianGlobal instance;

	return &instance;
}

void CivilianGlobal::Enter(Civilian* pCivilian)
{  

}

void CivilianGlobal::Execute(Civilian* pCivilian)
{

}

void CivilianGlobal::Exit(Civilian* pCivilian)
{

}

bool CivilianGlobal::OnMessage(Civilian* pCivilian, const Telegram& msg)
{	
	switch(msg.Msg)
	{
	case Msg_HitYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pCivilian->ID()) <<
				" at time: " << Clock->GetCurrentTime();

				pCivilian->GetFSM()->ChangeState(CivilianDie::Instance());

				Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY,
											pCivilian->ID(),
											ent_Zombie,
											Msg_KilledMe,
											NULL);
		}
		return true;
	case Msg_GetEscorted:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pCivilian->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			pCivilian->GetFSM()->ChangeState(SearchForItems::Instance());
		}
		return true;
	case Msg_AttackingYou:
		{
			cout << "\nMessage received by" << GetNameOfEntity(pCivilian->ID()) <<
				" at time: " << Clock->GetCurrentTime();
			//receives message from zombie and flees from the zombie
			pCivilian->GetFSM()->ChangeState(FleeFromZombie::Instance());
		}
		return true;
	case Msg_GotThePills:
		{
			cout <<"\nMessage received by" << GetNameOfEntity(pCivilian->ID()) <<
				" at time: " << Clock->GetCurrentTime();
			//receives from soldier, so now civilian heads back to base
			pCivilian->GetFSM()->ChangeState(SearchForBase::Instance());
		}
		return true;
	}
	//send msg to global message handler
	return false;
}

//--------------------------------------methods for EnterMineAndDigForNugget

SearchForItems* SearchForItems::Instance()
{
  static SearchForItems instance;

  return &instance;
}

void SearchForItems::Enter(Civilian* pCivilian)
{
	  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "Hey, can you escort me?";

}


void SearchForItems::Execute(Civilian* pCivilian)
{  


  pCivilian->AddToItemsCarried(4);

  if (pCivilian->FullyLoaded())
  {
    pCivilian->GetFSM()->ChangeState(SearchForBase::Instance());
  }
}


void SearchForItems::Exit(Civilian* pCivilian)
{
}

bool SearchForItems::OnMessage(Civilian* pCivilian, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//----------------------------------------methods for VisitBankAndDepositGold

SearchForBase* SearchForBase::Instance()
{
  static SearchForBase instance;

  return &instance;
}


void SearchForBase::Enter(Civilian* pCivilian)
{    
    SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "Great, where the heck is the base?";
}


void SearchForBase::Execute(Civilian* pCivilian)
{    
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " 
       << "I think I've found the base!";

	   SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " 
         << "Found the base!  I'm so awesome!";
	pCivilian->GetFSM()->ChangeState(SittingAtBase::Instance());
}


void SearchForBase::Exit(Civilian* pCivilian)
{
}

bool SearchForBase::OnMessage(Civilian* pCivilian, const Telegram& msg)
{

  //send msg to global message handler
  return false;
}
//----------------------------------------methods for GoHomeAndSleepTilRested

CivilianDie* CivilianDie::Instance()
{
  static CivilianDie instance;

  return &instance;
}

void CivilianDie::Enter(Civilian* pCivilian)
{
	//Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, pCivilian->ID(), ent_Zombie, Msg_KilledMe, NO_ADDITIONAL_INFO);
	// SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY); 
 //   cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " 
 //         << "I regret everything!";
}

void CivilianDie::Execute(Civilian* pCivilian)
{ 
    SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY); 
    cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " 
          << "I regret everything!";

     pCivilian->GetFSM()->ChangeState(Spawn::Instance());
}

void CivilianDie::Exit(Civilian* pCivilian)
{ 

}

bool CivilianDie::OnMessage(Civilian* pCivilian, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


//------------------------------------------------methods for QuenchThirst

FleeFromZombie* FleeFromZombie::Instance()
{
  static FleeFromZombie instance;

  return &instance;
}

void FleeFromZombie::Enter(Civilian* pCivilian)
{
}

void FleeFromZombie::Execute(Civilian* pCivilian)
{
     SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
     cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "Time to invis and run.";
	if(rand() % 2 == 0)
	{
		Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY,
		pCivilian->ID(),
		ent_Zombie,
		Msg_KilledMe,
		NO_ADDITIONAL_INFO);
		pCivilian->GetFSM()->ChangeState(CivilianDie::Instance());
	}
	else
	{
		Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY,
								   pCivilian->ID(),
								   ent_Zombie,
								   Msg_DidNotEscape,
								   NO_ADDITIONAL_INFO);
	}
}

void FleeFromZombie::Exit(Civilian* pCivilian)
{ 
}

bool FleeFromZombie::OnMessage(Civilian* pCivilian, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

SittingAtBase* SittingAtBase::Instance()
{
  static SittingAtBase instance;

  return &instance;
}

void SittingAtBase::Enter(Civilian* pCivilian)
{

    SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "Man, this base is boring, wish I had a gold nugget.";

}

void SittingAtBase::Execute(Civilian* pCivilian)
{
     SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
	 pCivilian->SetItemsCarried(0);
     cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "I need to go out and get more pills, and I need an escort.";
     pCivilian->GetFSM()->ChangeState(SearchForItems::Instance());
	 Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY,
					  pCivilian->ID(),
					  ent_Soldier,
					  Msg_NeedAnEscort,
					  NO_ADDITIONAL_INFO);

}

void SittingAtBase::Exit(Civilian* pCivilian)
{ 
}

bool SittingAtBase::OnMessage(Civilian* pCivilian, const Telegram& msg)
{
	switch(msg.Msg)
	{
		case Msg_AttackingYou:
		{
			cout << "\nMessage received by" << GetNameOfEntity(pCivilian->ID()) <<
				" at time: " << Clock->GetCurrentTime();
			//receives message from zombie and flees from the zombie
			SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "Silly zombie, trix are for kids.";
			
			Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY,
									   pCivilian->ID(),
									   ent_Zombie,
									   Msg_Escaped,
									   NULL);
		}
		return true;
	}
  //send msg to global message handler
  return false;
}

//Executes after a civilian dies, when a new one spawns.
Spawn* Spawn::Instance()
{
  static Spawn instance;

  return &instance;
}

void Spawn::Enter(Civilian* pCivilian)
{
  
    SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "What the hell?  There are zombies out here?! Where'd they come from?";

}

void Spawn::Execute(Civilian* pCivilian)
{

     SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
     cout << "\n" << GetNameOfEntity(pCivilian->ID()) << ": " << "I think I need to find someplace safe.";
     pCivilian->GetFSM()->ChangeState(SearchForBase::Instance());
  
}

void Spawn::Exit(Civilian* pCivilian)
{ 
}

bool Spawn::OnMessage(Civilian* pCivilian, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}