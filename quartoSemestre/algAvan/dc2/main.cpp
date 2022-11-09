#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> playlist, int time, int begin, int end){
    int mid;
    while(begin < end){
        mid = (begin+end)/2;
        if(playlist[mid] < time)
            begin = mid + 1;
        else if(playlist[mid] >= time)
            end = mid;
    }
    return begin;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> playlist;
    int c, t;
    int time = 0;
    for(int i = 0; i < n; i++){
        cin >> c >> t;
        time += c * t;  
        playlist.push_back(time);
    }
    //cout << "size = " << playlist.size() << endl;
    //for(auto songs : playlist)
    //    cout << songs << " ";
    int v;
    for(int i = 0; i < m; i++){
        cin >> v;
        cout << binary_search(playlist, v, 0, playlist.size()-1) + 1<< endl;
    }
    return 0;
}
