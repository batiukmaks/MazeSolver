#include "solver.hpp"
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

enum cellState { UNVISITED = -1, IMPASSE = -2 };

bool BFS_GetPathAndShowSteps(const vector<vector<bool>> &isObstacle,
                             vector<pair<int, int>> &path, const int delay,
                             const pair<int, int> &start,
                             const pair<int, int> &end);
void addUnvisitedNeighbors(vector<vector<pair<int, int>>> &fromWhichCellVisited,
                           const vector<vector<bool>> &isObstacle,
                           deque<pair<int, int>> &newNeighbors,
                           const int currRow, const int currCol);
void swapPairs(pair<int, int> &a, pair<int, int> &b);
void printCurrentStepInMaze(
    const vector<vector<bool>> &isObstacle,
    const vector<vector<pair<int, int>>> &fromWhichCellVisited,
    const deque<pair<int, int>> &q, const int delay,
    const pair<int, int> &start, const pair<int, int> &end);

void BreadthFirstSearchAlgorithm::showPathInFile(const string filename) {
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

  BFS_GetPathAndShowSteps(isWall, path, delay_, startPoint, endPoint);
  printPathChain(path);

  file.close();
}

bool BFS_GetPathAndShowSteps(const vector<vector<bool>> &isObstacle,
                             vector<pair<int, int>> &path, const int delay,
                             const pair<int, int> &start,
                             const pair<int, int> &end) {
  int rows = isObstacle.size(), cols = isObstacle.front().size();

  // {UNVISITED, UNVISITED} - the point is not visited,
  // {IMPASSE, IMPASSE} - visited and there is no way further
  vector<vector<pair<int, int>>> fromWhichCellVisited(
      rows, vector<pair<int, int>>(cols, {UNVISITED, UNVISITED}));
  fromWhichCellVisited[start.first][start.second] = start;

  deque<pair<int, int>> currStepDeque, nextStepDeque; // queues for BFS
  currStepDeque.push_back(start);

  bool isPathFound = false;
  while (!(currStepDeque.empty() && nextStepDeque.empty()) && !isPathFound) {
    printCurrentStepInMaze(isObstacle, fromWhichCellVisited, currStepDeque,
                           delay, start, end);
    while (!currStepDeque.empty()) {
      int currRow = currStepDeque.front().first,
          currCol = currStepDeque.front().second;
      currStepDeque.pop_front();

      int beforeNewNeighbors = nextStepDeque.size();
      addUnvisitedNeighbors(fromWhichCellVisited, isObstacle, nextStepDeque,
                            currRow, currCol);
      int afterNewNeighbors = nextStepDeque.size();
      if (beforeNewNeighbors == afterNewNeighbors)
        fromWhichCellVisited[currRow][currCol] = {IMPASSE, IMPASSE};
    }

    while (!nextStepDeque.empty()) {
      currStepDeque.push_back(nextStepDeque.front());
      nextStepDeque.pop_front();
    }
    isPathFound =
        fromWhichCellVisited[end.first][end.second].first != UNVISITED;
  }

  if (!isPathFound)
    return false;
  else {
    // Restore the path
    path.push_back(end);
    while (path.back() != start)
      path.push_back(
          fromWhichCellVisited[path.back().first][path.back().second]);

    // Reverse vector
    for (int i = 0, size = path.size(), mid = size / 2; i < mid; i++)
      swapPairs(path[i], path[size - i - 1]);

    // printFinalWayInMaze(isObstacle, fromWhichCellVisited, path);
    printCurrentStepInMaze(isObstacle, fromWhichCellVisited, currStepDeque,
                           delay, start, end);
    return true;
  }
}

void addUnvisitedNeighbors(vector<vector<pair<int, int>>> &fromWhichCellVisited,
                           const vector<vector<bool>> &isObstacle,
                           deque<pair<int, int>> &newNeighbors,
                           const int currRow, const int currCol) {
  int rows = isObstacle.size(), cols = isObstacle.front().size();
  vector<pair<int, int>> neighbors = {{currRow + 1, currCol},
                                      {currRow - 1, currCol},
                                      {currRow, currCol + 1},
                                      {currRow, currCol - 1}};
  for (pair<int, int> neighbor : neighbors) {
    int neighborRow = neighbor.first, neighborCol = neighbor.second;
    if (neighborRow < 0 || neighborRow >= rows || neighborCol < 0 ||
        neighborCol >= cols)
      continue;
    bool isVisited =
        fromWhichCellVisited[neighborRow][neighborCol].first != UNVISITED;
    if (!isVisited && !isObstacle[neighborRow][neighborCol]) {
      fromWhichCellVisited[neighborRow][neighborCol] = {currRow, currCol};
      newNeighbors.push_back(neighbor);
    }
  }
}

void swapPairs(pair<int, int> &a, pair<int, int> &b) {
  pair<int, int> swapper = a;
  a = b;
  b = swapper;
}

void printCurrentStepInMaze(
    const vector<vector<bool>> &isObstacle,
    const vector<vector<pair<int, int>>> &fromWhichCellVisited,
    const deque<pair<int, int>> &q, const int delay,
    const pair<int, int> &start, const pair<int, int> &end) {
  set<pair<int, int>> path;
  int rows = isObstacle.size(), cols = isObstacle.front().size();
  bool isReachedTheEnd =
      fromWhichCellVisited[end.first][end.second].first != UNVISITED;
  if (isReachedTheEnd) {
    pair<int, int> itr = end;
    path.insert(itr);
    while (!(itr.first == 1 && itr.second == 1)) {
      itr = fromWhichCellVisited[itr.first][itr.second];
      path.insert(itr);
    }
  } else
    for (int i = 0; i < q.size(); i++)
      path.insert(q[i]);

  Sleep(delay);
  system("cls");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      pair<int, int> parent = fromWhichCellVisited[i][j];
      bool isVisited = parent.first != UNVISITED;
      bool isNoFurtherWay = parent.first == IMPASSE;
      bool isInPath = path.find(make_pair(i, j)) != path.end();
      if (make_pair(i, j) == start)
        cout << 'A'; // start point
      else if (make_pair(i, j) == end)
        cout << 'B'; // final point
      else if (isObstacle[i][j])
        cout << '#'; // walls
      else if (!isReachedTheEnd && isNoFurtherWay)
        cout << 'x'; // Surrounded by only walls or/and visited neighbors
      else if (isVisited && isInPath) { // direction from parent to child
        if (parent.first < i)
          cout << "↓";
        else if (parent.first > i)
          cout << "↑";
        else if (parent.second < j)
          cout << "→";
        else if (parent.second > j)
          cout << "←";
      } else if (isVisited)
        cout << '.';
      else if (!isVisited)
        cout << ' ';
    }
    cout << endl;
  }
}

void BreadthFirstSearchAlgorithm::printPathChain(vector<pair<int, int>> &path) {
  if (path.empty())
    cout << "There is no way from A to B." << endl;
  else {
    cout << "Path from A to B: ";
    for (pair<int, int> coord : path)
      cout << "{" << coord.first << ", " << coord.second << "} ";
    cout << endl;
  }
}

void BreadthFirstSearchAlgorithm::setDelayInSeconds(double seconds) {
  delay_ = seconds * 1000;
  cout << "Set delay to " << delay_ / 1000 << " seconds." << endl;
}