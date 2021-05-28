/*ʵ��5 ��ά�ļ��α任��ʵ��*/
/*�ο�p181����6-2��ʹ�ô�����ʾ����2����������������ʾ�߿��������,��������ʾ�������ͼ���������塣*/
#include"pch.h"
#include<cstdio>
#include<gl/glut.h>
int iMode = 1;
GLuint lineList, lineList2;
GLint vp[4];
float xRot = 0.0, yRot = 0.0;
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
	float x[] = { 1.0-2, 3.0-2, 0, 1.0 };
	float y[] = { 1.0-2, 2.0-2, 2.0,1.0 };
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
	glEndList();
}
void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//if (w <= h) gluOrtho2D(0, 5, 0, 6.0*((GLfloat)h / w));
	//else gluOrtho2D(0, 5.0*((GLfloat)h / w), 0, 6);
	glOrtho(-5,5,-5,5,-5,5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	winWidth = w; winHeight = h;

}
void Displayt() {
	glClear(GL_COLOR_BUFFER_BIT);	//�õ�ǰ����ɫ��䴰��
	glCallList(lineList2);
	glFlush();//���OpenGL��������ִ��OpenGL����
}
void Displayw() {
	glClear(GL_COLOR_BUFFER_BIT);	//�õ�ǰ����ɫ��䴰��
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(fly);
	glLoadIdentity();
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, winWidth/2, winHeight);
	glGetIntegerv(GL_VIEWPORT, vp);

	glCallList(lineList);
	


	glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
	glGetIntegerv(GL_VIEWPORT, vp);
	glCallList(lineList2);
	glFlush();//���OpenGL��������ִ��OpenGL����
}
void ProcessMenu(int value) {
	iMode = value;
	glutPostRedisplay();
}
void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) xRot -= 5;
	if (key == GLUT_KEY_DOWN) xRot += 5;
	if (key == GLUT_KEY_LEFT) yRot -= 5;
	if (key == GLUT_KEY_RIGHT) yRot += 5;
	int k = x;
	x = (k + 360) % 360;
	k = y;
	y = (k + 360) % 360;
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);		//��GLUT����г�ʼ��
	/*glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//�趨���ڵ���ʾģʽ�������������ɫģ�͵�
	glutInitWindowSize(400, 300);		//���ô��ڴ�С400x300
	glutInitWindowPosition(100, 120);	//���ô���λ�ã�Windows�����Ͻ�Ϊ(0,0)��
	glutCreateWindow("������");			//����һ����Ϊ���εĴ���
	glutDisplayFunc(Displayt);			//���õ�ǰ���ڵĻص���������������ʾ�����ݣ�
	glutReshapeFunc(ChangeSize);
	Initial();					//��ɴ��ڳ�ʼ��*/

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(500, 120);
	glutCreateWindow("��������ӽ�");
	/*int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("face", 1);*/
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Displayw);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	Initial();
	glutMainLoop();			//������GLUT�¼�����ѭ��
	return 0;
}