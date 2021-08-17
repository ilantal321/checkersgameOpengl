/*
ilan tal 312201619
*/


#include <glut.h>
#include <stdio.h>
#include <math.h>

int SIZE = 12;
int newgamesubmenu, boardcolormenu, darkboardmenu, lightboardmenu, pcolormenu;
double lightred = 0.7, lightgreen = 0.7, lightblue = 0.7;
double darkred = 0.3, darkgreen = 0.3, darkblue = 0.3;
double redp1 = 0.7, greenp1 = 0.7, bluep1 = 0.7;
double redp2 = 0.3, greenp2 = 0.3, bluep2 = 0.3;
double p1red = 1, p1green = 0, p1blue = 1;
double p2red = 1, p2green = 1, p2blue = 0;
int box[12][12] = { 0 };
int torn = 1;
int flag = 0;
int xp, yp;
int number1 = 0, number2 = 0;

void cir(int xc, int yc, int r)// normal pice
{
	int x, y;
	double alfa;

	for (alfa = 0; alfa < 360; alfa += 0.5)
	{
		x = xc + floor(r*cos(alfa*3.14 / 180) + 0.5);
		y = yc + floor(r*sin(alfa*3.14 / 180) + 0.5);

		glBegin(GL_POINTS);

		glVertex2i(x, y);

		glEnd();

	}
}
void cir1(int xc, int yc, int r)//king
{
	int x, y;
	double alfa;

	for (alfa = 0; alfa < 360; alfa += 0.5)
	{
		x = xc + floor(r*cos(alfa*3.14 / 180) + 0.5);
		y = yc + floor(r*sin(alfa*3.14 / 180) + 0.5);

		glBegin(GL_LINES);
		glVertex2i(xc, yc);
		glVertex2i(x, y);

		glEnd();

	}

}
void Reshape(int width, int height)//new size to window
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SIZE * 50, SIZE * 50, 0);
	glMatrixMode(GL_MODELVIEW);
}
void kings()// make kings
{
	int i = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (box[i][0] == 1)
		{
			box[i][0] = 3;
		}
		if (box[i][SIZE - 1] == 2)
		{
			box[i][SIZE - 1] = 4;
		}
	}
}
void begin()//drow board with picese
{
	int i, j;
	kings();
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if ((i + j) % 2 == 1)
			{
				glColor3f(lightred, lightgreen, lightblue);

			}
			if ((i + j) % 2 == 0)
			{
				glColor3f(darkred, darkgreen, darkblue);

			}
			glRectf(i * 50, j * 50, i * 50 + 50, j * 50 + 50);
			if (box[i][j] == 1)
			{
				glColor3f(p1red, p1green, p1blue);
				cir((i * 50) + 25, j * 50 + 25, 20);
			}
			if (box[i][j] == 2)
			{
				glColor3f(p2red, p2green, p2blue);
				cir(i * 50 + 25, j * 50 + 25, 20);
			}

			if (box[i][j] == 3)//king p1
			{
				glColor3f(p1red, p1green, p1blue);
				cir1(i * 50 + 25, j * 50 + 25, 20);
			}
			if (box[i][j] == 4)//king p2
			{
				glColor3f(p2red, p2green, p2blue);
				cir1(i * 50 + 25, j * 50 + 25, 20);
			}


		}
	}
}


