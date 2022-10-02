#include "head.h"

//특징1. 프로젝션
void projection(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

	// 개수 초기화
	for (int i = 0; i < ROWS; i++) {
		count_r[i] = 0;
		count_c[i] = 0;
	}

	// 행마다 1의 개수를 셈
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (N[sort][order][i][j] == 1)
				count_r[i] += 1;
			else ;
		}
	}

	// 열마다 1의 개수를 셈
	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS; i++) {
			if (N[sort][order][i][j] == 1)
				count_c[j] += 1;
			else ;
		}
	}

}

//특징2. x,y의 분산값
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

	//printf("x축 평균 = %8.3f\n", mean_x);
	//printf("y축 평균 = %8.3f\n", mean_y);

	//printf("x축 분산 = %8.3f\n", var_x);
	//printf("y축 분산 = %8.3f\n", var_y);

	//printf("x축 표준편차 = %8.3f\n", sqrt(var_x));
	//printf("y축 표준편차 = %8.3f\n", sqrt(var_y));

}

//특징3. 교차 특징
void cross(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

	// 개수 초기화
	for (int i = 0; i < ROWS; i++) {
		cross_r[i] = 0;
		cross_c[i] = 0;
	}

	//행마다 교차특징 구함
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			if (N[sort][order][i][j] != N[sort][order][i][j + 1])
				cross_r[i]++;
			else ;
		}
	}

	//열마다 교차특징 구함
	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS - 1; i++) {
			if (N[sort][order][i][j] != N[sort][order][i + 1][j])
				cross_c[j]++;
			else;
		}
	}
}

//특징4. 망 특징
void matrix(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

		int t[8][8];

		for(int i=0;i<DIV*DIV;i++)			//망특징저장 행렬 초기화
			mat[i]=0;

		for (int i = 0; i < ROWS; i++) {			//행렬t에 원래 행렬 복사
			for (int j = 0; j < COLS; j++) {
				t[i][j] = N[sort][order][i][j];
			}
		}
		for (int i = 0; i < 8; i++) {				//가장자리 값으로 복제
			t[ROWS][i] = N[sort][order][ROWS][i];
			t[i][COLS] = N[sort][order][i][COLS];
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (t[i][j] > 0) {
					if (i < 4 && j < 4)			//제2사분면
						mat[0]++;
					else if (i < 4 && j>3)		//제1사분면
						mat[1]++;
					else if (i > 3 && j < 4)	//제3사분면
						mat[2]++;
					else
						mat[3]++;				//제4사분면
				}
				else;
			}
		}
}