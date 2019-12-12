#pragma once

//#import <vector>

using namespace std;

USING_NS_CC;

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

const int TAG_COUNT = 9;

enum Direction {
	LEFT = -1,
	RIGHT,
	ELSE
};
// place here consts


// bitmaps

const int PLAYER_CATEGORY_BM		{ 0b1 };

const int BUILDER_CATEGORY_BM		{ 0b10 };
const int WARRIOR_CATEGORY_BM		{ 0b100 };
const int WORKER_CATEGORY_BM		{ 0b1000 };
const int CITIZEN_CATEGORY_BM		{ 0b10000 };

const int SLAVE_TRAIDER_CATEGORY_BM	{ 0b100000 };
const int ENEMY_CATEGORY_BM			{ 0b1000000 };

const int WALL_CATEGORY_BM			{ 0b10000000 };
const int TOWER_CATEGORY_BM			{ 0b100000000 };
const int MINE_CATEGORY_BM			{ 0b1000000000 };

const int SHOOTER_CATEGORY_BM		{ 0b10000000000 };
const int ARROW_CATEGORY_BM			{ 0b100000000000 };



const int PLAYER_COLLIDE_BM			{ 0b001111111111 };

const int BUILDER_COLLIDE_BM		{ PLAYER_CATEGORY_BM | TOWER_CATEGORY_BM | MINE_CATEGORY_BM | WALL_CATEGORY_BM | ENEMY_CATEGORY_BM };
const int WORKER_COLLIDE_BM			{ PLAYER_CATEGORY_BM | MINE_CATEGORY_BM  | ENEMY_CATEGORY_BM };
const int WARRIOR_COLLIDE_BM		{ PLAYER_CATEGORY_BM | TOWER_CATEGORY_BM | ENEMY_CATEGORY_BM };
const int CITIZEN_COLLIDE_BM		{ PLAYER_CATEGORY_BM | ENEMY_CATEGORY_BM };

const int SLAVE_TRAIDER_COLLIDE_BM	{ PLAYER_CATEGORY_BM };
const int ENEMY_COLLIDE_BM			{ PLAYER_CATEGORY_BM | BUILDER_CATEGORY_BM | WARRIOR_CATEGORY_BM | WORKER_CATEGORY_BM |
										WALL_CATEGORY_BM | SHOOTER_CATEGORY_BM | ARROW_CATEGORY_BM};


const int WALL_COLLIDE_BM			{ PLAYER_CATEGORY_BM | BUILDER_CATEGORY_BM | ENEMY_CATEGORY_BM };
const int TOWER_COLLIDE_BM			{ PLAYER_CATEGORY_BM | BUILDER_CATEGORY_BM | WARRIOR_CATEGORY_BM };
const int MINE_COLLIDE_BM			{ PLAYER_CATEGORY_BM | BUILDER_CATEGORY_BM | WORKER_CATEGORY_BM };

const int SHOOTER_COLLIDE_BM		{ ENEMY_CATEGORY_BM };
const int ARROW_COLLIDE_BM			{ ENEMY_CATEGORY_BM };



const int DELTA_TIME{ 60 };
const int DAY_DURATION{ 120 };
const int SLAVE_TRAIDER_APPERANCE{ DAY_DURATION / 8 };
const int SLAVE_TRAIDER_DISAPPERANCE{ (DAY_DURATION / 8) * 3 };


const double SCALE_FACTOR{ 0.5 };

//UI
//-----coin-----
const std::string COINS_AMOUNT_FONT{ "fonts/PixelFont.ttf" };
const int LABEL_SCALE{ 4 };
const int COINS_LABEL_SIZE{ 70* LABEL_SCALE };

const int LABEL_X_SPACE_FROM_PLAYER{ 850 };
const int LABEL_Y_SPACE_FROM_PLAYER{ 720 };

const float COIN_SCALE_FACTOR{ 1.0f / SCALE_FACTOR };

//----heart-----

const float HEART_SCALE_FACTOR{ 1.0f / SCALE_FACTOR };

//-----paralax------

