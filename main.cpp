

#include <iostream>
#include <fstream>
#include<string>
using namespace std;

long int vocung = 0;
int weight[100][100]; // ma tran trong so
int V = 0;       // so diem trong do thi
int P[100];      // Tap hop diem tren duong di ngan nhat
bool isUsed[100]; 
int L[100]; // duong di ngan nhat tam thoi tu diem a toi diem hien tai
void readFile()
{
    ifstream inpFile;
    inpFile.open("inp3.txt");
    if (inpFile.is_open())
    {
        inpFile >> V; // 1st line

        for (int i = 1; i <= V; ++i)
        {
            for (int j = 1; j <= V; ++j)
            {
                int value;
                inpFile >> value;
                if (value >= 0)
                {
                    weight[i][j] = value;
                    vocung += value;
                }
                else
                {
                    cout << "Input Value <= 0";
                    return;
                }
            }
        }
    }
    else
    {
        throw string("error reading file");
    }

    inpFile.close();
}
void init(int &a, int &z)
{
    cout << "Nhap diem a ( 1<=a<=" << V << ") : ";
    cin >> a;
    cout << "Nhap diem z:( 1<=z<=" << V << ") : ";
    cin >> z;

    // gan cac phan tu = 0 ( i != j) = 1e9
    for (int i = 1; i <= V; ++i)
        for (int j = 1; j <= V; ++j)
        {
            if (i != j && weight[i][j] == 0)
                weight[i][j] = vocung;
        }

    // gan cac diem da di qua = false
    for (int i = 1; i <= V; ++i)
    {
        isUsed[i] = false;
        L[i] = vocung;
        P[i] = 0;
    }
    L[a] = 0; // a -> a = 0
}
void dijkstra(int &a, int &z)
{
    while (!isUsed[z])
    {
        int MIN = vocung;
        int index;
        for (int i = 1; i <= V; ++i) // tim min
        {
            if (!isUsed[i] && L[i] < vocung)
            {
                if (L[i] < MIN)
                {
                    MIN = L[i];
                    index = i;
                }
            }
        }
        if (MIN == vocung)
        {
            throw string("Path doesn't exist");
        }
        else if(MIN < vocung)
        {
            L[index] = MIN;
            isUsed[index] = true;
        }

        for (int j = 1; j <= V; ++j)
            if (!isUsed[j] && L[index] + weight[index][j] <= L[j])
            {
                L[j] = L[index] + weight[index][j];
                P[j] = index;
            }
    }
}
void result(int a, int z)
{
  
        cout << endl;
        cout << "Duong di ngan nhat co do dai : " << L[z] << endl;
        cout << "Cach di: " << endl;
        int i = z;
        cout << z;
        while (i != a)
        {
            cout << " <-- " << P[i];
            i = P[i];
        }
}
int main()
{
    int a, z;
    try
    {
        readFile();
        init(a, z);
        dijkstra(a, z);
    }
    catch(const string error)
    {
        cout<<error<<endl;
        system("pause");
        return 0;
    }    
    result(a, z);
    return 0;
}