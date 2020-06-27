#include "Game.h"
#include "Auxiliaries.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <iostream>
#include <memory>
using namespace mtm;

bool Game::isGridPointInBounds(GridPoint gridPoint) {
    return (gridPoint.row >=0 && gridPoint.row < matrix.height()
        && gridPoint.col >=0 && gridPoint.col < matrix.width());
}

Game::Game(int height, int width): matrix(Dimensions(height,width)) {
    for (int i = 0 ; i < matrix.height() ; i++) {
        for (int j = 0 ; j < matrix.width() ; j++) {
            matrix(i,j).gridPoint = GridPoint(i, j);
        }
    }
}

Game::~Game() {}

Game::Game(const Game& other) : matrix(other.matrix) {}

void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character) {
    if(!isGridPointInBounds(coordinates)){
        throw IllegalCell();
    }
    if(!matrix(coordinates.row, coordinates.col).isCellEmpty()){
        throw CellOccupied();        
    }

    matrix(coordinates.row, coordinates.col).character = character;
}

std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
    units_t health, units_t ammo, units_t range, units_t power) {
    if (health <=0 || ammo < 0 || range < 0 || power < 0) {
        throw IllegalArgument();
    }
    switch (type) {
    case SOLDIER:
        return std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
    case MEDIC:
        return std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));
    case SNIPER:
        return std::shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
    default:
        break;
    }
}

void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates) {
    if (!isGridPointInBounds(src_coordinates) || !isGridPointInBounds(dst_coordinates)) {
        throw IllegalCell();
    }
    if (matrix(src_coordinates.row, src_coordinates.col).isCellEmpty()) {
        throw CellEmpty();
    }
    if (GridPoint::distance(src_coordinates, dst_coordinates)
        > matrix(src_coordinates.row, src_coordinates.col).character->getMoveDistance()) {
        throw MoveTooFar();
    }
    if (!matrix(dst_coordinates.row, dst_coordinates.col).isCellEmpty()) {
        throw CellOccupied();
    }
    Cell::moveCharacter(matrix(src_coordinates.row, src_coordinates.col),
        matrix(dst_coordinates.row, dst_coordinates.col));
}

void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
    if (!isGridPointInBounds(src_coordinates) || !isGridPointInBounds(dst_coordinates)) {
        throw IllegalCell();
    }
    if (matrix(src_coordinates.row, src_coordinates.col).isCellEmpty()) {
        throw CellEmpty();
    }
    std::shared_ptr<Character> attacker = matrix(src_coordinates.row, src_coordinates.col).character;
    if(!attacker->isTargetInRange(src_coordinates, dst_coordinates)) {
        throw OutOfRange();
    }
    if(attacker->getAmmoNeededForAttack() > attacker->getAmmo()) {
        throw OutOfAmmo();
    }
    if(!attacker->canAttackTarget(matrix(dst_coordinates.row, dst_coordinates.col).character,
        src_coordinates == dst_coordinates)){
        throw IllegalTarget();
    }
    attacker->attackTarget(matrix(dst_coordinates.row, dst_coordinates.col).character);

    // take care of explosion zone and death
    for (int i = 0 ; i < matrix.height() ; i++) {
        for (int j = 0 ; j < matrix.width() ; j++) {
            if (!matrix(i,j).isCellEmpty()) {
                if (!(matrix(i,j).gridPoint == dst_coordinates) 
                    && GridPoint::distance(matrix(i,j).gridPoint, dst_coordinates) <= attacker->getExplosiveRange()) {
                    Cell& cell = matrix(i,j);
                    cell.character->takeDamage(attacker->getExplosiveDamage());
                }
                if (matrix(i,j).character->isDead()) {
                    matrix(i,j).removeCharacter();
                }
            }
        }
    }
}

void Game::reload(const GridPoint & coordinates) {
    if (!isGridPointInBounds(coordinates)) {
        throw IllegalCell();
    }
    if (matrix(coordinates.row, coordinates.col).isCellEmpty()) {
        throw CellEmpty();
    }
    matrix(coordinates.row, coordinates.col).character->reload();
}

std::ostream& mtm::operator<<(std::ostream& os, const Game& game) {
    std::string gameToString = "";
    for (int i = 0 ; i < game.matrix.height() ; i++) {
        for (int j = 0 ; j < game.matrix.width() ; j++) {
            gameToString += game.matrix(i,j).toString();
        }
    }
    return printGameBoard(os, gameToString.c_str(), gameToString.c_str()+gameToString.length(), game.matrix.width());
}

bool Game::isOver(Team* winningTeam) const {
    int countCpp = 0;
    int countPython = 0;

    for (int row = 0; row < matrix.height(); row++) {
        for(int col = 0; col < matrix.width(); col++) {
            if(!matrix(row,col).isCellEmpty()) {
                matrix(row,col).character->getTeam() == CPP ? ++countCpp : ++countPython;
            }
        }
    }
    if ((countCpp == 0 && countPython == 0) ||
        (countCpp > 0 && countPython > 0)) {
        return false;
    }
    
    if (winningTeam != nullptr) {
        countCpp == 0 ? *winningTeam = PYTHON : *winningTeam = CPP;
    }
    return true;
}
