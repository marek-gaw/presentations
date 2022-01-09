---
author: Marek Gawryszewski
title: Iterators
date: 06-02-2019
---

## The problem

* Let's define standard container.
* How to get to element in standard way?
* Is indexing an efficient way?
* Do we really need it?


## What is an iterator?

Traversal over collection

Iterator is a object, which allows to access (modify) element in a container

Trivial implementation: const pointer

## begin() and end()

## cbegin() and cend()

## rbegin() and rend()

## examples

To illustrate, consider the algorithm std::reduce. One of its overloads takes two iterators and returns the sum of the objects contained between those two iterators:
std::vector<int> numbers = {1, 2, 3, 4, 5};
    
std::cout << std::reduce(begin(numbers), end(numbers)) << '\n';
1
2
3
	
std::vector<int> numbers = {1, 2, 3, 4, 5};
    
std::cout << std::reduce(begin(numbers), end(numbers)) << '\n';

This should output 15, which is the sum of the elements inside numbers.

## Iterator is deprecated in C++17

. . .

Nice clickbiat, huh?

. . .

Deprecated is std::iterator (class)


## References

(std::iterator is deprecated: Why, What It Was, and What to Use Instead)[https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/]