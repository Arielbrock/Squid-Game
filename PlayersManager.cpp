//
// Created by Nir on 30/11/2021.
//

#include "PlayersManager.h"

void PlayersManager::addNonEmptyGroup(int group_id, Group* full_group){
    non_empty_groups.insert(group_id, full_group);
}

void PlayersManager::addGroup(int group_id) {
    Group group(group_id);
    AVLTreeNode<int, Group>* full_group = nullptr;
    groups.insertAndGet(group_id, group, full_group);
}

bool PlayersManager::checkGroupExists(int group_id) {
    if (groups.findNode(group_id) != nullptr){
        return true;
    }
    return false;
}

bool PlayersManager::checkPlayerExists(int player_id) {
    int level;
    if (levels.findNode(player_id) != nullptr){
        level = levels.findNode(player_id)->getData();
        if (players.findNode(Tuple2<int, int>(level, player_id)) != nullptr){
            return true;
        }
        return false;
    }
    return false;
}

void PlayersManager::addPlayer(int player_id, int level, int group_id) {
    levels.insert(player_id, level);
    Group& group = static_cast<AVLTreeNode<int,Group>*>(groups.findNode(group_id))->changeData();
    AVLTreeNode<Tuple2<int,int>,PlayerData*>& group_player_node = group.addPlayer(player_id, level, nullptr);
    Player player(player_id, level);
    PlayerData player_data(player, &group);
    AVLTreeNode<Tuple2<int, int>, PlayerData>* players_player;
    players.insertAndGet(Tuple2<int,int>(level, player_id), player_data, players_player);
    group_player_node.setData(&(players_player->changeData()));
    group.setMaxPlayer(group.getPlayersTree().getMax().getData()->getPlayerPointer());
    max_player = players.getMax().changeData().getPlayerPointer();
    if (non_empty_groups.findNode(group_id) == nullptr){
        addNonEmptyGroup(group_id, &group);
    }
}

PlayerData &PlayersManager::getPlayerDataById(int player_id) {
    int level = levels.findNode(player_id)->getData();
    return players.findNode(Tuple2<int, int>(level, player_id))->changeData();
}

Group *PlayersManager::getGroupById(int group_id) {
    return &(groups.findNode(group_id)->changeData());
}

void PlayersManager::removePlayer(int player_id) {
    int level = levels.findNode(player_id)->getData();
    AVLTreeNode<Tuple2<int, int>,PlayerData>* node_in_players = players.findNode(Tuple2<int, int>(level, player_id));
    Group* player_group = static_cast<Group*>(node_in_players->changeData().getGroupsNode());
    levels.removeNodeByKey(player_id);
    player_group->removePlayer(player_id, level);
    players.removeNodeByKey(Tuple2<int, int>(level, player_id));
    if (players.getSize()>0){
        max_player = players.getMax().changeData().getPlayerPointer();
    }
    else{
        max_player = nullptr;
    }
    if (player_group->getPlayersSize() == 0){
        non_empty_groups.removeNodeByKey(player_group->getId());
    }
}

PlayerData** mergeSortedPlayers(PlayerData** arr1, PlayerData** arr2, int arr1_size, int arr2_size, Tuple2<int, int>*& key_arr, Group* new_group){
    int total_size = arr1_size+arr2_size;
    key_arr = new Tuple2<int,int>[total_size];
    auto mergedArr = new PlayerData*[total_size];
    int i=0, j=0, k=0;
    for (; j<arr1_size && k<arr2_size; ++i){
        Tuple2<int, int> player1data(arr1[j]->getPlayerPointer()->getLevel(), arr1[j]->getPlayerPointer()->getId());
        Tuple2<int, int> player2data(arr2[k]->getPlayerPointer()->getLevel(), arr2[k]->getPlayerPointer()->getId());
        if (player1data < player2data){
            arr1[j]->setGroup(new_group);
            mergedArr[i] = arr1[j];
            key_arr[i] = player1data;
            j++;
        }
        else{ // player2 > player1 (impossible same player in two different groups)
            arr2[k]->setGroup(new_group);
            mergedArr[i] = arr2[k];
            key_arr[i] = player2data;
            k++;
        }
    }
    for (; j < arr1_size; ++j, ++i){
        arr1[j]->setGroup(new_group);
        mergedArr[i] = arr1[j];
        key_arr[i] = Tuple2<int, int>(arr1[j]->getPlayerPointer()->getLevel(), arr1[j]->getPlayerPointer()->getId());
    }
    for (; k < arr2_size; ++k, ++i) {
        arr2[k]->setGroup(new_group);
        mergedArr[i] =arr2[k];
        key_arr[i] = Tuple2<int, int>(arr2[k]->getPlayerPointer()->getLevel(), arr2[k]->getPlayerPointer()->getId());
    }
    return mergedArr;
}

