#include <iostream>
#include <algorithm> 
#include <string>
#include <stack>

using namespace std;

#define MAX_SIZE 20
int c[MAX_SIZE][MAX_SIZE]; //최장 공통 부분 길이 배열

/*
(1) 3번 문제
"10111010100"과 "00111010110의 최장 공통 부분 순서를 구하시오.

(2) 5번 문제
[알고리즘 9-11]을 최장 공통 부분 순서의 길이와 함께 최장 공통 부분 순서도 같이 구할 수 있도록 바꾸시오.
*/

//Q5 최장 공통 부분 순서 & 길이 찾는 함수
void LCS(string m, string n, int m_len, int n_len) {
	// 최장 공통 부분 순서를 저장하는 스택
	// LIFO 구조인 스택을 이용하여 부분 순서를 출력한다.
	stack<int> st; 

	/*
	Cij: 문자열 Xij=<x1, x2, ..., xi>와 Yij=<y1, y2, ..., yj>의 LCS 길이

	Cij = 0 (if i = 0 or j = 0)
	    = C_i-1, j-1 + 1 (if i, j>0 and xi = yi)
		= max{C_i-1, j, C_i, j-1} (if i, j > 0 and xi != yi)
	*/

	// Cij = 0 (if i = 0 or j = 0)
	for (int i = 0; i < m_len; i++)
		c[i][0] = 0;
	for (int j = 0; j < n_len; j++)
		c[0][j] = 0;

	for (int i = 1; i < m_len; i++) {
		for (int j = 1; j < n_len; j++) {
			if (m[i] == n[j]) // Cij = C_i - 1, j - 1 + 1 (if i, j > 0 and xi = yi)
				c[i][j] = c[i - 1][j - 1] + 1;
			else // Cij = max{ C_i - 1, j, C_i, j - 1 } (if i, j > 0 and xi != yi)
				c[i][j] = max(c[i - 1][j], c[i][j - 1]);
		}
	}
	
	int i = m_len - 1;
	int j = n_len - 1;
	// 위에서 만든 최장 공통 길이 배열을 가지고 왼쪽/위를 비교하여 같은 숫자인 곳으로 이동
	while (c[i][j] != 0) {
		if (c[i][j] == c[i][j - 1]) // 왼쪽과 같으면 왼쪽으로 이동
			j--;
		else if (c[i][j] == c[i - 1][j]) // 위와 같으면 위로 이동
			i--;
		else { // 양 옆에 같은 숫자가 없으면 대각선으로 이동
			st.push(i); // 해당 인덱스 stack에 저장
			i--; j--;
		}
	}

	cout << m <<"과 " << n << "의 최장 공통 부분 순서는 ";
	while (!st.empty()) { // 스택이 빌 때 까지 인덱스 꺼내어 해당 인덱스의 부분 출력
		cout << m[st.top()];
		st.pop();
	}
	cout << "입니다." << endl;
	cout << "최장 공통 부분 순서의 길이는 " << c[m_len - 1][n_len - 1] << "입니다."<<endl;
}

int main() {
	char m[] = "10111010100";
	char n[] = "00111010110";

	int m_length = strlen(m);
	int n_length = strlen(n);

	cout << "동적프로그래밍 프로젝트 Q3 & Q5" << "\n" << "1612169 배현진" << "\n\n";

	LCS(m, n, m_length, n_length);

	system("pause");
	return 0;
}

