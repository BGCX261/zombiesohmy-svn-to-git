#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_NeedAnEscort,		//Civilian to Soldier
  Msg_GetEscorted,		//Soldier to civilian to say lets go then
  Msg_GotThePills,		//Soldier tell the civilian that we got the pills and can run back
  Msg_GoPatrol,			//Delayed Message to/from Soldier
  Msg_StopPatrol,		//Delayed Message to/from Soldier
  Msg_AttackingYou,		//Zombie to Soldier/Civilian  OR Soldier to Zombie
  Msg_HitYou,			//Zombie to Soldier/Civilian OR Soldier to Zombie  (Send message whenever an attack does some damage)
  Msg_KilledMe,			//Civilian/Soldier to Zombie OR Zombie to Soldier
  Msg_Escaped,			//Civilian to Zombie (When civilian succesfully runs away)
  Msg_DidNotEscape		//Civilian to Zombie (When civilian does not escape in time)
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_NeedAnEscort: 
    return "NeedAnEscort"; 

  case Msg_GetEscorted:
	  return "GetEscorted";

  case Msg_GotThePills:
	  return "GotThePills";

  case Msg_GoPatrol:
    
    return "GoPatrol";

  case Msg_StopPatrol:

	  return "StopPatrol";

  case Msg_AttackingYou:

	  return "AttackingYou";

  case Msg_HitYou:

	  return "HitYou";

  case Msg_KilledMe:

	  return "KilledMe";

  case Msg_Escaped:

	  return "Escaped";

  case Msg_DidNotEscape:

	  return "Didn'tEscape";

  default:

    return "Not recognized!";
  }
}

#endif