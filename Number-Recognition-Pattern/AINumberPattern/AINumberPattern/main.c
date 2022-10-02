//* 숫자 인식하는 곳 -> main

#include "help.h"
#include <stdio.h>

void main() {

	//각 숫자들의 프로토타입의 특징벡터 추출
	//열의 값
	//avgCom, half(R), half(C), noFullCol, midFull(R),midFull(C) 순서
	/*
	int avgCom(int R[ROWS], int row_s, int row_e);
	int half(int R[ROWS], int start, int end);
	int noFullCol(int C[COLS], int start, int end, int r_s, int r_e);
	int midFull(int D[ROWS], int start, int end, int s, int e);
	*/
	printf("--프로토타입의 특징벡터 배열--\n");
	for (int i = 0; i < SORT; i++) {
		counting(protoData, i, 0);
		downsize(protoData, i, 0);
		
		featureNum[i][0] = avgCom(count_r, row_s, row_e);
		featureNum[i][1] = half(count_r, row_s, row_e);
		featureNum[i][2] = half(count_c, col_s, col_e);
		featureNum[i][3] = noFullCol(count_c, col_s, col_e, row_s, row_e);
		featureNum[i][4] = midFull(count_r, row_s, row_e, col_s, col_e);
		featureNum[i][5] = midFull(count_c, col_s, col_e, row_s, row_e);
		featureNum[i][6] = first0(protoData, i, 0, row_s, row_e, col_s, col_e);

		printf("숫자 %d : (%d, %d, %d, %d, %d, %d, %d) \n", i, featureNum[i][0], featureNum[i][1], featureNum[i][2], featureNum[i][3], featureNum[i][4], featureNum[i][5], featureNum[i][6]);
		rate[i] = 0;
	}
	printf("\n");

	//전체 일치율 초기화
	totalRate = 0;

	//100개의 숫자들 입력
	for (int i = 0; i < SORT; i++) {
		for (int j = 0; j < ORDER; j++) {

			counting(inData, i, j);
			downsize(inData, i, j);
			

			featureIn[0] = avgCom(count_r, row_s, row_e);
			featureIn[1] = half(count_r, row_s, row_e);
			featureIn[2] = half(count_c, col_s, col_e);
			featureIn[3] = noFullCol(count_c, col_s, col_e, row_s, row_e);
			featureIn[4] = midFull(count_r, row_s, row_e, col_s, col_e);
			featureIn[5] = midFull(count_c, col_s, col_e, row_s, row_e);
			featureIn[6] = first0(inData, i, j, row_s, row_e, col_s, col_e);

			for (int m = 0; m < SORT; m++) {
				for (int n = 0; n < FEATURE; n++) {
					if (featureNum[m][n] == featureIn[n])
						rate[m] += 1;
				}
			}


			for (int m = 0; m < SORT; m++) {
				if (rate[m] > rate[max])
					max = m;
			}

			if (max == i)
				numRate += 1;
			else
				;

			printf("숫자 %d의 %d번째: ", i, j+1);
			printf("%d", max);

			printf("\n rate행렬: (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)", rate[0], rate[1], rate[2], rate[3], rate[4], rate[5], rate[6], rate[7], rate[8], rate[9]);

			//프로토타입과의 일치율, 일치숫자 초기화
			for (int m = 0; m < SORT; m++)
				rate[m] = 0;
			max = 0;

			printf("\n");
		}
		totalRate += numRate;
		printf("숫자 %d의 일치율 : %d\n\n", i, numRate*10);
		//숫자일치율 초기화
		numRate = 0;
	}
	printf("전체 숫자일치율 : %d \n", totalRate);
}