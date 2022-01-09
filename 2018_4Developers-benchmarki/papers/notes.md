

## Problem z demanglingiem na Ubuntu

opis: https://bugs.launchpad.net/ubuntu/+source/linux/+bug/1396654
rozwiązanie: https://stackoverflow.com/questions/33057653/perf-enable-demangling-of-callgraph/34061874#34061874

```bash
sudo apt-get install libiberty-dev binutils-dev
```

włączyć źródła w /etc/apt/sources.list

```bash
apt-get source linux-tools-$(uname -r)
sudo apt-get build-dep linux-image-$(uname -r)
```

## Uzycie perf

http://www.brendangregg.com/perf.html

```bash
sudo ./perf record -F 97 ~/workspaces/qt4/build-4dev-Desktop_Qt_5_7_1_GCC_64bit-Debug/4dev 
sudo ./perf report
```

```bash
 Lx  …/tools/perf  sudo ./perf report                                                           
# To display the perf.data header info, please use --header/--header-only options.
#
#
# Total Lost Samples: 0
#
# Samples: 12  of event 'cycles:ppp'
# Event count (approx.): 1191957243
#
# Overhead  Command  Shared Object      Symbol                    
# ........  .......  .................  ..........................
#
    75.99%  4dev     4dev               [.] 0x0000000000003f55
     5.73%  4dev     [kernel.kallsyms]  [k] load_elf_binary
     4.10%  4dev     4dev               [.] 0x0000000000003aa5
     3.24%  4dev     4dev               [.] 0x0000000000003f58
     2.95%  4dev     4dev               [.] 0x0000000000003b0e
     2.77%  4dev     4dev               [.] 0x0000000000003fcf
     2.65%  4dev     4dev               [.] 0x0000000000004159
     2.55%  4dev     4dev               [.] 0x00000000000040c5
     0.01%  perf     [kernel.kallsyms]  [k] native_sched_clock
     0.00%  perf     [kernel.kallsyms]  [k] native_apic_mem_write
     0.00%  perf     [kernel.kallsyms]  [k] ctx_resched
     0.00%  perf     [kernel.kallsyms]  [k] intel_bts_enable_local
```

# Valgrind

Valgrind is simply a framework for building dynamic tools. Although, it's become synonymous with Memcheck, a tool built on Valgrind. Callgrind is a pretty good at profiler. – Falaina Jul 22 '09 at 23:10

[tutorial](https://baptiste-wicht.com/posts/2011/09/profile-c-application-with-callgrind-kcachegrind.html)

```bash
sudo apt-get install valgrind kcachegrind graphviz
```

KCachegrind

/usr/bin/valgrind  --tool=callgrind  --dump-instr=yes --collect-jumps=yes  ~/workspaces/qt4/build-4dev-Desktop_Qt_5_7_1_GCC_64bit-Debug/4dev  

 kcachegrind ./callgrind.out.16221

 https://stackoverflow.com/questions/1168766/what-is-a-good-easy-to-use-profiler-for-c-on-linux

 # gprof

 Use gprof.

Just compile with -pg flag (I think (but am not sure) you have to turn of optimizations though.) and use gprof to analyze the gmon.out file that your executable will then produce.

eg:

gcc -pg -o whatever whatever.c

./whatever

gprof whatever gmon.out
Same thing with g++ and cpp.

# Ogólne

https://www.reddit.com/r/cpp/comments/431yg1/how_do_you_profile_your_c_code/
https://cppcon.org/debugging-and-profiling-cpp-code-on-linux/

perf + google benchmark (Chandlers video from cppcon2015)

Instalacja libc++

https://stackoverflow.com/questions/39332406/install-libc-on-ubuntu
```
sudo apt-get install libc++-dev
```

lub rozwinięcie tematu: własny Clang i stdlib

ABI:
https://askubuntu.com/questions/471477/unmet-dependencies-libc
```
sudo apt-get install libc++1 multiarch-support libc6 libc++-dev libc++-helpers libc++-test libc++abi-dev libc++abi-test libc++abi1
```


## Statistics

```bash
# command line configuration
result=$(./bench2 --benchmark_format=json --benchmark_repetitions=10 --benchmark_report_aggregates_only=true)
```


## Summary

* number of monitoring tools
* 

::: notes

Big picture: 
* widać cały obraz systemu
* widać zależności i interakcje w systemie
* jest dużo wyspecjalizowanych narzędzi

:::