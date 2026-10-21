/**
 * Cross-platform C++17 drop simulator.
 *
 * Compiles with:
 *   - Linux: g++ dropsim.cpp -o dropsim -std=c++17
 *   - Windows: Visual Studio 2017+ (C++17 support required)
 */

 // Disable MSVC security warnings for fopen, strcspn, etc.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#if defined(_WIN32) || defined(_WIN64)
#define DIRECTORY_SEPARATOR '\\'
#define DIRECTORY_SEPARATOR_STRING "\\"
#else
#define DIRECTORY_SEPARATOR '/'
#define DIRECTORY_SEPARATOR_STRING "/"
#endif

#ifndef BASETC
#define BASETC 0
#endif

// #define DEBUG 1

#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <atomic>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <functional>

struct Entry {
    std::string name = "";
    int prob = 0;
};

struct TC {
    std::string name = "";
    int group = 0;
    int level = 0;
    int picks = 0;
    int unique = 0;
    int set = 0;
    int rare = 0;
    int magic = 0;
    int nodrop = 0;

    Entry items[10];

    std::string condition = "";

    int total = 0;
};

struct AtomicTC {
    std::vector<Entry> items;

    int total = 0;
};

struct Drop {
    std::string name = "";
    int magic = 0;
    int rare = 0;
    int set = 0;
    int unique = 0;

    bool operator==(const Drop& other) const {
        return name == other.name && magic == other.magic && rare == other.rare && set == other.set && unique == other.unique;
    }
};

namespace std {
    template <>
    struct hash<Drop> {
        std::size_t operator()(const Drop& d) const {
            std::size_t h1 = std::hash<std::string>()(d.name);
            std::size_t h2 = std::hash<int>()(d.magic);
            std::size_t h3 = std::hash<int>()(d.rare);
            std::size_t h4 = std::hash<int>()(d.set);
            std::size_t h5 = std::hash<int>()(d.unique);
            
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4);
        }
    };
}

std::unordered_map<std::string, AtomicTC> atomic;
std::unordered_map<std::string, TC> treasureClasses;

long playermod = 1;
int finditem = 0;
int heraldtier = 1;
bool desecrated = false;
int difficulty = 0;
constexpr size_t MAX_DROP_INDICES = 6;

std::unordered_map<std::string, std::function<bool()>> conditionFunctions = {
    {"(stat('heraldtier'.accr) >4) ", []() { return heraldtier > 4; }},
    {"(stat('heraldtier'.accr) >=4) ", []() { return heraldtier >= 4; }},
    {"(stat('heraldtier'.accr)>1) * (stat('heraldtier'.accr) < 4) ", []() { return heraldtier > 1 && heraldtier < 4; }},
    {"(stat('heraldtier'.accr)>2)*(stat('heraldtier'.accr) <5) ", []() { return heraldtier > 2 && heraldtier < 5; }},
    {"\"cond('Difficulty', hell)*(cond('Desecrated')==0)\"", []() { return (difficulty == 2) && (!desecrated); }},
    {"\"cond('Difficulty', hell)*cond('Desecrated')\"", []() { return (difficulty == 2) && desecrated; }},
    {"\"cond('Difficulty', hell)\"", []() { return difficulty == 2; }},
    {"\"cond('Difficulty', nightmare)\"", []() { return difficulty == 1; }},
    {"\"cond('Difficulty', normal)\"", []() { return difficulty == 0; }},
    {"\"cond('MonsterTestElite', herald)*(stat('heraldtier'.accr) >3) \"", []() { return heraldtier > 3; }},
    {"\"cond('MonsterTestElite', herald)\"", []() { return false; }},
    {"cond('Desecrated')", []() { return desecrated; }},
    {"cond('Desecrated')==0", []() { return !desecrated; }},
};

std::unordered_map<std::string, std::unordered_map<int, double>> countDistributionCache;

std::string makeCountDistributionKey(const std::string& tcname, int magic, int rare, int set, int unique) {
    return tcname + "|" + std::to_string(magic) + "|" + std::to_string(rare) + "|" + std::to_string(set) + "|" + std::to_string(unique);
}

std::unordered_map<int, double> getDropCountDistribution(const std::string& tcname, int magic, int rare, int set, int unique, int depth);

// Helper function to split string by tab delimiter, keeping empty strings between tabs
std::vector<std::string> splitByChar(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    // Add the last token (after the final tab or remaining text)
    tokens.push_back(str.substr(start));

    return tokens;
}

