#include <iostream>
#include <vector>

using namespace std;

// Declaration of classes
class Direction
{
public:
  string value;
  int i;
  int j;
};

class LCS
{
public:
  int length;
  vector<Direction> direction;
};

// Declarations of functions
vector<vector<LCS>> lcs(string X, string Y, int m, int n);
vector<string> printLCS(vector<vector<LCS>> C, int m, int n);

// Definitions of functions
vector<vector<LCS>> lcs(string X, string Y, int m, int n)
{
  // Dynamic Programming method
  vector<vector<LCS>> C(m, vector<LCS>(n));

  // Initialisation
  for (int i = 0; i < m; i++)
  {
    C[i][0].direction = vector<Direction>(1);

    C[i][0].length = 0;
    C[i][0].direction[0].value = "";
    C[i][0].direction[0].i = i;
    C[i][0].direction[0].j = 0;
  }

  for (int j = 0; j < n; j++)
  {
    C[0][j].direction = vector<Direction>(1);

    C[0][j].length = 0;
    C[0][j].direction[0].value = "";
    C[0][j].direction[0].i = 0;
    C[0][j].direction[0].j = j;
  }

  // Recurrence
  for (int i = 1; i < m; i++)
  {
    for (int j = 1; j < n; j++)
    {
      if (X[i] == Y[j])
      {
        C[i][j].direction = vector<Direction>(1);

        C[i][j].length = C[i - 1][j - 1].length + 1;
        C[i][j].direction[0].value = "diagonal";
        C[i][j].direction[0].i = i - 1;
        C[i][j].direction[0].j = j - 1;
      }
      else if (C[i - 1][j].length > C[i][j - 1].length)
      {
        C[i][j].direction = vector<Direction>(1);

        C[i][j].length = C[i - 1][j].length;
        C[i][j].direction[0].value = "up";
        C[i][j].direction[0].i = i - 1;
        C[i][j].direction[0].j = j;
      }
      else if (C[i - 1][j].length < C[i][j - 1].length)
      {
        C[i][j].direction = vector<Direction>(1);

        C[i][j].length = C[i][j - 1].length;
        C[i][j].direction[0].value = "left";
        C[i][j].direction[0].i = i;
        C[i][j].direction[0].j = j - 1;
      }
      else
      {
        C[i][j].direction = vector<Direction>(2);

        C[i][j].length = C[i - 1][j].length;
        C[i][j].direction[0].value = "up";
        C[i][j].direction[0].i = i - 1;
        C[i][j].direction[0].j = j;
        C[i][j].direction[1].value = "left";
        C[i][j].direction[1].i = i;
        C[i][j].direction[1].j = j - 1;
      }
    }
  }

  return C;
}

string printLCS(vector<vector<LCS>> C, string X, int i, int j) {
  string c("");

  while (i > 0 && j > 0) {
    if (C[i][j].direction[0].value == "diagonal") {
      c += X[i];
    }

    i = C[i][j].direction[0].i;
    j = C[i][j].direction[0].j;
  }

  return c;
}

void printLength(vector<vector<LCS>> C, int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << C[i][j].length << "  ";
    }

    cout << endl;
  }
}

int main()
{
  // Input
  string X = "_ABCCAC";
  string Y = "_ACACD";
  int m = X.length();
  int n = Y.length();

  // Output
  vector<vector<LCS>> C = lcs(Y, X, n, m);

  // Print the dynamic programing table
  printLength(C, n, m);

  cout << "Length of LCS: " << C[n - 1][m - 1].length << endl;

  return 0;
}