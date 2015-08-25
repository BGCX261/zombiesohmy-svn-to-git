#include "Civilian.h"
#include "CivilianOwnedStates.h"


bool Civilian::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}
//-----------------------------------------------------------------------------
void Civilian::AddToItemsCarried(const int val)
{
  m_iItemsCarried += val;

  if (m_iItemsCarried < 0) m_iItemsCarried = 0;
}


//-----------------------------------------------------------------------------
void Civilian::AddToItems(const int val)
{
  m_iItemsAtBase += val;

  if (m_iItemsAtBase < 0) m_iItemsAtBase = 0;
}


//-----------------------------------------------------------------------------
void Civilian::Update()
{
  m_iZombieSpotted += 1;
  
  m_pStateMachine->Update();
}


//-----------------------------------------------------------------------------


void Civilian::Render(void)
{

	//glTranslatef((float)this->GetXPos(),(float)this->GetYPos(),0.0f);						
	//glRotatef(rtri,0.0f,0.0f,1.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glColor4f(0.0f,1.0f,1.0f,0.7);						// Set Top Point Of Triangle To Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// First Point Of The Triangle
		glColor4f(1.0f,0.0f,0.0f,0.7);						// Set Left Point Of Triangle To Green
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Second Point Of The Triangle
		glColor4f(1.0f,0.0f,0.0f,0.7);						// Set Right Point Of Triangle To Blue
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Third Point Of The Triangle
	glEnd();											// Done Drawing The Triangle
}

bool Civilian::IsProtected()const
{
	if(m_iProtected > ProtectionLevel)
	{
		return true;
	}

	return false;
}

void Civilian::setHealth(int h)
{
	m_iHealth = h;
}

void Civilian::IncreaseHealth(int h)
{
	m_iHealth += h;
}

//---------------------------------------------------------------------------