void pickAtomic(std::string tcname, int dropindex, double multiplier, int magic, int rare, int set, int unique, std::unordered_map<size_t, std::unordered_map<Drop, double>>& drops) {
    if (atomic.find(tcname) == atomic.end()) {
        drops[dropindex][{tcname, magic, rare, set, unique}] += multiplier;
        return;
    }

    AtomicTC& atc = atomic[tcname];

    if (atc.total == 0) {
        return;
    }

    for (auto item : atc.items) {
        if (item.prob > 0) {
            drops[dropindex][{item.name, magic, rare, set, unique}] += multiplier * ((double)item.prob / atc.total);
        }
    }
}

// Adjusts NoDrop for the effective player count. The game does this in double precision with this exact
// sequence of operations, which can differ from the algebraically equivalent T * rho^n / (1 - rho^n).
long calcNodrop(long e, long nd, long d) {
    if (e <= 1 || nd < 1) {
        return nd < 1 ? 0 : nd;
    }

    double rho = (double)nd / (double)(nd + d);
    double pi = rho;

    for (long i = 1; i < e; i++) {
        pi *= rho;
    }

    double q = 1 - pi;

    if (q == 0) {
        return 0;
    }

    return (long)(((1 - q) * (double)d) / q);
}

// The chance of selecting each entry (index into tc.items) on each pick the TC makes. Whatever is left is NoDrop.
struct PickSlot {
    std::vector<std::pair<size_t, double>> entries;
    double nodrop = 0;
};

std::vector<PickSlot> getPickSlots(const TC& tc) {
    std::vector<PickSlot> slots;

    if (tc.total <= 0) {
        return slots;
    }

    // Picks of 0 means 1.
    int picks = std::max(std::abs(tc.picks), 1);

    if (tc.picks < 0) {
        // Sequential: the k-th pick takes position k on the weight line, so an entry of weight w is chosen w times
        // in a row. NoDrop is ignored, and the TC stops once it runs past the end of the line.
        for (size_t i = 0; i < 10 && (int)slots.size() < picks; i++) {
            for (int j = 0; j < tc.items[i].prob && (int)slots.size() < picks; j++) {
                slots.push_back({ { { i, 1.0 } }, 0 });
            }
        }

        return slots;
    }

    long nodrop = tc.nodrop;

    // Find Item ignores NoDrop entirely.
    if (finditem > 0) {
        nodrop = 0;
    } else if (tc.picks > 0) {
        nodrop = calcNodrop(playermod, nodrop, tc.total);
    }

    nodrop = std::max(0L, nodrop);
    long totalWithNodrop = tc.total + nodrop;

    PickSlot slot;
    slot.nodrop = (double)nodrop / totalWithNodrop;

    for (size_t i = 0; i < 10; i++) {
        if (tc.items[i].prob > 0) {
            slot.entries.push_back({ i, (double)tc.items[i].prob / totalWithNodrop });
        }
    }

    slots.assign(picks, slot);

    return slots;
}

std::unordered_map<int, double> getDropCountDistribution(const std::string& tcname, int magic, int rare, int set, int unique, int depth) {
    std::string cacheKey = makeCountDistributionKey(tcname, magic, rare, set, unique);
    auto cacheIt = countDistributionCache.find(cacheKey);
    if (cacheIt != countDistributionCache.end()) {
        return cacheIt->second;
    }

    std::unordered_map<int, double> result;

    if (treasureClasses.find(tcname) == treasureClasses.end()) {
        auto atomicIt = atomic.find(tcname);
        if (atomicIt != atomic.end() && atomicIt->second.total == 0) {
            result[0] = 1.0;
        } else {
            result[1] = 1.0;
        }
        countDistributionCache[cacheKey] = result;
        return result;
    }

    TC& tc = treasureClasses[tcname];

    magic = std::max(magic, tc.magic);
    rare = std::max(rare, tc.rare);
    set = std::max(set, tc.set);
    unique = std::max(unique, tc.unique);

    std::vector<PickSlot> slots = getPickSlots(tc);

    if (slots.empty()) {
        result[0] = 1.0;
        countDistributionCache[cacheKey] = result;
        return result;
    }

    std::vector<std::unordered_map<int, double>> itemCountDistributions(10);
    for (size_t i = 0; i < 10; i++) {
        if (tc.items[i].prob > 0) {
            itemCountDistributions[i] = getDropCountDistribution(tc.items[i].name, magic, rare, set, unique, depth + 1);
        }
    }

    result[0] = 1.0;

    for (const auto& slot : slots) {
        std::unordered_map<int, double> next;

        for (const auto& statePair : result) {
            int currentCount = statePair.first;
            double stateProb = statePair.second;

            if (stateProb <= 0) continue;

            for (const auto& [i, itemProb] : slot.entries) {
                for (const auto& countPair : itemCountDistributions[i]) {
                    next[currentCount + countPair.first] += stateProb * itemProb * countPair.second;
                }
            }

            if (slot.nodrop > 0) {
                next[currentCount] += stateProb * slot.nodrop;
            }
        }

        result = std::move(next);
    }

    countDistributionCache[cacheKey] = result;
    return result;
}

