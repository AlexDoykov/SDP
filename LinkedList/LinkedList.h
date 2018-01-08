template <typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node(const T& x):data(x), next(nullptr){

	}
};

template <typename T>
class LinkedList
{
private:
	Node<T>* first;

public:
class Iterator{
	private:
		Node<T>* first;

	public:
		Iterator(Node<T>* _first){
			first = _first;
		}

		void operator ++ (){
			first = first->next;
		}

		const T& operator * (){
			return first->data;
		}

		bool operator != (const Iterator& other){
			return first != other.first;
		}

	};

	Iterator begin(){
		return Iterator(first);
	}
	Iterator end(){
		return Iterator(nullptr);
	}

	LinkedList(){
		first = nullptr;
	}

	void pushBack(const T& x){
		if(first == nullptr){
			first = new Node<T>(x);
		}
		Node<T>* curr = first;
		while(curr->next != nullptr){
			curr = curr->next;
		}

		curr->next = new Node<T>(x);
	}
};