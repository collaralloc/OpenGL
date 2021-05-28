/*ʵ��5 ��ά�ļ��α任��ʵ��*/
/*�ο�p181����6-2��ʹ�ô�����ʾ����2����������������ʾ�߿��������,��������ʾ�������ͼ���������塣*/
#include"pch.h"
#include<cstdio>
#include<gl/glut.h>
#include <cstdlib>  
#include<cmath>
#include <windows.h>
#define MAX_CHAR 128
bool f = 0;
const float pi = 3.1415926;
void drawString(const char* str, GLfloat x, GLfloat y, GLfloat z) {
	//��x,y,zΪ��ʼλ�ã���ʾ�ַ���str  
	static GLuint lists;
	lists = glGenLists(MAX_CHAR);
	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	glListBase(lists);
	//��ʼλ��
	glRasterPos3f(x, y, z);
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
}
int iMode = 1;
GLuint lineList, lineList2;
GLint vp[4];
float xRot = 0.0, yRot = 0.0;
double ex, ey, ez;
int winWidth = 400, winHeight = 300;
GLubyte fly[] =
{
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
};
void Initial() {
	float x[] = { -2, 3.0-2, 2.0-2, 3.0-2 };
	float y[] = { -2, 2.0-2, 3.0-2,3.0-2 };
	float z[] = { 0, 0, 0, 1 };
	float cx[] = { 1, 0.0, 1.0, 0.0 };
	float cy[] = { 1, 1.0, 0.0,1.0 };
	float cz[] = { 0, 0, 0, 1 };
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//RGBA���ô��ڱ�����ɫΪ��ɫ
	glLineWidth(12.0);
	//MidBresehamEllipse(abs(50 - addw), abs(50 - addh));
	lineList = glGenLists(1);
	glNewList(lineList, GL_COMPILE);
	for (int i = 0; i < 4; i++) {
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 3; j++)
			glVertex3f(x[(i + j) % 4], y[(i + j) % 4], z[(i + j) % 4]);
		glEnd();
		glColor3f(cx[i], cy[i], cz[i]);
	}
	glEndList();
	lineList2 = glGenLists(2);
	glNewList(lineList2, GL_COMPILE);
	glBegin(GL_LINE_LOOP);
	glColor4f(0.0, 0.5, 1.0, 1.0);
	glVertex3f(x[0], y[0], z[0]);
	for (int j = 1; j < 3; j++) {
		glVertex3f(x[j], y[j], z[j]);
		glColor3f(cx[j], cy[j], cz[j]);
	}
	glEnd();
	glBegin(GL_LINES);
	glColor4f(0.0, 0.5, 1.0, 1.0);
	for (int j = 0; j < 3; j++) {
		glVertex3f(x[3], y[3], z[3]);
		glVertex3f(x[j], y[j], z[j]);
		glColor3f(cx[j], cy[j], cz[j]);
	}
	glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor4f(0.0, 1, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5);

	glColor4f(1, 0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 5, 0);

	glColor4f(0,0, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(5, 0, 0);
	//drawString("x axis",5,0,0);
	glEnd();
	glEndList();
}
void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//if (w <= h) gluOrtho2D(0, 5, 0, 6.0*((GLfloat)h / w));
	//else gluOrtho2D(0, 5.0*((GLfloat)h / w), 0, 6);
	
	winWidth = w; winHeight = h;

}
void Displayt() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  //������ǰ�ı任
	glEnable(GL_LINE_SMOOTH);  //ʹ�÷�����
	glEnable(GL_BLEND);  //���û�Ϻ���
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //ָ����Ϻ���
	
	glViewport(0, 0, winWidth / 2, winHeight);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	if (iMode == 1)  //iMode������ֵΪ���Ӧ����ͼ������ͼ�͸���ͼ
		gluLookAt(0, 3, 0, 0, 0, 0, 0, 0, 1); else //���۾���y�ᣬͷ��z�ᣬ��xOzƽ�棬������ԭ�㴦
		if (iMode == 2)
			gluLookAt(3, 0, 0, 0, 0, 0, 0, 0, 1); else//���۾���x�ᣬͷ��z�ᣬ��yOzƽ�棬������ԭ�㴦
			gluLookAt(0, 0, 3, 0, 0, 0, -1, 0, 0); //���۾���z�ᣬͷ��x�����ᣬ��xOyƽ�棬������ԭ�㴦
	glCallList(lineList2);
	glPopMatrix();
	drawString("x axis", 5, 0, 0);

	glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_STIPPLE);  //���ķ�ʽ
	glPolygonStipple(fly);
	gluPerspective(100.0f, (GLfloat)(winWidth / 2) / (GLfloat)winHeight, 1.0f, 100.0f);
	//ͨ�������ӽǵĽǶȷ�Χ���߿�����Լ�ǰ�������ʵ����ά͸��
	float dx=5, dy=5, dz=2;
	if (!f) {  //�����f�����ж��Ƿ�Ϊ��x����ת��f=0��Ϊ��x����ת��f=1Ϊ��y����ת
		dx = dx;  //ʹ�����ϵ���ά����任��ʽ��ʵ���۾�������任
		dy = dy * cos(xRot * pi / 180.0) - dz * sin(xRot * pi / 180.0); //ע�⻡����ת��
		dz = dy * sin(xRot * pi / 180.0) + dz * cos(xRot * pi / 180.0);
	}
	else {
		dx = dz * sin(yRot * pi / 180.0) + dx * cos(yRot * pi / 180.0);
		dy = dy;
		dz = dz * cos(yRot * pi / 180.0) - dx * sin(yRot * pi / 180.0);
	}
	gluLookAt(dx, dy, dz, 0, 0, 0, 0, 0, 1);
	glCallList(lineList2);
	glPopMatrix();
	glFlush();
}
void Displayw() {
	glClear(GL_COLOR_BUFFER_BIT);	//�õ�ǰ����ɫ��䴰��
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(fly);
	//glLoadIdentity();
	//glRotatef(xRot, 1.0, 0.0, 0.0);
	//glRotatef(yRot, 0.0, 1.0, 0.0);

	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, winWidth/2, winHeight);
	glGetIntegerv(GL_VIEWPORT, vp);
	glOrtho(-5, 5, -5, 5, -5, 5);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	glCallList(lineList);
	


	
	glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
	ex = 5*sin(xRot/57.4); ey = 0; ez = 2;
	gluPerspective(30,3.0/2.0,10,100);
	gluLookAt(ex,ey,ez,0,0,0,1,1,1);


	glGetIntegerv(GL_VIEWPORT, vp);
	glCallList(lineList2);
	glFlush();//���OpenGL��������ִ��OpenGL����
}
void ProcessMenu(int value) {
	iMode = value;
	glutPostRedisplay();
}
void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) xRot -= 2 ,f=0;
	if (key == GLUT_KEY_DOWN) xRot += 2,f=0;
	if (key == GLUT_KEY_LEFT) yRot -= 5,f=1;
	if (key == GLUT_KEY_RIGHT) yRot += 5,f=1;
	int k = x;
	x = (k + 360) % 360;
	k = y;
	y = (k + 360) % 360;
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(500, 120);
	glutCreateWindow("��������ӽ�");
	int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);
	glutAddMenuEntry("x", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Displayt);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	Initial();
	glutMainLoop();			//������GLUT�¼�����ѭ��
	return 0;
}