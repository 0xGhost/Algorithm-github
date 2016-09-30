#include <iostream>

using namespace std;
template<class T_>
void ExchangeArray(T_ a[],int k,int l) {
	//������a[0,k] ��a[k+1,l]����λ��
	T_ tmp;
	int i=0,j=k;
	while(i<j){
		tmp = a[i];
		a[i++]=a[j];
		a[j--]=tmp;
	}
	i=k+1,j=l;
	while(i<j){
		tmp = a[i];
		a[i++]=a[j];
		a[j--]=tmp;
	} 
	i=0,j=l;
	while(i<j){
		tmp = a[i];
		a[i++]=a[j];
		a[j--]=tmp;
	} 
} 


int main() {
	
	int a[20];
	for(int i=0;i<20;++i){
		a[i]=i;
	}
	
	ExchangeArray<int>(a,10,19);
	//ExchangeArray(a,10,19);
	for(int i=0;i<20;++i){
		cout<<a[i]<<' ';
	}
	return 0;
}
