#pragma once

#define SORT 10			//숫자 0~9
#define ORDER 160		//숫자가 갖고 있는 프로토타입의 개수(10개씩*16명)
#define ROWS 7			//행
#define COLS 7			//열
#define PEOPLE 16		//사람 수
#define FEAT 16			//특징벡터 행렬 수(프로젝션14 + 분산2)
#define DIV 2			//망 특징 추출 시 열,행을 DIV로 나눔(즉 전체를 DIV*DIV개의 망으로 나눔)


int count_r[ROWS];		// 1의 개수를 행마다 더한 행렬
int count_c[COLS];		// 1의 개수를 열마다 더한 행렬
int dist[2];			//x,y의 분산값	인덱스 0:x의 분산 1:y의 분산
int cross_r[ROWS];		//행의 0,1토글 횟수
int cross_c[COLS];		//열의 0,1토글 횟수
int mat[DIV*DIV];				//각 망에서 1의 개수


//특징1. 프로젝션
void projection(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
//특징2. x,y의 분산값
void distribute(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
//특징3. 교차 특징
void cross(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
//특징4. 망 특징
void matrix(int N[SORT][ORDER][ROWS][COLS], int sort, int order);

int protoData[SORT][ORDER][ROWS][COLS];		//16_1
int num[SORT][ORDER][ROWS][COLS];			//16_2