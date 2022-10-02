#pragma once
/*
* ���� �ν��ϴ� �� -> main
* �� ������ Ư¡���� �����ϴ� �� -> character
* �Էµ� ������ Ư¡���� �����ϴ� �� -> searcher
* ���ڵ����� �����ϴ� �� -> numbers

* ���� �ν� �����ϸ� �������� �ν��ϵ��� ��
(���� ��Ÿ���� ���� ���̹Ƿ�, �νķ��� ���̱� ����)
(����� ���ڰ� ����� �νĵǴ��� Ȯ���ؾ� �ϹǷ� �ϴ� ���ν��̶�� �߰� ��)
*/

//�ʿ��� ��ũ�� �Լ���
#define SORT 10
#define ORDER 10
#define ROWS 7
#define COLS 7
#define FEATURE 7	//Ư¡������ ��
#define PROTO 1		//������Ÿ���� ��

#define MID(x, y) (((y) - (x) + 1 ) / 2)
#define REST(x, y) (((y) - (x) + 1 ) % 2)
#define MAX(x, y) ( (x) > (y) ) ? (x) : (y)
#define MIN(x, y) ( (x) < (y) ) ? (x) : (y)

//����ȭ�� ���� �Լ���
void counting(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
int cross_r(int N[SORT][ORDER][ROWS][COLS], int sort, int order, int row);
int cross_c(int N[SORT][ORDER][ROWS][COLS], int sort, int order, int row);
void downsize(int N[SORT][ORDER][ROWS][COLS], int sort, int order);

//Ư¡���͵�
int half(int R[ROWS], int start, int end);
int noFullCol(int C[COLS], int start, int end, int r_s, int r_e);
int midFull(int D[ROWS], int start, int end, int s, int e);
int avgCom(int R[ROWS], int row_s, int row_e);
int first0(int D[SORT][ORDER][ROWS][COLS], int i, int j, int row_s, int row_e, int col_s, int col_e);

//�ʿ��� �迭��
int inData[SORT][ORDER][ROWS][COLS];	// [��������n][����n10��][��][��]
int protoData[SORT][ORDER][ROWS][COLS];			// ���� ������Ÿ�Ե�
int count_r[ROWS];		// 1�� ������ �ึ�� ���� ���
int count_c[COLS];		// 1�� ������ ������ ���� ���
int featureIn[FEATURE];	// �Էµ� ������ Ư¡������ ���� ���� �ִ� ���
int featureNum[SORT][FEATURE];	// ������Ÿ�Ե��� Ư¡������ ���� ���� �ִ� ���
int rate[SORT];			// ������Ÿ�԰��� ��ġ��

// �ʿ��� ����
int row_s, col_s;		// ���� 0�� �ƴ� ����
int row_e, col_e;		// ���� 0�� �ƴ� ��
int max;		//��ġ���� ���� ���� ����
int numRate, totalRate;			//�����ν��� ��� ��ġ�� ���ڴ�, ��ü