// Forward declaration
void pick(std::string tcname, int dropindex, double multiplier, int magic, int rare, int set, int unique, std::unordered_map<size_t, std::unordered_map<Drop, double>>& drops, int depth = 0);

void pick(std::string tcname, int dropindex, double multiplier, int magic, int rare, int set, int unique, std::unordered_map<size_t, std::unordered_map<Drop, double>>& drops, int depth) {
    if (treasureClasses.find(tcname) == treasureClasses.end()) {
        pickAtomic(tcname, dropindex, multiplier, magic, rare, set, unique, drops);
        return;
    }

    TC& tc = treasureClasses[tcname];

    magic = std::max(magic, tc.magic);
    rare = std::max(rare, tc.rare);
    set = std::max(set, tc.set);
    unique = std::max(unique, tc.unique);

    std::vector<PickSlot> slots = getPickSlots(tc);

    if (slots.empty()) {
        return;
    }

    std::vector<std::unordered_map<size_t, std::unordered_map<Drop, double>>> itemSubDrops(10);
    std::vector<std::unordered_map<int, double>> itemCountDistributions(10);
    for (size_t i = 0; i < 10; i++) {
        if (tc.items[i].prob > 0) {
            pick(tc.items[i].name, 0, 1.0, magic, rare, set, unique, itemSubDrops[i], depth + 1);
            itemCountDistributions[i] = getDropCountDistribution(tc.items[i].name, magic, rare, set, unique, depth + 1);
        }
    }

    // State: drop index before the current pick -> probability
    std::unordered_map<int, double> current;
    current[dropindex] = 1.0;

    for (const auto& slot : slots) {
        std::unordered_map<int, double> next;

        for (const auto& statePair : current) {
            int currentDropIdx = statePair.first;
            double stateProb = statePair.second;

            if (stateProb <= 0) continue;

            for (const auto& [i, itemProb] : slot.entries) {
                // Apply these drops offset by currentDropIdx
                for (auto& subDropPair : itemSubDrops[i]) {
                    int offsetDropIdx = currentDropIdx + subDropPair.first;
                    for (auto& itemDrop : subDropPair.second) {
                        drops[offsetDropIdx][itemDrop.first] += stateProb * itemProb * itemDrop.second;
                    }
                }

                // Next state advances according to child drop-count PMF
                for (const auto& countPair : itemCountDistributions[i]) {
                    next[currentDropIdx + countPair.first] += stateProb * itemProb * countPair.second;
                }
            }

            // NoDrop - stay at same drop index
            if (slot.nodrop > 0) {
                next[currentDropIdx] += stateProb * slot.nodrop;
            }
        }

        current = std::move(next);
    }
}

std::string realpath(std::string path) {
    return std::filesystem::canonical(std::filesystem::absolute(path)).string();
}

/**
 * Trim leading and trailing whitespace from a string.
 * This is a simple implementation and may not cover all Unicode whitespace characters.
 */
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return ""; // String is all whitespace
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

/**
 * Escape a string for JSON output.
 * Escapes special characters like quotes, backslashes, and control characters.
 */
std::string escapeJsonString(const std::string& str) {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '"':
                result += "\\\"";
                break;
            case '\\':
                result += "\\\\";
                break;
            case '\b':
                result += "\\b";
                break;
            case '\f':
                result += "\\f";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            default:
                if (c < 0x20) {
                    // Escape other control characters as \uXXXX
                    char buf[7];
                    snprintf(buf, sizeof(buf), "\\u%04x", (unsigned char)c);
                    result += buf;
                } else {
                    result += c;
                }
        }
    }
    return result;
}

