// newHashMap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#include "HashMap.h"

 

/*
*	���췽��
*/
template<class K,class V> HashMap<K,V>::HashMap()
{
	mSize = 0;
	init();
}
/*
*	��������
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

	//��ָ���Ƶ����
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
*��ռ���
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
*�������Ƿ������
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
*�������Ƿ����ֵ
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
���ؼ��ϵĴ�С
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
*	��ȡ�������浽һ��
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
* ��ʼ������
*/
template <class K,class V>void HashMap<K,V>::init(){

	headMap = NULL;
	currentMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>));
	oldMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>)); 
}


/*
*	��ֵ�����ظ��ļ� �滻�ظ��ļ�����Ӧ��ֵ
*/
template<class K,class V> void HashMap<K,V>::put(K key,V value){

	// �Ȳ����Ƿ����ظ��ļ�
	for(currentMap = headMap;currentMap!=NULL;currentMap = currentMap->next)
	{
		//�ҵ��� ֱ�Ӹ�ֵ
		
		if(currentMap->key == key)
		{
			//cout<<key<<endl;
			currentMap->value = value;
			return;
		}
	}
	//��֮ǰ���ظ������Һ�currentMap��ָ����������NULL����Ҫ���³�ʼ��
	//���ǲ��ܶ�����ͷ ��ΪNULL
	if(currentMap == NULL)
	{
		currentMap = (MAP<K,V>*)malloc(sizeof(MAP<K,V>));

	}
	//�����ֵ��
	currentMap->key = key;
	currentMap->value = value;
	currentMap->next = NULL;

	//��һ�ν��룬û������ͷ
	if(NULL == headMap)
	{	
		//�����ڵ�������Ϊͷ
		headMap = currentMap;	
		headMap->befor =NULL;
	}else{
		//������һ���Լ���һ������
		currentMap->befor  = oldMap;
		oldMap->next = currentMap;

	}

	//������ֵ
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
*�жϼ����Ƿ��ǿյ�
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
*   ��ȡ������Ӧ��ֵ
*/
template<class K,class V>V HashMap<K,V>::get(K key){
	//����ָ��ͷ��
	currentMap = headMap;
		V value = NULL;
	value = getDefValue(value);
	//��������
	for(;currentMap !=NULL;currentMap = currentMap->next){
		//�ҵ���������ֵ
		if(currentMap->key == key){
			value = currentMap->value;
			return value;
		}
	}

	return value;
}

/*
*	��ѯ��ֵ��
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
*	ɾ�������е�һ������ֵ��
*   ����ֵ����ɾ���ļ� ����Ӧ��ֵ 
*/
template <class K,class V> V HashMap<K,V>::remove(K key)
{
	V value = NULL;
	value = getDefValue(value);

	for(currentMap = headMap;currentMap!=NULL;currentMap = currentMap->next)
	{
		if(currentMap->key == key )
		{
			//������ͷ
			if(currentMap->befor==NULL)
			{
				//����ֻ��һ��ֵ
				if(currentMap->next ==NULL)
				{
					headMap->next = NULL;
					headMap->befor = NULL;

					headMap = NULL;
				}else{//������ͷ
					value = headMap->value;

					headMap->befor = NULL;
					headMap = headMap->next;

				}
			}else if(currentMap->next == NULL)//����β��
			{
				value = currentMap->value;

				currentMap->befor->next =NULL;;
				currentMap = currentMap->befor;

			}else{
				//��������м�

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

