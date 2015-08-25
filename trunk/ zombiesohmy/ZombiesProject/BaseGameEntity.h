#ifndef ENTITY_H
#define ENTITY_H
//------------------------------------------------------------------------
//
//  Name:   BaseGameEntity.h
//
//  Desc:   Base class for a game object
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include "GL/Glut.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include "messaging/Telegram.h"


class BaseGameEntity
{

private:

	//every entity must have a unique identifying number
	int			m_ID;

	//this is the next valid ID. Each time a BaseGameEntity is instantiated
	//this value is updated
	static int	m_iNextValidID;

	//this must be called within the constructor to make sure the ID is set
	//correctly. It verifies that the value passed to the method is greater
	//or equal to the next valid ID, before setting the ID and incrementing
	//the next valid ID
	void		SetID(int val);

	//****  Add Stuff for Motion Here ***/
	float			m_iXPos;	//The current XPosition of the entity.
	float			m_iYPos;	//The current YPosition of the entity.

public:

	BaseGameEntity(int id)
	{
		SetID(id);
		EntityMgr->RegisterEntity(this);
	}

	virtual ~BaseGameEntity(){}

	//all entities must implement an update function
	virtual void  Update()=0;
	virtual void Render()=0;

	//all entities can communicate using messages. They are sent
	//using the MessageDispatcher singleton class
	virtual bool  HandleMessage(const Telegram& msg)=0;

	int           ID()const{return m_ID;}

	//virtual void  Render();

	/****  Add functions for Motion in here/in the cpp  ***/
	void	SetPosition(float x, float y)
	{
		this->m_iXPos = x;
		this->m_iYPos = y;
	}

	float	GetXPosition(void)
	{
		return this->m_iXPos;
	}

	float	GetYPosition(void)
	{
		return this->m_iYPos;
	}

	void	Wander(void)
	{
		SetPosition(GetXPosition() + ((rand() % 3) - 1), GetYPosition() + ((rand() % 3) - 1));
	}
};



#endif