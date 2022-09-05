#include "Commands.h"
void sviridenko::help(std::ostream& ostream, std::vector< std::string >& words,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 1)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  ostream << "list - вывод списка словарей\n";
  ostream << "clear {нужный словарь} - очистка словаря\n";
  ostream << "translate {слово} - перевести слово\n";
  ostream << "find {словарь} {слово} - присутствует ли слово в словаре?\n";
  ostream << "search {слово} - поиск словарей, в которых обнаружено слово\n";
  ostream << "change_translation {словарь} {слово} {новый перевод} - замена перевода слова в определенном словаре\n";
  ostream << "print {словарь} - вывести содержимое словаря\n";
  ostream << "delete {словарь} {слово} - удалить слово из словаря\n";
  ostream << "insert {словарь} {слово} {перевод} - добавить новое слово в словарь\n";
  ostream << "compare {первый словарь} {второй словарь} - сравнить первый словарь со вторым\n";
  ostream << "merge {первый словарь} {второй словарь} {название нового словаря}"
    "- объединение первого и второго словаря без повторений\n";
  ostream << "save_result - сохранить словари в файл\n";
  ostream << "history - Вывести историю команд\n";
}

void sviridenko::list(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 1)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  for (std::map< std::string,
    std::map< std::string, std::vector< std::string > > >::iterator it = listOfDIcts.begin();
    it != listOfDIcts.end(); it++)
  {
    ostream << it->first;
    std::map< std::string, std::map< std::string, std::vector< std::string > > >::iterator its = it;
    if (++its != listOfDIcts.end())
    {
      ostream << " ";
    }
  }
  ostream << "\n";
}

void sviridenko::find(std::ostream& ostream, std::vector< std::string >& words, std::map< std::string,
  std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 3 || listOfDIcts.find(words[1]) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string map = words[1];
  std::string word = words[2];
  std::map< std::string, std::vector< std::string > > needMap = listOfDIcts.find(map)->second;
  for (std::map< std::string, std::vector< std::string > >::iterator it = needMap.begin(); it != needMap.end(); it++)
  {
    if (it->first == word)
    {
      ostream << "<TRUE>\n";
      return;
    }
  }
  ostream << "<FLASE>\n";
}

void sviridenko::search(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 2)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string word = words[1];
  int number = 0;
  for (std::map< std::string, std::map< std::string,
    std::vector< std::string > > >::iterator it = listOfDIcts.begin(); it != listOfDIcts.end(); it++)
  {
    for (std::map<std::string, std::vector< std::string > >::iterator its = it->second.begin();
      its != it->second.end(); its++)
    {
      if (its->first == word)
      {
        if (number != 0)
        {
          ostream << " ";
        }
        ostream << it->first;
        number++;
      }
    }
  }
  if (number == 0)
  {
    ostream << "Нет словаря с таким содержимым";
  }
  ostream << "\n";
}

void sviridenko::clear(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 2 || listOfDIcts.find(words[1]) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string needMap = words[1];
  listOfDIcts.find(needMap)->second.clear();
}

void sviridenko::searchWithTranslate(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 2)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string word = words[1];
  bool isFind = false;
  for (std::map< std::string, std::map< std::string,
    std::vector< std::string > > >::iterator it = listOfDIcts.begin(); it != listOfDIcts.end(); it++)
  {
    for (std::map<std::string, std::vector< std::string > >::iterator its = it->second.begin();
      its != it->second.end(); its++)
    {
      if (its->first == word)
      {
        ostream << "В словаре " << it->first << ": ";
        int number = 0;
        for (std::vector< std::string >::iterator vit = its->second.begin(); vit != its->second.end(); vit++)
        {
          if (number != 0)
          {
            ostream << ", ";
          }
          ostream << *vit;
          number++;
        }
        isFind = true;
        ostream << "\n";
      }
    }
  }
  if (isFind == false)
  {
    ostream << "В словарях нет такого слова\n";
  }
}

void sviridenko::changeTranslation(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() < 3 && listOfDIcts.find(words[1]) == listOfDIcts.end() ||
    listOfDIcts.find(words[1])->second.find(words[2]) == listOfDIcts.find(words[1])->second.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string needDict = words[1];
  std::string word = words[2];
  words.erase(words.begin());
  words.erase(words.begin());
  words.erase(words.begin());
  listOfDIcts.find(needDict)->second.find(word)->second = words;
}

