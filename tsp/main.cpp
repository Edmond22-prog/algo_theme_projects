#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Declaration of classes
class Point
{
private:
  int x;
  int y;

public:
  Point(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  // Getters
  int getX()
  {
    return this->x;
  }

  int getY()
  {
    return this->y;
  }

  // Setters
  void setX(int x)
  {
    this->x = x;
  }

  void setY(int y)
  {
    this->y = y;
  }
};

class TSP
{
private:
  vector<vector<Point>> plan;
  vector<Point> cycle;
  int size;
  int dimension;

public:
  TSP(int dimension, int size)
  {
    this->dimension = dimension;
    this->size = size;

    // Generate point randomly
    this->generatePoints();
  }

  // Getters
  int getSize()
  {
    return this->size;
  }

  int getDimension()
  {
    return this->dimension;
  }

  vector<vector<Point>> getPlan()
  {
    return this->plan;
  }

  vector<Point> getCycle()
  {
    return this->cycle;
  }

  /**
   * Generate number randomly range between 0 and dimension -1
   */
  int randomNumber(int max)
  {
    int rnum;

    /* generate number between 0 and dimension -1: */
    rnum = rand() % max;

    return rnum;
  }

  /**
   * Generates points randomly
   */
  void generatePoints()
  {
    // Initialize plan
    vector<vector<Point>> myPlan(this->dimension, vector<Point>(this->dimension, Point(-1, -1)));

    int i = 0;
    vector<Point> points(this->size, Point(-1, -1));

    while (i < this->size)
    {
      int x = randomNumber(this->dimension);
      int y = randomNumber(this->dimension);

      // Verify if point already exists or not
      if (myPlan[x][y].getX() == -1)
      {
        // Create new point
        Point point = Point(x, y);

        // Add point in the plan
        myPlan.at(x).at(y) = point;

        // Add point in the vector
        points.at(i) = point;

        i++;
      }
    }

    // Set plan
    this->plan = myPlan;

    // Set cycle
    this->cycle = points;
  }

  void simulatedAnnealing()
  {
    // Set temperature
    double temperature = 100;
    int k = 1;

    // Set initial solution
    vector<Point> currentSolution = this->cycle;

    // Set initial weight
    double currentWeight = this->calculateWeight(currentSolution);

    // Print initial solution
    this->printCycle(currentSolution);

    cout << "Initial weight: " << currentWeight << endl;
    cout << "Initial temperature: " << temperature << endl;

    // Set the stop condition
    while (k <= 30)
    {
      // Get new solution
      vector<Point> newSolution = this->generateNeighbor(currentSolution);

      // Get new weight
      double newWeight = this->calculateWeight(newSolution);

      // Decrease temperature
      temperature = this->updateTempreture(temperature);

      // Get probability
      double probability = this->probability(temperature, currentSolution, newSolution);

      // Generate random value between 0 and 1
      double randomValue = (double)rand() / (double)RAND_MAX;

      // Verify if new solution is better than current solution
      if (newWeight < currentWeight)
      {
        // Set new solution as current solution
        currentSolution = newSolution;

        // Set new weight as current weight
        currentWeight = newWeight;

        // Print current solution
        this->printCycle(currentSolution);
        cout << "Weight " << k << ": " << currentWeight << endl;
        cout << "Temperature " << k << ": " << temperature << endl;
      }
      else if (randomValue < probability)
      {
        // Set new solution as current solution
        currentSolution = newSolution;

        // Set new weight as current weight
        currentWeight = newWeight;

        // Print current solution
        this->printCycle(currentSolution);
        cout << "Weight " << k << ": " << currentWeight << endl;
        cout << "Temperature " << k << ": " << temperature << endl;
        cout << "Probability " << k << ": " << probability << endl;
        cout << "Random Value " << k << ": " << randomValue << endl;
      }

      k += 1;
    }

    // Set final solution
    this->cycle = currentSolution;
  }

  /**
   * Compute the distance between two points
   */
  double getDistance(Point p1, Point p2)
  {
    return sqrt(pow(abs((double)p1.getX() - (double)p2.getX()), 2) + pow(abs((double)p1.getY() - (double)p2.getY()), 2));
  }

  /**
   * Compute the weight of the cycle
   */
  double calculateWeight(vector<Point> cycle)
  {
    double weight = 0;

    // Add distance between point consecutively
    for (int i = 0; i < this->size - 1; i++)
    {
      weight += this->getDistance(cycle.at(i), cycle.at(i + 1));
    }

    // Add the distance between the first point and the last one
    weight += this->getDistance(cycle.at(0), cycle.at(this->size - 1));

    return weight;
  }

  /**
   * Compute the probability
   */
  double probability(double temperature, vector<Point> cycle1, vector<Point> cycle2)
  {
    // Get weights
    double w1 = this->calculateWeight(cycle1);
    double w2 = this->calculateWeight(cycle2);

    return exp((w1 - w2) / temperature);
  }

  /**
   * Update the temperature
   */
  double updateTempreture(double t)
  {
    return t * 0.95;
  }

  /**
   * Swap two points in the cycle and generate a neighbor
   */
  vector<Point> generateNeighbor(vector<Point> cycle)
  {
    vector<Point> neighbor = cycle;

    int i = this->randomNumber(this->size);
    int j = this->randomNumber(this->size);

    // Make sure that i and j are different
    while (j == i)
    {
      j = this->randomNumber(this->size);
    }

    // Swap points
    Point temp = neighbor.at(i);
    neighbor.at(i) = neighbor.at(j);
    neighbor.at(j) = temp;

    return neighbor;
  }

  /**
   * Print plan
   */
  void printPlan()
  {
    cout << "======= PLAN ORTHOGONAL =======" << endl
         << endl;

    for (int i = this->dimension - 1; i >= 0; i--)
    {
      cout << i << "\t";
      for (int j = 0; j < this->dimension; j++)
      {
        if (this->plan[i][j].getX() == -1)
        {
          cout << ". ";
        }
        else
        {
          cout << "o ";
        }
      }
      cout << endl;
    }
  }

  /**
   * Print cycle
   */
  void printCycle(vector<Point> cycle)
  {
    cout << endl
         << "======= CYCLE =======" << endl
         << endl;

    for (int i = 0; i < this->size; i++)
    {
      cout << "Point " << i << ": (" << cycle[i].getY() << ", " << cycle[i].getX() << ")" << endl;
    }
  }
};

int main()
{
  srand(time(NULL));

  cout << endl;
  cout << "======= SIMULATED ANNEALING FOR TSP =======" << endl
       << endl
       << endl;

  int n;

  cout << "Enter the number of points: ";
  cin >> n;

  // Create instance of TSP

  TSP tsp = TSP(30, n);

  tsp.printPlan();

  tsp.simulatedAnnealing();

  tsp.printCycle(tsp.getCycle());

  double weight = tsp.calculateWeight(tsp.getCycle());

  cout << "Final Weight: " << weight << endl;

  return 0;
}