#include<iostream>
#include<algorithm>
//̰���㷨��������� 
using namespace std;

//��Ҫ�������������������(nlog(n))
//��������ΪO(n) 
template<class T_> 
void GreedSelector(int n,T_ s[],T_ f[],bool ret[]) 
{ 
	//n:�������s[i]:i���ʼʱ�䣬f[i]:i�����ʱ��
	//s[i]��f[i]����f[i]�ǵݼ���ret[] ��ѡ���־
	ret[0]=true;
	int j=0;
	for(int i=1; i<n; ++i) {
		if(s[i]>=f[j]) {
			ret[i]=true;
			j = i;
		} else {
			ret[i]=false;
		}
	}
}

void GetPlan(bool ret[],int n)
{
	cout<<"ѡ��:";
	for(int i=0;i<n;++i){
		if(ret[i])
			cout<<i<<' ';
	}
	cout<<"End.\n";
} 


int main(int argc,char *argv[])
{
	int s[]={1,3,0,5,3,5,6,8,8,2,12};
	int f[]={4,5,6,7,8,9,10,11,12,13,14};
	bool ret[11];
	GreedSelector(11,s,f,ret);
	GetPlan(ret,11);
	getchar();
	return 0;
} 
