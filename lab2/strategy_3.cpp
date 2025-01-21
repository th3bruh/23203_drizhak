#include "strategy.h"

#include <fstream>
#include <ios>
#include <string_view>
#include "factory.h"

class Strategy_3 : public Strategy {
 public:
  Move GetNextMove() override {
    return current_score >= opponent_card_value + parameter ? Move::Stand : Move::Hit;
  }
  void TakeCard(Card card) override { current_score += card.Value(); }

  void TakeOpponentCard(Card card) override {
    opponent_card_value = card.Value();
  }

  std::string_view GetName() override { return "Strategy_3"; }

  void ReduceAce() override {
    current_score -= Card::ACE_REDUCTION_VALUE;
  }

  void ReadConfig([[maybe_unused]] std::string confdir) override {
    std::ifstream fin{confdir + "strategy_3.config"};
    fin.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    fin >> parameter;
  }

  void Reset() override {
    current_score = 0;
  }
 private:
  unsigned int parameter = 0;
  unsigned int opponent_card_value = 0;
  unsigned int current_score = 0;
};

namespace {
Registrator<std::string, Strategy, Strategy_3> r("strategy_3");
}
