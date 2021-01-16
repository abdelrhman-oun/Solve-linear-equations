/*--------------------------------------------------------------------------------------------------------------------------
* file name  : Source.cpp
* Author     : OUN
* Created on : July 30, 2019
* description: C++ program to solve linear equations. The program
			   reads first an integer n which is the number of equations
--------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------INCLUDES------------------------------------------------------------*/
#include <iostream> 
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/*-----------------------------------------------FUNCTIONS DEFINITIONS-----------------------------------------------------*/

float determinant(float matrix[100][100], int n) {
	float det = 0;
	if (n == 2) {
		float det = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
		return det;
	}
	else {
		float mat[100][100];
		int nn = n;
		for (int k = 0; k < nn; k++) {
			for (int i = 1; i < nn; i++) {
				int column = 0;
				for (int j = 0; j < nn; j++) {
					if (column < k) {
						mat[i - 1][column] = matrix[i][j];
					}
					else {
						mat[i - 1][column] = matrix[i][j + 1];
					}
					column++;
				}
			}
			det += pow((-1), k) * matrix[0][k] * determinant(mat, n - 1);
		}
	}
	return det;
}
int maxmum(string xx) {
	int max = 0, num1;
	string no1;
	for (int l = 0; l < xx.length(); l++) {
		if (xx[l] == 'x') {
			no1 = xx.substr(l + 1);
			num1 = atof(no1.c_str());
			if (num1 > max) {
				max = num1;
			}
		}
	}
	return max;
}
int main() {
	int no_equ, x = 0, z, max = 0, num1;
	float num;
	string str, str2, no, no1;
	getline(cin, no);
	no_equ = atof(no.c_str());
	vector <string> equ(no_equ);
	for (int i = 0; i < no_equ; i++)getline(cin, equ[i]);
	vector < vector < float > > coeff;
	for (int i = 0; i < no_equ; i++) {
		for (int l = 0; l < equ[i].length(); l++) {
			if (equ[i][l] == 'x') {
				no1 = equ[i].substr(l + 1);
				num1 = atof(no1.c_str());
				if (num1 > max) {
					max = num1;
				}
			}
			coeff.assign(no_equ, vector<float>(max + 1, 0));
		}
	}
	for (int i = 0; i < no_equ; i++) {
		for (int j = 1; j < equ[i].length(); j++) {
			if (equ[i][j] == '+' || equ[i][j] == '-' || equ[i][j] == '=') {
				str = equ[i].substr(x, j - x);
				x = j;
				num = atof(str.c_str());
				if (num == 0 && str[0] != '-')num = 1;
				else if (num == 0 && str[0] == '-')num = -1;
				z = -1;
				for (int k = 0; k < str.length(); k++)if (str[k] == 'x')z = k;
				if (z != -1) {
					str2 = str.substr(z + 1);
					z = atof(str2.c_str());
				}
				else z = 0;
				coeff[i][z] += num;
			}
			if (equ[i][j] == '=') {
				str = equ[i].substr(j + 1);
				num = atof(str.c_str());
				coeff[i][0] -= num;
			}
		}
		coeff[i][0] *= -1;
		x = 0;
	}
	////////////////////////////////
	string operation;
	getline(cin, operation);
	/*----------------------------------------------- Level 1 -----------------------------------------------------*/
	if (operation == "num_vars") {
		cout << max;
	}
	else if (operation.substr(0, 8) == "equation") {
		string no_of_equ;
		int number, max2 = 0;
		no_of_equ = operation.substr(8);
		number = atof(no_of_equ.c_str()) - 1;
		max2 = maxmum(equ[number]);

		bool kye = true;
		for (int i = 1; i <= max2; i++) {
			if (coeff[number][i] == 0)continue;
			else if (kye == false && coeff[number][i] > 0)cout << "+";
			cout << coeff[number][i] << "x" << i;
			kye = false;
			if (i == max2) cout << "=";

		}
		cout << coeff[number][0];
	}
	else if (operation.substr(0, 8) == "column x") {
		string no_of_equ;
		int number;
		no_of_equ = operation.substr(8);
		number = atof(no_of_equ.c_str());
		for (int i = 0; i < no_equ; i++) {
			cout << coeff[i][number] << endl;
		}
	}
	/*----------------------------------------------- Level 2 -----------------------------------------------------*/
	else if (operation.substr(0, 3) == "add") {
		string equ_1, equ_2;
		int equ1, equ2;
		int max1, max2;
		equ_1 = operation.substr(3);
		equ1 = atof(equ_1.c_str());
		equ_2 = operation.substr(operation.find(" ", 4));
		equ2 = atof(equ_2.c_str());
		max1 = maxmum(equ[equ1 - 1]);
		max2 = maxmum(equ[equ2 - 1]);
		if (max1 > max2)max = max1;
		else max = max2;
		vector<float>result(max + 1);
		for (int i = 0; i <= max; i++) {
			result[i] = coeff[equ1 - 1][i] + coeff[equ2 - 1][i];
		}
		bool kye = true;';'
		for (int i = 1; i <= max; i++) {
			if (result[i] == 0)continue;
			else if (kye == false && result[i] > 0)cout << "+";
			cout << result[i] << "x" << i;
			kye = false;
			if (i == max) cout << "=";

		}
		cout << result[0];
	}

	else if (operation.substr(0, 8) == "subtract") {
		string equ_1, equ_2;
		int equ1, equ2;
		int max1, max2;
		equ_1 = operation.substr(8);
		equ1 = atof(equ_1.c_str());
		equ_2 = operation.substr(operation.find(" ", 9));
		equ2 = atof(equ_2.c_str());
		max1 = maxmum(equ[equ1 - 1]);
		max2 = maxmum(equ[equ2 - 1]);
		if (max1 > max2)max = max1;
		else max = max2;
		vector<float>result(max + 1);
		for (int i = 0; i <= max; i++) {
			result[i] = coeff[equ1 - 1][i] - coeff[equ2 - 1][i];
		}
		bool kye = true;
		for (int i = 1; i <= max; i++) {
			if (result[i] == 0)continue;
			else if (kye == false && result[i] > 0)cout << "+";
			cout << result[i] << "x" << i;
			kye = false;
			if (i == max) cout << "=";

		}
		cout << result[0];
	}
	else if (operation.substr(0, 12) == "substitute x") {
		string column_, equ_1, equ_2;
		int column, equ1, equ2;
		column_ = operation.substr(12);
		column = atof(column_.c_str());
		equ_1 = operation.substr(operation.find(" ", 13));
		equ1 = atof(equ_1.c_str());
		equ_2 = operation.substr(operation.find(" ", (operation.find(" ", 13)) + 1));
		equ2 = atof(equ_2.c_str());
		vector<float>new_equ(max + 1);
		vector<float>result(max + 1);
		for (int i = 0; i <= max; i++) {
			new_equ[i] = coeff[equ2 - 1][i] * (-1 * coeff[equ1 - 1][column] / coeff[equ2 - 1][column]);
		}
		for (int i = 0; i <= max; i++) {
			result[i] = new_equ[i] + coeff[equ1 - 1][i];
		}

		bool kye = true;
		for (int i = 1; i <= max; i++) {
			if (result[i] == 0)continue;
			else if (kye == false && result[i] > 0)cout << "+";
			cout << result[i] << "x" << i;
			kye = false;
			if (i == max) cout << "=";

		}
		cout << result[0];

	}
	/*----------------------------------------------- Level 3 -----------------------------------------------------*/
	else if (operation == "D") {
		for (int i = 0; i < no_equ; i++) {
			for (int j = 1; j <= max; j++) {
				cout << coeff[i][j] << " ";
			}
			cout << endl;
		}
	}

	else if (operation.substr(0, 3) == "D x") {
		string no_of_equ;
		int number;
		no_of_equ = operation.substr(3);
		number = atof(no_of_equ.c_str());
		for (int i = 0; i < no_equ; i++) {
			for (int j = 1; j <= max; j++) {
				if (j == number) {
					cout << coeff[i][0] << " ";
					continue;
				}
				cout << coeff[i][j] << " ";
			}
			cout << endl;
		}

	}

	else if (operation == "D_value") {
		float mtx[100][100];
		for (int i = 0; i < no_equ; i++) {
			for (int j = 1; j <= max; j++) {
				mtx[i][j - 1] = coeff[i][j];
			}
		}
		float ans;
		ans = determinant(mtx, max);
		cout << ans;
	}
	else if (operation == "solve") {
	for (int k = 1; k <= no_equ; k++) {
		float mtx[100][100];
		for (int i = 0; i < no_equ; i++) {
			for (int j = 1; j <= max; j++) {
				mtx[i][j - 1] = coeff[i][j];
			}
		}
		float mtx2[100][100];
		for (int i = 0; i < no_equ; i++) {
			for (int j = 1; j <= max; j++) {
				if (j == k) {
					mtx2[i][j - 1] = coeff[i][0];
					continue;
				}
				mtx2[i][j - 1] = coeff[i][j];
			}
		}



		float ans;
		ans = determinant(mtx2, max) / determinant(mtx, max);
		cout << "x" << k << "=" << ans << endl;

	}
	}

	return 0;
}