void PlayersManager::replaceGroup(int old_group_id, int new_group_id){
    Group& old_group = groups.findNode(old_group_id)->changeData();
    Group& new_group = groups.findNode(new_group_id)->changeData();
    PlayerData** in_order_old_group = old_group.getPlayersTree().inOrderTraverse();
    PlayerData** in_order_new_group = new_group.getPlayersTree().inOrderTraverse();
    Tuple2<int, int>* key_arr = nullptr;
    int group1_size = old_group.getPlayersSize();
    int group2_size = new_group.getPlayersSize();
    groups.removeNodeByKey(old_group_id);
    if (non_empty_groups.findNode(old_group_id) != nullptr){
        non_empty_groups.removeNodeByKey(old_group_id);
    }
    groups.removeNodeByKey(new_group_id);
    if (non_empty_groups.findNode(new_group_id) != nullptr){
        non_empty_groups.removeNodeByKey(new_group_id);
    }
    addGroup(new_group_id);
    Group& very_new_group = groups.findNode(new_group_id)->changeData();
    PlayerData** merged_arr = mergeSortedPlayers(in_order_old_group, in_order_new_group, group1_size, group2_size, key_arr, &very_new_group);
    AVLTreeNode<Tuple2<int, int>, PlayerData*>* max_player_node = nullptr;
    AVLTreeNode<Tuple2<int, int>, PlayerData*>* new_group_players_root = AVLTree<Tuple2<int, int>, PlayerData*>::buildTreeFromSortedArr(key_arr, merged_arr, 0, group1_size+group2_size-1, group1_size+group2_size-1, max_player_node);
    Player *max_player_group = max_player_node?max_player_node->getData()->getPlayerPointer(): nullptr;
    very_new_group.setPlayersTree(new_group_players_root, group1_size+group2_size, max_player_group);
    if (very_new_group.getPlayersSize() != 0 && non_empty_groups.findNode(new_group_id) == nullptr){
        addNonEmptyGroup(new_group_id, &very_new_group);
    }
    delete[] key_arr;
    delete[] merged_arr;
    free(in_order_old_group);
    free(in_order_new_group);
}

void PlayersManager::getGroupPlayersByLevel(int group_id, int* num_of_players, int** id_array){
    if(group_id == 0){
        return;
    }
    else if(group_id < 0 ){
        *num_of_players = this->players.getSize();
        *id_array = (int*) malloc(sizeof(int)*(this->players.getSize()));
        if(*num_of_players == 0){
            return;
        }
        PlayerData* players_array = this->players.inOrderReverseTraverse();
        for(int i =0; i < this->players.getSize(); ++i) {
            (*id_array)[i] = players_array[i].getPlayerPointer()->getId();
        }
        free(players_array);
    }
    else{ // group_id > 0
        Group* group = getGroupById(group_id);
        *num_of_players = group->getPlayersSize();
        int size = group->getPlayersSize();
        *id_array = (int*)malloc(sizeof(int)*size);
        if(*num_of_players == 0){
            return;
        }
        Player* players_array = group->getAllPlayersByLevel();
        for(int i = 0; i < group->getPlayersSize(); ++i) {
            (*id_array)[i] = players_array[i].getId();
        }
        free(players_array);
    }
}

int* PlayersManager::getGroupHighestLevel(int num_of_groups){
    Group** limit_groups = non_empty_groups.limitedInOrderTraverse(num_of_groups);
    int* id_array = (int*) malloc(sizeof(int)*num_of_groups);
    for (int i = 0; i < num_of_groups; ++i) {
        Player* group_max_player = ((Group*)limit_groups[i])->getHighestLevel();
        id_array[i] = group_max_player->getId();
    }
    free(limit_groups);
    return id_array;
}

void PlayersManager::increaseLevel(int player_id, int level_increase){
    AVLTreeNode<int, int>* level_node = levels.findNode(player_id);
    int new_level = level_node->getData()+level_increase;
    Tuple2<int, int>old_key(level_node->getData(), player_id);
    Tuple2<int,int>new_key(new_level,player_id);
    level_node->setData(new_level);
    PlayerData player_data = players.findNode(old_key)->changeData();
    player_data.getPlayerPointer()->setLevel(new_level);
    players.removeNodeByKey(old_key);
    AVLTreeNode<Tuple2<int,int>,PlayerData>* players_new_node;
    players.insertAndGet(new_key, player_data, players_new_node);
    Group* group = static_cast<Group*>(player_data.getGroupsNode());
    group->removePlayer(player_id, new_level-level_increase);
    group->addPlayer(player_id, new_level, &(players_new_node->changeData()));
    max_player = players.getMax().changeData().getPlayerPointer();
}

int PlayersManager::getAllPlayersSize() {
    return players.getSize();
}

int PlayersManager::getMaxPlayerId() {
    return max_player->getId();
}

AVLTree<int, Group*> PlayersManager::getNonEmptyGroups() {
    return non_empty_groups;
}

AVLTree<int, Group> PlayersManager::getAllGroups() {
    return groups;
}
