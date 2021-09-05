//////////////////////////////////////////
// Muhammed Uğur Yıldız
// 1306180005
// Date: 2021.11.05
// IDE: Visual Studio 2019
///////////////////////////////////////////
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include<iomanip>
#include <list>
#include <queue>
using namespace std;

int yol_count = 0;
string yol;
vector<string> yollar;

const char FileName[] = "input.txt";



void printpath(vector<int>& path)
{
	int size = path.size();
	for (int i = 0; i < size; i++) {
		yol += to_string(path[i]);
	}
	yol += "K";
	yollar.push_back(yol);
	yol.clear();
}


int isNotVisited(int x, vector<int>& path)
{
	int size = path.size();
	for (int i = 0; i < size; i++)
		if (path[i] == x)
			return 0;
	return 1;
}


void findpaths(vector<vector<int> >& g, int src,
	int dst, int v)
{

	queue<vector<int> > q;


	vector<int> path;
	path.push_back(src);
	q.push(path);
	while (!q.empty()) {
		path = q.front();
		q.pop();
		int last = path[path.size() - 1];


		if (last == dst)
			printpath(path);

		for (int i = 0; i < g[last].size(); i++) {
			if (isNotVisited(g[last][i], path)) {
				vector<int> newpath(path);
				newpath.push_back(g[last][i]);
				q.push(newpath);
			}
		}
	}
}



int main()
{
	int links = 0;
	int paths = 0;
	int c = 0;
	vector<string> bolum;
	vector<string> birinci;
	string line;
	string v1;
	string v2;
	string limiter = "->";
	string token;
	int k1 = 0;
	int k2 = 0;
	int e = 0;
	size_t pos = 0;

	int indeks = 0;
	ifstream my_file(FileName);


	if (my_file.is_open())
	{

		while (getline(my_file, line))
		{
			bolum.push_back(line);
			
			
		}
	}
	my_file.close();

	for (int i = 0; i < bolum.size(); i++) {
		if (bolum[i] == "Links:") {
			links = i;
			links++;
		}
		else if (bolum[i] == "Paths:") {
			paths = i;
		}
	}

	e = paths - links;


	stringstream ss(bolum[0]);
	while (ss.good()) {
		string substr;
		getline(ss, substr, ',');
		birinci.push_back(substr);
	}

	int i = 0;
	int j = 0;
	int V = 0;
	V = birinci.size();
	vector<vector<int> > g;
	g.resize(V);
	

	for (links; links < paths; links++) {
		while ((pos = bolum[links].find(limiter)) != std::string::npos) {
			token = bolum[links].substr(0, pos);
			v1 = token;
			v2 = bolum[links].erase(0, pos + limiter.length());
		}


		for (int k_count = 0; k_count < birinci.size(); k_count++) {
			if (v1 == birinci[k_count]) {
				k1 = k_count + 1;
			}
			else if (v2 == birinci[k_count]) {
				k2 = k_count + 1;
			}
		}
		
		g[k1-1].push_back(k2-1);
	

	}


	int f = 0;
	for (f; f < V; f++) {
		int t = 0;
		for (t; t < V; t++) {
			findpaths(g, f, t, V);
		}
		
	}

	vector<string> istenenyollar;
	paths++;
	for (paths; paths < bolum.size(); paths++) {
		istenenyollar.push_back(bolum[paths]);
	}
	
	string* refArr = yollar.data();
	int size = yollar.size();


	vector<string> tum_yollar;

	vector<string> nodelar; // A A B B B

	char* nodes;
	for (int i = 0; i < birinci.size(); i++) {
		string str_obj = birinci[i];
		nodes = &str_obj[0];
		int sizeOfArray = sizeof(nodes) / sizeof(nodes[0]);
		string harf;
		harf = nodes[0];
		nodelar.push_back(harf);
	}

	char* char_arr;
	
	string alinan;

	for (int i = 0; i < size; i++) {
		string str_obj = refArr[i];
		char_arr = &str_obj[0];
		int sizeOfArray = sizeof(char_arr) / sizeof(char_arr[0]);
		for (int j = 0; j < sizeOfArray; j++) {
			string harf;
			harf = char_arr[j];
			if (harf == "K") {
				break;
			}
			int alma = stoi(harf);
			alinan += nodelar[alma];
		}
		tum_yollar.push_back(alinan);
		alinan.clear();
	}



	sort(tum_yollar.begin(), tum_yollar.end());
	tum_yollar.erase(unique(tum_yollar.begin(), tum_yollar.end()), tum_yollar.end());


	string cikti;

	for (int a = 0; a < istenenyollar.size(); a++) {
		int flag = 0;
		for (int b=0; b < tum_yollar.size(); b++) {
			flag++;
			if (istenenyollar[a] == tum_yollar[b]) {
				cikti += istenenyollar[a] + " [YES]\n";
				flag = flag - 1;
				break;
			}
			else if (flag == tum_yollar.size()) {
				cikti += istenenyollar[a] + " [NO]\n";
			}
		}

	}

	ofstream cikti_file("output.txt");
	if (cikti_file.is_open())
	{
		cikti_file << cikti;
		cikti_file.close();
	}

	
	return 0;
}