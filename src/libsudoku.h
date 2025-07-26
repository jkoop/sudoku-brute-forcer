#include <stdbool.h>
#include <stdint.h>

typedef uint_fast8_t sudoku_board[81];
struct sudoku_state {
	// the solved board, set by sudoku_next_solution()
	sudoku_board solved_board;

	// there aren't any more solutions
	bool is_done;

	// internal use below this line

	bool is_cell_readonly[81];

	struct {
		int_fast8_t board;
		int_fast8_t row;
		int_fast8_t column;
		int_fast8_t square;
	} positions;

	struct {
		uint_fast8_t rows[9][10];
		uint_fast8_t columns[9][10];
		uint_fast8_t squares[9][10];
	} counts;
};

/**
 * Resets the given state, copying data from the given board. Returns:
 * false, if the given board has immediate self-contradictions (e.g. two of
 *        the same number in the same row). The state is now invalid.
 * true, otherwise.
 */
bool sudoku_init(struct sudoku_state* state, sudoku_board given_board);

/**
 * Finds the next solution, and sets state->solved_board. Returns:
 * true, if there's a next solution.
 * false, otherwise. state->solved_board is now invalid.
 */
bool sudoku_next_solution(struct sudoku_state* state);
