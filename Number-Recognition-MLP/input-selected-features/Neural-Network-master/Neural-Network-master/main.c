/*
 * ������ �����ڵ� *
 * ���� : "https://juyoung-1008.tistory.com/5"
 * �ҽ��ڵ� : "https://github.com/park-ju1008/Neural-Network/tree/91343ec215ba3ec1e9c13f594bdfaf3f66eb9092"
 * ����Ϸ��� ������ �°� �����ϰ� �ڵ�� �ּ��� ����, ÷���Ͽ��� 
 */

#include "AI.h"
#include <stdio.h>
#include <time.h>
extern double c;

int main() {
	double sum_sq_error = 0.0; //�������� ��
	avg_sq_error = 0.0;			//������ ���
	double test_accurancy;
	int tr;

	printf("							     ����\n");
	printf("####################################################################\n\n");
	printf("������ ��� �� : ");
	for (int i = 0; i < NLayer; i++) {
		printf("%d ", M[i]);
	}
	printf("\n1epoch=%d\n", N_tr_examples);
	printf("train_threshold : %f\n", train_threshold);
	printf("�н��� c��: %f\n", c);
	printf("---------------------------------------\n");
	printf("Ʈ���̴� ������ �� �׽�Ʈ ������ �о���� ��...\n");
	data_Onmemory();
	printf("���� ����ġ ���� ��...\n ");
	weight_init();				//�ѹ� �����ϸ� visual ������� �ٲ��� ����(rand�Լ� ��������Ƿ�)
	printf("Ʈ���̴� ����\n");
	tr = training();
	printf("\n------------------------------------------\n");
	printf("�׽�Ʈ ����\n");
	test_accurancy = test();
	printf("-------------------������-----------------------\n");
	if (N - 1 == 49)
		printf("<7*7 ������ �״�� �Է��Ͽ� �н�>\n");
	else
		printf("<Ư¡ ���� �� �н�>\n");

	printf("������ ����� ����: ");
	printf("%d ", N - 1);
	for (int i = 0; i < NLayer; i++) {
		printf("%d ", M[i]);
	} 
	printf("\n�н��� : %f\n", c);
	printf("�н� Ƚ��(�ݺ��� ���� ��) : %d\n", tr);
	printf("�н� �������� �� (1epoch) : %d\n", N_tr_examples);
	printf("�׽�Ʈ �������� �� : %d\n", N_te_examples);

	printf("-------------------�����-----------------------\n");
	printf("������ ��տ����� : %lf\n", avg_sq_error);
	printf("�� �н��ð� : %.1f sec\n", trainTime);
	//printf("�׽�Ʈ�ð� : %lf sec\n", testTime);
	printf("��ü ���� �ν� ��Ȯ�� : %f\% \n", test_accurancy * 100);
	printf("---------------���ں� �ν���Ȯ��----------------\n");
	for (int i = 0; i<m2; i++)
		printf("���� %d : %f\% \n", i, (double)correct[i] / N_te_examples * 10 * 100.0);

	return 0;
}
