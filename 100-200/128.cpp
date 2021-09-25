void Problem128()
{
    long long i,z[16],k=6,kstart=3;

    //count=2 because 1 and 2 have pd=3
    int s,pd,count=2;

    for (i=3;count<2000;i++)
    {
        //new layer, calculate if differences are prime
        if (i==k+kstart) {

            kstart=i;
            k+=6;

            z[1 ]=k-1;
            z[2 ]=1; //k-2; is never prime (k%6==0)
            z[3 ]=k-3;
            z[4 ]=1; //k-4; is never prime (k%6==0)
            z[5 ]=1; //k-5; never used in relevant cases
            z[6 ]=1; //k-6; is never prime (k%6==0)
            z[7 ]=1; //k-7; never used in relevant cases
            z[8 ]=k+1;
            z[9 ]=1; //k+2; is never prime (k%6==0)
            z[10]=k+3;
            z[11]=1; //k+4; is never prime (k%6==0)
            z[12]=k+5;
            z[13]=1; //k+6; is never prime (k%6==0)
            z[14]=k+k+5;
            z[15]=k+k-7;
            for (s=1;s<16;s++)
            {
            	if (isprime(z[s]))
                    z[s]=1;
                else
                    z[s]=0;
            }
            pd = z[1 ] + z[6 ] + z[14] + z[8 ];
        }
        else if (i==kstart+k/2)     { pd = z[9 ] + z[10] + z[3 ] + z[12]; }
        else if (i==kstart+k-1)     { pd = z[1 ] + z[12] + z[13] + z[15]; }
        else pd=0;

        if (pd==3)
        {
            count ++;
            cout << i-1 << " " << count << endl;
        }
    }
}