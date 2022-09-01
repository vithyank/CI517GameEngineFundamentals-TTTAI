#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"

//These are the squares that make the tictactoe grid
class tttBoard {
public:
	int width;
	int height;
	int posX;
	int posY;
	bool X;
	bool O;
};

class MyEngineSystem {
	friend class XCube2Engine;
private:

public:
	void myFunction();
	void createRandomMove(tttBoard arr[][3]);
	void aiMovement(tttBoard arr[][3]);
};



#endif