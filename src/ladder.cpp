#include "ladder.h"
#include <cstdlib>

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
    else
    {
        for(size_t i = 0, j = 0; i < word1.size() && j < word2.size(); i++, j++)
        {
            if(word1[i] != word2[j]) 
            {
                ++diff;
                if(word1.size() > word2.size()) i++;
                else if (word2.size() > word1.size()) j++;
            }
            if(diff > 1) 
                return false;
        }
    }
    return diff == 1;
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
    for(string word : ladder)
    {
        cout << word << " ";
    }
}

void verify_word_ladder()
{

}