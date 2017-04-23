#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const short G_N = 3;		//������������ÿ��Ԫ�ظ���


class Node{
public:

	int x,y;						//0(����ֵ����λ��) 
	int chest[G_N][G_N];			//��ʱ�ֲ�״̬ 
	int h_value,g_value,f_value;					//�ɼۺ���ֵ 
	Node *prior;					//���ڵ�ָ��
	vector<Node*> childs;			//����ָ�� 

	Node *next_open;		//���ڷ���open����
	Node *prior_open;		//���ڷ���open����

	Node() {
		x=y=0;
		h_value = g_value = f_value = 0;
		prior = NULL;
		next_open = prior_open =NULL;
	}
	void inherit(Node* ff) {
		//������x,y,chest 
		if(!ff) return ;
		x = ff->x; y = ff->y;
		for (int i = 0; i < G_N; i++) {
			for (int j = 0; j < G_N; j++) {
				chest[i][j] = ff->chest[i][j];
			}
		}
		prior = ff;
	}

	void hn2(Node *target) {
		//�������� 1
		//����Ŀ��λ�õ�����Ϊh_value
	    int num = 0;  
	    for(int i = 0 ; i < G_N ; i++) {  
	        for(int j = 0 ; j < G_N ; j++) {  
	            if(this->chest[i][j] != target->chest[i][j])  
	                num++;  
	        }  
	    }  
	    h_value = num;  
	}

	void hn(Node *target) {
		//�������� 2
		class Distance {
		public:
			int operator() (int x,int y,int value,Node *target) {
				//����(x,y)��Ӧ��ֵvalue��target�е�λ����(x,y)�ľ���
				for (int i = 0; i < G_N; i++) 
					for (int j = 0; j < G_N; j++) 
						if (value == target->chest[i][j]) 
							return abs(x - i) + abs(y - j);
				return 1000;
			}
		} distance;
		//���е����Ŀ��λ�ú���Ϊh_value
		int num = 0;
		for (int i = 0; i < G_N; i++) {
			for (int j = 0; j < G_N; j++) {
				num += distance(i, j, chest[i][j], target);
			}
		}
		h_value = num;
	}

	//n��Ŀ������·��������ֵ 
	void gn() {
		if(this->prior == NULL)  
        	this->g_value = 0;  
    	else  
        	this->g_value = this->prior->g_value + 1;  
	}
	//fn���ۺ���
	void fn() {
		f_value = g_value + h_value;
	} 
	
	void show() {
		for (int i = 0; i < G_N; i++) {
			for (int j = 0; j < G_N; j++) {
				cout << this->chest[i][j] << ' ';
			}
		cout << endl;
		}
	}
};

bool is_same_node(Node *a, Node *b) {
	if (a->x != b->x || a->y != b->y) return false;
	for (int i = 0; i < G_N; i++) {
		for (int j = 0; j < G_N; j++) {
			if (a->chest[i][j] != b->chest[i][j]) {
				return false;
			}
		}
	}
	return true;
}


class OpenList {
//��class���ڷ�����open����
public:
	Node*  head_;
	void add_one(Node*one) {
		//list�м���one
		if(one == NULL) return ;
		one->next_open = NULL;
		Node* tmp = head_;
		if(head_ == NULL) {
			head_ = one;
			one->prior_open = NULL;
		} else {
			while(tmp->next_open!=NULL) tmp=tmp->next_open;
			tmp->next_open = one;
			one->prior_open = tmp;
			one->next_open = NULL;
		}
	}
	void delete_one(Node *one) {
		//list��ɾ��one
		if(one->prior_open==NULL) {
			head_ = one->next_open;
			if(one->next_open)			//���˼����bug,�����˴�֮ǰ©д�������������ʧ��
				one->next_open->prior_open = NULL;
		} else {
			one->prior_open->next_open = one->next_open;
			if(one->next_open != NULL) one->next_open->prior_open = one->prior_open;
		}
		one->next_open = one->prior_open = NULL;

	}
	Node* front() {
		//ȡ�� Openlist �� f_value����Ԫ�ص�ַ 
		Node *tmp = head_;
		Node *min=head_;
		while(tmp!=NULL) {
			if(tmp->f_value < min->f_value) {
				min = tmp;
			}
			tmp = tmp->next_open;
		}
		return min;
	}
	bool has_child(Node *child,Node *&who) {
		//�ж�OPEN�����Ƿ��н��child
		//����whoָ������open�е�λ��
		Node *tmp = head_;
		while(tmp) {
			if(is_same_node(tmp, child)) {
				who = tmp;
				return true;	
			}
			tmp = tmp->next_open;
		}
		who = NULL;
		return false;
	}
	bool empty() {
		return (head_ == NULL);
	}
};


Node target;
//priority_queue<Node*,vector<Node*>,cmp> OPEN;		//open������ȴ���չ�Ľ��
vector<Node*> CLOSED;								//closed��������ʹ��Ľڵ�
OpenList open_list;									//���ڷ���open���

bool is_on_closed(Node *child,Node * &who,int &who_pos) {
	
	//�ж�child�Ƿ���CLOSED�г��ֹ�,����whoָ������closed�е�λ��
		for(who_pos=0; who_pos < CLOSED.size(); who_pos++) {
			
			if(is_same_node(child,CLOSED[who_pos])) {
				who = (CLOSED[who_pos]);
				return true;
			}
		}
		who_pos = -1;
		who = NULL;
		return false;
}

