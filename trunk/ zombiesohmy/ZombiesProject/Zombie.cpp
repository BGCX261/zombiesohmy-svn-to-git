#include "Zombie.h"
#include "ZombieOwnedStates.h"
#include "GL/Glut.h"


bool Zombie::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}
//-----------------------------------------------------------------------------
void Zombie::Update()
{
  m_pStateMachine->Update();
}


//-----------------------------------------------------------------------------
void Zombie::AddHealth(int val)
{
	m_iHealth += val;
	if (m_iHealth >= MaxHealth)
		m_iHealth = MaxHealth;
}

//-----------------------------------------------------------------------------
void Zombie::SubHealth(int val)
{
	m_iHealth -= val;
	if (m_iHealth <= 0)
		m_iHealth = 0;
}
//-----------------------------------------------------------------------------
void Zombie::setHealth(int val)
{
	m_iHealth = val;
	if (m_iHealth >= MaxHealth)
		m_iHealth = MaxHealth;
	if (m_iHealth <= 0)
		m_iHealth = 0;
}
//-----------------------------------------------------------------------------
void Zombie::Render(void)
{

	glTranslatef(GetXPosition(),GetYPosition(),0.0f);										

	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glColor4f(1.0f,0.0f,0.0f,0.7);						// Set Top Point Of Triangle To Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// First Point Of The Triangle
		glColor4f(1.0f,0.0f,0.0f,0.7);						// Set Left Point Of Triangle To Green
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Second Point Of The Triangle
		glColor4f(1.0f,0.0f,0.0f,0.7);						// Set Right Point Of Triangle To Blue
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Third Point Of The Triangle
	glEnd();											// Done Drawing The Triangle
}

