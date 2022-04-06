#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool sortvec(const pair<int, string> &a, const pair<int, string> &b){
    if(a.second == b.second)
        return (a.first < b.first);
    else
        return a.second > b.second;
}

int main(){

    map <string , string> m; // id e projeto
    map <string , int> m_freq;
    set <string> s; //ids
    vector <pair <int, string>> vec;

    string project, userid, str;

    do {

        getline(cin, str);

        if (isupper(str[0])){
            project = str;
            m_freq[project] = 0;
        }
        else if (islower(str[0])){ 
            userid = str;
            if(s.find(userid) == s.cend()){ // primeira vez se inscrevendo
                s.insert(userid); // insere o id no set
                m[userid] = project; 
                m_freq[project]++;
            }
            else if(m[userid] != project){ // se inscreveu em 2 projetos
                m_freq[m[userid]]--;
                m.erase(userid);
            }
        }

        if(str == "1") {

            //push todos os projetos para o vec

            for(auto it = m_freq.cbegin(); it != m_freq.cend(); ++it){
                vec.push_back(make_pair((*it).second, (*it).first));
            }

            sort(vec.begin(), vec.end(), sortvec);
            
            for (long unsigned int i = 0; i < vec.size(); i++) {
                if(vec[i].first >= 0)
                    cout << vec[i].second << " " << vec[i].first << endl;
            }

            m_freq.clear();
            vec.clear();
            m.clear();
            s.clear();
        }
        
    } while (str != "0");  

    return 0;
}
