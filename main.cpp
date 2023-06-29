#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <chrono>
#include <cstring>
#include <vector>

class Fraud {
private:
    std::unordered_map<double, std::vector<std::vector<double>>> data;

public:

    Fraud(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::vector<double> row;
            std::stringstream ss(line);
            std::string value;

            while (std::getline(ss, value, ',')) {
                row.push_back(std::strtod(value.c_str(), nullptr));
            }

            double key = row[0];
            data[key].push_back(row);
        }

        file.close();
    }

    std::vector<std::vector<double>> search(const double key) {
        auto start = std::chrono::steady_clock::now();

        std::vector<std::vector<double>> result;

        if (data.find(key) != data.end()) {
            result = data[key];
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda search izvršena za: " << duration.count() << " sekundi." << std::endl;

        return result;
    }

    std::vector<std::vector<double>> searchN(const double key, const int n) {
        auto start = std::chrono::steady_clock::now();

        std::vector<std::vector<double>> result;

        if (data.find(key) != data.end()) {
            std::vector<std::vector<double>>& rows = data[key];
            int count = std::min(n, static_cast<int>(rows.size()));

            for (int i = 0; i < count; i++) {
                result.push_back(rows[i]);
            }
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda searchN izvršena za: " << duration.count() << " sekundi." << std::endl;

        return result;
    }

    void remove(const double key) {
        auto start = std::chrono::steady_clock::now();

        data.erase(key);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda remove izvršena za: " << duration.count() << " sekundi." << std::endl;
    }

    void removeN(const double key, const int n) {
        auto start = std::chrono::steady_clock::now();

        if (data.find(key) != data.end()) {
            std::vector<std::vector<double>>& rows = data[key];
            int count = std::min(n, static_cast<int>(rows.size()));
            rows.erase(rows.begin(), rows.begin() + count);
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda removeN izvršena za: " << duration.count() << " sekundi." << std::endl;
    }

    double getMinValue(const int column) {
        auto start = std::chrono::steady_clock::now();

        double minValue = std::numeric_limits<double>::max();

        for (const auto& pair : data) {
            for (const auto& row : pair.second) {
                minValue = std::min(minValue, row[column]);
            }
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda getMinValue izvršena za: " << duration.count() << " sekundi." << std::endl;

        return minValue;
    }

    double getMaxValue(const int column) {
        auto start = std::chrono::steady_clock::now();

        double maxValue = std::numeric_limits<double>::lowest();

        for (const auto& pair : data) {
            for (const auto& row : pair.second) {
                maxValue = std::max(maxValue, row[column]);
            }
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda getMaxValue izvršena za: " << duration.count() << " sekundi." << std::endl;

        return maxValue;
    }

    std::vector<std::vector<double>> getTopN(const int column, const int n) {
        auto start = std::chrono::steady_clock::now();

        std::vector<std::vector<double>> result;
        std::vector<double> columnData;

        for (const auto& pair : data) {
            for (const auto& row : pair.second) {
                columnData.push_back(row[column]);
            }
        }

        std::partial_sort(columnData.begin(), columnData.begin() + n, columnData.end(), std::greater<double>());

        for (const auto& pair : data) {
            for (const auto& row : pair.second) {
                if (std::find(columnData.begin(), columnData.begin() + n, row[column]) != columnData.begin() + n) {
                    result.push_back(row);
                }
            }
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda getTopN izvršena za: " << duration.count() << " sekundi." << std::endl;

        return result;
    }

    void add(const std::vector<double>& row) {
        auto start = std::chrono::steady_clock::now();

        double key = row[0];
        data[key].push_back(row);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda add izvršena za: " << duration.count() << " sekundi." << std::endl;
    }

    void addN(const std::vector<std::vector<double>>& rows) {
        auto start = std::chrono::steady_clock::now();

        for (const auto& row : rows) {
            double key = row[0];
            data[key].push_back(row);
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Metoda addN izvršena za: " << duration.count() << " sekundi." << std::endl;
    }
};

int main() {
    Fraud nultaistanca("fraudTest.csv");

    double key = 42.0;
    std::vector<std::vector<double>> result = nultaistanca.search(key);

    if (!result.empty()) {
        std::cout << "Zapis s ključem/vrijednošću " << key << " pronađen.\n";
    } else {
        std::cout << "Zapis s ključem/vrijednošću " << key << " nije pronađen.\n";
    }

    int n = 5;
    std::vector<std::vector<double>> results = nultaistanca.searchN(key, n);

    if (!results.empty()) {
        std::cout << "Prva " << n << " zapisa s ključem/vrijednošću " << key << " pronađena.\n";
    } else {
        std::cout << "Nijedan zapis s ključem/vrijednošću " << key << " nije pronađen.\n";
    }

    nultaistanca.remove(key);
    nultaistanca.removeN(key, n);

    int column = 2;
    double minValue = nultaistanca.getMinValue(column);
    double maxValue = nultaistanca.getMaxValue(column);

    std::cout << "Najmanja vrijednost u stupcu " << column << ": " << minValue << "\n";
    std::cout << "Najveća vrijednost u stupcu " << column << ": " << maxValue << "\n";

    std::vector<std::vector<double>> topN = nultaistanca.getTopN(column, n);

    if (!topN.empty()) {
        std::cout << "Prvih " << n << " najvećih/zapisa s ključem/vrijednošću u stupcu " << column << ":\n";
    } else {
        std::cout << "Nijedan zapis s ključem/vrijednošću u stupcu " << column << " nije pronađen.\n";
    }

    std::vector<double> newRow = { 1.0, 2.0, 3.0 };
    nultaistanca.add(newRow);

    std::vector<std::vector<double>> newRows = { { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };
    nultaistanca.addN(newRows);

    return 0;
}
