#include <iostream>
#include <queue>

//����װ�� -- ��֧�޽� 
using namespace std;

///��ͨ���� 
class QNode
{
public:
	QNode *parent;		//ָ�򸸽���ָ�� 
	bool LChild;		//���� 
	float weight;		//������ 
	
};

void EnQueue(queue<QNode*> &q, float wt, int i,int n,float bestw, 
			QNode *E,QNode *&bestE,int bestx[],bool ch ,queue<QNode*> &q2)
{
	//��������뵽����q�� 
	//q ָ����е�ָ�� 	//wt ��ǰ������ 		//i ��ǰ�Ӽ����Ĳ���
	// n ��װ��������   // bestw ��ǰ����ֵ  	//E	 ��ǰ��չ�ڵ� 
	//bestE ����ֵ��Ӧ�Ľ�� //bestx ���Ž�  	//ch ���ӱ�־    //q2���������� 
	if(i==n) {
		if(wt==bestw) {
			bestE = E;
			bestx[n] = ch?1:0;	
		}
 		return ;
	}
	
	QNode *b = new QNode;
	b->weight = wt;
	b->parent = E;
	b->LChild = ch;
	q.push(b);
	q2.push(b);	
}

float MaxLoading(float w[], float c,int n,int bestx[]) 
{
	//w[] ��װ������  //c �ִ������� 
	//n ��װ������    //bestx[] ���Ž� 
	//��������ֵ
	queue<QNode*> q,q2;
	q.push(NULL);
	int i=1;			//��ǰ�� 
    float bestw = 0; 	//���������� 
    float Ew = 0;		//��ǰ������	
    float r = 0;		//ʣ�������� 
	for(int j=2;j<=n;j++) r+=w[j];
	QNode *E = NULL,	//��ǰ��չ��� 
		  *bestE; 		//���Ž��Ӧ�Ľ�� 
		  
	while(true)  {
		float wt = Ew+w[i];
		//������� 
		if(wt <= c) {
			if(wt>bestw) bestw=wt;	//��ǰ�������Ž� 
			EnQueue(q,wt,i,n,bestw,E,bestE,bestx,true,q2); 
		}
		//�Һ��� 
		if(Ew+r>=bestw) {
			EnQueue(q,Ew,i,n,bestw,E,bestE,bestx,false,q2); 
		}
		E = q.front();
		q.pop();
		if(!E) {
			//������Ľ�β��־ 
			if(q.empty()) break;
			q.push(NULL);	//���뵱ǰ���β��־ 
			E = q.front();
			q.pop();
			++i;			//���Ӳ���
			r -= w[i]; 		//����ʣ�༯װ������ 
		}
		Ew = E->weight; //���µ�ǰ������ 
	}
	for(int j=n-1;j>0;--j) {
		bestx[j] = (bestE->LChild)?1:0;
		bestE = bestE->parent;
	}
	while(q2.empty()) {
		delete q2.front();
		q2.pop();
	}
	return bestw;
}






int main()
{
	int n = 3,sum; 
 	float w[] = {0,10,40,40}; 
 	int x[n+1]; 
 	//float bestw = ml.Solve(n,60.0,w,x); 
 	float bestw = MaxLoading(w,60.0,n,x); 
 	cout<<"����ֵ:"<<bestw<<endl<<"װ�ط�ʽ:\n"; 
 	for(int i=1; i<=n; ++i) { 
 		cout<<x[i]<<' '; 
 	} 
 	cin.get(); 
	
	return 0;
}

////���ȶ��� 
class QNode
{
public:
	QNode *parent;		//ָ�򸸽���ָ�� 
	bool LChild;		//���� 
	float uweight;		//�������Ͻ� 
	int level;			//���ڲ���  

};

class mycmp{
public:
	bool operator() (const QNode* a1,const QNode* a2) const
	{
		if( (a1->uweight) < (a2->uweight) ) return true;
		return false;
	}
};

void EnLiveQueue(priority_queue<QNode*,vector<QNode*>,mycmp > &q,  
			QNode *E,float wt, bool ch ,int i,queue<QNode*> &q2)
{
	//��������뵽����q�� 
	//q ָ����е�ָ�� 	//wt ��ǰ������ 		//i ��ǰ�Ӽ����Ĳ���
	//E	 ��ǰ��չ�ڵ� 
	//ch ���ӱ�־    //q2���������� 
		
	QNode *b = new QNode;
	b->parent =E;
	b->LChild = ch;
	b->level = i;
	b->uweight = wt;
	
	q.push(b);
	q2.push(b);	
}

float MaxLoading(float w[], float c,int n,int bestx[]) 
{
	//w[] ��װ������  //c �ִ������� 
	//n ��װ������    //bestx[] ���Ž� 
	//��������ֵ
	queue<QNode*> q2;
	priority_queue<QNode*,vector<QNode*>,mycmp > q;
	int i=1;			//��ǰ�� 
    float Ew = 0;		//��ǰ������	
    float r[n+1];		//ʣ�������� 
    r[n] = 0;
	for(int j=n-1;j>0;j--) r[j]=r[j+1]+w[j+1];
	QNode *E = NULL;	//��ǰ��չ��� 
		  
	while(i!=n+1)  {
		float wt = Ew+w[i];
		//������� 
		if(wt <= c) {
			EnLiveQueue(q,E,wt+r[i],true,i+1,q2); 
		}
		//�Һ��� 
		EnLiveQueue(q,E,Ew+r[i],false,i+1,q2);
		E = q.top();
		q.pop();
		i = E->level;
		Ew = E->uweight-r[i-1];
	}
	for(int j=n;j>0;--j) {
		bestx[j] = (E->LChild)?1:0;
		E = E->parent;
	}
	while(q2.empty()) {
		delete q2.front();
		q2.pop();
	}
	return Ew;
}
