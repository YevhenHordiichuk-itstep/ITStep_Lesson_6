/*Task 1. SquareMatrix
  1) по-умолчанию, создающий матрицу размером 2х2
	2) конструктор с аргументом - размером N
	3) конструктор глубокого копирования
	4) оператор присваивания с глубоким копированием
	5) деструктор
	6) операторы сложения, вычитания и умножения двух матриц
	7) функцию-член transpose(), которая транспонирует текущую матрицу
	8) операторы ввода и вывода  <<, >>
	9**) функцию-член, вычисляющущю детерминант текущей матрицы
*/

#include <iostream>                         
#include <cstdlib>

struct SquareMatrix {
  int** data;
  size_t H, W;
  
  friend std::istream& operator >> (std::istream& cin, SquareMatrix& A);
  friend std::ostream& operator << (std::ostream& cout, SquareMatrix& A);
  
  SquareMatrix() {
    this->H = 2;
    this->W = 2;
    data = new int*[H];
    for (size_t i = 0; i < this->H; ++i) {
      data[i] = new int[W];
    }
  }
  SquareMatrix(size_t n) 
  : W(n), H(n) {
    this->data = new int*[H];
    for (size_t i = 0; i < this->H; ++i) {
      this->data[i] = new int[W];
    }
  }
  SquareMatrix(size_t w, size_t h) 
  : W(w), H(h) {
		this->data = new int*[H];
		for (size_t i = 0; i < H; ++i) {
			this->data[i] = new int[W];
		}
	}
  SquareMatrix(const SquareMatrix& obj) 
  : W(obj.W), H(obj.H) {
    this->data = new int*[H];
    for (size_t i = 0; i < this->H; ++i) {
      data[i] = new int[W];
    }
    for (size_t j = 0; j < this->H; ++j) {
      for (size_t k = 0; k < this->W; ++k) {
        data[j][k] = obj.data[j][k];
      }
    }
  }
  ~SquareMatrix() {
    for (size_t i = 0; i < this->W; ++i) {              //5)
      delete[] data[i];
    }
    delete[] data;
  }
  
  SquareMatrix& operator = (const SquareMatrix& A) {
    this->W = A.W;
    this->H = A.H;
    for (size_t h = 0; h < this->H; ++h) {
      for (size_t w = 0; w < this->W; ++w) {
        this->data[h][w] = A.data[h][w];
      }
    }
    return *this;
  }
  SquareMatrix operator + (SquareMatrix& A) {
      SquareMatrix R(W, H);
      for (size_t j = 0; j < this->H; ++j) {
        for (size_t k = 0; k < this->W; ++k) {
          R.data[j][k] = data[j][k] + A.data[j][k];
        }
      }
    return R;
  }
  SquareMatrix operator - (SquareMatrix& A) {
      SquareMatrix R(W, H);
      for (size_t j = 0; j < this->H; ++j) {
        for (size_t k = 0; k < this->W; ++k) {
          R.data[j][k] = data[j][k] - A.data[j][k];
        }
      }
    return R;
  }
  SquareMatrix operator * (SquareMatrix& A) {
    SquareMatrix R(W, H);
    for (size_t j = 0; j < W; ++j) {
      for (size_t k = 0; k < H; ++k) {
        R.data[j][k] = 0;
        for (size_t key = 0; key < W; ++key) {
          R.data[j][k] = data[j][key] * A.data[key][k]; 
        }
      }
    }
    return R;
  }
  
  SquareMatrix transpose(const SquareMatrix& A) {
    SquareMatrix R(A.H, A.W);
    for (size_t j = 0; j < A.H; ++j) {
      for (size_t k = 0; k < A.W; ++k) {
        R.data[j][k] = A.data[k][j];
      }
    }
    return R;
  }
  
  int det(SquareMatrix& A) {
    if (A.W < 3 && A.H < 3) {
      return A.data[0][0] * A.data[1][1] - A.data[1][0] * A.data[0][1];
    }
    
    SquareMatrix R(W, H + H - 1);
    for (size_t j = 0; j < R.W; ++j) {
      for (size_t k = 0; k < R.H; ++k) {
        if (k >= H) {
          R.data[j][k] = A.data[j][k - H];
          continue;
        }
        R.data[j][k] = A.data[j][k];
      }
    }
    
    int det = 0;
    for (size_t j = 0; j < R.W; ++j) {
      int add = 1;
      for (size_t k = 0; k < A.H; ++k) {
        add *= R.data[k][k + j];
      }
      det += add;
    }
    
    for (size_t j = 0; j < R.W; ++j) {
      int add = 1;
      for (size_t k = 0; k < A.H; ++k) {
        add *= R.data[R.W - 1 - k][k + j];
      }
      det -= add;
    }
    
    return det;
  }
};

std::istream& operator >> (std::istream& cin, SquareMatrix& A) {
  for (size_t j = 0; j < A.H; ++j) {
    for (size_t k = 0; k < A.W; ++k) {
      cin >> A.data[j][k];
    }
  }
  std::cout << "\n";  return cin;
}

std::ostream& operator << (std::ostream& cout, SquareMatrix& A) {
  for (size_t j = 0; j < A.H; ++j) {
    for (size_t k = 0; k < A.W; ++k) {
      cout << A.data[j][k] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";  return cout;
}

void generate(SquareMatrix& A) {
  for (size_t j = 0; j < A.H; ++j) {
    for (size_t k = 0; k < A.W; ++k) {
      A.data[j][k] = 1 + rand() % 9;
    }
  }
}

void printMatrix(SquareMatrix& A) {
  for (size_t j = 0; j < A.H; ++j) {
    for (size_t k = 0; k < A.W; ++k) {
      std::cout << A.data[j][k] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main(int argc, char** argv) {
  
  std::cout << "1)\n";
  SquareMatrix A;
  generate(A);
  printMatrix(A);
  
  std::cout << "2)\n";
  size_t n = 5;
  SquareMatrix B(n);
  generate(B);
  printMatrix(B);
  
  std::cout << "3)\n";
  SquareMatrix C = A;
  printMatrix(C);
  
  std::cout << "4)\n";
  SquareMatrix D(n);
  D = B;
  printMatrix(D);
  
  std::cout << "6)\n";
  SquareMatrix E = A + C;
  printMatrix(E);
  SquareMatrix F(n);
  F = B - D - D;
  printMatrix(F);
  SquareMatrix H = F * D;
  printMatrix(H);
  
  std::cout << "7)\n";
  SquareMatrix R(n);
  generate(R);
  printMatrix(R);
  R = R.transpose(R);
  printMatrix(R);
  
  std::cout << "8)\n";
  std::cout << R;
  SquareMatrix M;
  std::cout << "Enter 2x2 Matrix:\n";
  std::cin >> M;
  std::cout << M;
  
  std::cout << "9)\n";
  n = 4;
  SquareMatrix N(n);
  printMatrix(N);
  std::cout << N.det(N);
  
  return 0;
}