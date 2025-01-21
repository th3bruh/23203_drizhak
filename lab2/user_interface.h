#pragma once

#include <string_view>
#include <vector>

#include "card.h"
#include "move.h"

class UserInterface {
 public:
  virtual void ShowRoundStatus(std::string_view name, Card card, Move move, unsigned int score) = 0;
  virtual void ShowEarlyLose(std::string_view name, Card card,
                               unsigned int score) = 0;
  virtual void ShowEarlyWin(std::string_view name, Card card,
                               unsigned int score) = 0;
  virtual void ShowCompetitionResult(std::string_view winner, unsigned int score) = 0;
  virtual void ShowCompetitionResultDraw(std::string_view name1, std::string_view name2, unsigned int score) = 0;
  virtual void ShowTournamentResult(const std::vector<std::string_view>& winners, unsigned int wincount) = 0;
  virtual void ShowPairToPlay(std::string_view name1, std::string_view name2) = 0;
  virtual bool IsFinished() = 0;
  virtual ~UserInterface() = default;
};
