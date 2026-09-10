#ifndef KASISKI_H
#define KASISKI_H

#include <string>
#include <vector>
#include <map>

std::map<std::string, std::vector<int>>
find_repeated_patterns(const std::string& ciphertext, int minLength, int maxLength);

std::map<std::string, std::vector<int>>
calculate_distances(const std::map<std::string, std::vector<int>>& patterns);

std::map<int, int>
find_factors(const std::map<std::string, std::vector<int>>& distances,
             int maxKeyLength);

std::vector<int>
kasiski_analysis(const std::string& ciphertext, int maxKeyLength);

double calculate_ic(const std::string& text);

std::vector<std::string>
split_into_groups(const std::string& ciphertext, int keyLength);

#endif