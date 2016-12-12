#include <iostream>
#include <algorithm>

//������������-���ݷ�
//������ 


using namespace std;

class WorkAssign{

private:
	int n;			//n����
	int *time; 		//(n+1)*(n+1)���󣬱�ʾi�ָ�j����ķ��� 
	int	*best_c;	 	//���Ž� 
	int *curr_c;	//��ǰ���ŷ��� 
	int curr_t;		//��ǰ�ķ� 
	int best_t;		//���źķ� 

private:
	void Backtrack(int t) 
	{
		//��i����
		 
		if(t>n&&curr_t<best_t) {
			for(int i=0;i<=n;++i) {
				best_c[i]=curr_c[i];
				best_t = curr_t;
			}
			return ;
		}
		for(int i=t; i<=n; ++i) {
			curr_c[t] = i;
			curr_t += time[t*(n+1)+i];
			swap<int>(curr_c[t],curr_c[i]);
			Backtrack(t+1); 
			swap<int>(curr_c[t],curr_c[i]);
			curr_t -= time[t*(n+1)+i];
			curr_c[t] = 0;
		}
	}

public:
	int Solve(int n_,int *time_,int *best,int max_time)
	{
		n = n_;
		time = time_;
		best_c = best;
		curr_c = new int[(n+1)*(n+1)];
		curr_t = 0;
		best_t = max_time;
		Backtrack(1);
		
		delete []curr_c;
		return best_t;
	}


}; 
int main()
{
	int n=5;
	int time_[] = {
		0,0,0,0,0,0,
		0,1,2,3,4,5,
		0,5,1,2,3,4,
		0,4,4,1,1,4,
		0,4,2,4,1,5,
		0,5,4,2,3,1
	};
	int wu[n+1];
	WorkAssign wa;
	cout<<"��С�ķ�"<<wa.Solve(n,time_,wu,50)<<endl;
	cout<<"��ҵ����"<<endl;
	for(int i=1; i<=n; ++i) {
		cout<<wu[i]<<' ';
	}
	cin.get();
	return 0;
} 
