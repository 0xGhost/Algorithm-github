#include <iostream>
#include <stdlib.h>
#include <stack>
using namespace std;

template <class T_>
class MaxLoading {
private:
	// in  
	int n;
	const T_ *w; //ÿ����װ������ 
	T_ c; 		 //�������� 
	
	// out
	T_ bestw;	//��ǰ���������� 
	int *bestx;	//��ǰ���Ž�
	
	//interior
	int *x;		//��ǰ��
	T_ cw;		//��ǰ������ 
	T_ r; 		//��ǰʣ����Ʒ����
	 
	void Backtrack(int i) {
		if(i>n) {
			//����Ҷ��
			bestw = cw;
			for(int j=1; j<=n; ++j) bestx[j] = x[j]; 
			return ;
		}
		//����ʣ������
		T_ r_backup = r;
		r -= w[i];
		
		//�������ӽڵ� 
		if(cw+w[i]<=c) {//Լ������ 
			x[i] = 1;
			T_ cw_backup = cw;
			cw+=w[i];
			Backtrack(i+1);
			cw = cw_backup; 
		}
		//�������ӽ��
		if(cw+r>bestw) { //�޽纯�� 
			x[i] = 0;
			Backtrack(i+1);
		} 
		r = r_backup;
		
	} 
	void Backtrack_Iterative(void) {
		int i = 1;
		
 		while(true) {
			//�������ӽڵ� 
			while(i<=n && cw+w[i]<=c) {
				r -=w[i];
				cw +=w[i];
				x[i] = 1;
				++i;
			}
			if(i>n) {
				for(int j=1; j<=n; ++j) 
					bestx[j] =x[j];
				bestw = cw;
			} else {
				//����������
				r-=w[i];
				x[i] = 0;
				++i; 
			}
			//��֦���� 
			while( cw+r<=bestw ) {
				--i;
				while(i>0 && !x[i]) {
					//������������ 
					r += w[i];
					--i; 
				}
				if(i==0)
					return ;
				//����������
				x[i] = 0;
				cw -= w[i];
				++i; 
			}
		}
	}
public:
	int Solve(int n_,T_ c_,const T_ *w_,int *bestx_) {
		//n_ ��Ʒ����
		//c_ ���������
		// w_[] ��Ʒ������
		// bestx_[] ���Ž� 
		n = n_;
		c = c_;
		w = w_;
		bestx = bestx_;
		
		x =  new int[n+1];
		cw = 0;
		bestw = 0;
		
		r = 0;
		for(int i=1; i<=n; ++i) r+=w[i];
		
		Backtrack(1);
		delete [] x;
		return bestw;
	}
	int Solve_Iterative(int n_,T_ c_,const T_ *w_,int *bestx_) {
		//n_ ��Ʒ����
		//c_ ���������
		// w_[] ��Ʒ������
		// bestx_[] ���Ž� 
		n = n_;
		c = c_;
		w = w_;
		bestx = bestx_;
		
		x =  new int[n+1];
		cw = 0;
		bestw = 0;
		
		r = 0;
		for(int i=1; i<=n; ++i) r+=w[i];
		
		Backtrack_Iterative();
		delete [] x;
		return bestw;
	}
	
};


int main()
{
	
	int n = 3,sum;
	MaxLoading<float> ml;
	float w[] = {0,10,40,40};
	int x[n+1];
	//float bestw = ml.Solve(n,60.0,w,x);
	float bestw = ml.Solve_Iterative(n,60.0,w,x);
	cout<<"����ֵ:"<<bestw<<endl<<"װ�ط�ʽ:\n";
	for(int i=1; i<=n; ++i) {
		cout<<x[i]<<' ';
	}
	
	cin.get();
	return 0;
}
