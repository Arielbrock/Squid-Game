//
// Created by ariel on 29/11/2021.
//

#include "Group.h"

int Group::getId() const{
    return this->id;
}

AVLTreeNode<Tuple2<int,int>,PlayerData*>& Group::addPlayer(int player_id, int level, PlayerData* player){
    AVLTreeNode<Tuple2<int,int>, PlayerData*>* player_node = nullptr;
    players.insertAndGet(Tuple2<int, int>(level, player_id), player, player_node);
    max_player = players.getMax().getData()->getPlayerPointer();
    return *player_node;
}

void Group::removePlayer(int player_id, int level){
    players.removeNodeByKey(Tuple2<int,int>(level, player_id));
    if (players.getSize()>0){
        max_player = players.getMax().getData()->getPlayerPointer();
    }
    else{
        max_player = nullptr;
    }
}

Player* Group::getHighestLevel() const{
    return max_player;
}

Player* Group::getAllPlayersByLevel() const{
    PlayerData** playerdata_array = players.inOrderReverseTraverse();
    Player* players_array = (Player*)malloc(players.getSize()* sizeof(Player));
    for (int i = 0; i < players.getSize(); ++i) {
        players_array[i] = *(playerdata_array[i]->getPlayerPointer());
    }
    free(playerdata_array);
    return players_array;
}

Player *Group::getPlayerById(int player_id, int level) {
    Player* p = players.findNode(Tuple2<int, int>(level, player_id))->changeData()->getPlayerPointer();
    return p;
}

int Group::getPlayersSize() const {
    return players.getSize();
}

const AVLTree<Tuple2<int, int>, PlayerData*> &Group::getPlayersTree() {
    return players;
}

AVLTree<Tuple2<int, int>, PlayerData*>* Group::changePlayersTree() {
    return &players;
}

void Group::setPlayersTree(AVLTreeNode<Tuple2<int, int>, PlayerData*>* root, int tree_size, Player *max_player) {
    this->players.setTreeNewMembers(root, tree_size);
    this->max_player = max_player;
}

void Group::setMaxPlayer(Player *new_max_player) {
    this->max_player = new_max_player;
}

