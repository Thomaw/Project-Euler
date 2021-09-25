  public static void  main(String argv[])
  {
    //P119
    Long power = 0L;
    for(Long a = 2L;a<144L;a++)
    {
      power = a;
      for(Long b=2L;;b++)
      {
        Double stellen = (double)b*Math.log10(a);
        if(stellen >= 16L) break;
        power *= a;
        if((long)a == (long)sumOfDigits(power.toString()))
        System.out.println(a+"^"+b+" = "+power+" "+sumOfDigits(power.toString()));
      }
    }
  }