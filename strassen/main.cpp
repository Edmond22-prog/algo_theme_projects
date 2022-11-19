#include <iostream>
#include <vector>
<<<<<<< HEAD
#include <chrono>
=======
#include <math.h>
>>>>>>> 350289d9a74ba6a5bd15bdca4ee76db18529ec91

using namespace std;

// Declaration section
vector<vector<int>> strassen(int n, vector<vector<int>> A, vector<vector<int>> B);
vector<vector<int>> add(int n, vector<vector<int>> A, vector<vector<int>> B);
vector<vector<int>> sub(int n, vector<vector<int>> A, vector<vector<int>> B);
void printMatrix(int n, int m, vector<vector<int>> A);
int getGreaterPowerOfTwo(int n);
vector<vector<int>> strassenWithFormatedMatrix(vector<vector<int>> A, vector<vector<int>> B);

// Add function
vector<vector<int>> add(int n, vector<vector<int>> A, vector<vector<int>> B)
{
  vector<vector<int>> C(n, vector<int>(n));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  return C;
}

// Sub function
vector<vector<int>> sub(int n, vector<vector<int>> A, vector<vector<int>> B)
{
  vector<vector<int>> C(n, vector<int>(n));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
  return C;
}

int getGreaterPowerOfTwo(int n)
{
  int i = 1;
  while (i < n)
  {
    i *= 2;
  }
  return i;
}


// Print matrix function
void printMatrix(int n, int m, vector<vector<int>> A)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cout << A[i][j] << "\t";
    }
    cout << endl;
  }
}

// Functions that format data and calls the strassen method
// Input: Matrix A and B
// Output: Print the result C = A*B
vector<vector<int>> strassenWithFormatedMatrix(vector<vector<int>> A, vector<vector<int>> B)
{
  // Get size of matrix A and B
  int n1 = A.size();  // number of lines of A
  int n2 = A[0].size(); // number of columns of A
  int m1 = B.size();  // number of lines of B
  int m2 = B[0].size();  // number of columns of B

  int n = max(n1, n2);  // Size of A
  int m = max(m1, m2);  // Size of B
  int k = max(m, n);

  // Get the greater power of two base of the max of n and m
  int greaterPowerOfTwo = getGreaterPowerOfTwo(k);

  //  Declare matrix A1 and B1 with the greater power of two size
  vector<vector<int>> A1(greaterPowerOfTwo, vector<int>(greaterPowerOfTwo, 0));
  vector<vector<int>> B1(greaterPowerOfTwo, vector<int>(greaterPowerOfTwo, 0));

  // Initialize the matrix A1 and B1 with the values of A and B
  for (int i = 0; i < n1; i++)
  {
    for (int j = 0; j < n2; j++)
    {
      A1[i][j] = A[i][j];
    }
  }

  for (int i = 0; i < m1; i++)
  {
    for (int j = 0; j < m2; j++)
    {
      B1[i][j] = B[i][j];
    }
  }

  auto start = chrono::high_resolution_clock::now();

  // Using strassen algorithm to multiply matrix A1 and B1
  vector<vector<int>> C = strassen(greaterPowerOfTwo, A1, B1);

  auto finish = chrono::high_resolution_clock::now();

  chrono::duration<double> elapsed = finish - start;

  cout << "Strassen Algorithm: " << elapsed.count() << " s" << endl;

  return C;
}

