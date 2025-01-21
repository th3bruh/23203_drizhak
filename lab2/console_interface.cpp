
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>

#include "card.h"
#include "factory.h"
#include "move.h"
#include "user_interface.h"

class ConsoleInterfase : public UserInterface {
 public:
  void ShowRoundStatus(std::string_view name, Card card, Move move,
                       unsigned int score) override {
    std::cout << name << " got " << RankName(card.rank) << " of "
              << SuitName(card.suit) << " and chose to " << MoveName(move)
              << " with total score: " << score << std::endl;
  }
  void ShowEarlyLose(std::string_view name, Card card,
                     unsigned int score) override {
    std::cout << name << " got " << RankName(card.rank) << " of "
              << SuitName(card.suit) << " and lost with score: " << score << "!"
              << std::endl;
  }

  void ShowEarlyWin(std::string_view name, Card card, unsigned int score) override {
    std::cout << name << " got " << RankName(card.rank) << " of "
              << SuitName(card.suit) << " and won with score: " << score << "!"
              << std::endl;
  }

  bool IsFinished() override {
    std::cout <<  "press <Enter> to continue, q to exit" << std::endl;
    int c = std::cin.peek();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return c == 'q' || c == 'Q';
  }

  void ShowCompetitionResult(std::string_view winner, unsigned int score) override {
    std::cout <<  winner << " won with score: " << score << "!" << std::endl;
  }

  void ShowCompetitionResultDraw(std::string_view name1, std::string_view name2, unsigned int score) override {
    std::cout <<  name1 << " and " << name2 << " got a draw with score: " << score << "!" << std::endl;
  }

  void ShowTournamentResult(const std::vector<std::string_view>& winners, unsigned int wincount) override {
    assert(winners.size() >= 1);
      std::cout <<  winners[0];
    for (size_t i = 1; i < winners.size(); ++i) {
      std::cout << ", "<<  winners[i];
    }
    std::cout << " won the tournament with " << wincount << " wins!" << std::endl;
  }

  void ShowPairToPlay(std::string_view name1, std::string_view name2) override {
    std::cout << name1 << " vs " << name2 << std::endl;
  }

private:
  constexpr std::string_view RankName(Card::Rank rank) {
    switch (rank) {
      case Card::Rank::one:
        return "one";
      case Card::Rank::two:
        return "two";
      case Card::Rank::three:
        return "three";
      case Card::Rank::four:
        return "four";
      case Card::Rank::five:
        return "five";
      case Card::Rank::six:
        return "six";
      case Card::Rank::seven:
        return "seven";
      case Card::Rank::eight:
        return "eight";
      case Card::Rank::nine:
        return "nine";
      case Card::Rank::ten:
        return "ten";
      case Card::Rank::jack:
        return "jack";
      case Card::Rank::queen:
        return "queen";
      case Card::Rank::king:
        return "king";
      case Card::Rank::ace:
        return "ace";
    }
  }

  constexpr std::string_view SuitName(Card::Suit suit) {
    switch (suit) {
      case Card::Suit::clubs:
        return "clubs";
      case Card::Suit::diamonds:
        return "diamonds";
      case Card::Suit::hearts:
        return "hearts";
      case Card::Suit::spades:
        return "spades";
    }
  }

  constexpr std::string_view MoveName(Move move) {
    switch (move) {
      case Move::Hit:
        return "hit";
      case Move::Stand:
        return "stand";
    }
  }
};

namespace {
Registrator<std::string, UserInterface, ConsoleInterfase> r("console");
}
