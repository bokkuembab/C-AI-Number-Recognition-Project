#include <stdio.h>
#include <math.h>
#include "head.h"


#define N 8

int main(void) {

	//�ڵ��� ����� ���Ϸ� �̾Ƴ���-������ �״��
	FILE *fp = NULL;
	fp = fopen("sample.txt", "w");
	if (fp == NULL) {
	printf("���� ���� ����\n");
	return 1;
	}
	for (int p = 0; p < PEOPLE; p++) {			//�ο�����ŭ ����
		for (int n = 0; n < SORT; n++) {			//����
			for (int m = p * 10; m < p * 10 + SORT; m++) {		//���ڴ� ������ 10��
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


	//�ڵ��� ����� ���Ϸ� �̾Ƴ���-Ư¡���� ��
	fp = fopen("feature.txt", "w");
	if (fp == NULL) {
		printf("���� ���� ����\n");
		return 1;
	}
	for (int p = 0; p < PEOPLE; p++) {			//�ο�����ŭ ����
		for (int n = 0; n < SORT; n++) {			//����
			for (int m = p * 10; m < p * 10 + SORT; m++) {		//���ڴ� ������ 10��
				fprintf(fp, "%d\n", n);

				projection(num, n, m);
				distribute(num, n, m);
				cross(num, n, m);
				matrix(num, n, m);

				for(int i=0;i<ROWS;i++)				//�������� r
					fprintf(fp, "%d ", count_r[i]);
				fputc('\n', fp);
				for (int i = 0; i<COLS; i++)		//�������� c
					fprintf(fp, "%d ", count_c[i]);
				fputc('\n', fp);
				for (int i = 0; i<2; i++)			//�л� x,y
					fprintf(fp, "%d ", dist[i]);
				fputc('\n', fp);
				for (int i = 0; i<ROWS; i++)		//����Ư¡ r
					fprintf(fp, "%d ", cross_r[i]);
				fputc('\n', fp);
				for (int i = 0; i<COLS; i++)		//����Ư¡ c
					fprintf(fp, "%d ", cross_c[i]);
				fputc('\n', fp);
				for (int i = 0; i<DIV*DIV; i++)		//��Ư¡
					fprintf(fp, "%d ", mat[i]);
				fputc('\n', fp);

			}
		}
	}

	fclose(fp);
	
	return 0;

}