//
// Created by ariel on 29/11/2021.
//

#ifndef UNTITLED_GROUP_H
#define UNTITLED_GROUP_H

#include "AVLTree.h"
#include "Tuple2.h"
#include "Player.h"
#include "PlayerData.h"

class Group
{
    int id;
    AVLTree<Tuple2<int, int>, PlayerData*> players; // *PlayerData so can point to big players tree node
    Player* max_player;
public:
    Group(int id): id(id), players(AVLTree<Tuple2<int, int>, PlayerData*>()), max_player(nullptr){}
    Group(int id, Group* full_group): id(id) {}
    ~Group() = default;
    Group(const Group& other_group) = default;
    const AVLTree<Tuple2<int, int>,  PlayerData*>& getPlayersTree();
    AVLTreeNode<Tuple2<int,int>, PlayerData*>& addPlayer(int player_id, int level, PlayerData* player);
    Player* getPlayerById(int player_id, int level);
    Player* getHighestLevel() const;
    Player* getAllPlayersByLevel() const;
    int getId() const;
    int getPlayersSize() const;
    void removePlayer(int player_id, int level);
    void setMaxPlayer(Player* new_max_player);
    void setPlayersTree(AVLTreeNode<Tuple2<int, int>, PlayerData*>* root, int tree_size, Player* max_player);
    AVLTree<Tuple2<int, int>, PlayerData *> *changePlayersTree();
};
#endif //UNTITLED_GROUP_H
