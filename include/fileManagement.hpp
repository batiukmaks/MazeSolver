#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace FileManagement {
bool isFileExist(string filename);
bool getFile(string filename, ifstream &file);
void getMaze(ifstream &file, vector<vector<bool>> &arr, pair<int, int> &start,
             pair<int, int> &end);
} // namespace FileManagement
