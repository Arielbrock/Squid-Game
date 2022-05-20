//
// Created by Nir on 29/11/2021.
//

#include "Player.h"

void Player::setLevel(int level){
    this->level = level;
}

int Player::getId() {
    return id;
}

int Player::getLevel() {
    return level;
}

void Player::increaseLevel(int how_much_to_increase) {
    if (how_much_to_increase>0){
        level += how_much_to_increase;
    }
}