// Main takes first parameter as treasure class name
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <treasure_class_name> <player_mod> <find_item_percent> <difficulty> <herald_tier> <desecrated>\n";
        return 1;
    }

    std::vector<std::string> pathParts = splitByChar(argv[0], DIRECTORY_SEPARATOR);
    pathParts.pop_back();
    std::string path = "";

    for (const auto& part : pathParts) {
        path += part + DIRECTORY_SEPARATOR_STRING;
    }

    path = realpath(path) + DIRECTORY_SEPARATOR_STRING;
    std::string txtDir = realpath(path + "txt") + DIRECTORY_SEPARATOR_STRING;

    std::string tcname = argv[1];

    if (argc >= 3) {
        playermod = atoi(argv[2]);
    }

    playermod = std::max(1L, playermod);
    playermod = std::min(8L, playermod);

    if (argc >= 4) {
        finditem = atoi(argv[3]);
    }

    if (argc >= 5) {
        difficulty = atoi(argv[4]);
    }

    if (argc >= 6) {
        heraldtier = atoi(argv[5]);
    }

    if (argc >= 7) {
        desecrated = atoi(argv[6]) ? true : false;
    }

    // Open the treasure class file at: txt/treasureclassex.txt
    FILE* tex = fopen((txtDir + (BASETC ? "base/treasureclassex.txt" : "treasureclassex.txt")).c_str(), "r");
    if (!tex) {
        std::cerr << "Error: Could not open treasure class file\n";
        return 1;
    }

    // Treasure class file is tab delimited and has a header row, so skip the first line
    char line[1024];
    fgets(line, sizeof(line), tex); // Skip header

    while (fgets(line, sizeof(line), tex)) {
        // remove newline if it exists
        line[strcspn(line, "\r\n")] = 0;

        // Split by tab delimiter, preserving empty strings
        std::string lineStr(line);
        std::vector<std::string> tokens = splitByChar(lineStr, '\t');

        if (tokens.empty()) continue;

        TC tc;
        tc.name = trim(tokens[0]);

        if (tokens.size() > 1) {
            tc.group = atoi(tokens[1].c_str());
        }

        if (tokens.size() > 2) {
            tc.level = atoi(tokens[2].c_str());
        }

        if (tokens.size() > 3) {
            tc.picks = atoi(tokens[3].c_str());
        }

        if (tokens.size() > 4) {
            tc.unique = atoi(tokens[4].c_str());
        }

        if (tokens.size() > 5) {
            tc.set = atoi(tokens[5].c_str());
        }

        if (tokens.size() > 6) {
            tc.rare = atoi(tokens[6].c_str());
        }

        if (tokens.size() > 7) {
            tc.magic = atoi(tokens[7].c_str());
        }

        if (tokens.size() > 8) {
            tc.nodrop = atoi(tokens[8].c_str());
        }

        // Process items
        for (int i = 0; i < 10; i++) {
            int itemIdx = 9 + (i * 2);
            int probIdx = itemIdx + 1;

            // The first empty Item cell ends the list, even if later cells are filled.
            if (itemIdx >= tokens.size() || trim(tokens[itemIdx]).empty()) {
                break;
            }

            tc.items[i].name = trim(tokens[itemIdx]);
            tc.items[i].prob = probIdx < tokens.size() ? atoi(tokens[probIdx].c_str()) : 0;

            // A weight below 1 skips the entry without ending the list.
            if (tc.items[i].prob < 1) {
                tc.items[i].prob = 0;
            }

            tc.total += tc.items[i].prob;
        }

        if (tokens.size() > 32) {
            tc.condition = tokens[32];
        }

        treasureClasses[tc.name] = tc;
    }

    fclose(tex);

    for (auto &[name, tc] : treasureClasses) {
        if (!tc.condition.empty()) {
            if (conditionFunctions.find(tc.condition) == conditionFunctions.end()) {
                std::cerr << "Error: No function found for condition on treasure class: " << name << ".\n";
                return 1;
            }

            if (!conditionFunctions[tc.condition]()) {
                std::cerr << "Condition not met for treasure class: " << name << ", disabling it.\n";
                tc.total = 0; // Effectively disable this treasure class by setting total to 0
                for (auto &item : tc.items) {
                    item.prob = 0; // Set all item probabilities to 0 as well
                }
            }
        }

        for (auto &[itemName, itemProb] : tc.items) {
            auto targetName = itemName;
            // Check if itemName is a treasure class.
            if (treasureClasses.find(itemName) != treasureClasses.end()) {
                // If so, we need to check if that treasure class has a condition that would disable it, and if so, disable this item as well by setting its probability to 0.
                TC& targetTC = treasureClasses[itemName];
                if (!targetTC.condition.empty()) {
                    if(conditionFunctions.find(targetTC.condition) == conditionFunctions.end()) {
                        std::cerr << "Error: No function found for condition on nested treasure class: " << itemName << ".\n";
                        return 1;
                    }

                    if (!conditionFunctions[targetTC.condition]()) {
                        tc.total -= itemProb; // Remove this item's probability from the total
                        itemProb = 0;
                    }
                }
            }
        }
    }

    // Open the file at: atomic.txt
    FILE* atomicbase = fopen((path + (BASETC ? "atomicbase.txt" : "atomic.txt")).c_str(), "r");

    if (!atomicbase) {
        std::cerr << "Error: Could not open atomic file\n";
        return 1;
    }

    while (fgets(line, sizeof(line), atomicbase)) {
        // remove newline if it exists
        line[strcspn(line, "\r\n")] = 0;

        // Split by tab delimiter, preserving empty strings
        std::string lineStr(line);
        std::vector<std::string> tokens = splitByChar(lineStr, '\t');

        if (tokens.empty()) continue;

        AtomicTC atc;
        std::string tcBaseName = trim(tokens[0]);
        atomic[tcBaseName] = atc;

        for (long i = 1; i < tokens.size() - 1; i += 2) {
            std::string itemName = trim(tokens[i]);
            int itemProb = atoi(tokens[i + 1].c_str());

            atomic[tcBaseName].items.push_back({ itemName, itemProb });
            atomic[tcBaseName].total += itemProb;
        }
    }

    fclose(atomicbase);

    if (treasureClasses.find(tcname) == treasureClasses.end()) {
        std::cerr << "Error: Treasure class not found: " << tcname << "\n";
        return 1;
    }


    std::unordered_map<size_t, std::unordered_map<Drop, double>> drops;
    pick(tcname, 0, 1.0f, 0, 0, 0, 0, drops);

    // Convert drops map to vector for sequential indexing
    std::vector<std::unordered_map<Drop, double>> dropsVector;
    if (!drops.empty()) {
        size_t maxIndex = 0;
        for (auto& pair : drops) {
            if (pair.first > maxIndex) {
                maxIndex = pair.first;
            }
        }
        dropsVector.resize(maxIndex + 1);
        for (auto& pair : drops) {
            dropsVector[pair.first] = pair.second;
        }
    }

    if (dropsVector.size() > MAX_DROP_INDICES) {
        dropsVector.resize(MAX_DROP_INDICES);
    }

    // Aggregate expected drops across all included drop indices
    std::unordered_map<Drop, double> expectedDrops;
    for (const auto& itemMap : dropsVector) {
        for (const auto& pair : itemMap) {
            expectedDrops[pair.first] += pair.second;
        }
    }

    // Output JSON representation of drops with metadata and aggregated totals
    std::cout << "{\n";
    std::cout << "  \"tc\": \"" << escapeJsonString(tcname) << "\",\n";
    std::cout << "  \"playermod\": " << playermod << ",\n";
    std::cout << "  \"finditem\": " << finditem << ",\n";
    std::cout << "  \"drops\": [\n";

    std::vector<std::pair<Drop, double>> sortedExpected(expectedDrops.begin(), expectedDrops.end());
    std::sort(sortedExpected.begin(), sortedExpected.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    bool firstExpected = true;
    for (const auto& itemPair : sortedExpected) {
        const Drop& drop = itemPair.first;
        double expectedValue = itemPair.second;

        if (!firstExpected) {
            std::cout << ",\n";
        }
        firstExpected = false;

        std::cout << "    [\"" << escapeJsonString(drop.name) << "\", " << expectedValue << ", "
                  << drop.magic << ", " << drop.rare << ", " << drop.set << ", " << drop.unique << "]";
    }

    std::cout << "\n  ]\n";
    std::cout << "}\n";

    return 0;
}
