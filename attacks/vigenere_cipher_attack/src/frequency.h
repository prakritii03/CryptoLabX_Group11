#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <string>
#include <vector>
#include <array>

std::array<int, 26>
frequency_analysis(const std::string& group);

int find_shift(const std::string& group);

void display_frequency_table(
    const std::vector<std::string>& groups
);

#endif
