#include "Event.h"

std::vector<User*>* UsersArray::users = new std::vector<User*>();

template<>
Handler<ActivityFactory> Singleton<ActivityFactory>::handler = Handler<ActivityFactory>();
