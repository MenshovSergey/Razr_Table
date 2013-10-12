#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

struct table {
	int number;
	long long min;
};
int ansl;
int ansr;
vector <long long> mas;
vector <long long> sum;
vector <vector<table>> minimum(18);
long long ans;
int deg;
int razn(int d){
	int p = 1;
	int count = 0;
	while (p <= d){
		p = p * 2;
		count++;
	}	
	if (count > 0){
	  count--;
	}
	return count;
}
void raz_table(){
	deg = razn(mas.size()- 1);
	table r;
	minimum[0].push_back(r);
	for (int i = 1; i < mas.size();i++){		
		r.min = mas[i];
		r.number = i;
		minimum[0].push_back(r);
	}	
	for (int j = 1; j <= deg; j++){
		minimum[j].push_back(r);
		for (int i = 1; (i + (1 << j)) <= mas.size(); i++){			
			int inmin = min(minimum[j - 1][i].min, minimum[j - 1][i + (1 << (j - 1))].min);
			int innumber;
			if (minimum[j - 1][i].min < minimum[j - 1][i + (1 << (j - 1))].min){
	    	   innumber =  minimum[j - 1][i].number;
		    } else {
			   innumber =  minimum[j - 1][i + (1 << (j - 1))].number;
		      }
			r.min = inmin;
			r.number = innumber;
			minimum[j].push_back(r);
		}
	}
}

void answer(int l, int r){
	if (r < l) {
		return;
	}
	if (r == l){
		if (ans < mas[l] * mas[l]){
			ans = mas[l] * mas[l];
			ansl = l;
			ansr = r;
		}
		return;
	}
	int degree = razn(r - l);
	int number;
	if (minimum[degree][l].min < minimum[degree][r - (1 << degree) + 1].min){
	    	number =  minimum[degree][l].number;
		} else {
			number =  minimum[degree][r - (1 << degree) + 1].number;
		}
	if (min(minimum[degree][l].min, minimum[degree][r - (1 << degree)+ 1].min) * (sum[r] - sum[l - 1]) > ans){
		ans = min(minimum[degree][l].min, minimum[degree][r - (1 << degree) + 1].min) * (sum[r] - sum[l - 1]);
		ansl = l;
		ansr = r;		
	}
	answer(l,number - 1);
	answer(number + 1,r);
}

int main(){
	int n;
	int x;
	cin >> n;
	mas.push_back(0);
	sum.push_back(0);
	for (int i = 0; i < n; ++i){
		cin >> x;
		mas.push_back(x);
		sum.push_back(sum[i] + x);
	}	
	raz_table();
	ans = -1;
	answer(1,n);
	cout << ans << endl;
	cout << ansl << ' ' << ansr;	
	cin >> n;
}
