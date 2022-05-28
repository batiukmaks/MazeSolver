#include "solver.hpp"
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

void DFS_Starter(vector<vector<bool>> &isObstacle, vector<pair<int, int>> &path,
                 const int delay, const pair<int, int> &start,
                 const pair<int, int> &end);
bool DFS_GetPathAndShowSteps(vector<vector<bool>> &isObstacle,
                             vector<vector<bool>> &isVisited,
                             vector<pair<int, int>> &path, const int delay,
                             const pair<int, int> &start,
                             const pair<int, int> &end);
void printCurrentProgress(vector<vector<bool>> &isObstacle,
                          vector<vector<bool>> &isVisited,
                          vector<pair<int, int>> &path, const int delay,
                          const pair<int, int> &start,
                          const pair<int, int> &end);

void DepthFirstSearchAlgorithm::showPathInFile(string filename) {
  ifstream file;
  bool fileOpened = FileManagement::getFile(filename, file);
  if (!fileOpened) {
    cout << "Cannot open the file!" << endl;
    return;
  }

  vector<vector<bool>> isWall;
  pair<int, int> startPoint = {-1, -1}, endPoint = {-1, -1};
  FileManagement::getMaze(file, isWall, startPoint, endPoint);

  vector<pair<int, int>> path;
  DFS_Starter(isWall, path, delay_, startPoint, endPoint);

  printPathChain(path);
  file.close();
}

void DFS_Starter(vector<vector<bool>> &isObstacle, vector<pair<int, int>> &path,
                 const int delay, const pair<int, int> &start,
                 const pair<int, int> &end) {
  vector<vector<bool>> isVisited(isObstacle.size(),
                                 vector<bool>(isObstacle.front().size()));
  path.push_back(start);

  bool isWay =
      DFS_GetPathAndShowSteps(isObstacle, isVisited, path, delay, start, end);
  if (!isWay)
    path.clear();
}

bool DFS_GetPathAndShowSteps(vector<vector<bool>> &isObstacle,
                             vector<vector<bool>> &isVisited,
                             vector<pair<int, int>> &path, const int delay,
                             const pair<int, int> &start,
                             const pair<int, int> &end) {
  printCurrentProgress(isObstacle, isVisited, path, delay, start, end);
  int rows = isObstacle.size(), cols = isObstacle.front().size();
  int row = path.back().first, col = path.back().second;

  if (row < 0 || row >= rows || col < 0 || col >= cols)
    return false;
  isVisited[row][col] = true;
  if (make_pair(row, col) == end)
    return true;

  vector<pair<int, int>> neighbors = {
      {row - 1, col}, {row, col + 1}, {row + 1, col}, {row, col - 1}};
  for (pair<int, int> neighbor : neighbors) {
    int neighborRow = neighbor.first, neighborCol = neighbor.second;
    if (isVisited[neighborRow][neighborCol] ||
        isObstacle[neighborRow][neighborCol])
      continue;
    path.push_back(neighbor);
    bool reachedTheEnd =
        DFS_GetPathAndShowSteps(isObstacle, isVisited, path, delay, start, end);
    if (!reachedTheEnd) {
      path.pop_back();
      printCurrentProgress(isObstacle, isVisited, path, delay, start, end);
    } else {
      if (make_pair(row, col) == start)
        printCurrentProgress(isObstacle, isVisited, path, delay, start, end);
      return true;
    }
  }
  return false;
}

void printCurrentProgress(vector<vector<bool>> &isObstacle,
                          vector<vector<bool>> &isVisited,
                          vector<pair<int, int>> &path, const int delay,
                          const pair<int, int> &start,
                          const pair<int, int> &end) {
  Sleep(delay);
  system("cls");

  int rows = isObstacle.size(), cols = isObstacle.front().size();
  bool foundPath = path.back() == make_pair(rows - 2, cols - 2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      auto itr = find(path.begin(), path.end(), make_pair(i, j));
      if (make_pair(i, j) == start)
        cout << 'A';
      else if (make_pair(i, j) == end)
        cout << 'B';
      else if (isObstacle[i][j])
        cout << '#';
      else if (isVisited[i][j] && itr == path.end())
        cout << 'x';
      else if (isVisited[i][j] && itr != path.end()) {
        if ((*(itr - 1)).first < (*itr).first)
          cout << "↓";
        else if ((*(itr - 1)).first > (*itr).first)
          cout << "↑";
        else if ((*(itr - 1)).second < (*itr).second)
          cout << "→";
        else if ((*(itr - 1)).second > (*itr).second)
          cout << "←";
      } else
        cout << ' ';
    }
    cout << endl;
  }
}

void DepthFirstSearchAlgorithm::printPathChain(vector<pair<int, int>> &path) {
  if (path.empty())
    cout << "There is no way from A to B." << endl;
  else {
    cout << "Path from A to B: ";
    for (pair<int, int> coord : path)
      cout << "{" << coord.first << ", " << coord.second << "} ";
    cout << endl;
  }
}

void DepthFirstSearchAlgorithm::setDelayInSeconds(double seconds) {
  delay_ = seconds * 1000;
}
