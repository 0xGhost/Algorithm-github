#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;
//�������Թ滮 


const int my_n = 5;
const int my_all = 20; 



int m[my_n+1][my_all+1];		//m[i][j]Ϊѡ��ǰi�����ԴΪjʱ�����Żر�ֵ��
int X[my_n+1][my_all+1];	//X[i][j]��������Ͷ�ʵ�i��Ʒ���ٵ�λ 

void how_to_invest(int n,int all,int w[],int v[])
{
	//n��ѡ��  all=������Դ 
	//x[i]/w[i]/v[i] ��i����Ŀ Ͷ���˶��ٵ�λ/��λ������Դ��/��λ�ر��� 
	//m[i][j]Ϊѡ��ǰi�����ԴΪjʱ�����Żر�ֵ��  
	//X[i][j]��������Ͷ�ʵ�i��Ʒ���ٵ�λ 
	for(int i=1; i<=n; i++)  m[i][0]=0;
	for(int i=1; i<w[1]; i++)  m[1][i]=0;
	for(int i=w[1]; i<=all; i++) {
		m[1][i] = int(i/w[1])*v[1];
		X[1][i] = int(i/w[1]);
	}
	//for(int i=1; i<=all; i++) cout<<m[1][i]<<endl;
	for(int i=2; i<=n; i++) {
		//��ǰ���
		int Jmax = all<(w[i]-1)?all:w[i]-1;
		for(int j=1; j<=Jmax; j++) {  //j<w[i];
			m[i][j] = m[i-1][j];
			X[i][j]=0;
		}
		for(int j=w[i]; j<=all; j++) { //j>=w[i];
			//max{m(i-1,j-x*wi)+x*vi}(1<=x<=k)}
			int Mmax = 0;
			int k = int(j/w[i]);
			for(int x=w[i]; x<=k; x++) {
				if(Mmax<m[i-1][j-x*w[i]]+x*v[i]) {
					X[i][j]=x;
					Mmax = m[i-1][j-x*w[i]]+x*v[i];
				}
			}
			//max{ m(i-1,j) , max{m(i-1,j-x*wi)+x*vi}(1<=x<=k)}
			if(m[i-1][j]>Mmax) {
				m[i][j]=m[i-1][j];
				X[i][j]=0;
			} else {
				m[i][j] = Mmax;
			}
		}
	}
}


void TraceBack(int w[],int n,int all) {
	//n��ѡ��  all=������Դ 
	if(X[n][all]==-1) return ;
	if(X[n][all]!=0) {
		cout<<"��"<<n<<"Ͷ����Դ��"<<X[n][all]*w[n]<<endl;
	}
	TraceBack(w,n-1,all-X[n][all]*w[n]);
}

int main(int argc,char *argv[])
{
	memset(X,-1,sizeof(int)*(my_n+1)*(my_all+1));
	int w[] = {0,2,3,4,5,6};
	int v[] = {0,3,4,8,6,9};
	how_to_invest(my_n,my_all,w,v);
	cout<<"�������"<<m[my_n][my_all]<<endl;
	TraceBack(w,my_n,my_all);
	cin.get();
	return 0;
}
