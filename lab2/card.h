#pragma once

#include <string>

struct Card {
  enum class Suit {
    clubs,
    diamonds,
    hearts,
    spades,
  };

  enum class Rank {
    one = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
  };

  Suit suit;
  Rank rank;
  constexpr int Value() {
    switch (rank) {
      case Rank::one:
        return 1;
      case Rank::two:
        return 2;
      case Rank::three:
        return 3;
      case Rank::four:
        return 4;
      case Rank::five:
        return 5;
      case Rank::six:
        return 6;
      case Rank::seven:
        return 7;
      case Rank::eight:
        return 8;
      case Rank::nine:
        return 9;
      case Rank::ten:
        return 10;
      case Rank::jack:
        return 10;
      case Rank::queen:
        return 10;
      case Rank::king:
        return 10;
      case Rank::ace:
        return 11;
    }
  }

  constexpr std::string Name() {
    switch (rank) {
      case Rank::one:
        return "one";
      case Rank::two:
        return "two";
      case Rank::three:
        return "three";
      case Rank::four:
        return "four";
      case Rank::five:
        return "five";
      case Rank::six:
        return "six";
      case Rank::seven:
        return "seven";
      case Rank::eight:
        return "eight";
      case Rank::nine:
        return "nine";
      case Rank::ten:
        return "ten";
      case Rank::jack:
        return "jack";
      case Rank::queen:
        return "queen";
      case Rank::king:
        return "king";
      case Rank::ace:
        return "ace";
    }
  }

  constexpr std::string SuitName() {
    switch (suit) {
      case Suit::clubs:
        return "clubs";
      case Suit::diamonds:
        return "diamonds";
      case Suit::hearts:
        return "hearts";
      case Suit::spades:
        return "spades";
    }
  }
};
