#pragma once
#include <iostream>
using namespace std;

#include "IllegalCharException.h"
#include "IllegalCoordinateException.h"
#include "Coordinate.h"


inline void verify(char c) {
	if (c!='.' && c!='X' && c!='O')
		throw IllegalCharException{c};
}


class BoardLocation {
	char& loc;
public:
	BoardLocation(char& loc): loc(loc) {}
	BoardLocation& operator=(char c) {
		verify(c);
		loc = c;
		return *this;
	}

	operator char() const { return loc; }
};

/**
 * Represents a tic-tac-toe board.
 */
class Board {
	char* theChars;
	uint theSize;

	uint offset(uint x, uint y) const {
		return x + y*theSize;
	}

public:
	Board(uint size): theSize(size), theChars(new char[size*size]) {
		operator=('.');
	}

	uint size() const {
		return theSize;
	}

	Board& operator=(char c) {
		verify(c);
		for(uint i=0; i<theSize*theSize; ++i) {
			theChars[i] = '.';
		}
		return *this;
	}

	char operator[] (Coordinate c) const {
		if (c.x>=theSize || c.y>=theSize)
			throw IllegalCoordinateException{c};
		return theChars[offset(c.x,c.y)];
	}

	BoardLocation operator[] (Coordinate c) {
		if (c.x>=theSize || c.y>=theSize)
			throw IllegalCoordinateException{c};
		return BoardLocation(theChars[offset(c.x,c.y)]);
	}

	ostream& output(ostream& out) const {
		for (uint y=0; y<theSize; ++y) {
			for (uint x=0; x<theSize; ++x) {
				out << theChars[offset(x,y)];
			}
			out << endl;
		}
		return out;
	}
};

inline ostream& operator<<(ostream& out, const Board& board) {
	return board.output(out);
}
