#include <iostream>
using namespace std;

#define MAX_SIZE 100

int m[MAX_SIZE][MAX_SIZE]; //최소 연산 값 배열
int loc[MAX_SIZE][MAX_SIZE]; //연산 위치 저장 배열
int p[MAX_SIZE]; // 행렬 크기

/*1번 문제
행렬 A1, A2, ..., A5가 각각 p0*p1, p1*p2, ..., p4*p5 행렬이고 <p0, p1, p2, p3, p4, p5> = <10, 5, 20, 7, 15, 3>이라 하자.
(1) 모든 가능한 곱셈 순서는 총 몇가지 인가?
(2) 동적 프로그래밍으로 최적 행렬 곱셈 순서를 찾으시오.
*/

// 5개 행렬로 이뤄진 곱셈 식에서 갯수구하기
int printAllOrder(int i, int j, int size)  {
	int count = 0; // 갯수 저장

	/*
	A1*A2*A3*A4*A5의 경우 다음과 같이 나눌 수 있다.:
	(1) A1*(A2*A3*A4*A5)
	(2) (A1*A2)*(A3*A4*A5)
	(3) (A1*A2*A3)*(A4*A5)
	(4) (A1*A2*A3*A4)*A5

	이 중 (1)/(4)(a = 1 / a = 4 일 때), (2)/(3)(a = 2 / a = 3 일 때)이 같은 케이스
	*/


	for (int a = 1; a < size; a++) {
		if (a == i or a == j - 1) { //(1)/(4)(a = 1 / a = 4 일 때)
			for (int j = 1; j < size - 1; j++) {
				/*
				(1)의 경우 A1은 더이상 나누어 지지 않으므로 (A2*A3*A4*A5)를 다시 나누는 경우를 고려
				(1-1) A2*(A3*A4*A5)
				(1-2) (A2*A3)*(A4*A5)
	            (1-3) (A2*A3*A4)*A5
				
				이 중 (1-1)/(1-3)(j = 1 / j = 3 일 때), (1-2)(j = 2 일 때) 같은 케이스
				*/
				if (j == 1 or j == 3) { // (1 - 1) / (1 - 3)(j = 1 / j = 3 일 때)
					/*
					(1-1)의 경우 A2는 더이상 나누어 지지 않으므로 (A3*A4*A5)를 다시 나누는 경우를 고려
					- A3*(A4*A5)
					- (A3*A4)*A5
					*/
					for (int b = 1; b < size - 2; b++) {
						count++;
					}
				}
				else if (j == 2) // (1-2)(j = 2 일 때) 
					count++;
			}
		}
		else if (a == i + 1 or a == j - 2) { // (2) / (3)(a = 2 / a = 3 일 때)
			/*
			(2)의 경우 (A1*A2)은 더이상 나누어지지 않으므로 (A3*A4*A5)을 나누는 경우만 고려
			- A3*(A4*A5)
			- (A3*A4)*A5
			*/
			for (int k = 1; k < size - 2; k++)
				count++;
		}
	}
	return count;
}

// 최적의 순서 출력하는 함수
void order(int i, int j)  
{
	int k;
	if (i == j)
		cout << "A" << i;
	else {
		k = loc[i][j]; // 연산위치가 저장되어 있는 loc배열에서 괄호가 들어갈 인덱스를 가져온다.
		cout << "(";
		order(i, k); // 재귀적으로 반복
		order(k + 1, j);
		cout << ")";
	}
}

// 최적 행렬 순서 찾기
int minmult(int size) {
	// 최적 행렬 순서를 저장하기 위한 위치 저장
	int location = 0;

	/*
	Cij: 행렬 Ai, ..., Aj의 곱 Ai...Aj를 계산하는 최소 비용
	Cij = 0 (if i = j)
	    = min(i <= k <= j-1){Cik + C_k-1,j + p_i-1pkpj} (if i < j)
	*/

	// i = j인 경우 0
	for (int i = 0; i <= size; i++)
		m[i][i] = 0;

	// 최적 행렬 순서 배열 초기화
	for (int i = 0; i <= size; i++)
		for (int j = 0; j <= size; j++)
			loc[i][j] = 0;

	for (int r = 1; r <= size; r++) {
		for (int i = 1; i <= size - r; i++) {
			for (int r = 1; r <= size - 1; r++) { // 대각선 순서로 계산
				for (int i = 1; i <= size - r; i++) {
					int j = i + r;
					m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j]; // 최소비용은 일단 배열이 곱해지는 순서대로 초기화
					location = i; // 끊을 위치 저장
					for (int k = i + 1; k <= j - 1; k++) { // 곱해지는 순서를 다르게 하여(괄호가 들어가는 위치를 다르게 하여) 초기화 한 값과 비교
						if (m[i][j] > m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]) { // 만약 기존의 값보다 작으면 바꿔준다.
							m[i][j] = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
							location = k; // 끊을 위치 저장
						}
						//count++;
					}
					loc[i][j] = location;
				}
			}
		}
	}

	return m[1][size]; // 최소 연산 값 리턴
}


int main(){
	int size = 5; // 곱할 행렬 갯수
	int result = 0;
	cout << "동적프로그래밍 프로젝트 Q1" << "\n" << "1612169 배현진" << "\n\n";
	p[0] = 10, p[1] = 5, p[2] = 20, p[3] = 7, p[4] = 15, p[5] = 3;  // p0*p1, p1*p2, ..., p4*p5 행렬, <p0, p1, p2, p3, p4, p5> = <10, 5, 20, 7, 15, 3>

	cout << "Q1-1 " << "모든 가능한 곱셈 순서는 총 " << printAllOrder(1, size, size) << "가지 입니다." << endl; // (1) 모든 가능한 곱셈 순서는 총 몇가지 인가? 

	result = minmult(size); // (2) 동적 프로그래밍으로 최적 행렬 곱셈 순서를 찾으시오.

	cout << "Q1-2 최적 행렬 곱셈 순서는 ";
	order(1, size);
	cout << ", 최적 행렬 곱셈 값은 " << result << "입니다." << endl;

	cout << endl;

	
	system("pause");
	return 0;
}
