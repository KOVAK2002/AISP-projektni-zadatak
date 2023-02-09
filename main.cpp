#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <unordered_map>
#include <map>
#include <iomanip>

using std::map;
using std::string;
using std::vector;
using namespace std::literals;
using namespace std;
class Fraud
{
public:
    void get_top_values(int n);
    void get_min_values(int n);

    int stupac1;
    vector<string> stupac2;
    map<int, vector<string>> redci;
};

void printVector(vector<int> &data)
{
    for (const auto &it : data)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

int main()
{


    string fname="fraudTest.csv";




    vector<int> v1 = {5, 6, 7};
    map<int, vector<int>> data;
    data.insert(std::make_pair(1, v1));


    
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

       
                fstream file (fname, ios::in);
        if(file.is_open())
        {
        while(getline(file, line))
        {
        row.clear();
        
        stringstream str(line);
        
        while(getline(str, word, ','))
        row.push_back(word);
        content.push_back(row);
        }
        }
        else
        cout<<"Could not open the file\n";
        
        for(int i=1;i<17;i++)
        {
        for(int j=0;j<14;j++)
        {
        cout<<content[i][j]<<" ";
        }
        cout<<"\n";
        }

            





    for (auto it = data.begin(); it != data.cend(); it++)
    {
        std::cout << it->first << ": ";
        printVector(it->second);
    }
}

 
return 0;
}
