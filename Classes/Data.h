#pragma once

//#import <vector>

using namespace std;

enum SprTag {
	PLAYER,
	SLAVE_TRAIDER,
	CITIZEN,
	WORKER,
	WARRIOR,
	BUILDER,
	CASTLE,
	TOWER,
	WALL,
	MINE
};

// place here consts

const int DELTA_TIME{ 60 };
const int DAY_DURATION{ 1 };
const double SCALE_FACTOR{ 0.5 };


//Z-orders

const int BUILDING_Z_ORDER{ 0 };
const int GROUND_Z_ORDER{ 3 };
const int NPC_Z_ORDER{ 2 };
const int PLAYER_Z_ORDER{ 1 };

// start position

const double GENERAL_Y{ 6 * 16 / SCALE_FACTOR };

const double SLAVE_TRAIDER_START_X{ 12 * 16 / SCALE_FACTOR };
const double PLAYER_START_X{ 6 * 16 / SCALE_FACTOR };


const int CAMERA_OFFSET_Y{ -220 };


//sprites name

const string GROUND_SPR{ "ground.png" };
const string PLAYER_SPR{ "player.png" };
const string SLAVE_TRAIDER_SPR{ "slaveTraider.png" };
const string CITIZEN_SPR{ "citizen.png" };
const string BUILDER_SPR{ "builder.png" };
const string WARRIOR_SPR{ "warrior.png" };
const string WORKER_SPR{ "worker.png" };

// UI elements

const string NEW_GAME_BTN{ "UI/newGameBtn.png" };
const string CONTINUE_BTN{ "UI/continueBtn.png" };
const string SETTINGS_BTN{ "UI/settingsBtn.png" };
const string EXIT_BTN{ "UI/exitBtn.png" };

const string PICK_SPR{ "UI/pickBtn.png" };
const string HUMMER_SPR{ "UI/hummerBtn.png" };
const string BOW_SPR{ "UI/bowBtn.png" };

//UI elements shift position

const double SELECT_SITIZEN_ROLE_Y{ GENERAL_Y + 16 * 4 / SCALE_FACTOR  };

const double SELECT_SITIZEN_ROLE_RIGHT_X{ 16 * 7 / SCALE_FACTOR };
const double SELECT_SITIZEN_ROLE_MIDDLE_X{ 0 };
const double SELECT_SITIZEN_ROLE_LEFT_X{ -(16 * 7 / SCALE_FACTOR) };

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


const int MAX_BUILDING_WIDTH{ 200 };

const int SPACING{ 650 };  // проміжок між будівлями

const int RANDOM_FACTOR{ 400 }; // здвиги вправо або вліво при генерації будівель



//collections 

const vector<int> towerLevelsPrices{ 0,2,3,4,6,8 };
const vector<int> wallLevelsPrices{ 0,2,4,6,8,10 };
const vector<int> castleLevelsPrices{ 0,5,8,10,12,14 };
const vector<int> mineLevelsPrices{ 0,4,6,8,10,14 };

const vector<int> towerTimeBuilding{ 10,15,20,22,25,27 };
const vector<int> wallTimeBuilding{ 12,17,22,25,27,30 };
const vector<int> castleTimeBuilding{ 15,20,25,27,30,34 };
const vector<int> mineTimeBuilding{ 13,18,21,24,28,33 };

//collections of images

const vector<std::string> WALLS{ 
	"buildings/walls/wall0.png",
	"buildings/walls/wall1.png",
	"buildings/walls/wall2.png",
	"buildings/walls/wall3.png",
	"buildings/walls/wall4.png"
};

const vector<std::string> TOWERS{ "buildings/towers/tower0.png","buildings/towers/tower3.png"};
const vector<std::string> CASTLES{ "buildings/castles/castle0.png","buildings/castles/castle1.png"};
const vector<std::string> MINES{ "buildings/mines/mine0.png","buildings/mines/mine1.png"};

//money


const int SLAVE_PRICE{ 4 };
const int SET_ROLE_PRICE{ 1 };
const int PLAYER_START_MONEY{ 100 };

//speed
const int PLAYER_SPEED{ 10 };
const int FRIENDLY_NPC_MOVE_SPEED{ 1 };
