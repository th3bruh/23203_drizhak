#pragma once

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

  static constexpr unsigned int TWENTY_ONE = 21;
  static constexpr unsigned int ACE_REDUCTION_VALUE = 10;

  constexpr unsigned int Value() {
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
};
