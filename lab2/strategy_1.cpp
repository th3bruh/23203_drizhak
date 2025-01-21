#include "strategy.h"

#include <fstream>
#include <ios>
#include <string_view>
#include "factory.h"

class Strategy_1 : public Strategy {
 public:
  Move GetNextMove() override {
    return current_score == max_score ? Move::Stand : Move::Hit;
  }
  void TakeCard(Card card) override { current_score += card.Value(); }

  void TakeOpponentCard([[maybe_unused]] Card card) override {}

  std::string_view GetName() override { return "Strategy_1"; }

  void ReduceAce() override {
    current_score -= Card::ACE_REDUCTION_VALUE;
  }

  void ReadConfig(std::string confdir) override {
    std::ifstream fin{confdir + "strategy_1.config"};
    fin.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    fin >> max_score;
  }

  void Reset() override {
    current_score = 0;
  }
 private:
  unsigned int max_score;
  unsigned int current_score = 0;
};

namespace {
Registrator<std::string, Strategy, Strategy_1> r("strategy_1");
}
