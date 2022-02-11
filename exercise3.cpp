//
// Created by Bruger on 11-02-2022.
//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

vector<string> read_wordle_js(istream&& is)
{

    vector<string> words;
    auto word = string{};
    while (is) { // check for EOF and potential I/O errors
        if (is.peek() == '"') { // look for an opening quote
            is >> quoted(word); // read the word in quotes and remove quotes
            if (word.length() == 5 && // must be 5-letter word
                all_of(cbegin(word), cend(word), // all lower-case letters
                            [](char c) { return isalpha(c) && islower(c); }))
                words.push_back(word);
        } else
            is.get(); // skip one character
    }
    sort(begin(words), end(words));
    words.erase(unique(begin(words), end(words)), words.end());
    return words;
}
vector<string> filter(vector<string>&& words, const string& pattern)
{ /* your filtering implementation here */
    auto i {0}, j{0};
    auto c = pattern[i];
    while(i < pattern.size()){
        try {
            switch (c) {
                case '-':
                    i++;
                    words.erase(remove_if(words.begin(), words.end(),
                                          [=](const string &s) mutable {
                                              return s.find(pattern[i]) != string::npos;
                                          }), words.end());
                    break;
                case '+':
                    i++;
                    words.erase(remove_if(words.begin(), words.end(),
                                          [=](const string &s) mutable {
                                              return (s.find(pattern[i]) == string::npos) || (s[j] == pattern[i]);
                                          }), words.end());
                    break;
                default:
                    words.erase(remove_if(words.begin(), words.end(),
                                          [=](const string &s) mutable {
                                              return s[j] != pattern[i];
                                          }), words.end());
                    break;
            }
            c = pattern[++i];
            j++;
        }catch( const std::exception &e){

        }
    }
    return words;
}

int main()
{
    std::ifstream strem("wordle.js");
    if (!strem.is_open())
        std::cout << "failed to open " << "wordle.js" << '\n';
    const auto database = read_wordle_js(move(strem));/* read the database from the javascript file */
    auto words = database; // make a copy of the database
    auto guess = string{}; // allocate memory to store guess patterns
    while (words.size()>1) {
        cout << words.size() << " words remaining\n";
        bool good = true;
        do {
            cout << "Enter a guess pattern: ";
            cin >> guess;
            /* sanitize: set good to false if input fails to follow the pattern */
        } while (!good);
        words = filter(move(words), guess);
        for(auto i{0}; i < 10 && i < words.size(); i++){
            cout << "Try:" << words[i] << endl;
        }
    }
    if (words.size() == 1) {
        cout << "Congratulations: " << words.front() << "\n";
    } else {
        cerr << "Something got messed up :-(\n";
    }
}