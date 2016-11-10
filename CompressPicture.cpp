#include <iostream>
#include <stdlib.h>
#include <time.h>

//ͼ��ֶ�ѹ�� 
using namespace std;


int Length(int i) {
	//�������ռ�ü�λ�ռ� 
	int k=1;
	i/=2;
	while(i>0) {
		k++;
		i/=2;
	}
	return k;
}
void Compress(int n,int p[],int s[],int L[],int b[],int bseg[])
{
	//n��������p[]ÿ�����ص�ֵ
	//s��iΪ���Ԫ�ص����зֶε�Ԫ��ռ��λ��
	//L[i]��iΪ���Ԫ�صķֶ���֮ǰ�ֶε�Ԫ����
	//b[]ÿ����ռ�õ�λ��  
	//bseg[]��iΪ���Ԫ�صķֶ��������ռ��λ��
	 
	int Lmax = 256,header=11;
	s[0]=0;
	for(int i=1;i<=n;i++) {
		b[i]=Length(p[i]);
		int bmax = b[i];
		s[i]=s[i-1]+bmax;
		L[i]=1;
		for(int j=2;j<=i&&j<=Lmax;++j){
			if(bmax<b[i-j+1]) bmax = b[i-j+1];
			if(s[i]>s[i-j]+j*bmax) {
				s[i]= s[i-j]+j*bmax;
				L[i]=j;
				bseg[i] = bmax;
			}
		}
		s[i]+=header;		
	}	
}

void Traceback(int n,int &i,int s[],int L[]) 
{
	if(n==0) return ;
	Traceback(n-L[n],i,s,L);
	s[i++]=n-L[n]; //����ÿ�ֶο�ʼλ�� 
	//cout<<s[i-1]<<endl; 
} 

void Print(int s[],int L[],int bseg[],int n)
{
	cout<<"����ֵ��"<<s[n]<<endl;
	int m =0;
	Traceback(n,m,s,L);
	s[m]=n;
	cout<<"�ֳ�"<<m<<"��\n" ;
	for(int j=1;j<=m;j++) {
		L[j]=L[s[j]];
		bseg[j]=bseg[s[j]];
	}
	for(int j=1;j<=m;j++) {
		cout<<"�ֶδ�С��"<<L[j]<<" �ö�ÿԪ��ռλ "<<bseg[j]<<endl;
	}
}

int main(int argc,char *argv[]) 
{
	int p[1024+1];
	int s[1024+1];
	int L[1024+1],b[1024+1],bseg[1024+1];
	srand(time(NULL));
	for(int i=0;i<1024+1;i++){
		if(i<=100) p[i] = 3;
		if(100<i&&i<=200) p[i] = 45;
		if(200<i&&i<=300) p[i] = 125;
		if(i>300) p[i]=rand()%254+1;
	}
	Compress(350,p,s,L,b,bseg);
	Print(s,L,bseg,350);
	cin.get();
	return 0;
}
