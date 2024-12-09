#include "Player.h"
#include <algorithm>

// Base abstract class
Player::Player()
{
    playerChar = ' ';

    moved = false;
}

bool Player::getMoved() const
{
    return moved;
}

char Player::getPlayerChar() const
{
    return playerChar;
}

void Player::toggleMoved()
{
    moved = !moved;
}

// Builder player class
BuilderPlayer::BuilderPlayer() : Player()
{
    partPositions = std::vector<std::pair<int, int>>(1, std::pair<int, int>{0, 0});
    //playerChar = char(178);
    playerChar = char(176);
    type = SHIPTYPE::ONE;

    savedPos = std::pair<int, int>{ 0,0 };

    rotated = false;
    inBuilderMode = true;
    preset = false;

    initShips();
}

BuilderPlayer::BuilderPlayer(bool done)
{
    rotated = false;
    type = SHIPTYPE::ONE;
    playerChar = char(178);

    builtShipPositions =
    {
        {0,0}, {0, 1}, {0, 2}, {0,3},
        {2, 0}, {2, 1},
        {7, 0}, {7, 1}, {7, 2},
        {4, 4}, {5, 4}, {6, 4}
    };
    inBuilderMode = false;
    preset = true;
}


void BuilderPlayer::update()
{
    // variable to check if zero ships on field and to progress on battle view
    int shipCount = 0;

    //player on board movement
    if (_kbhit())//check if player pressed any buttons 
    {
        switch (_getch())
        {
        //moves crosshair left and right
        case 'a':
            // check if player is on left border
            if (partPositions.front().second == 0)
            {
                break;
            }
            //Move each ship x coord to left
            std::for_each(partPositions.begin(), partPositions.end(), [](std::pair<int, int>& p) {p.second--; });
            moved = true;
            break;
        case 'd':
            // check if player is on right border
            if (partPositions.front().second == 7)
            {
                break;
            }
            // Move each ship x coord to right
            std::for_each(partPositions.begin(), partPositions.end(), [](std::pair<int, int>& p) {p.second++; });
            moved = true;
            break;
            // up and down
        case 'w':
            //Check if ship is on top
            if (partPositions.front().first == 0)
            {
                break;
            }
            // Move each ship y coord to up
            std::for_each(partPositions.begin(), partPositions.end(), [](std::pair<int, int>& p) {p.first--; });
            moved = true;
            break;
        case 's':
            // Check if ship is on bottom
            if (partPositions.front().first == 7)
            {
                break;
            }
            // If ship is more than one need to check last part
            if (type != SHIPTYPE::ONE) {
                if (partPositions.back().first == 7)
                {
                    break;
                }
            }
            std::for_each(partPositions.begin(), partPositions.end(), [](std::pair<int, int>& p) {p.first++; });
            moved = true;
            break;

        //for changing ship class
        case '1':
            // Changing ship types from 1 to 4
            // Check if we are trying to switch to same type as we are already
            if (type == SHIPTYPE::ONE) break;
            switchType(1);
            moved = true;
            break;
        case '2':
            if (type == SHIPTYPE::TWO) break;
            switchType(2);
            moved = true;
            break;
        case '3':
            if (type == SHIPTYPE::THREE) break;
            switchType(3);
            moved = true;
            break;
        case '4':
            if (type == SHIPTYPE::FOUR) break;
            switchType(4);
            moved = true;
            break;

        // SPACE bar pressed
        case 32:
            // Places ship on board and saves it location on board
            placeShip();
            break;

        // Enter pressed
        case 13:    
            for (const auto& [key, value] : ships)
            {
                shipCount += value;
            }
            if (shipCount == 0)
            {
                inBuilderMode = false;
                break;
            }
            break;

        // R button pressed to rotate ship
        case 'r':
            rotateShip();
            break;

        default:
            std::cout << _getch();
            break;
        }

    }
}

void BuilderPlayer::displayInfo()
{
    // first + 1 is becaouse vector index starts with 0
    // for second we just switch between collumns
    std::cout << "\nCurrent crosshair position : " << partPositions.front().first + 1
        << char('A' + partPositions.front().second) << '\n';
    std::cout << "\nTo place :\n" << char(178) << " - " << ships[SHIPTYPE::ONE] << "  ";
    std::cout << char(178) << char(178) << " - " << ships[SHIPTYPE::TWO] << "  ";
    std::cout << char(178) << char(178) << char(178) << " - " << ships[SHIPTYPE::THREE] << "  ";
    std::cout << char(178) << char(178) << char(178) << char(178) << " - " << ships[SHIPTYPE::FOUR] << "\n";
    std::cout << "To rotate ships press \"r\". If all ships placed press \"Enter\"";
}

void BuilderPlayer::initShips()
{
    ships[SHIPTYPE::FOUR] = 1;
    ships[SHIPTYPE::THREE] = 2;
    ships[SHIPTYPE::TWO] = 3;
    ships[SHIPTYPE::ONE] = 4;

}

// function to add parts of ship when type changed
void BuilderPlayer::addPartsPos(int repeat)
{
    // just delete all parts, and start again with saved position part
    partPositions.clear();
    partPositions.push_back(savedPos);
    for (int i{ 1 }; i < repeat; i++) 
    {
        // Adding part by part down
        std::pair<int, int> toAdd{ partPositions.front() };
        
        toAdd.first += i;
        partPositions.push_back(toAdd);

    }

}

