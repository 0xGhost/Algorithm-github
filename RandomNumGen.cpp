#include <iostream>
#include <time.h> 

//����ͬ�����α����� 
using namespace std;

class CRandom
{
private:
	unsigned long rand_seed; //���������

public:
	CRandom(unsigned long s = 0)
	{
		if(!s) rand_seed = time(0);
		else rand_seed = s; 
	}
	
	unsigned long Random(unsigned long n) 
	{
		//0-n-1֮�������� 
		const unsigned long multiplier = 1194211693L;
		const unsigned long adder = 15465L;
		
		rand_seed = multiplier*rand_seed + adder;
		
		return (rand_seed>>16) % n;
	} 
	
	double fRandom(void) 
	{
		//����0-1֮������ʵ�� 
		const unsigned long large_number =  0x10000;
		return Random(large_number) / double(large_number);
	}
	
};

int main()
{
	CRandom rnd;
	
	int i,n=100000;
	int m[10];
	for(i=0;i<10;++i) m[i]=0;
	//�鿴����������ķֲ� 
	for(i=0;i<n;i++) 
		m[rnd.Random(1000)/100]++;
	for(i=0;i<10;++i)	
	 	cout<<m[i]/(double)n<<endl;
	cin.get();
	
	return 0;
}
