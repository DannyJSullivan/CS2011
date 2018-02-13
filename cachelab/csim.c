//djsullivan, nchkhaidze - Danny Sullivan and Nugzar Chkhaidze - Cachelab
//import external files and libraries
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <strings.h>
#include <math.h>

//hold 64 bit memory
typedef unsigned long long int memHold;

//one address line
typedef struct addr{
    int v;//valid
    memHold t;//tag
    char *address;//address line
    int counter;//hit counter
} addr;//end addr

//group of address lines
typedef struct addrs{
    addr *addresses;//group of address lines
} addrs;//end addrs

//group of addresses
typedef struct cache{
    addrs *cache;//group of addresses
} cache;//end cache

//cache parameters
typedef struct params{
    int s,b,E,S,B;
    int hits,misses,evictions;
} params;//end params

//value only when verbosity is checked
int v;

//find power by shifting bits
long long powBit(int pow) {
    long long ans=1;
    ans=ans<<pow;//shift bits to do power function
    return ans;
}//end powBit

//make a cache
cache makeCache (long long s,int l,long long bs){
    cache newCache;
    addrs myAddresses;
    addr myAddress;

    //allocate space for cache
    newCache.cache = (addrs *) malloc(sizeof(addrs)*s);
    for (int i=0;i<s;i++){
    	myAddresses.addresses=(addr *) malloc(sizeof(addr)*l);
        newCache.cache[i]=myAddresses;
        for (int j = 0; j < l; j ++){
        	myAddress.counter = 0;
        	myAddress.v = 0;
        	myAddress.t = 0;
            myAddresses.addresses[j] = myAddress;
        }
    }
    return newCache;
}//end makeCache

//make cache empty
void emptyCache(cache myCache,long long s,int l,long long bs){
    for(int i=0;i<s;i++){
        addrs set = myCache.cache[i];
        if (set.addresses != NULL){
            free(set.addresses);
        }
    }
    if (myCache.cache!=NULL){
        free(myCache.cache);
    }
}//end emptyCache

//find an empty address
int emptyAddr(addrs s,params param){
    addr myAddress;
    int i;

    for(i=0;i<param.E;i++){
    	myAddress=s.addresses[i];
        if(myAddress.v==0){
            return i;
        }
    }
    return 0;
}//end emptyAddr

//find LRU
int leastRecentlyUsed (addrs s, params param, int *used_lines) {
	//initialize min&max
    int max=s.addresses[0].counter;
    int min=s.addresses[0].counter;
    int minIndex=0;

    for (int i=1;i<param.E;i++){
    	addr myAddress=s.addresses[i];
        if (min>myAddress.counter){
            minIndex=i;
            min=myAddress.counter;
        }
        if (max<myAddress.counter){
            max=myAddress.counter;
        }
    }
    //reset cache array positions
    used_lines[0]=min;
    used_lines[1]=max;
    return minIndex;

}//end leastRecentlyUsed

//simulation of a cache
params sim(cache myCache, params param, memHold address){
        int sizeTag=(64-(param.s+param.b));
        unsigned long long tempTag=address<<(sizeTag);
        unsigned long long newIndex=tempTag>>(sizeTag+param.b);
        memHold newTag=address>>(param.s+param.b);
        addrs cacheQuery=myCache.cache[newIndex];
        int origHit=param.hits;
        int flag=1;
        int *checked=(int*)malloc(sizeof(int)*2);
        int min_used_index = leastRecentlyUsed(cacheQuery,param,checked);

        //run simulation
        for(int i=0;i<param.E;i++){
            addr myAddress = cacheQuery.addresses[i];
            if(myAddress.v) {
                if(myAddress.t==newTag){
                	myAddress.counter++;
                    param.hits++;
                    cacheQuery.addresses[i]=myAddress;
                }
            } else if(!(myAddress.v)&&(flag)){
            	flag=0;
            }
        }
        if(origHit==param.hits){
            param.misses++;
        }
        else{
            return param;
        }
        if(flag){
            param.evictions++;
            cacheQuery.addresses[min_used_index].t=newTag;
            cacheQuery.addresses[min_used_index].counter=checked[1]+1;
        }
        else{
            int emptyLine=emptyAddr(cacheQuery,param);
            cacheQuery.addresses[emptyLine].t=newTag;
            cacheQuery.addresses[emptyLine].v=1;
            cacheQuery.addresses[emptyLine].counter=checked[1]+1;
        }
        free(checked);
        return param;
}//end sim

//main
int main(int argc,char **argv){
    cache myCache;
    params param;
    bzero(&param,sizeof(param));
    long long s,bs;
    FILE *f;
    memHold bits;
    int size;
    char *readF,c,input;

    //all cases
    while((c=getopt(argc,argv,"s:E:b:t:vh"))!=-1){
        switch(c){
        case 's':
        	param.s=atoi(optarg);
            break;
        case 'E':
        	param.E=atoi(optarg);
            break;
        case 'b':
        	param.b=atoi(optarg);
            break;
        case 't':
            readF=optarg;
            break;
        case 'v':
            v=1;
            break;
        case 'h':
            exit(0);
        default:
            exit(1);
        }
    }

    s=pow(2.0,param.s);
    bs=powBit(param.b);
    param.hits=param.misses=param.evictions=0;
    myCache = makeCache(s,param.E,bs);
    f = fopen(readF,"r");

    //scan file for hits and misses
   	if (f!=NULL) {
        while (fscanf(f," %c %llx,%d",&input,&bits,&size)==3){
            switch(input) {
                case 'I':
                	break;
                case 'L':
                    param=sim(myCache,param,bits);
                    break;
                case 'S':
                	param=sim(myCache,param,bits);
                	break;
                case 'M':
                	param=sim(myCache,param,bits);
                	param=sim(myCache,param,bits);
                	break;
                default:
                break;
            }
        }
    }
   	//print final results
    printSummary(param.hits,param.misses,param.evictions);
    //empty cache
    emptyCache(myCache,s,param.E,bs);
    //close file
    fclose(f);
    return 0;
}//end main
