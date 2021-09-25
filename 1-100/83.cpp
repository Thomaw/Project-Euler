#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <deque>
#include <queue>
#include <utility>

typedef enum direction {
    UP, DOWN, LEFT, RIGHT, NONE
} direction_t;

typedef struct pq_entry {
    int dist;
    std::pair<int, int> coords;

    pq_entry (int y, int x, int d) : dist (dist),
                                     coords (std::make_pair (y, x))
    {}
    
    bool operator< (const pq_entry &e) const
    {
	return dist < e.dist;
    }
} pq_entry_t;

void mark_succ (int matrix [80][80], int dist [80][80], direction_t prev [80][80], std::priority_queue<pq_entry_t> &pq, direction_t from, int y, int x)
{
    int alt, succ_y, succ_x;
    switch (from)
    {
	case UP:
	succ_y = y + 1;
	succ_x = x;
	break;
	
	case DOWN:
	succ_y = y - 1;
	succ_x = x;
	break;
	
	case LEFT:
	succ_y = y;
	succ_x = x + 1;
	break;
	
	case RIGHT:
	succ_y = y;
	succ_x = x - 1;
	break;
	
	default:
	fputs ("BUG\n", stderr);
	return;
    }
    alt = dist [y][x] + matrix [succ_y][succ_x];
    if (alt < dist [succ_y][succ_x])
    {
	dist [succ_y][succ_x] = alt;
	pq.push (pq_entry (succ_y, succ_x, alt));
	prev [succ_y][succ_x] = from;
    }
}

int minimal_path_sum (int matrix [80][80])
{
    int y, x;
    std::priority_queue<pq_entry_t> pq;
    int dist [80][80];
    direction_t prev [80][80];
    
    for (int i = 0; i < 80; ++i)
	for (int j = 0; j < 80; ++j)
	{
	    dist [i][j] = INT_MAX;
	    prev [i][j] = NONE;
	}

    dist [0][0] = matrix [0][0];
    pq.push (pq_entry (0, 0, 0));
    
    do
    {
	pq_entry_t t = pq.top ();
	pq.pop ();
	y = t.coords.first;
	x = t.coords.second;
	
	if (x < 79 && prev [y][x] != RIGHT)
	    mark_succ (matrix, dist, prev, pq, LEFT, y, x);
	
	if (x > 0 && prev [y][x] != LEFT)
	    mark_succ (matrix, dist, prev, pq, RIGHT, y, x);
	
	if (y < 79 && prev [y][x] != DOWN)
	    mark_succ (matrix, dist, prev, pq, UP, y, x);
	
	if (y > 0 && prev [y][x] != UP)
	    mark_succ (matrix, dist, prev, pq, DOWN, y, x);
    } while (!pq.empty ());

    return dist [79][79];
}
    
int main ()
{
    int matrix [80][80];
    FILE *fp = fopen ("p81.txt", "r");
    if (!fp)
    {
	perror ("open");
	exit (1);
    }
    
    for (int i = 0; i < 80; ++i)
	for (int j = 0; j < 80; ++j)
	{
	    char ch;
	    while (!isdigit (ch = fgetc (fp)));
	    matrix [i][j] = ch - '0';
	    while (isdigit (ch = fgetc (fp)))
	    {
		matrix [i][j] *= 10;
		matrix [i][j] += ch - '0';
	    }
	}
    
    fclose (fp);
    
    printf ("Answer: %d\n", minimal_path_sum (matrix));
    return 0;
}