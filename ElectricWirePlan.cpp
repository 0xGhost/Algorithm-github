#include <iostream> 
using namespace std; 

const int N = 10;
//���ÿ��ˣ���Ŀ������������ 


void MNS(int C[],int n,int **size)
{
	//C[i] = Pi(i) i��Ӧ���½����� 
	//n �Ͻ���������
	//size[][] ���� ����ཻ�Ӽ���Ԫ����  
	for(int j=0;j<C[1];j++)
		size[1][j]=0;

	for(int j=C[1]; j<=n; j++)
		size[1][j]=1;

	for(int i=2; i<n; i++)	{
		for(int j=0; j<C[i]; j++)
			size[i][j]=size[i-1][j];//��i<c[i]������
		for(int j=C[i]; j<=n; j++)
			//��j>=c[i]ʱ������(i��c[i])�Ƿ�����MNS(i,j)���������
			size[i][j]=size[i-1][j]>(size[i-1][C[i]-1]+1)?size[i-1][j]:(size[i-1][C[i]-1]+1);
	}
	size[n][n]=max(size[n-1][n],size[n-1][C[n]-1]+1);
}

void Traceback(int C[],int **size,int n,int Net[],int& m)
{
	//C[i] = Pi(i) i��Ӧ���½����� 
	//n �Ͻ���������
	//size[][] ���� ����ཻ�Ӽ���Ԫ����
	//Net ��� 
	// m ������ 
	int j=n;
	m=0;
	for(int i=n;i>1;i--) {
		if(size[i][j]!=size[i-1][j]) { //��ʱ��(i,c[i])������ཻ�Ӽ���һ����
			Net[m++]=i;
			j=C[i]-1;//������չ����������
		}
	}
	if(j>=C[1]) {	//����i=1������
		Net[m++]=1;
	}
}


int main()
{
	int c[] = {0,8,7,4,2,5,1,9,3,10,6};//�±��1��ʼ
	
	int **size = new int *[N+1];
	for(int i=0; i<=N; i++) {
		size[i] = new int[N+1];
	}

	MNS(c,N,size);

	cout<<"��·��������ཻ������ĿΪ��"<<size[N][N]<<endl;

	int Net[N],m;
	Traceback(c,size,N,Net,m);

	cout<<"����ཻ���߷ֱ�Ϊ��"<<endl;
	for(int i=m-1; i>=0; i--) {
		cout<<"("<<Net[i]<<","<<c[Net[i]]<<") ";
	}
	cout<<endl;
	cin.get();
	return 0;
}
