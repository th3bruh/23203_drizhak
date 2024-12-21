#include "engine_impl.h"

#include <cassert>
#include <functional>
#include <memory>
#include <vector>

#include "deck.h"
#include "factory.h"
#include "strategy.h"
#include "user_interface.h"

enum class Mode {
  DETAILED,
  FAST,
};

class Competition : public Engine {
 public:
  Competition(Mode mode, std::vector<std::string> strategies,
              std::string deck,
              std::string interface,
              unsigned int deck_number)
      : mode_(mode),
        deck_(Factory<std::string, std::function<Deck*(unsigned int)>>::Create(deck, deck_number)),
        interface_(Factory<std::string, std::function<UserInterface*()>>::Create(interface)) {
    // TODO? warning if mode == competition &
    assert(strategies.size() >= 2);
    s1.strategy = Factory<std::string, std::function<Strategy*()>>::Create(strategies[1]);
    s2.strategy = Factory<std::string, std::function<Strategy*()>>::Create(strategies[2]);
  }

  void Play() override {

    while (true) {
      if (!s1.stand) {
        if (GiveCard(s1)) break;
      }
      if (!s2.stand) {
        if (GiveCard(s2)) break;
      }
      if (s1.stand && s2.stand) break;
    }
  }

  bool GetWinner() {
    return winner;
  }

 private:
  enum class GameEnd {
    Win,
    Lose,
  };
  struct StrategyData {
    bool stand = false;
    unsigned int ace_count = 0;
    unsigned int score = 0;
    std::vector<Card> cards;
    std::unique_ptr<Strategy> strategy;
  };

  bool GiveCard(StrategyData& s) {
    Card card = deck_->GetCard();
    s.score += card.Value();
    s.cards.push_back(card);
    s.strategy->TakeCard(s.cards.back());
    s.stand = Move::Stand == s.strategy->GetNextMove();

    return s.score >= 21;
  }

  std::vector<size_t> GetWinners() override {return std::vector<size_t>();};
  unsigned int GetRandomCard() { return rand() % 9 + 1; }

  Mode mode_;
  bool winner = false;
  std::unique_ptr<Deck> deck_;
  std::unique_ptr<UserInterface> interface_;
  StrategyData s1;
  StrategyData s2;
};

namespace {
engine_namespace::Registrator<Competition> r("detailed", Mode::DETAILED);
engine_namespace::Registrator<Competition> d("fast", Mode::FAST);
}  // namespace
