#include <stdio.h>
#include <math.h>

#define LEN 100

char mapa[2*LEN + 1][2*LEN + 1];
int hx = 0, hy = 0, cnt = 0;
char hdir = 'U'; // U/D/L/R

char get_mapa(int f, int c) {
	return mapa[f + LEN][c + LEN];
}
void set_mapa(int f, int c, char ch) {
	mapa[f + LEN][c + LEN] = ch;
}

void show() {
	int f,c;
	for(f = -LEN ; f <= LEN ; f ++) {
		for(c = -LEN ; c <= LEN ; c ++) {
			printf("%c", get_mapa(f,c));
		}
		putchar('\n');
	}
}

void paso() {
	if(get_mapa(hx, hy) == '.') {
		set_mapa(hx, hy, '#');
		cnt ++;
		switch(hdir) {
			case 'U': hdir = 'L'; break;
			case 'L': hdir = 'D'; break;
			case 'D': hdir = 'R'; break;
			case 'R': hdir = 'U'; break;
		}
	} else {
		set_mapa(hx, hy, '.');
		cnt --;
		switch(hdir) {
			case 'U': hdir = 'R'; break;
			case 'R': hdir = 'D'; break;
			case 'D': hdir = 'L'; break;
			case 'L': hdir = 'U'; break;
		}
	}
	switch(hdir) {
		case 'U': hy ++; break;
		case 'L': hx ++; break;
		case 'D': hy --; break;
		case 'R': hx --; break;
	}
}

main() {

	int f,c,p;
	for(f = -LEN ; f <= LEN ; f ++) {
		for(c = -LEN ; c <= LEN ; c ++) {
			set_mapa(f,c,'.');
		}	
	}
	//show();
	for(p = 1 ; p < 12700 ; p ++) {
		paso();
			//show();
			printf("%d %d\n", p, cnt);
			//getchar();
	}
}