const int BACKGROUND_Z_ORDER{ -5 };
const int DISTANCE_TO_ENDING_OF_SCREEN{ 600 };
const string SKY_SPR{ "Environment/Background/sky.png" };
const string NIGHT_SKY_SPR{ "Environment/Background/night-sky.png" };
const string LAYER_MOUNTAINS_SPR{ "Environment/Background/far-mountains1.png" };
const string LAYER_TREES_SPR{ "Environment/Background/trees1.png" };
const string LAYER_TREES_BACK_SPR{ "Environment/Background/treesBack.png" };
const string LAYER_FAR_LAND_SPR{ "Environment/Background/far-grounds1.png" };

const float LAYER_FIRST_SPEED{ 0.1 };
const float LAYER_SECOND_SPEED{ 0.2 };
const float LAYER_TREES_SPEED{ 0.8 };
const float LAYER_TREES_BACK_SPEED{ 0.7 };
const float LAYER_SECOND_SPASING{ 500 };

const int APPROX_CLOUDS_AMOUNT{ 200 };
const float CLOUD_SIZE_RAND_FACTOR{ 0.5 };
const vector<std::string> CLOUDS{
	"Environment/Background/cloud.png",
	"Environment/Background/cloud2.png",
	"Environment/Background/cloud3.png",
	"Environment/Background/cloud4.png",
	"Environment/Background/cloud5.png"
};

//Parallax offsets
const string SUN_SPR{ "Environment/Background/sun.png" };
const string CLOUDS_SPR{ "Environment/Background/clouds.png" };
const int CLOUDS_SPEED{ 5 };
const int CLOUDS_OFFSET_Y{ 300 };

const int BACK_TREES_BACK_OFFSET{ 0 };
const int BACK_TREES_OFFSET{ 0 };
const int BACK_LAYER_FAR_LAND_OFFSET{ 212 };
const int BACK_LAYER_MOUNTAINS_OFFSET{ 128 };

// ANIMATION


//-----coin-----
const std::string COIN_FRAMES{ "UI/coins_frames.png" };
const int COIN_IMAGES_AMOUNT{ 8 };
const int COIN_IMAGE_SIZE{ static_cast<int>(16 / SCALE_FACTOR)};
const float COIN_TIME_PER_FRAME{ 0.5f };

//----heart-----

const std::string FULL_HEART_FRAMES{ "UI/full_frames.png" };
const std::string EMPTY_HEART_FRAMES{ "UI/empty_frames.png" };
const int HEART_IMAGES_AMOUNT{ 4 };
const int HEART_IMAGE_SIZE{ static_cast<int>(32 / SCALE_FACTOR) };
const float HEART_TIME_PER_FRAME{ 0.5f };

//----Player Run----
const std::string PLAYER_RUN_FRAMES{ "characters/player-run.png" };
const std::string PLAYER_RUN_IMAGE{ "characters/player-run-image.png" };
const int PLAYER_RUN_IMAGES_AMOUNT{6};
const int PLAYER_RUN_IMAGE_WIDTH{ static_cast<int>(125 / SCALE_FACTOR) };
const int PLAYER_RUN_IMAGE_HEIGHT{ static_cast<int>(96 / SCALE_FACTOR) };
const float PLAYER_RUN_TIME_PER_FRAME{ 0.1f };

//----Player Idle----
const std::string PLAYER_IDLE_FRAMES{ "characters/player-idle.png" };
const int PLAYER_IDLE_IMAGES_AMOUNT{ 2 };
const int PLAYER_IDLE_IMAGE_WIDTH{ static_cast<int>(125 / SCALE_FACTOR) };
const int PLAYER_IDLE_IMAGE_HEIGHT{ static_cast<int>(96 / SCALE_FACTOR) };
const float PLAYER_IDLE_TIME_PER_FRAME{ 0.5f };

//----Builder Walk----
const std::string BUILDER_WORK_FRAMES{ "characters/nps/builder-work.png" };
const int BUILDER_WORK_IMAGES_AMOUNT{ 4 };
const int BUILDER_WORK_IMAGE_WIDTH{ static_cast<int>(39 / SCALE_FACTOR) };
const int BUILDER_WORK_IMAGE_HEIGHT{ static_cast<int>(64 / SCALE_FACTOR) };
const float BUILDER_WORK_TIME_PER_FRAME{ 0.2f };

