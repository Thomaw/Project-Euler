class Problem75
{
  private static int max = 1000000;
  private static byte[] count = new byte[max+1];

  private static void Transform(int x, int y, int z)
  {
    int len = x+y+z;
    if(len>max) return;
    for(int l=len; l<=max; l+=len) count[l]++;
    Transform( x-2*y+2*z,  2*x-y+2*z,  2*x-2*y+3*z);
    Transform( x+2*y+2*z,  2*x+y+2*z,  2*x+2*y+3*z);
    Transform(-x+2*y+2*z, -2*x+y+2*z, -2*x+2*y+3*z);
  }

  public static void Solve()
  {
    Transform(3, 4, 5);

    int total = 0;
    for(int i=0; i<=max; i++)
      if(count[i]==1) total++;
    Console.WriteLine(total);
  }
}
