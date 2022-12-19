#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

// takes two strings and returns the number of characters that overlap from the end of one word to the beginning of another
int NumberOfCharactersOverlap(string const& first, string const& second)
{
    int overlap_chars = 0;
    string first_modified = first; //to erase the 1st character every iteration

    for (int i = 0; i < first.length(); i++) {
        size_t found = second.find(first_modified); //finds the first occurence of first string

        if (found != string::npos) //if finds it somewhere, check if it's at the beginning (index 0)
        {
            if (found == 0)
            {
                return first_modified.length();
            }
            else //erase the first char if not at the beginning
            {
                first_modified.erase(0, 1);
            }
        }
        else //erase the first char if not found
        {
            first_modified.erase(0, 1);
        }
    }
    return overlap_chars;
}

// takes 2 strings, number of char overlap and squeezes 2 strings into 1
string SqueezeIntoOne(string const& first, string const& second, int overlap_chars)
{
    return first + second.substr(overlap_chars);
}

//takes a sentence and returns a vector of all words
vector<string> BuildWordsVector(string line)
{
    vector<string> words{};
    string delimiter = " ";
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != string::npos) {
        words.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    return words;
}

//print vector of strings
void PrintResult(vector<string> const& result)
{
    string result_sentence;
    for (auto str : result) {
        result_sentence += str + " ";
    }
    if (result_sentence.at(result_sentence.length() - 2) == ' ') {
        result_sentence.pop_back();
        cout << result_sentence << endl;
    }
    else {
        cout << result_sentence << endl;
    }
}

//print one word with correct formatting
void PrintOneWord(string const& line)
{
    if (line.at(line.length() - 1) == ' ') {
        cout << line << endl;
    }
    else {
        cout << line + " " << endl;
    }
}

//checks if the last character of the line is a trailing space
//to preserve that space in a last words and put in a vector
vector<string> CheckLastElementSpace(string line)
{
    vector<string> words{};
    if (line.at(line.length() - 1) == ' ') {
        words = BuildWordsVector(line);
        string needs_space = words.at(words.size() - 1) + " ";
        words.pop_back(); //deletes the last element that did not preserve the whitespace
        words.push_back(needs_space); //adds a new element with a whitespace
    }
    else {
        line += " ";
        words = BuildWordsVector(line);
    }
    return words;
}

//builds a new vector with squeezed and replaced words
vector<string> GetReplacedVector(vector<string> const& words)
{
    vector<string> result{};
    string first_word = words.at(0);
    for (int i = 0; i < words.size() - 1; ++i) {
        string second_word = words.at(i + 1);

        int char_overlap = NumberOfCharactersOverlap(first_word, second_word);
        if (char_overlap) {
            string squeezed = SqueezeIntoOne(first_word, second_word, char_overlap);
            first_word = squeezed;
            if (i == words.size() - 2) {
                result.push_back(first_word);
            }
        }
        else {
            result.push_back(first_word);

            first_word = second_word;
            if (i == words.size() - 2) {
                result.push_back(second_word);
                return result;
            }
        }
    }
    return result;
}

int main()
{   
    string line, new_word;
    while (std::getline(std::cin, line, '\n')) {
        try {
            vector<string> words = CheckLastElementSpace(line);
            vector<string> result_vector = GetReplacedVector(words);
            PrintResult(result_vector);
        }
        catch (std::out_of_range& e) {
            PrintOneWord(line);
        }
    }
    return 0;
}
// g++ -std=c++17 -Wall -Werror -Wpedantic main.cpp
