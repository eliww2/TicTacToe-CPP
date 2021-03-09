#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board("xxooo"), std::invalid_argument);
  }

  SECTION("String is too long") {
    REQUIRE_THROWS_AS(Board("xxxo.xo.e1"), std::invalid_argument);
  }

  SECTION("String is empty") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }

}

TEST_CASE("Boards with no winner") {
  SECTION("Full board with no winner") {
    REQUIRE(Board("xxOooXxxo").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Empty board no winner") {
    REQUIRE(Board(".........").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress X moved last") {
    REQUIRE(Board("x.O.Xo...").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress O moved last") {
    REQUIRE(Board("x.O.Xo.o.").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("Unreachable state of board") {
  SECTION("To many X's") {
    REQUIRE(Board("xxo.xOx..").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("To many O's") {
    REQUIRE(Board("xoXoO....").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX == numO when X has won") {
    REQUIRE(Board("xoo.xo..x").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX == numO + 1 when O has won") {
    REQUIRE(Board("xxoxxo..o").EvaluateBoard() == BoardState::UnreachableState);
  }

}

TEST_CASE("Horizontal testing") {
  SECTION("X Wins Horizontally") {
    REQUIRE(Board("xxxoo....").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("O Wins Horizontally") {
    REQUIRE(Board("x.xooo.x.").EvaluateBoard() == BoardState::Owins);

  }

}

TEST_CASE("Vertical testing") {
  SECTION("X Wins Vertical") {
    REQUIRE(Board("xo.xo.x..").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("O Wins Vertical") {
    REQUIRE(Board("xoX.OX.o.").EvaluateBoard() == BoardState::Owins);
  }

}

TEST_CASE("Diagonal testing") {
  SECTION("X Wins Diagonal") {
    REQUIRE(Board("xoO.x...X").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("O Wins Diagonal") {
    REQUIRE(Board("xxoxo.O..").EvaluateBoard() == BoardState::Owins);
  }

}

