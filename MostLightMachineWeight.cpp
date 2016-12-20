#include <iostream>
#include <queue>
#include <vector> 

//�޶��۸�����С����������� - ��֧�޽�
 
using namespace std;

class Node{
public:
	int *x;	//��� 
	int w;
	int c;
	int level;
	bool operator<(const Node & a)  const
	{
		return w<a.w;
	}
};

class Machine
{
private:
	int n;			//n������ 
	int m;			//m����Ӧ�� 
	int *weight;	//weight[i][j]��Ӧ���� 
	int *cost;		//cost[i][j]��Ӧ�۸� 
	int d;			//�ܼ۸� 
	
	
public:
	int Solve(int n_,int m_,int *w_,int *c_,int d_,int *result)
	{
		n = n_;  
		m = m_;
		weight = w_;
		cost = c_;
		d = d_;
		priority_queue<Node> q;
		Node E;
		E.c = 0;
		E.w = 0;
		E.level = -1;
		E.x = new int[n];
		
		while(E.level+1<n)  {
			for(int i=0;i<m;++i) {
				//ȷ�������۸� 
				if(E.c+cost[(E.level+1)*m+i]<=d) {
					Node N;
					N.c = E.c+cost[(E.level+1)*m+i];
					N.w = E.w+weight[(E.level+1)*m+i];
					N.level = E.level+1;
					N.x = new int[n];
					for(int j=0;j<=E.level;++j) {
						N.x[j] = E.x[j];
					}
					N.x[E.level+1] = i;
					q.push(N);	
				}
			}
			delete []E.x;
			if(q.empty()) break;
			E = q.top();
			q.pop();
		}
		if(E.x == NULL) return -1;
		for(int i=0;i<n;++i) {
			result[i] = E.x[i];
		}
		delete []E.x;
		while(!q.empty()) {
			E = q.top();
			delete [] E.x;
			q.pop();
		}
		return E.w;
	}

};



int main()
{
	int n=3,m=3,d=4;
	int c[] = {1,2,3,3,2,1,2,2,2};
	int w[] = {1,2,3,3,2,1,2,2,2};
	int *result = new int[n];
	Machine ma;
	cout<<"BestW:"<<ma.Solve(n,m,w,c,d,result)<<endl;
	for(int i=0;i<n;++i) {
		cout<<result[i]<<' ';
	}
	delete [] result;	
	cin.get();
	return 0;
}
