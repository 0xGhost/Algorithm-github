#include <iostream>
#include <cmath> 
#include <cstring>
///����

using namespace std;

//�������  PS:��ע��˼�����ʵ�֣�so ���򺬴� 
//  X = [AB]    Y = [CD]
//  X = A*2^n+B    Y = C*2^n+D
//  XY = (A*2^n+B)(C*2^n+D) = AC*2^n + (AD+BC)*2^n + BD
//  XY =  AC*2^n + ((A-B)(D-C)+AC+BD)*2^n + BD

void test();
long CharToNum(char a[],int len) {
	//�ַ�����תlong 
	long result = 0;
	if(len==0) return result; 
	if(a[0] == '-') {
		for(int i=1; i<len; ++i){
			result = result*10+(a[i]-'0'+0); 
		}
		return -result;
	} 
	else {
		for(int i=0; i<len; ++i){
			result = result*10+(a[i]-'0'+0); 
		}
		return result;
	}
}

void NumToChar(long long a, char re[]) {
	char it[20];
	int i=0,k=0;
	while(a!=0) {
		it[i++] = (a%10)+'0';
		a /= 10;
	}
	it[i] = '\0';
	for(int j=strlen(it)-1; j>=0; --j) {
		re[k++] = it[j];
		//cout<<it[j]<<' ';
	}
	//cout<<strlen(it)<<'$'<<k<<endl;
	re[k] = '\0';
}

void CharNumAdd(char[] a,char b[],int len,re[]) {
	//re=a-b
	//������� 
}

void LargeNumberMulti(char X[], char Y[],int len,int local,char result[]) {
	long a=0, b=0, c=0, d=0, item1, item2, item3;
	if(len<4) {
		a = CharToNum(X,len);
		b = CharToNum(Y,len);
		c = a*b;
		NumToChar(c,result);
		return ;
	}
	char ac[50],bd[50],abdc[50];
	//AC
	LargeNumberMulti(X,Y,len/2,local?,ac);				
	//BD
	LargeNumberMulti(X+len/2,Y+len/2,len/2,local?,bd);	
	//A-B
	//D-C
	//Merge 
}
int main()
{
	char a[] = "1234567823131212";
	char b[40];
	for(int i=0;i<40;++i) b[i] = '0';
	b[39]='\0';
	cout<<"a[]:\n";
	for(int i=0;i<strlen(a);++i) {
		cout<<a[i];
	}
	cout<<endl<<"b[]:\n";
	for(int i=0;i<strlen(b);++i) {
		cout<<b[i];
	}
	cout<<endl;
	
	
	LargeNumberMulti(a, a, strlen(a),0,b);


	for(int i=0;i<30;++i) {
		cout<<b[i]<<' '; 
	}
	//test(); 
	system("pause");
	return 0; 
} 



///////////////////////////////////////////////////////////
///////	��ͬλ��2^k���������						///////
///////	ò��ֻ�ܽ���2��4λ���ļ��㣬����ʧЧ	 	///////
///////	˼·��ȷ��ȱ����long�ͱ�ʾ��Χ		 		///////
///////////////////////////////////////////////////////////
int length(long x) {
	//�ж���������ֵ�λ��
	int i = 0; 
	do {
		++i;
		x=x/10; 
	}while(x!=0);
	return i;
}

long mult(long x,long y,int n) {
	long a,b,c,d,s,AC,BD;
	if (length(x)==1) //����������˸�����
		return x*y;
	else
	{
		a=long(x/pow(10,(n/2))); 		//ȡx����벿��
		//cout<<"A"<<a<<endl;
		b=long(x%long(pow(10,(n/2))));  //ȡx���Ұ벿��
		//cout<<"B"<<b<<endl;
		c=long(y/pow(10,(n/2))); 		//ȡy����벿��
		d=long(y%long(pow(10,(n/2))));  //ȡy���Ұ벿��
		AC = long(mult(a,c,n/2));
		BD = long(mult(b,d,n/2));
		s=AC*pow(10,n)+long(mult((a-b),(d-c),length(a-b))+AC+BD)*pow(10,n/2)+BD;//��ʽ
		return (s);
	}
}
void test() {
	long long x,y;
	cout<<"input x,y:"<<endl;
	cin>>x>>y;
	cout<<mult(x,y,length(x))<<endl;
} 


