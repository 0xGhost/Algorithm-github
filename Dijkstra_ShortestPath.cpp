#include <iostream>
#include <vector>

//Dijkstra���·����� 
 
using namespace std;

template <class T_> 
void Dijkstra_ShortestPath(int n,int v,T_ dist[],int prev[],
						const T_ *c,const T_ INF) 
{
	//n��(in)��������
	//v��(in)Դ�������� ��0-...��
	//dist[]"(out) ��Դ���� ��ÿ������ľ���
	//prev[]��(out) �����·����ÿ�������ǰ���һ������ 
	//c(in)�����������ľ���
	bool s[n]; // s[i]��ʾ�õ��Ƿ������·����֪�Ķ��㼯���ڡ� 
	for(int i=0;i<n;i++) s[i] = false;
	
	for(int i=0; i<n; ++i) {
		dist[i]=c[v*n+i];
		if(dist[i]==INF) prev[i] = -1;
		else prev[i]=v;
	}
	//add v to s
	dist[v] = 0;
	s[v] = true;
	
	for(int i=1; i<n; ++i) {
		T_  dist_tmp = INF;
		int u = v;
		//ѡ���ôε�v��̵ĵ㣬�õ㲻����s 
		for(int j=0; j<n; ++j) {
			if(s[j]) continue;
			if(dist_tmp==INF || dist[j]<dist_tmp) {
				dist_tmp = dist[j];
				u = j;
			}
		}
		s[u] = true;
		//����õ����������Ӱ�� 
		for(int j=0; j<n; ++j) {
			if(s[j] || c[u*n+j]==INF) continue;
			T_ dist_new = dist[u]+c[u*n+j];
			if(dist_new<dist[j]) {
				dist[j]=dist_new;
				prev[j] = u;
			}
		}
	}
}  



template<class  T_>
void Out(int n,int v,T_ dist[],int prev[]) 
{
	//n��(in)��������
	//v��(in)Դ�������� ��0-...��
	//dist[]"(out) ��Դ���� ��ÿ������ľ���
	//prev[]��(out) �����·����ÿ�������ǰ���һ������ 
	int path_points[n*(n-1)/2+1];
	int i,j,k;
	for(i=0; i<n; ++i) {
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

int main() {
	
	int n=5;
	const float  INF = 65535;
	float dist[n];
	int prev[n];
	float c[n*n];
	const float graph_edges[] = {
		0,10,INF,30,100,
		10,0,50,INF,INF,
		INF,50,0,20,10,
		30,INF,20,0,60,
		100,INF,10,60,0
	};
	for(int i=0;i<n*n;i++) {
		c[i]=graph_edges[i];
	}
	
	Dijkstra_ShortestPath<float>(n,0,dist,prev,c,INF);
	Out<float>(n,0,dist,prev);
	
	
	cin.get();
	return 0;
}
