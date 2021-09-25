int total = 0;
for(int j=2; j<100; j++)
{
    if(Math.Sqrt(j)==(int)Math.Sqrt(j)) continue;
    string tmp = j.ToString();
    for(int i=0; i<100; i++) tmp += "00";
    BigInteger n = new BigInteger(tmp, 10);
    n = n.sqrt();
    string s = n.ToString();
    int sum = 0;
    for(int i=0; i<100; i++)
    {
        sum += int.Parse(s.Substring(0,1));
        s = s.Substring(1);
    }
    total += sum;
}
Console.WriteLine(total);