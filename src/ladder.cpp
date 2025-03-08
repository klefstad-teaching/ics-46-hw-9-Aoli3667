#include "ladder.h"
#include <cstddef>
#include <cstdlib>
#include <iterator>

void error(string word1, string word2, string msg)
{
    cout << msg << " with the words: " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    if(std::abs((int)(str1.size() - str2.size())) > d) 
        return false;
    return true;
}

bool is_adjacent(const string& word1, const string& word2)
{
    int diff = 0;
    if(word1 == word2)
        return false;
    if(!edit_distance_within(word1, word2, 1)) 
        return false;

    size_t len1 = word1.size();
    size_t len2 = word2.size();
    //Same length case
    if(len1 == len2)
    {
        for (size_t i = 0; i < len1; ++i) {
            if (word1[i] != word2[i]) 
            {
                ++diff;
                if (diff > 1)
                    return false;
            }
        }
        return diff == 1;
    }
    //diff length case
    else
    {
        const std::string& longer = (len1 > len2) ? word1 : word2;
        const std::string& shorter = (len1 < len2) ? word1 : word2;

        size_t i = 0, j = 0;
        bool diff_found = false;
    
        while (i < longer.size() && j < shorter.size()) 
        {
            if (longer[i] != shorter[j]) 
            {
                if (diff_found) 
                    return false; 
                diff_found = true;
                ++i;
            } 
            else 
            {
                ++i;
                ++j;
            }
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_q;
    vector<string> result_vec;
    if(begin_word == end_word) 
    {
        error(begin_word, end_word, "Same begin and end");
        return {};
    }
    set<string> visited;
    result_vec.push_back(begin_word);
    ladder_q.push(result_vec);
    visited.insert(begin_word);

    while(!ladder_q.empty())
    {
        vector<string> curr = ladder_q.front();
        ladder_q.pop();
        string last_word = curr.back();
        for(string word : word_list)
        {
            if(visited.find(word) == visited.end() && is_adjacent(last_word, word))
            {
                visited.insert(word);
                vector<string> new_ladder = curr;
                new_ladder.push_back(word);
                if(word == end_word)
                    return new_ladder;
                ladder_q.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name)
{
    ifstream in (file_name);
    for (string word; in >> word;)
    {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.size() == 0)
    {
        cout << "No word ladder found." << endl;
        return;
    }

    for(string word : ladder)
    {
        cout << word << " ";
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}