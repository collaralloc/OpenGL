/*ʵ��� ��Բ���е�Bresenham�㷨*/

#include"pch.h"
#include"GL/glut.h"
#include<cstdio>

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
	addw = winWidth >> 1; addh = winHeight >> 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}
inline void putpixel(int x, int y) {
	glColor3f(0,1.0,0);
	glLineWidth(4);
	glBegin(GL_POINTS);
	glVertex2d(x + addw, y + addh);
	glEnd();
}
void MidBresenhamline(int x0,int y0,int x1,int y1){
	int dx,dy,d,UpIncre,DownIncre,x,y;
	if (x0>x1){
		x=x1; x1=x0; x0=x;
		y=y1; y1=y0; y0=y;
	}
	x=x0; y=y0;
	dx=x1-x0;	dy=y1-y0; d=dx-2*dy;
	UpIncre=2*dx-2*dy; DownIncre=-2*dy;
	while (x<=x1){
		putpixel(x,y);
		x++;
		if (d<0)y++,d+=UpIncre;
		else d+=DownIncre;
	}
}
int LBLineClipTest(float p,float q,float &umax,float &umin) {
	float r = 0.0;
	if (p < 0.0) {
		r = q / p;
		if (r > umin) return 0;   // umaxС��uminֱ�߶β����ڴ����ڵĲ���
		else if (r > umax) umax = r;
	}
	else if (p > 0.0) {
		r = q / p;
		if (r < umax) return 0;   // umaxС��uminֱ�߶β����ڴ����ڵĲ���
		else if (r < umin) umin = r;
	}
	else if (q < 0.0) return 0;
	
	return 1;
}
void LBLineClip(float xwl,float xwr,float ywb,float ywt,float x1,float y1,float x2,float y2) {
	float umax,umin,deltax,deltay;
	deltax=x2-x1; deltay=y2-y1; umax=0.0; umin=1.0;
	//printf("%.1f  %.1f %.1f %.1f\n", x1, y1, x2, y2);
	if (LBLineClipTest(-deltax, x1 - xwl, umax, umin)) { //������߽罻��
		if (LBLineClipTest(deltax, xwr - x1, umax, umin)) { //�����ұ߽罻��
			if (LBLineClipTest(-deltay, y1 - ywb, umax, umin)) { //�����±߽罻��
				if (LBLineClipTest(deltay, ywt - y1, umax, umin)) { //�����ϱ߽罻��
					x1=int(x1+umax*deltax+0.5);
					y1=int(y1+umax*deltay+0.5);
					x1=int(x2+umin*deltax+0.5);
					y1=int(y2+umin*deltay+0.5);
					MidBresenhamline((int)x1, (int)y1, (int)x2, (int)y2);
					glutPostRedisplay();
					printf("ddddddd%.1f  %.1f %.1f %.1f\n", x1, y1, x2, y2);
					//std::cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
					//system("pause");
				}
				
			}
		}
	}
	int a[] = { xwl,xwl,xwr,xwr,xwl };
	int b[] = { ywb,ywt,ywt,ywb,ywb };
	for (int i = 0; i < 4; i++) {
		glBegin(GL_LINES);
		glVertex2i(a[i], b[i]);
		glVertex2i(a[i+1], b[i+1]);
		glEnd();
	}
	/*glBegin(GL_LINES);
	glColor3f(0,1,0);
	glVertex2i(addw,ywt);
	glVertex2i(addw,ywb);
	glEnd();
	glColor3f(1,0,0);*/
	
}
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	if (iPointNum >= 1) {
		//x1 += addw; x2 += addw;
		//y1 += addh; y2 += addh;
		switch (iMode)
		{
		case 1:
			LBLineClip(x1,x2,y1,y2,0,addh,winWidth,addh);
			break;
		case 2:	
			LBLineClip(x1, x2, y1, y2, addw, 0, addw, winHeight);
			break;
		case 3:
			LBLineClip(x1, x2, y1, y2, 0, 0, winWidth, winHeight);
			break;
		default:
			break;
		}
		
	}
	if (iPointNum<2) {
		switch (iMode) {
			case 1:
				glBegin(GL_LINES);
				glVertex2i(0, addh);
				glVertex2i(winWidth, addh);
				glEnd();
				break;
			case 2:
				glBegin(GL_LINES);
				glVertex2i(addw, 0);
				glVertex2i(addw, winHeight);
				glEnd();
				break;
			case 3:
				glBegin(GL_LINES);
				glVertex2i(0, 0);
				glVertex2i(winWidth, winHeight);
				glEnd();
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
	if (iPointNum == 1) {
		x2 = xMouse; y2 = winHeight - yMouse;
		glutPostRedisplay();

	}

}
void ProcessMenu(int value) {
	iMode = value;
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);		//��GLUT����г�ʼ��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//�趨���ڵ���ʾģʽ�������������ɫģ�͵�
	glutInitWindowSize(400, 300);		//���ô��ڴ�С400x300
	glutInitWindowPosition(100, 120);	//���ô���λ�ã�Windows�����Ͻ�Ϊ(0,0)��
	glutCreateWindow("liang");			//����һ����Ϊ���εĴ���
	int nGlutLineMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("- line", 1);
	glutAddMenuEntry("| line", 2);
	glutAddMenuEntry("/ line", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Display);			//���õ�ǰ���ڵĻص���������������ʾ�����ݣ�
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);	//�����Ӧ
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouseMove);
	Initial();					//��ɴ��ڳ�ʼ��
	glutMainLoop();			//������GLUT�¼�����ѭ��
	return 0;
}