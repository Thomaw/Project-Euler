#include <string>
#include <iostream>
#include <fstream>

int romanToInt( std::string s )
{
  int result = 0, pos, i;
  static std::string str[] = {"CM","M","CD","D","XC","C","XL","L","IX","X","IV","V","I"};
  static int val[] = {900,1000,400,500,90,100,40,50,9,10,4,5,1};
  for ( i = 0; i < 13; ++i )
    while ( (pos = s.find( str[i] )) != std::string::npos )
    {
      result += val[i];
      s.erase( pos, str[i].size() );
    }
  return result;
}

std::string intToRoman( int i )
{
  static std::string Clist[] = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
  static std::string Xlist[] = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
  static std::string Ilist[] = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
  std::string result;
  result.resize( i / 1000, 'M' );
  i %= 1000;
  result += Clist[ i / 100 ];
  i %= 100;
  return result + Xlist[ i / 10 ] + Ilist[ i % 10 ];
}

int main()
{
  std::ifstream istr("romansum.txt");
  std::string s;
  int result = 0;
  while ( istr >> s )
    result += s.size() - intToRoman( romanToInt(s) ).size();
  std::cout << result << std::endl;
  return 0;
}