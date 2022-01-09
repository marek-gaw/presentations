##

https://github.com/NelsonBilber/cpp-overview/blob/master/docs/containers.and.iterators.org

Scott Meyers
Look at Effective STL by Scott Meyers. It’s good at explaining how to use the STL.

If you want to store a determined/undetermined number of objects and you’re never going to delete any, then a vector is what you want. It’s the default replacement for a C array, and it works like one, but doesn’t overflow. You can set its size beforehand as well with reserve().

If you want to store an undetermined number of objects, but you’ll be adding them and deleting them, then you probably want a list…because you can delete an element without moving any following elements - unlike vector. It takes more memory than a vector, though, and you can’t sequentially access an element.

If you want to take a bunch of elements and find only the unique values of those elements, reading them all into a set will do it, and it will sort them for you as well.

If you have a lot of key-value pairs, and you want to sort them by key, then a map is useful…but it will only hold one value per key. If you need more than one value per key, you could have a vector/list as your value in the map, or use a multimap.

It’s not in the STL, but it is in the TR1 update to the STL: if you have a lot of key-value pairs that you’re going to look up by key, and you don’t care about their order, you might want to use a hash - which is tr1::unordered_map. I’ve used it with Visual C++ 7.1, where it was called stdext::hash_map. It has a lookup of O(1) instead of a lookup of O(log n) for map.

http://john-ahlgren.blogspot.com/2013/10/stl-container-performance.html

Some Additional Notes
Adaptors: queue and stack
For std::queue and std::stack, complexity depends on the underlying container used (by default std::deque).

vector
std::vector has constant time (O(1)) back insertion provided no reallocation needs to take place (use reserve/capacity to allocate/check). When reallocation is necessary, all elements are copied (or moved, if possible) to a need memory location. It is guaranteed that back insertion is amortized constant, meaning: "if we perform a large amount of back insertions, the average time for back insertion is constant".

Insertion does not invalidate iterators as long as no reallocation is performed (when reallocating, all iterators become invalid). Deletion invalidates all iterators after the deleted element, iterators to elements before are still valid.

deque
Insertion and deletion of elements in a std::deque may invalidate all its iterators. Pointers are however persistent. In practice accessing / iterating over a std::vector is faster than std::deque.

All iterators may become invalid after an insertion or deletion, but pointers/references are always valid.

list
If you have an iterator to an element, you can insert right after (or before) that element in constant time (O(1)). Of course, you can also erase it or access it directly (O(1)) using the iterator (or any adjacent element, as ++iterator / --iterator are constant time operations).

If you only know the index, e.g. that you wish to insert/retrieve/erase the 4th element, you'll need to iterate the list until you reach that element. Put differently: std::list does not provide random access.

sorted vector and deque
To search for an element in a sorted std::vector or std::deque, use std::equal_range. If only the first element is needed, there is std::lower_bound. If you only want to know whether an element exists or not, there is std::binary_search.

set and map
Requires a less-than comparison function. Complexities also apply to multiset and multimap.

unordered_set and unordered_map (hash tables)
unordered_set and unordered_map has constant time performance on all operations provided no collisions occur. When collisions occur, traversal of a linked list containing all elements of the same bucket (those that hash to the same value) is necessary, and in the worst case, there is only one bucket; hence O(n).

Requires a hash function and equality comparison function. Complexities also apply to unordered_multiset and unordered_multimap.

Deletion does not invalidate any iterators (other than erased element). Insertion keeps all iterators valid as long as no rehashing is done. When rehashing is performed, all iterators become invalid. Pointers/references to elements always remain valid.

multiset, multimap, unordered_multiset, unordered_multimap
std::multiset and std::multimap follow the same rules as std::set and std::map.
std::unordered_multiset and std::unordered_multimap follow the same rules as std::unordered_set and std::unordered_map.

The only reason they are not listed in the table/throughout this document is to save space.

basic_string
Strictly speaking std::string and std::wstring are typedefs for basic_string, which is a container. What applies to string above applies more generally to basic_string (and hence, to std::wstring too).

Note that prior to C++11 basic_string was not required to store its elements (characters) contiguously. Now it acts as std::vector, except its only valid for POD types and some tricks that don't violate the constraints may be employed (in practice: small string optimization).

priority_queue
Requires a less-than comparison function. Always gives the greatest element (according to comparison function) when top() is called. top() is constant time, but pop() requires O(log n) as the queue needs to be rearranged (to ensure next top() correctly gives greatest element).

Complexity
https://medium.com/@rodrigues.b.nelson/know-your-algorithms-complexity-116da218fd3f


## General Rules of Thumb

*Memory allocation may also be a factor in your decision. Here are the general rules of thumb for how the different sequential containers are storing memory:*

* std:vector, std::array, and std::string store memory contiguously and are compatible with C-style APIs
* std::deque allocates memory in chunks
* std::list allocates memory by node



https://stackoverflow.com/questions/3873802/what-are-containers-adapters-c
Sequence Containers
Here are the sequence containers, meaning the data is reliably ordered (that is, there is a front and a back to them. I do NOT mean that they automatically sort themselves!).

A vector is a bit like a flexibly-sized array. Vectors are random-access, meaning you can access any element with integer index in constant time (just like an array). You can add or remove from the end of the array in (nearly) constant time as well. Anywhere else, though, and you're probably looking at having to recopy potentially all of the elements.
A deque, or double-ended queue, is like a vector but you can add to the front or the back. You can still access elements in constant time, but deque elements are not guaranteed to be contiguous in memory like vectors or arrays.
A list is a linked list, meaning data which are linked together by pointers. You have constant-time access to the beginning and the end, but in order to get anywhere in the middle you need to iterate through the list. You can add elements anywhere in the list in constant time, though, if you already have a pointer to one of the nearby nodes.
Associative Containers
These are associative containers, meaning that elements are no longer ordered but instead have associations with each other used for determining uniqueness or mappings:

A set is a container with unique elements. You can only add one of each element to a set; any other additions are ignored.
A multiset is like a set, but you can put more than one of an element in. The multiset keeps track of how many of each kind of element are in the structure.
A map, also known as an associative array, is a structure in which you insert key-value pairs; then you can look up any value by supplying the key. So it's a bit like an array that you can access with a string index (key), or any other kind of index. (If you insert another key-value pair and the key already exists, then you just overwrite the value for the original key.)
A multimap is a map that allows for insertion of multiple values for the same key. When you do a key lookup, you get back a container with all the values in it.
Container Adapters
Container adapters, on the other hand, are interfaces created by limiting functionality in a pre-existing container and providing a different set of functionality. When you declare the container adapters, you have an option of specifying which sequence containers form the underlying container. These are:

A stack is a container providing Last-In, First-Out (LIFO) access. Basically, you remove elements in the reverse order you insert them. It's difficult to get to any elements in the middle. Usually this goes on top of a deque.
A queue is a container providing First-In, First-Out (FIFO) access. You remove elements in the same order you insert them. It's difficult to get to any elements in the middle. Usually this goes on top of a deque.
A priority_queue is a container providing sorted-order access to elements. You can insert elements in any order, and then retrieve the "lowest" of these values at any time. Priority queues in C++ STL use a heap structure internally, which in turn is basically array-backed; thus, usually this goes on top of a vector.
See this reference page for more information, including time complexity for each of the operations and links to detailed pages for each of the container types.