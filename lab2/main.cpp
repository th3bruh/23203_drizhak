// User Interface:
// MVC
// EBC
// MVVM

#include <algorithm>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <cassert>
#include <functional>
#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "deck.h"
#include "engine.h"
#include "factory.h"
#include "strategy.h"
#include "user_interface.h"

namespace po = boost::program_options;

void print_help(po::options_description options) {
  std::cout
      << "USAGE: blackjack [options] <strategy1> <strategy2> [<strategy3> ...]"
      << std::endl;

  std::cout << "Strategies availible: ";
  for (auto strategy :
       Factory<std::string, std::function<Strategy*()>>::GetKeys()) {
    std::cout << strategy << " ";
  }
  std::cout << std::endl << options << std::endl;
}

int main(int argc, char** argv) {

  std::string mode;
  std::string deck_name;
  std::string interface_name;
  std::string confdir;
  unsigned int deck_number;

  po::options_description visible("OPTIONS");
  visible.add_options()
    ("help,h", "Show this help message")
    ("mode,m",
     po::value<std::string>(&mode)->value_name("[detailed|fast|tournament]"),
     "Set game mode")
    ("deck,d",
     po::value<std::string>(&deck_name)->default_value("simple")->value_name("[simple|multiple]"),
     "Set deck mode")
    ("interface,i",
     po::value<std::string>(&interface_name)->default_value("console")->value_name("[console]"),
     "Set interface mode")
    ("confdir,c",
     po::value<std::string>(&confdir)->value_name("<path/to/dir>"),
     "Set directory with config files for strategies")
    ("deck_number,n",
     po::value<unsigned int>(&deck_number)->default_value(4)->value_name("<number>"),
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

  /*
  std::cout << "interface: " << interface_name << std::endl;
  std::cout << "deck: " << deck_name << std::endl;
  std::cout << "deck_number: " << deck_number << std::endl;
  std::cout << "strategies count: " << strategies.size() << std::endl;

  for (auto& strategy : strategies) {
    std::cout << strategy << std::endl;
  }
  std::cout << "mode: " << mode << std::endl;
  */
  if ((mode == "fast" || mode == "detailed") &&  strategies.size() > 2) {
    std::cout << "too many strategies for " << mode << " mode" << std::endl;
    print_help(visible);
    return 0;
  }

  if (strategies.size() < 2 || vm.contains("help")) {
    print_help(visible);
    return 0;
  }

  std::vector<std::unique_ptr<Strategy>> strategies_unique;
  std::vector<Strategy*> strategies_raw;

  for (auto strategy : strategies) {
    try {
      strategies_unique.push_back(Factory<std::string, std::function<Strategy*()>>::Create(strategy));
      strategies_unique.back()->ReadConfig(confdir);
    } catch (std::out_of_range) {
      std::cout << strategy << " is invalid strategy" << std::endl;
      return 0;
    } catch (std::ios_base::failure f) {
      std::cout << f.what() << "error occured while reading config file for " << strategy << std::endl;
      return 0;
    }
  }

  std::transform(strategies_unique.begin(), strategies_unique.end(),
                 std::back_inserter(strategies_raw),
                 [](auto& s) { return s.get(); });

  std::unique_ptr<UserInterface> interface;
  std::unique_ptr<Deck> deck;
  std::unique_ptr<Engine> engine;
  try {
    interface = Factory<std::string, std::function<UserInterface*()>>::Create(interface_name);
  } catch (std::out_of_range) {
    std::cout << interface_name << " is invalid interface" << std::endl;
    print_help(visible);
    return 0;
  }
  try {
    deck = Factory<std::string, std::function<Deck*(unsigned int)>>::Create(deck_name, deck_number);
  } catch (std::out_of_range) {
    std::cout << deck_name << " is invalid deck" << std::endl;
    print_help(visible);
    return 0;
  }
  try {
    engine = engine::Factory::Create(mode, strategies_raw, *interface, *deck);
  } catch (std::out_of_range) {
    std::cout << mode << " is invalid mode" << std::endl;
    print_help(visible);
    return 0;
  }

  engine->Play();
}
