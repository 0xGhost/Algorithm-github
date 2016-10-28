#include <iostream>
#include <algorithm>

//����Ӷκ� 
using namespace std;


int MaxSum(int n,int a[],int &start,int &end) 
{
	//������������Ӷκ� 
	//nԪ������aԪ������ 
	//startѡ�е��ֶο�ʼԪ���±� 
	//endѡ�е��ֶν���Ԫ���±� 
	int sum=0;
	for(int i=0;i<=n;++i) {
		int this_sum = 0;
		for(int j=i;j<=n;++j) {
			this_sum += a[j];
			if(this_sum>sum) {
				sum  = this_sum;
				start = i;
				end = j;
			}
		}
	}
	return sum;
}

int MaxSum(int n,int a[]) 
{
	//��̬�滮������Ӷκ� 
	int sum = 0,b= 0;
	for(int i=0;i<n;++i) {
		if(b>0) b+=a[i];
		else b = a[i];
		if(b>sum) sum = b;
	}
	return sum;
} 


int main() 
{
	int a[] = {1,2,-11,15,6,-5,-6,8,10,-12};
	int start,end;
	cout<<MaxSum(sizeof(a)/sizeof(int),a,start,end)<<endl;
	cout<<start<<' '<<end<<endl;
	cout<<MaxSum(sizeof(a)/sizeof(int),a)<<endl;
	getchar(); 
	return 0;
}