bool is_target(Node*target,Node* one) {
	//�ж��Ƿ񵽴�Ŀ��״̬
	return is_same_node(target, one);
}

bool is_same_as_parent(Node *one) {
	//�ж��Ƿ���丸����ͬ
	Node * tmp= one->prior;
	while (tmp != NULL) {
		if (is_same_node(one, tmp)) {
			return true;
		}
		tmp = tmp->prior;
	}
	return false;
}
void calculate_g_to_update_open(Node *source,Node* child,Node *who) {
	//source Ϊchild�ĸ��׽��
	///***�����ֵ�������޸�
	//��֪�丸��˭,����Ϊ����չ������������ 
	child->gn();
	child->fn();
	if(child->g_value < who->g_value) {
		
		who->g_value = child->g_value;
		who->f_value = child->f_value;
		who->prior = child->prior;
	}
	source->childs.push_back(who);
	delete child;
}

void calculate_g_to_update_closed(Node *source,Node* child,Node *who,int who_pos_on_closed) {
	//source Ϊchild�ĸ��׽��
	///***�����ֵ�������޸ģ�����չ���迼������ 
	child->gn();
	child->fn();
	source->childs.push_back(who);

	if(child->g_value < who->g_value) {
		who->g_value = child->g_value;
		who->f_value = child->f_value;
		who->prior = child->prior;
		who->childs.clear();
		CLOSED.erase(CLOSED.begin() + who_pos_on_closed);
		open_list.add_one(who);
		delete child;
	}
}

void check_child(Node *source,Node *child) {
	//source --child�ĸ��ڵ�
	//��麢������������ͼ�е�λ���Լ�״̬������Ӧ����
	if (is_same_as_parent(child)) return;
	child->hn(&target);
	Node *who;
	int who_pos_on_closed;
	if(open_list.has_child(child,who)) {
		//cout<<"on open"<<endl;
		calculate_g_to_update_open(source,child,who);
	} else if(is_on_closed(child,who, who_pos_on_closed)) {
		//cout<<"on closed"<<endl;
		calculate_g_to_update_closed(source,child,who, who_pos_on_closed);
	} else {
		//cout<<"add open"<<endl;
		source->childs.push_back(child);
		open_list.add_one(child);
	}
}


void creat_child(Node *source) {
	//����source���ĺ�̿��ܽ��(����һ�����״̬)
	
	class Swap {
		public: 
		 void operator()(int &a, int &b) {
			int t = a; 
			a = b;
			b = t;
		}
	}swap;

	//���󽻻�
	if(source->y>0) {
		//cout<<"��"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x][child->y - 1]);
		child->x = source->x;
		child->y = source->y-1;
		check_child(source,child);
	}
	//���ҽ���
	if(source->y<G_N-1) {
		//cout<<"��"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x][child->y + 1]);
		child->x = source->x;
		child->y = source->y + 1;
		check_child(source, child);
	}
	//���Ͻ���
	if(source->x>0) {
		//cout<<"��"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x - 1][child->y]);
		child->x = source->x - 1;
		child->y = source->y;
		check_child(source, child);	
	}
	//���½���
	if(source->x<G_N-1) {
		//cout<<"��"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x + 1][child->y]);
		child->x = source->x + 1;
		child->y = source->y;
		check_child(source, child);

	}
}



void show_path(Node *one) {
	Node *tmp = one;
	while (tmp) {
		cout << "��" << endl;
		tmp->show();
		tmp = tmp->prior;
	}
}

void search_Astar(Node *target, Node *init_node)
{
	
	
	//ѹ���ʼ״̬
	open_list.add_one(init_node);
	// ��������������ͼ
	Node *tmp = NULL;
	while (!open_list.empty()) {
		//ȡ���������ŵ�Ԫ�أ�����open���г���
		tmp = open_list.front();
		open_list.delete_one(tmp);

		//���ý���Ƿ�ΪĿ��ڵ�
		if(is_target(target,tmp)) {
			cout<<"Yes"<<endl;
			break;
		}
			
		//�к�״̬ 
		if(true) {
			//�������״̬����̽�㣩 
			creat_child(tmp);
		} 
		//�õ�����ϣ�ѹ��closed��
		CLOSED.push_back(tmp);

	}
	show_path(tmp);
	//�������������ս����tmp
}

void init_node_status(Node * a, int b[])
{
	for (int i = 0; i < G_N; i++) {
		for (int j = 0; j < G_N; j++) {
			a->chest[i][j] = b[i*G_N + j];
			if (b[i*G_N + j] == 0) {
				a->x = i;
				a->y = j;
			}
		}
	}
	a->hn(&target);
	a->gn();
	a->fn();
}

int main()
{
	Node init_node;
	init_node.next_open = NULL;
	int a[] = { 2,0,3,1,8,4,7,6,5 };
	int b[] = { 1,2,3,8,0,4,7,6,5 };

	init_node_status(&target, b);
	init_node_status(&init_node, a);

	target.show();
	search_Astar(&target, &init_node);
	cout << "Waitint for input" << endl;
	cin.get();
	return 0;
}
