#include "strategy.h"
#include "factory.h"

class Strategy_1 : public Strategy {
 public:
  Move GetNextMove() override {
    return current_score == 21 ? Move::Stand : Move::Hit;
  }
  void TakeCard(Card card) override { current_score += card.Value(); }
  void TakeOpponentCard([[maybe_unused]] Card card) override {}
  virtual std::string GetName() override { return "AllIn"; }
 private:
  int current_score = 0;
};

namespace {
Registrator<std::string, Strategy, Strategy_1> r("strategy_1");
}

