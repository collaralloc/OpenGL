/*实验二 椭圆的中点Bresenham算法*/

#include"pch.h"
#include"GL/glut.h"
static GLsizei iMode = 1;
int iPointNum = 0;
int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
int winWidth = 400, winHeight = 300;
int addw = 200, addh = 150;
void Initial(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void ChangeSize(int w, int h) {
	winWidth = w; winHeight = h;
	addw = winWidth >> 1; addh=winHeight>>1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}
inline void putpixel(int x,int y){
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glVertex2d(-x, y);
	glVertex2d(x, -y);
	glVertex2d(-x, -y);
	glEnd();
}
void MidBresehamEllipse(int a, int b) {
	int x, y;
	double d1, d2;
	x = 0; y = b;
	d1 = b * b + a * a*(-b + 0.25);
	putpixel(x, y);
	while (b*b*(x+1)<a*a*(y-0.5)) {
		if (d1 <= 0) {
			d1 += b * b*(2 * x + 3);
			x++;
		}
		else {
			d1 += b * b*(2 * x + 3) + a * a*(-2 * y + 2);
			x++; y--;
		}
		putpixel(x,y);
	}
	d2 = b * b*(x + 0.5)*(x + 0.5) + a * a*(y - 1)*(y - 1) - a * a*b*b;
	while (y > 0) {
		if (d2 <= 0) {
			d2 += b * b*(2 * x + 2) + a * a*(-2 * y + 3);
			x++; y--;
		}
		else {
			d2 += a * a*(-2 * y + 3);
			y--;
		}
		putpixel(x,y);
	}
}
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	if (iPointNum >= 1) {
		x1 += addw; x2 += addw;
		y1 += addh; y2 += addh;
		switch (iMode)
		{
		case 1:
			glBegin(GL_LINES);
			glVertex2i(x1, y1);
			glVertex2i(x2, y2);
			glEnd();
			break;
		case 2:
			MidBresehamEllipse(x1,y1);
			break;
		default:
			break;
		}

	}
	glutSwapBuffers();
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		//puts("leftkey click");
		//printf("ipoint=%d\n",iPointNum);
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			x1 = xMouse; y1 = winHeight - yMouse;
			
		}
		else {

			x2 = xMouse; y2 = winHeight - yMouse;
				iPointNum = 2;
				glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		iPointNum = 0;
		glutPostRedisplay();
	}
	//printf("ipoint=%d x=%d y=%d\n",iPointNum,x1,y1);
}

void Key(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'p':
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			x1 = x; y1 = winHeight - y;
		}
		else {
			x2 = x; y2 = winHeight - y;
			
			iPointNum = 2;
			glutPostRedisplay();
			
		}
		break;
	case 'c':
		iPointNum = 0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void PassiveMouseMove(GLint xMouse, GLint yMouse) {
	if (iPointNum == 1 || iPointNum == 5) {
		x2 = xMouse; y2 = winHeight - yMouse;
		glutPostRedisplay();
	}

}
void ProcessMenu(int value) {
	iMode = value;
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);		//对GLUT库进行初始化
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//设定窗口的显示模式，包括缓存和颜色模型等
	glutInitWindowSize(400, 300);		//设置窗口大小400x300
	glutInitWindowPosition(100, 120);	//设置窗口位置（Windows下右上角为(0,0)）
	glutCreateWindow("椭圆的中点Bresenham算法");			//创建一个名为矩形的窗口
	int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("mid ellipse", 1);
	glutAddMenuEntry("ellipse", 2);
	glutAddMenuEntry("Broken line", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Display);			//设置当前窗口的回调函数（即窗口显示的内容）
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);	//鼠标响应
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouseMove);
	Initial();					//完成窗口初始化
	glutMainLoop();			//启动主GLUT事件处理循环
	return 0;
}