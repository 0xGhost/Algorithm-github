#include <iostream>
#include <cmath>
#include <list>
#include <fstream>
#include <cstdlib>
//kmeans�㷨 
//����Ԥ���������ȥ�� 
using namespace std;

class Map{
public:
	int row,col;
	int valid;			//��Чֵ
	float value[4];
	int which_center = -1; 
	
public:
	Map() {
		row = 0;
		col = 0;
		valid = 0;
		value[0] = value[1] =value[2] =value[3]= 0;
	}	 
	void calc_row_column(int x,int y) {
		row = x*300;
		col = y*300;
	}
	bool is_valid() {
		return (value[0]!=0||value[1]!=0||value[2]!=0||value[3]!=0);
	}
};

class vector4 {
public:
	float val[4];
	float& operator[](int n) {
		return val[n];
	}
	vector4() {
		val[0] = val[1] = val[2] = val[3] =0;
	}
};

template<typename T_>
class KCenter {
public:
	int index;		//��� 
	vector4 center;		//���� 
	int num;		//��Ա�� 
	
	
	void set_kcenter(int index,vector4 center){
		this->index = index;
		this->center = center;
	}
	typename list<T_>::iterator is_member(T_ map) {
		for(typename list<T_>::iterator itr = member.begin(); itr!=member.end() ; itr++) {
			if(*itr == map) {
				return itr;
			}
		}
		return member.end();
	}
	void push(T_ map) {
		member.push_back(map);
		map->which_center = index;
		num ++;
	}
	void pop(T_ map) {
		typename list<T_>::iterator pos = is_member(map);
		if(pos != member.end()) {
			(*pos)->which_center = -1;
			member.erase(pos);
			num--;
		}
	}
	float distance_from_map(T_ samp) {
		//����samp����KCenter�ľ��� 
		float dist  = 0;
		dist += pow( (center[0]- (samp->value)[0]), 2);
		dist += pow( (center[1]- (samp->value)[1]), 2);
		dist += pow( (center[2]- (samp->value)[2]), 2);
		dist += pow( (center[3]- (samp->value)[3]), 2);
		return sqrt(dist);
	}
	
	void adjust_center() {
		//���ݳ�Ա���µ����������� 
		center[0] = center[1] = center[2] = center[3] = 0;
		for(typename list<T_>::iterator itr = member.begin(); itr!=member.end() ; itr++) {
			for(int j=0; j<4; j++)
				center[j] += ((*itr)->value)[j];
		}
		for(int j=0; j<4; j++)
			center[j] /= num;
	}
	
	float all_distance() {
		float dist = 0;
		for(typename list<T_>::iterator itr = member.begin(); itr!=member.end() ; itr++) {
			dist += distance_from_map(*itr);
		}
		return dist;
	}
	
private:
	list<T_> member;
	
};

const int N_K = 4; //K���ĸ��� 
KCenter<Map*> kcenters[N_K];


//Ѱ�ҳ�ʼ�ص�����
void find_centers(vector4 centers[],int n,Map maps[],int n_maps) {

	//ƽ��ȡ��ֵ��Ϊ������ (Ԥ�ȼ��������������147��Сֵ0) 
	int span = 147;
	for(int i=0;i<n;i++) {
		for(int j=0;j<4;j++)
			centers[i][j] = i*span/(N_K-1);
	}
	for(int i=0;i<N_K;i++)
			cout<<"cu "<<centers[i][0]<<' '<<centers[i][1]<<' '<<centers[i][2]<<' '<<centers[i][3]<<endl; 
}

void init_centers(vector4 centers[],int n) {
	//���ó�ʼ�ص����� 
	for(int i=0; i<n; i++) {
		kcenters[i].set_kcenter(i,centers[i]);
	}
}

bool divide(Map maps[],int n) {
	//Ϊÿ���������� 
	//����������Ƿ����µ������ı�־ 
	float dist = 0;
	int num_select = 0;	
	bool is_adjust = false;
	
	for(int i=0; i<n; i++) {
		//Ѱ������� 
		dist = kcenters[0].distance_from_map(maps+i);
		num_select = 0;
		for(int j=1; j<N_K; j++) {
			if( dist > kcenters[j].distance_from_map(maps+i) ) {
				dist = kcenters[j].distance_from_map(maps+i);
				num_select = j;		
			}
		}
		if(maps[i].which_center == -1) {
			//��δ����� 
			kcenters[num_select].push(maps+i);
			is_adjust = true;
		} else if (maps[i].which_center != num_select){
			//���ֵ�������
			//��֮ǰ��ȡ�� 
			kcenters[maps[i].which_center].pop(maps+i);
			//ѹ���´� 
			kcenters[num_select].push(maps+i);
			is_adjust = true;
		}
	}
	for(int i=0; i<N_K; i++)
		kcenters[i].adjust_center();
	return is_adjust;
}





/////////////	����Ϊ�����Ч����	//////////////////////
int n_maps = -1; //��Ч������ 
Map *maps;

int main() {

	//get_data(maps,&n_maps);//����ԭʼ���� maps���鱣�棬n_maps��ʾԪ�ظ��� 
	vector4 centers[5];
	find_centers(centers,N_K,maps,n_maps);
	init_centers(centers,N_K);
	
	//���������ݲ��ٱ䶯��Ϊ�����ж� 
	while(divide(maps,n_maps));
	
	for(int i=0;i<N_K;i++) {
		cout<<kcenters[i].num<<' ';
		for(int j=0;j<4;j++) cout<<kcenters[i].center[j]<<' ';
		cout<<endl;
	}
	delete [] maps;
	
	return 0;
}
