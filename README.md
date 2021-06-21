# Brute Force Sudoku

This is just something I made for fun in some free time I had.

## More stuff to read

+ [CHANGES.md](./CHANGES.md)
+ [LICENSE](./LICENSE)

## Usage

```
$ ./a.out
Enter numbers of sudoku. Use 0 for blank space:
5 3 - | - 7 - | - - -
6 - - | 1 9 5 | - - -
- 9 8 | - - - | - 6 -
---------------------
8 - - | - 6 - | - - 3
4 - - | 8 - 3 | - - 1
7 - - | - 2 - | - - 6
---------------------
- 6 - | - - - | 2 8 -
- - - | 4 1 9 | - - 5
- - - | - 8 - | - 7 9
```

or

```
$ echo '530070000600195000098000060800060003400803001700020006060000280000419005000080079' | ./a.out
```

## Compilation

No special compile parameters

```sh
sudo apt install build-essential
gcc sudoku.c
./a.out
```
