#include <iostream>
#include <stack>
//���ķǵݹ����

using namespace std;
typedef struct Node_{
	int val;
	struct Node_ *right;
	struct Node_ *left;
} TreeNode;

 
void preorderTraversal(TreeNode* root) {
	//ǰ��
    stack<TreeNode*> s;
    if (root == NULL)
    	return;
    	
    s.push(root);
    while(!s.empty()) {
        TreeNode* p = s.top();
        s.pop();
        cout<<(p->val)<<' ';
        if (p->right)
            s.push(p->right);
        if (p->left)
        	s.push(p->left);
    }
    return result;
}

void inorderTraversal(TreeNode* root) {
	//���� 
    stack<TreeNode*> s;
    if (root == NULL)
        return ;
    TreeNode* p = root;
    while (!s.empty() || p != NULL) {
        if (p != NULL) {
        	// push ��������ջ
	        s.push(p);
	        p = p->left;
    	} else {
        	// ������Ϊ��ʱ�����ʸýڵ㣬Ȼ�����������
            p = s.top();
            cout<<(p->val)<<' ';
            s.pop();
            p = p->right;
        }
    }  
}




int main() 
{
	
	
	
	
	return 0;	
} 
