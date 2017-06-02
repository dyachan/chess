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

	// check valid pieces
	if(board[llet][lnum] == empt)
		return ilegalMove;
	if(whiteTurn && board[ilet][inum] >= bPawn && board[ilet][inum] <= bKing)
	  return ilegalMove;
	if(!whiteTurn && board[ilet][inum] >= wPawn && board[ilet][inum] <= wKing)
	  return ilegalMove;

	// check legal capture
	if(whiteTurn && board[llet][lnum] >= wPawn && board[llet][lnum] <= wKing)
	  return ilegalMove;
	if(!whiteTurn && board[llet][lnum] >= bPawn && board[llet][lnum] <= bKing)
	  return ilegalMove;

	// TODO:
	// check movement.
	// check if current king is in check.
	// check if have do check or mate to other king.
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

bool Board::_movementBishop(sMove move){
	unsigned char ilet = move.iPos.let,
	    					inum = move.iPos.num;
	unsigned char llet = move.lPos.let,
	    					lnum = move.lPos.num;


}

bool Board::_movementRook(sMove move){
	unsigned char ilet = move.iPos.let,
	    					inum = move.iPos.num;
	unsigned char llet = move.lPos.let,
	    					lnum = move.lPos.num;

  if(ilet != llet && inum == lnum){ // horizontal movement
		if(ilet < llet)
		  for(short l = ilet+1; l<llet; i++)
			  if(board[l][inum] != empt)
					return false;
		else
			for(short l = llet+1; l<ilet; i++)
				if(board[l][inum] != empt)
					return false;

		return true;
	}
	if(ilet == llet && inum != lnum){ // vertical movement
		if(inum < lnum)
		  for(short n = inum+1; l<lnum; i++)
			  if(board[ilet][n] != empt)
					return false;
		else
			for(short l = lnum+1; l<inum; i++)
				if(board[ilet][n] != empt)
					return false;

		return true;
	}
}
