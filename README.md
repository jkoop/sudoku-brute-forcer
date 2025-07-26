# Brute Force Sudoku

Solves the sudoku no matter how hard it is. Also, it's insanely fast.

## More stuff to read

-   [CHANGES.md](./CHANGES.md)
-   [LICENSE](./LICENSE)

## Compilation

No special compile parameters

```sh
make
```

## Usage

```
./sudoku 530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

Additionally, the solver is implemented as a convenient helper library. See `src/sudoku.c:main` and `src/libsudoku.h` for more.
