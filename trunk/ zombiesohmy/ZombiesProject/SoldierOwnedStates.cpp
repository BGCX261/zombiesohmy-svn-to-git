#include "SoldierOwnedStates.h"
#include "fsm/State.h"
#include "Soldier.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"
#include <time.h>

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif
//---------------------------------methods for Global State
SoldierGlobal* SoldierGlobal::Instance()
{
	static SoldierGlobal instance;

	return &instance;
}

void SoldierGlobal::Enter(Soldier* pSoldier)
{  

}

void SoldierGlobal::Execute(Soldier* pSoldier)
{

}

void SoldierGlobal::Exit(Soldier* pSoldier)
{

}

bool SoldierGlobal::OnMessage(Soldier* pSoldier, const Telegram& msg)
{	
	switch(msg.Msg)
	{
	case Msg_NeedAnEscort:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Sorry, I'm busy.";   
		}
		return true;
	case Msg_HitYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			pSoldier->AddToHealth(-110);
			if (pSoldier->Health() <= 0)
			{
				pSoldier->GetFSM()->ChangeState(Die::Instance());
			}
		}
		return true;
	case Msg_AttackingYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			pSoldier->GetFSM()->ChangeState(ShootZombie::Instance());
		}
		return true;
	case Msg_GoPatrol:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "I already am patrolling.";
		}
		return true;
	case Msg_StopPatrol:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "I'm not patrolling right now."; 
		}
		return true;
	case Msg_KilledMe:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			//receives the message that he killed his target
			//and goes back to wahtever he was doing
			pSoldier->GetFSM()->RevertToPreviousState();
		}
		return true;
	}

	//send msg to global message handler
	return false;
}
//---------------------------------methods for Idle
Idle* Idle::Instance()
{
	static Idle instance;

	return &instance;
}

void Idle::Enter(Soldier* pSoldier)
{  
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Woo, time to sit and do nothin";
	Dispatch->DispatchMessage(2.0,
							  pSoldier->ID(),
							  pSoldier->ID(),
							  Msg_GoPatrol,
							  NO_ADDITIONAL_INFO);
}

void Idle::Execute(Soldier* pSoldier)
{
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	pSoldier->AddToHealth(5);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Still sitting in the base. HP: " << pSoldier->Health();
}

void Idle::Exit(Soldier* pSoldier)
{
	//doesnt need to say anything upon exiting
}

bool Idle::OnMessage(Soldier* pSoldier, const Telegram& msg)
{	
	switch(msg.Msg)
	{
	case Msg_NeedAnEscort:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Lets roll";

			//tell the civilian that we are leaving
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pSoldier->ID(), ent_Stan,
								Msg_GetEscorted, NO_ADDITIONAL_INFO);

			pSoldier->GetFSM()->ChangeState(EscortCiv::Instance());               
		}
	case Msg_GoPatrol:
		{
			SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "I'm goin' on patrol.";			

			pSoldier->GetFSM()->ChangeState(Patrol::Instance());
		}
		return true;
	case Msg_AttackingYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Can't get me, I'm in the base";              
		}
		return true;
	case Msg_HitYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Can't get me, I'm in the base";              
		}
		return true;
	}
	//send msg to global message handler
	return false;
}

//---------------------------------methods for Patrol
Patrol* Patrol::Instance()
{
	static Patrol instance;

	return &instance;
}

void Patrol::Enter(Soldier* pSoldier)
{  
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "I'm bored, time to patrol.";

	{
	Dispatch->DispatchMessage(5.0,	//delayed message to stop patrolling later
							  pSoldier->ID(),
							  pSoldier->ID(),
							  Msg_StopPatrol,
							  NO_ADDITIONAL_INFO);
	}
}

void Patrol::Execute(Soldier* pSoldier)
{
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "It's scary out here. HP: " << pSoldier->Health();

	//Moving the Soldier.  Just in one direction...for now.
	pSoldier->Wander();
}

void Patrol::Exit(Soldier* pSoldier)
{
}

