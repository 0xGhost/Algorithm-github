#include <iostream>
#include <vector>
#include <queue>

//ͼ�����·������ -- ��֧�޽編
//����Dijkskal 
using namespace std;
class Node{
public:
	int i;			//������ 
	int length;		//��ǰ·��
	operator int() const {return length;}  
}; 

class Grapth {
private:
	int n,		//ͼ�Ķ�����
		*prev;	//ǰ����������
	int *c;	//�ڽӾ���
	int	*dist;	//��̾������� 
		
public:
	void Shortest(int *c,int n,int *dist,int *prev,int v,int INF) 
	{
		this->c = c;
		this->n = n;
		this->dist = dist;
		queue<Node> q;
		Node E;
		E.i = v;
		E.length = 0;
		dist[v] = 0;
		//�ѽ�ռ�
		while(true) {
			for(int j=1;j<=n;++j) {
				if((c[E.i*(n+1)+j]<INF)&&(E.length+c[E.i*(n+1)+j]<dist[j])) {
					//����i��j�ɴ���������Լ��
					dist[j] =E.length + c[E.i*(n+1)+j];
					prev[j] = E.i;
					//����������ȶ���
					Node N;
					N.i = j;
					N.length = dist[j] ;
					q.push(N);
				} 
			}
			if(q.empty()) break;
			E = q.front();
			q.pop();
		}
	}
};
/*
template<class  T_>
void Out(int n,int v,T_ dist[],int prev[]) 
{
	//n��(in)��������
	//v��(in)Դ�������� ��0-...��
	//dist[]"(out) ��Դ���� ��ÿ������ľ���
	//prev[]��(out) �����·����ÿ�������ǰ���һ������ 
	int path_points[(n+1)*n/2+1];
	int i,j,k;
	for(i=1; i<=n; ++i) {
		if(i==v) continue;
		cout<<"����"<<i<<",���·������="<<dist[i]<<endl;
		
		j=1;
		path_points[0] =i;
		k = i;
		while(prev[k]!=v && prev[k]!=-1) {
			path_points[j++] = prev[k];
			k=prev[k];
		}
		for(--j; j>=0; j--) {
			cout<<path_points[j] <<" ";
		}
		cout<<endl;
	}
}
*/

int main() {
	
	int n=5;
	const int  INF = 65535;
	int dist[n+1];
	int prev[n+1];
	int c[(n+1)*(n+1)];
	const int graph_edges[] = {
		0,0,0,0,0,0,
		0,0,10,INF,30,100,
		0,10,0,50,INF,INF,
		0,INF,50,0,20,10,
		0,30,INF,20,0,60,
		0,100,INF,10,60,0
	};
	for(int i=0;i<(n+1)*(n+1);i++) {
		c[i]=graph_edges[i];
	}
	
	Grapth  g;
	g.Shortest(c,n,dist,prev,1,65535);
	Out<int>(n,1,dist,prev);
	
	
	cin.get();
	return 0;
}
