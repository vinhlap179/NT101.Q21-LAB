#include <bits/stdc++.h>
using namespace std;
string chuanhoa(string s) {
    string kq = "";
    for(char c : s) {
        if(isalpha(c)) {
            kq += toupper(c);
        }
    }
    return kq;
}
string taokhoalap(string text, string key) {
    string khoa = "";
    int j = 0;
    for(int i = 0; i < text.length(); i++) {
        khoa += key[j];
        j++;
        if(j == key.length()) {
            j = 0;
        }
    }
    return khoa;
}
string mahoa(string plaintext, string key) {
    string ciphertext = "";
    for(int i = 0; i < plaintext.length(); i++) {
        int p = plaintext[i] - 'A';
        int k = key[i] - 'A';
        char c = (p + k) % 26 + 'A';
        ciphertext += c;
    }
    return ciphertext;
}
string giaima(string ciphertext, string key) {
    string plaintext = "";
    for(int i = 0; i < ciphertext.length(); i++) {
        int c = ciphertext[i] - 'A';
        int k = key[i] - 'A';
        char p = (c - k + 26) % 26 + 'A';
        plaintext += p;
    }
    return plaintext;
}
int main() {
    string plaintext, key;
    cout << "nhap plaintext: ";
    getline(cin, plaintext);
    cout << "nhap key: ";
    getline(cin, key);
    plaintext = chuanhoa(plaintext);
    key = chuanhoa(key);
    string khoalap = taokhoalap(plaintext, key);
    string ciphertext = mahoa(plaintext, khoalap);
    string ketqua = giaima(ciphertext, khoalap);
    cout << "plaintext sau chuan hoa: " << plaintext << endl;
    cout << "khoa lap: " << khoalap << endl;
    cout << "ciphertext: " << ciphertext << endl;
    cout << "giai ma: " << ketqua << endl;
    return 0;
}