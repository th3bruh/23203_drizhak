#include "deck.h"
#include "engine_impl.h"
#include "strategy.h"
#include "user_interface.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Tournament : public Engine {
 public:
  Tournament(const std::vector<Strategy*>& strategies,
              UserInterface& interface,
              Deck& deck)
      : strategies_(strategies),
        interface_(interface),
        deck_(deck),
        win_count_(strategies.size(), 0) {
  }
  void Play() override {

    for (size_t i = 0; i < strategies_.size(); ++i) {
      for (size_t j = 0; j < strategies_.size(); ++j) {
        if (i == j) continue;

        std::vector<Strategy*> tmp{strategies_[i], strategies_[j]};
        std::unique_ptr<Engine> competition = engine::Factory::Create("fast", tmp, interface_, deck_);
        competition->Play();

        for (size_t k : competition->GetWinners()) {
          win_count_[k ? j : i]++;
        }
      }
    }
  }
  std::vector<size_t> GetWinners()  override {
    std::vector<size_t> winners;
    unsigned int max_win_count = *std::max_element(win_count_.begin(), win_count_.end());
    for (size_t i = 0; i < strategies_.size(); ++i) {
      if (win_count_[i] == max_win_count) winners.push_back(i);
    }
    
    return winners;
  }
 private:
  const std::vector<Strategy*>& strategies_;
  UserInterface& interface_;
  Deck& deck_;
  std::vector<unsigned int> win_count_;
};

namespace {
engine::Registrator<Tournament> r("tournament");
}  // namespace
