#include <iostream>

//����������������
//���ݷ� 


//�㷨ʱ�临�ӶȲ����밡��7*7�������ϸ��Ӷȶ����� 
//8*8����������������˽�50���� 
using namespace std;

class Point{
public:
	int x,y;
	Point(int x_,int y_) {
		x=x_;y=y_;
	}
	Point() {
		x=0;y=0;
	}
};

class Monitor{
private:
	int *rooms; 	// m*n�����ʾ���䱻���˼��� 
	int m;			//m�� 
	int n; 			//n�� 
	
	bool *robot;	//m*n�����ʾ��ǰ��Ļ����˰��� 
	bool *result;	//���ذ��Ž�� 
	
	int bestc;		//���ٻ�����λ��
	int curr_c;		//��ǰ������λ��
	
	int not_safe;	//��ǰ����ȫ������ 
	
	
private:
	void Change(Point &t)
	{
		//room,not_safe�� robot�䶯 
		//�м� 
		if(t.x>0&&t.y>0&&t.x<=m&&t.y<=n) {
			robot[t.x*(n+1)+t.y] = true;
			rooms[t.x*(n+1)+t.y]++; 
			if(rooms[t.x*(n+1)+t.y]==1) not_safe--;
		} else {
			return;
		}
		
		
		//�� 
		if(t.x-1>0&&t.y>0&&t.x-1<=m&&t.y<=n) { 
			rooms[(t.x-1)*(n+1)+t.y]++;
			if(rooms[(t.x-1)*(n+1)+t.y]==1) not_safe--;
		}
		//�� 
		if(t.x>0&&t.y+1>0&&t.x<=m&&t.y+1<=n) { 
			rooms[t.x*(n+1)+t.y+1]++;
			if(rooms[t.x*(n+1)+t.y+1]==1) not_safe--; 
		} 
		//��
		if(t.x+1>0&&t.y>0&&t.x+1<=m&&t.y<=n) { 
			rooms[(t.x+1)*(n+1)+t.y]++;
			if(rooms[(t.x+1)*(n+1)+t.y]==1) not_safe--;
		} 
		//��
		if(t.x>0&&t.y-1>0&&t.x<=m&&t.y-1<=n) { 
			rooms[t.x*(n+1)+t.y-1]++;
			if(rooms[t.x*(n+1)+t.y-1]==1) not_safe--; 	
		}
	}
	
	void Recover(Point &t) 
	{
		//room,not_safe�� robot�ָ�
		if(t.x>0&&t.y>0&&t.x<=m&&t.y<=n) {
			robot[t.x*(n+1)+t.y] = false;
			rooms[t.x*(n+1)+t.y]--; 
			if(rooms[t.x*(n+1)+t.y]==0) not_safe++;
		} else {
			return;
		}
		
		//�� 
		if(t.x-1>0&&t.y>0&&t.x-1<=m&&t.y<=n) {
			rooms[(t.x-1)*(n+1)+t.y]--;
			if(rooms[(t.x-1)*(n+1)+t.y]==0) not_safe++;
		}		
		//�� 
		if(t.x>0&&t.y+1>0&&t.x<=m&&t.y+1<=n) {
			rooms[t.x*(n+1)+t.y+1]--;
			if(rooms[t.x*(n+1)+t.y+1]==0) not_safe++;
		} 
		//�� 
		if(t.x+1>0&&t.y>0&&t.x+1<=m&&t.y<=n) {
			rooms[(t.x+1)*(n+1)+t.y]--;
			if(rooms[(t.x+1)*(n+1)+t.y]==0) not_safe++;
		}			
		//��	
		if(t.x>0&&t.y-1>0&&t.x<=m&&t.y-1<=n) {
			rooms[t.x*(n+1)+t.y-1]--;
			if(rooms[t.x*(n+1)+t.y-1]==0) not_safe++; 
		}		
	} 
	
	Point FindNotSafe(Point &t)const
	{
		//�ҵ�һ������ȫ���� 
		for(int i=t.x; i<=m; ++i) {
			for(int j=1; j<=n; ++j) {
				if(i>0&&rooms[i*(n+1)+j]==0) {
					//cout<<"("<<i<<","<<j<<")"<<endl;
					return Point(i,j);
				}
			}
		}
		return Point(0,0);//�������� 
	}
	
	void Backtrack(Point t)
	{
		//if(not_safe<0) {
		//	cout<<"("<<t.x<<","<<t.y<<")"<<endl;
		//	cout<<"Not safe"<<not_safe<<" C "<<curr_c<<endl;
		//	return;
		//}
		
		if(not_safe==0&&curr_c<bestc) {
			for(int i=0; i<(m+1)*(n+1); ++i) {
				result[i] = robot[i];	
				
				//cout <<"#" <<result[i]<<"#"<< endl;
			}
			bestc=curr_c;
			return ;
		}
		//������ 
		if(t.x<=0 || t.y<=0 || t.x>m || t.y>n)
			return ;
		Point x1,x2;
		//(t.x,t.y)
		Change(t);
		curr_c++;
		x1 =  FindNotSafe(t);
		//cout << "(" << x1.x << "," << x1.y << ")" << endl;
		Backtrack(x1);
		Recover(t);
		curr_c--;
		
		//(t.x,t.y+1)
		x2.x = t.x;
		x2.y = t.y+1;
		if (x2.x > 0 && x2.y > 0 && x2.x <= m && x2.y <= n) {
			Change(x2);
			curr_c++;
			x1 = FindNotSafe(t);
			Backtrack(x1);
			Recover(x2);
			curr_c--;
		}
		
		
		//(t.x+1,t.y)
		x2.x = t.x+1;
		x2.y = t.y;
		if (x2.x > 0 && x2.y > 0 && x2.x <= m && x2.y <= n) {
			Change(x2);
			curr_c++;
			x1 = FindNotSafe(t);
			Backtrack(x1);
			Recover(x2);
			curr_c--;
		}		
	}
	
	
public:
	int Solve(int m_,int n_,bool *res) 
	{
		//m_ �� n_�� res[] ���հ������� 
		//�����������ٻ������� 
		m =m_; n=n_; 
		rooms=(int*)malloc(sizeof(int)*(n+1)*(m+1));
		robot=(bool*)malloc(sizeof(bool)*(n+1)*(m+1));
		for(int i=0;i<(n+1)*(m+1);++i) {
			rooms[i] = 0;
			robot[i] = false;
		}
		result = res;
		bestc = m*n;
		curr_c = 0;
		not_safe=m*n;	//��ǰ����ȫ������ 
		Backtrack(Point(1,1)); 
		free(rooms);
		free(robot);
		return  bestc; 
	}
		
}; 

void show(int m_,int n_,bool *res) 
{
	for(int i=1; i<=m_; ++i) {
		for(int j=1; j<=n_; ++j) {
			if(res[i*(n_+1)+j]) cout<<"# ";
			else cout<<"O ";
		}
		cout<<'\n';
	}
}



int main(int argc,char *argv[])
{
	int n = 4, m = 4;
	cout << "���뷿������С����";
	cin >> m >> n;
	Monitor sl;
	bool *res = new bool[(n+1)*(m+1)];
	cout<<"�����ڱ�:"<<sl.Solve(m,n,res)<<endl;
	show(m,n,res);
	
	int aa;
	cin>>aa;
	
	return 0;
} 
