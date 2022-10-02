/*
 * ������ �����ڵ� *
 * ���� : "https://juyoung-1008.tistory.com/5"
 * �ҽ��ڵ� : "https://github.com/park-ju1008/Neural-Network/tree/91343ec215ba3ec1e9c13f594bdfaf3f66eb9092"
 * ����Ϸ��� ������ �°� �����ϰ� �ڵ�� �ּ��� ����, ÷���Ͽ��� 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memory.h>
#include "AI.h"

int M[NLayer] = { m0, m1, m2 };				//�������� ��� �� ����
int trainData[N_tr_examples][N - 1] = { 0, };		//�н������͵� �޾ƿͼ� ����
int d_tr[N_tr_examples][m2] = { 0, };				//N_tr_exples��°�� �н������Ͱ� �νĵǾ���� ����(��, ������-������ �ε����� 1��)
int testData[N_te_examples][N - 1] = { 0, };		//�׽�Ʈ �����͵� �޾ƿͼ� ����
int d_te[N_te_examples][m2] = { 0, };				////N_te_exples��°�� �׽�Ʈ�����Ͱ� �νĵǾ���� ����(��, ������)

int input[N];			//�Է� N�� ������
int D[m2];				//���� �־���


double s[NLayer][MLayerSize];		//NLayer���� MLayerSize��° ����� ��(���� ���� ����Ʈ ���� ���� ���)
double f[NLayer][MLayerSize];		//s���� �ñ׳��̵� �Լ��� �����Ų ���� ��
double delta[NLayer][MLayerSize];
double W[NLayer][MLayerSize][MLayerSize];		//����Ʈ ��
double c = 0.5;		//�н���

void data_Onmemory() {
	FILE *trainfp;
	FILE *testfp;
	int i = 0, j, ans;			//ans:���Ǵ� ��°�(����)
	input_max = 0;

	trainfp = fopen("train.txt", "rt");
	testfp = fopen("test.txt", "rt");
	if (trainfp != NULL) {

		while (!feof(trainfp)) {			//���Ͽ� �ִ� �͵��� ��� �ҷ��ͼ� �����Ŵ
			fscanf(trainfp, "%d ", &ans);
			d_tr[i][ans] = 1;				//d_tr�� i��° �������� ���ڴ� ans��(�´� ���� �ε��� ���� 1�־���)
			for (j = 0; j < N - 1; j++) {
				fscanf(trainfp, "%d ", &trainData[i][j]);
				if (input_max < trainData[i][j])
					input_max = trainData[i][j];		//���� ū �Է°� ã��
				else ;
			}
			i++;
		}
		fclose(trainfp);

	}
	if (testfp != NULL) {
		while (!feof(testfp)) {
			for (i = 0; i < N_te_examples; i++) {
				fscanf(testfp, "%d", &ans);
				d_te[i][ans] = 1;
				for (j = 0; j < N - 1; j++) {
					fscanf(testfp, "%d ", &testData[i][j]);
				}

			}
		}
		fclose(testfp);
	}
}


void weight_init() {				//��� ����� weight parameter�� �ʱ�ȭ
	int i, j, k, r, pre_layer;
	srand(time(NULL));
	for (i = 0; i < NLayer; i++) {
		if (i == 0) {
			pre_layer = N;
			for (j = 0; j < M[i]; j++) {
				for (k = 0; k < pre_layer; k++) {
					r = (double)(rand());						//�ʱ⿡ rand()�Լ� ������ �������� ���� ������ ����ġ ������Ŵ(rand()�Լ��� ���α׷� �� �� �����ϸ� �ٲ���X)
					W[i][j][k] = (r / (double)RAND_MAX) - 0.5; //�Է� ���� Ŀ w�� �۰� ���� -->
				}
			}
		}
		else {
			pre_layer = M[i - 1] + 1;
			for (j = 0; j < M[i]; j++) {
				for (k = 0; k < pre_layer; k++) {
					r = (double)(rand());
					W[i][j][k] = (r / (double)RAND_MAX) - 0.5;
				}
			}
		}
	}
}

void forward_compute() {
	int i, j, layer;
	//0���� ���� s��� �� f���
	for (i = 0; i < M[0]; i++) {
		s[0][i] = 0.0;
		for (j = 0; j < N; j++) {
			//s[0][i] += (input[j] / 255.0) * W[0][i][j];		//gray scale �̹����� 0~1������ �Ǽ��� �ٲ�(�ʱ�ü �ν� MNIST �����͸� ����� ��)
			s[0][i] += (input[j] / (double)input_max) * W[0][i][j];			//0~1������ �Ǽ��� �ٲ��ֱ� ���� �Է��� �ִ밪���� ������
		}
		f[0][i] = 1.0 / (1.0 + exp(-s[0][i]));			//�ñ׸��̵� �Լ� ����		//exp(n):�����Լ�(e�� n����)
	}
	f[0][m0] = 1.0; //���� �Է�

	//��1 ���� s��� �� f���
	for (layer = 1; layer < NLayer; layer++) {
		for (i = 0; i < M[layer]; i++) {		//layer���� ��� ���� ��ŭ ����
			s[layer][i] = 0.0; //�ʱ�ȭ
			for (j = 0; j < M[layer - 1] + 1; j++) {	//layer-1���� ��� ���� ��ŭ ����
				s[layer][i] += f[layer - 1][j] * W[layer][i][j];		//layer���� i��° ��
			}
			f[layer][i] = 1.0 / (1.0 + exp(-s[layer][i])); //layer���� i��° ������ ��°�
		}
		f[layer][M[layer]] = 1.0; //���� �Է�
	}
}
void backward_compute() {
	int i, j;
	double tsum;
	int k = NLayer - 1; //��������
	for (i = 0; i < M[k]; i++) {		//���������� ��Ÿ���� ���ϱ�
		delta[k][i] = (D[i] - f[k][i])*f[k][i] * (1 - f[k][i]);			//D-f:�߻� ����		f*(1-f):�ñ׸��̵��Լ� �̺а�
	}
	for (k = NLayer - 2; k >= 0; k--) {//�߰����� ��Ÿ�� ���ϱ�
		for (i = 0; i < M[k]; i++) { //k�� ���� ��Ÿ ��
			tsum = 0.0;
			for (j = 0; j < M[k + 1]; j++) {//k+1�� ������ ��Ÿ*����ġ
				tsum += delta[k + 1][j] * W[k + 1][j][i];
			}
			delta[k][i] = f[k][i] * (1 - f[k][i])*tsum;
		}
	}
}
void weight_update() {
	int i, j, layer;

	for (i = 0; i < M[0]; i++) {// 0���� ����ġ ������Ʈ
		for (j = 0; j < N; j++) {
			W[0][i][j] += c*delta[0][i] * input[j];			//�н���, �Է°�, delta�� �ݿ��Ͽ� ����
		}
	}
	for (layer = 1; layer < NLayer; layer++) {		// layer ���� ����ġ ������Ʈ
		for (i = 0; i < M[layer]; i++) {
			for (j = 0; j < M[layer - 1] + 1; j++) {
				W[layer][i][j] += c*delta[layer][i] * f[layer - 1][j];
			}
		}
	}

}

int training() {
	int tr = 0, i, j;
	int num = 0;
	int plus_t=1;
	int epoch = N_tr_examples;
	double sum_sq_error;
	char flag = 'n';
	trainTime = 0.0;
	while (plus_t>=1) { //���� �н�Ƚ�� �̸��� ��� ���� 
		do {
			time_t startTime = time(NULL);				//���۽ð� ����

			for (i = 0; i < epoch; i++) {				//��ü �н� ������ �н� ��Ŵ
				memcpy(input, trainData[i], sizeof(trainData[i]));			//�޸� ī�� memcpy(dest,sour,size):sour�� �޸𸮿����� dest�� ������, size�� ������ ����Ʈ ����
				input[N - 1] = 1;
				memcpy(D, d_tr[i], sizeof(d_tr[i]));			//D�迭�� i��° �Է��� ���ڰ�(0~9) �־���(��õ� ��)
				forward_compute();
				backward_compute();
				weight_update();
			}
			sum_sq_error = 0.0;				//�������� �� �ʱ�ȭ

			for (i = 0; i < epoch; i++) {

				memcpy(input, trainData[i], sizeof(trainData[i]));
				input[N - 1] = 1;
				memcpy(D, d_tr[i], sizeof(d_tr[i]));
				forward_compute();
				for (j = 0; j < M[NLayer - 1]; j++)
					sum_sq_error += (D[j] - f[NLayer - 1][j])* (D[j] - f[NLayer - 1][j]);		//�� �������� ������ ����(�����ϼ��� �����Ƿ�)

			}
			//c = c*0.98;			//���� �ڵ��� �н����� ��� ���� -->���ϱ�??		but �����ڵ�����ϴ� ��Ȯ�� �������� �ּ�ó����
			tr++;		//Ʈ���̴� Ƚ��
			avg_sq_error = sum_sq_error / (epoch*M[NLayer - 1]); //������ ���
			printf("#%depoch �� ��� ������: %f \n", tr, avg_sq_error);

			time_t endTime = time(NULL);		//���� �ð�
			trainTime += difftime(endTime, startTime);		//�� �н��ð� ����
		} while (tr<tr_N+num);				//������ Ʈ���̴� Ƚ������ ���� ���� �ݺ�
		printf("��ǥ Ʈ���̴� Ƚ����ŭ �н��Ͽ����ϴ�.\n�߰��н� Ƚ���� �����ּ���(�׸��Ϸ��� 0) : ");
		scanf("%d", &plus_t);
		num += plus_t;
	}
	return tr;
}

double test() {	
	int num_correct = 0;
	for (int i = 0; i < m2; i++)
		correct[i] = 0;
	int i, index;
	double test_accurancy;
	time_t startTime = time(NULL);				//���۽ð� ����
	for (i = 0; i < N_te_examples; i++) {
		memcpy(input, testData[i], sizeof(testData[i]));
		input[N - 1] = 1;
		memcpy(D, d_te[i], sizeof(d_te[i]));
		forward_compute();
		index = correctNum();		//�νİ���� ����
		if (D[index] == 1) {		//�ν��Ѵ�� ���ڰ� index���
			num_correct++;			//���� ���� ����
			correct[index]++;		//�� ���ڸ��� ���� ���� ����
		}
	}
	time_t endTime = time(NULL);		//���� �ð�
	testTime = difftime(endTime, startTime);		//�׽�Ʈ �ð� ����

	test_accurancy = (double)num_correct / N_te_examples;		//�׽�Ʈ�� ��� ��ü��Ȯ��
	return test_accurancy;
}

int correctNum() {
	double temp = f[NLayer - 1][0];
	int ret = 0;
	for (int i = 1; i < M[NLayer - 1]; i++) {			//��³�� ����ŭ ����(10)
		if (temp < f[NLayer - 1][i]) {					//���� �� ū�� Ȯ����
			temp = f[NLayer - 1][i];
			ret = i;
		}
	}
	return ret; //���� ū ���� �迭�� index ���
}