// Strassen algorithm for matrix multiplication
// Input: two square matrices A and B of size n*n
// Output: the product matrix C = A*B
vector<vector<int>> strassen(int n, vector<vector<int>> A, vector<vector<int>> B)
{
  // Final result matrix C
  vector<vector<int>> C(n, vector<int>(n, 0));

  // Base case
  if (n <= 0) {
    cout << "Invalid matrix size" << endl;

    return C;
  }
  
  if (n == 1)
  {
    C[0][0] = A[0][0] * B[0][0];

    return C;
  }

  int new_size = n / 2;

  // Submatrix of A
  vector<vector<int>> A11(new_size, vector<int>(new_size, 0));
  vector<vector<int>> A12(new_size, vector<int>(new_size, 0));
  vector<vector<int>> A21(new_size, vector<int>(new_size, 0));
  vector<vector<int>> A22(new_size, vector<int>(new_size, 0));

  // Submatrix of B
  vector<vector<int>> B11(new_size, vector<int>(new_size, 0));
  vector<vector<int>> B12(new_size, vector<int>(new_size, 0));
  vector<vector<int>> B21(new_size, vector<int>(new_size, 0));
  vector<vector<int>> B22(new_size, vector<int>(new_size, 0));

  // Submatrix of C
  vector<vector<int>> C11(new_size, vector<int>(new_size, 0));
  vector<vector<int>> C12(new_size, vector<int>(new_size, 0));
  vector<vector<int>> C21(new_size, vector<int>(new_size, 0));
  vector<vector<int>> C22(new_size, vector<int>(new_size, 0));

  // Generated matrix
  vector<vector<int>> M1(new_size, vector<int>(new_size, 0));
  vector<vector<int>> M2(new_size, vector<int>(new_size, 0));
  vector<vector<int>> M3(new_size, vector<int>(new_size, 0));
  vector<vector<int>> M4(new_size, vector<int>(new_size, 0));
  vector<vector<int>> M5(new_size, vector<int>(new_size, 0));
  vector<vector<int>> M6(new_size, vector<int>(new_size, 0));
  vector<vector<int>> M7(new_size, vector<int>(new_size, 0));

  // Extraction of sub-matrices
  for (int i = 0; i < new_size; i++)
  {
    for (int j = 0; j < new_size; j++)
    {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + new_size];
      A21[i][j] = A[i + new_size][j];
      A22[i][j] = A[i + new_size][j + new_size];
      
      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + new_size];
      B21[i][j] = B[i + new_size][j];
      B22[i][j] = B[i + new_size][j + new_size];
    }
  }

  M1 = strassen(new_size, add(new_size, A11, A22), add(new_size, B11, B22));
  M2 = strassen(new_size, add(new_size, A21, A22), B11);
  M3 = strassen(new_size, A11, sub(new_size, B12, B22));
  M4 = strassen(new_size, A22, sub(new_size, B21, B11));
  M5 = strassen(new_size, add(new_size, A11, A12), B22);
  M6 = strassen(new_size, sub(new_size, A21, A11), add(new_size, B11, B12));
  M7 = strassen(new_size, sub(new_size, A12, A22), add(new_size, B21, B22));

  C11 = add(new_size, sub(new_size, add(new_size, M1, M4), M5), M7);
  C12 = add(new_size, M3, M5);
  C21 = add(new_size, M2, M4);
  C22 = add(new_size, sub(new_size, add(new_size, M1, M3), M2), M6);

  // Joining sub-matrices
  for (int i = 0; i < new_size; i++)
  {
    for (int j = 0; j < new_size; j++)
    {
      C[i][j] = C11[i][j];
      C[i][j + new_size] = C12[i][j];
      C[i + new_size][j] = C21[i][j];
      C[i + new_size][j + new_size] = C22[i][j];
    }
  }

  return C;
}

// Product of two matrices using the naive algorithm
// Input: two square matrices A and B of size n*n
// Output: the product matrix C = A*B
vector<vector<int>> naive(int n, vector<vector<int>> A, vector<vector<int>> B)
{
  auto start = chrono::high_resolution_clock::now();

  vector<vector<int>> C(n, vector<int>(n, 0));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      for (int k = 0; k < n; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  auto end = chrono::high_resolution_clock::now();

  chrono::duration<double> elapsed = end - start;

  cout << "Naive algorithm: " << elapsed.count() << " s" << endl;

  return C;
}

/* 
  retourne la puissance de 2 la plus plus proche
  du max des deux tailles
*/
int powerTwo(int n, int m)
{
  int p = 1;
  int new_size = fmax(n, m);
  while (p < new_size)
  {
    p *= 2;
  }
  return p;
}

vector<vector<int>> createMatrix( int n, int m)
{
  vector<vector<int>> A;
  A.assign(n, vector<int>(m));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cout << "entrer l'élément [" << i << "][" << j << "] >> ";
      cin >> A[i][j];
    }
  }
  return A;
}


int main()
{
  int n(0), m(0), p(0), k(0);
  vector<vector<int>> A;
  vector<vector<int>> B;
  vector<vector<int>> C;

  cout << endl
        << "======================= Produit DE DEUX MATRICES ================" << endl
        << endl;
  
  // saisie des deux matrices
  
  // première matrice
  cout << "---------------- première matrice ------------------" << endl << endl;
  cout << "entrer le nombre de lignes : ";
  cin >> n;
  cout << "entrer le nombre de colonnes : ";
  cin >> m;
  A = createMatrix(n, m);
  printMatrix(n, m, A);


  // deuxième matrice
  cout << "---------------- deuxième matrice ------------------" << endl << endl;
  cout << endl << "le nombre de lignes de la deuxième matrice est " << m << endl ;
  cout << endl << "entrer le nombre de colonnes : ";
  cin >> k;
  B = createMatrix(m, k);
  printMatrix(m, k, B);
  cout << endl << "Résultat de la multiplication : " << endl;

  C = strassenWithFormatedMatrix(A, B);

  printMatrix(n, k, C);

  // test avec initialisation

  // A.assign(8, vector<int>(8, 7));
  // printMatrix(8, A); cout << endl;
  // B.assign(8, vector<int>(8, 3));
  // printMatrix(8, B); cout << endl;
  // C = strassen(8, A, B);
  // printMatrix(8, C);


  // reformatage


  return 0;
}