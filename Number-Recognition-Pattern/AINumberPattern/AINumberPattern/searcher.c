//* 입력된 숫자의 특징벡터 추출하는 곳 -> searcher

#include "help.h"

void counting(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {
	
	// 개수 초기화
	for (int i = 0; i < ROWS; i++) {
		count_r[i] = 0;
		count_c[i] = 0;
	}

	// 행마다 1의 개수를 셈
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (N[sort][order][i][j] == 1)
				count_r[i] += 1;
			else
				;
		}
	}

	// 열마다 1의 개수를 셈
	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS; i++) {
			if (N[sort][order][i][j] == 1)
				count_c[j] += 1;
			else
				;
		}
	}

}

// 가로, 세로의 각각의 합이 1인 행, 열도 제외(십자 중에 합이 1이면 1)
int cross_r(int N[SORT][ORDER][ROWS][COLS], int sort, int order, int row) {
	int col;

	if (count_r[row] == 1) {
		//1이 있는 열의 위치 찾음
		for (int m = 0; m < COLS; m++) {
			if (N[sort][order][row][m] == 1) {
				col = m;
				break;
			}
			else ;
		}
		//열의 1개수가 1인지 
		if (count_c[col] == 1)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
int cross_c(int N[SORT][ORDER][ROWS][COLS], int sort, int order, int col) {
	int row;

	if (count_c[col] == 1) {
		//1이 있는 행의 위치 찾음
		for (int m = 0; m < ROWS; m++) {
			if (N[sort][order][m][col] == 1) {
				row = m;
				break;
			}
			else;
		}
		//행의 1개수가 1인지 
		if (count_r[row] == 1)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

void downsize(int N[SORT][ORDER][ROWS][COLS], int sort, int order) {

	// 1의 개수합이 0인 행 인식계산에서 제외하기
	for (int i = 0; i < ROWS; i++) {
		if (count_r[i] != 0 && cross_r(N, sort, order, i) == 0) {
				row_s = i;
				for (int j = i; j < ROWS; j++) {
					if (cross_r(N, sort, order, j) == 1) {
						row_e = j - 1;
						break;
					}
					else if (count_r[j] == 0 && cross_r(N, sort, order, j) == 0) {
						row_e = j - 1; 
						break;
					}
					else if (count_r[6] != 0 && cross_r(N, sort, order, 6)==0) {
						row_e = 6;
						break;
					}
					else
						;
				}
				break;
		}

	}

	// 1의 개수합이 0인 열 인식계산에서 제외하기
	for (int i = 0; i < COLS; i++) {
		if (count_c[i] != 0 && cross_c(N, sort, order, i) == 0) {
			col_s = i;
			for (int j = i; j < COLS; j++) {
				if (cross_c(N, sort, order, j) == 1) {
					col_e = j - 1;
					break;
				}
				else if (count_c[j] == 0) {
					col_e = j - 1;
					break; 
				}
				else if (count_c[6] != 0 && cross_c(N, sort, order, 6) == 0) {
					col_e = 6;
					break;
				}
				else
					;
			}
			break;
		}

	}


}

//열 개수가 양옆 대칭 인지
/*
int symmetry(int C_c[COLS], int col_s, int col_e) {
	int mid = MID(col_s, col_e) + col_s;
	int count = 0;
	//개수가 짝수이면
	if (MID(col_s, col_e) == 0) {
		for (int i = 0; i < MID(col_s, col_e); i++) {
			if (C_c[col_s + i] == C_c[col_e - i])
				count += 1;
			else ;
		}
		if (count == MID(col_s, col_e))
			return 1;
		else
			return 0;
	}

	//개수가 홀수이면
	else {

	}
}
*/

//맨위아래행과 가운데행들의 평균 1의 개수비교(위아래행 평균이 더 크면 1)
int avgCom(int R[ROWS], int start, int end) {
	double count_edge = (R[start] + R[end]) / 2.0;
	double count_center = 0.0;
	int center_num = end - start - 1;

	for (int i = 0; i < center_num; i++) {
		count_center += R[start + 1 + i];
	}
	count_center /= center_num;

	if (count_edge > count_center)
		return 1;
	else if (count_edge < count_center)
		return -1;
	else
		return 0;
}

//행,열을 반으로 나눠 1의 개수 비교(위쪽이 더 큰가?)
int half(int R[ROWS], int start, int end) {
	int count_l = 0;
	int count_r = 0;

	for (int i = 0; i < MID(start, end); i++) {
		count_l += R[start + i];
		count_r += R[end - i];
	}
	if (count_l == count_r)
		return 0;
	else if (count_l > count_r)
		return 1;
	else
		return -1;
}

//100%로 차있는 열이 없음(없으면 1)
int noFullCol(int C[COLS], int start, int end, int r_s, int r_e) {
	int count = 0;
	for (int i = 0; i < end - start + 1; i++) {
		if (C[start + i] == r_e - r_s + 1)
			count += 1;
		else
			;
	}
	if (count > 0)
		return 0;
	else
		return 1;
}

//행, 열의 중간이 100% 차있음(차있으면 1)
int midFull(int D[ROWS], int start, int end, int s, int e) {
	int mid = MID(start, end) + start;
	if (D[mid] == e - s + 1)
		return 1;
	else
		return 0;
}

//숫자 2,5 구분을 위한 앞, 뒤 뚫려있는 거 찾기(둘의 행위치 달라야 함)
int first0(int D[SORT][ORDER][ROWS][COLS], int r, int c, int row_s, int row_e, int col_s, int col_e) {
	int left = 10;
	int right = 10;
	
	//왼쪽 위부터
	for (int i = 0; i < row_e - row_s-1; i++) {
		if (D[r][c][row_s + i + 1][col_s] == 0) {
			left = row_s + i + 1;
			break;
		}
	}
	//오른쪽 아래부터
	for (int i = 0; i < row_e - row_s - 1; i++) {
		if (D[r][c][row_e - i - 1][col_e] == 0) {
			right = row_e - i - 1;
			break;
		}
	}
	if (left == 10 || right == 10)
		return 0;
	else if (left < right && left != 10 && right != 10)
		return 1;
	else if (right < left && left != 10 && right != 10)
		return -1;
	else
		return 0;
}