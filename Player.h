//
// Created by Nir on 29/11/2021.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H


class Player {
    int id;
    int level;
public:
    Player(int id, int level): id(id), level(level) {};
    ~Player() = default;
    Player(const Player& p) = default;
    Player& operator=(const Player& player2) = default;
    int getId();
    int getLevel();
    void increaseLevel(int how_much_to_increase);
    void setLevel(int level);

};


#endif //WET1_PLAYER_H
