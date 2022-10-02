/*
 * 참고한 기존코드 *
 * 설명 : "https://juyoung-1008.tistory.com/5"
 * 소스코드 : "https://github.com/park-ju1008/Neural-Network/tree/91343ec215ba3ec1e9c13f594bdfaf3f66eb9092"
 * 사용하려는 목적에 맞게 적절하게 코드와 주석을 수정, 첨가하였음 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memory.h>
#include "AI.h"

int M[NLayer] = { m0, m1, m2 };				//층마다의 노드 수 저장
int trainData[N_tr_examples][N - 1] = { 0, };		//학습데이터들 받아와서 저장
int d_tr[N_tr_examples][m2] = { 0, };				//N_tr_exples번째의 학습데이터가 인식되어야할 숫자(즉, 정답명시-정답인 인덱스에 1들어감)
int testData[N_te_examples][N - 1] = { 0, };		//테스트 데이터들 받아와서 저장
int d_te[N_te_examples][m2] = { 0, };				////N_te_exples번째의 테스트데이터가 인식되어야할 숫자(즉, 정답명시)

int input[N];			//입력 N개 저장함
int D[m2];				//정답 넣어줌


double s[NLayer][MLayerSize];		//NLayer층의 MLayerSize번째 노드의 값(들어온 값에 웨이트 값을 곱한 결과)
double f[NLayer][MLayerSize];		//s값을 시그노이드 함수에 통과시킨 후의 값
double delta[NLayer][MLayerSize];
double W[NLayer][MLayerSize][MLayerSize];		//웨이트 값
double c = 0.5;		//학습률

void data_Onmemory() {
	FILE *trainfp;
	FILE *testfp;
	int i = 0, j, ans;			//ans:기대되는 출력값(숫자)
	input_max = 0;

	trainfp = fopen("train.txt", "rt");
	testfp = fopen("test.txt", "rt");
	if (trainfp != NULL) {

		while (!feof(trainfp)) {			//파일에 있는 것들을 모두 불러와서 저장시킴
			fscanf(trainfp, "%d ", &ans);
			d_tr[i][ans] = 1;				//d_tr의 i번째 데이터의 숫자는 ans임(맞는 숫자 인덱스 값에 1넣어줌)
			for (j = 0; j < N - 1; j++) {
				fscanf(trainfp, "%d ", &trainData[i][j]);
				if (input_max < trainData[i][j])
					input_max = trainData[i][j];		//가장 큰 입력값 찾음
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


void weight_init() {				//모든 노드의 weight parameter들 초기화
	int i, j, k, r, pre_layer;
	srand(time(NULL));
	for (i = 0; i < NLayer; i++) {
		if (i == 0) {
			pre_layer = N;
			for (j = 0; j < M[i]; j++) {
				for (k = 0; k < pre_layer; k++) {
					r = (double)(rand());						//초기에 rand()함수 돌려서 랜덤으로 나온 값으로 가중치 고정시킴(rand()함수는 프로그램 한 번 실행하면 바뀌지X)
					W[i][j][k] = (r / (double)RAND_MAX) - 0.5; //입력 값이 커 w값 작게 설정 -->
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
			//s[0][i] += (input[j] / 255.0) * W[0][i][j];		//gray scale 이미지를 0~1사이의 실수로 바꿈(필기체 인식 MNIST 데이터를 사용할 때)
			s[0][i] += (input[j] / (double)input_max) * W[0][i][j];			//0~1사이의 실수로 바꿔주기 위해 입력의 최대값으로 나눠줌
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
	int num = 0;
	int plus_t=1;
	int epoch = N_tr_examples;
	double sum_sq_error;
	char flag = 'n';
	trainTime = 0.0;
	while (plus_t>=1) { //설정 학습횟수 미만일 경우 선택 
		do {
			time_t startTime = time(NULL);				//시작시간 저장

			for (i = 0; i < epoch; i++) {				//전체 학습 데이터 학습 시킴
				memcpy(input, trainData[i], sizeof(trainData[i]));			//메모리 카피 memcpy(dest,sour,size):sour의 메모리영역을 dest에 복사함, size는 복사할 바이트 개수
				input[N - 1] = 1;
				memcpy(D, d_tr[i], sizeof(d_tr[i]));			//D배열에 i번째 입력의 숫자값(0~9) 넣어줌(명시된 값)
				forward_compute();
				backward_compute();
				weight_update();
			}
			sum_sq_error = 0.0;				//오차율의 합 초기화

			for (i = 0; i < epoch; i++) {

				memcpy(input, trainData[i], sizeof(trainData[i]));
				input[N - 1] = 1;
				memcpy(D, d_tr[i], sizeof(d_tr[i]));
				forward_compute();
				for (j = 0; j < M[NLayer - 1]; j++)
					sum_sq_error += (D[j] - f[NLayer - 1][j])* (D[j] - f[NLayer - 1][j]);		//각 층에서의 에러값 제곱(음수일수도 있으므로)

			}
			//c = c*0.98;			//기존 코딩은 학습률을 계속 줄임 -->왜일까??		but 기존코딩대로하니 정확도 낮아져서 주석처리함
			tr++;		//트레이닝 횟수
			avg_sq_error = sum_sq_error / (epoch*M[NLayer - 1]); //오차의 평균
			printf("#%depoch 후 평균 오차율: %f \n", tr, avg_sq_error);

			time_t endTime = time(NULL);		//끝난 시간
			trainTime += difftime(endTime, startTime);		//총 학습시간 더함
		} while (tr<tr_N+num);				//설정한 트레이닝 횟수보다 작을 동안 반복
		printf("목표 트레이닝 횟수만큼 학습하였습니다.\n추가학습 횟수를 적어주세요(그만하려면 0) : ");
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
	time_t startTime = time(NULL);				//시작시간 저장
	for (i = 0; i < N_te_examples; i++) {
		memcpy(input, testData[i], sizeof(testData[i]));
		input[N - 1] = 1;
		memcpy(D, d_te[i], sizeof(d_te[i]));
		forward_compute();
		index = correctNum();		//인식결과의 숫자
		if (D[index] == 1) {		//인식한대로 숫자가 index라면
			num_correct++;			//맞은 개수 더함
			correct[index]++;		//각 숫자마다 맞은 개수 더함
		}
	}
	time_t endTime = time(NULL);		//끝난 시간
	testTime = difftime(endTime, startTime);		//테스트 시간 구함

	test_accurancy = (double)num_correct / N_te_examples;		//테스트한 결과 전체정확도
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
