#include <bits/stdc++.h>
using namespace std;
int ucln(int a, int b) {
    if (b == 0) return a;
    return ucln(b, a % b);
}
int tim_nghich_dao(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
string chuan_hoa(string text) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) {
            res += toupper(c);
        }
    }
    return res;
}
string ma_hoa(string text, int a, int b) {
    string ket_qua = "";
    for (char c : text) {
        int p = c - 'A';
        int C = (a * p + b) % 26;
        ket_qua += char(C + 'A');
    }
    return ket_qua;
}
string giai_ma(string text, int a, int b) {
    string ket_qua = "";
    int a_nghich_dao = tim_nghich_dao(a, 26);
    for (char c : text) {
        int C = c - 'A';
        int p = (a_nghich_dao * (C - b + 26)) % 26;
        ket_qua += char(p + 'A');
    }
    return ket_qua;
}
int main() {
    int lua_chon;
    string van_ban;
    int a, b;
    cout << "chuong trinh affine cipher\n";
    cout << "1. ma hoa\n";
    cout << "2. giai ma\n";
    cout << "chon: ";
    cin >> lua_chon;
    cin.ignore();
    cout << "nhap van ban: ";
    getline(cin, van_ban);
    cout << "nhap khoa a: ";
    cin >> a;
    cout << "nhap khoa b: ";
    cin >> b;
    if (ucln(a, 26) != 1) {
        cout << "khoa a khong hop le (ucln(a,26) phai = 1)\n";
        return 0;
    }
    van_ban = chuan_hoa(van_ban);
    if (lua_chon == 1) {
        string cipher = ma_hoa(van_ban, a, b);
        cout << "ciphertext: " << cipher << endl;
    }
    else if (lua_chon == 2) {
        string plain = giai_ma(van_ban, a, b);
        cout << "plaintext: " << plain << endl;
    }
    return 0;
}