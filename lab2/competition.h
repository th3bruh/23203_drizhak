#pragma once

#include "deck.h"
#include "engine.h"
#include "strategy.h"
#include "user_interface.h"

enum class Mode {
  DETAILED,
  FAST,
};

class Competition : public Engine {
 public:
   Competition(Mode mode, std::vector<Strategy*> strategies,
              UserInterface& interface,
              Deck& deck);
    void Play() override;
  std::vector<unsigned int> GetWinners() { return winners; };

 private:
  enum class Status {
    Win,
    Lose,
    Continue,
  };

  Status CheckScore(unsigned int idx);
  void GiveCard(unsigned int idx);

  struct StrategyData {
    Move move = Move::Hit;
    unsigned int ace_count = 0;
    unsigned int score = 0;
    std::vector<Card> cards;
    Strategy* strategy;
  };

  Mode mode_;
  std::vector<unsigned int> winners;
  UserInterface& interface_;
  Deck& deck_;
  StrategyData s[2];
  static constexpr unsigned int TWENTY_ONE = 21;
  static constexpr unsigned int ACE_REDUCTION_VALUE = 10;
};

