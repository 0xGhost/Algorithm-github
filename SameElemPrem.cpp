#include <iostream>
#include <algorithm>


///���ظ�Ԫ�ص�ȫ�������� 

using namespace std;

int ElemCount = 0;
// ����Ԫ��
void swap(char &a, char &b) {
    char tmp;
    tmp = a;
    a = b;
    b = tmp;
}
 
// �ݹ�ȫ����
void perm(char c[], int s, int e) {
    if(s == e) {    // ��ʼindex == ����index 
        for( int i = 0; i <= e; i ++)
            cout << c[i];
        cout << endl;
        ElemCount ++;
    }else {
        for(int i = s; i <= e;  i++) {
            int mark = 0;
            for(int j = s; j < i; j ++) {
                if(c[j] == c[i]) {
                    mark = 1;
                    break;
                }
            }
            if(1 == mark) 
                continue;
            swap(c[s], c[i]);
            perm(c, s + 1, e);
            swap(c[s], c[i]);
        }
    }
}
 
 
void Algo1() {
	int n;
    char c[16];
    char tmp;
    std::cin >> n;
    tmp = getchar();    // ���ܻس�
    if(1 <= n && n <= 15) {
        for( int i = 0; i < n; i ++) {
            c[i] = getchar();
        }
        perm(c, 0, n - 1);
        cout << ElemCount << endl;
    }
}
/////////////////////////////////////////////////
void BySTL() {
	
	int a[]={1,1,6,7,8};
	
	while(next_permutation(a,a+5))
	{
		for(int i = 0; i < 5; i++)
			printf("%d ", a[i]);
		printf("\n");
	}
} 

int main()
{
	Algo1();
	//BySTL();
    return 0;
}



