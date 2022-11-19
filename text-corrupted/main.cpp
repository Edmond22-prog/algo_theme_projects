#include <iostream>
#include <vector>

using namespace std;

// Declaration of functions
bool dict(string word)
{
  vector<string> words(26);

  words[0] = "je";
  words[1] = "suis";
  words[2] = "un";
  words[3] = "etudiant";
  words[4] = "de";
  words[5] = "master";
  words[6] = "1";
  words[7] = "tu";
  words[8] = "es";
  words[9] = "un";
  words[10] = "grand";
  words[11] = "bandit";
  words[12] = "laisse";
  words[13] = "tomber";
  words[14] = "et";
  words[15] = "boss";
  words[16] = "developpeur";
  words[17] = "fullstack";
  words[18] = "en";
  words[19] = "javascript";
  words[20] = "appelez";
  words[21] = "moi";
  words[22] = "😎";
  words[23] = "le";
  words[24] = "ordinateur";
  words[25] = ",";

  int i = 0;
  bool find = false;

  while (i < words.size() && !find)
  {
    if (words[i] == word)
    {
      find = true;
    }

    i += 1;
  }

  return find;
}

// Declaration of classes

class Text
{
private:
  string text;
  int length;
  vector<bool> table;
  vector<bool> indices;

public:
  Text(string text)
  {
    this->text = text;
    this->length = text.size();
    this->table = vector<bool>(this->length + 1);
    this->indices = vector<bool>(this->length + 1, false);
  }

  // Getters

  string getText()
  {
    return this->text;
  }

  int getLength()
  {
    return this->length;
  }

  vector<bool> getIndices()
  {
    return this->indices;
  }

  void textCorrupted()
  {
    bool b;
    int j;
    this->table[0] = true;

    for (int i = 1; i < this->length + 1; i++)
    {
      b = false;
      j = 0;

      while (j < i && !b)
      {
        string substring = this->text.substr(j, i - j);

        b = this->table[j] && dict(substring);
        j += 1;
      }

      this->table[i] = b;

      if (b)
      {
        this->indices[i] = true;
      }
    }
  }

  bool getResult()
  {
    return this->table[this->length];
  }

  string getCorrectText()
  {
    string correctText = "";

    for (int i = 1; i <= this->length; i++)
    {
      correctText += this->text[i - 1];

      if (this->indices[i])
      {
        correctText += " ";
      }
    }

    return correctText;
  }
};

int main()
{
  cout << endl
       << "================ Program of Text Corrupted ================" << endl
       << endl
       << endl;

  // Initialization of variables
  Text text = Text("jesuisunetudiantdemaster1etjesuisundeveloppeurfullstackjavascript");

  // Run the main algorithm to determine if the text is correct or not
  text.textCorrupted();

  // Get result
  string correctText = text.getCorrectText();

  cout << ">>>> The Text Corrupted" << endl
       << " - " << text.getText()
       << endl
       << endl;

  if (text.getResult()) {
    cout << ">>>> The Text is Correct" << endl
         << " - " << correctText
         << endl
         << endl;
  } else {
    cout << ">>>> The Text is Not Correct"
         << endl
         << endl;
  }

  return 0;
}