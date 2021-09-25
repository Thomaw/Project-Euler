int board[40];
int cnt = 0;
int pos = 0;
int lika = 0;

while(cnt < 10000000)
{
	int d1 = (rand_lim(3)+1);
	int d2 = (rand_lim(3)+1);

	pos += (d1 + d2);
	if(pos > 39) pos -= 40;

	if(d1 == d2) lika++;
	else lika = 0;

	if(pos == 2 || pos == 17 || pos == 33)
	{
		int r = rand_lim(15)+1;

		if(r == 1) pos = 0;
		if(r == 2) pos = 10;
	}

	if(pos == 7 || pos == 22 || pos == 36)
	{
		int r = rand_lim(15)+1;

		if(r == 1) pos = 0;
		if(r == 2) pos = 10;
		if(r == 3) pos = 11;
		if(r == 4) pos = 24;
		if(r == 5) pos = 39;
		if(r == 6) pos = 5;

		if(r == 7 || r == 8)
		{
			if(pos == 7) pos = 15;
			if(pos == 22) pos = 25;
			if(pos == 36) pos = 5;
		}

		if(r == 9)
		{
			if(pos == 7) pos = 12;
			if(pos == 22) pos = 28;
			if(pos == 36) pos = 12;
		}

		if(r == 10) pos -= 3;
	}

	if(pos == 30 || lika == 3) pos = 10;

	board[pos]++;
	cnt++;
}

for(int i = 0; i < 40; i++)
{
	if(board[i] > 300000)
		cout << i << " " << board[i] << endl;
}