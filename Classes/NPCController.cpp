#include "NPCController.h"

//template <class NPC> std::vector<NPC*>NPCController<NPC>::vectorNPCs* = new std::vector<NPC>();

//template <class NPC>NPCController<NPC>::NPCController(){
//	vectorNPCs = new std::vector<NPC>();
//}

template <class NPC> void  NPCController<NPC>::createNPC(Vec2 position) {
	vectorNPCs.push_back(new NPC(position));
}