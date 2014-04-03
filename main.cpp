#include "tools.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

double randDouble ();
std::pair<double, double> randPoint ();
double distance (double, double, double, double);
double distance (std::pair<double, double>, std::pair<double, double>);
std::vector<std::pair<double, double> > randomGrid (int);
std::vector<std::pair<double, double> > hexGrid (int);
std::vector<std::pair<double, double> > mostlyHexGrid (int);
double solveSimple (std::vector<std::pair<double, double> >);
double solveSlow (std::vector<std::pair<double, double> >);
double solveFast (std::vector<std::pair<double, double> >);
double slowRecurse (std::vector<std::pair<double, double> > points);
double fastRecurse (std::vector<std::pair<double, double> > points);


int main () {

  std::ofstream fout ("/Users/fred.christensen/Dropbox/school/Algorithms/closest-point/results.csv");
  std::cout << "\n\n";
  fout << "Number Of Points, Random Points (Simple), Random Points (Slow), Random Points (Fast), Hex Points (Simple), Hex Points (Slow), Hex Points (Fast), Mixed Points (Simple), Mixed Points (Slow), Mixed Points (Fast)" << std::endl;
  std::cout << "Number Of Points, Random Points (Simple), Random Points (Slow), Random Points (Fast), Hex Points (Simple), Hex Points (Slow), Hex Points (Fast), Mixed Points (Simple), Mixed Points (Slow), Mixed Points (Fast)\n";

  for (int i = 2; i < pow(2, 16); i *= 2) {
    std::vector<clock_t> resRandSimple;
    std::vector<clock_t> resRandSlow;
    std::vector<clock_t> resRandFast;
    std::vector<clock_t> resHexSimple;
    std::vector<clock_t> resHexSlow;
    std::vector<clock_t> resHexFast;
    std::vector<clock_t> resMixSimple;
    std::vector<clock_t> resMixSlow;
    std::vector<clock_t> resMixFast;
      // run random points test
    for (int k = 0; k < 30; ++k) {
      auto randomPoints = randomGrid(i);
      auto hexPoints = hexGrid(i);
      auto mostlyHexPoints = mostlyHexGrid(i);

      resRandSimple.push_back( tools::funcTime ( [=] () { solveSimple(randomPoints);    } ) );
      resRandSlow.push_back(   tools::funcTime ( [=] () { solveSlow(randomPoints);      } ) );
      resRandFast.push_back(   tools::funcTime ( [=] () { solveFast(randomPoints);      } ) );
      resHexSimple.push_back(  tools::funcTime ( [=] () { solveSimple(hexPoints);       } ) );
      resHexSlow.push_back(    tools::funcTime ( [=] () { solveSlow(hexPoints);         } ) );
      resHexFast.push_back(    tools::funcTime ( [=] () { solveFast(hexPoints);         } ) );
      resMixSimple.push_back(  tools::funcTime ( [=] () { solveSimple(mostlyHexPoints); } ) );
      resMixSlow.push_back(    tools::funcTime ( [=] () { solveSlow(mostlyHexPoints);   } ) );
      resMixFast.push_back(    tools::funcTime ( [=] () { solveFast(mostlyHexPoints);   } ) );
    }
    fout << i << ", ";
    fout << tools::average(resRandSimple) << ", ";
    fout << tools::average(resRandSlow)   << ", ";
    fout << tools::average(resRandFast)   << ", ";
    fout << tools::average(resHexSimple)  << ", ";
    fout << tools::average(resHexSlow)    << ", ";
    fout << tools::average(resHexFast)    << ", ";
    fout << tools::average(resMixSimple)  << ", ";
    fout << tools::average(resMixSlow)    << ", ";
    fout << tools::average(resMixFast)    << ", ";
    fout << std::endl;

    std::cout << i << ", ";
    std::cout << tools::average(resRandSimple) << ", ";
    std::cout << tools::average(resRandSlow)   << ", ";
    std::cout << tools::average(resRandFast)   << ", ";
    std::cout << tools::average(resHexSimple)  << ", ";
    std::cout << tools::average(resHexSlow)    << ", ";
    std::cout << tools::average(resHexFast)    << ", ";
    std::cout << tools::average(resMixSimple)  << ", ";
    std::cout << tools::average(resMixSlow)    << ", ";
    std::cout << tools::average(resMixFast)    << ", ";
    std::cout << "\n";
  }

  int a = 100;
  double b = 3;
  std::cout << b / a << std::endl;
  return 0;
}


double randDouble () {
  // http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 100);
  return dis(gen);
}

std::pair<double, double> randPoint () {
  int x = randDouble();
  int y = randDouble();
  return std::make_pair(x, y);
}

std::vector<std::pair<double, double> > randomGrid (int n) {
  std::vector<std::pair<double, double> > points;
  for (auto i = 0; i < n; ++i) {
    points.push_back(randPoint());
  }
  return points;
}