void sviridenko::print(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 2 || listOfDIcts.find(words[1]) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string needDict = words[1];
  ostream << "В " << listOfDIcts.find(needDict)->first << ":\n";
  for (std::map< std::string, std::vector< std::string > >::iterator it = listOfDIcts.find(needDict)->second.begin();
    it != listOfDIcts.find(needDict)->second.end(); it++)
  {
    ostream << it->first << " - ";
    int number = 0;
    for (std::vector< std::string >::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
    {
      if (number != 0)
      {
        ostream << ", ";
      }
      ostream << *vit;
      number++;
    }
    ostream << "\n";
  }
}

void sviridenko::deleteWord(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 3 || listOfDIcts.find(words[1]) == listOfDIcts.end() ||
    listOfDIcts.find(words[1])->second.find(words[2]) == listOfDIcts.find(words[1])->second.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string needDict = words[1];
  std::string word = words[2];
  listOfDIcts.find(needDict)->second.erase(listOfDIcts.find(needDict)->second.find(word));
}

void sviridenko::insert(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() < 3 || listOfDIcts.find(words[1]) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string needDict = words[1];
  std::string word = words[2];
  words.erase(words.begin());
  words.erase(words.begin());
  words.erase(words.begin());
  listOfDIcts.find(needDict)->second.insert({ word, words });
}

void sviridenko::compare(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 3 || listOfDIcts.find(words[1]) == listOfDIcts.end() ||
    listOfDIcts.find(words[2]) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string firstDict = words[1];
  std::string secondDict = words[2];
  std::map< std::string, std::vector< std::string > >::iterator itSecond = listOfDIcts.find(firstDict)->second.begin();
  for (std::map< std::string,
    std::vector< std::string > >::iterator itFirst = listOfDIcts.find(firstDict)->second.begin();
    itFirst != listOfDIcts.find(firstDict)->second.end(); itFirst++)
  {
    if (listOfDIcts.find(firstDict)->second.size() == listOfDIcts.find(secondDict)->second.size())
    {
      if (*itFirst == *itSecond)
      {
        itSecond++;
      }
      else
      {
        ostream << "<FALSE>\n";
        return;
      }
    }
    else
    {
      ostream << "<FALSE>\n";
      return;
    }
  }
  ostream << "<TRUE>\n";
}

void sviridenko::merge(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  if (words.size() != 4 || listOfDIcts.find(words[1]) == listOfDIcts.end() ||
    listOfDIcts.find(words[2]) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string firstDict = words[1];
  std::string secondDict = words[2];
  std::string newDict = words[3];
  std::map< std::string, std::vector< std::string > > thirdDict = listOfDIcts.find(firstDict)->second;
  for (std::map< std::string,
    std::vector< std::string > >::iterator it = listOfDIcts.find(secondDict)->second.begin();
    it != listOfDIcts.find(secondDict)->second.end(); it++)
  {
    if (std::find(listOfDIcts.find(secondDict)->second.begin(),
      listOfDIcts.find(secondDict)->second.end(), *it) != listOfDIcts.find(secondDict)->second.end())
    {
      thirdDict.insert({ it->first, it->second });
    }
  }
  listOfDIcts.insert({ newDict, thirdDict });
}

void sviridenko::history(std::ostream& ostream, std::vector< std::string >& words,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  for (std::map<int, std::vector< std::string > >::iterator it = hist.begin(); it != hist.end(); it++)
  {
    int num = 0;
    for (std::vector< std::string >::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
    {
      if (num != 0)
      {
        ostream << " ";
      }
      ostream << *vit;
      num++;
    }
    ostream << "\n";
  }
}

void sviridenko::save(std::ostream& ostream, std::vector< std::string >& words,
  std::map< std::string, std::map< std::string, std::vector< std::string > > >& listOfDIcts, char* arg,
  std::map<int, std::vector< std::string > >& hist, int& numberOfCommand)
{
  hist.insert({ numberOfCommand, words });
  numberOfCommand++;
  std::ofstream out;
  out.open(arg, std::ios::trunc);
  out.close();
  out.open(arg, std::ios::app);
  if (!out.is_open())
  {
    sviridenko::failedEnter(ostream);
  }
  for (std::map< std::string, std::map< std::string,
    std::vector< std::string > > >::iterator it = listOfDIcts.begin(); it != listOfDIcts.end(); it++)
  {
    out << "В словаре " << it->first << ":\n";
    for (std::map<std::string, std::vector< std::string > >::iterator its = it->second.begin();
      its != it->second.end(); its++)
    {
      int number = 0;
      out << its->first << " - ";
      for (std::vector< std::string >::iterator vit = its->second.begin(); vit != its->second.end(); vit++)
      {
        if (number != 0)
        {
          out << ", ";
        }
        out << *vit;
        number++;
      }
      out << "\n";
    }
  }
  out << "===================================================\n";
  out.close();
}
