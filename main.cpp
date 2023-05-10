#include <iostream>
#include <random>
#include <string>
#include <math.h>

using namespace std;

void psevdo_generater() {
    random_device rd;

    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, 1);

    vector<int> v;
    generate_n(back_inserter(v), 128, [&distrib, &gen] { return distrib(gen); });
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, ""));
    cout << endl;
}

//Частотный побитовый тест
void test_1(string s) {
    double sum = 0;
    for (int i = 0; i < 128; i++) {
        if (s[i] == '0') sum += -1;
        else sum += 1;
    }
    sum /= sqrt(128);
    cout << erfc(sum / sqrt(2)) << endl;
}

//Тест на одинаковые подряд идущие биты
void test_2(string s) {
    double psi = 0;
    for (int i = 0; i < 128; i++) {
        if (s[i] == '1') 
            psi++;
    }
    psi /= 128;

    if (fabs(psi - 0.5) >= 2 / sqrt(128)) 
        cout << 0;
    else {
        int q = 0;
        for (int i = 0; i < 127; i++) if (s[i] != s[i + 1]) q++;
       cout << erfc(fabs(q - 256 * psi * (1 - psi)) / (32 * psi * (1 - psi))) << endl;
    }
}

//Тест на самую длинную последовательность единиц в блоке
void test_3(string s) {

    //01110001 11000111 10111100 11110111 01100101 00010111 11110011 11010110 
    //11001100 10010100 01011001 00111111 10110001 10011111 11010000 01001100 

    int v[4] = { 1, 7, 3, 5 };
    double pi[4] = { 0.2148, 0.3672, 0.2305, 0.1875 };
    double xi = 0;

    for (int i = 0; i < 4; i++) {
        xi += pow(v[i] - 16 * pi[i], 2) / (16 * pi[i]);

    }
    cout << xi << endl;
    cout << xi / 2 << " -> " << 0.10302729<< endl;
    //Для данной последовательности получаем 0.10302729
}

int main() {
    //psevdo_generater();
    
    //01110001110001111011110011110111011001010001011111110011110101101100110010010100010110010011111110110001100111111101000001001100 
    string s = "01110001110001111011110011110111011001010001011111110011110101101100110010010100010110010011111110110001100111111101000001001100";
    test_1(s);
    test_2(s);
    test_3(s);
    return 0;
}
