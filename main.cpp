#include <string>
#include <functional>
#include <Windows.h>
#include "Commands.h"
int main(int argc, char* argv[], std::ostream& ostream = std::cout)
{
  if (argc < 3)
  {
    std::cerr << "Incorrect argc\n";
    return 1;
  }
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  std::map<int, std::vector< std::string > > hist;
  int numberOfCommand = 1;
  std::map< std::string, std::map< std::string, std::vector< std::string > > > listOfDIcts;
  std::string name = "";
  for (std::size_t i = 3; i != argc; i++)
  {
    std::ifstream fstream;
    std::string srcFile = argv[i];
    fstream.open(srcFile);
    if (!fstream.is_open())
    {
      std::cerr << "Incorrect argc\n";
      return 1;
    }
    std::map<std::string, std::vector< std::string> > tree;
    int counter = 1;
    while (!fstream.eof())
    {
      std::vector< std::string> words;
      std::vector< std::string> russian;
      std::string line = "";
      std::getline(fstream, line);
      if (counter == 1)
      {
        name = line;
        counter++;
        continue;
      }
      if (line == "")
      {
        std::cerr << "<EMPTY>\n";
      }
      else
      {
        if (line != "\0")
        {
          line += ' ';
          std::string temp = "";
          for (std::size_t i = 0; i < line.size(); i++)
          {
            if (line[i] == ' ')
            {
              words.push_back(temp);
              temp = "";
            }
            else
            {
              temp += line[i];
            }
          }
        }
        std::string english = words[0];
        words.erase(words.begin());
        for (std::vector< std::string >::iterator it = words.begin(); it != words.end(); it++)
        {
          russian.push_back(*it);
        }
        tree.insert({ english, russian });
      }
    }
    fstream.close();
    listOfDIcts.insert({ name, tree });
  }
  std::ifstream fstream;
  std::string srcFile = argv[2];
  fstream.open(srcFile);
  if (!fstream.is_open())
  {
    std::cerr << "Incorrect argc\n";
    return 1;
  }
  std::map<std::string, std::vector< std::string> > tree;
  while (!fstream.eof())
  {
    std::vector< std::string> words;
    std::string line = "";
    std::getline(fstream, line);
    if (line == "")
    {
      std::cerr << "<EMPTY>\n";
    }
    else
    {
      if (line != "\0")
      {
        line += ' ';
        std::string temp = "";
        for (std::size_t i = 0; i < line.size(); i++)
        {
          if (line[i] == ' ')
          {
            words.push_back(temp);
            temp = "";
          }
          else
          {
            temp += line[i];
          }
        }
      }
      std::map< std::string, std::function< void() > > commands(
        {
        {"list", std::bind(sviridenko::list, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"help", std::bind(sviridenko::help, std::ref(ostream), std::ref(words),
        std::ref(hist), std::ref(numberOfCommand))},
        {"find", std::bind(sviridenko::find, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"search", std::bind(sviridenko::search, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"clear", std::bind(sviridenko::clear, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"translate", std::bind(sviridenko::searchWithTranslate, std::ref(ostream),
        std::ref(words), std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"change_translation", std::bind(sviridenko::changeTranslation, std::ref(ostream),
        std::ref(words), std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"print", std::bind(sviridenko::print, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"delete", std::bind(sviridenko::deleteWord, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"insert", std::bind(sviridenko::insert, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"compare", std::bind(sviridenko::compare, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"merge", std::bind(sviridenko::merge, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(hist), std::ref(numberOfCommand))},
        {"history", std::bind(sviridenko::history, std::ref(ostream), std::ref(words),
        std::ref(hist), std::ref(numberOfCommand))},
        {"save_result", std::bind(sviridenko::save, std::ref(ostream), std::ref(words),
        std::ref(listOfDIcts), std::ref(argv[1]), std::ref(hist), std::ref(numberOfCommand))}
        });
      if (commands.find(words[0]) != commands.end())
      {
        commands.find(words[0])->second();
      }
      else
      {
        sviridenko::failedEnter(ostream);
      }
    }
  }
}
