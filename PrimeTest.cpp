#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include <iostream>


//�������� --���ؿ����㷨  
using namespace std;

void PowerAndPrimeTest(unsigned int a,unsigned int p,unsigned int n,
		unsigned int &result,bool &composite)
{
	//����power(a,p) mod n ,ͬʱʵʩ��n�Ķ���̽�� 
	//result������		composite�Ƿ�Ϊ���� 
	unsigned int x;
	if(p==0) result = 1;
	else {
		PowerAndPrimeTest(a,p/2,n,x,composite);
		
		result = (x*x)%n;
		if(result==1 && x!=1 && x!=n-1)
			composite = true; 
		//������ 
		if(p%2==1) //p������ 
			result = (result*a)%n;
	}
	
}

bool PrimeTestMC(unsigned int n,unsigned int k)  
{
	//���n�Ƿ�Ϊ����
	//�ظ�����k�����ؿ����㷨  
	unsigned int a,result;
	bool composite  = false;
	if(n<5) {
		if(n==2 || n == 3) return true;
		return false;
	} 
	for(int i=1;i<=k;++i) {
		//����������5������������������ 
		a = rand()%(n-3)+2 ;
		PowerAndPrimeTest(a,n-1,n,result,composite);
		if(composite || (result!=1)) return false;
	}
	return true;
}

bool PrimeTest(unsigned int n)   
{
	if(n==1) return false;
	else if(n==2) return true;
	unsigned int i,m = sqrt(n);
	for(i=2;i<=m;++i) 
		if(n%i==0) return false;
	return true;
}

int main()
{
	unsigned int n = 1194211693L;
	for(int i=2000;i<5000;++i) 
		if(PrimeTest(i)) {
			cout<<i<<endl;
			n=i;
			break;
		}
	
	for(int i=0;i<20;++i) {
		if(PrimeTestMC(n,4)) cout<<true<<endl;
		else cout<<false<<endl;
	}
	
	
	cin.get();
	return 0;
}
