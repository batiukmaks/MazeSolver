#pragma once

#include "fileManagement.hpp"
#include <bits/stdc++.h>

class ISearchAlgorithm {
private:
  int delay_ = 1000;

public:
  virtual void showPathInFile(const std::string filename) = 0;
  virtual void setDelayInSeconds(double seconds) = 0;
};

class DepthFirstSearchAlgorithm : public ISearchAlgorithm {
private:
  int delay_ = 1000;

public:
  DepthFirstSearchAlgorithm() {}
  void showPathInFile(const std::string filename) override;
  void printPathChain(vector<pair<int, int>> &path);
  void setDelayInSeconds(double seconds) override;
};

class BreadthFirstSearchAlgorithm : public ISearchAlgorithm {
private:
  int delay_ = 1000;

public:
  BreadthFirstSearchAlgorithm() {}
  void showPathInFile(const std::string filename) override;
  void setDelayInSeconds(double seconds) override;
  void printPathChain(vector<pair<int, int>> &path);
};

class Solver {
private:
  ISearchAlgorithm *algorithm = nullptr;

public:
  Solver(ISearchAlgorithm *p_algorithm) : algorithm(p_algorithm) {}
  void showSolution(const std::string filename) {
    algorithm->showPathInFile(filename);
  }

  void setDelayInSeconds(double seconds) {
    algorithm->setDelayInSeconds(seconds);
  }
};