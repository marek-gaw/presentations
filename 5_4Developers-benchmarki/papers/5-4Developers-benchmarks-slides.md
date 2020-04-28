---
author: Marek Gawryszewski
title: Narzędzia do analizy wydajności aplikacji
date: 23-10-2018
---

# Intro

::: notes

Agenda:
Wydajność aplikacji jest drugą najważniejszą rzeczą (pierwsza - poprawne działanie) jaką powinniśmy zapewnić. Pisanie kodu, którego wydajność nie będzie dla nas (najczęściej niemiłym...) zaskoczeniem, nie jest łatwe. Na szczęście programiści C++ mają w zanadrzu kilka narzędzi, które pozwalają zmierz...

Czas:
45min

:::

## What is the question?

* Why we are interested in application performance?

. . . 

* Because fuck off that's why.

## What do we need to improve?

We need tools.
We need to understand our tools.

## Who am i?

* Software Engineer at Harman
* Founder/facilitator of C/Embedded/Hardware User Group

## Agenda
- benchmarking vs profiling
- what should be benchmarked?
- How to measure time, CPU/memory consumption?
- perf
- Google Benchmark

## Life is full of sorrow...

Writing correct programs is hard.
Profiling is far more harder.



## What do we need before starting?

_CLEAN ARCHITECTURE_
_TESTS_

::: notes

* Zanim zaczniemy profilować, musimy mieć kod, który poprawnie dziala
* TESTY!

Profilowanie niepoprawnego kodu nie ma sensu - uzyskamy błędne wyniki - tylko szybciej.
Szybki ale błędny kod jest tak samo bezużyteczny.
Nie lubimy testów, choć wiemy, że powinniśmy je pisać.

:::

## What do we need before starting?

Before even staring to thing about profiling/benchmarking, we need to be sure that our code:
* correct: it is doing what it is supposed to
* understandable: code is written for humans
* testable:

This is "must have" to prove, that code upgrade did not introduced regression

## The problem

1. Application which is "slow" all the time
2. Application which is "slow" from time to time

## The problem

What can be done?

# Admin Toolbox

## How to find hot spots?

There are numerous tools to check performance
(obrazek z narzędziami z linuxa)

::: notes

* Jest wiele narzędzi
* Które z nich wybierzemy jako pierwsze?
* Zwykle bierzemy narzędzia bo je znamy....

## How to find hot spots?

