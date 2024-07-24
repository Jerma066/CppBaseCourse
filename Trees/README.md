# HWRQ: Range Queries

## Problem description:
1. Given a tree with a specified number of elements, find the count of keys in the tree that fall within the range defined by pairs of elements provided as input<br>

2. Input and output data format<br/>
  - Input includes:
    - The total number of tree elements (n) followed by the tree elements (int numbers).
    - The count of pairs for querying the tree and the pairs themselves (pair of int numbers).
  - Output should display:
    - For each query, the number of tree elements lying between the pair elements.
  - Example:<br/>
&nbsp; &nbsp; &nbsp; Input data: <br/>
&nbsp; &nbsp; &nbsp; &nbsp; 2 <br/>
&nbsp; &nbsp; &nbsp; &nbsp; 10 20 30 40 <br/>
&nbsp; &nbsp; &nbsp; &nbsp; 3 <br/>
&nbsp; &nbsp; &nbsp; &nbsp; 8 31 <br/>
&nbsp; &nbsp; &nbsp; &nbsp; 6 9 <br/>
&nbsp; &nbsp; &nbsp; &nbsp; 15 40 <br/>
&nbsp; &nbsp; &nbsp; Output data: <br/>
&nbsp; &nbsp; &nbsp; &nbsp; 3 0 3 <br/>

## Build and launch
1. To build solution use the following command:
  ```bash
  ./build.sh
  ```
2. To launch the solution use generated executable file:
  ```bash
  ./build/main
  ```
3. To build and launch unit tests use the following comand:
  ```bash
  cd build
  make unit_tests
  ./unit_test
  ```
