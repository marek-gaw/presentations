accumulate.md

# std::accumulate

```cpp
#include <numeric>
```

**Definition**

Computes the sum of the given value init and the elements in the range [first, last). 

# Example

```cpp
std::vector<int> numbers = { 2, 9, -4, 2 };
int sum = std::accumulate(begin(numbers), end(numbers), 0);
```
. . .

Beware!

```cpp
std::vector<double> doubles = { 1.5, 2, 3.5 };
double sum = std::accumulate(begin(doubles), end(doubles), 0);
```

#Example:

```cpp
std::vector<std::string> words = { "Winter ", "is ", "Coming." };
std::string sentence = std::accumulate(begin(words), end(words), std::string(""));
```

. . . 

Hint!

. . .

```cpp
type_of("") // ?
type_of(std::string("")) //?
```

# Example

Lambda? Lambda!

```cpp
double totalWeight = std::accumulate(begin(group), end(group), 0.,
                    [](double currentWeight, Person const& person)
                    {
                        return currentWeight + person.getWeight();
                    });
```

first parameter is _very_ interesting!

# Don't go this way!

```cpp
std::accumulate(begin(group), end(group), &weights,
                [](std::vector<double>* currentWeights, Person const& person)
                {
                    currentWeights->push_back(person.getWeight());
                    return currentWeights;
                });
```
Why?

But this is wrong. I’ve seen this in code. Hell, I’ve done it myself before I knew better about algorithms.

Why is it wrong? Because this code traverses a range, applies a function on each element and puts the results in a new collection. This is what std::transform would express in code.

# Do/nt!

When the return value of std::accumulate is discarded, it is a sign that it is not the right tool to use.

# Example

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    int sum = std::accumulate(v.begin(), v.end(), 0);
 
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
 
    std::string s = std::accumulate(std::next(v.begin()), v.end(),
                                    std::to_string(v[0]), // start with first element
                                    [](std::string a, int b) {
                                        return a + '-' + std::to_string(b);
                                    });
 
    std::cout << "sum: " << sum << '\n'
              << "product: " << product << '\n'
              << "dash-separated string: " << s << '\n';
}
```


```bash
sum: 55
product: 3628800
dash-separated string: 1-2-3-4-5-6-7-8-9-10
```

# Scott Mayers said:

_"std::accumulate is made to summarize a range"_

which means:

_std::accumulate takes a collection of elements and returns only one value._

and:

_If you don’t specify anything, std::accumulate does the sum of all the elements in the range that it takes. This sum being done with operator+. And since we need two values to call operator+, we also need a initial value to start off the algorithm._

# Sweetnes

pretty much every algorithm of the STL can be implemented by using std::accumulate!

```
std::accumulate(std::begin(booleans), std::end(booleans), true, std::logical_and<>())
```

# See also

adjacent_difference - computes the differences between adjacent elements in a range 
inner_product - computes the inner product of two ranges of elements 
partial_sum - computes the partial sum of a range of elements 
reduce - similar to std::accumulate, except out of order 