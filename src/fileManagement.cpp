#include "fileManagement.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace FileManagement {
bool isFileExist(string filename) {
  ifstream f(filename.c_str());
  return f.is_open();
}

bool getFile(string filename, ifstream &file) {
  bool fileExists = isFileExist(filename);
  if (!fileExists)
    return false;
  else {
    file.open(filename.c_str());
    return true;
  }
}

void getMaze(ifstream &file, vector<vector<bool>> &arr, pair<int, int> &start,
             pair<int, int> &end) {
  string currLine;
  int row = 0, col = 0;
  while (getline(file, currLine)) {
    col = 0;
    arr.push_back({});
    while (col < currLine.size()) {
      if (currLine[col] == '#')
        arr.back().push_back(true);
      else
        arr.back().push_back(false);

      if (currLine[col] == 'A')
        start = {row, col};
      if (currLine[col] == 'B')
        end = {row, col};
      col++;
    }
    row++;
  }
  if (start.first == -1)
    start = {1, 1};
  if (end.first == -1)
    end = {row - 2, col - 2};
}
} // namespace FileManagement