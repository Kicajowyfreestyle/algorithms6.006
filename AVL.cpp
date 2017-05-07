#include <iostream>
#include <algorithm> 
using namespace std;

class AVL;

class AVL{
	int value;
	AVL* left;
	AVL* right;
	int height;

	public:

	AVL(int val){
		value = val;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
	void inorderTraversal(){
		if(left != nullptr)
			left->inorderTraversal();
		cout<<value<<" ";
		if(right != nullptr)
			right->inorderTraversal();
	}

	

	AVL* insert(int val){
		cout<<"INSERT"<<endl;
		if(val > this->value){
            if(this->right != nullptr)
                this->right->insert(val);
            else
                this->right = new AVL(val);
        }
        else if(val < this->value){
            if(this->left != nullptr)
                this->left->insert(val);
            else
                this->left = new AVL(val);
        }

		updateHeight();

		if(balance() > 1){
			if(val > left->value)
				left->leftRotate();
			rightRotate();
		}
		else if(balance() < -1){
			if(val < right->value)
				right->rightRotate();
			leftRotate();
		}
	}

	private:

	void leftRotate(){
		cout<<"LEFT"<<endl;
		AVL* temp = this;
		temp->right = this->right->left;

		this->value = this->right->value;
		this->left = temp;
		this->right = this->right->right;

		this->updateHeight();
		this->left->updateHeight();
	}


	void rightRotate(){
		cout<<"RIGHT"<<endl;
		AVL* newThis = this->left;
		AVL* toMove = this->left->right;

		this->left = toMove;
		newThis->right = this;

		cout<<"CO LECI"<<endl;
		*this = *newThis;

		cout<<"KONIEC RIGHT"<<endl;
		this->updateHeight();
		this->right->updateHeight();
	}


	int balance(){
		if(left != nullptr && right != nullptr)
			return left->height - right->height;
		else if(left != nullptr && right == nullptr)
			return left->height+1;
		else if(left == nullptr && right != nullptr)
			return -right->height-1;
		else
			return 0;
	}

	void updateHeight(){
		int leftHeight = (left != nullptr) ? left->height : -1;
		int rightHeight = (right != nullptr) ? right->height : -1;
		height = max(leftHeight, rightHeight) + 1;
	}
};
int main(){
	AVL* tree = new AVL(6);
	tree->insert(5);
	tree->insert(3);
	//tree->insert(1);
	tree->inorderTraversal();
}