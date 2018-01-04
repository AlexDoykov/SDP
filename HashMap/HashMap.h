//#include <iostream>

template <typename KEY, typename VALUE>
class HashMap
{
private:
	std::vector<std::vector<std::pair<KEY, VALUE>>> hashMap;
	unsigned (*f)(KEY);
	unsigned hashMapSize;
	unsigned collided;

public:
	HashMap(unsigned (*_f)(KEY), unsigned initialSize){
		hashMap.resize(initialSize);
		f = _f;
		hashMapSize = 0;
		collided = 0;
	}

	void add(KEY key, VALUE value){
		unsigned hashedKey = f(key);
		hashedKey %= hashMap.size();

		for(unsigned i = 0; i < hashMap[hashedKey].size(); i++){
			if(hashMap[hashedKey][i].first == key){
				hashMap[hashedKey][i] = make_pair(key, value);
				return;
			}
		}



		hashMap[hashedKey].push_back(make_pair(key, value));
		if(hashMap[hashedKey].size() > 1){
			collided += 1;
		}
		hashMapSize += 1;
	}

	long take(KEY key){
		unsigned hashedKey = f(key);
		hashedKey %= hashMap.size();

		for(unsigned i = 0; i < hashMap[hashedKey].size(); i++){
			if(hashMap[hashedKey][i].first == key){
				return hashMap[hashedKey][i].second;
			}
		}

		return -1;
	}

	unsigned size(){
		return hashMapSize;
	}

	void prettyPrint(){
		for(unsigned i = 0; i < hashMap.size(); i++){
			for(unsigned j = 0; j < hashMap[i].size(); j++){
				std::cout<<hashMap[i][j].first<<" "<<hashMap[i][j].second<<std::endl;
			}			
		}
	}

	double efficiency(){
		if(hashMap.size() == 0){
			return 0;
		}
		return (hashMapSize - collided) / hashMapSize;
	}

	friend std::ostream& operator << (std::ostream& out, const HashMap& hash){
		for(unsigned i = 0; i < hash.hashMap.size(); i++){
			for(unsigned j = 0; j < hash.hashMap[i].size(); j++){
				out<<hash.hashMap[i][j].first<<" "<<hash.hashMap[i][j].second<<"\n";
			}			
		}
		return out;
	}

	KEY mostCommonWord(){
		VALUE mValue = hashMap[0][0].second;
		std::string mKey = hashMap[0][0].first;
		for(int i = 0; i < hashMapSize; i++){
			for(unsigned j = 0; j < hashMap[i].size(); j++){
				if(hashMap[i][j].second > mValue && ){
					mValue = hashMap[i][j].second;
					mKey = hashMap[i][j].first;
				}
			}	
		}
	}
};