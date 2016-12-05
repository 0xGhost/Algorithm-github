#include <iostream>
#include <stdlib.h>

//Luomio and Zhuliye ���� P155 
//����ŷ������Ҷ���Թ����� 

using namespace std;

typedef struct {
	int x;
	int y;
}Point;		//��ʾһ�Թ����� 


void FindWay(int *path,int n,int m,Point start,Point end) {
	while(start.x!=end.x || start.y!=end.y) {
		cout<<"("<<start.x<<','<<start.y<<")"<<' ';
		switch(path[start.x*(m+1)+start.y]) {
			case 0:	start.x--; break;
			case 1:	start.x--; start.y++; break;
			case 2:	start.y++; break; 
			case 3: start.x++; start.y++; break;
			case 4: start.x++; break;
			case 5:	start.x--; start.y--; break;
			case 6: start.y--; break;
			case 7:	start.y--; break;
			default: cout<<"??\n"; return ;
		}
	}
	cout<<"("<<end.x<<','<<end.y<<")";
	return ;
}

void showAll(int *path,int n,int m) 
{
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;j++) {
			switch(path[i*(m+1)+j]) {
				case 0:	cout<<"��\t"; break;
				case 1:	cout<<"����\t"; break;
				case 2:	cout<<"��\t"; break; 
				case 3: cout<<"����\t"; break;
				case 4: cout<<"��\t"; break;
				case 5:	cout<<"����\t"; break;
				case 6: cout<<"��\t"; break;
				case 7:	cout<<"����\t"; break;
				default :cout<<"��\t";break;
			}
		}
		cout<<endl;
	}
	
	
}


class TravelMaze {

private:
	Point start,end;
	//Point current_point;
	
	int best_num_turn;    	//����ת����� 
	int num_traved;			//��¼�������ٷ��� 
	int curr_num_turn;		//��ǰת����� 
	int *TX ;
	int *TY ;
	int n,m;
	int b; 					//���ɽ������� 
	bool *maze;//�Թ� 
	
	int *curr_path;			//��ǰ��õ���һ������ 0-7 ˳ʱ�� 
	int *best_path;			//���Ž�ĸõ���һ������ 0-7 ˳ʱ�� 
	
private:
	bool IsOK(Point current_point)
	{
		//�Ƿ񵽴ﲢ������ת������ 
		if(num_traved==n*m-b && 
			current_point.x==end.x && current_point.y==end.y)
			if(curr_num_turn<best_num_turn) 
					return true;
		return false;
	}
	
	
	void BackTrack(Point current_point,int dir)
	{
		if(IsOK(current_point)) {
			curr_path[current_point.x*(m+1)+current_point.y] = -1;
			for(int i=1; i<=n; ++i) 
				for(int j=1; j<=m; ++j) {
					best_path[i*(m+1)+j] =curr_path[i*(m+1)+j];
					best_num_turn=curr_num_turn;
				}
			return;
		}
		if(current_point.x == end.x && current_point.y == end.y)
			return ;
		bool flag = true;
		Point tmp;
		for(int i=0; i<=7; ++i)	 {
			curr_path[current_point.x*(m+1)+current_point.y] = i;
			tmp.x = current_point.x + TX[i];
			tmp.y = current_point.y + TY[i];
			//�Ƿ����Թ��� 
			if(tmp.x<=0 || tmp.y<=0 || tmp.x>n || tmp.y>m)
				continue;
			//�Ƿ��Ѿ����� 
			if(!maze[tmp.x*(m+1)+tmp.y]) {
				maze[tmp.x*(m+1)+tmp.y] = true;
				if(i!=dir) ++curr_num_turn; //�Ƿ�ת��
				++num_traved;
				BackTrack(tmp,i);
				--num_traved;
				if(i!=dir) --curr_num_turn; 
				//curr_path[current_point.x*(m+1)+current_point.y] = -1; 
				maze[tmp.x*(m+1)+tmp.y] = false;
			}
		}
 	} 	
	
public:
	int Solve(int n_,int m_,Point bb[],int b_,Point start_,Point end_,int *path) 
	{
		n = n_;				//n�� 
		m = m_;				//m �� 
		b = b_;				//���ɽ������� 
		start = start_;		//��ʽλ�� 
		end = end_;			//����λ�� 
		best_num_turn = n*m+1;    	//����ת����� 
	    num_traved = 1;				//��¼�������ٷ��� 
		curr_num_turn = 0;
		maze = new bool [(n+1)*(m+1)];
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=m;++j) 
				maze[i*(m+1)+j] = false;
		curr_path = new int [(n+1)*(m+1)];
		best_path = path;
		
		TX = new int[8];
		TY = new int[8];
		int tx[] = {-1,-1,0,1,1,1,0,-1};
		int ty[] = {0,1,1,1,0,-1,-1,-1};
		for(int i=0;i<=7;++i) {
			TX[i]=tx[i];
			TY[i]=ty[i];
		}
		for(int i=0;i<b;++i) {
			curr_path[bb[i].x*(m+1)+bb[i].y] = -1;
			maze[bb[i].x*(m+1)+bb[i].y] = true;
		}
		maze[start.x*(m+1)+start.y] = true;
		BackTrack(start_,-1);
		
		delete[] TX;
		delete[] TY;
		delete[] maze;
		delete[] curr_path;
		return best_num_turn;
	}
};



int main()
{
	
	int n = 3,m=3;
	Point a[4];
	a[0].x = 1;a[0].y = 2;
	a[1].x = 3;a[1].y = 7;
	a[2].x = 5;a[2].y = 5;
	a[3].x = 8;a[3].y = 2;
	int path[(n+1)*(m+1)];
	Point start,end;
	start.x = start.y = 1;
	end.x = end.y = 3;
	
	TravelMaze tm;
	int least=tm.Solve(n,m,a,1,start,end,path);
	cout<<"����ת��"<<least<<endl<<"Path\n";
	
	//FindWay(path,n,m,start,end);
	showAll(path,n,m);
	cin.get();
	return 0;
}
