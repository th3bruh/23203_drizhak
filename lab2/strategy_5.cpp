#include "card.h"
#include "move.h"
#include "strategy.h"

#include <functional>
#include <memory>
#include <string_view>
#include "factory.h"

class Strategy_5 : public Strategy {
 public:
  Move GetNextMove() override {
    return s1->GetNextMove() == Move::Stand || s2->GetNextMove() == Move::Stand
               ? Move::Stand
               : Move::Hit;
  }
  void TakeCard(Card card) override {
    s1->TakeCard(card);
    s2->TakeCard(card);
  }

  void TakeOpponentCard(Card card) override {
    s1->TakeOpponentCard(card);
    s2->TakeOpponentCard(card);
  }

  std::string_view GetName() override { return "Strategy_5"; }

  void ReduceAce() override {
    s1->ReduceAce();
    s2->ReduceAce();
  }

  void ReadConfig([[maybe_unused]] std::string confdir) override {
    s1->ReadConfig(confdir);
    s2->ReadConfig(confdir);
  }

  void Reset() override {
  }
 private:
  std::unique_ptr<Strategy> s1 = Factory<std::string, std::function<Strategy*()>>::Create("strategy_2");
  std::unique_ptr<Strategy> s2 = Factory<std::string, std::function<Strategy*()>>::Create("strategy_4");
};

namespace {
Registrator<std::string, Strategy, Strategy_5> r("strategy_5");
}
