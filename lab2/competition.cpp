#include "competition.h"
#include "engine_impl.h"

#include <cassert>
#include <vector>

#include "card.h"
#include "deck.h"
#include "strategy.h"
#include "user_interface.h"

Competition::Competition(Mode mode, std::vector<Strategy*> strategies,
                         UserInterface& interface, Deck& deck)
    : mode_(mode), interface_(interface), deck_(deck) {
  assert(strategies.size() == 2);
  s[0].strategy = strategies[0];
  s[1].strategy = strategies[1];
}

void Competition::Play() {
  GiveCard(0);
  GiveCard(1);
  if (mode_ == Mode::DETAILED) {
    interface_.ShowRoundStatus(s[0].strategy->GetName(), s[0].cards.back(),
                               s[0].move, s[0].score);
    interface_.ShowRoundStatus(s[1].strategy->GetName(), s[1].cards.back(),
                               s[1].move, s[1].score);
  }
  s[0].strategy->TakeOpponentCard(s[1].cards.back());
  s[1].strategy->TakeOpponentCard(s[0].cards.back());

  while (true) {
    if (mode_ == Mode::DETAILED) {
      if (interface_.IsFinished()) return;
    }

    for (unsigned int i = 0; i < 2; ++i) {
      if (s[i].move == Move::Hit) {
        GiveCard(i);
      }

      switch (CheckScore(i)) {
        case Status::Win:
          if (mode_ == Mode::FAST) {
            interface_.ShowCompetitionResult(s[i].strategy->GetName(),
                                             s[i].score);
          }
          return;
        case Status::Lose:
          if (mode_ == Mode::FAST) {
            interface_.ShowCompetitionResult(s[!i].strategy->GetName(),
                                             s[!i].score);
          }
          return;
        case Status::Continue:
          break;
      }

      if (mode_ == Mode::DETAILED) {
        interface_.ShowRoundStatus(s[i].strategy->GetName(), s[i].cards.back(),
                                   s[i].move, s[i].score);
      }
    }

    if (s[0].move == Move::Stand && s[1].move == Move::Stand) {
      if (s[0].score == s[1].score) {
        interface_.ShowCompetitionResultDraw(
            s[0].strategy->GetName(), s[1].strategy->GetName(), s[0].score);
        return;
      }
      const bool winner_idx = s[0].score < s[1].score;
      interface_.ShowCompetitionResult(s[winner_idx].strategy->GetName(),
                                       s[winner_idx].score);
      winners.push_back(winner_idx);
      return;
    }
  }
}

Competition::Status Competition::CheckScore(unsigned int idx) {
  if (s[idx].score == TWENTY_ONE) {
    winners.push_back(idx);
    if (mode_ == Mode::DETAILED) {
      interface_.ShowEarlyWin(s[idx].strategy->GetName(), s[idx].cards.back(),
                              s[idx].score);
    }
    return Status::Win;
  }
  if (s[idx].score > TWENTY_ONE) {
    winners.push_back(!idx);
    if (mode_ == Mode::DETAILED) {
      interface_.ShowEarlyLose(s[idx].strategy->GetName(), s[idx].cards.back(),
                               s[idx].score);
    }
    return Status::Lose;
  }
  return Status::Continue;
}

void Competition::GiveCard(unsigned int idx) {
  Card card = deck_.GetCard();
  s[idx].ace_count += card.rank == Card::Rank::ace;
  s[idx].score += card.Value();
  s[idx].strategy->TakeCard(card);
  s[idx].cards.push_back(card);

  if (s[idx].score > TWENTY_ONE && s[idx].ace_count) {
    s[idx].strategy->ReduceAce();
    s[idx].score -= ACE_REDUCTION_VALUE;
    s[idx].ace_count--;
  }

  s[idx].move = s[idx].strategy->GetNextMove();
}

namespace {
engine::Registrator<Competition> d("detailed", Mode::DETAILED);
engine::Registrator<Competition> f("fast", Mode::FAST);
}  // namespace
