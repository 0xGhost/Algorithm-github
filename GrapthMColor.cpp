#include <iostream>
#include <memory.h>
using namespace std;

class GraphMColor
{
private:
	int n;	//ͼ�Ķ������� 
	int m;	//��ɫ���� 
	int *a;	//ͼ���ڽӾ��� 
	
	int *x;	//��ǰ�� 
	long sum;	//���н����� 
	
private:
	void Backtrack(int t); 
	bool OK(int k);
public:
	int solve(int n_,int m_,int *a_);
	
};

int GraphMColor::solve(int n_,int m_,int *a_)
{
	//int n_;	//ͼ�Ķ������� 
	//int m_;	//��ɫ���� 
	//int *a_;	//ͼ���ڽӾ��� 
	n = n_;
	m = m_;
	a = a_;
	
	sum=0;
	x=new int[n+1];
	memset(x,0,sizeof(int)*(n+1));
	Backtrack(1);
	delete[] x;
	return sum;
}

void GraphMColor::Backtrack(int t) 
{
	if(t>n) {
		++sum;
		for(int i=1; i<=n; ++i) 
			cout<<x[i]<<' ';
		cout<<endl;
	} else {
		for(int i=1; i<=m; ++i) {
			x[t] = i;
			if(OK(t)) Backtrack(t+1);
			//x[t] = 0; //��ֹ��ȵݹ���ɶ�OK��Ӱ�� 
		}
	}
}

bool GraphMColor::OK(int k) 
{
	for(int i=1; i<=k-1; ++i) {
		if(a[k*(n+1)+i]==1 && x[i]==x[k])
			return false;
	}
	return true;
}



int main()
{
	int n= 5;
	int m=4;
	int a[] = {
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 1, 0, 1, 1, 1,
		0, 1, 1, 0, 1, 0,
		0, 1, 1, 1, 0, 1,
		0, 0, 1, 0, 1, 0
	};
	GraphMColor gc;
	int sum = gc.solve(n,m,a);
	
	cout<<"���н�����:"<<sum<<endl;
	cin.get();
	return 0;
}