//----Builder Walk----
const std::string BUILDER_WALK_FRAMES{ "characters/nps/builder-walk.png" };
const int BUILDER_WALK_IMAGES_AMOUNT{ 4 };
const int BUILDER_WALK_IMAGE_WIDTH{ static_cast<int>(39 / SCALE_FACTOR) };
const int BUILDER_WALK_IMAGE_HEIGHT{ static_cast<int>(64 / SCALE_FACTOR) };
const float BUILDER_WALK_TIME_PER_FRAME{ 0.2f };

//----Worker Walk----
const std::string WORKER_WALK_FRAMES{ "characters/nps/worker-walk.png" };
const int WORKER_WALK_IMAGES_AMOUNT{ 4 };
const int WORKER_WALK_IMAGE_WIDTH{ static_cast<int>(39 / SCALE_FACTOR) };
const int WORKER_WALK_IMAGE_HEIGHT{ static_cast<int>(64 / SCALE_FACTOR) };
const float WORKER_WALK_TIME_PER_FRAME{ 0.2f };

//----Builder Walk----
const std::string WARRIOR_WALK_FRAMES{ "characters/nps/warrior-walk.png" };
const int WARRIOR_WALK_IMAGES_AMOUNT{ 4 };
const int WARRIOR_WALK_IMAGE_WIDTH{ static_cast<int>(39 / SCALE_FACTOR) };
const int WARRIOR_WALK_IMAGE_HEIGHT{ static_cast<int>(64 / SCALE_FACTOR) };
const float WARRIOR_WALK_TIME_PER_FRAME{ 0.2f };

//----CITIZEN Walk----
const std::string CITIZEN_WALK_FRAMES{ "characters/nps/citizen-walk.png" };
const int CITIZEN_WALK_IMAGES_AMOUNT{ 4 };
const int CITIZEN_WALK_IMAGE_WIDTH{ static_cast<int>(39 / SCALE_FACTOR) };
const int CITIZEN_WALK_IMAGE_HEIGHT{ static_cast<int>(64 / SCALE_FACTOR) };
const float CITIZEN_WALK_TIME_PER_FRAME{ 0.2f };

//----Ghost Enemy----
const std::string GHOST_ENEMY_FRAMES{ "characters/nps/ghost-enemy.png" };
const int GHOST_ENEMY_IMAGES_AMOUNT{ 9 };
const int GHOST_ENEMY_IMAGE_WIDTH{ static_cast<int>(48 / SCALE_FACTOR) };
const int GHOST_ENEMY_IMAGE_HEIGHT{ static_cast<int>(96 / SCALE_FACTOR) };
const float GHOST_ENEMY_TIME_PER_FRAME{ 0.2f };

//Z-orders
const int FENCE_Z_ORDER{ -3 };
const int TREE_Z_ORDER{ -2 };
const int WARRIOR_ON_TOWER_Z_ORDER{ -1 };
const int BUILDING_Z_ORDER{ 0 };
const int NPC_Z_ORDER{ 1 };
const int PLAYER_Z_ORDER{ 2 };
const int ARROW_Z_ORDER{ 3 };
const int GROUND_Z_ORDER{ 4 };
const int GAMEOVER_Z_ORDER{ 5 };

const int SKY_Z_ORDER{ -7 };
const int CLOUDS_Z_ORDER{ -5 };
const int BACK_TREES_BACK_Z_ORDER{ -1 };
const int BACK_TREES_Z_ORDER{ -2 };
const int BACK_LAYER_FAR_LAND_Z_ORDER{ -3 };
const int BACK_LAYER_MOUNTAINS_Z_ORDER{ -4 };
const int BACK_LAYER_SUN_Z_ORDER{ -6 };


// start position

const double GENERAL_Y{ 6 * 16 / SCALE_FACTOR };

