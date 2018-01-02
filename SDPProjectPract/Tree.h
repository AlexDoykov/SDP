
struct Node{
	std::pair<char, unsigned> data;
	Node *left, *right;
	Node(std::pair<char, unsigned> _data):data(_data), left(nullptr), 
														right(nullptr){

	}

	Node(std::pair<char, unsigned> _data, Node *_left, Node *_right):
							data(_data), left(_left), right(_right){

	}
};

class Tree
{
private:
	Node* root;

	Node* copy(Node *subRoot){
		if(subRoot == nullptr){
			return nullptr;
		}
		return new Node(subRoot->data, copy(subRoot->left), copy(subRoot->right));
	}

	void printSpaces(unsigned spaces) {
		for(int i = 0; i < spaces; i++){
			std::cout<<"     ";
		}
	}

	unsigned count(Node *root){
		if(root == nullptr){
			return 0;
		}
		return 1 + count(root->left) + count(root->right);
	}

	void print(Node *root, unsigned spaces){
		if(root == nullptr){
			return;
		}

		print(root->right, spaces + 1);
		printSpaces(spaces);
		std::cout<<root->data.first<<" "<<root->data.second<<std::endl;
		print(root->left, spaces + 1);

	}

public:
	Tree():root(nullptr){

	}

	Tree(std::pair<char, unsigned> data){
		root = new Node(data);
	}

	Tree(std::pair<char, unsigned> data, const Tree& leftTree,
											const Tree& rightTree){
		root = new Node(data, copy(leftTree.root), copy(rightTree.root));
	}

	unsigned rootData(){
		return root->data.second;
	}

	unsigned count(){
		return count(root);
	}

	void print(){
		print(root, 0);
	}
};