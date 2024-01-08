# HWC: Cache replacement policy

## Problem description:
1. Support any caching algorithm from the listed below<br/>
  • ARC (adaptive replacement cache)<br/>
  • 2Q (two queue algorithm, further development of LRU)<br/>
  • LFU (the least frequently used replacement)<br/>
  • LIRS (low-inference recency set)<br/>

2. Input and output data format<br/>
  • The cache size and number of elements are passed to standard input (stdin), then the elements are passed themselves (elements are written in integers).<br/>
  • The number of cache hits is returned to stdout.<br/>
  • Example:<br/>
&nbsp; &nbsp; &nbsp; Input data:  2 6 1 2 1 2 1 2 <br/>
&nbsp; &nbsp; &nbsp; Output data: 4 <br/>
## Build and launch
1. To build solution use the following command:
  ```bash
  make main
  ```
2. To launch the solution use generated executable file:
  ```bash
  ./main
  ```
3. To build and launch unit tests use the following comand:
  ```bash
  make unit_tests
  ```
