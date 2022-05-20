//
// Created by Nir on 01/12/2021.
//

#include "PlayerData.h"

Player* PlayerData::getPlayerPointer(){
    return &player;
}

void *PlayerData::getGroupsNode(){
    return group_of_player;
}

void PlayerData::setGroup(void *group) {
    group_of_player = group;
}
