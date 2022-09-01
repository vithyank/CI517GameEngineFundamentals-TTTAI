#include "MyGame.h"
#include <Windows.h>



tttBoard tttboards [3][3];

bool CheckLoss() {
	//Every space on the board is checked to see the Os present
	for (int i = 0; i < 3; i++) {
		if (tttboards[i][0].O && tttboards[i][1].O && tttboards[i][2].O) {
			return true;
		}
	}

	//Every column is checked
	for (int i = 0; i < 3; i++) {
		if (tttboards[0][i].O && tttboards[1][i].O && tttboards[2][i].O) {
			return true;
		}
	}
	//Diagonal combinations are checked
	if (tttboards [0][0].O && tttboards[1][1].O && tttboards[2][2].O) {
		return true;
	}
	else if (tttboards[0][2].O && tttboards[1][1].O && tttboards[2][0].O) {
		return true;
	}
	//If there are no 3 Os in a row, the player doesn't lose
	return false;
}

bool CheckWin() {
	//Every row is checked to see how many Xs are placed
	for (int i = 0; i < 3; i++) {
		if (tttboards [i][0].X && tttboards [i][1].X && tttboards[i][2].X) {
			return true;
		}
	}
	//Every column is checked
	for (int i = 0; i < 3; i++) {
		if (tttboards[0][i].X && tttboards [1][i].X && tttboards[2][i].X) {
			return true;
		}
	}
	//Diagonal combinations are checked
	if (tttboards [0][0].X && tttboards[1][1].X && tttboards[2][2].X) {
		return true;
	}
	else if (tttboards[0][2].X && tttboards[1][1].X && tttboards[2][0].X) {
		return true;
	}
	//If there are no 3 Xs in a row, the player doesn't lose
	return false;
}

bool CheckDraw() {
	//checks and counts the number of empty spaces
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tttboards[i][j].O || tttboards[i][j].X) {
				count++;
			}
		}
	}
	//A Draw is concluded if the player and AI don't have a 3 in a row of either Os and/or Xs
	if (count == 9 && !CheckWin() && !CheckLoss()) {
		return true;
	}
	else {
		return false;
	}
}

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), gameLost(false), gameDraw(false), minimaxOpponent(false), box(5, 5, 30, 30) {
	TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 14);
	gfx->useFont(font);
	gfx->setVerticalSync(true);


	ResourceManager::loadMP3("res/sounds/bg.mp3");
	sfx->playMP3(ResourceManager::getMP3("res/sounds/bg.mp3"), -1);




	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tttboards[i][j].width = 100;
			tttboards[i][j].height = 100;
			tttboards[i][j].O = false;
			tttboards[i][j].X = false;
		}

	}
	tttboards[0][0].posX = 10; tttboards[0][0].posY = 10; tttboards[0][1].posX = 110;
	tttboards[0][1].posY = 10; tttboards[0][2].posX = 210;tttboards[0][2].posY = 10;
	tttboards[1][0].posX = 10;tttboards[1][0].posY = 110;tttboards[1][1].posX = 110;
	tttboards[1][1].posY = 110;tttboards[1][2].posX = 210;tttboards[1][2].posY = 110;
	tttboards[2][0].posX = 10;tttboards[2][0].posY = 210;tttboards[2][1].posX = 110;
	tttboards[2][1].posY = 210;tttboards[2][2].posX = 210;tttboards[2][2].posY = 210;
}

MyGame::~MyGame() {


}



void MyGame::handleKeyEvents() {
	MyEngineSystem EngineSystem;


	if (eventSystem->isPressed(Mouse::BTN_LEFT)) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {

				if (eventSystem->getMousePos().x > tttboards[i][j].posX && eventSystem->getMousePos().x < (tttboards[i][j].posX + 100) && eventSystem->getMousePos().y > tttboards[i][j].posY && eventSystem->getMousePos().y < tttboards[i][j].posY + 100)
				{
				if (!tttboards[i][j].X && !tttboards[i][j].O) {
					tttboards[i][j].X = true;
					if (minimaxOpponent) {
						EngineSystem.aiMovement(tttboards);
					}
					else {
						EngineSystem.createRandomMove(tttboards);
					}
				}


				};
			}
		}
		if (eventSystem->getMousePos().x > 100 && eventSystem->getMousePos().x < 150 && eventSystem->getMousePos().y > 400 && eventSystem->getMousePos().y < 450) {
			std::cout << "A tough opponent! The Minimax algorithm generated opponent! Vithyan_CI517_2022 would be proud!";
			minimaxOpponent = true;
		}
		if (eventSystem->getMousePos().x > 200 && eventSystem->getMousePos().x < 250 && eventSystem->getMousePos().y > 400 && eventSystem->getMousePos().y < 450) {
			std::cout << "You are playing against a randomly generated opponent! Good Luck";
			minimaxOpponent = false;
		}
	}

}



void MyGame::update() {

	if (CheckWin()) {
		gameWon = true;
	}
	if (CheckLoss()) {
		gameLost = true;
	}
	if (CheckDraw()) {
		gameDraw = true;
	}
}



void MyGame::render() {
	MyEngineSystem EngineSystem{};

	gfx->drawText("CI517 2021 :TicTacToe VS AI by Vithyan Karunaharan", 315, 50); 
	gfx->drawText("How To Play: Place 3 Naughts in a Row to Win. Simple Right?", 315, 100);
	gfx->drawText("Click the Blue Button to play against a MiniMax Generated",315,150);
	gfx->drawText("Opponent and click the Green Button to play against", 315, 170);
	gfx->drawText("the Random Generated Opponent!", 315, 190);
	
		
	

	//The Tic-Tac-Toe Board is drawn, followed by the Xs and Os (noughts and crosses)
	gfx->setDrawColor(SDL_COLOR_WHITE);
	

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			gfx->drawRect(tttboards[i][j].posX, tttboards[i][j].posY, tttboards[i][j].height, tttboards[i][j].width);

			if (tttboards[i][j].X == true) {
				gfx->drawLine({ tttboards[i][j].posX, tttboards[i][j].posY }, { (tttboards[i][j].posX + 100), (tttboards[i][j].posY + 100) });
				gfx->drawLine({ (tttboards[i][j].posX + 100), tttboards[i][j].posY }, { (tttboards[i][j].posX), (tttboards[i][j].posY + 100) });

			}
			else if (tttboards[i][j].O == true) {
				gfx->drawCircle({ tttboards[i][j].posX + 50, tttboards[i][j].posY + 50 }, 50);
			}

		}
	}



}





void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_YELLOW);
	
	
	if (gameWon)
		
		gfx->drawText("CONGRATS, YOU WON!", 250, 500); //Win Message displayed (win condition)
	
		
		
		
	if (gameLost)
		
		gfx->drawText("UNLUCKY, YOU LOST!", 250, 500);//Loss Message displayed (loss condition)
		
		
	if (gameDraw) {
		
		gfx->drawText("ITS ALL EVEN!", 250, 500);//Draw Message displayed (draw condition)
		
		
	}
	

	gfx->setDrawColor(SDL_COLOR_BLUE);
	gfx->drawRect(100, 400, 50, 50);
	gfx->fillRect(100, 400, 50, 50);
	gfx->drawText("MINIMAX", 100, 350);

	gfx->setDrawColor(SDL_COLOR_GREEN);
	gfx->drawRect(200, 400, 50, 50);
	gfx->fillRect(200, 400, 50, 50);
	gfx->drawText("RANDOM", 200, 350);
}