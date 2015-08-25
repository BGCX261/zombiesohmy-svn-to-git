#include <fstream>
#include <time.h>
#include "GL/Glut.h"
#include <cmath>

#include "Soldier.h"
#include "Civilian.h"
#include "Zombie.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

void init(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glEnable (GL_BLEND);								// Enable Blending that allows translucency
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
}

//void display(void)
//{
//	EntityMgr->Display();
//}
//
void reshape(int w, int h)
{
	//windowW = w; windowH = h;
	//cout<<"windowWidth ="<<windowW<<"  windowHeight =   "<<windowH<<endl;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//
//void mouse(int a, int b, int c, int d)
//{
//
//}

void update()
{
	//go through the entity manager and update all our objects
	for (int i = 0; i < EntityManager::Instance()->m_EntityMap.size(); ++i)
	{
		EntityManager::Instance()->m_EntityMap[i]->Update();
	}

	//register them with the entity manager
	//EntityMgr->RegisterEntity(Bob);
	//EntityMgr->RegisterEntity(Stan);
	//EntityMgr->RegisterEntity(Steve);

	//run Bob, Stan, and Steve through a few Update calls
	//for (int i=0; i< EntityMgr->m_EntityMap.begin(; ++i)
	//{ 
	//	Bob->Update();
	//	Stan->Update();
	//	Steve->Update();

	//	Dispatch->DispatchDelayedMessages();

	//	Sleep(200);
	//}

	glutPostRedisplay();
}

void render()
{
	//glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	
	glLoadIdentity();

	//go through the entity manager and update all our objects
	for (int i = 0; i < EntityManager::Instance()->m_EntityMap.size(); ++i)
	{
		glPushMatrix();
		EntityManager::Instance()->m_EntityMap[i]->Render();
		glPopMatrix();

	}
	

	glutSwapBuffers();
}

std::ofstream os;

int main(int argc, char** argv)
{
	//Seed random number generator
	srand(time(NULL));
	//create a soldier
	Soldier Bob;

	//Create a Civilian
	Civilian Stan;

	//Create a Zombie
	Zombie Steve;


	//seed random number generator
	srand((unsigned) time(NULL));

	/*	START GLUT INITIALIZATION */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);

	init();
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	//glutMouseFunc(mouse);

	glutMainLoop();

	/*	END GLUT INITIALIZATION   */

	//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
	os.open("output.txt");
#endif



	//parse through entity manager and 
	//tidy up
	//delete Bob;
	//delete Stan;
	//delete Steve;

	//wait for a keypress before exiting
	PressAnyKeyToContinue();

	return 0;//Like a boss...
}