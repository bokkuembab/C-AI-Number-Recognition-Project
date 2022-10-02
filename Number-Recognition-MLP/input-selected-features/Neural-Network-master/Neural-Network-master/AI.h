/*
 * ������ �����ڵ� *
 * ���� : "https://juyoung-1008.tistory.com/5"
 * �ҽ��ڵ� : "https://github.com/park-ju1008/Neural-Network/tree/91343ec215ba3ec1e9c13f594bdfaf3f66eb9092"
 * ����Ϸ��� ������ �°� �����ϰ� �ڵ�� �ּ��� ����, ÷���Ͽ��� 
 */

#ifndef _AI_H_
#define _AI_H_

#define NLayer 3		//��ü ���̾��
#define MLayerSize 1000			//������1/2 �� �������� ū ������ ��
#define m0 50		//������1 ����
#define m1 50		//������2 ����
#define m2 10		//����� ����
#define N 49+1		//�� �Է� �ñ׳��� ��(������ �״��:49  Ư¡���� ��:34)
#define tr_N 3000	//������ �н� Ƚ��
#define train_threshold 0.005		//��ǥ ������
#define N_tr_examples 3200		//�н� �������� ��
#define N_te_examples 3200		//�׽�Ʈ �������� ��
int M[NLayer];
double trainTime;		//�н� �ð�
double testTime;		//�׽�Ʈ �ð�
int correct[m2];		//���� m2�� ���� ����
int input_max;			//�Է°��� �ִ밪
double avg_sq_error;	//������


void data_Onmemory(); //Ʈ���̴� ������ �� �׽�Ʈ ������ �޸𸮿� �����ϴ� �Լ�
void weight_init(); // �ʱ� ����ġ ���� �Լ�
void forward_compute();		//������ ��� �Լ�
void backward_compute();	//BP�����Լ�(������)
void weight_update();		//����ġ �����ϴ� �Լ�
int training(); //Ʈ���̴� �����ͷ� �Ʒ��ϴ� �Լ�
double test(); //�׽�Ʈ �����ͷ� ����� ��� �Լ�
int correctNum(); // ��� ���߿� ���� ū ���� ������ �迭�� index ���(index=�νĵ� ����)
#endif 