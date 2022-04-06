#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct PROJECT{
    string name;
    int frequency;
}Project;

bool sortFunc(const pair<string, int> &a, const pair<string, int> &b){
    if(a.second == b.second) return (a.first < b.first);
    else return a.second > b.second;
}

int main(){
    string project, user, s;
    set<string> totalUsers;
    map<string, string> projectMap;
    // vector< pair<string, int> > frequency;
    map<string, int> frequencyMap;
    int nProjects = 0;
    getline(cin, s);
    while(s.compare("0") != 0){
        while(s.compare("1") != 0){
            if(s[0] < 91){ //capital letter tell its a project
                project = s;
                nProjects++;
                frequencyMap.insert(make_pair(project, 0));
            }else{
                user = s;
                if(totalUsers.find(user) == totalUsers.end()){ //wasnt in any project
                    totalUsers.insert(user);
                    projectMap.insert(make_pair(user, project));
                    frequencyMap[project]++;
                }else{ //user was already in a project
                    if(projectMap[user] != project){ //subscribed twice for same pj
                        frequencyMap[projectMap[user]]--;
                        projectMap.erase(user);
                    }
                }
            }
            getline(cin, s);
        }
        vector< pair<string, int> > frequencyVector;
        copy(frequencyMap.begin(), 
            frequencyMap.end(), 
            back_inserter(frequencyVector));
        sort(frequencyVector.begin(), 
            frequencyVector.end(),
            sortFunc); 
        // frequencyVector.pop_back();
        for(auto it=frequencyVector.begin(); it != frequencyVector.end(); it++){
            if((*it).second >= 0)
                cout << (*it).first << " " << (*it).second << endl;
        }
        projectMap.clear();
        frequencyVector.clear();
        frequencyMap.clear();
        totalUsers.clear();
            
        getline(cin, s);
    }
    

    return 0;
}