std::vector<std::pair<double, double> > hexGrid (int n) {
  auto xSpace = 100.0 / sqrt(n);
  auto ySpace = sqrt(pow(xSpace, 2.0) - pow((xSpace/2.0), 2.0));

  int columns = std::floor(100.0 / xSpace);
  int rows = std::ceil((double)n / (double)columns);

  std::vector<std::pair<double, double> > points;
  for (auto i = 0; i < rows; ++i) {
    double move = ((double)(i % 2) * xSpace) / 2.0;
    for (auto j = 0; j < columns; ++j) {
      if (points.size() >= n) {
        break;
      }
      points.push_back(std::make_pair(j * xSpace + move, i * ySpace));
    }
  }
  return points;
}

std::vector<std::pair<double, double> > mostlyHexGrid (int n) {
  auto points = hexGrid ((int)(n * 0.95));
  for (auto i = points.size(); i < n; ++i) {
    points.push_back(randPoint());
  }
  return points;
}

double distance (double x1, double y1, double x2, double y2) {
  return sqrt( pow(x2-x1, 2) + pow(y2-y1, 2) );
}

double distance (std::pair<double, double> p1, std::pair<double, double> p2) {
  return distance (p1.first, p1.second, p2.first, p2.second);
}


double solveSimple (std::vector<std::pair<double, double> > points) {
  double minDistance = 999999.9;
  for (auto i = 0; i < points.size(); ++i) {
    for (auto j = i + 1; j < points.size(); ++j) {
      minDistance = std::min(minDistance, distance(points[i], points[j]));
    }
  }
  return minDistance;
}

double solveSlow (std::vector<std::pair<double, double> > points) {
  std::sort(points.begin(), points.end(), [] (std::pair<double, double> a, std::pair<double, double> b) {
    return b.first > a.first;
  });
  return slowRecurse (points);
}

double solveFast (std::vector<std::pair<double, double> > points) {
  std::sort(points.begin(), points.end(), [] (std::pair<double, double> a, std::pair<double, double> b) {
    return b.first > a.first;
  });
  return fastRecurse (points);
}

double slowRecurse (std::vector<std::pair<double, double> > points) {
  if (points.size() == 2) {
    return distance(points[0], points[1]);
  }

  std::vector<std::pair<double, double> > leftPoints;
  std::vector<std::pair<double, double> > rightPoints;
  for (auto i = 0; i < points.size()/2; ++i) {
    leftPoints.push_back(points[i]);
    rightPoints.push_back(points[i + points.size()/2]);
  }

  std::vector<std::pair<double, double> > midPoints;
  double minDist = std::min(slowRecurse(leftPoints), slowRecurse(rightPoints));
  for (auto i = leftPoints.size() -1; i > -1; --i) {
    if (distance (leftPoints[i], rightPoints[0]) < minDist) {
      midPoints.push_back(leftPoints[i]);
    } else {
      i = -1;
    }
  }

  for (auto i = 0; i < rightPoints.size(); ++i) {
    if (distance (leftPoints[leftPoints.size() -1], rightPoints[i]) < minDist) {
      midPoints.push_back(rightPoints[i]);
    } else {
      i = rightPoints.size();
    }
  }

  return std::min(minDist, solveSimple(midPoints));
}

double fastRecurse (std::vector<std::pair<double, double> > points) {
  if (points.size() == 2) {
    return distance(points[0], points[1]);
  }

  std::vector<std::pair<double, double> > leftPoints;
  std::vector<std::pair<double, double> > rightPoints;
  for (auto i = 0; i < points.size()/2; ++i) {
    leftPoints.push_back(points[i]);
    rightPoints.push_back(points[i + points.size()/2]);
  }

  std::vector<std::pair<double, double> > midPoints;
  double minDist = std::min(slowRecurse(leftPoints), slowRecurse(rightPoints));
  for (auto i = leftPoints.size() -1; i > -1; --i) {
    if (distance (leftPoints[i], rightPoints[0]) < minDist) {
      midPoints.push_back(leftPoints[i]);
    } else {
      i = -1;
    }
  }

  for (auto i = 0; i < rightPoints.size(); ++i) {
    if (distance (leftPoints[leftPoints.size() -1], rightPoints[i]) < minDist) {
      midPoints.push_back(rightPoints[i]);
    } else {
      i = rightPoints.size();
    }
  }

  std::sort(points.begin(), points.end(), [] (std::pair<double, double> a, std::pair<double, double> b) {
    return b.second > a.second;
  });

  for (auto i = 0; i < midPoints.size(); ++i) {
    for (int j = 0; j < 6 && i+j < midPoints.size(); ++i) {
      if (std::abs(midPoints[i].second - midPoints[i + j].second) < minDist) {
        minDist = std::min(distance(midPoints[i], midPoints[i + j]), minDist);
      } else {
        j = 6;
      }
    }
  }
  return minDist;
}

