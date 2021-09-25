#include <iostream>
const int N = 30, M = 30, T = 50;
double p[N][M][N][M],q[N][M][N][M],edges[N][M];
void print_expectation (int step) {
	double expected_blanks = 0.0;
	int x,y,i,j;
	for (i=0;i<N;++i) for (j=0;j<M;++j) {
		double prob_ij_cell_is_blank = 1.0;
		for (x=0;x<N;++x) for (y=0;y<M;++y) {
			prob_ij_cell_is_blank *= (1.0 - p[x][y][i][j]);
		}
		expected_blanks += prob_ij_cell_is_blank;
	}
	printf("Expected number of blank squares after %d steps: %.06f\n",step,expected_blanks);
}
void step_grid (void) {
	int x,y,i,j;
	for (x=0;x<N;++x) for (y=0;y<M;++y)
		for (i=0;i<N;++i) for (j=0;j<M;++j) q[x][y][i][j]=0.0;
	for (x=0;x<N;++x) for (y=0;y<M;++y) {
		for (i=0;i<N;++i) for (j=0;j<M;++j) {
			if (i>0) q[x][y][i-1][j] += p[x][y][i][j]/edges[i][j];
			if (j>0) q[x][y][i][j-1] += p[x][y][i][j]/edges[i][j];
			if (i+1<N) q[x][y][i+1][j] += p[x][y][i][j]/edges[i][j];
			if (j+1<M) q[x][y][i][j+1] += p[x][y][i][j]/edges[i][j];
		}
	}
	for (x=0;x<N;++x) for (y=0;y<M;++y)
		for (i=0;i<N;++i) for (j=0;j<M;++j) p[x][y][i][j]=q[x][y][i][j];
}
int main(void) {
	int x,y,i,j;
	for (x=0;x<N;++x) for (y=0;y<M;++y) {
		edges[x][y]=0.0;
		if (x>0) edges[x][y]+=1.0;
		if (y>0) edges[x][y]+=1.0;
		if (x+1<N) edges[x][y]+=1.0;
		if (y+1<M) edges[x][y]+=1.0;
	}
	for (x=0;x<N;++x) for (y=0;y<M;++y)
		for (i=0;i<N;++i) for (j=0;j<M;++j) p[x][y][i][j]=0.0;
	for (x=0;x<N;++x) for (y=0;y<M;++y) p[x][y][x][y]=1.0;
	print_expectation(0);
	int step;
	for (step=1;step<=T;++step) {
		step_grid();
		print_expectation(step);
	}
}
