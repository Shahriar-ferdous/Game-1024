/* Author: Shahriar Ferdous
//Course: CSCI-135
//Instructor: Tong-Yi
//Assignment: Project 3A
Define constructors, destructor, and method print for Board.cpp"*/
#include "Board.hpp"
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
Board::Board(){
    max = 0;
    target = 32;
    numRows = 3;
    numCols = 3;
    panel = new int* [numRows];
    for(int i = 0; i < numRows; i++){
        panel[i] = new int [numCols];
    }
}
Board::Board(int m){
    max = 0;
    target = 32;
    if(m >= 1){
        numRows = m;
        numCols = m;
    }
    else{
        numRows = 3;
        numCols = 3;
    }
    panel = new int*[numRows];
    for(int i = 0; i < numRows; i++){
        panel[i] = new int [numCols];
    }
}
Board::Board(int m, int n){
    max = 0;
    target = 32;
    if(m >= 1 && n >= 1){
        numRows = m;
        numCols = n;
    }
    else{
        numRows = 3;
        numCols = 3;
    }
    panel = new int*[numRows];
    for(int i = 0; i < numRows; i++){
        panel[i] = new int [numCols];
    }
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            panel[i][j] = 0;
        }
    }
}   
Board::~Board(){
    for(int i = 0; i < numRows; i++){
        delete[] panel[i];
        panel[i] = NULL;
    }
    delete [] panel;
    panel = NULL;
}

void print_lines( int numCols){
    cout << "+";
    for(int i = 0; i < numCols; i++){
        cout << "----+";
    }
    cout << endl;
}
void Board::print() const{
    print_lines(numCols);
    for(int j = 0; j < numRows; j++){
        cout << "|";
        for(int i = 0; i < numCols; i++){
            if(panel[j][i]!= 0){
                cout << setw(4) << panel[j][i]<< "|";
            }
            else{
                cout << "    |";
            }
        }
        cout << endl;
        print_lines(numCols);

    }
}
int Board::getNumRows () const{
    return numRows;
}
int Board::getNumCols() const{
    return numCols;
}
int Board::getTarget()const{
    return target;
}
int Board::getMax()const{
    return max;
}
struct Location
{
 int row;
 int col;
};
bool Board:: noAdjacentSameValue() const{
    for (int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols-1; j++){
            if(panel[i][j] == panel[i][j+1]){
                return false;
            }
        }
    }
    for(int j = 0; j < numCols; j++){
        for(int i = 0; i < numRows-1; i++){
            if(panel[i][j] == panel[i+1][j]){
                return false;
            }
        }
    }
    if( max < target){
        return true;
    }
}

void Board::selectRandomCell(int& row, int& col){
    vector<Location>zeros;
    Location cell;
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            if(panel[i][j] == 0){
                cell.row = i;
                cell.col = j;
                zeros.push_back(cell);
            }
        }
    }
    if(zeros.size() > 0){
        int index = rand() % zeros.size();
        row = zeros[index].row;
        col = zeros[index].col;
        panel[row][col] = 1;
        print();

    }
     if(zeros.size() == 0 || zeros.size() == 1){
        if(noAdjacentSameValue()){
            if(max < target){
                cout << "Game over. Try again." << endl;
            }
            else{
                cout << "Congratulations!" << endl;
            }
            exit(0);
        }
        else{
            return;
        }
    }
}
void merge(vector<int>& result) {
    int i = 0;
    int size = result.size();

    while (i < size) {
        if (i + 1 < size && result[i] == result[i + 1]) {
            result[i] *= 2;
            result[i + 1] = 0;
            i += 2;
        } else {
            i += 1;
        }
    }
}
void Board::pressLeft() {
    for (int row = 0; row < numRows; row++) {
        vector<int> nonZeros;

        for (int col = 0; col < numCols; col++) {
            if (panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }

        merge(nonZeros);

        int col = 0;
        for (int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i]!= 0) {
                panel[row][col] = nonZeros[i];
                col++;
            }
        }

        for (int i = col; i < numCols; i++) {
            panel[row][i] = 0;
        }
    }

    int randRow, randCol;
    selectRandomCell(randRow, randCol);
}

void Board::pressRight() {
    for (int row = 0; row < numRows; row++) {
        vector<int> nonZeros;

        for (int col = numCols - 1; col >= 0; col--) {
            if (panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }

        merge(nonZeros);

        int col = numCols - 1;
        for (int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col--] = nonZeros[i];
            }
        }

        for (; col >= 0; col--) {
            panel[row][col] = 0;
        }
    }

    int randRow, randCol;
    selectRandomCell(randRow, randCol);
}

void Board::pressUp() {
    for (int col = 0; col < numCols; col++) {
        vector<int> nonZeros;

        for (int row = 0; row < numRows; row++) {
            if (panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }

        merge(nonZeros);

        int row = 0;
        for (int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col] = nonZeros[i];
                row++;
            }
        }

        for (int i = row; i < numRows; i++) {
            panel[i][col] = 0;
        }
    }

    int randRow, randCol;
    selectRandomCell(randRow, randCol);
}

void Board::pressDown() {
    for (int col = 0; col < numCols; col++) {
        vector<int> nonZeros;

        for (int row = numRows - 1; row >= 0; row--) {
            if (panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }

        merge(nonZeros);

        int row = numRows - 1;
        for (int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row--][col] = nonZeros[i];
            }
        }

        for (; row >= 0; row--) {
            panel[row][col] = 0;
        }
    }

    int randRow, randCol;
    selectRandomCell(randRow, randCol);
}
void Board::start(){
    int round = 1;
    int randrow1, randcol1;
    selectRandomCell(randrow1, randcol1);
    int randrow2, randcol2;
    selectRandomCell(randrow2, randcol2);
    char ch;
    while (true){
        ch = getchar();
        if (ch == 'S'){
            break;
        }
        if(ch == '\033'){
            getchar();
            switch (getchar()){
                case 'A':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press UP. " << "Goal: " << target << endl;
                    pressUp();
                    round ++;
                    break;
                case 'B':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press DOWN. " << "Goal: " << target << endl;
                    pressDown();
                    round ++;
                    break;
                case 'C':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press RIGHT. " << "Goal: " << target << endl;
                    pressRight();
                    round ++;
                    break;
                case 'D':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press LEFT. " << "Goal: " << target << endl;
                    pressLeft();
                    round ++;
                    break;
            }
            max = 0;
            for(int i = 0; i < numRows; i++){
                for(int j = 0; j < numCols; j++){
                    if(panel[i][j] > max){
                        max = panel[i][j];
                    }
                }
            }
            if(max >= target){
                cout << "Congratulation!" << endl;
                break;
            }

        }

    }
}