bool Patrol::OnMessage(Soldier* pSoldier, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_StopPatrol:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "I need to get back to base.";

			//tells the soldier to start heading back to the base from his patrol
			pSoldier->GetFSM()->ChangeState(BackToBase::Instance());               
		}

		return true;
	}
	//send msg to global message handler
	return false;
}

//////////////////////////////////////////////////////
//--------------methods for EscortCiv				//
//////////////////////////////////////////////////////
EscortCiv* EscortCiv::Instance()
{
	static EscortCiv instance;

	return &instance;
}

void EscortCiv::Enter(Soldier* pSoldier)
{  
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "What? Protection? Sure.";
	pSoldier->SetViewDistance(200.0);
}

void EscortCiv::Execute(Soldier* pSoldier)
{
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Let's keep moving. HP: " << pSoldier->Health();

	//when we get to the location of the pills
	//tell civilian we got em so we can go back home
	if ((rand() % 6) == 0)
	{
		pSoldier->GetFSM()->ChangeState(BackToBase::Instance());
		//tell the civilian that we are leaving
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pSoldier->ID(), ent_Stan,
									Msg_GotThePills, NO_ADDITIONAL_INFO);
	}
}

void EscortCiv::Exit(Soldier* pSoldier)
{
	//Not escorting, doesnt have the sight bonus
	pSoldier->SetViewDistance(100.0);
}

bool EscortCiv::OnMessage(Soldier* pSoldier, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//////////////////////////////////////////////////////
//--------------methods for BackToBase				//
//////////////////////////////////////////////////////
BackToBase* BackToBase::Instance()
{
	static BackToBase instance;

	return &instance;
}

void BackToBase::Enter(Soldier* pSoldier)
{  
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Haul ass back to base.";
}

void BackToBase::Execute(Soldier* pSoldier)
{
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Still heading straight for base";

	//If the soldier is back at the base, go into the idle state
	if ((rand() % 5) == 0)
	{
		pSoldier->GetFSM()->ChangeState(Idle::Instance());
	}
}

void BackToBase::Exit(Soldier* pSoldier)
{
}

bool BackToBase::OnMessage(Soldier* pSoldier, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//////////////////////////////////////////////////////
//-----------------methods for ShootZombie			//
//////////////////////////////////////////////////////
ShootZombie* ShootZombie::Instance()
{
	static ShootZombie instance;

	return &instance;
}

void ShootZombie::Enter(Soldier* pSoldier)
{  
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Get back! Opening fire!";
}

void ShootZombie::Execute(Soldier* pSoldier)
{
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Shooting a zombie. HP: " << pSoldier->Health();

	//tell the zombie I am shooting at him, so he can chase me
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pSoldier->ID(), ent_Zombie,
								Msg_AttackingYou, NO_ADDITIONAL_INFO);

	//let the zombie know that I'm a damn good shot, and I always hit him too
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,	pSoldier->ID(), ent_Zombie,
								Msg_HitYou, NO_ADDITIONAL_INFO);
}

void ShootZombie::Exit(Soldier* pSoldier)
{
}

bool ShootZombie::OnMessage(Soldier* pSoldier, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_AttackingYou:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pSoldier->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "I'm already shooting the zombie!";              
		}
		return true;
	}
	//send msg to global message handler
	return false;
}


//////////////////////////////////////////////////////
//-----------------------methods for Die			//
//////////////////////////////////////////////////////
Die* Die::Instance()
{
	static Die instance;

	return &instance;
}

void Die::Enter(Soldier* pSoldier)
{  
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Oh noes I am dying!";

	//tells the zombie that the soldier was killed, so he can do other things
	Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, pSoldier->ID(), ent_Zombie, Msg_KilledMe, NO_ADDITIONAL_INFO);
}

void Die::Execute(Soldier* pSoldier)
{
	SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pSoldier->ID()) << ": " << "Blarg I am dead";

	//move the soldier back to the base instantly and reset his info
	pSoldier->GetFSM()->ChangeState(Idle::Instance());
	pSoldier->SetHealth(100);
}

void Die::Exit(Soldier* pSoldier)
{
}

bool Die::OnMessage(Soldier* pSoldier, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}