#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    static char out[500];

    {
        ifstream cities("cities.txt");

        cout << "static const char* _g_cities[] = {\n";
        while (cities.getline (out, 500, '\t')) {
            cout << "\""<< out <<"\", \n";
        }
        cout << "0 \n";
        cout << "};\n";
    }

    cout << "\n";

    {
        ifstream items("items.txt");

        cout << "static const char* _g_items[] = {\n";
        while (!items.eof()) {
            items.getline(out, 500, '\n');
            cout << "\"" << out <<"\", \n";
        }
        cout << "0 \n";
        cout << "};\n";
    }

    cout << "\n";

    {
        ifstream year("year.txt");

        cout << "static const char* _g_anual[] = {\n";
        while (!year.eof()) {
            year.getline(out, 500, '\n');

            string s(out);
            vector<string> tokens;

            std::stringstream ss(s);
            std::string item;
            while (std::getline(ss, item, '\t')) {
               tokens.push_back(item);
            }

            for (int i = 0; i < tokens.size(); ++i) {
                cout << "\"" << tokens[i] <<"\", ";
            }

            cout << "\n";
        }
        cout << "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0\n";
        cout << "};\n";
    }

    cout << "\n";

    {
        ifstream monthly("monthly.txt");

        cout << "static const char* _g_monthly[] = {\n";
        while (!monthly.eof()) {
            monthly.getline(out, 500, '\n');

            string s(out);
            vector<string> tokens;

            std::stringstream ss(s);
            std::string item;
            while (std::getline(ss, item, '\t')) {
               tokens.push_back(item);
            }

            for (int i = 0; i < tokens.size(); ++i) {
                cout << "\"" << tokens[i] <<"\", ";
            }

            cout << "\n";
        }
        cout << "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0\n";
        cout << "};\n";
    }

    cout << "\n";
    cout << "static const char* g_month_year = \"Janeiro/2015\";\n\n";

    return 0;
}
