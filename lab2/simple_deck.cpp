#include "deck.h"

#include <random>
#include <string>

#include "card.h"
#include "factory.h"

class SimpleDeck : public Deck {
 public:
  SimpleDeck([[maybe_unused]] unsigned int n) {};
  void Reset() override {}
  Card GetCard() override {
    std::random_device rd;
    std::uniform_int_distribution dist(1, 10);
    return Card{Card::Suit::clubs, static_cast<Card::Rank>(dist(rd))};
  }
};

namespace {
Registrator<std::string, Deck, SimpleDeck, unsigned int> r("simple");
}
