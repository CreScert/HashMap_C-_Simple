// newHashMap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "HashMap.h"

template<class K,class V> HashMap<K,V>::HashMap(){
}
template<class K,class V> HashMap<K,V>::~HashMap(){
	
}

template<class K,class V> K* HashMap<K,V>::keySet(){
	currentMap = headMap;
	
	int i =0;
	for(;currentMap!=NULL;currentMap = currentMap->next)
	{
		i++;
	}
	K *set = (K *)malloc(sizeof(K)*i); 
	
	currentMap = headMap;
	int j =0;
	for(;currentMap!=NULL;currentMap = currentMap->next)
	{
		*(set+j) = currentMap->key;
		j++;
	}

	size = j--;
 return set;
}

template <class K,class V>int HashMap<K,V>::temp = 20;
template <class K,class V>void HashMap<K,V>::init(){
	
	headMap = NULL;
	currentMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>));
	oldMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>)); 
}


template<class K,class V> void HashMap<K,V>::put(K key,V value){
	
	currentMap->key = key;
	currentMap->value = value;
	currentMap->next = NULL;
	
	if(NULL == headMap)
	{	
		headMap = currentMap;	
		headMap->befor =NULL;
	}else{
		currentMap->befor  = oldMap;
		oldMap->next = currentMap;

	}
	
	oldMap = currentMap;
	
	
	currentMap = (MAP<K,V>* )malloc(sizeof(MAP<K,V>));
	
}

template<class K,class V>V HashMap<K,V>::get(K key){
	currentMap = headMap;
	V value = NULL;
	for(;currentMap !=NULL;currentMap = currentMap->next){
		if(currentMap->key == key){
			value = currentMap->value;
		}
	}
	
	return value;
}

template<class K,class V>void HashMap<K,V>::query(){
	currentMap = headMap;
	MAP<K,V>* beforMap =  NULL;
	if(NULL !=currentMap){
		for(;currentMap!=NULL;currentMap=currentMap->next){
			
			beforMap = currentMap;
		//	printf("%d,%d\n",currentMap->key,currentMap->value);
		}
	}
	
	puts(" ");
		for(;beforMap!=NULL;beforMap=beforMap->befor){
		 
		//	printf("%d,%d\n",beforMap->key,beforMap->value);
		}
}
template<class K,class V>  void HashMap<K,V>::Static()
{
	cout<<"this is static"<<endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
 
	/*HashMap<char*> hashMap;
	hashMap.init();
	hashMap.put("aa","22");
	hashMap.put("aa","22");
	hashMap.put("131","22");
	hashMap.query();*/
	HashMap<int,int>::Static();
	HashMap<char*,int> hashMap;
	hashMap.init();
	hashMap.put("a0",30);
	hashMap.put("f5",32);
	hashMap.query();
	
	printf("%d\n",hashMap.temp);
	char** set = hashMap.keySet(); 
	
	for(int i = 0;i<hashMap.size ;i++){
		char* key = *(set+i);
		for(int j =0;j<strlen(key);j++)
		{
			char keych = *(key+j);
		
			int keychsum = keych-'0';
			cout<<"keych:"<<keych<<"keychsum:"<<keychsum<<endl;
			cout<<"hash:"<<hashMap.hash(keychsum)<<endl;
		}
		
		printf("%s,%d\n",key,hashMap.get(key));
		
	}
//	printf("%d\n",hashMap.get(11));
	system("pause");
	return 0;
}

