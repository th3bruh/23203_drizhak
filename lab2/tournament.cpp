#include "engine_impl.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Tournament : public Engine {
 public:
  Tournament(std::vector<std::string> strategies,
              std::string deck,
              std::string interface,
              unsigned int deck_number)
      : strategies_(strategies),
        deck_(deck),
        deck_number_(deck_number),
        interface_(interface),
        win_count_(strategies.size(), 0) {
  }
  void Play() override {

    for (size_t i = 0; i < strategies_.size(); ++i) {
      for (size_t j = 0; j < strategies_.size(); ++j) {
        if (i == j) continue;

        std::vector<std::string> tmp{strategies_[i], strategies_[j]};
        std::unique_ptr<Engine> competition = engine_namespace::Factory::Create("fast", tmp, deck_, interface_, deck_number_);
        competition->Play();

        for (size_t k : competition->GetWinners()) {
          win_count_[k]++;
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
  std::vector<std::string> strategies_;
  std::string deck_;
  unsigned int deck_number_;
  std::string interface_;
  std::vector<unsigned int> win_count_;
};

namespace {
engine_namespace::Registrator<Tournament> r("tournament");
}  // namespace
