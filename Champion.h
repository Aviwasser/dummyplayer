#include "DummyPlayers.h"

class Champion: public XYPlayer {
	public:
	const string name() const override {return "winner";}	
};
