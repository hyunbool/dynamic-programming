#include <iostream>
#include <algorithm>
using namespace std;

#define size 100

/*
6번 문제
2절의 행렬 경로 문제를 조금만 변형해보시오. n*n 행렬의 왼쪽 위에서 시작해 오른쪽 아래까지 한 칸씩 이동하여 도달하는 것은 동일하나
이동상의 규칙이 다음과 같이 조금 다르다.
- 오른쪽이나 아래쪽, 또는 오른쪽 대각선으로만 이동할 수 있다.
- 왼쪽, 위쪽으로의 이동과 여타의 대각선 이동은 허용하지 않는다.
다음 (a)와 (b)는 규칙에 위반되는 예외 규칙을 만족하는 예다. 행렬의 원소 (1, 1)에서 (n, n)으로 이동하는 모든 경로의 점수 중 가장 높은 점수를 찾는
동적 프로그래밍 알고리즘을 작성하시오.
*/

// 오른쪽&아래쪽&오른쪽 대각선 중 최대값을 찾는 함수
int maximum(int x, int y, int z)
{
	if (x > y)
		if (x > z)
			return x;
		else
			return z;
	else
		if (y > z)
			return y;
		else
			return z;
}

// 최적 경로 찾는 함수
void matrixPath(int m[][size], int arr_size) {
	int c[size][size]; // 최적 값 저장 배열
	int tmp = 0;
	int I[size], J[size]; // 경로 인덱스 저장 배열
	int index = 0;

	/*
	cij: 원소 (0, 0)에서 원소(i, j)에 이르는 최고 점수

	cij = mij + C_i, j-1 (if i = 0)
	    = mij + C_i-1, j (if j = 0)
	    = mij + max{C_i, j-1 , C_i-1, j , C_i-1, j-1} otherwise
	*/

	c[0][0] = m[0][0];  // 첫 경로의 점수는 경로 행렬의 첫번째 값과 동일하다.

	// m[0][n]과 m[n][0]으로 가는 경로는 오른쪽/아래쪽으로 가는 한가지 경로밖에 없으므로 미리 초기화
	for (int i = 1; i < arr_size; i++)
		c[0][i] = m[0][i] + c[0][i - 1];

	for (int j = 1; j < arr_size; j++)
		c[j][0] = m[j][0] + c[j - 1][0];

	// cij = mij + max{C_i, j-1 , C_i-1, j , C_i-1, j-1} otherwise
	for (int i = 1; i < arr_size; i++) {
		for (int j = 1; j < arr_size; j++) {
			tmp = maximum(c[i - 1][j], c[i][j - 1], c[i - 1][j - 1]); // 최적값 = 최댓값이므로 오른쪽/아래쪽/오른쪽 대각선의 점수 중 가장 큰 값을 찾는다.
			c[i][j] = m[i][j] + tmp; // 자신의 점수와 더해서 저장
		}
	}

	cout << "최적 값 행렬: " << endl;
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	/* 
	c[n][n] 배열을 backtrack하여 경로를 찾는다.
	*/
	int i = arr_size - 1;
	int j = arr_size - 1;

	int max_tmp = 0;

	while (i > 0 && j > 0) {
		max_tmp = maximum(c[i - 1][j], c[i][j - 1], c[i - 1][j - 1]); // 현재 값의 왼쪽/위쪽/왼쪽 위 중 가장 큰 값을 찾는다.
		if (max_tmp == c[i][j - 1]) { // 왼쪽과 같으면 왼쪽으로 이동
			I[index] = i;
			J[index] = j;
			j--; index++;
		}
		else if (max_tmp == c[i - 1][j]) { // 위와 같으면 위로 이동
			I[index] = i;
			J[index] = j;
			i--; index++;
		}
		else { // 대각선과 같으면 대각선으로 이동
			I[index] = i;
			J[index] = j;
			i--; j--; index++;
		}
	}

	/*
	벽에 부딪히는 c[0][n], c[n][0]의 경우 따로 계산해준다.
	*/
	// 오른쪽 벽에 부딪히는 경우(j=0)
	if (i != 0) {
		while (i >= 0) { // (0, 0)이 될 때 까지 위쪽으로 이동
			I[index] = i;
			J[index] = j;
			i--; index++;
		}
	}
	// 위쪽 벽에 부딪히는 경우(i=0)
	else if (j != 0) {
		while (j >= 0) { // (0, 0)이 될 때 까지 오른쪽으로 이동
			I[index] = i;
			J[index] = j;
			j--; index++;
		}
	}

	// 최적 경로와 최적 값 출력
	cout << "최적 경로는 ";
	for (int a = index-1; a >= 0; a--) {
		cout << "(" << I[a] << ", " << J[a] << ")" << " ";
	}
	cout << "입니다." << endl;
	cout << "최적 값은 " << c[arr_size - 1][arr_size - 1] << "점 입니다." << endl;
}

int main() {
	int arr_size = 4;

	//길찾기 행렬 저장
	int m[][size] = { {6, 7, 12, 5},
				{5, 3, 11, 18},
				{7, 17, 3, 3},
				{8, 10, 14, 9} }; 

	cout << "동적프로그래밍 프로젝트 Q6" << "\n" << "1612169 배현진" << "\n\n";

	cout << "현재 경로 행렬: "<<endl;
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// 최적 경로와 값 찾기
	matrixPath(m, arr_size);

	system("pause");
	return 0;
}

