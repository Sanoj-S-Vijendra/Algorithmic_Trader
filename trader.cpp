#include "receiver.h"
#include <vector>
#define MAX 1000000000
#define MIN -999999999
using namespace std;
struct quad
{
    bool seen;
    int prices;
    int buy;
    int sell;
};
class MyHashMap {
    vector<quad> mapArray;
public:
    MyHashMap() {
        mapArray = vector<quad>(1000001, {0,0,MIN,MAX});
    }
    void put(int key, quad value) {
        mapArray[key] = value;
    }
    quad get(int key) {
        return mapArray[key];
    }
    void remove(int key) {
        mapArray[key] = {0,0,MIN,MAX};
    }
};
struct Offer
{
    string company;
    int price;
    string commit;
};
void part1(string message) {
    istringstream mess(message);
    vector<string> offers;
    string token;
    while (getline(mess, token, '\r'))
    {
        offers.push_back(token);
    }
    int l = offers.size();
    Offer received[l];
    for(int i=0; i<l; ++i)
    {
        istringstream rec(offers[i]);
        string token;
        int p = 0;
        while(getline(rec, token, ' '))
        {
            if(p==0) received[i].company = token;
            if(p==1) received[i].price = stoi(token);
            if(p==2)
            {
                if(token == "s#" || token == "s#$") received[i].commit = 's';
                if(token == "b#" || token == "b#$") received[i].commit = 'b';
            }
            p+=1;
        }
    }
    int t = 0;
    MyHashMap trades;
    while(t<l)
    {
        int k = 0;
        for(char ch: received[t].company)
        {
            k+=int(ch);
        }
        k = k%1000001;
        if(trades.get(k).seen==0)
        {
            quad u;
            u.seen = 1;
            u.prices = received[t].price;
            u.buy = MIN;
            u.sell = MAX;
            trades.put(k, u);
            if(received[t].commit == "s") cout<<received[t].company<<" "<<received[t].price<<" "<<"b\r";
            if(received[t].commit == "b") cout<<received[t].company<<" "<<received[t].price<<" "<<"s\r";
        }
        else
        {
            if(received[t].commit == "s")
            {
                int p = trades.get(k).prices;
                if(p <= received[t].price)
                {
                    if(received[t].price < trades.get(k).sell)
                    {
                        quad u;
                        u.prices = p;
                        u.seen = trades.get(k).seen;
                        u.buy = trades.get(k).buy;
                        u.sell = received[t].price;
                        trades.put(k,u);
                    }
                    cout<<"No Trade\r";
                }
                else if(p > received[t].price)
                {
                    if(received[t].price >= trades.get(k).sell && received[t].price != trades.get(k).buy) cout<<"No Trade\r";
                    else if(received[t].price == trades.get(k).buy && received[t].price >= trades.get(k).sell)
                    {
                        cout<<"No Trade\r";
                        quad u;
                        u.seen = trades.get(k).seen;
                        u.prices = trades.get(k).prices;
                        u.sell = trades.get(k).sell;
                        u.buy = MIN;
                        trades.put(k,u);
                    }
                    else if(received[t].price == trades.get(k).buy && received[t].price < trades.get(k).sell)
                    {
                        cout<<"No Trade\r";
                        quad u;
                        u.seen = trades.get(k).seen;
                        u.prices = trades.get(k).prices;
                        u.sell = MAX;
                        u.buy = MIN;
                        trades.put(k,u);
                    }
                    else
                    {
                        quad u;
                        u.seen = 1;
                        u.prices = received[t].price;
                        u.sell = trades.get(k).sell;
                        u.buy = trades.get(k).buy;
                        trades.put(k, u);
                        cout<<received[t].company<<" "<<received[t].price<<" "<<"b\r";
                    }
                }
            }
            if(received[t].commit == "b")
            {
                int p = trades.get(k).prices;
                if(p >= received[t].price)
                {
                    if(received[t].price > trades.get(k).buy)
                    {
                        quad u;
                        u.prices = p;
                        u.seen = trades.get(k).seen;
                        u.buy = received[t].price;
                        u.sell = trades.get(k).sell;
                        trades.put(k,u);
                    }
                    cout<<"No Trade\r";
                }
                else if(p < received[t].price)
                {
                    if(received[t].price <= trades.get(k).buy && received[t].price != trades.get(k).sell) cout<<"No Trade\r";
                    else if(received[t].price == trades.get(k).sell && received[t].price <= trades.get(k).buy)
                    {
                        cout<<"No Trade\r";
                        quad u;
                        u.seen = trades.get(k).seen;
                        u.prices = trades.get(k).prices;
                        u.sell = MAX;
                        u.buy = trades.get(k).buy;
                        trades.put(k,u);
                    }
                    else if(received[t].price > trades.get(k).buy && received[t].price == trades.get(k).sell)
                    {
                        cout<<"No Trade\r";
                        quad u;
                        u.seen = trades.get(k).seen;
                        u.prices = trades.get(k).prices;
                        u.sell = MAX;
                        u.buy = MIN;
                        trades.put(k,u);
                    }
                    else
                    {
                        quad u;
                        u.seen = 1;
                        u.prices = received[t].price;
                        u.sell = trades.get(k).sell;
                        u.buy = trades.get(k).buy;
                        trades.put(k, u);
                        cout<<received[t].company<<" "<<received[t].price<<" "<<"s\r";
                    }
                }
            }
        }
        t+=1;
    }
}
struct Offer2
{
    vector<string> arbitrage;
};
struct pair2
{
    string name;
    int hash_value;
};
void findSubsetsWithZeroSum(const std::vector<int>& arr, int index, int currentSum, std::vector<int>& currentSubset, std::vector<std::vector<int>>& result) {
    if (currentSum == 0 && !currentSubset.empty()) {
        result.push_back(currentSubset);
    }
    for (int i = index; i < arr.size(); ++i) {
        currentSubset.push_back(i);  // Include the current element
        findSubsetsWithZeroSum(arr, i + 1, currentSum + arr[i], currentSubset, result);
        currentSubset.pop_back();     // Backtrack and exclude the current element
    }
}
vector<vector<int>> formed_arbitrage(vector<vector<int>> a, vector<vector<int>> b)
{
    vector<vector<int>> arb;
    for(int i = 0; i < a.size(); i++)
    {
        bool t = 1;
        for(int j = 0; j < b.size(); j++)
        {
            int sum = 0;
            for(int k : a[i])
            {
                sum += b[j][k];
            }
            if(sum != 0) {t = 0; break;}
        }
        if(t == 1) arb.push_back(a[i]);
    }
    return arb;
}
int max_profit(vector<int> a, vector<vector<int>> b)
{
    int k;
    int max = -99999999;
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] > max) {max = a[i]; k = i;}
    }
    for(int i = 0; i < a.size(); ++i)
    {
        if(a[i] == a[k] && b[i].size() < b[k].size()) {k = i;}
    }
    return k;
}
// bool isSubset(const std::vector<int>& subset, const std::vector<int>& superset) {
//     for (const int& element : subset) {
//         bool found = false;
//         for (const int& superElement : superset) {
//             if (element == superElement) {
//                 found = true;
//                 break;
//             }
//         }
//         if (!found) {
//             return false;  // Element in the subset not found in the superset
//         }
//     }
//     return true;  // All elements in the subset are found in the superset
// }
void part2(string message)
{
    istringstream mess(message);
    vector<string> offers;
    string token;
    while (getline(mess, token, '\r'))
    {
        offers.push_back(token);
    }
    int l = offers.size();
    Offer2 received[l];
    vector<pair2> companies_hv;
    vector<vector<int>> companies_prices;
    for(int i=0; i<l; ++i)
    {
        istringstream rec(offers[i]);
        string token;
        while(getline(rec, token, ' '))
        {
            received[i].arbitrage.push_back(token);
        }
        int k = received[i].arbitrage.size();
        if(received[i].arbitrage[k-1]=="s#" || received[i].arbitrage[k-1]=="s#$")
        {
            for(int p = 1; p < k-1; p+=2)
            {
                if(received[i].arbitrage[p][0]== '-') received[i].arbitrage[p] = received[i].arbitrage[p].substr(1);
                else
                {
                    string g = "-";
                    received[i].arbitrage[p] = g + received[i].arbitrage[p];
                }
            }
            if(received[i].arbitrage[k-2][0]== '-') received[i].arbitrage[k-2] = received[i].arbitrage[k-2].substr(1);
            else
            {
                string g = "-";
                received[i].arbitrage[k-2] = g + received[i].arbitrage[k-2];
            }
        }
        for(int j = 0; j < k-2; j+=2)
        {
            int f = companies_hv.size();
            bool y = 0;
            for(int q = 0; q < f; q++)
            {
                if(companies_hv[q].name == received[i].arbitrage[j]) { y = 1; companies_prices[q].push_back(stoi(received[i].arbitrage[j+1])); break;}
            }
            if(y == 0) 
            {
                companies_hv.push_back({received[i].arbitrage[j],f});
                vector<int> u;
                for(int r = 0; r < i; r++)
                {
                    u.push_back(0);
                }
                companies_prices.push_back(u);
                companies_prices[f].push_back(stoi(received[i].arbitrage[j+1]));
            }
        }
        int f = companies_prices.size();
        for(int r = 0; r < f; r++)
        {
            if(companies_prices[r].size()<i+1) companies_prices[r].push_back(0);
        }
    }
    vector<std::vector<int>> result;
    vector<int> currentSubset;
    findSubsetsWithZeroSum(companies_prices[0], 0, 0, currentSubset, result);
    vector<vector<int>> arbitrage1 = formed_arbitrage(result, companies_prices);
    vector<int> profit;
    for(int i = 0; i < arbitrage1.size(); i++)
    {
        int sum = 0;
        for(int j : arbitrage1[i])
        {
            int k = received[j].arbitrage.size();
            sum += stoi(received[j].arbitrage[k-2]);
        }
        profit.push_back(sum);
    }
    int pro = max_profit(profit, arbitrage1);
    // vector<bool> subset;
    // int count = 0;
    // for(int i = 0; i < arbitrage1.size(); i++)
    // {
    //     bool t = isSubset(arbitrage1[i],arbitrage1[pro]);
    //     if(i == pro) {subset.push_back(0); count++;}
    //     else if(t == 1 && profit[i] > 0) {subset.push_back(1); count++;}
    //     else subset.push_back(0);
    // }
    int end = arbitrage1[pro][arbitrage1[pro].size()-1];
    for(int i = 0; i < end; i++)
    {
        cout<<"No Trade\n";
    }
    for(int i = arbitrage1[pro].size()-1; i >= 0; i--)
    {
        int k = received[arbitrage1[pro][i]].arbitrage.size();
        if(received[arbitrage1[pro][i]].arbitrage[k-1]=="s#" || received[arbitrage1[pro][i]].arbitrage[k-1]=="s#$")
        {
            for(int p = 1; p < k-1; p+=2)
            {
                if(received[arbitrage1[pro][i]].arbitrage[p][0]== '-') received[arbitrage1[pro][i]].arbitrage[p] = received[arbitrage1[pro][i]].arbitrage[p].substr(1);
                else
                {
                    string g = "-";
                    received[arbitrage1[pro][i]].arbitrage[p] = g + received[arbitrage1[pro][i]].arbitrage[p];
                }
            }
            if(received[arbitrage1[pro][i]].arbitrage[k-2][0]== '-') received[arbitrage1[pro][i]].arbitrage[k-2] = received[arbitrage1[pro][i]].arbitrage[k-2].substr(1);
            else
            {
                string g = "-";
                received[arbitrage1[pro][i]].arbitrage[k-2] = g + received[arbitrage1[pro][i]].arbitrage[k-2];
            }
            for(int p = 0; p < k-1; p++)
            {
                cout<<received[arbitrage1[pro][i]].arbitrage[p]<<" ";
            }
            cout<<"b\n";
        }
        if(received[arbitrage1[pro][i]].arbitrage[k-1]=="b#" || received[arbitrage1[pro][i]].arbitrage[k-1]=="b#$")
        {
            for(int p = 0; p < k-1; p++)
            {
                cout<<received[arbitrage1[pro][i]].arbitrage[p]<<" ";
            }
            cout<<"s\n";
        }
    }
    for(int i = end+1; i < offers.size(); i++)
    {
        cout<<"No Trade\n";
    }
    if(arbitrage1.size() != 0) cout<<profit[pro];
    else cout<<"0";
}
void part3(string message)
{
    istringstream mess(message);
    vector<string> offers;
    string token;
    while (getline(mess, token, '\r'))
    {
        offers.push_back(token);
    }
    int l = offers.size();
    Offer2 received[l];
    vector<pair2> companies_hv;
    vector<vector<int>> companies_prices;
    for(int i=0; i<l; ++i)
    {
        istringstream rec(offers[i]);
        string token;
        while(getline(rec, token, ' '))
        {
            received[i].arbitrage.push_back(token);
        }
        int k = received[i].arbitrage.size();
        if(received[i].arbitrage[k-1]=="s#" || received[i].arbitrage[k-1]=="s#$")
        {
            for(int p = 1; p < k-2; p+=2)
            {
                if(received[i].arbitrage[p][0]== '-') received[i].arbitrage[p] = received[i].arbitrage[p].substr(1);
                else
                {
                    string g = "-";
                    received[i].arbitrage[p] = g + received[i].arbitrage[p];
                }
            }
            if(received[i].arbitrage[k-3][0]== '-') received[i].arbitrage[k-3] = received[i].arbitrage[k-3].substr(1);
            else
            {
                string g = "-";
                received[i].arbitrage[k-3] = g + received[i].arbitrage[k-3];
            }
        }
        for(int j = 0; j < k-3; j+=2)
        {
            int f = companies_hv.size();
            bool y = 0;
            for(int q = 0; q < f; q++)
            {
                if(companies_hv[q].name == received[i].arbitrage[j]) { y = 1; companies_prices[q].push_back(stoi(received[i].arbitrage[j+1])); break;}
            }
            if(y == 0) 
            {
                companies_hv.push_back({received[i].arbitrage[j],f});
                vector<int> u;
                for(int r = 0; r < i; r++)
                {
                    u.push_back(0);
                }
                companies_prices.push_back(u);
                companies_prices[f].push_back(stoi(received[i].arbitrage[j+1]));
            }
        }
        int f = companies_prices.size();
        for(int r = 0; r < f; r++)
        {
            if(companies_prices[r].size()<i+1) companies_prices[r].push_back(0);
        }
    }
    vector<std::vector<int>> result;
    vector<int> currentSubset;
    findSubsetsWithZeroSum(companies_prices[0], 0, 0, currentSubset, result);
    vector<vector<int>> arbitrage1 = formed_arbitrage(result, companies_prices);
    vector<int> profit;
    for(int i = 0; i < arbitrage1.size(); i++)
    {
        int sum = 0;
        for(int j : arbitrage1[i])
        {
            int k = received[j].arbitrage.size();
            sum += stoi(received[j].arbitrage[k-2])*stoi(received[j].arbitrage[k-3]);
        }
        profit.push_back(sum);
    }
    int pro = max_profit(profit, arbitrage1);
    // vector<bool> subset;
    // int count = 0;
    // for(int i = 0; i < arbitrage1.size(); i++)
    // {
    //     bool t = isSubset(arbitrage1[i],arbitrage1[pro]);
    //     if(i == pro) {subset.push_back(0); count++;}
    //     else if(t == 1 && profit[i] > 0) {subset.push_back(1); count++;}
    //     else subset.push_back(0);
    // }
    int end = arbitrage1[pro][arbitrage1[pro].size()-1];
    for(int i = 0; i < end; i++)
    {
        cout<<"No Trade\n";
    }
    for(int i = arbitrage1[pro].size()-1; i >= 0; i--)
    {
        int k = received[arbitrage1[pro][i]].arbitrage.size();
        if(received[arbitrage1[pro][i]].arbitrage[k-1]=="s#" || received[arbitrage1[pro][i]].arbitrage[k-1]=="s#$")
        {
            for(int p = 1; p < k-2; p+=2)
            {
                if(received[arbitrage1[pro][i]].arbitrage[p][0]== '-') received[arbitrage1[pro][i]].arbitrage[p] = received[arbitrage1[pro][i]].arbitrage[p].substr(1);
                else
                {
                    string g = "-";
                    received[arbitrage1[pro][i]].arbitrage[p] = g + received[arbitrage1[pro][i]].arbitrage[p];
                }
            }
            if(received[arbitrage1[pro][i]].arbitrage[k-3][0]== '-') received[arbitrage1[pro][i]].arbitrage[k-3] = received[arbitrage1[pro][i]].arbitrage[k-3].substr(1);
            else
            {
                string g = "-";
                received[arbitrage1[pro][i]].arbitrage[k-3] = g + received[arbitrage1[pro][i]].arbitrage[k-3];
            }
            for(int p = 0; p < k-1; p++)
            {
                cout<<received[arbitrage1[pro][i]].arbitrage[p]<<" ";
            }
            cout<<"b#\n";
        }
        if(received[arbitrage1[pro][i]].arbitrage[k-1]=="b#" || received[arbitrage1[pro][i]].arbitrage[k-1]=="b#$")
        {
            for(int p = 0; p < k-1; p++)
            {
                cout<<received[arbitrage1[pro][i]].arbitrage[p]<<" ";
            }
            cout<<"s#\n";
        }
    }
    for(int i = end+1; i < offers.size(); i++)
    {
        cout<<"No Trade\n";
    }
    if(arbitrage1.size() != 0) cout<<profit[pro];
    else cout<<"0";
}
int main(int argc, char** argv)
{
    Receiver rcv;
    // sleep(5);
    std::string message = rcv.readIML();
    if(strcmp(argv[1],"1") == 0){
        part1(message);
    }
    if(strcmp(argv[1],"2")==0){
        part2(message);
    }
    if(strcmp(argv[1],"3")==0){
        part3(message);
    }
}
