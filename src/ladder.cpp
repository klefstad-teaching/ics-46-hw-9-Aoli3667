#include "ladder.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void error(string word1, string word2, string msg)
{
    cout << msg << " with the words: " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int diff = 0;
    if(std::abs((int)(str1.size() - str2.size())) > d) 
        return false;
    if(str1 == str2)
        return true;
    size_t len1 = str1.size();
    size_t len2 = str2.size();
    if(len1 == len2)
    {
        for (size_t i = 0; i < len1; ++i) 
        {
            if (str1[i] != str2[i]) 
            {
                ++diff;
                if (diff > d)
                    return false;
            }
        }
        return diff == d;
    }
    //diff length case
    else
    {
        const std::string& longer = (len1 > len2) ? str1 : str2;
        const std::string& shorter = (len1 < len2) ? str1 : str2;

        size_t i = 0, j = 0;
        bool diff_found = false;
    
        while (i < longer.size() && j < shorter.size()) 
        {
            if (longer[i] != shorter[j]) 
            {
                if (diff_found) 
                    return false; 
                if(diff >= d)
                    diff_found = true;
                ++diff;
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

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) 
{
    queue<vector<string>> ladder_q;
    unordered_set<string> word_list_set(word_list.begin(), word_list.end());
    
    if (begin_word == end_word) 
    {
        return {};
    }

    ladder_q.push({begin_word});
    word_list_set.erase(begin_word);  

    while (!ladder_q.empty()) 
    {
        int level_size = ladder_q.size();
        unordered_set<string> level_visited;

        for (int i = 0; i < level_size; i++) 
        {
            vector<string> curr = ladder_q.front();
            ladder_q.pop();
            string last_word = curr.back();

            for (size_t j = 0; j < last_word.size(); ++j) 
            {
                char original_char = last_word[j];

                // One-off 
                for (char c = 'a'; c <= 'z'; ++c) 
                {
                    if (c == original_char) 
                    {
                        continue;
                    }
                    
                    last_word[j] = c;

                    if (word_list_set.find(last_word) != word_list_set.end()) 
                    {
                        vector<string> new_ladder = curr;
                        new_ladder.push_back(last_word);

                        if (last_word == end_word) 
                        {
                            return new_ladder;
                        }

                        ladder_q.push(new_ladder);
                        level_visited.insert(last_word);
                    }
                }
                last_word[j] = original_char; 
            }

            // Deletion
            if (last_word.size() > 1) 
            {
                for (size_t j = 0; j < last_word.size(); ++j) 
                {
                    string deleted_word = last_word;
                    deleted_word.erase(j, 1);

                    if (word_list_set.find(deleted_word) != word_list_set.end()) 
                    {
                        vector<string> new_ladder = curr;
                        new_ladder.push_back(deleted_word);

                        if (deleted_word == end_word) 
                        {
                            return new_ladder;
                        }

                        ladder_q.push(new_ladder);
                        level_visited.insert(deleted_word);
                    }
                }
            }

            // Insertion
            for (size_t j = 0; j <= last_word.size(); ++j) 
            {
                for (char c = 'a'; c <= 'z'; ++c) 
                {
                    string inserted_word = last_word;
                    inserted_word.insert(inserted_word.begin() + j, c);

                    if (word_list_set.find(inserted_word) != word_list_set.end()) 
                    {
                        vector<string> new_ladder = curr;
                        new_ladder.push_back(inserted_word);

                        if (inserted_word == end_word) 
                        {
                            return new_ladder;
                        }

                        ladder_q.push(new_ladder);
                        level_visited.insert(inserted_word);
                    }
                }
            }
        }

        for (const string& word : level_visited) 
        {
            word_list_set.erase(word);
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
    cout << "Word ladder found: ";
    for(string word : ladder)
    {
        cout << word << " ";
    }
    cout << endl;
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