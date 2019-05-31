#include <math.h>
#include <iostream>
#include <glut.h>

//#pragma comment(lib, "legacy_stdio_definitions.lib")

using namespace std;

double g = 9.81, PI = 3.1415;

int Width = 700, Height = 700;
float i = 0;
int a = 0, b = 0;
double N, s;
double omega0, l; //omega0 угол отклонения
double A, omega, angle, sigma;

void Display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(-6, 16, 0);
	glLineWidth(2);
	glColor3d(1, 1, 1);
	//Потолок
	glBegin(GL_LINES);
	glVertex2d(-8, 0);
	glVertex2d(8, 0);

	glVertex2d(-8, 1);
	glVertex2d(-7, 0);
	glVertex2d(-5, 1);
	glVertex2d(-4, 0);
	glVertex2d(-2, 1);
	glVertex2d(-1, 0);

	glVertex2d(1, 1);
	glVertex2d(2, 0);
	glVertex2d(4, 1);
	glVertex2d(5, 0);
	glVertex2d(7, 1);
	glVertex2d(8, 0);

	glEnd();
	glRotatef(angle, 0, 0, 1);
	glColor3d(1, 1, 1);
	//Нить
	glBegin(GL_LINES);
	glVertex2d(0, 0);
	glVertex2d(0, -8);
	glEnd();

	glColor3d(1, 1, 1);
	//Шарик
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 100; i += 0.1)
	{
		glVertex2d(2 * sin(i), 2 * cos(i) - 10);
	}
	glEnd();

	glLoadIdentity();
	glLineWidth(4);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	//Оси
	glVertex2d(-20, -16);
	glVertex2d(-20, 0);
	glVertex2d(20, -8);
	glVertex2d(-20, -8);
	glVertex2d(20, -8);
	glVertex2d(19, -7.5);
	glVertex2d(20, -8);
	glVertex2d(19, -8.5);


	glVertex2d(-20, 0);
	glVertex2d(-19, -1.5);
	//t
	glVertex2d(16, -11.5);
	glVertex2d(16, -9);

	glVertex2d(17, -11.5);
	glVertex2d(16, -11.5);

	glVertex2d(16.5, -10.5);
	glVertex2d(15.5, -10.5);
	glEnd();
	if (N > 10*PI)
	{
		glTranslatef(-N + (11), -8, 0);
	}
	else
	{
		glTranslatef(-20, -8, 0);
	}
	glColor3d(1, 0.3, 0);

	glBegin(GL_LINE_STRIP);

	omega = sqrt(g / l);
	A = omega0 / (180 / PI);
	for (double i = 0; i < N; i += 0.01)
	{
		//график синуса
		glVertex2d(4 * i / PI, 4 * exp(-sigma*i)*sin(i*omega));
		//угол поворота
		angle = A*exp(-sigma*i)*sin(i*omega)*(180 / PI);//радиан
		if (fabs(A*exp(-sigma*i)*omega*sin(i*omega)) < 0.0004 && fabs(A*exp(-sigma*i)*omega*cos(i*omega)) < 0.0004)
		{
			return;
		}
	}
	glEnd();

	glLoadIdentity();
	glTranslatef(9, 5, 0);

	glLineWidth(2);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	//Оси фазового портрета
	glVertex2d(0, -10);
	glVertex2d(0, 10);
	glVertex2d(-10, 0);
	glVertex2d(10, 0);
	//x
	glVertex2d(-2, 8);
	glVertex2d(-3, 9);
	glVertex2d(-3, 8);
	glVertex2d(-2, 9);
	//x
	glVertex2d(-8, -2);
	glVertex2d(-9, -3);
	glVertex2d(-9, -2);
	glVertex2d(-8, -3);
	//.
	glVertex2d(-8.5, -1.4);
	glVertex2d(-8.3, -1.3);

	glEnd();

	glLineWidth(1);
	glColor3d(1, 0, 0);
	//фазовый портрет
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < N; i += 0.01)
	{
		if (exp(-sigma*i) > 0.01)
		{
			glVertex2d(exp(-sigma*i) * 8 * sin(i*omega + 0.01), exp(-sigma*i) * 8 * cos(i*omega + 0.01));
		}
		else glVertex2f(0, 0);
	}
	glEnd();
	glFinish();
}

void Timer(int = 0)
{
	Display();
	glutTimerFunc(10, Timer, 0);
	N += 0.01;
}

void Reshape(int w, int h)
{
	Width = w;
	Height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int left = 0, top = 0;
	if (w > h)
	{
		Width = h;
		left = (w - Width) / 2;
	}
	else
	{
		Height = w;
		top = (h - Height) / 2;
	}

	glViewport(left, top, Width, Height);
	gluOrtho2D(-20, 20, -20, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	do
	{
		cout << "Введите угол отклонения (от 0 до 90): ";
		cin >> omega0;
	} while (omega0 <= 0 || omega0 > 90);

	do
	{
		cout << "Введите длину подвеса: ";
		cin >> l;
	} while (l <= 0);
	if (l > 6)
	{
		l = 5;
	}
	do
	{
		cout << "Введите коэфициент затухания (от 0 до 1): ";
		cin >> sigma;
	} while (sigma < 0 || sigma > 1);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Pendulum");
	glutDisplayFunc(Display);
	Timer();
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
