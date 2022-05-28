#include "di.hpp"
#include "menu.hpp"
#include "solver.hpp"
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;
namespace di = boost::di;

int main() {
  system("chcp 65001");

  while (true) {
    int choice;
    cout << "########## MENU ##########" << endl;
    cout << "0. Exit" << endl;
    cout << "1. Solve a maze" << endl;
    cout << "Choice: ";
    cin >> choice;

    if (choice == Menu::EXIT) {
      return 0;
    } else if (choice == 1) {
      if (Menu::solveMaze() == Menu::EXIT) {
        return 0;
      }
    }
  }

  return 0;
}