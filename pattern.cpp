#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)

vector<int> kmp(string &s){ // ok
  int n = (int)s.length();
  vector<int> pi(n);

  for(int i = 1; i < n; i++) {
    int j = pi[i-1];
    while(j > 0 && s[i] != s[j])
      j = pi[j-1];

    if(s[i] == s[j])
      j++;
    pi[i] = j;
  }

  return pi;
}

bool period(int period_len, string &s){
  int n = s.size();

  for(int i = period_len; i < n; i++){
    if(s[i] != s[(i)%period_len]){
      //cout << "XD ";
      return false;
    }
  }

  return true;
}

int shortest_period(string &s){
  vector<int> pi = kmp(s);
  int n = s.size();

  vector<int> odnies(n);
  for(int x = 0; x < n; x++){
    if(pi[x] != 0){
      odnies[pi[x]-1]++; // or pi[x-1]
    }
  }

  int period_len = 0;
  vector<int> repeat(27);

  // search for a period
  for(int i = 0; i < n; i++){
    if(odnies[i] == 0) return 1;

    if(pi[i] == 0){
      period_len++;
      repeat[(int)s[i]-96] += odnies[i] - 1;
    } else {
      if(repeat[(int)s[i]-96] > 0){
        repeat[(int)s[i]-96]--;
        repeat[(int)s[i]-96] += odnies[i] - 1;
        period_len++;
      } else{
        break;
      }
    }
  }

  // DEBUG
  /*
  for(char x : s){
    cout << x << ' ';
  } cout << "\n";
  for(int x : pi){
    cout << x << ' ';
  } cout << "\n";
  for(int x : odnies){
    cout << x << ' ';
  } cout << "\n";
  cout << period_len << "\n";
  */
  if(period(period_len, s)){
    return n/period_len;
  } else{
    return 1;
  }
}

int main(){
  fastio;

  int t;
  cin >> t;
  
  while(t--){
    string s;
    cin >> s;
    cout << shortest_period(s) << "\n";
  }
}