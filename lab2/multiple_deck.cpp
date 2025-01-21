#include "deck.h"

#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include "card.h"
#include "factory.h"

const std::vector<Card::Suit> suits = {Card::Suit::clubs, Card::Suit::diamonds,
                                       Card::Suit::hearts, Card::Suit::spades};

const std::vector<Card::Rank> ranks = {
    Card::Rank::one,  Card::Rank::two, Card::Rank::three, Card::Rank::four,
    Card::Rank::five, Card::Rank::six, Card::Rank::seven, Card::Rank::eight,
    Card::Rank::nine, Card::Rank::ten, Card::Rank::jack,  Card::Rank::queen,
    Card::Rank::king, Card::Rank::ace};

class MultipleDeck : public Deck {
 public:
  MultipleDeck(unsigned int n) : n_(n){
    FillDeck();
  }

  void Reset() override {
    deck.clear();
    FillDeck();
  }

  Card GetCard() override {
    const Card card = deck.back();
    deck.pop_back();
    return card;
  }

 private:
  void FillDeck() {
    for (unsigned int i = 0; i < n_; ++i) {
      for (auto rank : ranks) {
        for (auto suit : suits) {
          deck.push_back(Card{suit, rank});
        }
      }
    }
    std::random_device rd;
    std::default_random_engine rng{rd()};
    std::ranges::shuffle(deck, rng);
  }

  const unsigned int n_;
  std::vector<Card> deck;
};

namespace {
Registrator<std::string, Deck, MultipleDeck, unsigned int> r("multiple");
}
