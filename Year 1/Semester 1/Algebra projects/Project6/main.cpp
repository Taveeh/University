#include <fstream>
#include <vector>

template<typename T>
void generateCombinations(const std::vector<T>& numbers, unsigned size, std::vector<T>& temp, std::vector<std::vector<T>>& res) {
    // generates all the possible combinations of n vectors from Z2^n
    for (unsigned i = 0; i < numbers.size(); i++) {
        temp.push_back(numbers[i]);
        if (size <= 1) {
            std::vector<T> sol;
            for (const auto& it: temp) {
                sol.push_back(it);
            }
            res.push_back(sol);
            temp.erase(temp.end() - 1);
        } else {
            generateCombinations<T>(numbers, size - 1, temp, res);
            temp.erase(temp.end() - 1);
        }
    }
}

void getCofactor(std::vector<std::vector<int>>& mat, std::vector<std::vector<int>>& temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(std::vector<std::vector<int>>& mat, int n) {
    // calculates the determinant of a matrix
    int D = 0;
    if (n == 1) {
        return mat[0][0];
    }
    std::vector<std::vector<int>> temp;
    temp.resize(n, std::vector<int>(n));
    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }
    return D;
}

int main() {
    // set up the i/o streams and read the data
    // Example 1
    std::ifstream fin("date1.in");
    std::ofstream fout("date1.out");
    // Example 2
//    std::ifstream fin("date2.in");
//    std::ofstream fout("date2.out");
    // Example 3
//    std::ifstream fin("date3.in");
//    std::ofstream fout("date3.out");
    // Example 4
//    std::ifstream fin("date4.in");
//    std::ofstream fout("date4.out");
    // Example 5
//    std::ifstream fin("date5.in");
//    std::ofstream fout("date5.out");
    int n;
    fin >> n;
    // calculate the number of bases and output it
    // using the formula p = (2^n - 1)(2^n - 2^2) ... (2^n - 2^(n-1))
    long long d = 1 << n;
    long long p = 1;
    for (int i = 0; i < n; ++i) {
        p *= d - (1 << i);
    }
    fout << p << "\n\n";
    if (n <= 4) {
        // generate all combinations with size n using only the digits 0 and 1, erasing the first one which only contains zeroes
        std::vector<int> numbers = {0, 1};
        std::vector<int> temp;
        std::vector<std::vector<int>> res;
        generateCombinations<int>(numbers, n, temp, res);
        res.erase(res.begin());
        // generate combinations with size n of the previously generated combinations
        std::vector<std::vector<int>> temp2;
        std::vector<std::vector<std::vector<int>>> finalRes;
        generateCombinations<std::vector<int>>(res, n, temp2, finalRes);
        // find the combinations which contain duplicate tuples and construct a new vector which contains only the unique ones
        std::vector<std::vector<std::vector<int>>> finalResWithoutDuplicates;
        std::copy_if(finalRes.begin(), finalRes.end(), std::back_inserter(finalResWithoutDuplicates), [](auto element) {
            std::vector<std::vector<int>> copy(element);
            std::sort(copy.begin(), copy.end());
            auto it = std::unique(copy.begin(), copy.end());
            return it == copy.end();
        });
        // calculate the determinant of the matrix and check its parity, then construct a new vector that contains only the combinations with an odd determinant
        std::vector<std::vector<std::vector<int>>> finalResWithoutDuplicatesAndThatIsAccordingToTheFormula;
        std::copy_if(finalResWithoutDuplicates.begin(), finalResWithoutDuplicates.end(),
                     std::back_inserter(finalResWithoutDuplicatesAndThatIsAccordingToTheFormula), [n](auto element) {
                    return std::abs(determinantOfMatrix(element, n)) % 2 == 1;
                });
        // output the combinations
        for (const auto &it: finalResWithoutDuplicatesAndThatIsAccordingToTheFormula) {
            fout << "(";
            for (const auto &it2: it) {
                fout << "(";
                for (const auto &it3: it2) {
                    fout << it3;
                    if (&it3 - &it2[0] != n - 1) {
                        fout << ",";
                    }
                }
                fout << ")";
                if (&it2 - &it[0] != n - 1) {
                    fout << ",";
                }
            }
            fout << ")\n";
        }
    }
    return 0;
}
