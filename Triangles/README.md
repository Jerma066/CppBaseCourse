# HW3D: Triagnles intersection detection

## Problem description:
1. Task statement: Print the numbers of all triangles from input set that intersect with any other.

2. Input and output data format<br/>
  • The number 0 < N < 1000000 comes from the standard input, and then N sets of points representing three-dimensional triangles.<br/>
  • The idexes of the triangles that intersect with any other are returned to stdout.<br/>
  • Example:<br/>
&nbsp; &nbsp; &nbsp;Input data:<br/>
&nbsp; &nbsp; &nbsp; &nbsp;2<br/>
&nbsp; &nbsp; &nbsp; &nbsp;0 0 0 1 0 0 0 1 0<br/>
&nbsp; &nbsp; &nbsp; &nbsp;0 0 0 5 5 0.01 5 5 0<br/>
&nbsp; &nbsp; &nbsp;Output data:<br/>
&nbsp; &nbsp; &nbsp; &nbsp;0<br/>
&nbsp; &nbsp; &nbsp; &nbsp;1<br/>

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
