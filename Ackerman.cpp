#include <iostream>
#include <cmath>

using namespace std;
//˫�ݹ麯��Ackerman 
//�������죬�ܿ��޷����� 
long long Ackerman(int n, int m) {
	if(n==1 && !m) return 2;
	if(!n && m>=0) return 1;
	if(n>=2 && !m) return n+2;
	if(n>=1 && m>=1) return Ackerman(Ackerman(n-1, m), m-1);
}
int main() 
{
	int n, m;
	cin>>n>>m;
	cout<<Ackerman(n,m)<<endl;
	
	
	return 0;
}
