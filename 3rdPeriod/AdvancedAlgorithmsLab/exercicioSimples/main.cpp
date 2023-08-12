#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct server{
	string name, ip;
};

int main(){
	//n: number of ips and servers
	//m: number of commands
 	int n, m;	
	cin >> n >> m;
	
	//reads all ips and stores in a vector of struct	
	vector<struct server> vec(n);
	for(int i = 0; i < n; i++)		
		cin >> vec[i].name >> vec[i].ip;		
	
	//then, for every command ip, print the corresponding server ip 	
	for(int i = 0; i < m; i++){
		string command, ip;
		cin >> command >> ip; 	
		cout << command << " " << ip;
		ip.pop_back();		
		for(int j = 0; j < n; j++)
			if(vec[j].ip.compare(ip) == 0)
				cout << " #" << vec[j].name << "\n";
	}
	return 0;
}
