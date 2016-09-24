#include <iostream>
#include <cmath> 
#include <stdlib.h>
#include <ctime>
#include <algorithm>
//����ʱ�����


using namespace std;

int a[100];
///////////////////////////////////
///////һ����˵�˷�ʱ�临�Ӷ�O(N)//
///////////////////////////////////
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
	return j;//�����м�λ��(�ϸ���˵�Ⲣ�����м���)
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

///////////////////////////////////
///////�˷����ʱ�临�Ӷ�O(N)//////
///////////////////////////////////

template<class T_>
bool cmp(T_ a,T_ b) {
	if(a<=b)
		return true;
	return false;
}

template<class T_>
T_ Select(T_��a[],int s,int e,int k) {
	if(e-s<75) {
		sort(a,a+e,cmp<T_>); //ĳ���㷨��a���� 
		return a[s+k-1];
	}
	for(int i=0;i<=(e-s-4)/5;++i) {
		//��a[s+5*i]��a[s+5*i+4]�ĵ���СԪ����a[s+i]
		//Swap<T_>(a[s+i],); 
	}
	//����λ�ã��ҵ���λ������λ��
	T_ x = Select<T_>(a,s,s+(e-s-4)/5,(e-s-4)/10);
	int i = Partition<T_>(a,s,e,x),j=i-s+1;
	if(k<=j) 
		return Select<T_>(a,s,i,k);
	else
		return Select<T_>(a,i+1,e,k-j);
	
} 


int main() {
	
	for(int i=0;i<100;++i) {
		a[i] = i;
	}
	
	int pp=0;
	cin>>pp;
	int j = RandomizedSelect<int>(a,0,99,pp);
	int c = Select<int>(a,0,99,pp);
	cout<<j<<endl<<c;
	cin>>pp;
	
	
	return 0;
} 
