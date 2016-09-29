#include <iostream>
#include <cmath> 
//ѭ�����̰���
//��������n=2^k 

using namespace std;
const int n = 8;

void timetable(int k,int a[][n]) {
	// n = 2^k 
	//�ǵݹ�д�� 
	int n = 1; 
	for(int i=0;i<k;++i) n*=2; 
	for(int i=0;i<n;++i) a[0][i] = i+1;
	int m=1;						//��ĳߴ� 
	for(int s=0;s<k;++s) {			//ѭ��ÿ������ 
		n/=2;
		for(int t=0;t<n;++t)		// tΪÿ����ı�� 
			for(int i=m;i<2*m;++i)	// i=column, j=row 
				for(int j=m;j<2*m;++j){
					a[i][j+t*m*2] = a[i-m][j+t*m*2-m];
					a[i][j+t*m*2-m] = a[i-m][j+t*m*2];
				}
			
		m*=2;
	}
}

void timetable(int m,int t,int a[][n]) {
	//m��Ĵ�С, t��ı�ţ�a��������
	//�ݹ�д�� 
	if(m==2) {
		a[t][1]=a[t+1][0];
		a[t+1][1]=a[t][0];
		return ;
	}
	timetable(m/2,t,a);
	timetable(m/2,t+m/2,a);
	int sub_m = m/2; 
	for(int i=0;i<sub_m;++i) { 			//row
		for(int j=0;j<sub_m;++j) {		//column
			//�¾���˺ô󾢲ŷ����д�ע��tʵ�ʱ�ʾ�����У������в�ʹ��t 
			a[t+i+sub_m][j+sub_m]=a[t+i][j];//���½�  
			a[t+i][j+sub_m]=a[t+i+sub_m][j];//���Ͻ� 
		}
	}
}

int main() {
	
	int a[n][n];
	for(int i=0;i<n;++i) a[i][0]=i+1;
	//timetable(3,a);
	timetable(n,0,a); 
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<a[i][j]<<'\t';
		}
		cout<<endl;
	}
	

	
	return 0;
}
