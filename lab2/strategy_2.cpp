#include "strategy.h"

#include <string_view>
#include "factory.h"

class Strategy_2 : public Strategy {
 public:
  Move GetNextMove() override {
    return cards_taken++ == 3 ? Move::Stand : Move::Hit;
  }
  void TakeCard(Card card) override { cards_taken += card.Value(); }

  void TakeOpponentCard([[maybe_unused]] Card card) override {}

  std::string_view GetName() override { return "Strategy_2"; }

  void ReduceAce() override {}

  void ReadConfig([[maybe_unused]] std::string confdir) override {}

  void Reset() override {
    cards_taken = 0;
  }
 private:
  unsigned int cards_taken = 0;
};

namespace {
Registrator<std::string, Strategy, Strategy_2> r("strategy_2");
}
