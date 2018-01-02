
struct Node{
	std::pair<char, unsigned> data;
	Node *left, *right;
	Node(std::pair<char, unsigned> _data):data(_data), left(nullptr), right(nullptr){

	}
};

class Tree
{
private:
	Node* root;
public:
	BinaryOrderedTree():root(nullptr){

	}

	void insert(char data){
		if(root == nullptr){
			root = new Node(make_pair(data, 1));
		}

		if(root->data.first == data){
			root->data = make_pair(data, root->data.second + 1);
		}

		if(root->data)
	}

};