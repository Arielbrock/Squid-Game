//
// Created by Nir on 30/11/2021.
//

#ifndef WET1_PLAYERSMANAGER_H
#define WET1_PLAYERSMANAGER_H
#include "AVLTree.h"
#include "Tuple2.h"
#include "PlayerData.h"
#include "Group.h"
#include <assert.h>
#include <stdexcept>


class PlayersManager {
    AVLTree<int, int> levels;
    AVLTree<int, Group> groups;
    AVLTree<int, Group*> non_empty_groups;
    AVLTree<Tuple2<int, int>, PlayerData> players;
    Player* max_player;
public:
    PlayersManager() = default;
    ~PlayersManager() = default;
    PlayersManager(const PlayersManager& p) = default;
    void addPlayer(int player_id, int level, int group_id);
    void removePlayer(int player_id);
    void replaceGroup(int old_group, int new_group);
    void addGroup(int group_id);
    PlayerData& getPlayerDataById(int player_id);
    Group* getGroupById(int group_id);
    bool checkGroupExists(int group_id);
    bool checkPlayerExists(int player_id);
    void getGroupPlayersByLevel(int group_id, int* num_of_players, int** players);
    int* getGroupHighestLevel(int numOfGroups);
    void increaseLevel(int player_id, int level_increase);
    int getAllPlayersSize();
    int getMaxPlayerId();
    AVLTree<int, Group*> getNonEmptyGroups();
    AVLTree<int, Group> getAllGroups();
private:
    void getGroupHighestLevelUtility(const AVLTreeNode<int, Group>*  group, int& numOfGroups, int* players_array, int& counter);
    void addNonEmptyGroup(int group_id, Group *full_group);
};


#endif //WET1_PLAYERSMANAGER_H
