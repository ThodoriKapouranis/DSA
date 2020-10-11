#include <vector>
#include <string>
#include "hash.h"
#include <iostream>
#include <fstream>

int primeNumbers[]={1217,1549,2017,4049,8009,10007,15331,30047,50021,75029,100003,150001,200003,385027,500009,1000003,2000003,4000011,8000009,16000057};

 /* ＣＯＮＳＴＲＵＣＴＯＲ */
hashTable::hashTable(int size){
    size=hashTable::getPrime(size);
    data.resize(size);
    filled=0;
    capacity=size;
};

/* P U B L I C */

int hashTable::insert(const std::string &key, void *pv){
    if (hashTable::contains(key)==true) return 1; 

    else{
        if( capacity > filled ){
            int index = hashTable::hash(key);

            // Iterate through occupied files (and wraparound) until vacant spot
            while(data[index].isOccupied==true && data[index].isDeleted==false){
                if(index>=capacity-1) index=0;
                else index++;
            }

            data[index].key=key;
            data[index].isOccupied=true;
            data[index].isDeleted=false;
            data[index].pv=pv;

            filled++;
            return 0;
        }

        else{
            std::cout << "I AM GOING TO REHASH BECAUSE FILLED | CAPACITY: " << filled << " | " << capacity << std::endl;
            hashTable::rehash();
            return 2;
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
if (findPos(key)==-1)
    return false;
else
    return true;
};


int hashTable::setPointer(const std::string &key, void *pv){
    int index = findPos(key);
    if (index==-1) return 1;
    data[index].pv=pv;
    return 0;
};

//default parameter seems to break... fix later and delete this line plz
void *hashTable::getPointer(const std::string &key, bool *b){
    int index = findPos(key);
    *b=false; 
    if (index == -1) return nullptr;
    *b = true;
    return data[index].pv;
};

bool hashTable::remove(const std::string &key){
    /* OOPS! DOING LAZY DELETION INSTEAD NOW
    hashItem emptyNode;
    emptyNode.key = {""};
    emptyNode.isOccupied = {false};
    emptyNode.isDeleted = {false};
    emptyNode.pv = {nullptr};
    */

    int index = findPos(key);
    if (index==-1) return false;
    
    data[index].isDeleted=true;
    filled--;
    return true;
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
    int index = hashTable::hash(key);

        while (data[index].isOccupied==true){  

            if (data[index].key==key && data[index].isDeleted==false){
                return index;
            }

            else if(index>=capacity-1){ //implement wrap around
                index=0;
            }

            else{
                index++;
            }
        }
        return -1;
};

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
    hashTable copy;
    copy.data=data;
    copy.capacity=capacity; 

    try{
        //Clear the hashtable and resize it
        clear();
        capacity=getPrime(capacity*2);
        std::cout << capacity << std::endl;
        data.resize(capacity); //
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

unsigned int hashTable::getPrime(int size){
    for (int i=0; i<sizeof(primeNumbers); i++){
        if(primeNumbers[i]>size){
            return primeNumbers[i];
        }
    }
    return 0;
};


