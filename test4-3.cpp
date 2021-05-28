/*ʵ���� ����ε�ͼ������ʵ��*/
/*����p147����5-12����Ʋ˵����˵������߿����䣬�˵���ֵ�ֱ�Ϊ1��2��ʵ�����ġ��߿�������۲������塣*/
#include"pch.h"
#include<cstdio>
#include<gl/glut.h>
int iMode = 1;
int addw = 200, addh = 150;
GLuint lineList,lineList2,lineList3;
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
inline void putpixel(int x, int y) {
	/*glBegin(GL_POINTS);
	glVertex2d(x + addw, y + addh); glVertex2d(-x + addw, y + addh);
	glVertex2d(x + addw, -y + addh); glVertex2d(-x + addw, -y + addh);
	glEnd();*/
	//glRectf(x + addw, y + addh, -x + addw, -y + addh);
	
	glVertex3f(x+addw, y+addh, 0.0);
	
}
void MidBresehamEllipse(int a, int b) {
	int x, y;
	double d1, d2;
	lineList3 = glGenLists(3);
	glNewList(lineList3,GL_COMPILE);
	glBegin(GL_TRIANGLES);
	x = 0; y = b;
	d1 = b * b + a * a*(-b + 0.25);
	putpixel(x, y);
	while (b*b*(x + 1) < a*a*(y - 0.5)) {
		if (d1 <= 0) { d1 += b * b*(2 * x + 3); x++; }
		else { d1 += b * b*(2 * x + 3) + a * a*(-2 * y + 2); x++; y--; }
		putpixel(x, y);
	}
	d2 = b * b*(x + 0.5)*(x + 0.5) + a * a*(y - 1)*(y - 1) - a * a*b*b;
	while (y > 0) {
		if (d2 <= 0) { d2 += b * b*(2 * x + 2) + a * a*(-2 * y + 3); x++; y--; }
		else { d2 += a * a*(-2 * y + 3); y--; }
		putpixel(x, y);
	}
	glEnd();
	glEndList();
}
void Initial(){
	float x[] = {1.0, 3.0, 2.0, 3.0};
	float y[] = {1.0, 2.0, 4.0,3.0 };
	float z[] = {0, 0, 0, 1};
	float cx[] = { 1, 0.0, 1.0, 0.0 };
	float cy[] = { 1, 1.0, 0.0,1.0 };
	float cz[] = { 0, 0, 0, 1 };
	glClearColor(1.0f,1.0f,1.0f,1.0f);	//RGBA���ô��ڱ�����ɫΪ��ɫ
	glLineWidth(12.0);
	//MidBresehamEllipse(abs(50 - addw), abs(50 - addh));
	lineList = glGenLists(1);
	glNewList(lineList,GL_COMPILE);
	for (int i = 0; i < 4; i++) {
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 3; j++)
			glVertex3f(x[(i+j)%4],y[(i+j)%4],z[(i+j)%4]);
		glEnd();
		glColor3f(cx[i], cy[i], cz[i]);
	}
	glEndList();
	lineList2 = glGenLists(2);
	glNewList(lineList2,GL_COMPILE);
	glBegin(GL_LINE_LOOP);
	glColor4f(0.0, 0.5, 1.0, 1.0);
	glVertex3f(x[0], y[0], z[0]);
	for (int j = 1; j < 3; j++) {
		glVertex3f(x[j],y[j],z[j]);
		glColor3f(cx[j],cy[j], cz[j]);
	}
	glEnd();
	glBegin(GL_LINES);
	glColor4f(0.0, 0.5, 1.0, 1.0);
	for (int j = 0; j < 3; j++) {
		glVertex3f(x[3], y[3], z[3]);
		glVertex3f(x[j], y[j], z[j]);
		glColor3f(cx[j],cy[j],cz[j]);
	}	
	glEnd();
	glEndList();
}
void ChangeSize(GLsizei w,GLsizei h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) gluOrtho2D(0, 5, 0, 6.0*((GLfloat)h / w));
	else gluOrtho2D(0, 5.0*((GLfloat)h / w), 0, 6);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Displayt() {
	glClear(GL_COLOR_BUFFER_BIT);	//�õ�ǰ����ɫ��䴰��
	glClear(GL_COLOR_BUFFER_BIT);	//�õ�ǰ����ɫ��䴰��
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(fly);
	glLoadIdentity();
	
	glCallList(lineList);
	//glCallList(lineList3);
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();//���OpenGL��������ִ��OpenGL����
}
void Displayw() {
	glClear(GL_COLOR_BUFFER_BIT);	//�õ�ǰ����ɫ��䴰��
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (iMode==1)glCallList(lineList);
	else glCallList(lineList2);
	glFlush();//���OpenGL��������ִ��OpenGL����
}
void ProcessMenu(int value) {
	iMode = value;
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);		//��GLUT����г�ʼ��
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	//�趨���ڵ���ʾģʽ�������������ɫģ�͵�
	glutInitWindowSize(400,300);		//���ô��ڴ�С400x300
	glutInitWindowPosition(100,120);	//���ô���λ�ã�Windows�����Ͻ�Ϊ(0,0)��
	glutCreateWindow("������");			//����һ����Ϊ���εĴ���
	glutDisplayFunc(Displayt);			//���õ�ǰ���ڵĻص���������������ʾ�����ݣ�
	glutReshapeFunc(ChangeSize);
	Initial();					//��ɴ��ڳ�ʼ��

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(500, 120);
	glutCreateWindow("������2");
	int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("face", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Displayw);
	glutReshapeFunc(ChangeSize);
	Initial();
	glutMainLoop();			//������GLUT�¼�����ѭ��
	return 0;
}