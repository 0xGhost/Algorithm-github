#include <iostream>
#include <cmath> 
#include <stdlib.h>
#include <ctime>
//����ʱ�����


using namespace std;

int a[100];

template<class T_> 
void Swap(T_ &a,T_ &b) {
	T_ it = a;
	a = b;
	b = it;
}
template<class T_>
int Partition(T_ a[],int s,int e) {
	int i=s, j=e+1;
	T_ x = a[s];
	//�� < x ������Ԫ���Ƶ����
	//�� > x ������Ԫ���Ƶ��ұ� 
	while(true) {
		while(a[++i]<x&&i<e);
		while(a[--j]>x);
		if(i>=j) break;
		Swap<T_>(a[i],a[j]);
	}
	a[s] = a[j];
	a[j] = x;
	return j;//�����м�λ�� 
}
template<class T_> 
int RandomizedPartition(T_ a[], int s,int e) {
	srand(time(NULL));
	int i = 0;
	i = rand()%(e-s)+s;
	Swap<T_>(a[i],a[s]);
	return Partition<T_>(a,s,e); 
}

template<class T_>
T_ RandomizedSelect(T_ a[],int s,int e,int k) {
	if(s==e) return a[s];
	int i = RandomizedPartition<T_>(a,s,e);	//����м�ĳֵԪ��λ�� 
	int j = i-s+1;
	if(k<=j) {		//���Σ�����ÿ��ֻ����һ�� 
		return RandomizedSelect<T_>(a,s,i,k);
	} else {
		return RandomizedSelect<T_>(a,i+1,e,k-j);
	}
	
}

int main() {
	
	for(int i=0;i<100;++i) {
		a[i] = i;
	}
	
	int pp=0;
	cin>>pp;
	int j = RandomizedSelect<int>(a,0,99,pp);
	cout<<j;
	
	
	
	return 0;
} 
