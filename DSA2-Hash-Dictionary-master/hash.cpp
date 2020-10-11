#include <vector>
#include <string>
#include "hash.h"
#include <iostream>
#include <fstream>

int primeNumbers[]={577,1217,1549,2017,4049,8009,10007,15331,30047,50021,75029,100003,150001,200003,385027,500009,1000003,2000003,4000011,8000009,16000057};

 /* ＣＯＮＳＴＲＵＣＴＯＲ */
hashTable::hashTable(int size){
    size=hashTable::getPrime(size);
    data.resize(size);
    capacity=size;
};


/* ＰＲＩＶＡＴＥ */
///////////////////////////////////////////////////////////////////////////
int hashTable::hash(const std::string &key){
    int hashVal=0;
    std::string lowerKey=key;

      for(int i=0; i<key.length(); i++){
        lowerKey[i]=tolower(key[i]);
    };
    for (int i =0; i<=lowerKey.length(); i++){
        hashVal= 37 * hashVal+ lowerKey[i];
    };

    hashVal %= capacity;
    if (hashVal <0)
    hashVal += capacity;

    return hashVal;
};

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
// ＮＯＴ　ＲＥＱＵＩＲＥＤ
int hashTable::findPos(const std::string &key){

};

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
    hashTable copy;
    copy.data=data;
    copy.capacity=capacity; 

    try{
        //Clear the hashtable and resize it
        returnSize();
        clear();
        capacity=getPrime(capacity*2);
        std::cout << capacity << std::endl;
        data.resize(capacity); //
        returnSize();
        //Rehash everything, using the new capacity
        for (int i=0; i<copy.capacity; i++){
            data[hash(copy.data[i].key)]=copy.data[i];
        }
        return true;
    }
    catch (const std::exception& error){
        std::cout << "Error with rehashing" << std::endl;
        return false;
    }
};

/*static*/ unsigned int hashTable::getPrime(int size){
    for (int i=0; i<sizeof(primeNumbers); i++){
        if(primeNumbers[i]>size){
            return primeNumbers[i];
        }
    }
};


/* P U B L I C */

int hashTable::insert(const std::string &key, void *pv){
    if (hashTable::contains(key)==true){
        std::cout << "DUPLICATE: " << key << std::endl;
        return 1; // return so no duploicates
    }
    else{
        if(capacity>filled+100){
            int index = hashTable::hash(key);
            //LINEAR PROBING HERE/*
            while(data[index].isOccupied==true){
                //wraparound
                if (index==capacity-1)
                    index=0;

                index++;
               // std::cout << index << " " << key << std::endl;
            }
                //std::cout << index << " " << key << std::endl;
            data[index].key=key;
            data[index].isOccupied=true;
            data[index].pv=pv;
            //std::cout << index << "-->" << data[index].key << std::endl;
            filled++;
            return 0;
        }
        else{  //make bigger and retry
            hashTable::rehash();        
        }
    }           
};

void hashTable::clear(){
    hashItem emptyNode;
    emptyNode.key = {""};
    emptyNode.isOccupied = {false};
    emptyNode.isDeleted = {false};
    emptyNode.pv = {nullptr};

    for(int i=0; i<capacity; i++){
        data[i]=emptyNode;
    }
};


bool hashTable::contains(const std::string &key){
    int index = hashTable::hash(key);
    while (data[index].isOccupied==true){  
        if(index==capacity-1){ //implement wrap around
            index=0;
        }
        if (data[index].key==key){
            return true;
        }
        else{
            index++;
        }
    }
    return false;
};


int hashTable::setPointer(const std::string &key, void *pv){

};


bool hashTable::remove(const std::string &key){

};