void BuilderPlayer::placeShip()
{
    if (ships[type] == 0) {
        return;
    }

    if (!checkValidPlace()) {
        return;
    }

    for (auto i : partPositions) {
        builtShipPositions.push_back(i);
    }
    ships[type]--;
    
}

bool BuilderPlayer::checkValidPlace()
{
    for (auto& part : partPositions)
    {
        for (auto& b_part : builtShipPositions)
        {
            //if any part is close enought to other ship, ship can't be placed here
            if ((abs(part.first - b_part.first) < 2) && (abs(part.second - b_part.second) < 2)) {
                return false;
            }
        }
    }
    return true;

}

void BuilderPlayer::deleteShip()
{
    for (auto& part : partPositions)
    {

        for (auto& b_part : builtShipPositions)
        {

            if (((part.first - b_part.first) == 0) && ((part.second - b_part.second) == 0))
            {
                break;
            }
        }
    }
}

void BuilderPlayer::rotateShip()
{
    int i;
    rotated = !rotated;
    std::vector<std::pair<int, int>> backUpPosition{ partPositions };

    if (rotated) {
        i = 1;
        std::for_each(partPositions.begin() + 1, partPositions.end(), [&](std::pair<int, int>& coords)
            {
                coords.first = partPositions.front().first;
                coords.second = partPositions.front().second + i;
                i++;
            }
        );
        for (auto& i : partPositions) {
            if (!checkValidRotate(i)) {
                partPositions = backUpPosition;
                break;
            }
        }

    }
    else if (!rotated) {
        i = 0;
        std::for_each(partPositions.begin() + 1, partPositions.end(), [&](std::pair<int, int>& coords)
            {
                coords.second = partPositions.front().second;
                coords.first = partPositions.front().first + i;
                i++;
            }
        );
        for (auto& i : partPositions) {
            if (!checkValidRotate(i)) {
                partPositions = backUpPosition;
                break;
            }
        }

    }
}

bool BuilderPlayer::checkValidRotate(std::pair<int,int>& position)
{
    if (position.first > 8 || position.second > 8)return false;

    if (position.first < 0 || position.second < 0) return false;

    return true;
}

void BuilderPlayer::switchType(int partsNum)
{
    rotated = false;
    savedPos = partPositions.front();
    switch (partsNum)
    {
    case 1:
        type = SHIPTYPE::ONE;
        addPartsPos(1);
        break;
    case 2:
        type = SHIPTYPE::TWO;
        if (!checkValidSwitchType(2)) { break; }
        addPartsPos(2);
        break;
    case 3:
        type = SHIPTYPE::THREE;
        if (!checkValidSwitchType(3)) { break; }
        addPartsPos(3);
        break;
    case 4:
        type = SHIPTYPE::FOUR;
        if (!checkValidSwitchType(4)) { break; }
        addPartsPos(4);
        break;
    default:
        break;
    }
}

bool BuilderPlayer::checkValidSwitchType(int partsToAdd)
{
    if (partPositions.back().first + (partsToAdd - partPositions.size()) > 8) {
        return false;
    }
    return true;
}

const std::vector<std::pair<int, int>>& BuilderPlayer::getCurrentPositions()
{
    return partPositions;
}

const std::vector<std::pair<int, int>>& BuilderPlayer::getPlacedShipPositions()
{
    return builtShipPositions;
}

const std::pair<int, int>& BuilderPlayer::getPosition()
{
    return partPositions.front();
}

const bool BuilderPlayer::getMode() const
{
    return inBuilderMode;
}

const bool BuilderPlayer::getPresset() const
{
    return preset;
}



// Battle player class implementation 
// Need to copy enemy ships, not mine
BattlePlayer::BattlePlayer(Enemy& enemy) : Player()
{
    for (auto i : enemy.getPlacedShipsPositions()) {
        shipsPositions.push_back(i);
    }
    shipsCount = 10;
    inGame = true;
}

void BattlePlayer::doShoot(std::pair<int, int> shootPosition)
{
    // Try to find if already shoot in this position
    auto it = std::find(shootsPositions.begin(), shootsPositions.end(), shootPosition);

    if (it != shootsPositions.end())
    {
        return;
    }
    
    // Then try shoot
    auto p_shoot = std::find(shipsPositions.begin(), shipsPositions.end(), shootPosition);

    // So if player missed
    if (p_shoot == shipsPositions.end()) {
        shootsPositions.push_back(shootPosition);
    }
    // If player hit enemy ship
    else {
        shootsPositions.push_back(shootPosition);
        hitedShipsPoisitions.push_back(shootPosition);
    }

}

void BattlePlayer::update()
{
    std::string answer{ " " };
    std::cout << "Please enter field where to shoot in form(A1 or B2) : ";
    std::cin >> answer;

    int second = abs(65 - answer[0]);
    int first = (answer[1] - '0') - 1;
    std::pair<int, int> shootPosition{ first, second };

    doShoot(shootPosition);

}

const std::vector<std::pair<int, int>>& BattlePlayer::getHitedShipsPositions()
{
    return hitedShipsPoisitions;
}

const std::vector<std::pair<int, int>>& BattlePlayer::getShootsPositions()
{
    return shootsPositions;
}

const std::vector<std::pair<int, int>>& BattlePlayer::getShipsPositions()
{
    return shipsPositions;
}

const std::pair<int, int>& BattlePlayer::getPosition()
{
    return currentPosition;
}

const bool BattlePlayer::isInGame() const
{
    return inGame;
}
