// LAB1-BAI2.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <regex>

using namespace std;

const int HILLS = 5;// boi vi la thuat toan leo doi nen co the thay doi so luong HILLS neu giai ma khong ra 
const int STAIRS_PER_HILL = 5000;

// Load trigrams tu file txt co san 
vector<double> loadTrigrams() {
    vector<double> fast_dict(17576, 0.0);
    ifstream file("trigrams.txt");
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        regex pattern(R"('([A-Z]{3})'\s*:\s*([0-9.eE+-]+))");
        sregex_iterator currentMatch(content.begin(), content.end(), pattern);
        sregex_iterator lastMatch;
        int count = 0;
        while (currentMatch != lastMatch) {
            smatch match = *currentMatch;
            string tri = match[1].str();
            double score = stod(match[2].str()); 

            int index = (tri[0] - 'A') * 676 + (tri[1] - 'A') * 26 + (tri[2] - 'A');
            fast_dict[index] = score;
            count++;
            currentMatch++;
        }
        cout << "Da nap " << count << " trigrams vao mang tra cuu." << endl;
    }
    else {
        cout << "Loi: Khong tim thay file 'trigrams.txt'!" << endl;
    }
    return fast_dict;
}

// Rate 50 hill ngau nhien bang ham nay 
double rate_hills(const string& ciphertext, const string& testkey, const vector<double>& fast_dict) {
    double rating = 0;

    char rev_map[256];
    for (int i = 0; i < 256; ++i) rev_map[i] = i;
    for (int i = 0; i < 26; ++i) {
        rev_map[(unsigned char)toupper(testkey[i])] = 'A' + i;
        rev_map[(unsigned char)tolower(testkey[i])] = 'A' + i;
    }

    for (size_t i = 0; i + 2 < ciphertext.length(); ++i) {
        char c1 = rev_map[(unsigned char)ciphertext[i]];
        char c2 = rev_map[(unsigned char)ciphertext[i + 1]];
        char c3 = rev_map[(unsigned char)ciphertext[i + 2]];

        if (isalpha((unsigned char)c1) && isalpha((unsigned char)c2) && isalpha((unsigned char)c3)) {
            int index = (toupper(c1) - 'A') * 676 + (toupper(c2) - 'A') * 26 + (toupper(c3) - 'A');
            rating += fast_dict[index];
        }
    }
    return rating;
}

// Ham show ket qua 
string final_result(const string& ciphertext, const string& testkey) {
    string result = "";
    result.reserve(ciphertext.size());
    char rev_map[256] = { 0 };
    for (int i = 0; i < 26; ++i) {
        rev_map[(unsigned char)toupper(testkey[i])] = 'a' + i;
        rev_map[(unsigned char)tolower(testkey[i])] = 'a' + i;
    }
    for (char c : ciphertext) {
        if (isalpha((unsigned char)c)) result += rev_map[(unsigned char)c];
        else result += c;
    }
    return result;
}

int main() {
    vector<double> fast_dict = loadTrigrams();

    ifstream file("2.2_cipher_text.txt");
    if (!file.is_open()) return 1;
    string ciphertext((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 25);

    string best_key = "";
    double best_rating = -1;

    cout << "\nBat dau tinh toan leo doi\n\n";

    for (int key_num = 1; key_num <= HILLS; ++key_num) {
        string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        shuffle(key.begin(), key.end(), gen);

        double hill_rating = rate_hills(ciphertext, key, fast_dict);
        int j = 0;

        while (j < STAIRS_PER_HILL) {
            int rand1 = distrib(gen);
            int rand2 = distrib(gen);
            while (rand2 == rand1) rand2 = distrib(gen);

            string new_key = key;
            swap(new_key[rand1], new_key[rand2]);

            double new_rating = rate_hills(ciphertext, new_key, fast_dict);

            if (new_rating > hill_rating) {
                hill_rating = new_rating;
                key = new_key;
                j = 0;
            }
            else {
                j++;
            }
        }

        if (hill_rating > best_rating) {
            best_key = key;
            best_rating = hill_rating;
        }

        cout << "Hill " << setw(2) << key_num << ": " << key
            << " | Score: " << fixed << setprecision(4) << hill_rating << endl;
    }

    cout << "Best key found: " << best_key << "\n\n";
    cout << final_result(ciphertext, best_key) << endl;

    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