void Draw(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	begin();
	glFlush();
}
void MouseFunc(int button, int state, int x, int y)
{

	int xx, yy;
	xx = x / 50;
	yy = y / 50;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && torn == 1 && flag == 0)// player 1 chose a pice
	{
		if (box[xx][yy] == 1 || box[xx][yy] == 3)
		{
			xp = xx;
			yp = yy;
			flag = 1;
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 1 && torn == 1) // a place to go p1
	{
		if (box[xx][yy] == 0)
		{
			if ((xx - 1 == xp || xx + 1 == xp) && yy == yp - 1 && !number1)// normal move for pice & king
			{
				if (box[xp][yp] == 3)
				{
					box[xx][yy] = 3;
				}
				else
				{
					box[xx][yy] = 1;
				}
				box[xp][yp] = 0;
				xp = -2;
				yp = -2;
				torn = 2;
			}
			if (box[xp][yp] == 3 && ((xx - 1 == xp || xx + 1 == xp) && yy == yp + 1) && !number1)// king move
			{
				box[xx][yy] = 3;
				box[xp][yp] = 0;
				xp = -2;
				yp = -2;
				torn = 2;
				number1 = 0;
			}
			if ((xx - 2 == xp && (box[xx - 1][yy + 1] == 2 || box[xx - 1][yy + 1] == 4) && yy == yp - 2))// eat pice l to r
			{
				box[xx - 1][yy + 1] = 0;

				if (box[xp][yp] == 3)
				{
					box[xx][yy] = 3;
				}
				else
				{
					box[xx][yy] = 1;
				}
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 2;
				number1 = 0;
			}
			if ((xx + 2 == xp && (box[xx + 1][yy + 1] == 2 || box[xx + 1][yy + 1] == 4) && yy == yp - 2))//eat pice r to l
			{
				box[xx + 1][yy + 1] = 0;
				if (box[xp][yp] == 3)
				{
					box[xx][yy] = 3;
				}
				else
				{
					box[xx][yy] = 1;
				}
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 2;
				number1 = 0;
			}
			if ((box[xp][yp] == 3 && xx + 2 == xp && (box[xx + 1][yy - 1] == 2 || box[xx + 1][yy - 1] == 4) && yy == yp + 2))//king reverse eat r to l
			{
				box[xx + 1][yy - 1] = 0;
				box[xx][yy] = 3;
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 2;
				number1 = 0;
			}
			if ((box[xp][yp] == 3 && xx - 2 == xp && (box[xx - 1][yy - 1] == 2 || box[xx - 1][yy - 1] == 4) && yy == yp + 2))//king reverse eat l to r 
			{
				box[xx - 1][yy - 1] = 0;
				box[xx][yy] = 3;
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 2;
				number1 = 0;
			}
			flag = 0;
			if ((box[xx + 1][yy - 1] == 2 || box[xx + 1][yy - 1] == 4) && (box[xx + 2][yy - 2] == 0) && xp == -3 && yp == -3 && xx + 2 < SIZE && yy - 2 > -1)//p1 pice multieat
			{
				torn = 1;
				number1 = 1;
			}
			if ((box[xx - 1][yy - 1] == 2 || box[xx - 1][yy - 1] == 4) && (box[xx - 2][yy - 2] == 0) && xp == -3 && yp == -3 && xx - 2 > -1 && yy - 2 > -1)//p1 pice multi eat
			{
				torn = 1;
				number1 = 1;
			}
			if (box[xx][yy] == 3 && (box[xx - 1][yy + 1] == 2 || box[xx - 1][yy + 1] == 4) && (box[xx - 2][yy + 2] == 0) && xp == -3 && yp == -3 && xx - 2 > -1 && yy + 2 < SIZE)//p1 pice multi eat
			{
				torn = 1;
				number1 = 1;
			}
			if (box[xx][yy] == 3 && (box[xx + 1][yy + 1] == 2 || box[xx + 1][yy + 1] == 4) && (box[xx + 2][yy + 2] == 0) && xp == -3 && yp == -3 && xx + 2 < SIZE && yy + 2 < SIZE)//p1 pice multi eat
			{
				torn = 1;
				number1 = 1;
			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && torn == 2 && flag == 0)// player 2 chose king or pice
	{
		if (box[xx][yy] == 2 || box[xx][yy] == 4)
		{
			xp = xx;
			yp = yy;
			flag = 1;
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 1 && torn == 2)//p2 move
	{
		if (box[xx][yy] == 0)
		{
			if ((xx - 1 == xp || xx + 1 == xp) && yy == yp + 1 && !number2)// normal move
			{
				if (box[xp][yp] == 4)
				{
					box[xx][yy] = 4;
				}
				else
				{
					box[xx][yy] = 2;
				}
				box[xp][yp] = 0;
				xp = -2;
				yp = -2;
				torn = 1;
			}
			if (box[xp][yp] == 4 && ((xx - 1 == xp || xx + 1 == xp) && yy == yp - 1) && !number2)// king move
			{
				box[xx][yy] = 4;
				box[xp][yp] = 0;
				xp = -2;
				yp = -2;
				torn = 1;
			}
			if ((xx - 2 == xp && (box[xx - 1][yy - 1] == 1 || box[xx - 1][yy - 1] == 3) && yy == yp + 2))// normal eat r to l
			{
				box[xx - 1][yy - 1] = 0;
				if (box[xp][yp] == 4)
				{
					box[xx][yy] = 4;
				}
				else
				{
					box[xx][yy] = 2;
				}
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 1;
				number2 = 0;
			}
			if ((xx + 2 == xp && (box[xx + 1][yy - 1] == 1 || box[xx + 1][yy - 1] == 3) && yy == yp + 2))// normal eat l to r
			{
				box[xx + 1][yy - 1] = 0;
				if (box[xp][yp] == 4)
				{
					box[xx][yy] = 4;
				}
				else
				{
					box[xx][yy] = 2;
				}
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 1;
				number2 = 0;
			}
			if ((box[xp][yp] == 4 && xx + 2 == xp && (box[xx + 1][yy + 1] == 1 || box[xx + 1][yy + 1] == 3) && yy == yp - 2))//king reverse eat r to l
			{
				box[xx + 1][yy + 1] = 0;
				box[xx][yy] = 4;
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 1;
				number2 = 0;
			}
			if ((box[xp][yp] == 4 && xx - 2 == xp && (box[xx - 1][yy + 1] == 1 || box[xx - 1][yy + 1] == 3) && yy == yp - 2))//king reverse eat l to r 
			{
				box[xx - 1][yy + 1] = 0;
				box[xx][yy] = 4;
				box[xp][yp] = 0;
				xp = -3;
				yp = -3;
				torn = 1;
				number2 = 0;
			}
			flag = 0;
			if ((box[xx + 1][yy + 1] == 1 || box[xx + 1][yy + 1] == 3) && (box[xx + 2][yy + 2] == 0) && xp == -3 && yp == -3 && xx + 2 < SIZE && yy + 2 < SIZE)//p2 pice multieat
			{
				torn = 2;
				number2 = 1;
			}
			if ((box[xx - 1][yy + 1] == 1 || box[xx - 1][yy + 1] == 3) && (box[xx - 2][yy + 2] == 0) && xp == -3 && yp == -3 && xx - 2 > -1 && yy + 2 < SIZE)//p2 pice multi eat
			{
				torn = 2;
				number2 = 1;
			}
			if (box[xx][yy] == 4 && (box[xx - 1][yy - 1] == 1 || box[xx - 1][yy - 1] == 3) && (box[xx - 2][yy - 2] == 0) && xp == -3 && yp == -3 && xx - 2 > -1 && yy - 2 > -1)//p2 king pice multi eat
			{
				torn = 2;
				number2 = 1;
			}
			if (box[xx][yy] == 4 && (box[xx + 1][yy - 1] == 1 || box[xx + 1][yy - 1] == 3) && (box[xx + 2][yy - 2] == 0) && xp == -3 && yp == -3 && xx + 2 < SIZE && yy - 2 > -1)//p1 pice multi eat
			{
				torn = 2;
				number2 = 1;
			}
		}
	}
	Draw();
	glFlush();




}
void buildbox()// start new game
{
	int i = 0, j = 0;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			box[i][j] = 0;
			if ((i + j) % 2 == 1 && j > SIZE / 2 && j < SIZE && i < SIZE)
			{
				box[i][j] = 1;
			}
			if ((i + j) % 2 == 1 && j < (SIZE / 2) - 1 && i < SIZE)
			{
				box[i][j] = 2;
			}
			printf("%d ", box[i][j]);
		}
		printf("\n");
	}
}
void newgame(int what)//new game by size
{
	number1 = 0;
	number2 = 0;
	torn = 1;
	flag = 0;
	switch (what)
	{
	case 1:
		SIZE = 8;
		buildbox();
		glutReshapeWindow(SIZE * 50, SIZE * 50);

		Draw();
		break;
	case 2:
		SIZE = 10;
		buildbox();
		glutReshapeWindow(SIZE * 50, SIZE * 50);
		Draw();
		break;

	case 3:
		SIZE = 12;
		buildbox();
		glutReshapeWindow(SIZE * 50, SIZE * 50);
		Draw();
		break;
	}
}
void darkboard(int what)//dark board part color
{
	switch (what)
	{
	case 1:
		darkred = 0.7, darkgreen = 0.3, darkblue = 0.3;
		Draw();
		break;
	case 2:
		darkred = 0.3, darkgreen = 1, darkblue = 0.3;
		Draw();
		break;
	case 3:
		darkred = 0.3, darkgreen = 0.3, darkblue = 1;
		Draw();
		break;
	case 4:
		darkred = 1, darkgreen = 1, darkblue = 0.3;
		Draw();
		break;
	case 5:
		darkred = 0.3, darkgreen = 0.3, darkblue = 0.3;
		Draw();
		break;
	case 6:
		darkred = 1, darkgreen = 0.7, darkblue = 0.2;
		Draw();
		break;
	}
}

void lightboard(int what)//light board part color
{
	switch (what)
	{
	case 1:
		lightred = 1, lightgreen = 0.7, lightblue = 0.7;
		Draw();
		break;
	case 2:
		lightred = 0.7, lightgreen = 1, lightblue = 0.7;
		Draw();
		break;
	case 3:
		lightred = 0.7, lightgreen = 0.7, lightblue = 1;
		Draw();
		break;
	case 4:
		lightred = 1, lightgreen = 1, lightblue = 0.7;
		Draw();
		break;
	case 5:
		lightred = 0.7, lightgreen = 0.7, lightblue = 0.7;
		Draw();
		break;
	case 6:
		lightred = 1, lightgreen = 0.8, lightblue = 0.5;
		Draw();
		break;
	}
}
void changecolor(int value)//player change his color
{
	switch (value)
	{
	case 1:
		if (torn == 1)
		{
			p1red = 0, p1green = 0, p1blue = 0;
		}
		else
		{
			p2red = 0, p2green = 0, p2blue = 0;
		}
		Draw();
		break;
	case 2:
		if (torn == 1)
		{
			p1red = 1, p1green = 1, p1blue = 1;
		}
		else
		{
			p2red = 1, p2green = 1, p2blue = 1;
		}
		Draw();
		break;
	case 3:
		if (torn == 1)
		{
			p1red = 1, p1green = 0, p1blue = 0;
		}
		else
		{
			p2red = 1, p2green = 0, p2blue = 0;
		}
		Draw();
		break;
	case 4:
		if (torn == 1)
		{
			p1red = 0, p1green = 1, p1blue = 0;
		}
		else
		{
			p2red = 0, p2green = 1, p2blue = 0;
		}
		Draw();
		break;
	case 5:
		if (torn == 1)
		{
			p1red = 0, p1green = 0, p1blue = 1;
		}
		else
		{
			p2red = 0, p2green = 0, p2blue = 1;
		}
		Draw();
		break;
	case 6:
		if (torn == 1)
		{
			p1red = 1, p1green = 0, p1blue = 1;
		}
		else
		{
			p2red = 1, p2green = 0, p2blue = 1;
		}
		Draw();
		break;
	case 7:
		if (torn == 1)
		{
			p1red = 1, p1green = 1, p1blue = 0;
		}
		else
		{
			p2red = 1, p2green = 1, p2blue = 0;
		}
		Draw();
		break;
	}
}

/* Selection for main menu */
void main_menu(int value)
{
	switch (value) {
	case 1:
		exit(1); break;
	}
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitWindowSize(SIZE * 50, SIZE * 50);
	glutInitWindowPosition(50, 50);

	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("checkers");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutMouseFunc(MouseFunc);

	//new game select size
	darkboardmenu = glutCreateMenu(darkboard);
	glutAddMenuEntry("dark red", 1);
	glutAddMenuEntry("dark green", 2);
	glutAddMenuEntry("dark blue", 3);
	glutAddMenuEntry("dark yellow", 4);
	glutAddMenuEntry("dark gray", 5);
	glutAddMenuEntry("dark orange", 6);

	lightboardmenu = glutCreateMenu(lightboard);
	glutAddMenuEntry("light red", 1);
	glutAddMenuEntry("light green", 2);
	glutAddMenuEntry("light blue", 3);
	glutAddMenuEntry("light yellow", 4);
	glutAddMenuEntry("light gray", 5);
	glutAddMenuEntry("light orange", 6);

	newgamesubmenu = glutCreateMenu(newgame);
	glutAddMenuEntry("small", 1);
	glutAddMenuEntry("medium", 2);
	glutAddMenuEntry("big", 3);

	pcolormenu = glutCreateMenu(changecolor);
	glutAddMenuEntry("black", 1);
	glutAddMenuEntry("white", 2);
	glutAddMenuEntry("red", 3);
	glutAddMenuEntry("green", 4);
	glutAddMenuEntry("blue", 5);
	glutAddMenuEntry("purple", 6);
	glutAddMenuEntry("yellow", 7);

	/* Create main menu */
	glutCreateMenu(main_menu);

	glutAddSubMenu("new game", newgamesubmenu);
	glutAddSubMenu("light color board", lightboardmenu);
	glutAddSubMenu("dark color board", darkboardmenu);
	glutAddSubMenu("player color", pcolormenu);
	glutAddMenuEntry("EXIT", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//start menu
	glClearColor(1, 1, 1, 0);
	glutMainLoop();
	return 0;
}