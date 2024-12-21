
#include <iostream>

#include "factory.h"
#include "user_interface.h"

class ConsoleInterfase : public UserInterface {
 public:
  void ShowRoundResult(std::string winnername) override {
    std::cout << winnername << std::endl;
  }
  void ShowCompetitionResult(std::string winnername) override {
    std::cout << "strategy " << winnername << "won" << std::endl;
  }
  void ShowTournamentResult(std::string winnername) override {
    std::cout << "strategy " << winnername << "won the tournament" << std::endl;
  }
};

namespace {
Registrator<std::string, UserInterface, ConsoleInterfase> r("console");
}
