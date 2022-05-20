//
// Created by Nir on 01/12/2021.
//

#ifndef WET1_PLAYERDATA_H
#define WET1_PLAYERDATA_H

#include "Player.h"
#include "AVLTreeNode.h"
#include "Tuple2.h"

class PlayerData {
    Player player;
    void* group_of_player;
public:
    PlayerData(const Player& player, void* group_of_player) : player(player), group_of_player(group_of_player) {}
    ~PlayerData() = default;
    PlayerData(const PlayerData& player_data) = default;
    Player* getPlayerPointer();
    void* getGroupsNode();
    void setGroup(void* group);
};


#endif //WET1_PLAYERDATA_H
