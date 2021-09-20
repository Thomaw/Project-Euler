int sum_of_divisors(int num)
{
    int sum=1;
    for(int i=2; i*i<=num; sum+=num%i?0:(i*i==num?i:i+num/i) ,i++);
    return sum;
}
