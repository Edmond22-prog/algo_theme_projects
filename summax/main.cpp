#include <iostream>
#include <vector>

using namespace std;

// Declaration of class
class Indices
{
private:
  int start;
  int end;
  int max;

public:
  Indices(int i, int j, int max)
  {
    this->start = i;
    this->end = j;
    this->max = max;
  }

  int getStart()
  {
    return this->start;
  }

  int getEnd()
  {
    return this->end;
  }

  int getMax()
  {
    return this->max;
  }

  void setStart(int i)
  {
    this->start = i;
  }

  void setEnd(int i)
  {
    this->end = i;
  }

  void setMax(int max)
  {
    this->max = max;
  }
};

// Declaration of functions
Indices sumMax(vector<int>, int);

// Definition of functions
Indices sumMax(vector<int> T, int n)
{
  Indices indices = Indices(0, 0, T[0]);
  vector<int> S(n);

  S[0] = T[0];

  for (int i = 1; i < n; i++)
  {
    if (T[i] + S[i - 1] >= T[i])
    {
      S[i] = T[i] + S[i - 1];

      if (S[i] > indices.getMax())
      {
        indices.setMax(S[i]);
        indices.setEnd(i);
      }
    }
    else
    {
      S[i] = T[i];

      if (S[i] > indices.getMax())
      {
        indices.setMax(S[i]);
        indices.setStart(i);
        indices.setEnd(i);
      }
    }
  }

  return indices;
}

// Print table
void printTable(vector<int> T)
{
  cout << "[ ";
  for (int i = 0; i < T.size(); i++)
  {
    cout << T[i] << "  ";
  }

  cout << "]" << endl
       << endl;
}

int main()
{
  cout << endl
       << "================ Program of SumMax ================" << endl
       << endl
       << endl;

  // Size of Table
  int n;

  cout << "Enter the size of the table T: ";
  cin >> n;
  cout << endl
       << endl;

  vector<int> T(n);

  int i = 0;
  while (i < n)
  {
    cout << "Provide the value of T[" << i + 1 << "]: ";
    cin >> T[i];

    i += 1;
  }

  cout << endl
       << endl;
  cout << "------ Print Table ------" << endl;

  printTable(T);

  Indices indices = sumMax(T, T.size());

  cout << "------ Result -------" << endl;
  cout << "start: " << indices.getStart() + 1 << endl
       << "end: " << indices.getEnd() + 1 << endl
       << "sum: " << indices.getMax() << endl
       << endl;

  return 0;
}