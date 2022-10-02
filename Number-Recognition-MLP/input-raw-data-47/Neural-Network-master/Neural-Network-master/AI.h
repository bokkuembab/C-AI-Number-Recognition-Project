#ifndef _AI_H_
#define _AI_H_

#define NLayer 3		//��ü ���̾��
#define MLayerSize 1000			//������1/2 �� �������� ū ������ ��
#define m0 200		//������1 ����
#define m1 200		//������2 ����
#define m2 10		//����� ����
#define N 49+1		//�� �Է� �ñ׳��� ��
#define tr_N 500	//������ �н� Ƚ��
#define train_threshold 0.053		//��ǥ ������
#define N_tr_examples 1600		//�н� �������� ��
#define N_te_examples 1600		//�׽�Ʈ �������� ��
int M[NLayer];


void data_Onmemory(); //Ʈ���̴� ������ �� �׽�Ʈ ������ �޸𸮿� �����ϴ� �Լ�
void weight_init(); // �ʱ� ����ġ ���� �Լ�
void forward_compute();		//������ ��� �Լ�
void backward_compute();	//BP�����Լ�(������)
void weight_update();		//����ġ �����ϴ� �Լ�
int training(); //Ʈ���̴� �����ͷ� �Ʒ��ϴ� �Լ�
double test(); //�׽�Ʈ �����ͷ� ����� ��� �Լ�
int correctNum(); // ��� ���߿� ���� ū ���� ������ �迭�� index ���(index=�νĵ� ����)
#endif 