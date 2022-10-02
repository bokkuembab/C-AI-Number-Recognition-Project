#ifndef _AI_H_
#define _AI_H_

#define NLayer 3		//전체 레이어수
#define MLayerSize 1000			//은닉층1/2 의 개수보다 큰 임의의 수
#define m0 200		//은닉층1 개수
#define m1 200		//은닉층2 개수
#define m2 10		//출력층 개수
#define N 49+1		//총 입력 시그날의 수
#define tr_N 500	//설정한 학습 횟수
#define train_threshold 0.053		//목표 오차율
#define N_tr_examples 1600		//학습 데이터의 수
#define N_te_examples 1600		//테스트 데이터의 수
int M[NLayer];


void data_Onmemory(); //트레이닝 데이터 및 테스트 데이터 메모리에 저장하는 함수
void weight_init(); // 초기 가중치 설정 함수
void forward_compute();		//포워드 계산 함수
void backward_compute();	//BP연산함수(역전파)
void weight_update();		//가중치 수정하는 함수
int training(); //트레이닝 데이터로 훈련하는 함수
double test(); //테스트 데이터로 정답률 출력 함수
int correctNum(); // 출력 값중에 가장 큰 값을 가지는 배열의 index 출력(index=인식된 숫자)
#endif 