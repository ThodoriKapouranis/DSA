#include <vector>
#include <string>
#include "heap.h"
#include <iostream>
#include <fstream>

//Instead of creating a new temp node, i just allocate to data[0]

/*
Notes for myself:
static_cast<... *> to set the correct size of what is initially a void* ptr

*/


/*ＣＯＮＳＴＲＵＣＴＯＲ*/
heap::heap(int size):mapping(size*2){
    capacity=size;
    data.resize(size+1);
    filled=0;
};

/*ＰＵＢＬＩＣ*/

int heap::insert(const std::string &id, int key, void *pv){
    
    if(capacity==filled)
        return 1;
    
    if(mapping.contains(id))
        return 2;

    node toInsert;
    toInsert.id=id;
    toInsert.key=key;
    toInsert.pData=pv;

    data[filled+1]=toInsert; //make hole, later check place with percolateUp();
    mapping.insert(id, &data[filled]); //put string and data in hashtable
    filled++;

    percolateUp(filled);   //check place
    /*
    std::cout << std::endl << "filled: " <<filled << std::endl;
    
    for(int i=1; i<=filled; i++){
        std::cout << i << ": " <<data[i].id << " " <<  data[i].key << std::endl;
    }
    */

    return 0;
};

int heap::setKey(const std::string &id, int key){
    bool b;
    node* ptr;

    ptr = static_cast<node *> (mapping.getPointer(id, &b)); //conversion
    if (b == false) return 1;

    //data[0] as temp storage. change original key to new key, and percolate according to if it is expected to go up or down the heap.

    int posCur=getPos(ptr);
    data[0]=data[posCur];
    data[posCur].key=key;
    //std::cout << "CHANGING KEY OF: " << data[0].id << " " << data[0].key << std::endl;
    if(data[0].key > key) percolateUp(posCur);
    if(data[0].key < key) percolateDown(posCur);
    /*
    for(int i=1; i<=filled; i++){
        std::cout << i << ": " <<data[i].id << " " <<  data[i].key << std::endl;
    }
    */
    return 0;
};

int heap::deleteMin(std::string *pId , int *pKey, void *ppData){
    if (filled==0)
        return 1;
    

    data[0]=data[1]; // instead of making a temp node, just use data[0]

    if( pId != nullptr) *pId = data[0].id;
    if (pKey != nullptr) *pKey = data[0].key;
    if (ppData != nullptr) *(static_cast<void **> (ppData)) = data[0].pData;

    data[1]=data[filled--];
    mapping.remove(data[0].id);
    percolateDown(1); //constant cause index=1 in heap should always be lowest
    
    /*
    for(int i=1; i<=filled; i++){
        std::cout << i << ": " <<data[i].id << " " <<  data[i].key << std::endl;
    }
    */
    return 0;
};

int heap::remove(const std::string &id, int *pKey, void *ppData ){
   // DNE check
    bool b;
    node* ptr;
    ptr = static_cast<node *> (mapping.getPointer(id, &b)); 
    if (b == false) return 1;

    int posCur=getPos(ptr);
    data[0]=data[posCur];

    if (pKey != nullptr) *pKey = data[0].key;
    if (ppData != nullptr) *(static_cast<void **> (ppData)) = data[0].pData;
    int lowestKey = data[1].key;   

    setKey(id,lowestKey-1); //this covers the return 1 value
    percolateDown(1);
    //deleteMin() without;
    data[0]=data[1];
    data[1]=data[filled--];
    mapping.remove(data[0].id);
    percolateDown(1); //constant cause index=1 in heap should always be lowest

    /*
    for(int i=1; i<=filled; i++){
        std::cout << i << ": " <<data[i].id << " " <<  data[i].key << std::endl;
    }
    */
    return 0;     
};

/*ＰＲＩＶＡＴＥ*/

void heap::percolateUp(int posCur){
    int hole=posCur;
    data[0]=data[posCur];

    //we basically want to keep checking the parent node (divide by 2).
    //Whenever our insert key is lower than parent node, we swap places.
    //Also, making sure we update the pointers whenever we move stuff around.

    for (; hole>1 && (data[0].key < data[hole/2].key); hole/=2){
        data[hole] = data[hole/2]; //bring parent node down
        mapping.setPointer(data[hole].id, &data[hole]); 
    };

    //now replace location where it should be with our toInsert node.
    data[hole]=data[0];
    mapping.setPointer(data[hole].id, &data[hole]); 
};


void heap::percolateDown(int posCur){
    int holeIndex=posCur; //start. for deleteMin, should be 1
    int childIndex;
    data[0]=data[posCur]; //use this empty node for storage

    for ( ; posCur*2 <= filled; posCur=childIndex){
        childIndex=posCur*2;

        //if right child exists, check if its smaller than left
        if (childIndex+1 <= filled){     
            if (data[childIndex+1].key<data[childIndex].key) 
                childIndex++;
        };

        if(data[childIndex].key > data[0].key) 
            break;

        data[posCur]=data[childIndex];
        mapping.setPointer(data[posCur].id, &data[posCur]); 
    };

    data[posCur]=data[0];
    mapping.setPointer(data[posCur].id, &data[posCur]); 
};

int heap::getPos(node *pn){
    //std::cout << "GETTING POS" << std::endl;
    int pos = pn - &data[0];
    return pos; //find relative position
};
