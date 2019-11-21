#pragma once

//#import <vector>

using namespace std;

// place here consts

const int DAY_DURATION{ 1 };
const double SCALE_FACTOR{ 1 };


//Z-orders

const int GROUND_Z_ORDER{ 3 };
const int NPC_Z_ORDER{ 2 };
const int PLAYER_Z_ORDER{ 1 };

//sprites names

const string GROUND{ "ground.png" };
const string PLAYER{ "player.png" };
const string SLAVE_TRAIDER{ "slaveTraider.png" };
const string CITIZEN{ "citizen.png" };

const int SLAVE_TRAIDER_START_X = 12 * 16 / SCALE_FACTOR ;
const int SLAVE_TRAIDER_START_Y = 6 * 16 / SCALE_FACTOR ;

const int PLAYER_START_X = 6 * 16 / SCALE_FACTOR ;
const int PLAYER_START_Y = 6 * 16 / SCALE_FACTOR ;
const int PLAYER_SPEED{ 5 };

const int DELTA_TIME{ 60 };

const vector<int> towerLevelsPrices{ 0,2,3,4,6,8 };
const vector<int> wallLevelsPrices{ 0,2,4,6,8,10 };
const vector<int> castleLevelsPrices{ 0,5,8,10,12,14 };
const vector<int> mineLevelsPrices{ 0,4,6,8,10,14 };

const vector<int> towerTimeBuilding{ 10,15,20,22,25 };
const vector<int> wallTimeBuilding{ 12,17,22,25,27 };
const vector<int> castleTimeBuilding{ 15,20,25,27,30 };
const vector<int> mineTimeBuilding{ 13,18,21,24,28 };

const int SLAVE_PRICE{ 4 };