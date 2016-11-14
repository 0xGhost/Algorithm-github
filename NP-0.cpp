#include <iostream> 
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <vector>

//�����������	NP 
using namespace std;

class Job{
public:
	int id;
	int time;
	operator int () const {
		return time;
	} 
	
};
class Machine{
public:
	int id;
	int avail;
	operator int () const {
		return avail;
	}
};
class cmp2{
public:
    bool operator ()(Machine a,Machine b){
        return int(a)>int(b);//�����ж� 
    }
};


bool cmp (Job a,Job b){
	
	if(int(a)>int(b)) return true;
	return false;
} 


template <class T_>
void Greedy(T_ a[],int n,int m){
	//a(in) ��ҵ���� [1-n]
	//n(in)��ҵ��
	//m(in)������  
	sort((a+1),(a+(n+1)),cmp);
	
	if(n <= m) {
		cout<<"ÿ��ҵ������һ������\n";
		cout<<"���ʱ��"<<int(a[0])<<endl; 
	} else {
		//���л������ȶ��� 
		priority_queue<Machine,vector<Machine>,cmp2> q; 	//���ȼ����� 
		
		Machine x;
		for(int i=1;i<=m;++i) {
			x.avail = 0;
			x.id = i;
			q.push(x);
		}
		for(int i=n;i>=1;i--) {
			x = q.top();
			q.pop();
			cout<<"������"<<x.id<<"��"<<x.avail
				<<"��"<<(x.avail+a[i].time)<<"��ʱ��������ҵ"
				<<a[i].id<<endl;
				x.avail+=a[i].time;
				q.push(x); 
		}
	}
	
	
} 

int main()
{
	Job a[11];
	srand(time(NULL));
	
	for(int i=1;i<=10;i++){
		a[i].id = i;
		a[i].time = rand()%5+5;
	}
	
	Greedy<Job>(a,10,4);
	
	cin.get();
	return 0;
}
