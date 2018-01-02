#include <vector>
#include <algorithm>

using Pair = std::pair<char,unsigned>;

unsigned hashFunc(char symbol){
	return (int) symbol;
}



class Hash
{
private:
	std::vector<std::pair<char,unsigned>> hash;
public:
	class Iterator{
	private:
		unsigned index;
		const std::vector<std::pair<char,unsigned>> *hash;
	public:

		Iterator(const std::vector<std::pair<char,unsigned>> &_hash, unsigned _index){
			index = _index;
			hash = &_hash;
		}

		void operator ++ (){
			int i = index + 1;
			for(; i <= (*hash).size(); i++){
				if((*hash)[i] != std::make_pair(char(), unsigned())){
					index = i;
					return;
				}
			}
		}

		std::pair<char, unsigned> operator * () const{
			return (*hash)[index];
		}

		bool operator != (const Iterator& other) const{
			return index != other.index;
		}

	};

	Iterator begin() const{
		for(int i = 0; i < hash.size(); i++){
			if(hash[i].first != char()){
				return Iterator(hash, i);
			}
		}
	}

	Iterator end() const{
		return Iterator(hash, hash.size());
	}

	Hash(){
		hash.resize(255, std::make_pair(char(), unsigned()));
	}

	/*std::pair<char, unsigned> operator [] (unsigned index){
		//std::cout<<"ddddd";
		return hash[hashFunc(index)];
	}*/
	
	void add(char symbol){
		if(contains(symbol)){
			hash[hashFunc(symbol)] = std::make_pair(symbol,getValue(symbol) + 1);
			return;
		}

		hash[hashFunc(symbol)] = std::make_pair(symbol,1);
	}
	
	bool contains(char symbol) const{
		return (hash[hashFunc(symbol)].first != char());
	}

	unsigned getValue(char symbol) const{
		if(contains(symbol)){
			return hash[hashFunc(symbol)].second;
		}

		return 0;
	}

	size_t size(){
		return hash.size();
	}

	void sort(){
		std::sort(hash.begin(), hash.end(), [](Pair i,Pair j) { return (i.second < j.second);} );
	}
};