const double SLAVE_TRAIDER_START_X{ 320 * 16 / SCALE_FACTOR };
const double PLAYER_START_X{ 200 * 16 / SCALE_FACTOR };


const int CAMERA_OFFSET_Y{ -300 };
const int CUST_OFFSET{ 50 };



//sprites name

const string GROUND_SPR{ "kalush_map.png" };
const string PLAYER_SPR{ "player.png" };
const string SLAVE_TRAIDER_SPR{ "slaveTraider.png" };
const string CITIZEN_SPR{ "citizen.png" };
const string BUILDER_SPR{ "builder.png" };
const string WARRIOR_SPR{ "warrior.png" };
const string WORKER_SPR{ "worker.png" };
const string FENCE_SPR{ "Environment/fence2.png" };
const string ENEMY_SPR{ "enemy.png" };
const string ARROW_SPR{ "arrow.png" };
const string NPS_BASE_SPR{ "characters/nps/nps-base-sprite.png" };

// UI elements

const string NEW_GAME_BTN{ "UI/newGameBtn.png" };
const string CONTINUE_BTN{ "UI/continueBtn.png" };
const string SETTINGS_BTN{ "UI/settingsBtn.png" };
const string EXIT_BTN{ "UI/exitBtn.png" };

const string PICK_SPR{ "UI/pickBtn.png" };
const string HUMMER_SPR{ "UI/hummerBtn.png" };
const string BOW_SPR{ "UI/bowBtn.png" };

const string BACKGROUND_SPR{ "UI/background.png" };
const string GAME_OVER_SPR{ "UI/game_over2.png" };

const string MARK_ICO_SPR{ "UI/mark.png" };
const string HUMMER_ICO_SPR{ "UI/hummer.png" };
const string SELECTOR_ICO_SPR{ "UI/selector.png" };

const string GAME_OVER_BACK_SPR{ "UI/game_over_back.png" };
const string VICTORY_SPR{ "UI/victory.png" };

const int GAME_OVER_BACK_OPACITY{ 40 };

//UI elements shift position

const double SELECT_SITIZEN_ROLE_Y{ GENERAL_Y + 16 * 4 / SCALE_FACTOR  };

const double SELECT_SITIZEN_ROLE_RIGHT_X{ 16 * 7 / SCALE_FACTOR };
const double SELECT_SITIZEN_ROLE_MIDDLE_X{ 0 };
const double SELECT_SITIZEN_ROLE_LEFT_X{ -(16 * 7 / SCALE_FACTOR) };

const double MARKS_Y_SHIFT{ 64 / SCALE_FACTOR };
const double SELECTOR_Y_SHIFT{ MARKS_Y_SHIFT / 2 };
const double SUN_Y_SHIFT{ 128 / SCALE_FACTOR };

//AMOUNT OF EACH BUILDING

const int WALLS_AMOUNT = 10;
const int TOWERS_AMOUNT = 5;
const int MINES_AMOUNT = 10;

//TREES

const int TREES_AMOUNT{ 50 };

//sprites texture size per picture


const int MAX_BUILDING_WIDTH{ 200 };

const int SPACING{ 650 };  // проміжок між будівлями

const int RANDOM_FACTOR{ 400 }; // здвиги вправо або вліво при генерації будівель



//collections 

const vector<int> towerLevelsPrices{ 0,3,3,4,6,8 };
const vector<int> wallLevelsPrices{ 0,3,4,6,8,10 };
const vector<int> castleLevelsPrices{ 0,5,8,10,12,14 };
const vector<int> mineLevelsPrices{ 0,4,6,8,10,14 };

const vector<int> towerTimeBuilding{ 10,15,20,22,25,27 };
const vector<int> wallTimeBuilding{ 12,17,22,25,27,30 };
const vector<int> castleTimeBuilding{ 15,20,25,27,30,34 };
const vector<int> mineTimeBuilding{ 13,18,21,24,28,33 };

const vector<int> towerMaxWarriors{ 0,1,1,2,3 };

