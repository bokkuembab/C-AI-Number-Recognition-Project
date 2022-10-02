#pragma once
/*
* 숫자 인식하는 곳 -> main
* 각 숫자의 특징벡터 추출하는 곳 -> character
* 입력된 숫자의 특징벡터 추출하는 곳 -> searcher
* 숫자데이터 저장하는 곳 -> numbers

* 숫자 인식 실패하면 랜덤으로 인식하도록 함
(제일 나타나기 쉬운 수이므로, 인식률을 높이기 위해)
(현재는 숫자가 제대로 인식되는지 확인해야 하므로 일단 오인식이라고 뜨게 함)
*/

//필요한 매크로 함수들
#define SORT 10
#define ORDER 10
#define ROWS 7
#define COLS 7
#define FEATURE 7	//특징벡터의 수
#define PROTO 1		//프로토타입의 수

#define MID(x, y) (((y) - (x) + 1 ) / 2)
#define REST(x, y) (((y) - (x) + 1 ) % 2)
#define MAX(x, y) ( (x) > (y) ) ? (x) : (y)
#define MIN(x, y) ( (x) < (y) ) ? (x) : (y)

//정규화를 위한 함수들
void counting(int N[SORT][ORDER][ROWS][COLS], int sort, int order);
int cross_r(int N[SORT][ORDER][ROWS][COLS], int sort, int order, int row);
int cross_c(int N[SORT][ORDER][ROWS][COLS], int sort, int order, int row);
void downsize(int N[SORT][ORDER][ROWS][COLS], int sort, int order);

//특징벡터들
int half(int R[ROWS], int start, int end);
int noFullCol(int C[COLS], int start, int end, int r_s, int r_e);
int midFull(int D[ROWS], int start, int end, int s, int e);
int avgCom(int R[ROWS], int row_s, int row_e);
int first0(int D[SORT][ORDER][ROWS][COLS], int i, int j, int row_s, int row_e, int col_s, int col_e);

//필요한 배열들
int inData[SORT][ORDER][ROWS][COLS];	// [숫자종류n][숫자n10개][행][열]
int protoData[SORT][ORDER][ROWS][COLS];			// 정한 프로토타입들
int count_r[ROWS];		// 1의 개수를 행마다 더한 행렬
int count_c[COLS];		// 1의 개수를 열마다 더한 행렬
int featureIn[FEATURE];	// 입력된 숫자의 특징벡터의 값을 갖고 있는 행렬
int featureNum[SORT][FEATURE];	// 프로토타입들의 특징벡터의 값을 갖고 있는 행렬
int rate[SORT];			// 프로토타입과의 일치율

// 필요한 값들
int row_s, col_s;		// 합이 0이 아닌 시작
int row_e, col_e;		// 합이 0이 아닌 끝
int max;		//일치율이 가장 높은 숫자
int numRate, totalRate;			//숫자인식한 결과 일치율 숫자당, 전체