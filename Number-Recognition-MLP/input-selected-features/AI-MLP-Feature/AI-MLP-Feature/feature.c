#include "head.h"

//Ư¡1. ��������
void projection(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

	// ���� �ʱ�ȭ
	for (int i = 0; i < ROWS; i++) {
		count_r[i] = 0;
		count_c[i] = 0;
	}

	// �ึ�� 1�� ������ ��
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (N[sort][order][i][j] == 1)
				count_r[i] += 1;
			else ;
		}
	}

	// ������ 1�� ������ ��
	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS; i++) {
			if (N[sort][order][i][j] == 1)
				count_c[j] += 1;
			else ;
		}
	}

}

//Ư¡2. x,y�� �л갪
void distribute(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

	double sum_x = 0, mean_x, var_x = 0;
	double sum_y = 0, mean_y, var_y = 0;
	int count = 0;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (N[sort][order][i][j] > 0) {
				count++;
				sum_x += i;
				sum_y += j;
			}
		}
	}

	mean_x = sum_x / count;
	mean_y = sum_y / count;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (N[sort][order][i][j] > 0) {
				var_x += (i - mean_x)*(i - mean_x);
				var_y += (j - mean_y)*(j - mean_y);
			}
		}
	}

	//var_x /= (count - 1);
	//var_y /= (count - 1);

	dist[0] = var_x / (count - 1);
	dist[1] = var_y / (count - 1);

	//printf("x�� ��� = %8.3f\n", mean_x);
	//printf("y�� ��� = %8.3f\n", mean_y);

	//printf("x�� �л� = %8.3f\n", var_x);
	//printf("y�� �л� = %8.3f\n", var_y);

	//printf("x�� ǥ������ = %8.3f\n", sqrt(var_x));
	//printf("y�� ǥ������ = %8.3f\n", sqrt(var_y));

}

//Ư¡3. ���� Ư¡
void cross(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

	// ���� �ʱ�ȭ
	for (int i = 0; i < ROWS; i++) {
		cross_r[i] = 0;
		cross_c[i] = 0;
	}

	//�ึ�� ����Ư¡ ����
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			if (N[sort][order][i][j] != N[sort][order][i][j + 1])
				cross_r[i]++;
			else ;
		}
	}

	//������ ����Ư¡ ����
	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS - 1; i++) {
			if (N[sort][order][i][j] != N[sort][order][i + 1][j])
				cross_c[j]++;
			else;
		}
	}
}

//Ư¡4. �� Ư¡
void matrix(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

		int t[8][8];

		for(int i=0;i<DIV*DIV;i++)			//��Ư¡���� ��� �ʱ�ȭ
			mat[i]=0;

		for (int i = 0; i < ROWS; i++) {			//���t�� ���� ��� ����
			for (int j = 0; j < COLS; j++) {
				t[i][j] = N[sort][order][i][j];
			}
		}
		for (int i = 0; i < 8; i++) {				//�����ڸ� ������ ����
			t[ROWS][i] = N[sort][order][ROWS][i];
			t[i][COLS] = N[sort][order][i][COLS];
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (t[i][j] > 0) {
					if (i < 4 && j < 4)			//��2��и�
						mat[0]++;
					else if (i < 4 && j>3)		//��1��и�
						mat[1]++;
					else if (i > 3 && j < 4)	//��3��и�
						mat[2]++;
					else
						mat[3]++;				//��4��и�
				}
				else;
			}
		}
}