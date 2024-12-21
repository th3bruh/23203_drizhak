#pragma once

#include <string>

class UserInterface {
 public:
  virtual void ShowRoundResult(std::string winnername) = 0;
  virtual void ShowCompetitionResult(std::string winnername) = 0;
  virtual void ShowTournamentResult(std::string winnername) = 0;
  virtual ~UserInterface() = default;
};
