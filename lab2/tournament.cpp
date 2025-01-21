#include <algorithm>
#include <cassert>
#include <string_view>
#include <vector>

#include "competition.h"
#include "deck.h"
#include "engine_impl.h"
#include "strategy.h"
#include "user_interface.h"

class Tournament : public Engine {
 public:
  Tournament(const std::vector<Strategy*>& strategies, UserInterface& interface,
             Deck& deck)
      : strategies_(strategies),
        interface_(interface),
        deck_(deck),
        win_count_(strategies.size(), 0) {
    assert(strategies.size() > 2);
  }

  void Play() override {
    for (size_t i = 0; i < strategies_.size(); ++i) {
      for (size_t j = 0; j < strategies_.size(); ++j) {
        if (i == j) continue;
        interface_.ShowPairToPlay(strategies_[i]->GetName(),
                                  strategies_[j]->GetName());

        std::vector<Strategy*> tmp{strategies_[i], strategies_[j]};
        Competition competition =
            Competition(Mode::FAST, tmp, interface_, deck_);
        competition.Play();
        strategies_[i]->Reset();
        strategies_[j]->Reset();
        deck_.Reset();

        for (bool k : competition.GetWinners()) {
          win_count_[k ? i : j]++;
        }
      }
    }

    std::vector<std::string_view> winners;
    size_t max_win_count =
        *std::max_element(win_count_.begin(), win_count_.end());

    for (size_t i = 0; i < strategies_.size(); ++i) {
      if (win_count_[i] == max_win_count) winners.push_back(strategies_[i]->GetName());
    }
    interface_.ShowTournamentResult(winners, max_win_count);
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
