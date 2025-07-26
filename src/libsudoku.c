#include "libsudoku.h"

/**
 * Resets the given state, copying data from the given board. Returns:
 * false, if the given board has immediate self-contradictions (e.g. two of
 *        the same number in the same row). The state is now invalid.
 * true, otherwise.
 */
bool sudoku_init(struct sudoku_state* state, sudoku_board given_board) {
	uint_fast8_t i;
	uint_fast8_t j;
	struct {
		int_fast8_t row;
		int_fast8_t column;
		int_fast8_t square;
	} positions;
	bool found_start_position = false;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 10; j++) {
			state->counts.rows[i][j] = 0;
			state->counts.columns[i][j] = 0;
			state->counts.squares[i][j] = 0;
		}
	}

	for (i = 0; i < 81; i++) {
		positions.row = i / 9;
		positions.column = i % 9;
		positions.square = positions.row / 3 * 3 + positions.column / 3;

		state->solved_board[i] = given_board[i];
		state->is_cell_readonly[i] = given_board[i] > 0;

		state->counts.rows[positions.row][given_board[i]] += 1;
		state->counts.columns[positions.column][given_board[i]] += 1;
		state->counts.squares[positions.square][given_board[i]] += 1;

		if (!state->is_cell_readonly[i] && !found_start_position) {
			found_start_position = true;
			state->positions.board = i;
			state->positions.row = positions.row;
			state->positions.column = positions.column;
			state->positions.square = positions.square;
		}
	}

	state->is_done = !found_start_position;

	for (i = 0; i < 9; i++) {
		for (j = 1; j < 10; j++) {
			if (
				state->counts.rows[i][j] > 1 ||
				state->counts.columns[i][j] > 1 ||
				state->counts.squares[i][j] > 1
			) {
				return false;
			}
		}
	}

	return true;
}

/**
 * Finds the next solution, and sets state->solved_board. Returns:
 * true, if there's a next solution.
 * false, otherwise. state->solved_board is now invalid.
 */
bool sudoku_next_solution(struct sudoku_state* state) {
	// We're essentially counting with extra rules.
	// Increment the current digit. If that results in there being more than one of that value in the row, column, or square, try incementing again. If incrementing results in that digit being greater than 9, set it to zero and backtrack to the left, trying to increment that one... After successfully incrementing a digit, advance to the right. Once we've reached the rightward end, the sudoku is solved. Once we've backtracked to the leftward end, we've run out of solutions.

	if (state->is_done) {
		return false;
	}

	while (1 > 0) {
		// Increment the current digit.
		state->counts.rows[state->positions.row][state->solved_board[state->positions.board]] -= 1;
		state->counts.columns[state->positions.column][state->solved_board[state->positions.board]] -= 1;
		state->counts.squares[state->positions.square][state->solved_board[state->positions.board]] -= 1;
		state->solved_board[state->positions.board] += 1;
		state->counts.rows[state->positions.row][state->solved_board[state->positions.board]] += 1;
		state->counts.columns[state->positions.column][state->solved_board[state->positions.board]] += 1;
		state->counts.squares[state->positions.square][state->solved_board[state->positions.board]] += 1;

		// If incrementing results in that digit being greater than 9
		if (state->solved_board[state->positions.board] > 9) {
			// set it to zero
			state->solved_board[state->positions.board] = 0;

			// and backtrack to the left
			while (1 > 0) {
				// Once we've backtracked to the leftward end
				if (state->positions.board == 0) {
					// we've run out of solutions
					state->is_done = true;
					return false;
				}

				state->positions.board -= 1;
				if (state->is_cell_readonly[state->positions.board]) {
					continue;
				}

				state->positions.row = state->positions.board / 9;
				state->positions.column = state->positions.board % 9;
				state->positions.square = state->positions.row / 3 * 3 + state->positions.column / 3;
				break;
			}

			continue;
		}

		// If that results in there being more than one of that value in the row, column, or square
		if (
			state->counts.rows[state->positions.row][state->solved_board[state->positions.board]] > 1 ||
			state->counts.columns[state->positions.column][state->solved_board[state->positions.board]] > 1 ||
			state->counts.squares[state->positions.square][state->solved_board[state->positions.board]] > 1
		) {
			// try incementing again
			continue;
		}

		// After successfully incrementing a digit, advance to the right
		while (1 > 0) {
			// Once we've reached the rightward end
			if (state->positions.board == 80) {
				// the sudoku is solved

				// if the rightmost digit is not writable,
				if (state->is_cell_readonly[state->positions.board]){
					// backtrack to the left
					while (1 > 0) {
						// safety check
						if (state->positions.board == 0) {
							break;
						}

						state->positions.board -= 1;
						if (state->is_cell_readonly[state->positions.board]) {
							continue;
						}

						state->positions.row = state->positions.board / 9;
						state->positions.column = state->positions.board % 9;
						state->positions.square = state->positions.row / 3 * 3 + state->positions.column / 3;
						break;
					}
				}

				return true;
			}

			state->positions.board += 1;
			if (state->is_cell_readonly[state->positions.board]) {
				continue;
			}

			state->positions.row = state->positions.board / 9;
			state->positions.column = state->positions.board % 9;
			state->positions.square = state->positions.row / 3 * 3 + state->positions.column / 3;
			break;
		}
	}
}
