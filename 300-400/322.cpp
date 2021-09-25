// Count how many are *not* divisible by d
static long doit_one(long m, long n, long d)
{
    long count=0;
    
    long den2=n;
    long da=factors_in_factorial(den2,d);

    for (long i=n;i<m;i++)
    {
        long num=i;
        long den1=i-n;
        
        long n2=factors_in_factorial(num,d);
        long d2=factors_in_factorial(den1,d)+da;

        if (n2>d2)
        {
            long k2=n2-d2;
            long nk2=1;
            
            while (k2>0 && nk2<(m-n)/d)
            {
                nk2*=d;
                if (den1%nk2>num%nk2)
                    k2--;
            }

            long den1r2;
            
            den1r2=den1%nk2;
            long den1_2=den1+(nk2-den1r2);
            den1_2=min(den1_2,m-n);
            
            long skip=den1_2-den1;
            // Check for periodic behaviour
            if (skip==n)
            {
                long mul=(m-n)/den1_2;
                den1_2=mul*den1_2;
                skip=den1_2-den1;
                count*=mul;
            }
            i+=skip-1; // the last 1 is in the "i++"
        }
        else
        {
            long k2=n2-d2;
            long nk2=1;
            
            while (k2<=0 && nk2<(m-n)/d)
            {
                nk2*=d;
                if (den1%nk2<num%nk2)
                    k2++;
            }

            long numr2;
            numr2=num%nk2;

            long num_2=num+(nk2-numr2);
            num_2=min(num_2,m);
            
            long skip=num_2-num;

            i+=skip-1; // the last 1 is in the "i++"
            count+=skip;
        }
    }
    return count;
}

static long doit_both(long m, long n)
{
    long count=0;
    
    long den2=n;
    long d2a=factors_in_factorial(den2,2);
    long d5a=factors_in_factorial(den2,5);
    for (long i=n;i<m;i++)
    {
        long num=i;
        long den1=i-n;
        
        long n2=factors_in_factorial(num,2);
        long n5=factors_in_factorial(num,5);
        long d2=factors_in_factorial(den1,2)+d2a;
        long d5=factors_in_factorial(den1,5)+d5a;
        

        if (n2>d2 && n5>d5)
        {
            long k2=n2-d2;
            long k5=n5-d5;
            
            long nk2=1;
            
            while (k2>0 && nk2<(m-n)/2)
            {
                nk2*=2;
                if (den1%nk2>num%nk2)
                    k2--;
            }

            long nk5=1;
            
            while (k5>0 && nk5<(m-n)/5)
            {
                nk5*=5;
                if (den1%nk5>num%nk5)
                    k5--;
            }

            long den1r2;
            long den1r5;
            
            den1r2=den1%nk2;
            den1r5=den1%nk5;

            

            long den1_2=den1+(nk2-den1r2);
            long den1_5=den1+(nk5-den1r5);
            long den1_min=max(den1_2,den1_5);
            den1_min=min(den1_min,m-n);
            
            long skip=den1_min-den1;
            i+=skip-1; // the last 1 is in the "i++"
        }
        else
        {
            long k2=n2-d2;
            long k5=n5-d5;

            if (k2==0 && k5==0)
                count++;
        }
        
    }
    return count;
}

int main(int argc, char** argv)
{
    long mp=atol(argv[1]);
    long np=atol(argv[2]);

    long m=1;
    long n=1;

    for (long i=0;i<mp;i++)
        m*=10;
    for (long i=0;i<np;i++)
        n*=10;

    n-=10;
    
    long a2=doit_one(m,n,2);
    long a5=doit_one(m,n,5);
    long ab=doit_both(m,n);
    long answer=m-n-(a5+a2-ab);
    
    
    printf("answer is %ld\n",answer);
}