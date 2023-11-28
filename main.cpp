// importing relevent libraries and structs
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "node.h"

using namespace std;

// This function rectifies the line read by getline to split it into two strings of date and value

vector <string> From_line_to_desired(string s){

vector <string> res;

string insertion = "";
s += ' ';

// add to the vector if the character equal to a space 
for(int i = 0; i < s.length();i++){
    if (s[i] != ' '){
        insertion+=s[i];
    }
    else{
           res.push_back(insertion);
           insertion = "";
       
    }
}

return res;
}

// Heapify max function
void heapify_max(vector<Hnode>& arr, int n, int i) {

// declaring the parent, left, and right childs 
    int greatest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

// update if left child is greater 

    if (left < n && arr[left].value > arr[greatest].value) {
        greatest = left;
    }
// update if right child is greater

    if (right < n && arr[right].value > arr[greatest].value) {
        greatest = right;
    }

    if (greatest != i) {
        swap(arr[i], arr[greatest]);
        heapify_max(arr, n, greatest);
    }
}

// This function builds a maximum heap utilizing the heapify max algorithm
void build_max_heap(vector<Hnode>& arr) {
    int s = arr.size(); 
    for (int i = s / 2 - 1; i >= 0; i--) {
        heapify_max(arr, s, i);
    }
}

void heapify_min(vector<Hnode>& arr, int n, int i) {
    int smallest = i;
    int left_c = 2 * i + 1;
    int right = 2 * i + 2;

// update if left child is smaller
    if (left_c < n && arr[left_c].value < arr[smallest].value) {
        smallest = left_c;
    }
// update if right child is smaller
    if (right < n && arr[right].value < arr[smallest].value) {
        smallest = right;
    }

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapify_min(arr, n, smallest);
    }
}

// This function builds a minimum heap usign heapify min algorithm
void build_min_heap(vector<Hnode>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_min(arr, n, i);
    }
}

// This function the greastest or smallest element
// It receives two parameters the vector and a key to determine if we want to remove as a maximum or minimum value 
Hnode remove_by_k(vector<Hnode> &VecOfN , int k){
    Hnode res;
    // k = 1 for min heap
    if (k == 1 ){
        res = VecOfN[0];
        VecOfN.erase(VecOfN.begin());
        build_min_heap(VecOfN);
    }
    // k = 2 for max heap
    else if (k == 2){
        res = res = VecOfN[0];
        VecOfN.erase(VecOfN.begin());
        build_max_heap(VecOfN);
    }
    return res;
}
// This is a function to implement the maximum subsequent algorithm and return the indices of the 
double maxSubsequenceSum(vector<double>& differences, int& start, int& end) {
    double maxSum = 0;
    double currentSum = 0;
    start = 0;

    for (int i = 0; i < differences.size(); ++i) {
        currentSum += differences[i];
    // The current sum is negative this means it needs to be reset and the second element should be considered now
        if (currentSum < 0) {
            currentSum = 0;
            start = i + 1;
        }
    // if the current sum is greater than the maximum sum just assign current sum to maxSum 
        if (currentSum > maxSum) {
            maxSum = currentSum;
            end = i;
        }
    }

    return maxSum;
}

int main(){

// Declaring the variables
// The instance used in reading the data
ifstream in;
string x;
vector <vector<string>> vector_of_tokens;
vector <Hnode> vector_of_nodes_max;
vector <Hnode> vector_of_nodes_min;

vector <Hnode> vector_of_nodes_for_max_sub;
vector <double> differences;
int start=0, end=0;

// getting the data using getline
in.open("Input_data.txt");

while(getline(in,x)){

// skipping the first line "date value" 

if(x[0] == 'd'){continue;}

// passing the line to the rectifing function and adding it to the vector
vector <string> vec = From_line_to_desired(x);

// create a node to hold the data from the rectifying function
Hnode N;
N.date = vec[0]; N.value = stod(vec[1]); 
vector_of_tokens.push_back(vec);
vector_of_nodes_max.push_back(N);
vector_of_nodes_min.push_back(N);
vector_of_nodes_for_max_sub.push_back(N);
}

// computing the differences between each two years
for (int j = 0; j< vector_of_nodes_for_max_sub.size()-1;j++){
double diff_dash = vector_of_nodes_for_max_sub[j+1].value- vector_of_nodes_for_max_sub[j].value;
differences.push_back(diff_dash);
}

cout << "The value of the greatest change is "<<  maxSubsequenceSum(differences , start , end)<<"\nand the period of maximum increasing is between " << vector_of_nodes_for_max_sub[start].date << " and " << vector_of_nodes_for_max_sub[end+1].date << endl; 
cout << "\nMax values: \n";

// getting the greatest 10 exchange rates
// buidling the heap then call the remove function 10 times 

build_max_heap(vector_of_nodes_max);
for (int i = 0; i < 10; i++){
Hnode z = remove_by_k(vector_of_nodes_max,2);
cout << i+1 << ". Value: "<< z.value << "  Date: " << z.date<<endl;
}

// getting the least 10 exchange rates
// buidling the heap then call the remove function 10 times 

cout << "\nMin values: \n";
build_min_heap(vector_of_nodes_min);
for (int i = 0; i < 10; i++){
Hnode z = remove_by_k(vector_of_nodes_min,1);
cout << i+1 << ". Value: "<< z.value << "  Date: " << z.date<<endl;}
}