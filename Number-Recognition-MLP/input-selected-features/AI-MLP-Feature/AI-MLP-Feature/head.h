#pragma once

#define SORT 10			//���� 0~9
#define ORDER 160		//���ڰ� ���� �ִ� ������Ÿ���� ����(10����*16��)
#define ROWS 7			//��
#define COLS 7			//��
#define PEOPLE 16		//��� ��
#define FEAT 16			//Ư¡���� ��� ��(��������14 + �л�2)
#define DIV 2			//�� Ư¡ ���� �� ��,���� DIV�� ����(�� ��ü�� DIV*DIV���� ������ ����)


int count_r[ROWS];		// 1�� ������ �ึ�� ���� ���
int count_c[COLS];		// 1�� ������ ������ ���� ���
int dist[2];			//x,y�� �л갪	�ε��� 0:x�� �л� 1:y�� �л�
int cross_r[ROWS];		//���� 0,1��� Ƚ��
int cross_c[COLS];		//���� 0,1��� Ƚ��
int mat[DIV*DIV];				//�� ������ 1�� ����


//Ư¡1. ��������
void projection(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
//Ư¡2. x,y�� �л갪
void distribute(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
//Ư¡3. ���� Ư¡
void cross(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
//Ư¡4. �� Ư¡
void matrix(int N[SORT][ORDER][ROWS][COLS], int sort, int order);

int protoData[SORT][ORDER][ROWS][COLS];		//16_1
int num[SORT][ORDER][ROWS][COLS];			//16_2