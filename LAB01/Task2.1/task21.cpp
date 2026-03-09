#include <bits/stdc++.h>
using namespace std;
string mahoa(string text, int key){
    string res="";
    key = key % 26;
    for(int i=0;i<text.size();i++){
        if(isupper(text[i])){
            res += char((text[i]-'A'+key)%26+'A');
        }
        else if(islower(text[i])){
            res += char((text[i]-'a'+key)%26+'a');
        }
        else{
            res += text[i];
        }
    }
    return res;
}

string giaima(string text, int key){
    string res="";
    key = key % 26;
    for(int i=0;i<text.size();i++){
        if(isupper(text[i])){
            res += char((text[i]-'A'-key+26)%26+'A');
        }
        else if(islower(text[i])){
            res += char((text[i]-'a'-key+26)%26+'a');
        }
        else{
            res += text[i];
        }
    }
    return res;
}
void bruteforce(string text){
    for(int key=0; key<26; key++){
        cout<<"Key "<<key<<" : "<<giaima(text,key)<<endl;
    }
}
int main(){
    int luachon;
    string text;
    int key;
    cout<<"1. Giai ma\n";
    cout<<"2. Ma hoa\n";
    cout<<"3. Bruteforce\n";
    cout<<"Nhap lua chon: ";
    cin>>luachon;
    cin.ignore();
    cout<<"Nhap text: ";
    getline(cin,text);
    if(luachon==1){
        cout<<"Nhap key: ";
        cin>>key;
        cout<<"Plaintext: "<<giaima(text,key);
    }
    else if(luachon==2){
        cout<<"Nhap key: ";
        cin>>key;
        cout<<"Ciphertext: "<<mahoa(text,key);
    }
    else if(luachon==3){
        bruteforce(text);
    }
    else{
        cout<<"Lua chon khong hop le";
    }
}