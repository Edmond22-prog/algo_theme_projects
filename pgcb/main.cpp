#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Declaration of functions
int randomNumber();

// Definition of functions
int randomNumber()
{
  int rnum;

  /* generate secret number between 0 and 1: */
  rnum = rand() % 2;

  return rnum;
}

// Definition of classes
class Cell
{
private:
  int value;
  string color;
  int x;
  int y;

public:
  Cell(int value = 0, string color = "black", int x = 0, int y = 0)
  {
    this->value = value;
    this->color = color;
    this->x = x;
    this->y = y;
  }

  // Getters

  int getValue()
  {
    return value;
  }

  string getColor()
  {
    return color;
  }

  int getX()
  {
    return x;
  }

  int getY()
  {
    return y;
  }

  // Setters

  void setValue(int value)
  {
    this->value = value;
  }

  void setColor(string color)
  {
    this->color = color;
  }

  void setX(int x)
  {
    this->x = x;
  }

  void setY(int y)
  {
    this->y = y;
  }
};

class Matrix
{
private:
  vector<vector<Cell>> matrix;
  int size;

public:
  Matrix(int size)
  {
    this->size = size;

    this->generateMatrix(size);
  }

  // Getters

  vector<vector<Cell>> getMatrix()
  {
    return matrix;
  }

  int getSize()
  {
    return size;
  }

  // Setters

  void setMatrix(vector<vector<Cell>> matrix)
  {
    this->matrix = matrix;
  }

  /**
   * Generate a matrix of cell randomly of length size x size
   */
  void generateMatrix(int size)
  {
    vector<vector<Cell>> matrix(size, vector<Cell>(size));

    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        int rnum = randomNumber(); // Generate a random number
        string color = "";

        if (rnum == 0)
        {
          color = "black";
        }
        else
        {
          color = "white";
        }

        matrix[i][j].setColor(color);
        matrix[i][j].setValue(rnum);
        matrix[i][j].setX(i);
        matrix[i][j].setY(j);
      }
    }

    this->setMatrix(matrix);
  }

  /**
   *  Compute by filling the matrix the PGCB
   */
  void computePgcb()
  {
    // Test if the matrix size if greater than 1 before continue
    if (this->size > 1)
    {
      for (int i = 1; i < this->size; i++)
      {
        for (int j = 1; j < this->size; j++)
        {
          // If the current cell has a black color
          if (this->matrix[i][j].getColor() == "black")
          {
            this->matrix[i][j].setValue(0); // Set the value to 0
          }
          else // Elsewhere
          {
            // Get the minimum value of the 3 cells around
            int m = min(this->matrix[i - 1][j].getValue(), this->matrix[i][j - 1].getValue());
            m = min(m, this->matrix[i - 1][j - 1].getValue());

            this->matrix[i][j].setValue(1 + m);
          }
        }
      }
    }
  }

  /**
   *  Loop through the matrix and return the max value
   *  which is the PGCB
   */
  int getPgcb()
  {
    int max = 0; // Initial max value

    for (int i = 0; i < this->size; i++)
    {
      for (int j = 0; j < this->size; j++)
      {
        if (this->matrix[i][j].getValue() > max)
        {
          max = this->matrix[i][j].getValue();
        }
      }
    }

    return max;
  }

  /**
   *  Print the matrix in the console
   */
  void printMatrix()
  {
    for (int i = 0; i < this->getSize(); i++)
    {
      for (int j = 0; j < this->getSize(); j++)
      {
        cout << this->getMatrix()[i][j].getValue() << " ";
      }

      cout << endl;
    }
  }
};

int main()
{
  /* initialize random seed: */
  srand(time(NULL));

  cout << endl
       << "================ Program of PGCB ================" << endl
       << endl
       << endl;

  // Size of the matrix
  int n;

  cout << "Enter the size of the matrix: ";
  cin >> n;
  cout << endl
       << endl;

  // Generate a new matrix
  Matrix matrix = Matrix(n);

  // Compute the highest white square
  matrix.computePgcb();

  // Get the highest white square size
  int pgcb = matrix.getPgcb();

  cout << "The Matrix: " << endl;
  matrix.printMatrix();

  cout << endl;
  cout << "PGCB: " << pgcb << endl;

  return 0;
}
