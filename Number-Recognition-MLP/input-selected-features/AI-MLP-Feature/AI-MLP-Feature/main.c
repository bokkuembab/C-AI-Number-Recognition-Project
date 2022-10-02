#include <stdio.h>
#include <math.h>
#include "head.h"


#define N 8

int main(void) {

	//코딩의 행렬을 파일로 뽑아내기-데이터 그대로
	FILE *fp = NULL;
	fp = fopen("sample.txt", "w");
	if (fp == NULL) {
	printf("파일 열기 실패\n");
	return 1;
	}
	for (int p = 0; p < PEOPLE; p++) {			//인원수만큼 돌림
		for (int n = 0; n < SORT; n++) {			//숫자
			for (int m = p * 10; m < p * 10 + SORT; m++) {		//숫자당 데이터 10개
				fprintf(fp, "%d\n", n);
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						fprintf(fp, "%d ", num[n][m][i][j]);
					}
					fputc('\n', fp);
				}
			}
		}
	}

	fclose(fp);
	//return 0;


	//코딩의 행렬을 파일로 뽑아내기-특징추출 후
	fp = fopen("feature.txt", "w");
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		return 1;
	}
	for (int p = 0; p < PEOPLE; p++) {			//인원수만큼 돌림
		for (int n = 0; n < SORT; n++) {			//숫자
			for (int m = p * 10; m < p * 10 + SORT; m++) {		//숫자당 데이터 10개
				fprintf(fp, "%d\n", n);

				projection(num, n, m);
				distribute(num, n, m);
				cross(num, n, m);
				matrix(num, n, m);

				for(int i=0;i<ROWS;i++)				//프로젝션 r
					fprintf(fp, "%d ", count_r[i]);
				fputc('\n', fp);
				for (int i = 0; i<COLS; i++)		//프로젝션 c
					fprintf(fp, "%d ", count_c[i]);
				fputc('\n', fp);
				for (int i = 0; i<2; i++)			//분산 x,y
					fprintf(fp, "%d ", dist[i]);
				fputc('\n', fp);
				for (int i = 0; i<ROWS; i++)		//교차특징 r
					fprintf(fp, "%d ", cross_r[i]);
				fputc('\n', fp);
				for (int i = 0; i<COLS; i++)		//교차특징 c
					fprintf(fp, "%d ", cross_c[i]);
				fputc('\n', fp);
				for (int i = 0; i<DIV*DIV; i++)		//망특징
					fprintf(fp, "%d ", mat[i]);
				fputc('\n', fp);

			}
		}
	}

	fclose(fp);
	
	return 0;

}