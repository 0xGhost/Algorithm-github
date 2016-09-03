#include <iostream>

using namespace std;

//��ŵ���ƶ�

void move(int a,int b) {
	cout<<"move "<<a<<" to"<<b<<endl; 
}
void move(int n,int a,int b) {
	cout<<"move "<<n<<" from "<<a<<" to "<<b<<endl; 
}
 
void hanoi(int n, int a, int b, int c) {
	if(n>0) {
		hanoi(n-1, a, c, b);
		move(a,b);
		hanoi(n-1, c, b, a);
	}
} 

void hanoi2(int n, int x, int y, int z) {
	//����x�ϰ�ֱ���Ӵ�С�����϶��±��Ϊ1-n��n��ԭ�̰�����
	//�ᵽz,y���� 
	if(n==1) move(1,x,z);
	else {
		hanoi2(n-1, x, z, y);
		move(n, x, z);
		hanoi2(n-1, y, x, z);
	}
} 
int main()
{
	int n;
	cout<<"��������"<<endl;
	cin>>n;
	//hanoi(n, 1, 2, 3);	
	hanoi2(n, 1, 2, 3);
	return 0; 
} 
