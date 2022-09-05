#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Errors.h"
namespace sviridenko
{
  void help(std::ostream& ostream, std::vector< std::string >& words,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void list(std::ostream& ostream, std::vector< std::string >& words, std::map< std::string,
    std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void find(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void search(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void clear(std::ostream& ostream, std::vector< std::string >& words, std::map< std::string,
    std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void searchWithTranslate(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void changeTranslation(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void print(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void deleteWord(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void insert(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void compare(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void merge(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void history(std::ostream& ostream, std::vector< std::string >& words,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
  void save(std::ostream& ostream, std::vector< std::string >& words,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts, char* arg,
    std::map<int, std::vector< std::string > >& hist, int& numberOfCommand);
}
