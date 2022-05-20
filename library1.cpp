//
// Created by Nir on 29/11/2021.
//

#include"library1.h"
#include"PlayersManager.h"
#include <exception>

void* Init() {
    PlayersManager *DS;
    try{
        DS = new PlayersManager();
    }
    catch (std::bad_alloc &e) {
        DS = NULL;
    }
    return (void*)DS;
}

StatusType AddGroup(void *DS, int group_id){
    if (DS == nullptr || group_id <= 0){
        return INVALID_INPUT;
    }
    if (static_cast<PlayersManager*>(DS)->checkGroupExists(group_id)){
        return FAILURE;
    }
    try{
        static_cast<PlayersManager*>(DS)->addGroup(group_id);
    }
    catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AddPlayer(void *DS, int player_id, int group_id, int level){
    if (DS == nullptr || group_id <=0 || player_id <= 0 || level < 0){
        return INVALID_INPUT;
    }
    if (static_cast<PlayersManager *>(DS)->checkPlayerExists(player_id)){
        return FAILURE;
    }
    if (!static_cast<PlayersManager *>(DS)->checkGroupExists(group_id)){
        return FAILURE;
    }
    try{
        static_cast<PlayersManager*>(DS)->addPlayer(player_id, level, group_id);
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType RemovePlayer(void *DS, int player_id){
    if (DS == nullptr || player_id <= 0){
        return INVALID_INPUT;
    }
    if (!static_cast<PlayersManager*>(DS)->checkPlayerExists(player_id)){
        return FAILURE;
    }
    static_cast<PlayersManager*>(DS)->removePlayer(player_id);
    return SUCCESS;
}

StatusType ReplaceGroup(void *DS, int old_group_id, int new_group_id){
    if (DS == nullptr || old_group_id <= 0 || new_group_id <= 0 || old_group_id == new_group_id){
        return INVALID_INPUT;
    }
    if (!static_cast<PlayersManager*>(DS)->checkGroupExists(old_group_id) || !static_cast<PlayersManager*>(DS)->checkGroupExists(new_group_id)){
        return FAILURE;
    }
    try{
        static_cast<PlayersManager*>(DS)->replaceGroup(old_group_id, new_group_id);
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetHighestLevel(void *DS, int group_id, int *player_id){
    if (DS == nullptr || player_id == nullptr || group_id == 0){
            return INVALID_INPUT;
    }
    if(group_id > 0){
        if (!(static_cast<PlayersManager*>(DS)->checkGroupExists(group_id))){
            return FAILURE;
        }
        else{
            Group& group = *static_cast<PlayersManager*>(DS)->getGroupById(group_id);
            if (group.getPlayersSize() == 0){
                *player_id = -1;
            }
            else{
                *player_id = group.getHighestLevel()->getId();
            }
        }
    }
    else{  //group_id <0
        if (static_cast<PlayersManager*>(DS)->getAllPlayersSize() == 0){
            *player_id = -1;
        }
        else{
            *player_id = static_cast<PlayersManager*>(DS)->getMaxPlayerId();
        }
    }
    return SUCCESS;
}

StatusType GetAllPlayersByLevel(void *DS, int group_id, int **players, int *players_num){
    if(DS == nullptr || group_id == 0 || players_num == nullptr || players == nullptr){
        return INVALID_INPUT;
    }
    if(group_id > 0 && !(static_cast<PlayersManager*>(DS)->checkGroupExists(group_id))){
        return FAILURE;
    }
    try {
        static_cast<PlayersManager*>(DS)->getGroupPlayersByLevel(group_id, players_num, players);
    }
    catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetGroupsHighestLevel(void *DS, int num_of_groups, int **players){
    if(DS == nullptr || num_of_groups < 1 || players == nullptr){
        return INVALID_INPUT;
    }
    int non_empty_groups = static_cast<PlayersManager*>(DS)->getNonEmptyGroups().getSize();
    if (num_of_groups>non_empty_groups){
        return FAILURE;
    }
    try {
        *players = static_cast<PlayersManager*>(DS)->getGroupHighestLevel(num_of_groups);
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType IncreaseLevel(void *DS, int player_id, int level_increase){
    if (DS == nullptr || player_id <= 0 || level_increase <= 0){
        return INVALID_INPUT;
    }
    if (!static_cast<PlayersManager*>(DS)->checkPlayerExists(player_id)){
        return FAILURE;
    }
    try{
        static_cast<PlayersManager*>(DS)->increaseLevel(player_id, level_increase);
    }
    catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


void Quit(void **DS){
    delete static_cast<PlayersManager*>(*DS);
    *DS = nullptr;
}