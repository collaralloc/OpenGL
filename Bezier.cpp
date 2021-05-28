#include "pch.h"
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h> 
#include <cstring>
#include <cstdio>
int iPointNum = 5;
float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
int winWidth = 400, winHeight = 300;
int id[4] = { 0,3,1,2};//顺序数组改变控制点顺序
GLfloat ControlP[4][3] = { {-80.0,-40.0,0.0},{-10.0,90.0,0.0},{10.0,-90.0,0.0},{80.0,40.0,0.0} };
void initial() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glLineWidth(4.0);
}
void  Display() {
	glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);
	glEnable(GL_MAP1_VERTEX_3);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMapGrid1f(100,0.0,1.0);
	glEvalMesh1(GL_LINE,0,100);
	glFlush();
}
void Reshape(GLint newWidth, GLint newHeight) {
	winWidth = newWidth; winHeight = newHeight;
	glViewport(0,0,newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-winWidth/2,winWidth/2,-winHeight/2,winHeight/2);
}
void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		
		x1 = xMouse; y1 = winHeight - yMouse;
		x1 -= winWidth / 2; y1 -= winHeight / 2;
		//x1 /= 2.0; y1 /= 2.0;
		if (iPointNum >=4) {
			iPointNum = 0;//第一次单击时清空曲线控制数组
			memset(ControlP,0,sizeof(ControlP));
			ControlP[3][0] = x1; ControlP[3][1] = y1;
			ControlP[2][0] = x1; ControlP[2][1] = y1;
			ControlP[1][0] = x1; ControlP[1][1] = y1;
		}
		int t = id[iPointNum];
		ControlP[t][0] = x1; ControlP[t][1] = y1;
		printf("%d=%.1f %.1f\n",iPointNum,x1,y1);
		iPointNum++;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++)
				printf("%.1f ",ControlP[i][j]);
			printf("-------\n");
		}
		glutPostRedisplay();
	}
	
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		memset(ControlP, 0, sizeof(ControlP));
		iPointNum = 5;
		glutPostRedisplay();
	}
}
void PassiveMouseMove(GLint xMouse, GLint yMouse) {
	if (iPointNum < 4) {
		x1 = xMouse; y1 = winHeight - yMouse;
		x1 -= winWidth / 2; y1 -= winHeight / 2;
		//修改控制点坐标
		printf("%d=%.1f %.1f\n", iPointNum, x1, y1);
		int t = id[iPointNum];//得到自已应该控制的点
		ControlP[t][0] = x1; ControlP[t][1] = y1;
		glutPostRedisplay();
	}

}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Bezier 曲线");
	initial();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MousePlot);
	glutPassiveMotionFunc(PassiveMouseMove);
	glutMainLoop();
	return 0;
}