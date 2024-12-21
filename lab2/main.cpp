// User Interface:
// MVC
// EBC
// MVVM


#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "engine.h"

namespace po = boost::program_options;

void print_help(po::options_description options) {
  std::cout
      << "USAGE: blackjack [options] <strategy1> <strategy2> [<strategy3> ...]"
      << std::endl
      << options << std::endl;
}

int main(int argc, char** argv) {

  std::string mode;
  std::string deck;
  std::string interface;
  std::string confdir;
  unsigned int deck_number;

  po::options_description visible("OPTIONS");
  visible.add_options()
    ("help,h", "Show this help message")
    ("mode,m",
     po::value<std::string>(&mode)->value_name("[detailed|fast|tournament]"),
     "Set game mode")
    ("deck,d",
     po::value<std::string>(&deck)->default_value("simple")->value_name("[simple|multiple]"),
     "Set deck mode")
    ("interface,i",
     po::value<std::string>(&interface)->default_value("console")->value_name("[console]"),
     "Set interface mode")
    ("confdir,c",
     po::value<std::string>(&confdir)->value_name("<path/to/dir>"),
     "Set directory with config files for strategies")
    ("deck_number,n",
     po::value<unsigned int>(&deck_number)->default_value(4)->value_name("int"),
     "If deck mode is set to \"multiple\", set number of decks used")
  ;

  std::vector<std::string> strategies;

  po::options_description positional;
  positional.add_options()
    ("strategies", po::value<std::vector<std::string>>(&strategies))
  ;

  po::options_description all;
  all.add(visible).add(positional);
  po::positional_options_description pd;
  pd.add("strategies", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
      .options(all)
      .positional(pd)
      .run(),
      vm);
  po::notify(vm);

  if (mode.empty()) {
    mode = strategies.size() == 2 ? "detailed" : "tournament";
  }

  std::cout << "deck: " << deck << std::endl;
  std::cout << "deck_number: " << deck_number << std::endl;
  std::cout << "strategies count: " << strategies.size() << std::endl;

  for (size_t i = 0; i < strategies.size(); ++i) {
    std::cout << strategies[i] << std::endl;
  }
  std::cout << "mode: " << mode << std::endl;

  if (strategies.size() < 2 || vm.contains("help")) {
    print_help(visible);
  }
  std::unique_ptr<Engine> engine =
      engine_namespace::Factory::Create(mode, strategies, deck, interface, deck_number);

  engine->Play();

  std::cout << "bruh" << std::endl;
}
