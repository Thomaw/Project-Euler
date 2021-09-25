int next(int n)
{
  int result = 0;
  while ( n )
    result += (n%10)*(n%10), n /= 10;
  return result;
}

int main()
{
  int result = 0;
  for ( int start = 1; start < 10000000; ++start )
    {
      int curr = start;
      while ( curr != 1 && curr != 89 )
        curr = next(curr);
      result += curr == 89;
    }
  std::cout << result << std::endl;
  return 0;
}