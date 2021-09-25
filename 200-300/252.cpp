#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int * S;
void setupS(){
  printf("Setting up S\n");
  S = new int[2001];
  S[0] = 290797;
  for (int i = 0; i < 2000; ++i){
    long long l = S[i];
    l *= l;
    l %= 50515093;
    S[i+1] = l;
    if (i < 10)
      printf("S[%d] = %d\n", i+1, S[i+1]);
  }
}

int ** T;
void setupT(){
  printf("Setting up T\n");
  T = new int*[500];
  for (int i = 0; i < 500; ++i){
    T[i] = new int[2];
    T[i][0] = (S[2*i+1] % 2000) - 1000;
    T[i][1] = (S[2*i+2] % 2000) - 1000;
    if (i < 10)
      printf("T[%d] = [%d, %d]\n", i+1, T[i][0], T[i][1]);
  }
}

int *** ars;
bool *** cvx;
void setupars(){
  ars = new int**[500];
  cvx = new bool**[500];
  for (int i = 0; i < 500; ++i){
    ars[i] = new int*[i];
    cvx[i] = new bool*[i];
    for (int j = 0; j < i; ++j){
      ars[i][j] = new int[j];
      cvx[i][j] = new bool[j];
      for (int k = 0; k < j; ++k){
	ars[i][j][k] = -1;
	cvx[i][j][k] = false;
      }
    }
  }
}

int area(int i, int j, int k){
  if (i == j) return 0;
  if (i == k) return 0;
  if (j == k) return 0;
  if (i < j){
    int l = i; i = j; j = l;
  }
  if (i < k){
    int l = i; i = k; k = l;
  }
  if (j < k){
    int l = j; j = k; k = l;
  }
  if (ars[i][j][k] == -1){
    int x0 = T[j][0]-T[i][0];
    int x1 = T[k][0]-T[i][0];
    int y0 = T[j][1]-T[i][1];
    int y1 = T[k][1]-T[i][1];
    ars[i][j][k] = (x1 * y0 - y1 * x0);
    if (ars[i][j][k] < 0)
      ars[i][j][k] = -ars[i][j][k];
  }
  return ars[i][j][k];
}

int findarea(int* x, int lev){
  vector<pair<int, int> > pts;
  for (int i = 0; i <= lev; ++i)
    pts.push_back(make_pair(T[x[i]][0],T[x[i]][1]));
  sort(pts.begin(),pts.end());
  for (int i = 1; i <= lev; ++i)
    pts[i] = make_pair(pts[i].first-pts[0].first, pts[i].second-pts[0].second);
  pts[0] = make_pair(0,0);
  vector<pair<int, int> > ptsInOrder;
  vector<pair<int, int> > ptsInReverseOrder;
  ptsInOrder.push_back(pts[0]);
  ptsInOrder.push_back(pts[0]);
  bool upStart = false;
  bool downStart = false;
  for (int i = 1; i < lev; ++i){
    int mdeterm = (pts[i].first*pts[lev].second) - (pts[i].second*pts[lev].first);
    if (mdeterm > 0)
      upStart = true;
    if (mdeterm < 0)
      downStart = true;
  }
  for (int i = 1; i < lev; ++i){
    int mdeterm = (pts[i].first*pts[lev].second) - (pts[i].second*pts[lev].first);
    if (mdeterm > 0)
      ptsInOrder.push_back(pts[i]);
    else
      if (mdeterm < 0)
	ptsInReverseOrder.push_back(pts[i]);
      else
	if (!downStart)
	  ptsInReverseOrder.push_back(pts[i]);
	else
	  if (!upStart)
	    ptsInReverseOrder.push_back(pts[i]);
	  else
	    printf("Alert!\n");
  }
  ptsInOrder.push_back(pts[lev]);
  ptsInReverseOrder.push_back(pts[lev]);
  int ar = 0;
  for (int i = 0; i + 1 < ptsInOrder.size(); ++i){
    ar += ptsInOrder[i].first * ptsInOrder[i+1].second;
    ar -= ptsInOrder[i].second * ptsInOrder[i+1].first;
  }
  for (int i = 0; i + 1 < ptsInReverseOrder.size(); ++i){
    ar -= ptsInReverseOrder[i].first  * ptsInReverseOrder[i+1].second;
    ar += ptsInReverseOrder[i].second * ptsInReverseOrder[i+1].first;
  }
  return (ar > 0) ? ar : -ar;
}

int main(){
  setupS();
  setupT();
  ofstream z;
  z.open("d:\\dummy.txt");
  for (int i = 0; i < 500; ++i)
    z << T[i][0] << " " << T[i][1] << endl;
  z.close();
  setupars();
  int* x2 = new int[4];
  x2[0] = 7; x2[1] = 44; x2[2] = 121; x2[3] = 331;
  int N = 500;
  int numtris = 0;
  int recar = 0;
  int reca = -1;
  int recb = -1;
  int recc = -1;
  for (int a = 0; a < N-2; ++a)
    for (int b = a+1; b < N-1; ++b)
      for (int c = b+1; c < N; ++c){
	int ar = area(a,b,c);
	//	printf("Triangle [%d,%d,%d] has area %d\n", a, b, c, ar);
	bool gd = true;
	for (int d = 0; d < N; ++d){
	  int ar1 = area(a,b,d);
	  int ar2 = area(a,c,d);
	  int ar3 = area(b,c,d);
	  if (ar1 > 0 and ar2 > 0 and ar3 > 0 and ar == ar1+ar2+ar3){
	    gd = false;
	    break;
	  }
	}
	if (gd){
	  ++numtris;
	  cvx[c][b][a] = true;
	  if (recar < ar){
	    recar = ar; reca = a; recb = b; recc = c;
	    printf("%.2f: [%d,%d,%d]\n", (recar+0.0)/2, reca,recb,recc);
	  }
	}
      }
  printf("%d triangles found\n", numtris);
  printf("Right. Let's get started on quadrilaterals\n");
  int numquads = 0;
  int numpents = 0;
  int recd = -1;
  int x[500];
  int y[500];
  for (int i = 0; i  < 500; ++i)
    y[i] = 0;
  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  int lev = 2;
  while (x[0] < N-2){
    bool ok = x[lev] < N;
    for (int i = 0; ok && (i < lev-1); ++i){
      for (int j = i+1; ok && (j < lev); ++j){
	ok = cvx[x[lev]][x[j]][x[i]];
      }
    }
    if (ok){
      if (lev >= 2){
	int ar = findarea(x,lev);
	if (ar > recar){
	  recar = ar;
	  printf("%.2f: [", (recar+0.0)/2);
	  for (int i = 0; i <= lev; ++i){
	    printf("%d",x[i]);
	    if (i != lev)
	      printf(",");
	  }
	  printf("]\n");
	}
      }
      ++y[lev];
      x[lev+1] = x[lev]+1;
      ++lev;
    } else {
      if (x[lev] == 500)
	--lev;
      ++x[lev];
    }    
  }
  for (int i = 3; i < 20; ++i){
    printf("%d polygons with %d vertices found\n", y[i], i);
  }
}