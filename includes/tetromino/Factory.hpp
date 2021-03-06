#pragma once

#include "O.hpp"
#include "I.hpp"
#include "J.hpp"
#include "L.hpp"
#include "S.hpp"
#include "T.hpp"
#include "Z.hpp"
#include <boost/shared_ptr.hpp>
#include <random>
#include <chrono>

class TetrominoFactory {
 public:
  static boost::shared_ptr<Tetromino> create(const Tetromino::Type type)
  {
    if (type == Tetromino::Type::I)
        return boost::shared_ptr<Tetromino>(new ITetromino);
    else if (type == Tetromino::Type::J)
        return boost::shared_ptr<Tetromino>(new JTetromino);
    else if (type == Tetromino::Type::L)
        return boost::shared_ptr<Tetromino>(new LTetromino);
    else if (type == Tetromino::Type::O)
        return boost::shared_ptr<Tetromino>(new OTetromino);
    else if (type == Tetromino::Type::S)
        return boost::shared_ptr<Tetromino>(new STetromino);
    else if (type == Tetromino::Type::T)
        return boost::shared_ptr<Tetromino>(new TTetromino);
    else if (type == Tetromino::Type::Z)
        return boost::shared_ptr<Tetromino>(new ZTetromino);
  }

  static boost::shared_ptr<Tetromino> random_tetromino()
  {
    std::random_device rd;
    std::mt19937 mt{static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> dist(0, 6);

    auto type(dist(mt));

    return create(static_cast<Tetromino::Type>(type));
  }
};
