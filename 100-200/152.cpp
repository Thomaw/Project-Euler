#include "stdafx.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

int InverseMod(int arg, int mod)
{
	for (int i = 1; i < mod; i++)
		if ((i*arg)%mod==1)
			return i;
	throw "not inversible";
	return -1;
}

bool NextPos(vector<char>& v)
{
	int size = v.size();
	for (int pos = 0; pos < size; pos++)
	{
		if (v[pos] == '0')
		{
			for(int pos2 = 0; pos2 < pos; pos2++)
				if (v[pos2]=='1') v[pos2]='0';
			v[pos]='1';
			return true;
		}
	}
	return false;
}

int N = 80;

vector<char> Init(const vector<char>& thetemplate,int prime)
{
	vector<char> v = thetemplate;
	for (int pos = 0; pos <= N; pos++)
	{
		if (v[pos]=='1')
			v[pos]='I';
		else if (v[pos]=='0')
			v[pos]='O';
	}
	for (int pos = prime; pos <=N; pos+=prime)
		if (v[pos] == '?') 
			v[pos] = '0';
	return v;
}

int NextPrime(int prime)
{
	static int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};
	int *pprime = find<int*,int>(primes,primes+22,prime);
	return *(--pprime);
}

map<int,int> primepowmap;
map<int,vector<int> > primefactsmap;

void InitMaps(int prime)
{
	int primepow = prime;
	while (primepow < N) primepow *= prime;
	primepow /= prime;
	primepow *= primepow;
	primepowmap[prime] = primepow;
	for (int mul = prime; mul <= N; mul += prime)
	{
		int a = primepow;
		int b = mul*mul;
		while (b%prime==0)
		{
			a/= prime;
			b/= prime;
		}
		primefactsmap[prime].push_back((a*InverseMod(b,primepow))%primepow);
	}
}


int Ways(int prime, const vector<char>& fixed)
{
	int count = 0;
	if (prime == 2)
	{
		vector<char> v = Init(fixed,2);
		for (bool proceed = true; proceed; proceed=NextPos(v))
		{
			double res = 0.5;
			for (int i = 2; i <= N; i++)
				if (v[i] == 'I' || v[i] == '1')
					res -= 1.0/i/i;
			if (res < 1.e-10 && res > -1.e-10)
			{
				count++;
				for (int i = 2; i <= N; i++)
				if (v[i] == 'I' || v[i] == '1')
					cout << i << " ";
				cout << endl;
			}
		}
		return count;
	}

	map<int,int>::iterator it = primepowmap.find(prime);
	if (it == primepowmap.end())
	{
		InitMaps(prime);
		it = primepowmap.find(prime);
	}
	int primepow = it->second;
	vector<int>& facts = primefactsmap[prime];
	vector<char> v = Init(fixed,prime);
	int nextPrime = NextPrime(prime);
	for (bool proceed = true; proceed; proceed=NextPos(v))
	{
		int res = 0;
		for (int index = 0, mul = prime; mul <= N;mul+=prime,index++)
			if(v[mul]=='I' || v[mul] == '1')
				res += facts[index];
		if (res % primepow == 0)
			count += Ways(nextPrime,v);
	}
	return count;
}



int _tmain(int argc, _TCHAR* argv[])
{
	vector<char> fixed(N+2,'?');
	fixed[0]=fixed[1]='O';
	//cout << Ways(43,fixed);
	cout << Ways(79,fixed);
	cin.get();
	return 0;
}