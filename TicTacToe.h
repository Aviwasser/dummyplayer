#pragma once
#include <iostream>
using namespace std;

#include "Board.h"
#include "Player.h"
#include "Coordinate.h"


class TicTacToe {
	Board _board;
	uint _maxSteps;
	Player* _winner;

	/**
	 * Return true if row y is full with char c.
	 */
	bool fullRow(uint y, char c) {
		for (uint x=0; x<_board.size(); ++x) {
			if (_board[{y,x}]!=c)
				return false;
		}
		return true;
	}

	/**
	 * Return true if row y is full with char c.
	 */
	bool fullCol(uint x, char c) {
		for (uint y=0; y<_board.size(); ++y) {
			if (_board[{y,x}]!=c)
				return false;
		}
		return true;
	}

	bool isWinner(char c) {
		// Check winner in cols:
		for (uint x=0; x<_board.size(); ++x) {
			if (fullCol(x,c)) {
				return true;
			}
		}

		// Check winner in rows:
		for (uint y=0; y<_board.size(); ++y) {
			if (fullRow(y,c)) {
				return true;
			}
		}

		return false;
	}

	void playAndVerify(Player& currentPlayer, Player& otherPlayer) {
		Coordinate move{0,0};
		try {
			Board boardCopy = _board;
			move = currentPlayer.play(boardCopy);
		} catch (...) {
			_winner = &otherPlayer;
		}

		if (_board[move]=='.') {
			_board[move] = currentPlayer.getChar();
		} else { // illegal move - other player wins
			_winner = &otherPlayer;
		}

		if (isWinner(currentPlayer.getChar())) {
			_winner = &currentPlayer;
		}
	}

	
public:
	TicTacToe(uint size): 
		_board(size), 
		_maxSteps(size*size),
		_winner(nullptr) {}

	void play(Player& xPlayer, Player& oPlayer) {
		_winner = nullptr;
		xPlayer.setChar('X');
		oPlayer.setChar('O');
		_board = '.';  // initialize board to empty
		for (uint i=0; i<_maxSteps; ++i) {
			playAndVerify(xPlayer, oPlayer);
			if (_winner) break;
			playAndVerify(oPlayer, xPlayer);
			if (_winner) break;
		}
	}

	void printResults() const {
		cout << "And the winner is " << winner().name() << ", playing as " << winner().getChar() << "!" << endl;
		cout << "The final board is " << endl << board() << endl;
	}

	const Board& board() const { 
		return _board; 
	}

	const Player& winner() const {
		return *_winner;
	}
};
