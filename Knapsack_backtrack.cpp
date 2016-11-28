#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Object {
public:
	int ID; 	//ԭʼ��� 
	float d; 	//��λ�����ļ�ֵ
	
	bool operator< (const Object & a) const {
		return d>=a.d;
	}
	
};


template <class T_,class W_>
class Knapsack {
private:
	// in  
	int n;
	T_ *w; //ÿ����Ʒ���� 
	W_ *p; //ÿ����Ʒ��ֵ ,��Ҫ�Ӵ�С���� 
	T_ c; 		 //������������ 
	
	// out
	W_ bestp;	//��ǰ�����ؼ�ֵ 
	int *bestx;	//��ǰ���Ž�
	
	//interior
	int *x;		//��ǰ��
	T_ cw;		//��ǰ������ 
	W_ cp; 		//��ǰ��ֵ 


private:
	W_ Bound(int i) { //�����Ͻ� 
		T_ c_left = c- cw;
		W_ b = cp;
		while(i<=n && w[i]<=c_left)   {
			c_left -= w[i];
			b+=p[i];
			++i;
		}
		if(i<=n) b+=p[i]*c_left/w[i];
		return b;
	}	 
	void Backtrack(int i) {
		if(i>n) {
			//����Ҷ��
			bestp = cp;
			for(int j=1; j<=n; ++j) bestx[j] = x[j]; 
			return ;
		}

		//�������ӽڵ� 
		if(cw+w[i]<=c) {//Լ������ 
			x[i] = 1;
			T_ cw_backup = cw;
			W_ cp_backup = cp; 
			cw+=w[i];
			cp+=p[i];
			Backtrack(i+1);
			cw = cw_backup; 
			cp = cp_backup;
		}
		//�������ӽ��
		if(Bound(i+1)>bestp) { //�޽纯�� 
			x[i] = 0;
			Backtrack(i+1);
		} 	
	} 
	/*void Backtrack_Iterative(int i) {
		//
		int k = 1;
		bool flag = true;
		while(k>0) {
			//������
			if(flag && cw+w[k]<=c) {//Լ������ 
				x[k] = 1;
				T_ cw_backup = cw;
				cw+=w[i];
				Backtrack(i+1);
				cw = cw_backup; 
			}
			
			
			
			//������  
			if(flag && cw+r>bestw) { //�޽纯�� 
				x[i] = 0;
				Backtrack(i+1);
			} 
			
		}
	
	
	}*/
public:
	W_ Solve(int n_,T_ c_,const T_ *w_,const W_ *p_,int *bestx_) {
		//n_ ��Ʒ����
		//c_ �������������
		// w_[] ��Ʒ������
		// p_[] ��Ʒ��ֵ 
		// bestx_[] ���Ž� 
		//�������ż�ֵ 
		n = n_;
		c = c_;
		w = new T_[n+1];
		p = new W_[n+1]; 
		bestx = bestx_;
		
		x =  new int[n+1];
		cw = 0;
		cp = 0;
		bestp = 0;
		Object *Q = new Object[n];
		T_ w_total = 0; //������
		W_ p_total = 0; //�ܼ�ֵ 
		
		for(int i=1; i<=n; i++) {
			Q[i-1].ID = i;
			Q[i-1].d = p_[i]/(float)w_[i]; ////!!!
			w_total += w_[i]; 
			p_total += p_[i];
		}
		//����Ƿ�ȫ��װ�� 
		if(w_total < c) {
			delete [] Q;
			for(int i=1; i<=n; ++i) x[i] = 1;
			return p_total; 
		}
		
		sort(Q,Q+n); //��Ʒ����λ��ֵ�Ӵ�С���� ,�Ա�Bound() 
		//һ����� 
		for(int i=1; i<=n; ++i) {
			p[i] = p_[ Q[i-1].ID ];
			w[i] = w_[ Q[i-1].ID ]; 
		}
		Backtrack(1);
		
		//���Ž� 
		for(int i=1; i<=n; ++i) 
			x[Q[i-1].ID] = bestx[i];
		for(int i=1; i<=n; ++i) 
			x[i] = bestx[i];
			
		delete [] p;
		delete [] w;
		delete [] x;
		return bestp;
	}
	
};



int main()
{
	
	int n = 4,sum;
	Knapsack<int,float> ml;
	int w[] = {0,3,5,2,1};
	float p[] = {0,9,10,7,4};
	int x[n+1];
	float bestp = ml.Solve(n,7,w,p,x);
	
	cout<<"����ֵ:"<<bestp<<endl<<"װ�ط�ʽ:\n";
	for(int i=1; i<=n; ++i) {
		cout<<x[i]<<' ';
	}
	
	cin.get();
	return 0;
}
