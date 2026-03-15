// LAB1-BAI2.6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

const vector<double> ENGLISH_FREQ = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};

string normalizeText(const string& text) {
    string normalized = "";
    for (char c : text) {
        if (isalpha(c)) {
            normalized += toupper(c);
        }
    }
    return normalized;
}

double calculateIoC(const string& text) {
    int N = text.length();
    if (N <= 1) return 0.0;

    vector<int> counts(26, 0);
    for (char c : text) {
        counts[c - 'A']++;
    }
    double numer = 0;
    for (int count : counts) {
        numer += count * (count - 1);
    }
    return (26.0 * numer) / (N * (N - 1));
}

int findKeyLength(const string& ciphertext, int max_len = 20) {
    for (int period = 1; period <= max_len; ++period) {
        vector<string> slices(period, "");
        for (size_t i = 0; i < ciphertext.length(); ++i) {
            slices[i % period] += ciphertext[i];
        }

        double sum_ioc = 0;
        for (int i = 0; i < period; ++i) {
            sum_ioc += calculateIoC(slices[i]);
        }
        double avg_ioc = sum_ioc / period;
        if (avg_ioc > 1.6) {
            return period;
        }
    }
    return 0; 
}

double cosAngle(const vector<double>& x, const vector<double>& y) {
    double numerator = 0, lengthx2 = 0, lengthy2 = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        numerator += x[i] * y[i];
        lengthx2 += x[i] * x[i];
        lengthy2 += y[i] * y[i];
    }
    if (lengthx2 == 0 || lengthy2 == 0) return 0.0;
    return numerator / sqrt(lengthx2 * lengthy2);
}

string findKey(const string& ciphertext, int period) {
    string key = "";
    vector<string> slices(period, "");
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        slices[i % period] += ciphertext[i];
    }
    for (int i = 0; i < period; ++i) {
        string slice = slices[i];
        double max_cos = -1.0;
        char best_char = 'A';
        for (int shift = 0; shift < 26; ++shift) {
            vector<double> test_freq(26, 0.0);
            for (char c : slice) {
                int p = (c - 'A' - shift + 26) % 26;
                test_freq[p]++;
            }
            for (int j = 0; j < 26; ++j) {
                test_freq[j] /= slice.length();
            }
            double angle = cosAngle(test_freq, ENGLISH_FREQ);
            if (angle > max_cos) {
                max_cos = angle;
                best_char = (char)('A' + shift);
            }
        }
        key += best_char;
    }
    return key;
}

string decryptVigenere(const string& raw_ciphertext, const string& key) {
    string plaintext = "";
    int keyLen = key.length();
    int keyIndex = 0;

    for (char c : raw_ciphertext) {
        if (isalpha(c)) {
            bool isUpper = isupper(c);
            int p = toupper(c) - 'A';
            int k = key[keyIndex % keyLen] - 'A';
            int plainChar = (p - k + 26) % 26;

            if (isUpper) plaintext += (char)(plainChar + 'A');
            else plaintext += (char)(plainChar + 'a');

            keyIndex++;
        }
        else {
            plaintext += c;
        }
    }
    return plaintext;
}

int main() {
    string raw_ciphertext = "";
    string line;
    cout << "Nhap ciphertext:\n";

    while (getline(cin, line) && !line.empty()) {
        raw_ciphertext += line + "\n";
    }

    string normalizedText = normalizeText(raw_ciphertext);
    int period = findKeyLength(normalizedText, 20);
    if (period == 0) {
        cout << "Khong the tim thay do dai khoa phu hop.\n";
        return 1;
    }

    string found_key = findKey(normalizedText, period);
    string plaintext = decryptVigenere(raw_ciphertext, found_key);
    cout << "Khoa: " << found_key << endl;
    cout << "Giai ma: \n\n" << plaintext << endl;

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
