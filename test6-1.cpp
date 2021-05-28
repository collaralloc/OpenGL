/*实验5 三维的几何变换的实现*/
/*参考p181程序6-2，使得窗口显示左右2个视区，左视区显示线框的四面体,右视区显示填充棋盘图案的四面体。*/
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
	//按x,y,z为起始位置，显示字符串str  
	static GLuint lists;
	lists = glGenLists(MAX_CHAR);
	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	glListBase(lists);
	//起始位置
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//RGBA设置窗口背景颜色为白色
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
	glLoadIdentity();  //消除以前的变换
	glEnable(GL_LINE_SMOOTH);  //使用反走样
	glEnable(GL_BLEND);  //启用混合函数
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //指定混合函数
	
	glViewport(0, 0, winWidth / 2, winHeight);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	if (iMode == 1)  //iMode的三个值为别对应正视图，侧视图和俯视图
		gluLookAt(0, 3, 0, 0, 0, 0, 0, 0, 1); else //让眼睛在y轴，头在z轴，看xOz平面，物体在原点处
		if (iMode == 2)
			gluLookAt(3, 0, 0, 0, 0, 0, 0, 0, 1); else//让眼睛在x轴，头在z轴，看yOz平面，物体在原点处
			gluLookAt(0, 0, 3, 0, 0, 0, -1, 0, 0); //让眼睛在z轴，头在x负半轴，看xOy平面，物体在原点处
	glCallList(lineList2);
	glPopMatrix();
	drawString("x axis", 5, 0, 0);

	glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_STIPPLE);  //填充的方式
	glPolygonStipple(fly);
	gluPerspective(100.0f, (GLfloat)(winWidth / 2) / (GLfloat)winHeight, 1.0f, 100.0f);
	//通过定义视角的角度范围，高宽比例以及前后界面来实现三维透视
	float dx=5, dy=5, dz=2;
	if (!f) {  //这里的f是来判断是否为绕x轴旋转，f=0则为绕x轴旋转，f=1为绕y轴旋转
		dx = dx;  //使用书上的三维矩阵变换公式来实现眼睛的坐标变换
		dy = dy * cos(xRot * pi / 180.0) - dz * sin(xRot * pi / 180.0); //注意弧度制转换
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
	glClear(GL_COLOR_BUFFER_BIT);	//用当前背景色填充窗口
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
	glFlush();//清空OpenGL缓冲区，执行OpenGL程序
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
	glutCreateWindow("四面体多视界");
	int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);
	glutAddMenuEntry("x", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Displayt);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	Initial();
	glutMainLoop();			//启动主GLUT事件处理循环
	return 0;
}