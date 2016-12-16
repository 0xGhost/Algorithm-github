#include <iostream>
#include <queue>
#include <vector>

//�������� --�򵥷�֧�޽� 
using namespace std;


class Point{
public:
	int x,y;
	Point *parent;
	int level;
	int cost; 
	Point(int x_,int y_) { x = x_; y = y_;	}
	Point() { x=0; y = 0; }
};

class FindPath {
private:
	int n,			//n�� 
		m;			//m��
	bool *a;		//���о���
	Point end;
	Point start; 
	int cc;			//Ŀǰ���� 
	int bestc;		//���Ų��� 
	Point *best;
private:
	
	
public:
	int Find(bool *a_,int n_,int m_,Point s,Point e,Point *re)
	{
		//a_���о���s��ʼλ��,eĿ��λ�ã�re����·���������� 
		//n_  a_���У�m_ a_����    �������貽��
		a = a_;
		n = n_;
		m = m_;
		start = s; 
		end = e;
		bestc = 65535;
		queue<Point*> q,recl;
		int dx[] = {-1,0,1,0};
		int dy[] = {0,1,0,-1};
		Point * E = new Point();
		E->x = s.x;
		E->y = s.y;
		E->level = 0;
		E->parent = NULL;
		//recl.push(E);
		while(true) {
			//�ﵽ�������߲����� 
			if(E->x==e.x && E->y==e.y && E->level<bestc) {
				bestc = E->level;
				best = E;
				break;
			}
			for(int i=0;i<4;++i) {
				//�ýڵ���� 
				if( (E->x+dx[i])>0 && (E->x+dx[i])<=n && 
					E->y+dy[i]<=m && E->y+dy[i]>0 &&
					a[(E->x+dx[i])*(m+1)+E->y+dy[i]]) {
					Point *N =  new Point();
					N->level = E->level+1;
					N->x = E->x+dx[i];
					N->y = E->y+dy[i];
					N->parent = E;
					a[(N->x)*(m+1)+N->y] = false;		//��Ϊһ����չ��㼴�� 
					q.push(N);
					recl.push(N);
				}
			}
			if(q.empty()) break;
			E = q.front();
			q.pop();
		}
		int ii=0;
		while(best) {
			re[best->level-ii].x = best->x ;
			re[best->level-ii].y = best->y ;
			//cout<<"("<<best->x<<','<<best->y<<")"<<endl;
			best=best->parent;
		}
		while(!recl.empty()) {
			delete recl.front();
			recl.pop();
		}
		return bestc; 
	}
	
};


int main()
{
	int n = 7,m=7;
	bool a[(n+1)*(m+1)];
	for(int i=0;i<(n+1)*(m+1);++i) a[i]= true;
	a[1*(m+1)+3] =a[2*(m+1)+3] = a[2*(m+1)+4] = a[3*(m+1)+5] = false;
	a[4*(m+1)+4] = a[4*(m+1)+5]	=a[5*(m+1)+5] = false;
	a[5*(m+1)+1] = a[6*(m+1)+2] =a[6*(m+1)+3] = a[7*(m+1)+3] = false;
	
	Point *re = new Point[(n+1)*(m+1)];
	int n_re = 0;
	FindPath fp;
	n_re = fp.Find(a,n,m,Point(3,2),Point(4,6),re);
	
	cout<<"��"<<n_re<<"��"<<endl;
	for(int i=0;i<=n_re;++i) {
		cout<<"("<<re[i].x<<','<<re[i].y<<")"<<endl;
	}
	delete[] re;
	return 0;
}
