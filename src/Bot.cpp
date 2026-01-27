#include "Bot.hpp"

// Constructeur de Bot
Bot::Bot(std::string name, COLOR color) : Player(name, color)
{
}

// Tour de jeu du Bot
enum Bot::playTurn(){
}


// Prevision des 3 prochains coups
void Bot::nextMove();

// Destructeur de Bot
Bot::~Bot(){};


