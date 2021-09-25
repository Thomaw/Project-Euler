#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
  vector< vector<int> > courses;
  vector<int> bricks, joints;
  for(int twos = 1; twos <= 16; twos += 3) {
    bricks.clear();
    for(int i = 0; i < twos; ++i) bricks.push_back(2);
    for(int i = 0; i < (32 - 2*twos)/3; ++i) bricks.push_back(3);
    
    do {
      joints.clear();
      for(int i = 0, j = 0; i < bricks.size() - 1; ++i) joints.push_back(j += bricks[i]);
      courses.push_back(joints);
    } while (next_permutation(bricks.begin(), bricks.end()));
  }
  cout << courses.size() << " courses" << endl;
    
  int adjacencies = 0;
  vector< vector<int> > adjacent(courses.size());
  for(int i = 0; i < courses.size(); ++i) {
    for(int j = 0; j < courses.size(); ++j) {
      vector<int>::const_iterator ip = courses[i].begin(), jp = courses[j].begin();
      bool ok = true;
      while (ip != courses[i].end() && jp != courses[j].end()) {
        if (*ip < *jp) { ++ip; }
        else if (*ip > *jp) { ++jp; }
        else { ok = false; break; }
      }
      if (ok) { adjacent[i].push_back(j); ++adjacencies; }
    }
  }
  cout << adjacencies << " adjacencies" << endl;
  
  vector< vector<unsigned long long> > walls(10);
  walls[1].resize(courses.size()); for(int i = 0; i < courses.size(); ++i) {
    walls[1][i] = adjacent[i].size();
  }
  for(int layer = 2; layer < 10; ++layer) {
    unsigned long long total = 0;
    walls[layer].resize(courses.size());
    for(int i = 0; i < courses.size(); ++i) {
      walls[layer][i] = 0;
      for(int j = 0; j < adjacent[i].size(); ++j) {
        walls[layer][i] += walls[layer - 1][adjacent[i][j]];
      }
      total += walls[layer][i];
    }
    cout << total << " walls of height " << (layer + 1) << endl;
  }

  return 0;
}