#include <lc-util.h>

class Spreadsheet {
public:
  vector<vector<int>> grid;

  Spreadsheet(int rows) {
    grid = vector(rows, vector<int>(26));
  }

  void setCell(string cell, int value) {
    int j = cell[0] - 'A';
    int i = stoi(cell.substr(1)) - 1;
    grid[i][j] = value;
  }

  void resetCell(string cell) {
    int j = cell[0] - 'A';
    int i = stoi(cell.substr(1)) - 1;
    grid[i][j] = 0;
  }

  int getValue(string formula) {
    int p = formula.find('+');
    string c1 = formula.substr(1, p - 1);
    string c2 = formula.substr(p + 1);
    return getCell(c1) + getCell(c2);
  }

  int getCell(string cell) {
    if ('A' <= cell[0] && cell[0] <= 'Z') {
      int j = cell[0] - 'A';
      int i = stoi(cell.substr(1)) - 1;
      return grid[i][j];
    } else {
      return stoi(cell);
    }
  }
};
