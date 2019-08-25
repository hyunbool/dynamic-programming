#include <iostream>
#include <algorithm> 
#include <string>
#include <stack>

using namespace std;

#define MAX_SIZE 20
int c[MAX_SIZE][MAX_SIZE]; //���� ���� �κ� ���� �迭

/*
(1) 3�� ����
"10111010100"�� "00111010110�� ���� ���� �κ� ������ ���Ͻÿ�.

(2) 5�� ����
[�˰��� 9-11]�� ���� ���� �κ� ������ ���̿� �Բ� ���� ���� �κ� ������ ���� ���� �� �ֵ��� �ٲٽÿ�.
*/

//Q5 ���� ���� �κ� ���� & ���� ã�� �Լ�
void LCS(string m, string n, int m_len, int n_len) {
	// ���� ���� �κ� ������ �����ϴ� ����
	// LIFO ������ ������ �̿��Ͽ� �κ� ������ ����Ѵ�.
	stack<int> st; 

	/*
	Cij: ���ڿ� Xij=<x1, x2, ..., xi>�� Yij=<y1, y2, ..., yj>�� LCS ����

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
	// ������ ���� ���� ���� ���� �迭�� ������ ����/���� ���Ͽ� ���� ������ ������ �̵�
	while (c[i][j] != 0) {
		if (c[i][j] == c[i][j - 1]) // ���ʰ� ������ �������� �̵�
			j--;
		else if (c[i][j] == c[i - 1][j]) // ���� ������ ���� �̵�
			i--;
		else { // �� ���� ���� ���ڰ� ������ �밢������ �̵�
			st.push(i); // �ش� �ε��� stack�� ����
			i--; j--;
		}
	}

	cout << m <<"�� " << n << "�� ���� ���� �κ� ������ ";
	while (!st.empty()) { // ������ �� �� ���� �ε��� ������ �ش� �ε����� �κ� ���
		cout << m[st.top()];
		st.pop();
	}
	cout << "�Դϴ�." << endl;
	cout << "���� ���� �κ� ������ ���̴� " << c[m_len - 1][n_len - 1] << "�Դϴ�."<<endl;
}

int main() {
	char m[] = "10111010100";
	char n[] = "00111010110";

	int m_length = strlen(m);
	int n_length = strlen(n);

	cout << "�������α׷��� ������Ʈ Q3 & Q5" << "\n" << "1612169 ������" << "\n\n";

	LCS(m, n, m_length, n_length);

	system("pause");
	return 0;
}

