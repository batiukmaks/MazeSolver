#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "di.hpp"
namespace di = boost::di;

namespace Menu {
int solveMaze();
int getAlgorithm();
int getActionToTheSolver();
void printExitMessage();

enum choices { EXIT = 0, DFS, BFS };

int solveMaze() {
  int algorithm = getAlgorithm();
  if (algorithm == EXIT)
    return 0;

  auto injector = di::make_injector(di::bind<ISearchAlgorithm>().to(
      [&](const auto &injector) -> ISearchAlgorithm * {
        if (algorithm == DFS)
          return injector.template create<DepthFirstSearchAlgorithm *>();
        else if (algorithm == BFS)
          return injector.template create<BreadthFirstSearchAlgorithm *>();
      }));
  auto solver = injector.create<Solver>();

  while (true) {
    int action = getActionToTheSolver();
    switch (action) {
    case EXIT:
      return EXIT;
    case 1: {
      cout << "Enter the filename: ";
      string filename;
      cin >> filename;
      solver.showSolution(filename);
      return algorithm;
    }
    case 2: {
      cout << "Enter the delay in seconds: ";
      double seconds;
      cin >> seconds;
      solver.setDelayInSeconds(seconds);
    }
    }
  }
}

int getAlgorithm() {
  int choice;
  do {
    system("cls");
    cout << "########## MENU ##########" << endl;
    cout << "Choose the algorithm:" << endl;
    cout << "0. Exit" << endl;
    cout << "1. DFS" << endl;
    cout << "2. BFS" << endl;
    cout << "Choice: ";
    cin >> choice;
  } while (!(choice >= EXIT && choice <= BFS));
  return choice;
}

int getActionToTheSolver() {
  int choice;
  do {
    system("cls");
    cout << "########## MENU ##########" << endl;
    cout << "0. Exit" << endl;
    cout << "1. Solve a maze" << endl;
    cout << "2. Set delay" << endl;
    cout << "Choice: ";
    cin >> choice;
  } while (!(choice >= 0 && choice <= 2));
  return choice;
}

} 