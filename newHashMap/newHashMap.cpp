// newHashMap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "HashMap.h"

 

/*
*	构造方法
*/
template<class K,class V> HashMap<K,V>::HashMap()
{
	mSize = 0;
	init();
}
/*
*	析构方法
*/
template<class K,class V> HashMap<K,V>::~HashMap()
{
	if(headMap!=NULL)
	{
		free(headMap);
		headMap = NULL;
	}
}
template<class K,class V>void HashMap<K,V>::Free()
{
	currentMap = headMap;

	//将指针移到最后
	for(;currentMap!=NULL&&currentMap->next!=NULL;currentMap= currentMap->next);
	
	for(;currentMap!=NULL &&currentMap->befor!=NULL;currentMap = currentMap->befor){
		 
		currentMap->befor->next = NULL;
		free(currentMap->befor->next);
		currentMap->befor->next=NULL;
	}

	if(currentMap == headMap){
	 
		free(headMap);
		headMap = NULL;
		currentMap=NULL;
	}else{
		if(headMap!=NULL){
			free(headMap);
			headMap =NULL;
			if(currentMap !=NULL)
			currentMap =NULL;
		}
	}

}
/*
*
*清空集合
*/
template<class K,class V>void HashMap<K,V>::clear()
{
	if(mSize!=0 && size())
	{
		Free();
		init();
		mSize = 0;
	}
}

/*
*集合中是否包含键
*/
template<class K,class V> bool HashMap<K,V>::containsKey(K key)
{
	bool isExist = false;

	K *set =  keySet();
	
	for(int i = 0; i <mSize;i++)
	{
		

		K getKey = *(set + i);
		
		 
		if(getKey == key )
		{
			isExist = true;
			break;
		}
	}

	return isExist;
}
 
/*
*集合中是否包含值
*/
template<class K,class V> bool HashMap<K,V>::containsValue(V value)
{
	bool isExist = false;

	K *set =  keySet();

	for(int i = 0; i <mSize;i++)
	{

		K getKey = *(set + i);
		V getValue = get(getKey);
		 
		
		if(getValue == value )
		{
			isExist = true;
			break;
		}
	}
	return isExist;
}

/**
返回集合的大小
*/
template<class K,class V> int HashMap<K,V>::size()
{
	if(mSize == 0)
	{
		keySet();
	}
	return mSize;
}
/*
*	获取键，保存到一个
*/
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

 
	return set;
}

/*
* 初始化链表
*/
template <class K,class V>void HashMap<K,V>::init(){

	headMap = NULL;
	currentMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>));
	oldMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>)); 
}


/*
*	存值，有重复的键 替换重复的键所对应的值
*/
template<class K,class V> void HashMap<K,V>::put(K key,V value){

	// 先查找是否有重复的键
	for(currentMap = headMap;currentMap!=NULL;currentMap = currentMap->next)
	{
		//找到后 直接赋值
		
		if(currentMap->key == key)
		{
			//cout<<key<<endl;
			currentMap->value = value;
			return;
		}
	}
	//对之前的重复键查找后，currentMap会指向链表最后的NULL，需要重新初始化
	//但是不能对链表头 置为NULL
	if(currentMap == NULL)
	{
		currentMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>));

	}
	//保存键值对
	currentMap->key = key;
	currentMap->value = value;
	currentMap->next = NULL;

	//第一次进入，没有链表头
	if(NULL == headMap)
	{	
		//将现在的链表保存为头
		headMap = currentMap;	
		headMap->befor =NULL;
	}else{
		//设置下一个以及上一个链表
		currentMap->befor  = oldMap;
		oldMap->next = currentMap;

	}

	//对链表赋值
	oldMap = currentMap;

	if(mSize == 0)
	{
		mSize = 0;
	}
	mSize++;
	currentMap = (MAP<K,V>* )malloc(sizeof(MAP<K,V>));

}
/*
*
*判断集合是否是空的
*/ 
template <class K,class V>bool HashMap<K,V>::isEmpty()
 {
 
	if(mSize == 0)
	{
		return true;
	}
	return false;
 }
 
