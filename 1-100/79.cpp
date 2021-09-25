class Problem79
{
    static int[] log = {319,680,...,716};

    public static void Solve()
    {
        string s = log[0].ToString();
        for(int i=1; i&lt;log.Length; i++)
        {
            string s2 = log[i].ToString();

            if(s[0]==s2[2])
                // prepend s2
                s = s2 + s.Substring(1);
            else if(s[s.Length-1]==s2[0])
                // append s2
                s += s2.Substring(0,2);
            else if(s.Substring(0,2)==s2.Substring(1))
                // prepend first digit of s2
                s = s2[0] + s;
            else if(s.Substring(s.Length-2)==s2.Substring(0,2))
                // append last digit of s2
                s += s2[2];
            else
                // insert middle digit of s2
                s = s.Replace(s2[0]+""+s2[2], s2);
        }
        Console.WriteLine(s);
    }
}