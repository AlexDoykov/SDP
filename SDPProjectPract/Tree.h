
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
	Tree():root(nullptr){

	}

	Tree(std::pair<char, unsigned> data){
		root = new Node(data);
	}

};