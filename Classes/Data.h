#pragma once

//#import <vector>

using namespace std;

enum SprTag {
	PLAYER ,
	SLAVE_TRAIDER,
	BUILDING
};

// place here consts

const int DAY_DURATION{ 1 };
const double SCALE_FACTOR{ 0.5 };


//Z-orders
const int BUILDING_Z_ORDER{ 0 };

const int GROUND_Z_ORDER{ 3 };
const int NPC_Z_ORDER{ 2 };
const int PLAYER_Z_ORDER{ 1 };

//sprites name

const string GROUND_SPR{ "ground.png" };
const string PLAYER_SPR{ "player.png" };
const string SLAVE_TRAIDER_SPR{ "slaveTraider.png" };
const string CITIZEN_SPR{ "citizen.png" };

//AMOUNT OF EACH BUILDING

const int WALLS_AMOUNT = 10;
const int TOWERS_AMOUNT = 10;
const int MINES_AMOUNT = 4;

//sprites texture size per picture


const int WALL_WIDTH{ 64 };
const int WALL_HEIGHT{ 120 };

const int CASTLE_WIDTH{ 64 };
const int CASTLE_HEIGHT{ 120 };

const int TOWER_WIDTH{ 64 };
const int TOWER_HEIGHT{ 120 };

const int MINE_WIDTH{ 64 };
const int MINE_HEIGHT{ 120 };

//

const double GENERAL_Y{ 6 * 16 / SCALE_FACTOR };
const int PLAYER_SPEED{ 20 };
const double SLAVE_TRAIDER_START_X{ 12 * 16 / SCALE_FACTOR };

const double PLAYER_START_X{ 6 * 16 / SCALE_FACTOR };

const int DELTA_TIME{ 60 };

const int MAX_BUILDING_WIDTH{ 200 };

const int SPACING{ 750 };  // проміжок між будівлями

const int RANDOM_FACTOR{ 300 }; // здвиги вправо або вліво при генерації будівель

//collections 

const vector<int> towerLevelsPrices{ 0,2,3,4,6,8 };
const vector<int> wallLevelsPrices{ 0,2,4,6,8,10 };
const vector<int> castleLevelsPrices{ 0,5,8,10,12,14 };
const vector<int> mineLevelsPrices{ 0,4,6,8,10,14 };

const vector<int> towerTimeBuilding{ 10,15,20,22,25 };
const vector<int> wallTimeBuilding{ 12,17,22,25,27 };
const vector<int> castleTimeBuilding{ 15,20,25,27,30 };
const vector<int> mineTimeBuilding{ 13,18,21,24,28 };

//collections of images

const vector<std::string> WALLS{ 
	"buildings/walls/wall0.png",
	"buildings/walls/wall1.png",
	"buildings/walls/wall2.png",
	"buildings/walls/wall3.png",
	"buildings/walls/wall4.png"
};

const vector<std::string> TOWERS{ "buildings/towers/tower0.png","buildings/towers/tower1.png"};
const vector<std::string> CASTLES{ "buildings/castles/castle0.png","buildings/castles/castle1.png"};
const vector<std::string> MINES{ "buildings/mines/mine0.png","buildings/mines/mine1.png"};

const int SLAVE_PRICE{ 4 };
const int PLAYER_START_MONEY{ 10 };
