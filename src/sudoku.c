#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "libsudoku.h"

void print_usage(char** argv) {
	printf("Usage: %s <sudoku>\n\nsudoku:\tan 81 digit number, representing the unsolved sudoku. Digits are given for every cell, left-to-right, top-down, where empty spaces are represented by zeros.\n\nExamples:\n\t%s 530070000600195000098000060800060003400803001700020006060000280000419005000080079\n", argv[0], argv[0]);
}

int main(int argc, char** argv) {
	struct sudoku_state state;
	sudoku_board given_board;
	uint_fast8_t i;
	uintmax_t count = 0;
	bool count_overflowed = false;
	char buffer[82] = {0};

	if (argc != 2 || strlen(argv[1]) != 81) {
		print_usage(argv);
		return 1;
	}

	for (i = 0; i < 81; i++) {
		if (argv[1][i] < '0' || argv[1][i] > '9') {
			print_usage(argv);
			return 1;
		}

		given_board[i] = argv[1][i] - '0';
	}

	if (!sudoku_init(&state, given_board)) {
		printf("E: The given sudoku has immediate self-contradictions.\n");
		return 1;
	}

	while (sudoku_next_solution(&state)) {
		count += 1;
		if (count == 0) {
			count_overflowed = true;
		}

		for (i = 0; i < 81; i++) {
			buffer[i] = state.solved_board[i] + '0';
		}

		printf("%s\n", buffer);
	}

	if (count_overflowed) {
		printf("Found > %ld solutions.\n", UINTMAX_MAX);
	} else {
		printf("Found %ld solutions.\n", count);
	}

	return 0;
}
