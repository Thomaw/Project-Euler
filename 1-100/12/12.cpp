#include<math.h>

int prim(int tal)
{
	int summa=0;
	for(int i=1;i<tal;i++){
		if(tal%i==0){
			if((i*i)>tal){
				summa*=2;
				break;
			}
			else if((i*i)==tal){
				summa*=2;
				summa++;
				break;
			}
			else{
				summa++;
			}
		}
	}
	return summa;
}		
int main()
{
	system("cls");
	bool hittad=false;
	int tal=0;
	for(int i=1;!hittad;i++){
		tal+=i;
		int div2=prim(tal);
		if(div2>500){
			hittad=true;
			cout<< i <<' '<<tal<<endl;
		}
	}
	system("pause");
}
