#include <iostream>
#include <cmath>
//����

using namespace std;
const int n = 8;
int Board[n][n];
int tile=1;
void FillChessBoard(int tr, int tc, int dr, int dc, int size) {
	/// tr,tc ���Ͻ����к� 
	/// dr, dc ���ⷽ�����к�
	/// size = 2^k 
	
	if(size == 1) return;
	int t = tile++;//L�ι��ƺ�
	int s = size/2;//�ָ�����
	
	//������Ͻ�������
	if(dr<tr+s && dc<tc+s)
		FillChessBoard(tr,tc,dr,dc,s);//���ⷽ���ڴ�
	else {
		Board[tr+s-1][tc+s-1] = t;//����������½�
		FillChessBoard(tr,tc,tr+s-1,tc+s-1,s);//����������½� 
	} 
	
	//������Ͻ�������
	if(dr<tr+s && dc>=tc+s) 
		FillChessBoard(tr,tc+s,dr,dc,s);//���ⷽ���ڴ�
	else {
		Board[tr+s-1][tc+s] = t;//����������½�
		FillChessBoard(tr,tc+s,tr+s-1,tc+s,s); //����������½�
	}
	
	//������½�
	if(dr>=tr+s && dc<tc+s)
		FillChessBoard(tr+s,tc,dr,dc,s);//���ⷽ���ڴ�
	else {
		Board[tr+s][tc+s-1] = t;//����������Ͻ�
		FillChessBoard(tr+s,tc,tr+s,tc+s-1,s); 
	}
	
	//������½�
	if(dr>=tr+s && dc>=tc+s)
		FillChessBoard(tr+s,tc+s,dr,dc,s);//���ⷽ���ڴ�
	else {
		Board[tr+s][tc+s] = t;//����������Ͻ�
		FillChessBoard(tr+s,tc+s,tr+s,tc+s,s); 
	}
	
} 

int main() 
{
	FillChessBoard(0,0,4,4,8);
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<Board[i][j]<<'\t';
		}
		cout<<endl;
	}
	system("pause"); 
	return 0; 
}
