#include "board.h"

Board::Board()
{

	for (size_t l = 0; l < 8; l++){
		for (size_t n = 2; n < 6; n++){
			board[n][l] = empt;
		}
		board[1][l] = wPawn;
		board[6][l] = bPawn;
	}
	board[0][0] = board[0][7] = wTower;
	board[7][0] = board[7][7] = bTower;

	board[0][1] = board[0][6] = wKnight;
	board[7][1] = board[7][6] = bKnight;

	board[0][2] = board[0][5] = wBishop;
	board[7][2] = board[7][5] = bBishop;

	board[0][3] = wQueen;
	board[7][3] = bQueen;

	board[0][4] = wKing;
	board[7][4] = bKing;
}


Board::~Board()
{
}

Board::eBoardStatus Board::getboard(Board::tBoard &retBoard){
	for (size_t l = 0; l < 8; l++)
		for (size_t n = 0; n < 0; n++)
			retBoard[n][l] = board[n][l];
	return status;
}

Board::eMoveResp Board::addMove(Board::sMove move){
	int flet = move.fPos.let,
	    fnum = move.fPos.num;
	int tlet = move.tPos.let,
	    tnum = move.tPos.num;

	// check valid pos
	if(fnum > 8 && fnum < 0 &&
	   flet > 8 && flet < 0 &&
	   tnum > 8 && tnum  < 0 &&
	   tlet > 8 && tlet < 0)
	    return ilegalMove;

	oldPiece = board[tnum][tlet];

	if (whiteTurn){
		// check if to position isn't a white piece
		if (board[fnum][flet] < wPawn && board[fnum][flet] > wKing)
			return ilegalMove;

		switch (board[fnum][flet]) {
		case wPawn:
			// one space to forward
			if(tnum == fnum+1 && flet == tlet && board[tnum][tlet] == empt){
				_doMove(move);
				return legalMove;
			}
			// double movement
			if(fnum == 1 && tnum == 3 && flet == tlet && board[2][tlet] == board[3][tlet] == empt){
				_doMove(move);
				return legalMove;
			}
			// eat
			if(tnum == fnum+1 && (tlet == flet+1 || tlet == flet-1) && board[tnum][tlet] > wKing){
				_doMove(move);
				return legalMove;
			}
			break;
		case wKnight:
			// check valid movement
			if( (tnum == fnum - 1 && tlet == flet + 2) || // up left
			    (tnum == fnum + 1 && tlet == flet + 2) || // up right
			    (tnum == fnum - 2 && tlet == flet + 1) || // left up
			    (tnum == fnum + 2 && tlet == flet + 1) || // right up
					(tnum == fnum - 2 && tlet == flet - 1) || // left down
					(tnum == fnum + 2 && tlet == flet - 1) || // right down
					(tnum == fnum - 1 && tlet == flet - 2) || // down left
					(tnum == fnum + 1 && tlet == flet - 2) ){  // down right
				_doMove(move);
				return legalMove;
			}
			break;
		case wBishop:
			break;
		case wTower:
			break;
		case wQueen:
			break;
		case wKing:
			break;
		}
	}
	return ilegalMove
}

void Board::_doMove(sMove move){
	board[move.tPos.let][.tPos.num] = board[move.fPos.let][.fPos.num];
	board[move.fPos.let][.fPos.num] = empt;
}
