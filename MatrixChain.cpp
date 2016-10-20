#include <iostream> 
#include <cmath>

using namespace std;

//����������У�������ĳ�ִ��򣬾�����˵�����˷��������� 

int m[6][6],s[6][6];
int p[5];

void MatrixChain(int *p, int n) {
	//p[i]Ϊ���������о���[i]������==��һ��������� 
	//n==��������m��¼����������s��¼�Ͽ�λ�� 
	
	for(int i=1; i<=n; ++i) m[i][i]=0;//��������������Ϊ0 
	for(int r=2; r<=n; ++r) {         // ÿһб�� 
		for(int i=1;i <=n-r+1; ++i) {  //�� 
			int j=i+r-1;		       //�� 
			m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
			s[i][j]=i;				   //��A[i:j]֮����s[i][j]���� 
			for(int k=i+1; k<j; ++k) {
				//��Ȿ�η���(����j-i��Ԫ�صķ���)����С�ļ������ 
				int t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j]) {
					m[i][j] =t;
					s[i][j] = k;//������λ�� 
				}
			}
		}
	}
}

int RecurMatrixChain(int i,int j) {
	//�ݹ�ʽ����ȡ����¼���� 
	//���ʼ��m[i][j]=-1; 
	if(m[i][j]>0) return m[i][j]; //������¼���Դ˼��ٵݹ������ 
	if(i==j) return 0;
	int u = RecurMatrixChain(i,i)+RecurMatrixChain(i+1,j)+p[i-1]*p[i]*p[j];
	s[i][j]=i;
	for(int k=i+1; k<j; ++k) {
		int t = RecurMatrixChain(i,k)+RecurMatrixChain(k+1,j)+p[i-1]*p[k]*p[j];
		if(t<u) {
			u = t;
			s[i][j]=k;
		}
	}
	m[i][j]=u;
	return u;
} 

void Traceback(int i,int j) {
	//A[i:n]���ż����ŷ�ʽ (A[1:s[1][n]]) (A[s[1][n]+1:n])
	if(i==j) return ;
	Traceback(i,s[i][j]); 
	Traceback(s[i][j]+1,j);
	cout<<"Multiply A "<<i<<","<<s[i][j];
	cout<<" and A "<<(s[i][j]+1)<<","<<j<<endl;
} 

int main(int argc,char*argv[]) {
	p[0]=10;	p[1]=20;	p[2]=10;	p[3]=30;
	p[4]=40;
	for(int i=0; i<6; ++i) {
		for(int j=0; j<6; ++j) {
			m[i][j]=0;
			s[i][j]=0;
		}
	}
	MatrixChain(p,5);
	//RecurMatrixChain(1,5);
	Traceback(1,5);
	return 0;
}
