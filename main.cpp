// 21-45001-2 Compiler Design [A]
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

map<string, bool> keywords;
map<char, bool> punctuations;
map<string, bool> operators;

vector<string> tokenizedKeywords;
vector<char> tokenizedPunctuations;
vector<string> tokenizedConstants;
vector<string> tokenizedOperators;
vector<string> tokenizedIdentifiers;

void setKeywords()
{
    keywords["asm"] = true;
    keywords["bool"] = true;
    keywords["string"] = true;
    keywords["namespace"] = true;
    keywords["include"] = true;
    keywords["main"] = true;
    keywords["using"] = true;
    keywords["std"] = true;
    keywords["double"] = true;
    keywords["new"] = true;
    keywords["switch"] = true;
    keywords["auto"] = true;
    keywords["if"] = true;
    keywords["else"] = true;
    keywords["operator"] = true;
    keywords["template"] = true;
    keywords["break"] = true;
    keywords["enum"] = true;
    keywords["private"] = true;
    keywords["this"] = true;
    keywords["case"] = true;
    keywords["extern"] = true;
    keywords["protected"] = true;
    keywords["throw"] = true;
    keywords["catch"] = true;
    keywords["float"] = true;
    keywords["public"] = true;
    keywords["try"] = true;
    keywords["char"] = true;
    keywords["for"] = true;
    keywords["register"] = true;
    keywords["typedef"] = true;
    keywords["class"] = true;
    keywords["friend"] = true;
    keywords["return"] = true;
    keywords["union"] = true;
    keywords["const"] = true;
    keywords["goto"] = true;
    keywords["short"] = true;
    keywords["unsigned"] = true;
    keywords["continue"] = true;
    keywords["ifsignedvirtual"] = true;
    keywords["default"] = true;
    keywords["inline"] = true;
    keywords["sizeofvoid"] = true;
    keywords["delete"] = true;
    keywords["int"] = true;
    keywords["static"] = true;
    keywords["volatile"] = true;
    keywords["do"] = true;
    keywords["long"] = true;
    keywords["struct"] = true;
    keywords["while"] = true;
    keywords["cout"] = true;
    keywords["cin"] = true;
}

bool isKeyword(string s)
{
    return keywords[s];
}

void setPunctuations()
{
    punctuations['('] = true;
    punctuations[')'] = true;
    punctuations['{'] = true;
    punctuations['{'] = true;
    punctuations['['] = true;
    punctuations[']'] = true;
    punctuations[';'] = true;
    punctuations[':'] = true;
    punctuations[','] = true;
    punctuations['.'] = true;
}

bool isPunctuation(char c)
{
    return punctuations[c];
}

void setOperators()
{
    operators["+"] = true;
    operators["-"] = true;
    operators["/"] = true;
    operators["*"] = true;
    operators["^"] = true;
    operators["%"] = true;
    operators["!"] = true;
    operators["|"] = true;
    operators["||"] = true;
    operators["&"] = true;
    operators["&&"] = true;
    operators["<"] = true;
    operators[">"] = true;
    operators["="] = true;
    operators["=="] = true;
    operators["<="] = true;
    operators[">="] = true;
    operators["!="] = true;
    operators["+="] = true;
    operators["-="] = true;
    operators["/="] = true;
    operators["*="] = true;
    operators["%="] = true;
    operators["^="] = true;
    operators["&="] = true;
    operators["|="] = true;
    operators["++"] = true;
    operators["--"] = true;
    operators["<<"] = true;
    operators[">>"] = true;
}

bool isOperator(string s)
{
    return operators[s];
}

vector<string> splitString(string s)
{
    vector<string> result;
    string word;
    for (char c : s)
    {
        if (c == ' ')
        {
            if (!word.empty())
            {
                result.push_back(word);
                word.clear();
            }
        }
        else
        {
            word += c;
        }
    }
    if (!word.empty())
    {
        result.push_back(word);
    }
    return result;
}
string getStringWithoutSemiAndParentheses(string s)
{
    string newString = "";
    for (char c : s)
    {
        if (c != ';' && c != '(' && c != ')')
        {
            newString += c;
        }
    }
    return newString;
}
bool isStringConstant(string s)
{
    string newString = "";
    for (char c : s)
    {
        if (!isPunctuation(c))
        {
            newString += c;
        }
    }
    return newString[0] == '"' && newString[newString.length() - 1] == '"';
}

