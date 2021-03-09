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
  // Unreachable state testing
  int xCount = 0;
  int oCount = 0;
  string x_In_A_Row = "";
  string o_In_A_Row = "";
  for (int i = 0; i < BOARD_LENGTH; i++) {
    x_In_A_Row += "x";
    o_In_A_Row += "o";
  }


  for (int boardSpot = 0; boardSpot < BOARD_SIZE; boardSpot++) {
    if (boardString.at(boardSpot) == 'x' || boardString.at(boardSpot) == 'X') {
      xCount++;
    }
    if (boardString.at(boardSpot) == 'o' || boardString.at(boardSpot) == 'O') {
      oCount++;
    }
  }
  if (xCount > oCount + 1 || oCount > xCount) {
    return BoardState::UnreachableState;
  }

  // determines winner, if one is above 0, they win, unless both then unreachable state.
  int xWins = 0;
  int oWins = 0;

  // Horizontal testing
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    string print = boardString.substr(BOARD_LENGTH * i, BOARD_LENGTH * (i + 1));
    if (boardString.substr(BOARD_LENGTH * i, BOARD_LENGTH) == x_In_A_Row) {
      xWins++;
    } else if (boardString.substr(BOARD_LENGTH * i, BOARD_LENGTH) == o_In_A_Row) {
      oWins++;
    }
  }

  // Vertical testing
  for (int i = 0; i < BOARD_LENGTH; i++) {
    string vertical = "";
    for (int j = i; j < BOARD_SIZE; j += BOARD_LENGTH) {
      vertical += boardString.at(j);
    }
    if (vertical == x_In_A_Row) {
      xWins++;
    } else if (vertical == o_In_A_Row) {
      oWins++;
    }
  }

  // Left to Right Diagonal testing (this is mostly applicable for boards with m = n = k)
  std::string diagonalLeftToRight = "";
  for (int i = 0; i < BOARD_LENGTH; i++) {
    diagonalLeftToRight += boardString.at(i * (BOARD_LENGTH + 1));
  }
  if (diagonalLeftToRight == x_In_A_Row) {
    xWins++;
  } else if (diagonalLeftToRight == o_In_A_Row) {
    oWins++;
  }

  // Right to Left Diagonal testing
  std::string diagonalRightToLeft = "";
  for (int i = 1; i < BOARD_LENGTH + 1; i++) {
    diagonalRightToLeft += boardString.at(i * (BOARD_LENGTH - 1));
  } if (diagonalRightToLeft == x_In_A_Row) {
    xWins++;
  } else if (diagonalRightToLeft == o_In_A_Row) {
    oWins++;
  }

  // winner decided
  if (xWins > 0 && oWins > 0) {
    return BoardState::UnreachableState;
  } else if (oWins > 0 && xCount == oCount + 1) {
    return BoardState::UnreachableState;
  } else if (xWins > 0 && xCount == oCount) {
    return BoardState::UnreachableState;
  } else if (xWins > 0) {
    return BoardState::Xwins;
  } else if (oWins > 0) {
    return BoardState::Owins;
  }
  return BoardState::NoWinner;
}
}  // namespace tictactoe
