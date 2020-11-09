#include <iostream>

#include "flatmat.h"

using namespace std;

int main()
{
  Matrix<int> mat(5, 10);

  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      mat[i][j] = (10 * i) + j;
    }
  }

  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      cout << mat[i][j] << " ";
    }

    cout << endl;
  }

  return 0;
}