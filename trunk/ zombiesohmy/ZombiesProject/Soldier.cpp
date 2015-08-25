#include "Soldier.h"

void Soldier::Render(void)
{
	glTranslatef(this->GetXPosition(),this->GetYPosition(),0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 0.7f);

	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glVertex3f( 0.0f, 1.0f, 0.0f);					// First Point Of The Triangle
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Second Point Of The Triangle
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Third Point Of The Triangle
	glEnd();											// Done Drawing The Triangle
}

bool Soldier::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}

void Soldier::Update()
{
  m_pStateMachine->Update();
}

void Soldier::AddToHealth(const int val)
{
  m_iHealth += val;

  //if (m_iHealth <= 0)
	  //m_pStateMachine->SetCurrentState(Die::Instance());
  if (m_iHealth > 100) m_iHealth = 100;
}