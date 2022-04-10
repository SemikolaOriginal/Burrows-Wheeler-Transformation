#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
using std::sort;
using std::find;

#include <iterator>
using std::distance;

namespace BWT{

std::pair<string, int> encode(string s) {
    vector<string> BWT_table;
    for(unsigned int i = 0; i < s.size(); i++){
        BWT_table.push_back(s);

        s.insert(s.begin(), s[s.size() - 1]);
        s.pop_back();                
    }

    sort(
        BWT_table.begin(), 
        BWT_table.end(), 
        [](const string &a, const string &b){return a < b;}
    );

    string result = "";
    for(const auto& row: BWT_table){
        result += row[row.size() - 1];
    }

    int start_str_idx_in_sort = distance(
        BWT_table.begin(),
        find(BWT_table.begin(), BWT_table.end(), s)
    );

    return {result, start_str_idx_in_sort};
}

string decode(const string &s, const int& n) {
    if(n >= s.size() || s.empty())
      return "";
  
    vector<string> reverse_BWT_table(s.size(), string(s.size(), ' '));

    for(int step = s.size() - 1; step >= 0 ; step--){
        for(unsigned int line = 0; line < s.size(); line++){
            reverse_BWT_table[line].replace(step, 1, 1, s[line]);
        }
        sort(
            reverse_BWT_table.begin(), 
            reverse_BWT_table.end(),
            [](const string &a, const string &b){return a < b;}
        );
    }

    return reverse_BWT_table[n];
}
}