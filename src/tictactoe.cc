#include "tictactoe/tictactoe.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <string.h>


namespace tictactoe {

using std::string;

Board::Board(const string& board) {
  if (board.size() != BOARD_SIZE) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }
  boardString = board.substr(0, board.length());
  transform(boardString.begin(), boardString.end(), boardString.begin(), ::tolower);
}

BoardState Board::EvaluateBoard() const {
  //variables
  int x_count = 0;
  int o_count = 0;
  string x_in_row = "";
  string o_in_row = "";
  for (int i = 0; i < BOARD_LENGTH; i++) {
    x_in_row += "x";
    o_in_row += "o";
  }

  // Unreachable state testing
  for (int boardSpot = 0; boardSpot < BOARD_SIZE; boardSpot++) {
    if (boardString.at(boardSpot) == 'x' || boardString.at(boardSpot) == 'X') {
      x_count++;
    }
    if (boardString.at(boardSpot) == 'o' || boardString.at(boardSpot) == 'O') {
      o_count++;
    }
  }
  if (x_count > o_count + 1 || o_count > x_count) {
    return BoardState::UnreachableState;
  }

  // determines winner, if one is above 0, they win, unless both then unreachable state.
  int xWins = 0;
  int oWins = 0;

  // Horizontal testing
  for (int row = 0; row < BOARD_HEIGHT; row++) {
    if (boardString.substr(BOARD_LENGTH * row, BOARD_LENGTH) == x_in_row) {
      xWins++;
    } else if (
        boardString.substr(BOARD_LENGTH * row, BOARD_LENGTH) == o_in_row) {
      oWins++;
    }
  }

  // Vertical testing
  for (int column = 0; column < BOARD_LENGTH; column++) {
    string vertical = "";
    for (int j = column; j < BOARD_SIZE; j += BOARD_LENGTH) {
      vertical += boardString.at(j);
    }
    if (vertical == x_in_row) {
      xWins++;
    } else if (vertical == o_in_row) {
      oWins++;
    }
  }

  // Left to Right Diagonal testing (this is mostly applicable for boards with m = n = k)
  string diagonalLeftToRight = "";
  for (int i = 0; i < BOARD_LENGTH; i++) {
    diagonalLeftToRight += boardString.at(i * (BOARD_LENGTH + 1));
  }
  if (diagonalLeftToRight == x_in_row) {
    xWins++;
  } else if (diagonalLeftToRight == o_in_row) {
    oWins++;
  }

  // Right to Left Diagonal testing
  string diagonalRightToLeft = "";
  for (int i = 1; i < BOARD_LENGTH + 1; i++) {
    diagonalRightToLeft += boardString.at(i * (BOARD_LENGTH - 1));
  } if (diagonalRightToLeft == x_in_row) {
    xWins++;
  } else if (diagonalRightToLeft == o_in_row) {
    oWins++;
  }

  // winner decided
  if (xWins > 0 && oWins > 0) {
    return BoardState::UnreachableState;
  } else if (oWins > 0 && x_count == o_count + 1) {
    return BoardState::UnreachableState;
  } else if (xWins > 0 && x_count == o_count) {
    return BoardState::UnreachableState;
  } else if (xWins > 0) {
    return BoardState::Xwins;
  } else if (oWins > 0) {
    return BoardState::Owins;
  }
  return BoardState::NoWinner;
}
}  // namespace tictactoe
