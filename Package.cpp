#include <iostream>


//0-1��������
 
using namespace std;


void Knapsack(int n,float c,float v[],float w[],float x[]) 
	//�������� 
{	//n��Ʒ������c�����ܳ��� 
	//v[i] i���ܼ�ֵ��w[i] i �������� 
	//x[i] ѡ��i���ٷ� 
	int i;
	for(i=0;i<n;++i) x[i]=0;
	for(i=0;i<n;++i) {
		if(w[i]>c) break;
		x[i]=1;
		c-=w[i];
	}
	if(i<=n) x[i]=c/w[i];
} 

void printResult(float x[],int n) {
	for(int i=0;i<n;++i) {
		cout<<"seletc "<<x[i]<<" �� "<<i<<endl; 
	}
}

int main()
{
	
	
	
	return 0;
}
