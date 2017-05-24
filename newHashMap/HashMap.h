#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;
template<class K,class V>struct MAP 
{
	K key;
	V value;
	MAP *next;
	MAP *befor;
};
template<class K,class V> class  HashMap{

	public:
		 static void Static();
		HashMap();
		void init();
		void put(K key,V value);
		V get(K key);
		K* keySet();
		
		static int temp;
		int size;
		int hash(int h){
		 h ^= (h >> 20) ^ (h >> 12);
        return h ^ (h >> 7) ^ (h >> 4);
		}
		
		void query();
		~HashMap();
		
		
	
		
		 MAP<K,V> *headMap,*currentMap,*oldMap;

		
};
