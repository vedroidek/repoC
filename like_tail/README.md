# Tail

__My own version of the program 'tail'. It show the newly lines in the target file. Useful for viewing logs in real time. Since the long type is used, the file size should not exceed 2^32 bits.__

For launch, the installed GCC 11.4.0 compiler is required or newer.

In your terminal:
```sh
# if need include '-g' flag for debugging
$ gcc -std=c11 -o <filename> my_tl.c
# or run Makefile
$ make
# launch
$ ./<filename> -h
```

---
_The program was written on OS Linux (Xubuntu 22.04 LTS). **On other systems was not checked!**_