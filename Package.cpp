#include <iostream>
#include <algorithm>

//0-1��������
 
using namespace std;
class Goods{
public:
	int i;//��� 
	float v,w;//��ֵ������ 
}; 
bool cmp(Goods a,Goods b) {
	if(a.v/a.w < b.v/b.w) return true;
	return false;
}
void Knapsack(int n,float c,Goods g[],float x[]) 
	//�������� 
{	//n��Ʒ������c�����ܳ��� 
	//g[i].v=i���ܼ�ֵ��g[i].w=i �������� 
	//x[i] ѡ��i���ٷ� 
	sort(g,g+n,cmp);
	int i;
	for(i=0;i<n;++i) x[i]=0;
	for(i=0;i<n;++i) {
		if(g[i].w>c) break;
		x[i]=1;
		c-=g[i].w;
	}
	if(i<=n) x[i]=c/g[i].w;
} 

void printResult(Goods g[] ,float x[],int n) {
	for(int i=0;i<n;++i) {
		cout<<"seletc "<<x[i]<<" �� "<<g[i].i<<endl; 
	}
}

int main()
{
	Goods a[10];
	for(int i=0;i<10;++i) a[i].i=i;
	
	
	return 0;
}
