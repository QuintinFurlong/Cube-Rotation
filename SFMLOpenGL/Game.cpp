#include "Game.h"

bool updatable = false;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);
	corners[0] = Vector3Class(-1.0f,1.0f,-7.0f);
	corners[1] = Vector3Class(1.0f, 1.0f, -7.0f);
	corners[2] = Vector3Class(-1.0f, 1.0f, -5.0f);
	corners[3] = Vector3Class(1.0f, 1.0f, -5.0f);
	corners[4] = Vector3Class(-1.0f, -1.0f, -7.0f);
	corners[5] = Vector3Class(1.0f, -1.0f, -7.0f);
	corners[6] = Vector3Class(-1.0f, -1.0f, -5.0f);
	corners[7] = Vector3Class(1.0f, -1.0f, -5.0f);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		initialize();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Front Face(6)
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(corners[2].X(), corners[2].Y(), corners[2].Z());
		glVertex3f(corners[3].X(), corners[3].Y(), corners[3].Z());
		glVertex3f(corners[6].X(), corners[6].Y(), corners[6].Z());
		glVertex3f(corners[7].X(), corners[7].Y(), corners[7].Z());
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		//Back Face(1)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(corners[0].X(), corners[0].Y(), corners[0].Z());
		glVertex3f(corners[1].X(), corners[1].Y(), corners[1].Z());
		glVertex3f(corners[5].X(), corners[5].Y(), corners[5].Z());
		glVertex3f(corners[4].X(), corners[4].Y(), corners[4].Z());
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		//Right Side Face(2)
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(corners[3].X(), corners[3].Y(), corners[3].Z());
		glVertex3f(corners[1].X(), corners[1].Y(), corners[1].Z());
		glVertex3f(corners[5].X(), corners[5].Y(), corners[5].Z());
		glVertex3f(corners[7].X(), corners[7].Y(), corners[7].Z());
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		//Left Side Face(5)
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(corners[0].X(), corners[0].Y(), corners[0].Z());
		glVertex3f(corners[2].X(), corners[2].Y(), corners[2].Z());
		glVertex3f(corners[6].X(), corners[6].Y(), corners[6].Z());
		glVertex3f(corners[4].X(), corners[4].Y(), corners[4].Z());
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		//Top Face(3)
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(corners[0].X(), corners[0].Y(), corners[0].Z());
		glVertex3f(corners[1].X(), corners[1].Y(), corners[1].Z());
		glVertex3f(corners[3].X(), corners[3].Y(), corners[3].Z());
		glVertex3f(corners[2].X(), corners[2].Y(), corners[2].Z());
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		//Bottom Face(4)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(corners[4].X(), corners[4].Y(), corners[4].Z());
		glVertex3f(corners[5].X(), corners[5].Y(), corners[5].Z());
		glVertex3f(corners[7].X(), corners[7].Y(), corners[7].Z());
		glVertex3f(corners[6].X(), corners[6].Y(), corners[6].Z());

		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	
	Matrix3 m1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		for (int inde = 0;inde < 8;inde++)
		{
			corners[inde] = m1.Rotation(1) * corners[inde];
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		for (int inde = 0; inde < 8; inde++)
		{
			corners[inde] = m1.Rotation(-1) * corners[inde];
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		for (int inde = 0; inde < 8; inde++)
		{
			corners[inde] = m1.Translate(.01, .01) * corners[inde];
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		for (int inde = 0; inde < 8; inde++)
		{
			corners[inde] = m1.Translate(-.01, -.01) * corners[inde];
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int inde = 0; inde < 8; inde++)
		{
			corners[inde] = m1.Scale(99,99) * corners[inde];
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int inde = 0; inde < 8; inde++)
		{
			corners[inde] = m1.Scale(101, 101) * corners[inde];
		}
	}

	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	glLoadIdentity();
	//glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis

	glCallList(1);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

