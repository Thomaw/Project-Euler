#include <iostream>
#include <gmp.h>
#include <fstream>

using namespace std;

long stoi( const char *digit) 
{
	long result = 0;
	
	while (*digit >= '0' && *digit <='9') 
		result = (result * 10) + (*digit++ - '0');
   
	return result;
}

int main()
{
	mpz_t largest, base, exp, result, remainder;
	mpz_init(largest);
	mpz_init(base);
	mpz_init(exp);
	mpz_init(result);
	mpz_init(remainder);
	mpz_init_set_ui(largest,0);
	
	string line1, line2;
	
	int line=0, biggest;
	
	ifstream f("base_exp2.txt"); 
	
	while(getline(f,line1) && getline(f,line2) && ++line)
	{
		long i1 = stoi(line1.c_str());
		long i2 = stoi(line2.c_str());
		
		cout << "checking line " << line << " ..." << endl;
		
		mpz_set_ui(base,i1);
		mpz_set_ui(exp,i2);
		mpz_set_ui(result,1);
		
		while (mpz_cmp_ui(exp,0) != 0)
		{
			if (mpz_mod_ui(remainder,exp,2) == 1)
			{
				mpz_mul(result,result,base);
				mpz_sub_ui(exp,exp,1);
			}
			
			if (mpz_cmp_ui(exp,0) > 0)
			{
				mpz_mul(base,base,base);
				mpz_div_ui(exp,exp,2);
			}
		}
			
		
		if (mpz_cmp(result,largest) > 0)
		{
			mpz_set(largest,result);
			biggest = line;
			cout << endl << "found new largest number on line " << line << "!" << endl << endl;
		}
	}
	
	cout << biggest << endl;
}