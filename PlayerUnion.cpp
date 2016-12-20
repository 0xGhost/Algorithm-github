#include <iostream>
#include <queue>
#include <vector> 

//  �˶�Ա������ - ��֧�޽�
 
using namespace std;

class Node {
public:
	int level;		//��level�����˶�Ա
	int c;			//Ŀǰ���������ӳ�
	int *x;			//��Ա���ŷ�ʽ 
	bool operator <(const Node &a) const 
	{
		return this->c < a.c; 
	}
}; 
void Swap(int &a,int &b)
{
	if(a==b) return;
	int c =a;
	a = b;
	b = c;
}

class Organize
{
private:
	int n;		//n��nŮ 
	int *P;		//p[i][j] ����i��Ůjһ��ʱ�������ӳ� 
	int *Q;		//Q[i][j] ��Ůi����jһ��ʱ�������ӳ�
	int bestc;
	
public:	
	int Solve(int n_,int *p_,int *q_,int *result)
	{
		n = n_;
		Q = q_;
		P = p_;
		Node E;
		E.c = 0;
		E.level = 0;
		E.x = new int[n];
		for(int i=0;i<n;++i) E.x[i] = i;
		priority_queue<Node> qq;
		bestc = 0;
		while(E.level<=n) {
			//������ǰ�ڵ����չ�ڵ� 
			if(E.level == n) {
				if(E.c>bestc) {
					bestc = E.c;
					for(int i=0;i<n;++i) {
						result[i]=E.x[i];
						//if(E.c == 55)
						//cout<<result[i]<<endl;
					}
					delete [] E.x;
				}
			}
			else {
				for(int i=E.level;i<n;++i) {
					Swap(E.x[E.level],E.x[i]);
					Node N;
					N.c = E.c + P[E.level*n+E.x[E.level]] * Q[E.x[E.level]*n+E.level];
					N.level = E.level+1;
					N.x = new int[n];
					for(int j=0;j<n;++j) N.x[j] = E.x[j];
					qq.push(N);
					Swap(E.x[E.level],E.x[i]);
				}
				delete [] E.x;
			}
			if(qq.empty()) break;
			E= qq.top() ; 
			qq.pop();
		}
		while(!qq.empty()) {
			E = qq.top();
			delete [] E.x;
			qq.pop();
		}
		return bestc;
	}
};

int main()
{
	int n = 3;
	int p[] = {10,2,3,2,3,4,3,4,5};
	int q[] = {2,2,2,3,5,3,4,5,1};
	int *result = new int [n];
	
	Organize org;
	cout<<"Best:"<<org.Solve(n,p,q,result)<<endl;
	
	
	for(int i=0;i<n;++i) 
	cout<<result[i]<<' ';
	cin.get();
	delete [] result;
	return 0;
}
