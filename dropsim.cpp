/**
 * Cross-platform C++17 drop simulator.
 *
 * Compiles with:
 *   - Linux: g++ dropsim.cpp -o dropsim -std=c++17 -pthread
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

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <atomic>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <functional>

const long MAX_TREASURE_CLASSES = 3000;
const long MAX_TOTAL_DROPS = 2000;
const long SIMULATION_COUNT = 20000000;

struct Entry {
    long name = -1;
    int prob = 0;
};

struct TC {
    char name[256] = { 0 };
    int group = 0;
    int level = 0;
    int picks = 0;
    int unique = 0;
    int set = 0;
    int rare = 0;
    int magic = 0;
    int nodrop = 0;
    bool isFinal = true;

    Entry items[20];

    long condition = -1;

    int total = 0;
};

struct Drop {
    long name = -1;
    int magic = 0;
    int rare = 0;
    int set = 0;
    int unique = 0;
    int count = 0;
};

struct ThreadStorage {
    Drop totaldrops[MAX_TOTAL_DROPS];
    long totalsims = 0;
    long totalpicks = 0;
};

TC treasureClasses[MAX_TREASURE_CLASSES] = { "" };

long playermod = 1;
int finditem = 0;
int heraldtier = 1;
bool desecrated = false;
int difficulty = 0;

bool isDifficultyNormal() {
    return difficulty == 0;
}

bool isDifficultyNightmare() {
    return difficulty == 1;
}

bool isDifficultyHell() {
    return difficulty == 2;
}

bool isHeraldTierAbove3() {
    return heraldtier > 3;
}

bool isHeraldTier2To3() {
    return heraldtier > 1 && heraldtier < 4;
}

bool isHeraldTier4OrAbove() {
    return heraldtier >= 4;
}

bool isHeraldTierAbove4() {
    return heraldtier > 4;
}

bool isHeraldTier3To4() {
    return heraldtier > 2 && heraldtier < 5;
}

bool isHellAndNotDesecrated() {
    return difficulty == 2 && !desecrated;
}

bool isHellAndDesecrated() {
    return difficulty == 2 && desecrated;
}

bool isHerald() {
    return heraldtier > 0;
}

bool isDesecrated() {
    return desecrated;
}

bool isNotDesecrated() {
    return !desecrated;
}

const char* conditionStrings[] = {
    "\"cond('Difficulty', normal)\"",
    "\"cond('Difficulty', nightmare)\"",
    "\"cond('Difficulty', hell)\"",
    "\"cond('MonsterTestElite', herald)*(stat('heraldtier'.accr) >3) \"",
    "(stat('heraldtier'.accr)>1) * (stat('heraldtier'.accr) < 4) ",
    "(stat('heraldtier'.accr) >=4)",
    "(stat('heraldtier'.accr) >4) ",
    "(stat('heraldtier'.accr)>2)*(stat('heraldtier'.accr) <5) ",
    "\"cond('Difficulty', hell)*(cond('Desecrated')==0)\"",
    "\"cond('Difficulty', hell)*cond('Desecrated')\"",
    "\"cond('MonsterTestElite', herald)\"",
    "cond('Desecrated')",
    "cond('Desecrated')==0",
};

bool (*conditionFunctions[])() = {
    isDifficultyNormal,
    isDifficultyNightmare,
    isDifficultyHell,
    isHeraldTierAbove3,
    isHeraldTier2To3,
    isHeraldTier4OrAbove,
    isHeraldTierAbove4,
    isHeraldTier3To4,
    isHellAndNotDesecrated,
    isHellAndDesecrated,
    isHerald,
    isDesecrated,
    isNotDesecrated,
};

const long CONDITION_FUNCTIONS_SIZE = sizeof(conditionFunctions) / sizeof(conditionFunctions[0]);

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

long calcNodrop(long e, long nd, long d) {
    if (e < 1) {
        return 0;
    }

    double _e = (double)e, _nd = (double)nd, _d = (double)d;
    if (nd < 1) {
        return 0;
    }

    if (d < 1) {
        return nd;
    }

    return (long)(_d / (pow((_nd + _d) / nd, _e) - 1));
}

void pick(std::mt19937& gen, long tcname, int magic, int rare, int set, int unique, Drop (&drops)[6], int depth = 0) {
    if (tcname < 0 || tcname >= MAX_TREASURE_CLASSES) {
        std::cerr << "Error: Invalid treasure class index: " << tcname << "\n";
        return;
    }
    
    TC& tc = treasureClasses[tcname];

    if (tc.isFinal) {
        for (auto& drop : drops) {
            if (drop.name == -1) {
                drop.name = tcname;
                drop.magic = magic;
                drop.rare = rare;
                drop.set = set;
                drop.unique = unique;
                drop.count = 1;
                break;
            }
        }

        return;
    }

    magic = std::max(magic, tc.magic);
    rare = std::max(rare, tc.rare);
    set = std::max(set, tc.set);
    unique = std::max(unique, tc.unique);

    if (tc.picks == 0) {
        return;
    }

    if (tc.total == 0) {
        return;
    }

    long nodrop = tc.nodrop;

    if (depth == 0 && finditem > 0) {
        std::uniform_int_distribution<long> dis(0, 100);
        long finditemnum = dis(gen);

        if (finditemnum >= finditem) {
            return;
        }

        nodrop = 0;
    }
    else {
        nodrop = calcNodrop(playermod, nodrop, tc.total);
    }

    int picks = tc.picks > 0 ? tc.picks : -tc.picks;

    std::uniform_int_distribution<long> dis(0, nodrop + tc.total - 1);

    if (tc.picks > 0) {
        for (int i = 0; i < picks; i++) {
            long picknum = dis(gen) - nodrop;

            if (picknum < 0) {
                continue;
            }

            for (const auto& item : tc.items) {
                if (item.prob > 0) {
                    if (picknum < item.prob) {
                        pick(gen, item.name, magic, rare, set, unique, drops, depth + 1);

                        if (drops[5].name > -1) {
                            // Game can only drop 6, so stop recursion early if we hit that limit to save time.
                            return;
                        }

                        break;
                    }

                    picknum -= item.prob;
                }
            }
        }
    }
    else {
        for (const auto& item : tc.items) {
            for (int i = 0; i < item.prob; i++) {
                if (picks <= 0) {
                    return;
                }

                pick(gen, item.name, magic, rare, set, unique, drops, depth + 1);
                if (drops[5].name > -1) {
                    // Game can only drop 6, so stop recursion early if we hit that limit to save time.
                    return;
                }

                picks--;
            }
        }
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

long findTC(const std::string& name) {
    for (long i = 0; i < MAX_TREASURE_CLASSES; ++i) {
        if (strcmp(name.c_str(), treasureClasses[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

long getTC(const std::string& name) {
    for (long i = 0; i < MAX_TREASURE_CLASSES; ++i) {
        if (treasureClasses[i].name[0] == '\0') {
            strlcpy(treasureClasses[i].name, name.c_str(), sizeof(treasureClasses[i].name));
            treasureClasses[i].name[sizeof(treasureClasses[i].name) - 1] = '\0'; // Ensure null termination
            return i;
        }

        if (strcmp(name.c_str(), treasureClasses[i].name) == 0) {
            return i;
        }
    }

    std::cerr << "Out of TCs!";
    exit(1);
}

long findCondition(const std::string& conditionStr) {
    for (long i = 0; i < CONDITION_FUNCTIONS_SIZE; ++i) {
        if (strcmp(conditionStrings[i], conditionStr.c_str()) == 0) {
            return i;
        }
    }

    return -1;
}

// Main takes first parameter as treasure class name
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <treasure_class_name> <player_mod> <find_item_percent> <difficulty> <herald_tier>\n";
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

    playermod = std::max(0L, playermod);
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

        TC &tc = treasureClasses[getTC(trim(tokens[0]))];

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

            if (probIdx < tokens.size() && tokens[itemIdx][0] != '\0' && tokens[probIdx][0] != '\0') {
                tc.items[i].name = getTC(trim(tokens[itemIdx]));
                tc.items[i].prob = atoi(tokens[probIdx].c_str());
                tc.total += tc.items[i].prob;

                if (tc.items[i].prob > 0) {
                    tc.isFinal = false;
                }
            }
        }

        if (tokens.size() > 32 && tokens[32][0] != '\0') {
            std::string conditionStr = trim(tokens[32]);
            tc.condition = findCondition(conditionStr);

            if (tc.condition == -1) {
                std::cerr << "Unknown condition on treasure class: " << tc.name << "\n";
                std::cerr << "Condition string: " << conditionStr << "\n";
            }
        }
    }

    fclose(tex);

    for (size_t i = 0; i < MAX_TREASURE_CLASSES; i++) {
        auto &tc = treasureClasses[i];
        if (tc.condition >= CONDITION_FUNCTIONS_SIZE) {
            std::cerr << "Error: Treasure class " << tc.name << " has invalid condition index: " << tc.condition << "\n";
            continue;
        }

        if (tc.condition > -1) {
            auto &condition = conditionFunctions[tc.condition];
            auto passed = condition();

            if (!passed) {
                std::cerr << "Condition not met for treasure class: " << tc.name << ", disabling it.\n";
                tc.total = 0; // Effectively disable this treasure class by setting total to 0
                for (auto &item : tc.items) {
                    item.prob = 0; // Set all item probabilities to 0 as well
                }
            }
        }

        for (auto &item : tc.items) {
            // Check if itemName is a treasure class.
            if (item.name > -1) {
                // If so, we need to check if that treasure class has a condition that would disable it, and if so, disable this item as well by setting its probability to 0.
                if (item.name >= MAX_TREASURE_CLASSES) {
                    std::cerr << "Error: Invalid item treasure class index: " << item.name << "\n";
                    continue;
                }
                
                TC& targetTC = treasureClasses[item.name];
                if (targetTC.condition >= CONDITION_FUNCTIONS_SIZE) {
                    std::cerr << "Error: Treasure class " << targetTC.name << " has invalid condition index: " << targetTC.condition << "\n";
                    continue;
                }

                if (targetTC.condition > -1) {
                    auto &condition = conditionFunctions[targetTC.condition];
                    auto passed = condition();

                    if (!passed) {
                        tc.total -= item.prob; // Remove this item's probability from the total
                        item.prob = 0;
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

        TC &atc = treasureClasses[getTC(trim(tokens[0]))];
        atc.picks = 1;

        for (long i = 1, itemIndex = 0; i < tokens.size() - 1; i += 2, itemIndex++) {
            int itemProb = atoi(tokens[i + 1].c_str());

            atc.items[itemIndex].name = getTC(trim(tokens[i]));
            atc.items[itemIndex].prob = itemProb;
            atc.total += itemProb;

            if (atc.items[i].prob > 0) {
                atc.isFinal = false;
            }
        }
    }

    long tccount = 0;

    for (size_t i = 0; i < MAX_TREASURE_CLASSES; i++) {
        if (treasureClasses[i].name[0] != '\0') {
            tccount++;
        }
    }

    fclose(atomicbase);

    long tcIndex = findTC(tcname);

    if (tcIndex == -1) {
        std::cerr << "Error: Treasure class not found: " << tcname << "\n";
        return 1;
    }

    // Get CPU count.
    // size_t thread_count = 1;
    size_t thread_count = std::thread::hardware_concurrency(); // Use 2/3 of available threads to avoid overloading the system
    thread_count = std::max(size_t(1), thread_count - 6);

    if (thread_count < 1) {
        thread_count = 1; // Fallback to 1 if hardware_concurrency cannot determine.
    }
    else {
        if (thread_count < 1) {
            thread_count = 1; // Ensure at least one thread is used
        }
    }

    std::vector<std::thread> threads;
    std::vector<ThreadStorage> threadStorage(thread_count);

    // The current time in seconds
    std::time_t currentTime = std::time(nullptr);

    for (size_t i = 0; i < thread_count; i++) {
        /** @todo These threads can be cuda */
        threads.emplace_back([i, thread_count, tcIndex, &threadStorage, &currentTime]() {
            std::random_device rd;
            std::mt19937 gen(rd());
            
            for (size_t l = 0; l < SIMULATION_COUNT; l++) {
                Drop rundrops[6];

                pick(gen, tcIndex, 0, 0, 0, 0, rundrops);

                for (const auto& drop : rundrops) {
                    if (drop.name == -1) {
                        continue;
                    }
                    
                    bool foundExistingDrop = false;

                    for (auto& existingDrop : threadStorage[i].totaldrops) {
                        if (
                            existingDrop.name == drop.name &&
                            existingDrop.magic == drop.magic &&
                            existingDrop.rare == drop.rare &&
                            existingDrop.set == drop.set &&
                            existingDrop.unique == drop.unique
                        ) {
                            existingDrop.count += drop.count;
                            threadStorage[i].totalpicks++;
                            foundExistingDrop = true;
                            break;
                        }

                        if (existingDrop.name == -1) {
                            existingDrop.name = drop.name;
                            existingDrop.magic = drop.magic;
                            existingDrop.rare = drop.rare;
                            existingDrop.set = drop.set;
                            existingDrop.unique = drop.unique;
                            existingDrop.count = drop.count;
                            threadStorage[i].totalpicks++;
                            foundExistingDrop = true;
                            break;
                        }
                    }

                    if (!foundExistingDrop) {
                        std::cerr << "Error: Exceeded maximum unique drops in thread " << i << ".\n";
                        exit(1);
                    }
                }

                threadStorage[i].totalsims++;
            }
        });
    }

    for (size_t i = 0; i < thread_count; i++) {
        threads[i].join();
    }

    long finalSims = 0;
    long finalPicks = 0;
    std::vector<Drop> finaldrops;

    for (const auto &threaddrops : threadStorage) {
        for (const auto& drop : threaddrops.totaldrops) {
            if (drop.name == -1) {
                continue;
            }

            bool foundFinalDrop = false;

            for (auto& finalDrop : finaldrops) {
                if (
                    finalDrop.name == drop.name &&
                    finalDrop.magic == drop.magic &&
                    finalDrop.rare == drop.rare &&
                    finalDrop.set == drop.set &&
                    finalDrop.unique == drop.unique
                ) {
                    finalDrop.count += drop.count;
                    foundFinalDrop = true;
                    break;
                }
            }

            if (!foundFinalDrop) {
                finaldrops.push_back(drop);
            }
        }
        finalSims += threaddrops.totalsims;
        finalPicks += threaddrops.totalpicks;
    }

    std::cout << "{\n";
    std::cout << "  \"tc\": \"" << tcname << "\",\n";
    std::cout << "  \"playermod\": " << playermod << ",\n";
    std::cout << "  \"runs\": " << finalSims << ",\n";
    std::cout << "  \"finditem\": " << finditem << ",\n";
    std::cout << "  \"drops\": [\n";

    // Convert to vector and sort by count descending
    std::vector<Drop> sortedDrops(finaldrops.begin(), finaldrops.end());
    std::sort(sortedDrops.begin(), sortedDrops.end(),
        [](const auto& a, const auto& b) { return a.count > b.count; });

    long count = 0;

    for (const auto& drop : sortedDrops) {
        std::string escapedDrop = treasureClasses[drop.name].name;
        // Escape backslashes and double quotes in the drop name
        size_t pos = 0;
        while ((pos = escapedDrop.find('\\', pos)) != std::string::npos) {
            escapedDrop.insert(pos, "\\");
            pos += 2; // Move past the escaped backslash
        }
        pos = 0;
        while ((pos = escapedDrop.find('\"', pos)) != std::string::npos) {
            escapedDrop.insert(pos, "\\");
            pos += 2; // Move past the escaped quote
        }
        std::cout << "    [\"" + trim(escapedDrop) + "\", " << ((double)drop.count / finalSims) << ", " << drop.magic << ", " << drop.rare << ", " << drop.set << ", " << drop.unique << "]";
        if (++count < sortedDrops.size()) {
            std::cout << ",";
        }
        std::cout << "\n";
    }

    std::cout << "  ]\n";
    std::cout << "}\n";

    return 0;
}
