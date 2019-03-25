//
//  main.cpp
//  urlCount
//
//  Created by Dedicatus on 2019/3/24.
//  Copyright © 2019 Dedicatus. All rights reserved.
//
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;
const unsigned mod = 1009;
const int topk = 100;

string numToStr(size_t num) {
    string ret;
    while (num) {
        ret.push_back((num&0xF) + 'a');
        num >>= 4;
    }
    return ret;
}

void cutDoc(const char urlDoc[]) {
    hash<string> BKDRhash;
    string str;
    ifstream fin(urlDoc);
    ofstream fout;
    while (fin >> str) {
        string docId = numToStr(BKDRhash(str)%mod + 1);
        fout.open(docId, ios::app);
        fout << str << endl;
        fout.close();
    }
}

using iter = unordered_map<string, size_t>::iterator;
struct cmp {
    bool operator()(iter a, iter b) {
        return a->second < b->second;
    }
};
vector<pair<string, size_t>> getTopK() {
    ifstream fin;
    unordered_map<string, size_t> mmp;
    for (size_t k = 1; k <= mod; ++k) {
        string docId = numToStr(k);
        fin.open(docId);
        if (fin.fail()) {
            fin.clear();
            continue;
        }
        string str;
        unordered_map<string, size_t> mp;
        while (fin >> str) {
            auto it = mp.find(str);
            if (it == mp.end())
                mp.insert(make_pair(str, 1));
            else
                it->second++;
        }
        priority_queue<iter, vector<iter>, cmp> q;
        for (iter i = mp.begin(); i != mp.end(); ++i) {
            q.push(i);
        }
        for (int i = 0; i < topk && !q.empty(); ++i) {
            iter tp = q.top();
            q.pop();
            //if (tp->second > 1)
              //  cout << tp->first << " " << tp->second << endl;
            auto it = mmp.find(tp->first);
            if (it == mmp.end())
                mmp.insert(*tp);
            else
                it->second += tp->second;
        }
        fin.close();
    }
    priority_queue<iter, vector<iter>, cmp> qq;
    for (iter i = mmp.begin(); i != mmp.end(); ++i) {
        qq.push(i);
    }
    vector<pair<string, size_t>> ret(topk);
    for (int i = 0; i < topk && !qq.empty(); ++i) {
        iter tp = qq.top();
        qq.pop();
        ret[i] = *tp;
    }
    return ret;
}


int main(int argc, const char * argv[]) {
    cutDoc("./100.txt");
    auto ans = getTopK();
    ofstream fout("./Answer");
    for (auto& a : ans) {
        fout << a.first << " " << a.second << endl;
    }
    return 0;
}
