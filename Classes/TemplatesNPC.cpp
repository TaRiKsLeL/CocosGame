#include "NPCController.h"
#include "NPCController.cpp"
#include "Builder.h"
#include "Citizen.h"
#include "Warrior.h"
#include "Worker.h"

template class NPCController<Worker>;
template class NPCController<Warrior>;
template class NPCController<Citizen>;
template class NPCController<Builder>;