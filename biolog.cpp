#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<std::string> findRepeatedDnaSequences(std::string s) {
    std::unordered_map<std::string, int> seen;
    std::vector<std::string> result;

    if (s.length() < 10) return result; 

    for (int i = 0; i <= s.length() - 10; ++i) {
        std::string sequence = s.substr(i, 10);
        if (++seen[sequence] == 2) {
            result.push_back(sequence);
        }
    }

    return result;
}

int main() {
    std::string dna = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    std::vector<std::string> sequences = findRepeatedDnaSequences(dna);
    
    for (const auto& seq : sequences) {
        std::cout << seq << std::endl;
    }

    return 0;
}
