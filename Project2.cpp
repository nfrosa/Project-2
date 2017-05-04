using namespace std;
#include <iostream> 
#include <string> 
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <queue>
#include <stack>
//This code involves taking in an initial string and a hint string from user input, where the first
//inputted line is the initial string and the second is a hint string. 
//The output of this code is a combination of integers.
//This combination is the difference in the indices of each occurence of the hint string. 
//In addition to this, the output must be the longest common subsequence between the sequences
//of numbers.
vector<int> substring(string hint) {
	vector<int> substring;
	//finds the longest substring of the hint that repeats itself.
	// i.e. abcdeabc. substring would be abc
	//this is done with an array of integers denoting where substrings begin and end
	substring.resize(hint.length());
	int j = 0;
	for (int i = 1; i < hint.length();i++) {
		if (hint.at(i) == hint.at(j)) {
			j++;
			substring.at(i) = j;
		} else {
			if (j == 0) {
				//no substring in progress
				substring.at(i) = 0;
			}
			else {
				//if character isn't found but a substring was found before
				//j becomes the index before the substring was found, but i remains where it was
				j = substring.at(j - 1);
				i--;
			}

		}
	}
	return substring;
}
vector<int> getIndex(string str,string sub) {
	//getting a vector of the indexes of the hint string
	vector<int> indices;
	vector<int> subs = substring(sub);
	int j = 0; 
	int i = 0;
	while(i < str.length()){
		// i represents the index in the string ; j represents the index in the hint
		if (str.at(i) == sub.at(j)) {
			//a character in the hint is found, and i and j are incremented to reflect that
			i++;
			j++;
			//if j is the same size as the hint, the hint has been found
			if (j == sub.size()) {
				indices.push_back(i - j);
				j = subs.at(j - 1);
			}
		} else {
			if (j != 0) {
				//hint was not fully found
				j = subs.at(j - 1);	
			}
			else {
				i++;

			}
		}
	}
	return indices; 
}
void findCombination(vector<int> d) {
	//d is differences between indices
	//creating the same combination of differences but backwards
	vector<int> b;
	vector<int> combination;
	for (int i = d.size()-1; i >=0; i--) {
		b.push_back(d.at(i));
	}
	//using the longest common subsequence problem
	int dim = d.size();
	//making 2d array of values
	//for (int i = 0; i < d.size(); i++)
	//	cout << d.at(i) << " ";
	vector<vector<int>> combinations;
	combinations.resize(dim+1);
	for (int i = 0; i < dim + 1; i++)
		combinations[i].resize(dim + 1);
	for (int i = 1; i < dim + 1; i++) {
		for (int j = 1; j < dim + 1; j++) {
			//two cases
			if (d.at(i - 1) == b.at(j - 1)) {
				combinations[i][j] = combinations[i - 1][j - 1] + 1;
			} else {
				combinations[i][j] = max(combinations[i][j - 1], combinations[i - 1][j]);
			}
		}
	}
	//placing mutual values in vector
	int i = dim;
	int j = dim;
	while (i!= 0 || j!=0) {
		if (i == 0 || j == 0)
			break;
		//checking if any of the entries surrounding the current entry have a value less than it and if it is a corner on the graph
		if ((combinations[i][j] > combinations[i - 1][j - 1]) && 
			(combinations[i][j] != combinations[i - 1][j]) && 
			(combinations[i][j] != combinations[i][j - 1])) {
			combination.push_back(d.at(i-1));
			i--;
			j--;
		}
		//check if i and j is correct
		else {
			if (combinations[i][j - 1] > combinations[i - 1][j]) {
				j--;
			} else if (combinations[i][j - 1] < combinations[i - 1][j]){
				i--;
			}
			else if ((combinations[i][j - 1] == combinations[i][j])
				&& (combinations[i][j] == combinations[i - 1][j])
				&& (combinations[i][j - 1] == combinations[i - 1][j])
				&& (combinations[i][j] == combinations[i - 1][j - 1])) {
				i--;
				j--;
			}
			else if ((combinations[i][j - 1] == combinations[i][j])
				&& (combinations[i][j] == combinations[i - 1][j])) {
				i--;
			}
		}
	}
	//debugging
	for (int i = 0; i < combination.size(); i++)
		cout << combination.at(i) << " ";
	cout << endl;
	//for (int i = 0; i < dim + 1; i++) {
	//	for (int j = 0; j < dim + 1; j++) {
	//		cout << combinations[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}
int main() {
	string initial;
	getline(cin, initial);
	if (cin.fail()) {
		return -1;
		cin.clear();
		cin.ignore();
	}
	string hint;
	getline(cin, hint);
	if (cin.fail()) {
		return -1;
		cin.clear();
		cin.ignore();
	}
	vector<int> indices = getIndex(initial,hint);
	vector<int> differences;
	int curr = 0;
	if (!indices.empty())
		for (int i = 0; i < indices.size()-1; i++) {
			int curr =  indices.at(i+1) - indices.at(i) ;
			differences.push_back(curr);
		}
	//for (int i = 0; i < differences.size(); i++)
	//	cout << differences.at(i) << endl;
	if (differences.empty())
		cout << endl;
	else
		findCombination(differences);
	return 0;
}