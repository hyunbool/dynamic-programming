#include <iostream>
#include <algorithm>
using namespace std;

#define size 100

/*
6�� ����
2���� ��� ��� ������ ���ݸ� �����غ��ÿ�. n*n ����� ���� ������ ������ ������ �Ʒ����� �� ĭ�� �̵��Ͽ� �����ϴ� ���� �����ϳ�
�̵����� ��Ģ�� ������ ���� ���� �ٸ���.
- �������̳� �Ʒ���, �Ǵ� ������ �밢�����θ� �̵��� �� �ִ�.
- ����, ���������� �̵��� ��Ÿ�� �밢�� �̵��� ������� �ʴ´�.
���� (a)�� (b)�� ��Ģ�� ���ݵǴ� ���� ��Ģ�� �����ϴ� ����. ����� ���� (1, 1)���� (n, n)���� �̵��ϴ� ��� ����� ���� �� ���� ���� ������ ã��
���� ���α׷��� �˰����� �ۼ��Ͻÿ�.
*/

// ������&�Ʒ���&������ �밢�� �� �ִ밪�� ã�� �Լ�
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

// ���� ��� ã�� �Լ�
void matrixPath(int m[][size], int arr_size) {
	int c[size][size]; // ���� �� ���� �迭
	int tmp = 0;
	int I[size], J[size]; // ��� �ε��� ���� �迭
	int index = 0;

	/*
	cij: ���� (0, 0)���� ����(i, j)�� �̸��� �ְ� ����

	cij = mij + C_i, j-1 (if i = 0)
	    = mij + C_i-1, j (if j = 0)
	    = mij + max{C_i, j-1 , C_i-1, j , C_i-1, j-1} otherwise
	*/

	c[0][0] = m[0][0];  // ù ����� ������ ��� ����� ù��° ���� �����ϴ�.

	// m[0][n]�� m[n][0]���� ���� ��δ� ������/�Ʒ������� ���� �Ѱ��� ��ιۿ� �����Ƿ� �̸� �ʱ�ȭ
	for (int i = 1; i < arr_size; i++)
		c[0][i] = m[0][i] + c[0][i - 1];

	for (int j = 1; j < arr_size; j++)
		c[j][0] = m[j][0] + c[j - 1][0];

	// cij = mij + max{C_i, j-1 , C_i-1, j , C_i-1, j-1} otherwise
	for (int i = 1; i < arr_size; i++) {
		for (int j = 1; j < arr_size; j++) {
			tmp = maximum(c[i - 1][j], c[i][j - 1], c[i - 1][j - 1]); // ������ = �ִ��̹Ƿ� ������/�Ʒ���/������ �밢���� ���� �� ���� ū ���� ã�´�.
			c[i][j] = m[i][j] + tmp; // �ڽ��� ������ ���ؼ� ����
		}
	}

	cout << "���� �� ���: " << endl;
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	/* 
	c[n][n] �迭�� backtrack�Ͽ� ��θ� ã�´�.
	*/
	int i = arr_size - 1;
	int j = arr_size - 1;

	int max_tmp = 0;

	while (i > 0 && j > 0) {
		max_tmp = maximum(c[i - 1][j], c[i][j - 1], c[i - 1][j - 1]); // ���� ���� ����/����/���� �� �� ���� ū ���� ã�´�.
		if (max_tmp == c[i][j - 1]) { // ���ʰ� ������ �������� �̵�
			I[index] = i;
			J[index] = j;
			j--; index++;
		}
		else if (max_tmp == c[i - 1][j]) { // ���� ������ ���� �̵�
			I[index] = i;
			J[index] = j;
			i--; index++;
		}
		else { // �밢���� ������ �밢������ �̵�
			I[index] = i;
			J[index] = j;
			i--; j--; index++;
		}
	}

	/*
	���� �ε����� c[0][n], c[n][0]�� ��� ���� ������ش�.
	*/
	// ������ ���� �ε����� ���(j=0)
	if (i != 0) {
		while (i >= 0) { // (0, 0)�� �� �� ���� �������� �̵�
			I[index] = i;
			J[index] = j;
			i--; index++;
		}
	}
	// ���� ���� �ε����� ���(i=0)
	else if (j != 0) {
		while (j >= 0) { // (0, 0)�� �� �� ���� ���������� �̵�
			I[index] = i;
			J[index] = j;
			j--; index++;
		}
	}

	// ���� ��ο� ���� �� ���
	cout << "���� ��δ� ";
	for (int a = index-1; a >= 0; a--) {
		cout << "(" << I[a] << ", " << J[a] << ")" << " ";
	}
	cout << "�Դϴ�." << endl;
	cout << "���� ���� " << c[arr_size - 1][arr_size - 1] << "�� �Դϴ�." << endl;
}

int main() {
	int arr_size = 4;

	//��ã�� ��� ����
	int m[][size] = { {6, 7, 12, 5},
				{5, 3, 11, 18},
				{7, 17, 3, 3},
				{8, 10, 14, 9} }; 

	cout << "�������α׷��� ������Ʈ Q6" << "\n" << "1612169 ������" << "\n\n";

	cout << "���� ��� ���: "<<endl;
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// ���� ��ο� �� ã��
	matrixPath(m, arr_size);

	system("pause");
	return 0;
}

