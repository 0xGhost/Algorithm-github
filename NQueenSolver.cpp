#include <iostream>
#include <stdlib.h>

using namespace std;

class NQueenSolver {
private:
	int n;	//�ʺ����� 
	int *x;	//ÿһ�еĻʺ����ڵ���
	int sum;	//��ǰ������� 
	
private:
	bool Validate(int k) {
		//��֤��k�лʺ�λ���Ƿ����
		for(int i=1; i<k; ++i) {
			if((k-i)==abs(x[i]-x[k]) || x[i]==x[k])
				return false;
		}
		return true;
	}
	void Backtrack(int t) {
		if(t>n) {	//�����ռ�����Ҷ��  
			++sum;	
			if(sum==1) show_plan();
		} else {
			//�������е��ӽ��
			for(int i=1; i<=n; ++i) {
				x[t] = i;
				if(Validate(t)) 
					Backtrack(t+1);
			}
		}
	} 
	void Backtrack_Iterative() {
		int k =1 ; //�������
		x[1] = 0;
		while(k>0) {
			++x[k];
			//���������ӽ�㣬Ѱ������Լ�����ӽ�� 
			while(x[k]<=n && !Validate(k)) ++x[k];
			if(x[k]<=n) { //�ҵ�����Լ�����ӽ�� 
				if(k==n) { //����Ҷ�ӽ��  
					++sum;
					if(sum == 1) show_plan(); 
				} else {
					//������һ���� 
					++k;
					x[k] = 0; 
				}
			} else {
				//�����ӽ�������ϣ����� 
				--k;
			}							
		}
	} 
	void show_plan() {
		for(int i=1; i<=n; ++i) {
			for(int j=1; j<=n; ++j) {
				if(x[i]==j) cout<<"Q ";
				else cout<<"* ";
			}
			cout<<endl;
		}
	}
public:
	int Solve(int num_queens) {
		//num_queens�ʺ�����
		//������� 
		n = num_queens;
		sum = 0;
		x = new int[n+1];
		Backtrack(1);
		delete []x;
		return sum;
	}
	int Solve_iterative(int num_queens) {
		//num_queens�ʺ�����
		//������� 
		n = num_queens;
		sum = 0;
		x = new int[n+1];
		Backtrack_Iterative();
		delete []x;
		return sum;
	}
};


int main()
{
	
	int num = 0,sum;
	cout<<"����ʺ���\n";
	cin >> num;
		
	NQueenSolver qs;
	sum = qs.Solve(num);
	//sum = qs.Solve_iterative(num);
	cout<<num<<"�ʺ�����������:"<<sum<<endl; 
	
	return 0;
}
