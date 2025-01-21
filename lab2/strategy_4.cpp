#include "strategy.h"

#include <string_view>
#include "factory.h"

class Strategy_4 : public Strategy {
 public:
  Move GetNextMove() override {
    return current_score >= Card::TWENTY_ONE - opponent_card_value ? Move::Stand : Move::Hit;
  }
  void TakeCard(Card card) override { current_score += card.Value(); }

  void TakeOpponentCard(Card card) override {
    opponent_card_value = card.Value();
  }

  std::string_view GetName() override { return "Strategy_4"; }

  void ReduceAce() override {
    current_score -= Card::ACE_REDUCTION_VALUE;
  }

  void ReadConfig([[maybe_unused]] std::string confdir) override {}

  void Reset() override {
    current_score = 0;
  }
 private:
  unsigned int opponent_card_value = 0;
  unsigned int current_score = 0;
};

namespace {
Registrator<std::string, Strategy, Strategy_4> r("strategy_4");
}
