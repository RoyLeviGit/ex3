#include "Game.h"
#include "Auxiliaries.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <memory>
using namespace mtm;

bool Game::isGridPointInBounds(GridPoint gridPoint) {
    return (gridPoint.row >=0 && gridPoint.row < matrix.width()
        && gridPoint.col >=0 && gridPoint.col < matrix.height());
}

Game::Game(int height, int width): matrix(Dimensions(height,width)) {
    for (int i = 0 ; i < matrix.height() ; i++) {
        for (int j = 0 ; matrix.width() ; j++) {
            matrix(i,j).gridPoint = GridPoint(i, j);
        }
    }
}

Game::~Game() {}

Game::Game(const Game& other) : matrix(other.matrix) {
}

void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character) {
    if(!isGridPointInBounds(coordinates)){
        throw IllegalCell();
    }
    if(!matrix(coordinates.row, coordinates.col).isCellEmpty()){
        throw CellOccupied();        
    }

    matrix(coordinates.row, coordinates.col).character = character;
}

static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
    units_t health, units_t ammo, units_t range, units_t power) {
    if (health <=0 || ammo < 0 || range < 0 || power < 0) {
        throw Game::IllegalArgument();
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
    moveChracter(matrix(src_coordinates.row, src_coordinates.col),
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
    if(attacker->getAmmoNeededForAttack() 
        > attacker->getAmmo()) {
        throw OutOfAmmo();
        }
    if(!attacker->canAttackTarget(matrix(dst_coordinates.row, dst_coordinates.col).character)){
        throw IllegalTarget();
    }
    attacker->attackTarget(matrix(dst_coordinates.row, dst_coordinates.col).character);

    // take care of explosion zone
    for (int i = 0 ; i < matrix.height() ; i++) {
        for (int j = 0 ; matrix.width() ; j++) {
            if (!(matrix(i,j).gridPoint == dst_coordinates) 
                && GridPoint::distance(matrix(i,j).gridPoint, dst_coordinates) <= attacker->getExplosiveRange()) {
                matrix(i,j).character->takeDamage(attacker->getExplosiveDamage());
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
        for (int j = 0 ; game.matrix.width() ; j++) {
            gameToString += game.matrix(i,j).toString();
        }
    }
    return printGameBoard(os, gameToString.c_str(), gameToString.c_str()+gameToString.length(), game.matrix.width());
}