const vector<vector<Vec2>> towerSetWariorShift{ 
	{Vec2(0, 0)},
	{Vec2(0, 80 / SCALE_FACTOR)},
	{Vec2(0, 110 / SCALE_FACTOR)},
	{Vec2(-30 / SCALE_FACTOR, 100 / SCALE_FACTOR), Vec2(30 / SCALE_FACTOR, 100 / SCALE_FACTOR)},
	{Vec2(-40 / SCALE_FACTOR, 120 / SCALE_FACTOR), Vec2(0, 120 / SCALE_FACTOR), Vec2(40 / SCALE_FACTOR, 120 / SCALE_FACTOR)},
};

//collections of images

const vector<std::string> WALLS{ 
	"buildings/walls/wall0.png",
	"buildings/walls/wall1.png",
	"buildings/walls/wall2.png",
	"buildings/walls/wall3.png",
	"buildings/walls/wall4.png"
};

const vector<std::string> TOWERS{
	"buildings/towers/tower0.png",
	"buildings/towers/tower1.png",
	"buildings/towers/tower2.png",
	"buildings/towers/tower3.png",
	"buildings/towers/tower4.png"
};
const vector<std::string> CASTLES{ "buildings/castles/castle0.png"};
const vector<std::string> MINES{ "buildings/mines/mine0.png","buildings/mines/mine1.png"};

const vector<std::string> TREES{ "Environment/tree1.png","Environment/tree2.png","Environment/tree3.png",
"Environment/tree4.png","Environment/tree5.png","Environment/tree6.png",
"Environment/plant1.png","Environment/plant2.png",
"Environment/bush1.png","Environment/grass1.png","Environment/stick1.png" };


//money

const int SLAVE_PRICE{ 4 };
const int NPC_RERIVE{ 2 };
const int SET_ROLE_PRICE{ 1 };
const int PLAYER_START_MONEY{ 200 };
const int PLAYER_MAX_HEALTH{ 10 };

//speed
const int PLAYER_SPEED{ 10 };
const int FRIENDLY_NPC_MOVE_SPEED{ 3 };
const int DEFAULT_NPC_MOVE_SPEED{ 1 };

const int ENEMY_MOVE_SPEED_MIN{ 3 };
const int ENEMY_MOVE_SPEED_MAX{ 5 };
const int ENEMY_RAND_DIVISION{ 10 };

//HP
const int PLAYER_HP{ 3 };
const int ENEMY_HP{ 1 };
const vector<int> WALL_HP{ 0,10,20,30,40,50 };


//MINE CAPACITY

const int MAX_MINE_CAPACITY{ 3 };

//SALARY

const int COINS_PER_WORKER{ 27 };
const int SALARY_MOMENT{ DAY_DURATION/3 };


//attack power
const int FRIENDLY_ATTACK{ 1 };
const int ENEMY_ATTACK{ 1 };

//enemy jmp parameters
const int ENEMY_JMP_DURATION{ 1 };
const double ENEMY_JMP_LENGTH{ 256 / SCALE_FACTOR };
const double ENEMY_JMP_HEIGTH{ 128 / SCALE_FACTOR};
const int ENEMY_JMP_QUANTITY{ 1 };

// enemy lastWave per second

const int ENEMY_LAST_WAVE_QUANTITY_PER_SEC{ 3 };

//shoot range && arrow

const double WARRIOR_SHOOT_WIGTH{ 512 / SCALE_FACTOR };
const double WARRIOR_SHOOT_HEIGTH{ 256 / SCALE_FACTOR };
const double ARROW_RELATIVE_HEIGTH{ 0.5 };
const int ARROW_FLY_DURATION{ 1 };
const int ARROW_REMOVE_DELAY{ ARROW_FLY_DURATION + 3 };
const int ARROW_MISS_X{ static_cast<int>(48 / SCALE_FACTOR) };

// warriors 

const int WALL_DIAPASON_WARRIORS_STAND{ static_cast<int>(64 / SCALE_FACTOR) };
const int WALL_DISTANCE_TO_WARRIORS{ static_cast<int>(64 / SCALE_FACTOR) };

// SLAVE TRAIDER SLAVES AMOUNT
const int SLAVE_AMMOUNT_PER_DAY{ 6 };
