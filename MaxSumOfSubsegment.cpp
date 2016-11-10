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

int MaxSubSum(int *a,int left,int right) 
{
	//���η� 
	int sum = 0;
	if(left == right) sum = a[left]>0?a[left]:0;
	else {
		int center =(left+right) / 2;
		int leftsum = MaxSubSum(a,left,center);
		int rightsum = MaxSubSum(a,center+1,right);
		int s1 = 0;
		int lefts = 0;
		for(int i=center;i>=left;i--) {
			lefts +=a[i];
			if(lefts>s1) s1 = lefts;
		}
		int s2 = 0;
		int rights = 0;
		for(int i=center+1;i<=rights;++i) {
			rights+=a[i];
			if(rights>s2) s2=right;
		}
		sum = s1+s2;
		if(sum<leftsum) sum = leftsum;
		if(sum<rightsum) sum = rightsum;
	} 
	return sum;
}

int MaxSubSum(int n,int *a,int &istart,int &iend) 
{
	//nԪ����
	//a�������ֶκ͵����� 
	//start end����ֶκ͵���ʼ����ֹλ��
	//��������ֶκ� 
	int b[n+1];//b[i]��a[i]��β�������ֶκ͵����ֵ 
	int d[n+1];
	
	int sum = 0;
	b[0]=0;
	for(int i=1;i<=n;i++) {
		if(b[i-1]>0) {
			b[i]=b[i-1]+a[i];
			d[i]=1;
		} else {
			b[i]=a[i];
			d[i]=2;
		}
		if(sum<b[i]) {
			sum = b[i];
			iend = i;
		}
	}
	istart =iend;
	while(istart>0&&d[istart]==1) istart--;
	return sum;
}

int main() 
{
	
	int a[] = {0,-1,2,3,45,-34,15,33,-24};
	int i,j;
	cout<<"����ֶκͣ�"<<MaxSubSum(sizeof(a)/sizeof(int)-1,a,i,j)<<endl;
	cout<<"����ֶδ�"<<i<<"��"<<j<<endl; 
	cin.get();
	return 0;
} 



