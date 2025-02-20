#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>

enum class Input { Right, Left, Down, Up };

struct GameData {
  std::bitset<5> m_input;  // [up, down, left, right]
};

#endif