/*
*����2-1
*һ��������OpenGL����
*/
#include"pch.h"
#include<iostream>
#include<gl/glut.h>

using namespace std;
void Initial(){
	glClearColor(1.0f,1.0f,1.0f,1.0f);	//RGBA���ô��ڱ�����ɫΪ��ɫ
	glMatrixMode(GL_PROJECTION);		//ָ������ͶӰ����
	gluOrtho2D(0.0,200.0,0.0,150.0);	//����ͶӰ����
	/*��Ȼ�����ǻ���һ����ά���Σ�����OpenGL����ͼ�εķ�ʽ��Ȼ����ά�ġ�
	Ҳ����˵����ά����Ҫ����ά����ռ��д�����
	*/
}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);	//�õ�ǰ����ɫ��䴰��
	glColor3f(1.0f,0.0f,0.0);		//���õ�ǰ��ͼ��ɫΪ��ɫ
	glRectf(50.0f,100.0f,150.0f,50.0f);//����һ������
	glFlush();//���OpenGL��������ִ��OpenGL����
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);		//��GLUT����г�ʼ��
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	//�趨���ڵ���ʾģʽ�������������ɫģ�͵�
	glutInitWindowSize(400,300);		//���ô��ڴ�С400x300
	glutInitWindowPosition(100,120);	//���ô���λ�ã�Windows�����Ͻ�Ϊ(0,0)��
	glutCreateWindow("����");			//����һ����Ϊ���εĴ���
	glutDisplayFunc(Display);			//���õ�ǰ���ڵĻص���������������ʾ�����ݣ�
	Initial();					//��ɴ��ڳ�ʼ��
	glutMainLoop();			//������GLUT�¼�����ѭ��
	return 0;
}