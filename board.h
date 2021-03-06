#pragma once
#include <array>

class Board
{
public:

  /** ePiece represent one square in board.
  */
  enum ePiece : char {
    empt = 0,
    wPawn, // white pieces
    wKnight,
    wBishop,
    wRook,
    wQueen,
    wKing,
    bPawn, // black pieces
    bKnight,
    bBishop,
    bRook,
    bQueen,
    bKing
  };

  /** eMoveResp is a posible response of server to a player when do one move.
  */
  enum eMoveResp: char{
    notTurn = 0,
    legalMove,
    ilegalMove,
  };

  /** Status that can have a match in relation of last move.
  */
  enum eBoardStatus :char{
    normalMove = 0,
    checkMove,
    mateMove
  };

  /** tBoard is an array 8x8 of ePiece
  * CONVENTION: tBoard[Letter][number]
  */
  typedef std::array < std::array<ePiece, 8>, 8 > tBoard;

  /** A position is a letter [A;H] and a number [1;8]
  */
  struct sPos{
    unsigned char let, num;
  };

  /** A move is an Initial position and a Last position.
  */
  struct sMove{
    sPos iPos;
    sPos lPos;
  };

private:
public:
  /** constructor */
  Board();
  /** Destructor */
  ~Board();

  /** Get status of match
  * @param[out] retBoard Mem space where copy actual board.
  */
  eBoardStatus getboard(tBoard &retBoard);

  /** Play a move */
  eMoveResp addMove(sMove move);

private:
  // https://isocpp.org/wiki/faq/pointers-to-members
  typedef bool (*_movementPtr)(tBoard &board, sMove move);

  tBoard board; //< board where play
  eBoardStatus status;	//< actual status of match
  bool whiteTurn; //< true if white must play, false if black must play

  /** do move in board */
  inline void _doMove(sMove move);

  bool _movementPawn(tBoard &board, sMove move);
  bool _movementKnight(tBoard &board, sMove move);
  bool _movementBishop(tBoard &board, sMove move);
  bool _movementRook(tBoard &board, sMove move);
  bool _movementQueen(tBoard &board, sMove move);
  bool _movementKing(tBoard &board, sMove move);
};
