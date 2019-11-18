#pragma once

using namespace std;

// place here consts

const int DAY_DURATION{ 1 };



//Z-orders

const int GROUND_Z_ORDER{ 3 };
const int NPC_Z_ORDER{ 2 };
const int PLAYER_Z_ORDER{ 1 };

//sprites names

const string GROUND{ "ground.png" };
const string PLAYER{ "player.png" };
const string SLAVE_TRAIDER{ "slaveTraider.png" };
const string CITIZEN{ "citizen.png" };

const int SLAVE_TRAIDER_START_X{ 12 * 16 };
const int SLAVE_TRAIDER_START_Y{ 6 * 16 };

const int PLAYER_START_X{ 6 * 16 };
const int PLAYER_START_Y{ 6 * 16 };
const int PLAYER_SPEED{ 5 };

const int SLAVE_PRICE{ 4 };