/*
*
*   获取键所对应的值
*/
template<class K,class V>V HashMap<K,V>::get(K key){
	//链表指向头部
	currentMap = headMap;
		V value = NULL;
	value = getDefValue(value);
	//遍历链表
	for(;currentMap !=NULL;currentMap = currentMap->next){
		//找到键，返回值
		if(currentMap->key == key){
			value = currentMap->value;
			return value;
		}
	}

	return value;
}

/*
*	查询键值对
*/
template<class K,class V>void HashMap<K,V>::query(){
	currentMap = headMap;
	MAP<K,V>* beforMap =  NULL;
	if(NULL !=currentMap){
		for(;currentMap!=NULL;currentMap=currentMap->next){

			beforMap = currentMap;
			printf("%s,%d\n",currentMap->key,currentMap->value);
		}
	}

	puts(" ");
	for(;beforMap!=NULL;beforMap=beforMap->befor){

		//	printf("%d,%d\n",beforMap->key,beforMap->value);
	}
}

template <class K,class V> V HashMap<K,V>::getDefValue(V value)
{
	V defValue ;
	if(typeid(V) == typeid(int))defValue = (V)-1;
	else if(typeid(V) == typeid(char))defValue =(V)-1;
	else if(typeid(V) == typeid(short))defValue = (V)-1;
	else if(typeid(V) == typeid(bool))defValue = false;
	else if(typeid(V) == typeid(float))defValue = (V)-1;
	else if(typeid(V) == typeid(double))defValue = (V)-1; 
	else if(typeid(V) == typeid(char *))defValue =  NULL;
	else defValue = NULL;

	return defValue;
}


/*
*
*	删除集合中的一个键键值对
*   返回值，被删除的键 所对应的值 
*/
template <class K,class V> V HashMap<K,V>::remove(K key)
{
	V value = NULL;
	value = getDefValue(value);

	for(currentMap = headMap;currentMap!=NULL;currentMap = currentMap->next)
	{
		if(currentMap->key == key )
		{
			//在链表头
			if(currentMap->befor==NULL)
			{
				//链表只有一个值
				if(currentMap->next ==NULL)
				{
					headMap->next = NULL;
					headMap->befor = NULL;

					headMap = NULL;
				}else{//在链表头
					value = headMap->value;

					headMap->befor = NULL;
					headMap = headMap->next;

				}
			}else if(currentMap->next == NULL)//链表尾部
			{
				value = currentMap->value;

				currentMap->befor->next =NULL;;
				currentMap = currentMap->befor;

			}else{
				//在链表的中间

				value = currentMap->value;

				currentMap->befor->next = currentMap->next;
				currentMap->next->befor = currentMap->befor;

				currentMap = currentMap->befor;
			}
		}
	}


	return value;
}

template<class K,class V>void HashMap<K,V>::putAll(HashMap<K,V> hash)
{
	 
	K * set = hash.keySet();
	
	for (int i = 0; i < hash.mSize; i++)
	{
		K key = *(set + i);

		V value = hash.get(key);
		this->put(key,value);
	}
}	

int _tmain(int argc, _TCHAR* argv[])
{

	HashMap<char*,int> hash;

	char * temp = (char*)malloc(50);
	*(temp+0) = 'a';
	*(temp+1) = 'a';
	*(temp+2) = 'b';
	*(temp+3) = 'c';
	*(temp+4) = 0;
	hash.put(temp,22);
	hash.put("afffaadds",66);
	hash.put("aaaafg",55);
	hash.put("aasddd",88);
	
	 
	 hash.clear();
	 hash.init();
	 hash.put("aa",55);

 hash.query();
	system("pause");
	return 0;
}