bool isIdentifierValid(string s)
{
    if (isKeyword(s))
    {
        return false;
    }

    if (s == "_")
    {
        return false;
    }

    if (s[0] != '_' && !(s[0] >= 'A' && s[0] <= 'Z') && !(s[0] >= 'a' && s[0] <= 'z'))
    {
        return false;
    }

    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] != '_' && !(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= '0' && s[i] <= '9'))
        {

            return false;
        }
    }

    return true;
}

string getStringWithAlphabets(string s)
{
    string newString = "";
    for (char c : s)
    {
        if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        {
            newString += c;
        }
    }

    return newString;
}

void tokenizeKeywords()
{
    string inputLine;
    ifstream filerReader("lex_input.txt");

    while (getline(filerReader, inputLine))
    {
        vector<string> parsedWords = splitString(inputLine);
        for (string word : parsedWords)
        {
            string wordWithoutPunctuation = getStringWithAlphabets(word);
            if (isKeyword(wordWithoutPunctuation))
            {
                tokenizedKeywords.push_back(wordWithoutPunctuation);
            }
        }
    }

    filerReader.close();
}

void tokenizeStringConstants()
{
    string inputLine;
    ifstream filerReader("lex_input.txt");

    while (getline(filerReader, inputLine))
    {
        vector<string> parsedWords = splitString(inputLine);
        for (string word : parsedWords)
        {
            string newWord = getStringWithoutSemiAndParentheses(word);
            if (isStringConstant(newWord))
            {
                tokenizedConstants.push_back(newWord);
            }
        }
    }

    filerReader.close();
}

void tokenizeOperators()
{
    string inputLine;
    ifstream filerReader("lex_input.txt");

    while (getline(filerReader, inputLine))
    {
        vector<string> parsedWords = splitString(inputLine);
        for (string word : parsedWords)
        {

            if (isOperator(word))
            {
                tokenizedOperators.push_back(word);
            }
        }
    }

    filerReader.close();
}

void tokenizePunctuations()
{
    string inputLine;
    ifstream filerReader("lex_input.txt");

    while (getline(filerReader, inputLine))
    {
        vector<string> parsedWords = splitString(inputLine);
        for (string word : parsedWords)
        {
            for (char c: word){
                if(isPunctuation(c)){
                    tokenizedPunctuations.push_back(c);
                }
            }
        }
    }

    filerReader.close();
}

void tokenizeIdentifiers()
{
    string inputLine;
    ifstream filerReader("lex_input.txt");

    while (getline(filerReader, inputLine))
    {
        vector<string> parsedWords = splitString(inputLine);
        for (string word : parsedWords)
        {
            if (isIdentifierValid(word))
            {
                tokenizedIdentifiers.push_back(word);
            }
        }
    }

    filerReader.close();
}

void tokenizeNumericConstants()
{
    string inputLine;
    ifstream filerReader("lex_input.txt");

    while (getline(filerReader, inputLine))
    {
        vector<string> parsedWords = splitString(inputLine);
        for (string word : parsedWords)
        {
            string newWord = getStringWithoutSemiAndParentheses(word);
            try
            {
                stoi(newWord);
                tokenizedConstants.push_back(newWord);
            }
            catch (invalid_argument &e)
            {
            }
        }
    }

    filerReader.close();
}


int main()
{
    setKeywords();
    setPunctuations();
    setOperators();

    string inputLine;
    ifstream filerReader("lex_input.txt");
    getline(filerReader, inputLine);
    if (splitString(inputLine)[0] != "#include")
    {
        cout << "Not A Valid File" << "\n";
        return 0;
    }
    filerReader.close();

    tokenizeKeywords();
    cout << "Tokenized Keywords: ";
    for (string s : tokenizedKeywords)
    {
        cout << s << ", ";
    }
    cout << "\n";

    tokenizeNumericConstants();
    tokenizeStringConstants();
    cout << "Tokenized Constants: ";
    for (string s : tokenizedConstants)
    {
        cout << s << ", ";
    }
    cout << "\n";

    tokenizeOperators();
    cout << "Tokenized Operators: ";
    for (string s : tokenizedOperators)
    {
        cout << s << ", ";
    }
    cout << "\n";

    tokenizePunctuations();
    cout << "Tokenized Punctuations: ";
    for (char s : tokenizedPunctuations)
    {
        cout << s << ", ";
    }
    cout << "\n";

    tokenizeIdentifiers();
    cout << "Tokenized Identifiers: ";
    for (string s : tokenizedIdentifiers)
    {
        cout << s << ", ";
    }
    cout << "\n";

    return 0;
}
