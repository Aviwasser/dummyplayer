#pragma once

#include "Coordinate.h"
#include <string>
using namespace std;

class IllegalCoordinateException {
	Coordinate c;
public:
	IllegalCoordinateException(Coordinate c): c(c) {}
	Coordinate theCoordinate() const { return c; }
};