![https://raw.githubusercontent.com/brendangregg/perf-tools/master/images/perf-tools_2016.png](images/png/perf-tools_2016.png)

## How to find hot spots?

_Which one should I use?_

* The one I know?
* The one I suspect is the right one?
* ... all?

## Tools for "first contact" - system wide

[top](https://linux.die.net/man/1/top)/[htop](http://hisham.hm/htop/)

::: notes

Zestaw narzędzi z prezentacji Gregga

wegdług podzialu na rodzaje monitorowanych zasobów

:::

## Side note: why general tools are important

::: incremental

- Application does not work without a context
- OS, hardware, peipherials
- network

:::



## Perf

Linux profiling tool

```bash
apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r`
```

::: notes

Czym jest profilowanie?

Perf korzysta z hardwareowych performance counters - nie wpływa na performance aplikacji


Changler Carruth - dużo fajnych talków


:::

## Perf: use case

::: notes

Tutaj wjeżdza albo przykład, albo obrazki

:::

## Summary

There are number of tools.

_Take a look at the whole system first_


# Developer's perspective

## What is in our toolbox?

* gperf
* valgrind (+kcachegrind)
* strace
* likwid


online:

* godbolt.org
* [http://quick-bench.com](http://quick-bench.com/suql1AKnQ9a5l7ijd6ehwz_iVFk)


## What elese?

Engineering approach:
we need to prove our guess.

How?
::: incremental
* monitoring
* logging
* benchmark

:::


## Reminder

What about the coding?

*Let you compiler do its job*

::: notes

generalna idea jest taka, że ludzie mają tendencję do przedwczesnej optymalizacji.
Np. loop unrlolling.
Na prawdę, lepsze wyniki daje czytelny kod, który jest rozumnie napisany niż spagetti, gdzie fora zatępujemy ifami. Chyba, że nazywamy się Alexandrescu i C++ znamy na 6/10.

Lepiej ten czas poświęcić na lepsze zrozumienie języka i tego co się dzieje pod spodem i dlaczego.


::

## How to measure the code?

_std::chrono_ to the rescue!

##

```cpp
#include <chrono>
#include <iostream>
#include "production_code.hpp"
#include "new_ideas.hpp"

int main(int argc, char** argv){

    auto start = std::chrono::high_resolution_clock::now();
    auto result = production_code::algorithm();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_p = (end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto new_result = new_ideas::algorithm();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_i = (end - start);

    std::cout << "we achieved a speed-up of " << t_p.count()/t_i.count() 
              << std::endl;
              
    return 0;
}
```

## check for correctness

```cpp
#include <chrono>
#include <iostream>
#include "production_code.hpp"
#include "new_ideas.hpp"

int main(int argc, char** argv){

    auto start = std::chrono::high_resolution_clock::now();
    auto result = production_code::algorithm();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_p = (end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto new_result = new_ideas::algorithm();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_i = (end - start);

    if(result == new_result)
        std::cout << "we achieved a speed-up of " << t_p.count()/t_i.count() 
                  << std::endl;
    else
        std::cout << "Never mind!" << std::endl;
}
```

## noisy lab under your fingers

```cpp
#include ...

int main(int argc, char** argv){

    auto result = 0;
    auto new_result = 0;
    
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0;i<n_repetitions;++i)
        result = production_code::algorithm();
   
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_p = (end - start);
    
    start = std::chrono::high_resolution_clock::now();
    
    for(int i = 0;i<n_repetitions;++i)
        new_result = new_ideas::algorithm();
        
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_i = (end - start);

    if(result == new_result)
        std::cout << "we achieved a speed-up of " << t_p.count()/t_i.count() 
                  << std::endl;
    else
        std::cout << "Never mind!" << std::endl;
}
```
## please take notes
```cpp
#include ...

using duration_t = std::chrono::duration<double>;

int main(int argc, char** argv){
    //..
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start;
    std::vector<duration_t> my_timings(n_repetitions);

    for(int i = 0;i<n_repetitions;++i){
        start = std::chrono::high_resolution_clock::now();
        result = production_code::algorithm();
        my_timings[i] = std::chrono::high_resolution_clock::now() - start;
    }
   
    //same with new_result = new_ideas::algorithm()

    if(result == new_result){
        std::ofstream ofile("results.csv");ofile.open();
        for(int i = 0;i<n_repetitions;++i){
            ofile << i << ",production," << prod_timings[i].count() << ",seconds" << std::endl;
        }
        //same with new_idea
        ofile.close()
    }
    else
        std::cout << "Never mind!" << std::endl;
}
```

We need some instrumentation

## How to make this simpler?

Use Google Benchmark

## Tools: [Google benchmark](https://github.com/google/benchmark)

You have to create simple wrappers around code you want to benchmark and link either statically or dynamically with the benchmark lib

## Example 1

The Task:
calculate forward kinematics of 6DOF robot.

_Actually_ this is all about mutiplication of matrix.

## Ok, so I have some numbers...

* How many measurements?
* Statistics?

## Why do we need to care about methodolgy?

(obrazek z wykresem)

Is one measurement sufficient to prove hypothesis?
How many?
Which metrics we should use?

## Anything else?


Hardware is important!


::: notes

Trzeba by poszukać jakiegoś podręcznika od statystyki:-)

:::



# Summary

## It's good to listen to smart people

[CppCon 2015: Chandler Carruth "Tuning C++: Benchmarks, and CPUs, and Compilers! Oh My!"](https://www.youtube.com/watch?v=nXaxk27zwl)
[Awesome Perf Cpp](https://fenbf.github.io/AwesomePerfCpp/)

# Q&A

## Contact me!

Feel free to meet me at CEHUG!

Reach me via LI, FB