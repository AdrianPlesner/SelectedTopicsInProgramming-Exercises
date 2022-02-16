//
// Created by Bruger on 11-02-2022.
//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<string> read_wordle_js(istream&& is) //is er en Base class for char input streams.
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
    sort(begin(words), end(words)); // Sortere elementerne i ascending rækkefølge
    words.erase(unique(begin(words), end(words)), words.end()); //Sletter dublicate ord?
    return words;
}

// Filter the database by removing words which do not match the guess pattern from the puzzle.
vector<string> filter(vector<string>&& words, const string& pattern)
{
    auto i {0}, j{0}; //Integers, der bliver initialiseret til 0
    auto c = pattern[i]; // Char, som bliver sat til første element af pattern
    while(i < pattern.size()){ // For hvert i, så længe i er mindre en længden af pattern
        try {
            switch (c) {
                case '-': //The character is absent, og ord der indeholder denne character er derfor ikke relevant.
                    i++; // Hvis strengen nu er "-a-r-ise, og man har det første element, så bliver der peget på "-", men vi skal bruge a
                    //remove_if: removes elements from a sequence using a predicate. 3 arguments
                    words.erase(remove_if(words.begin(), words.end(),
                                          [=](const string &s) mutable {
                                              return s.find(pattern[i]) != string::npos;
                                          }), words.end()); // Lambda-funktion, der returnere true hvis et ord indeholder denne character
                    break;
                case '+': // The character is present, but not in the right place
                    i++; // Hvis strengen nu er "+a+r+ise, og man har det første element, så bliver der peget på "-", men vi skal bruge a
                    //remove_if: removes elements from a sequence using a predicate. 3 arguments
                    words.erase(remove_if(words.begin(), words.end(),
                                          [=](const string &s) mutable {
                                              // Returnere true for ord, der enten ikke indeholder bogstavet, eller indeholder bogstavet, men i den specifikke position
                                              return (s.find(pattern[i]) == string::npos) || (s[j] == pattern[i]);
                                          }), words.end());
                    break;
                default: // The character is present and in the right place
                    //remove_if: removes elements from a sequence using a predicate. 3 arguments
                    //Der er ingen i++;, bogstaver som er på det rette sted, ikke har et - eller + prefix.
                    words.erase(remove_if(words.begin(), words.end(),
                                          //Lambda-funktion, der returnere true, hvis denne character ikke er i den specifikke posistion
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

bool sanitize(string& guess){
    auto entries {0};
    auto in {0};
    string result {};
    char c;
    while (entries < 5 && in < guess.size()){
        c = guess.at(in);
        switch (c){
            case '-':
                in++;
                c = guess.at(in);
                if(isalpha(c)){
                    result.append("-");
                    result.append(string{static_cast<char>(tolower(c))});
                } else{
                    return false;
                }
                in++;
                entries++;
                break;
            case '+':
                in++;
                c = guess.at(in);
                if(isalpha(c)){
                    result.append("+");
                    result.append(string{static_cast<char>(tolower(c))});
                } else{
                    return false;
                }
                in++;
                entries++;
                break;
            default:
                if(isalpha(c)){

                    result.append(string{static_cast<char>(tolower(c))});
                } else{
                    return false;
                }
                in++;
                entries++;
                break;
        }
    }
    if(in == guess.size()){
        guess = result;
        return true;
    }
    else{
        return false;
    }
}

void suggest(vector<string>& words){
    map<char, int> tf {};
    for(const auto& s : words){
        for(const auto& c : s){
            tf[c] += 1;
        }
    }
    vector<pair<string, int>> scores {};
    for(const auto& s: words){
        auto score {0};
        set<char> chars {};
        for(const auto& c : s){
            chars.insert(c);
        }
        for(const auto& c : chars){
            score += tf[c];
        }
        scores.emplace_back(s, score);
    }
    sort(scores.begin(), scores.end(),[](const pair<string, int>& a, const pair<string, int>& b){return b.second <= a.second;});
    auto flag {true};
    auto i {0};
    while(flag){
        cout << "Try: " << scores[i].first << " with score: " << scores[i].second << endl;
        cout << "One more word?";
        cin >> flag;
        i++;
    }
}

// Main function which asks the user for the guess pattern, applies the filter, displays one of the remaining valid words and asks for the next guess-pattern.
int main()
{
    std::ifstream strem("wordle.js"); // Loader databasen med ord
    if (!strem.is_open()) //Checker om den fejlede i at åbne databasen.
        std::cout << "failed to open " << "wordle.js" << '\n';
    const auto database = read_wordle_js(move(strem));/* read the database from the javascript file */
    auto words = database; // make a copy of the database
    auto guess = string{}; // allocate memory to store guess patterns
    while (words.size()>1) { // Et loop der kører så længe at listen af ord er større end 1.
        cout << words.size() << " words remaining\n";
        bool good = true;
        do {
            cout << "Enter a guess pattern: ";
            cin >> guess;
            /* sanitize: set good to false if input fails to follow the pattern */
            good = sanitize(guess);
        } while (!good);
        words = filter(move(words), guess); // Kalder suggest funktionen, som gør listen af ord mindre.
        suggest(words);

    }
    if (words.size() == 1) {
        cout << "Congratulations: " << words.front() << "\n";
    } else {
        cerr << "Something got messed up :-(\n";
    }
}