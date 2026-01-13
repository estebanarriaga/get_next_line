# Libft

A library of C functions for 42 Madrid


### The project consists of two main parts:

## The **main** part

It consist on a series of functions in C, some of which are copies from already existing UNIX functions like `ft_strlen()` which has the same functionality as `strlen()` and other are 42 made like `ft_split()`. The UNIX based functions were made based solely on the information from the man pages from each function.

The correct functionality of the project was tested using the [francinette](https://github.com/xicodomingues/francinette) tester. This test all the possible errors and leaks that a concrete function may have. It also tests that the Makefile is working as it should.

The functions are separated in individual files that are compiled into a `libft.a` file. You can find the purpose of each function at the beginning of the function file.


## The **bonus** part

This part is optional and consist of working with C structures.
The node list can be found in the `libft.h` file.

The functions files from the bonus part are marked with `_bonus.c` at the end of the file
