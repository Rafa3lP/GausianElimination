# Gausian Elimination

This is a C program that solves a system of linear equations using Gaussian Elimination. Work carried out as part of the numerical algorithms discipline.

## Summary
- [Overview](#overview)
- [Usage](#usage)
- [File Format](#file-format)
- [Compilation](#compilation)
- [Debugging](#debugging)

## Overview

This program implements the Gaussian Elimination algorithm to solve a system of linear equations in the form of `Ax = b`, where A is a square matrix, x is the solution vector, and b is the right-hand side vector.

## Usage

1. Create an input file containing the linear system you want to solve.
2. Run the program, passing the input file as a command-line argument.
```bash
./gausianElimination linearSystem.dat
```

## File Format
The input file should follow the format described below:

1. The first line should contain a single integer n, representing the dimension of the square matrix A.
2. The next n lines should contain n space-separated values, representing the elements of the matrix A.
3. The final line should contain n space-separated values, representing the elements of the vector b.

Example input file:
```
3
5.0 2.0 1.0
2.0 -1.0 3.0
0.0 1.0 -2.0
8.0 9.0 -6.0
```
The file above represents the following linear system:
```math
\begin{cases}
5x + 2y + z = 8 \\
2x - y + 3z = 9 \\
y - 2z = -6
\end{cases}
```
## Compilation
Use make to compile the program:
```bash
make release
```

## Debugging
It is also possible to generate a debug version that better describes the steps performed:
```bash
make debug
```
