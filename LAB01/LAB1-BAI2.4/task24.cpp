#include <bits/stdc++.h>
using namespace std;
char maTran[5][5];
string chuanhoakhoa(string khoa){
    string kq = "";
    set<char> daCo;
    for(char c : khoa){
        if(isalpha(c)){
            c = toupper(c);
            if(c == 'J') c = 'I';
            if(!daCo.count(c)){
                kq += c;
                daCo.insert(c);
            }
        }
    }
    for(char c = 'A'; c <= 'Z'; c++){
        if(c == 'J') continue;
        if(!daCo.count(c)){
            kq += c;
            daCo.insert(c);
        }
    }
    return kq;
}
void taomatran(string khoa){
    string k = chuanhoakhoa(khoa);
    int idx = 0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            maTran[i][j] = k[idx++];
        }
    }
}
void inmatran(){
    cout<<"Ma tran Playfair:\n";
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<maTran[i][j]<<" ";
        }
        cout<<endl;
    }
}
void timvitri(char c, int &hang, int &cot){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(maTran[i][j] == c){
                hang = i;
                cot = j;
                return;
            }
        }
    }
}
string chuanhoabanro(string text){
    string kq="";
    for(char c : text){
        if(isalpha(c)){
            c = toupper(c);
            if(c=='J') c='I';
            kq += c;
        }
    }
    string res="";
    for(int i=0;i<kq.length();i++){
        res+=kq[i];
        if(i+1<kq.length() && kq[i]==kq[i+1]){
            res+='X';
        }
    }
    if(res.length()%2!=0) res+='X';
    return res;
}
string mahoa(string text){
    string banRo = chuanhoabanro(text);
    string kq="";
    for(int i=0;i<banRo.length();i+=2){
        char a = banRo[i];
        char b = banRo[i+1];
        int r1,c1,r2,c2;
        timvitri(a,r1,c1);
        timvitri(b,r2,c2);

        if(r1==r2){
            kq+=maTran[r1][(c1+1)%5];
            kq+=maTran[r2][(c2+1)%5];
        }
        else if(c1==c2){
            kq+=maTran[(r1+1)%5][c1];
            kq+=maTran[(r2+1)%5][c2];
        }
        else{
            kq+=maTran[r1][c2];
            kq+=maTran[r2][c1];
        }
    }
    return kq;
}
string giaima(string text){
    string kq="";
    for(int i=0;i<text.length();i+=2){
        char a = text[i];
        char b = text[i+1];
        int r1,c1,r2,c2;
        timvitri(a,r1,c1);
        timvitri(b,r2,c2);
        if(r1==r2){
            kq+=maTran[r1][(c1+4)%5];
            kq+=maTran[r2][(c2+4)%5];
        }
        else if(c1==c2){
            kq+=maTran[(r1+4)%5][c1];
            kq+=maTran[(r2+4)%5][c2];
        }
        else{
            kq+=maTran[r1][c2];
            kq+=maTran[r2][c1];
        }
    }
    return kq;
}
int main(){
    string khoa;
    cout<<"Nhap khoa: ";
    getline(cin,khoa);
    taomatran(khoa);
    inmatran();
    int luaChon;
    cout<<"\n1. Ma hoa\n";
    cout<<"2. Giai ma\n";
    cout<<"Chon: ";
    cin>>luaChon;
    cin.ignore();
    if(luaChon==1){
        string text;
        cout<<"Nhap plaintext: ";
        getline(cin,text);
        cout<<"Ciphertext: "<<mahoa(text)<<endl;
    }
    else{
        string text;
        cout<<"Nhap ciphertext: ";
        getline(cin,text);
        cout<<"Plaintext: "<<giaima(text)<<endl;
    }
}