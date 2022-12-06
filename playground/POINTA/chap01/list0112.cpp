#include <iostream>

using namespace std;

void swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

int main(void)
{
    int a, b;

    cout << "2つの整数を入力してください。\n";
    cout << "整数A : "; cin >> a;
    cout << "整数B : "; cin >> b;

    swap(a, b);

    cout << "整数AとBの値を交換しました。\n";
    cout << "A : " << a << "\n";
    cout << "B : " << b << "\n";
}