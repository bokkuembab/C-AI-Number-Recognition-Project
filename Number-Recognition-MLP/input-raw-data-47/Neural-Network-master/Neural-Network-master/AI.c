#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memory.h>
#include "AI.h"

int M[NLayer] = { m0, m1, m2 };
int trainData[N_tr_examples][N - 1] = { 0, };
int d_tr[N_tr_examples][m2] = { 0, };
int testData[N_te_examples][N - 1] = { 0, };
int d_te[N_te_examples][m2] = { 0, };

int input[N];
int D[m2];		


double s[NLayer][MLayerSize];		//NLayer층의 MLayerSize번째 노드의 값(들어온 값에 웨이트 값을 곱한 결과)
double f[NLayer][MLayerSize];		//s값을 시그노이드 함수에 통과시킨 후의 값
double delta[NLayer][MLayerSize];
double W[NLayer][MLayerSize][MLayerSize];		//웨이트 값
double c = 0.05;		//학습률

void data_Onmemory() {
	FILE *trainfp;
	FILE *testfp;
	int i = 0, j, ans;			//ans:기대되는 출력값(숫자)

	trainfp = fopen("train.txt", "rt");
	testfp = fopen("test.txt", "rt");
	if (trainfp != NULL) {

		while (!feof(trainfp)) {
			fscanf(trainfp, "%d ", &ans);
			d_tr[i][ans] = 1;
			for (j = 0; j < N - 1; j++) {
				fscanf(trainfp, "%d ", &trainData[i][j]);
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


void weight_init() {				//모든 노드의 weight parameter들 초기화
	int i, j, k, r, pre_layer;
	srand(time(NULL));
	for (i = 0; i < NLayer; i++) {
		if (i == 0) {
			pre_layer = N;
			for (j = 0; j < M[i]; j++) {
				for (k = 0; k < pre_layer; k++) {
					r = (double)(rand());
					W[i][j][k] = (r / (double)RAND_MAX) - 0.5; //입력 값이 커 w값 작게 설정 -->왜??
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
	//0층에 대한 s계산 및 f계산
	for (i = 0; i < M[0]; i++) {
		s[0][i] = 0.0;
		for (j = 0; j < N; j++) {
			//s[0][i] += (input[j] / 255.0) * W[0][i][j];		//gray scale 이미지를 0~1사이의 실수로 바꿈
			s[0][i] += input[j] * W[0][i][j];			//우리는 0/1의 값을 가지므로 그대로 사용함
		}
		f[0][i] = 1.0 / (1.0 + exp(-s[0][i]));			//시그모이드 함수 적용		//exp(n):지수함수(e의 n제곱)
	}
	f[0][m0] = 1.0; //더미 입력

	//층1 부터 s계산 및 f계산
	for (layer = 1; layer < NLayer; layer++) {
		for (i = 0; i < M[layer]; i++) {		//layer층의 노드 개수 만큼 돌림
			s[layer][i] = 0.0; //초기화
			for (j = 0; j < M[layer - 1] + 1; j++) {	//layer-1층의 노드 개수 만큼 돌림
				s[layer][i] += f[layer - 1][j] * W[layer][i][j];		//layer층의 i번째 값
			}
			f[layer][i] = 1.0 / (1.0 + exp(-s[layer][i])); //layer층의 i번째 뉴런의 출력값
		}
		f[layer][M[layer]] = 1.0; //더미 입력
	}
}
void backward_compute() {
	int i, j;
	double tsum;
	int k = NLayer - 1; //마지막층
	for (i = 0; i < M[k]; i++) {		//마지막층의 델타값들 구하기
		delta[k][i] = (D[i] - f[k][i])*f[k][i] * (1 - f[k][i]);			//D-f:발생 에러		f*(1-f):시그모이드함수 미분값
	}
	for (k = NLayer - 2; k >= 0; k--) {//중간층의 델타값 구하기
		for (i = 0; i < M[k]; i++) { //k의 층의 델타 값
			tsum = 0.0;
			for (j = 0; j < M[k + 1]; j++) {//k+1층 에서의 델타*가중치
				tsum += delta[k + 1][j] * W[k + 1][j][i];
			}
			delta[k][i] = f[k][i] * (1 - f[k][i])*tsum;
		}
	}
}
void weight_update() {
	int i, j, layer;

	for (i = 0; i < M[0]; i++) {// 0층의 가중치 업데이트
		for (j = 0; j < N; j++) {
			W[0][i][j] += c*delta[0][i] * input[j];			//학습률, 입력값, delta값 반영하여 수정
		}
	}
	for (layer = 1; layer < NLayer; layer++) {		// layer 층의 가중치 업데이트
		for (i = 0; i < M[layer]; i++) {
			for (j = 0; j < M[layer - 1] + 1; j++) {
				W[layer][i][j] += c*delta[layer][i] * f[layer - 1][j];
			}
		}
	}

}

int training() {
	int tr = 0, i, j;
	int epoch = N_tr_examples;
	double sum_sq_error;
	double avg_sq_error;
	char flag = 'n';
	while (flag == 'n' || flag == 'N') { //설정 오차율 미만일 경우 선택 
		do {
			for (i = 0; i < epoch; i++) {
				memcpy(input, trainData[i], sizeof(trainData[i]));			//메모리 카피 memcpy(dest,sour,size):sour의 메모리영역을 dest에 복사함, size는 복사할 바이트 개수
				input[N - 1] = 1;
				memcpy(D, d_tr[i], sizeof(d_tr[i]));			//D배열에 i번째 입력의 숫자값(0~9) 넣어줌(명시된 값)
				forward_compute();
				backward_compute();
				weight_update();
			}
			sum_sq_error = 0.0;

			for (i = 0; i < epoch; i++) {

				memcpy(input, trainData[i], sizeof(trainData[i]));
				input[N - 1] = 1;
				memcpy(D, d_tr[i], sizeof(d_tr[i]));
				forward_compute();
				for (j = 0; j < M[NLayer - 1]; j++)
					sum_sq_error += (D[j] - f[NLayer - 1][j])* (D[j] - f[NLayer - 1][j]);		//각 층에서의 에러값 제곱

			}
			//c = c*0.98;			//기존 코딩은 학습률을 계속 줄임 -->왜일까??		but 기존코딩대로하니 정확도 낮아져서 주석처리함
			tr++;		//트레이닝 횟수
			avg_sq_error = sum_sq_error / (epoch*M[NLayer - 1]); //오차의 평균
			printf("#%depoch 후 평균 오차율: %f \n", tr, avg_sq_error);
		} while (avg_sq_error > train_threshold && tr<tr_N); //설정한 오차율 보다 높거나 설정한 트레이닝 횟수보다 작을 동안 반복
		printf("목표 오차율에 도달했습니다. 훈련을 마치시겠습니까? (y/n):");
		fflush(stdin);
		scanf("%c", &flag);
	}
	return tr;
}

double test() {	
	int num_correct = 0;
	int i, index;
	double test_accurancy;
	for (i = 0; i < N_te_examples; i++) {
		memcpy(input, testData[i], sizeof(testData[i]));
		input[N - 1] = 1;
		memcpy(D, d_te[i], sizeof(d_te[i]));
		forward_compute();
		index = correctNum();		//인식결과의 숫자
		if (D[index] == 1) {		//인식한대로 숫자가 index라면
			num_correct++;			//맞은 개수 더함
		}

	}
	test_accurancy = (double)num_correct / N_te_examples;		//테스트한 결과 정확도
	return test_accurancy;
}

int correctNum() {
	double temp = f[NLayer - 1][0];
	int ret = 0;
	for (int i = 1; i < M[NLayer - 1]; i++) {			//출력노드 수만큼 돌림(10)
		if (temp < f[NLayer - 1][i]) {					//값이 더 큰지 확인함
			temp = f[NLayer - 1][i];
			ret = i;
		}
	}
	return ret; //가장 큰 값의 배열의 index 출력
}