#include <iostream> 


//͹��������������ʷ� 
//2016-11-3
//�����������һ�������͹��������������ʷ� 
using namespace std;
const int N = 7;





int weight(int i,int j,int k) {
	//�����������
	//��������� 
	return abs(k+k-i-j); 
} 

void MinWeightTri(int n, int t[][N+1],int s[][N+1])
{
	//����n+1���ι���weight�����Ż���
	//t[i][j] {Vi..Vj}�����Ȩֵ
	//s[i][j] ����ʹ�õĶ���
	for(int i=1;i<=n;i++) t[i][i]=0; 	//�˻���������� 
	for(int r=2;r<=n;r++) {				//ÿб�� 
		for(int i=1;i<=n-r+1;++i) {		
			int j = i+r-1;
			t[i][j]=t[i][i]+t[i+1][j]+weight(i-1,i,j);
			s[i][j]=i;
			for(int k=i+1;k<i+r-1;++k) {//�ò����� 
				int u=t[i][k]+t[k+1][j]+weight(i-1,k,j);
				if(u<t[i][j]) {
					t[i][j]=u;
					s[i][j]=k;
				}
			}	
		}
	}	
} 

void Traceback(int i,int j,int s[][N+1]) {
	//���ѡ��Ĺ������ǵĶ��� 
	if(i==j) return ;
	Traceback(i,s[i][j],s); 
	cout<<s[i][j]<<" ";
} 

int main(int argc,char *argv[])
{
	
	int  t[N+1][N+1];
	int s[N+1][N+1];
	MinWeightTri(N,t,s);
	Traceback(1,N,s);
	
	cin.get(); 
	return 0;
}
