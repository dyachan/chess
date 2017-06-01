#include "board.h"

Board::Board()
{

	for (size_t l = 0; l < 8; l++){
		// fill empties ...
		for (size_t n = 2; n < 6; n++){
			board[l][n] = empt;
		}
		// pawns ...
		board[l][1] = wPawn;
		board[l][6] = bPawn;
	}
	// towers ...
	board[0][0] = board[7][0] = wTower;
	board[0][7] = board[7][7] = bTower;

	// knights ...
	board[1][0] = board[6][0] = wKnight;
	board[1][7] = board[6][7] = bKnight;

	// bishops ...
	board[2][0] = board[5][0] = wBishop;
	board[2][7] = board[5][7] = bBishop;

	// and others stuffs.
	board[3][0] = wQueen;
	board[3][7] = bQueen;
	board[4][0] = wKing;
	board[4][7] = bKing;
}


Board::~Board(){
}

Board::eBoardStatus Board::getboard(Board::tBoard &retBoard){
	for (size_t l = 0; l < 8; l++)
		for (size_t n = 0; n < 0; n++)
			retBoard[l][n] = board[l][n];
	return status;
}

Board::eMoveResp Board::addMove(Board::sMove move){
	unsigned char ilet = move.iPos.let,
	    					inum = move.iPos.num;
	unsigned char llet = move.lPos.let,
	    					lnum = move.lPos.num;

	// check valid pos
	if(inum > 8 && ilet > 8 && lnum > 8 && llet > 8)
	  return ilegalMove;

	ePiece oldPiece = board[let][lnum];

	if (whiteTurn){
		// check if to position isn't a white piece
		if (board[ilet][inum] < wPawn && board[ilet][inum] > wKing)
			return ilegalMove;

		switch (board[ilet][inum]) {
		case wPawn:
			// one space to forward
			if(lnum == inum+1 && ilet == llet && board[lnum][llet] == empt){
				_doMove(move);
				return legalMove;
			}
			// double movement
			if(inum == 1 && lnum == 3 && ilet == llet && board[2][llet] == board[3][llet] == empt){
				_doMove(move);
				return legalMove;
			}
			// eat
			if(lnum == inum+1 && (llet == ilet+1 || llet == ilet-1) && board[lnum][llet] > wKing){
				_doMove(move);
				return legalMove;
			}
			break;
		case wKnight:
			// check valid movement
			if( (lnum == inum - 1 && llet == ilet + 2) || // up left
			    (lnum == inum + 1 && llet == ilet + 2) || // up right
			    (lnum == inum - 2 && llet == ilet + 1) || // left up
			    (lnum == inum + 2 && llet == ilet + 1) || // right up
					(lnum == inum - 2 && llet == ilet - 1) || // left down
					(lnum == inum + 2 && llet == ilet - 1) || // right down
					(lnum == inum - 1 && llet == ilet - 2) || // down left
					(lnum == inum + 1 && llet == ilet - 2) ){  // down right
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
	board[move.lPos.let][.lPos.num] = board[move.iPos.let][.iPos.num];
	board[move.iPos.let][.iPos.num] = empt;
}

bool Board::_movementPawn(sMove move){
	unsigned char ilet = move.iPos.let,
	    					inum = move.iPos.num;
	unsigned char llet = move.lPos.let,
	    					lnum = move.lPos.num;

	short T = 1; //< 1 when whiteTurn, -1 if not
	if(!whiteTurn)
		T = -1;

	// one space to forward
	if(lnum == inum+T && ilet == llet && board[llet][lnum] == empt)
		return true;

	// double movement
	if(inum == 1 && lnum == 3 && ilet == llet && board[2][llet] == board[3][llet] == empt){
			if(whiteTurn && inum == 1 && lnum == 3 && board[2][llet] == empt && board[3][llet] == empt)
				return true;
			if(!whiteTurn && inum == 6 && lnum == 4 && board[7][llet] == empt && board[4][llet] == empt)
				return true;
	}

	// eat
	if(lnum == inum+T && (llet == ilet+1 || llet == ilet-1) && board[lnum][llet] > wKing){
		if(whiteTurn && board[lnum][llet] >= bPawn && board[lnum][llet] <= bQueen)
			return true;
		if(!whiteTurn && board[lnum][llet] >= wPawn && board[lnum][llet] <= wQueen)
			return true;
	}
	return false;
}

bool Board::_movementKnight(sMove move){
	unsigned char ilet = move.iPos.let,
	    					inum = move.iPos.num;
	unsigned char llet = move.lPos.let,
	    					lnum = move.lPos.num;

	if( (llet == ilet - 1 && lnum == inum + 2) || // up left
			(llet == ilet + 1 && lnum == inum + 2) || // up right
			(llet == ilet - 2 && lnum == inum + 1) || // left up
			(llet == ilet + 2 && lnum == inum + 1) || // right up
			(llet == ilet - 2 && lnum == inum - 1) || // left down
			(llet == ilet + 2 && lnum == inum - 1) || // right down
			(llet == ilet - 1 && lnum == inum - 2) || // down left
			(llet == ilet + 1 && lnum == inum - 2) ){  // down right
		return true;
	}
	return false;
}
