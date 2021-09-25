#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

int digits(int n)
{
	int r=0;
	while(n>0)
	{
		n/=10;
		r++;
	}
	return r;
}

int sqrt(int n)
{
	int r1=n;
	int r2=n/2;
	if (r2==0)
		r2=1;
	while(r1-r2>0)
	{
		r1 = r2;
		r2=(r1+n/r1)/2;
	}
	return r1;
}

const int rajat[] = {0,1,4,10,32,100,317,1000,3173,10000,31723};

int main()
{
	vector<string> words[15];
	FILE* filu = fopen("words.txt", "rb");
	string temp;
	while(!feof(filu))
	{
		char a;
		fread(&a, 1, 1, filu);
		switch(a)
		{
		case '"':
			break;
		case ',':
			words[temp.length()].push_back(temp);
			temp.clear();
			break;
		default:
			temp.push_back(a);
			break;
		}
	}
	fclose(filu);
	vector<pair<string,string> > anagrams;
	for(int i=1; i<=14; i++)
	{
		for(int j=0; j<words[i].size(); j++)
		{
			int luvut1[27] = {};
			for(int k=0; k<words[i][j].size(); k++)
				luvut1[words[i][j][k]-'A']++;
			for(int k=j+1; k<words[i].size(); k++)
			{
				int luvut2[27] = {};
				for(int l=0; l<words[i][k].size(); l++)
					luvut2[words[i][k][l]-'A']++;
				bool good = true;
				for(int l=0; l<27; l++)
				{
					if (luvut1[l] != luvut2[l])
						good = false;
				}
				if (good == true)
				{
					pair<string,string> a;
					a.first = words[i][j];
					a.second = words[i][k];
					anagrams.push_back(a);
				}
			}
		}
	}
	bool vie_mut_pois_taalta = false;
	int isoke=0;
	for(int i=anagrams.size()-4; i>=0; i--)
	{
		string& nyk = anagrams[i].first;
		int tamalen = nyk.length();
		int cur=0;
		for(int j=rajat[tamalen]; j<rajat[tamalen+1]; j++)
		{
			int k=j*j;
			int num[256] = {};
			for(int W=0; W<256; W++)
				num[W] = -1;
			char let[10] = {};
			for(int W=0; W<10; W++)
				let[W] = -1;
			bool cont=false;
			int laskuri=0;
			int vanha = k;
			while(k>0)
			{
				if (let[k%10] != -1 && let[k%10] != nyk[tamalen-laskuri-1])
				{
					cont = true;
					break;
				}
				if (num[nyk[tamalen-laskuri-1]] != -1)
				{
					if (num[nyk[tamalen-laskuri-1]] != k%10)
					{
						cont=true;
						break;
					}
					k/=10;
					laskuri++;
					continue;
				}
				num[nyk[tamalen-laskuri-1]] = k%10;
				let[k%10] = nyk[tamalen-laskuri-1];
				laskuri++;
				k/=10;
			}
			if (cont == true)
				continue;
			string& nyk2 = anagrams[i].second;
			int laka=0;
			for(int i=0; i<nyk2.length(); i++)
			{
				laka *= 10;
				laka += num[nyk2[i]];
			}
			if (sqrt(laka)*sqrt(laka) == laka)
			{
				if (digits(laka) == digits(vanha))
				{
					if (laka > vanha)
						isoke = laka;
					else
						isoke = vanha;
					vie_mut_pois_taalta = true;
					break;
				}
			}
			
		}
		if (vie_mut_pois_taalta == true)
			break;
	}
	cout << isoke << endl;
}