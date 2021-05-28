/*实验四 多边形的图案填充的实现*/
/*改造p147程序5-12，设计菜单，菜单项是线框和填充，菜单项值分别为1、2，实现填充的、线框的正交观察四面体。*/
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
	glClearColor(1.0f,1.0f,1.0f,1.0f);	//RGBA设置窗口背景颜色为白色
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
	glClear(GL_COLOR_BUFFER_BIT);	//用当前背景色填充窗口
	glClear(GL_COLOR_BUFFER_BIT);	//用当前背景色填充窗口
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(fly);
	glLoadIdentity();
	
	glCallList(lineList);
	//glCallList(lineList3);
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();//清空OpenGL缓冲区，执行OpenGL程序
}
void Displayw() {
	glClear(GL_COLOR_BUFFER_BIT);	//用当前背景色填充窗口
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (iMode==1)glCallList(lineList);
	else glCallList(lineList2);
	glFlush();//清空OpenGL缓冲区，执行OpenGL程序
}
void ProcessMenu(int value) {
	iMode = value;
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);		//对GLUT库进行初始化
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	//设定窗口的显示模式，包括缓存和颜色模型等
	glutInitWindowSize(400,300);		//设置窗口大小400x300
	glutInitWindowPosition(100,120);	//设置窗口位置（Windows下右上角为(0,0)）
	glutCreateWindow("四面体");			//创建一个名为矩形的窗口
	glutDisplayFunc(Displayt);			//设置当前窗口的回调函数（即窗口显示的内容）
	glutReshapeFunc(ChangeSize);
	Initial();					//完成窗口初始化

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(500, 120);
	glutCreateWindow("四面体2");
	int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("face", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Displayw);
	glutReshapeFunc(ChangeSize);
	Initial();
	glutMainLoop();			//启动主GLUT事件处理循环
	return 0;
}