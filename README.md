## TO COMPILE AND RUN
To Compile :- "g++ -std=c++17 main.cpp Cache.cpp FIFO.cpp LFU.cpp LRU.cpp -o obj"
To Run :- "./obj"

## Design description
LRU cache and LFU cache and FIFO cache are implemented.
To visualize the cache, print function is added.

### Cache design
From a cache, we expect few functionalities to be exposed.
In this implementation, we have exposed most of the CRUD functionalities:
* GET
* PUT
* DELETE
* CLEAR

A cache can have different eviction policies. In this implementation, LRU, LFU and FIFO is considered. 
A common base class for Cache is created, which is then inherited by LRU, LFU and FIFO cache implementations. 
A factory method is exposed to instatiate a particular cache.

### LRU (Least Recently Used) Cache design
Doubly Linked List is used to implement cache. 
In every Put, if key is not present, new node is created and pushed to back of the queue. 
During any get, the node is removed from existing position and pushed to back of the queue. 
For eviction, front of the queue is evicted. 
To access a particular node, a map of key to node is maintained

### LFU (Least Frequently Used) Cache design
Three DataStructures are used
1. Key - Value map
2. Key - frequency map
3. Frequency - Key map

In every Put, key - value map is updated. Similarly frequency of 1 is assigned to this. 
In a get, Frequency is increased by 1, and key is moved in frequency - key map from current frequency to next. 
In frequency-key map, multiple keys can have same frequency. Hence a queue of keys is maintained.
During eviction, we extract key from bucket having least frequency. As we extract key from a queue, least recently used key is evicted

### FIFO (First In First Out) Cache design
Doubly Linked List is used to implement cache. 
In every Put, if key is not present, new node is created and pushed to back of the queue. 
During any get, there is no change done whether there is hit or miss. 
For eviction, front of the queue is evicted. 
To access a particular node, a map of key to node is maintained

### TTL implementation
TTL can be implemented in various ways.
One of the most popular way is reactive TTL. i.e., when user asks for a key, it's expiry is checked and deleted if required. 
In here, Psuedo proactive method is used. During any call to cache, we check if there are any keys to be expired and it is deleted. 
To achieve this one, a min heap is used where comparison is on TTL. Top of the heap denotes the node which has to be expired at the earliest. 
As C++ STL priority queue does not support random erase, the STL is extended to support the functionality

### Additional tools
For doubly linked list, we have created a new custom templatized class, which expose required functionalities