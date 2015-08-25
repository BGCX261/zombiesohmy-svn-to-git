#ifndef NAMES_H
#define NAMES_H

#include <string>

enum
{
  ent_Soldier,

  ent_Stan,

  ent_Zombie
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Soldier:

    return "Soldier";

  case ent_Stan:
    
    return "Civilian Stan";

  case ent_Zombie:

	  return "Zombie";

  default:

    return "UNKNOWN!";
  }
}

#endif