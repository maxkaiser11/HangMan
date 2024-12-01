#include <array>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>
#include <conio.h>

// hangman game
// [[noreturn]]
const char* image1 =

R"( 
.----------------.  .----------------.  .----------------.  .----------------.  .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
| |    _______   | || |  _________   | || |      __      | || |  _______     | || |  _________   | |
| |   /  ___  |  | || | |  _   _  |  | || |     /  \     | || | |_   __ \    | || | |  _   _  |  | |
| |  |  (__ \_|  | || | |_/ | | \_|  | || |    / /\ \    | || |   | |__) |   | || | |_/ | | \_|  | |
| |   '.___`-.   | || |     | |      | || |   / ____ \   | || |   |  __ /    | || |     | |      | |
| |  |`\____) |  | || |    _| |_     | || | _/ /    \ \_ | || |  _| |  \ \_  | || |    _| |_     | |
| |  |_______.'  | || |   |_____|    | || ||____|  |____|| || | |____| |___| | || |   |_____|    | |
| |              | || |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'  '----------------' 
)"; // '\0'

const char* image2 = R"(
 .----------------.  .----------------.  .----------------.  .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. |
| |    ______    | || |      __      | || | ____    ____ | || |  _________   | |
| |  .' ___  |   | || |     /  \     | || ||_   \  /   _|| || | |_   ___  |  | |
| | / .'   \_|   | || |    / /\ \    | || |  |   \/   |  | || |   | |_  \_|  | |
| | | |    ____  | || |   / ____ \   | || |  | |\  /| |  | || |   |  _|  _   | |
| | \ `.___]  _| | || | _/ /    \ \_ | || | _| |_\/_| |_ | || |  _| |___/ |  | |
| |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |
| |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------' 
)";

// R "()" - R "delim1 delim2"

enum Difficulty {
    EASY = 7,
    MEDIUM = 5,
    HARD = 3
};

// prototypes
int randomWord(const std::vector<std::string>&);
void show(const std::string& chosen);
void update(char, std::string&, const std::string&, int&);

int main() {
    const char* BIG_TAB = "\t\t\t\t\t\t\t";
    char user_input;
    int lifes = 0;
    enum Difficulty easy = EASY;
    enum Difficulty medium = MEDIUM;
    enum Difficulty hard = HARD;
    bool running = true;
    bool start_game = false;
    int difficulty = 0;
    int chosen_difficulty;
    int key_space = 32;

    
    std::cout << image1 << std::endl;
    std::cout << image2 << std::endl;
    std::cout << BIG_TAB;
    std::cout << "Press Space to start a game\n";

    while (!start_game)
    {
        // TODO: Read user input to start the game (SpaceBar)
        char key = _getch();
        int value = key;

        if (value == key_space)
        {
            start_game = true;
        }
    }

    do
    {
        std::cout << "Choose a difficulty - Easy, Medium or Hard\n";
        std::cout << "1. Easy\n";
        std::cout << "2. Medium\n";
        std::cout << "3. Hard\n";
        std::cin >> chosen_difficulty;

        if (chosen_difficulty == 1 || chosen_difficulty == 2 || chosen_difficulty == 3)
            start_game = true;
    } while (!start_game);
  
    // appple, lion, starwars
    // 1) random to pick a word - function return a string word
    // while
    std::vector<std::string> words = { "apple", "lion", "starwars", "programming", "peanut", "car", "school" };
    int pos = randomWord(words);
    std::string chosen_word = words[pos];
    //std::cout << chosen_word;  - cheat code
    // _ _ _ _ _  apple - show() -> [[noreturn]]
    switch (chosen_difficulty)
    {
    case 1:
        lifes = EASY;
        if (chosen_word.size() > 5)
            ++lifes;
        std::cout << "You Have " << lifes << " Lifes. Good Luck!" << std::endl;
        break;
    case 2:
        lifes = MEDIUM;
        if (chosen_word.size() > 5)
            lifes += 2;
        std::cout << "You Have " << lifes << " Lifes. Good Luck!" << std::endl;
        break;
    case 3:
        lifes = HARD;
        if (chosen_word.size() > 5)
            lifes += 3;
        std::cout << "You Have " << lifes << " Lifes. Good Luck!" << std::endl;
        break;
    }
    std::string guess_word(chosen_word.size(), '_');
    show(guess_word);
    std::cout << "\n";
  

    while (running)
    {
        std::cin >> user_input;
        update(user_input, guess_word, chosen_word, lifes);
        show(guess_word);
        if (lifes <= 0)
        {
            std::cout << "\nYou ran out of Lifes!";
            running = false;
        }
        if (guess_word == chosen_word)
        {
            std::cout << "\nGood Job, You Won!";
            running = false;
        }
            
    }
    // string view
    // dissappear in windows

    return 0;
}

// definition

int randomWord(const std::vector<std::string>& words) {
    srand(time(0));
    return rand() % words.size();
}

void show(const std::string& chosen) {
    for (auto it = chosen.begin(); it < chosen.end(); ++it) {
        std::cout << *it;
    }
}

void update(char input, std::string& empty_word, const std::string& chosen_word, int& lifes)
{
    bool flag = false;
    for (int i = 0; i < chosen_word.size(); ++i)
    {
        if (input == chosen_word[i])
        {
            empty_word[i] = input;
            flag = true;
        }
    }
    if (flag == false)
    {
        --lifes;
    }
}
