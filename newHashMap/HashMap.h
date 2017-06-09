#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

#define TEMPLATE template<class K,class V> ;

template<class K,class V>struct MAP 
{
	K key;
	V value;
	MAP *next;
	MAP *befor;
};
template<class K,class V> class  HashMap{

	public:
		HashMap();

		void init();
		void put(K key,V value);
		V get(K key);
		K* keySet();
		V remove(K);
		V getDefValue(V);

		bool containsKey(K key);
		bool containsValue(V value);
		bool isEmpty();
		 

		void putAll(HashMap<K,V>);

		int size();
		void clear();
		static int temp;
		int mSize;
		int hash(int h){
		 h ^= (h >> 20) ^ (h >> 12);
        return h ^ (h >> 7) ^ (h >> 4);
		}
		
		void query();
		~HashMap();
		
		
	
		
		 MAP<K,V> *headMap,*currentMap,*oldMap;

		
 
	void Free();
};
