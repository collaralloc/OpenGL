/*实验一 橡皮筋技术实现*/
#include"pch.h"
#include<gl/glut.h>
#include<cstdio>
struct Brockenline {
	GLint x, y;
	Brockenline* next;
	Brockenline(GLint x, GLint y) :x(x), y(y) { next = NULL; }
}* head=NULL,* tail=NULL;
static GLsizei iMode = 1;
int iPointNum = 0;
int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
int winWidth = 400, winHeight = 300;
void Initial(void) {
	glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void ChangeSize(int w, int h) {
	winWidth = w; winHeight = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	if (iPointNum>=1) {
		switch (iMode)
		{
		case 1:
			glBegin(GL_LINES);
			glVertex2i(x1,y1);
			glVertex2i(x2,y2);
			glEnd();
			break;
		case 2:
			glRecti(x1, y1, x2, y2);
			break;
		case 3:
			Brockenline *pa,*temp;
			pa = head;
			while (pa!=NULL && pa->next != NULL) {
				temp = pa->next;
				glBegin(GL_LINES);
				glVertex2i(pa->x, pa->y);
				glVertex2i(temp->x, temp->y);
				glEnd();
				pa = temp;
				
			}
			break;
		default:
			break;
		}
		
	}
	glutSwapBuffers();
}
void Clearline() {
	while (head != NULL) {
		Brockenline * temp = head->next;
		delete head;
		head = temp;
	}
}
void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		//puts("leftkey click");
		//printf("ipoint=%d\n",iPointNum);
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			x1 = xMouse; y1 = winHeight-yMouse;
			if (iMode == 3) {
				iPointNum = 5;
				if (head != NULL)Clearline();
				Brockenline *temp = new Brockenline(x1,y1);
				head = temp;
				tail = head;
			}
		}
		else {
			
			x2 = xMouse; y2 = winHeight - yMouse;
			if (iMode == 3) {
				//iPointNum = 5;
				Brockenline *temp = new Brockenline(x2,y2);
				tail->next = temp;
				tail = temp;
			}
			else {
				iPointNum = 2;
				glutPostRedisplay();
			}
			
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
			if (iMode == 3) {
				iPointNum = 5;
				if (head != NULL)Clearline();
				Brockenline *temp = new Brockenline(x1, y1);
				head = temp;
				tail = head;
			}
		}
		else {
			x2 = x; y2 = winHeight - y;
			if (iMode == 3) {
				
				Brockenline *temp = new Brockenline(x2, y2);
				tail->next = temp;
				tail = temp;
			}
			else {
				iPointNum = 2;
				glutPostRedisplay();
			}
		}
		break;
	case 'c':
		//printf("c %d %d",iMode,iPointNum);
		if (iMode != 3||iPointNum==0) {
			Clearline();
			//若是折线，第一次按'c'停止，第二次清除；
			glutPostRedisplay();
		}
		iPointNum = 0;
		
		
		break;
	default:
		break;
	}
}

void PassiveMouseMove(GLint xMouse, GLint yMouse) {
	if (iPointNum == 1 || iPointNum==5) {
		x2 = xMouse; y2 = winHeight - yMouse;
		
		//printf("ipoint=%d x2=%d y2=%d\n", iPointNum, x2, y2);
		if (iPointNum == 5) {
			Brockenline *temp = new Brockenline(x2, y2);
			delete tail->next;
			tail->next = temp;
			
		}
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
	glutCreateWindow("橡皮筋技术");			//创建一个名为矩形的窗口
	int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Straight line", 1);
	glutAddMenuEntry("Rectangle", 2);
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