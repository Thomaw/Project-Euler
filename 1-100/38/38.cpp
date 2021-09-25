#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

int main(){
	std::string str;
	std::string str1;
	std::string check="123456789";
	std::ofstream ot("result38.txt");
	int n,m;
	int count=0;
	std::stringstream ss;
	for(int i=1;i!=10000;++i){
		m=1;
		str="";	
		while(str.length()<9){
			n=i*m;
			++m;
			ss.clear();
			ss << n;
			ss >> str1;
			str.append(str1);
		}
		if(str.length()==9){
			str1=str;
			std::sort(str.begin(),str.end());
			if(str==check){
				ot << i << " " << m-1 << " " << str1 << '\n';
				++count;
			}
		}
	}
	ot << "total: " << count << std::endl;
	ot.close();
}
