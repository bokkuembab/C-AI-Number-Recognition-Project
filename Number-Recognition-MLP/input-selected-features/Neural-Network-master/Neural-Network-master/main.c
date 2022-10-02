/*
 * 참고한 기존코드 *
 * 설명 : "https://juyoung-1008.tistory.com/5"
 * 소스코드 : "https://github.com/park-ju1008/Neural-Network/tree/91343ec215ba3ec1e9c13f594bdfaf3f66eb9092"
 * 사용하려는 목적에 맞게 적절하게 코드와 주석을 수정, 첨가하였음 
 */

#include "AI.h"
#include <stdio.h>
#include <time.h>
extern double c;

int main() {
	double sum_sq_error = 0.0; //오차들의 합
	avg_sq_error = 0.0;			//오차의 평균
	double test_accurancy;
	int tr;

	printf("							     시작\n");
	printf("####################################################################\n\n");
	printf("각층의 노드 수 : ");
	for (int i = 0; i < NLayer; i++) {
		printf("%d ", M[i]);
	}
	printf("\n1epoch=%d\n", N_tr_examples);
	printf("train_threshold : %f\n", train_threshold);
	printf("학습률 c값: %f\n", c);
	printf("---------------------------------------\n");
	printf("트레이닝 데이터 및 테스트 데이터 읽어오는 중...\n");
	data_Onmemory();
	printf("랜덤 가중치 설정 중...\n ");
	weight_init();				//한번 설정하면 visual 끄기까지 바뀌지 않음(rand함수 사용했으므로)
	printf("트레이닝 시작\n");
	tr = training();
	printf("\n------------------------------------------\n");
	printf("테스트 시작\n");
	test_accurancy = test();
	printf("-------------------설정값-----------------------\n");
	if (N - 1 == 49)
		printf("<7*7 데이터 그대로 입력하여 학습>\n");
	else
		printf("<특징 추출 후 학습>\n");

	printf("층마다 노드의 개수: ");
	printf("%d ", N - 1);
	for (int i = 0; i < NLayer; i++) {
		printf("%d ", M[i]);
	} 
	printf("\n학습률 : %f\n", c);
	printf("학습 횟수(반복한 에폭 수) : %d\n", tr);
	printf("학습 데이터의 수 (1epoch) : %d\n", N_tr_examples);
	printf("테스트 데이터의 수 : %d\n", N_te_examples);

	printf("-------------------결과값-----------------------\n");
	printf("마지막 평균오차율 : %lf\n", avg_sq_error);
	printf("총 학습시간 : %.1f sec\n", trainTime);
	//printf("테스트시간 : %lf sec\n", testTime);
	printf("전체 숫자 인식 정확도 : %f\% \n", test_accurancy * 100);
	printf("---------------숫자별 인식정확도----------------\n");
	for (int i = 0; i<m2; i++)
		printf("숫자 %d : %f\% \n", i, (double)correct[i] / N_te_examples * 10 * 100.0);

	return 0;
}
