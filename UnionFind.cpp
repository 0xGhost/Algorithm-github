#include <iostream>


using namespace std;

class CUnionFind {
public:
	CUnionFind();
	~CUnionFind(); 
	void Init(int num_elem) ;
	
	int FindSubSet(int elem_id) ;
	
	void SubSetUnion(int set1,int ste2);
protected:
	int n_;			//Ԫ������ 
	int *parent_id_;	//ÿ��Ԫ�صĸ��ڵ�����,-1��ʾ�õ�Ϊ���ڵ�
	int *depth_;		//ÿ��Ԫ��������������� 
	void Release();
};

void CUnionFind::Release() {
	n_ = 0;
	if(parent_id_) {
		delete [] parent_id_;
		parent_id_ = NULL;
	}
		
	if(depth_) {
		delete [] depth_;
		depth_ = NULL;
	}
}

CUnionFind::CUnionFind() {
	n_ = 0;
	parent_id_ = NULL;
	depth_ = NULL; 
}
 
CUnionFind::~CUnionFind() {
	Release();
}
void CUnionFind::Init(int num_elem) {
	//Ԫ�ر�Ŵ�1��ʼ
	Release();
	n_ = num_elem;
	parent_id_ = new int[n_];
	depth_ = new int[n_];
	for(int i=0;i<n_;++i) {
		parent_id_[i]=-1;
		depth_[i]=0;
	}
}
	
int CUnionFind::FindSubSet(int elem_id) {
	//����Ԫ��elem_id�����Լ��ı��
	int i = elem_id-1;
	while(parent_id_[i]!=-1)
		i = parent_id_[i];
	return i;
}
void CUnionFind::SubSetUnion(int set1,int set2) {
	//�ϲ�set1,set2 
	if(set1 == set2) return ;
	if(depth_[set1]==depth_[set2]) {
		parent_id_[set2] = set1;
		depth_[set1]++;
	} else if(depth_[set1]<depth_[set2]){
		parent_id_[set1] = set2;
	} else {
		parent_id_[set2] = set1;
	}
} 
int main() 
{
	CUnionFind uf;
	uf.Init(6);
	int i,j,k;
	int iv[][2] = {
	{1,3},{4,6},{2,5},{3,6},{2,3} };
	
	for(k=0;k<5;k++) {
		i = uf.FindSubSet(iv[k][0]);
		j = uf.FindSubSet(iv[k][1]);
		uf.SubSetUnion(i,j);
	
		cout<<' '<<iv[k][0]<<"U"<<iv[k][1]<<endl;
		for(i=0;i<6;++i) {
			j = uf.FindSubSet(i+1);
			if(i)
				cout<<',';
			cout<<i+1<<"["<<j+1<<"]";
		}
		cout<<endl;
	}
	
	
	return 0;
} 
