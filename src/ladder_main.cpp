#include "ladder.h"

void verify_word_ladder_main() 
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> result = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(result);
    result = generate_word_ladder("marty", "curls", word_list);
    print_word_ladder(result);
    result = generate_word_ladder("code", "data", word_list);
    print_word_ladder(result);
    result = generate_word_ladder("work", "play", word_list);
    print_word_ladder(result);
}

int main()
{
    vector<string> result = generate_word_ladder("car", "cheat", {"cat", "chat", "cheat"});
    print_word_ladder(result);
    cout << "finish" << endl;
    verify_word_ladder_main();
    verify_word_ladder();
}