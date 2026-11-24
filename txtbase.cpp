#include "txtbase.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace D2::BASE {

  // Split a line on tabs, ignoring any trailing CR/LF.
  static std::vector<std::string> splitline(const char* line) {
    std::vector<std::string> values;
    std::string text(line);

    while (!text.empty() && (text.back() == '\r' || text.back() == '\n')) {
      text.pop_back();
    }

    std::stringstream ss(text);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    return values;
  }

  size_t t_actinfo::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { act = (int32_t) std::strtol(values[0].c_str(), nullptr, 10); }
    if (values.size() > 1) { town = values[1]; }
    if (values.size() > 2) { start = values[2]; }
    if (values.size() > 3) { maxnpcitemlevel = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { classlevelrangestart = values[4]; }
    if (values.size() > 5) { classlevelrangeend = values[5]; }
    if (values.size() > 6) { wanderingnpcstart = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { wanderingnpcrange = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { commonactcof = values[8]; }
    if (values.size() > 9) { waypoint1 = values[9]; }
    if (values.size() > 10) { waypoint2 = values[10]; }
    if (values.size() > 11) { waypoint3 = values[11]; }
    if (values.size() > 12) { waypoint4 = values[12]; }
    if (values.size() > 13) { waypoint5 = values[13]; }
    if (values.size() > 14) { waypoint6 = values[14]; }
    if (values.size() > 15) { waypoint7 = values[15]; }
    if (values.size() > 16) { waypoint8 = values[16]; }
    if (values.size() > 17) { waypoint9 = values[17]; }
    if (values.size() > 18) { wanderingMonsterPopulateChance = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { wanderingMonsterRegionTotal = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { wanderingPopulateRandomChance = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_actinfo> t_actinfo::readfile(std::string filename) {
    std::vector<t_actinfo> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_actinfo v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_armor::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { version = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { compactsave = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { rarity = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { spawnable = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 6) { minac = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { maxac = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { speed = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { reqstr = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { reqdex = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { block = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { durability = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { nodurability = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { level = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { ShowLevel = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { levelreq = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { cost = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { gamblecost = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { code = values[19]; }
    if (values.size() > 20) { namestr = values[20]; }
    if (values.size() > 21) { magiclvl = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { autoprefix = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { alternategfx = values[23]; }
    if (values.size() > 24) { normcode = values[24]; }
    if (values.size() > 25) { ubercode = values[25]; }
    if (values.size() > 26) { ultracode = values[26]; }
    if (values.size() > 27) { component = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { invwidth = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { invheight = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { hasinv = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { gemsockets = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { gemapplytype = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { flippyfile = values[33]; }
    if (values.size() > 34) { invfile = values[34]; }
    if (values.size() > 35) { uniqueinvfile = values[35]; }
    if (values.size() > 36) { setinvfile = values[36]; }
    if (values.size() > 37) { rArm = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { lArm = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { Torso = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { Legs = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { rSPad = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { lSPad = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { useable = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 48) { Transmogrify = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { TMogType = values[49]; }
    if (values.size() > 52) { type = values[52]; }
    if (values.size() > 54) { dropsound = values[54]; }
    if (values.size() > 55) { dropsfxframe = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { usesound = values[56]; }
    if (values.size() > 57) { unique = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { transparent = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { transtbl = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { quivered = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { lightradius = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { belt = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 65) { missiletype = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { durwarning = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { qntwarning = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { mindam = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { maxdam = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { StrBonus = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 72) { gemoffset = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { bitfield1 = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { CharsiMin = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { CharsiMax = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 76) { CharsiMagicMin = (int32_t) std::strtol(values[76].c_str(), nullptr, 10); }
    if (values.size() > 77) { CharsiMagicMax = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { CharsiMagicLvl = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 79) { GheedMin = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 80) { GheedMax = (int32_t) std::strtol(values[80].c_str(), nullptr, 10); }
    if (values.size() > 82) { GheedMagicMax = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }
    if (values.size() > 83) { GheedMagicLvl = (int32_t) std::strtol(values[83].c_str(), nullptr, 10); }
    if (values.size() > 88) { AkaraMagicLvl = (int32_t) std::strtol(values[88].c_str(), nullptr, 10); }
    if (values.size() > 89) { FaraMin = (int32_t) std::strtol(values[89].c_str(), nullptr, 10); }
    if (values.size() > 90) { FaraMax = (int32_t) std::strtol(values[90].c_str(), nullptr, 10); }
    if (values.size() > 91) { FaraMagicMin = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }
    if (values.size() > 92) { FaraMagicMax = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { FaraMagicLvl = (int32_t) std::strtol(values[93].c_str(), nullptr, 10); }
    if (values.size() > 98) { LysanderMagicLvl = (int32_t) std::strtol(values[98].c_str(), nullptr, 10); }
    if (values.size() > 99) { DrognanMin = (int32_t) std::strtol(values[99].c_str(), nullptr, 10); }
    if (values.size() > 100) { DrognanMax = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { DrognanMagicMin = (int32_t) std::strtol(values[101].c_str(), nullptr, 10); }
    if (values.size() > 102) { DrognanMagicMax = (int32_t) std::strtol(values[102].c_str(), nullptr, 10); }
    if (values.size() > 103) { DrognanMagicLvl = (int32_t) std::strtol(values[103].c_str(), nullptr, 10); }
    if (values.size() > 104) { HratliMin = (int32_t) std::strtol(values[104].c_str(), nullptr, 10); }
    if (values.size() > 105) { HratliMax = (int32_t) std::strtol(values[105].c_str(), nullptr, 10); }
    if (values.size() > 106) { HratliMagicMin = (int32_t) std::strtol(values[106].c_str(), nullptr, 10); }
    if (values.size() > 107) { HratliMagicMax = (int32_t) std::strtol(values[107].c_str(), nullptr, 10); }
    if (values.size() > 108) { HratliMagicLvl = (int32_t) std::strtol(values[108].c_str(), nullptr, 10); }
    if (values.size() > 113) { AlkorMagicLvl = (int32_t) std::strtol(values[113].c_str(), nullptr, 10); }
    if (values.size() > 115) { OrmusMax = (int32_t) std::strtol(values[115].c_str(), nullptr, 10); }
    if (values.size() > 117) { OrmusMagicMax = (int32_t) std::strtol(values[117].c_str(), nullptr, 10); }
    if (values.size() > 118) { OrmusMagicLvl = (int32_t) std::strtol(values[118].c_str(), nullptr, 10); }
    if (values.size() > 119) { ElzixMin = (int32_t) std::strtol(values[119].c_str(), nullptr, 10); }
    if (values.size() > 120) { ElzixMax = (int32_t) std::strtol(values[120].c_str(), nullptr, 10); }
    if (values.size() > 121) { ElzixMagicMin = (int32_t) std::strtol(values[121].c_str(), nullptr, 10); }
    if (values.size() > 122) { ElzixMagicMax = (int32_t) std::strtol(values[122].c_str(), nullptr, 10); }
    if (values.size() > 123) { ElzixMagicLvl = (int32_t) std::strtol(values[123].c_str(), nullptr, 10); }
    if (values.size() > 124) { AshearaMin = (int32_t) std::strtol(values[124].c_str(), nullptr, 10); }
    if (values.size() > 125) { AshearaMax = (int32_t) std::strtol(values[125].c_str(), nullptr, 10); }
    if (values.size() > 126) { AshearaMagicMin = (int32_t) std::strtol(values[126].c_str(), nullptr, 10); }
    if (values.size() > 127) { AshearaMagicMax = (int32_t) std::strtol(values[127].c_str(), nullptr, 10); }
    if (values.size() > 128) { AshearaMagicLvl = (int32_t) std::strtol(values[128].c_str(), nullptr, 10); }
    if (values.size() > 129) { CainMin = (int32_t) std::strtol(values[129].c_str(), nullptr, 10); }
    if (values.size() > 130) { CainMax = (int32_t) std::strtol(values[130].c_str(), nullptr, 10); }
    if (values.size() > 131) { CainMagicMin = (int32_t) std::strtol(values[131].c_str(), nullptr, 10); }
    if (values.size() > 132) { CainMagicMax = (int32_t) std::strtol(values[132].c_str(), nullptr, 10); }
    if (values.size() > 133) { CainMagicLvl = (int32_t) std::strtol(values[133].c_str(), nullptr, 10); }
    if (values.size() > 134) { HalbuMin = (int32_t) std::strtol(values[134].c_str(), nullptr, 10); }
    if (values.size() > 135) { HalbuMax = (int32_t) std::strtol(values[135].c_str(), nullptr, 10); }
    if (values.size() > 136) { HalbuMagicMin = (int32_t) std::strtol(values[136].c_str(), nullptr, 10); }
    if (values.size() > 137) { HalbuMagicMax = (int32_t) std::strtol(values[137].c_str(), nullptr, 10); }
    if (values.size() > 138) { HalbuMagicLvl = (int32_t) std::strtol(values[138].c_str(), nullptr, 10); }
    if (values.size() > 139) { JamellaMin = (int32_t) std::strtol(values[139].c_str(), nullptr, 10); }
    if (values.size() > 140) { JamellaMax = (int32_t) std::strtol(values[140].c_str(), nullptr, 10); }
    if (values.size() > 141) { JamellaMagicMin = (int32_t) std::strtol(values[141].c_str(), nullptr, 10); }
    if (values.size() > 142) { JamellaMagicMax = (int32_t) std::strtol(values[142].c_str(), nullptr, 10); }
    if (values.size() > 143) { JamellaMagicLvl = (int32_t) std::strtol(values[143].c_str(), nullptr, 10); }
    if (values.size() > 144) { LarzukMin = (int32_t) std::strtol(values[144].c_str(), nullptr, 10); }
    if (values.size() > 145) { LarzukMax = (int32_t) std::strtol(values[145].c_str(), nullptr, 10); }
    if (values.size() > 146) { LarzukMagicMin = (int32_t) std::strtol(values[146].c_str(), nullptr, 10); }
    if (values.size() > 147) { LarzukMagicMax = (int32_t) std::strtol(values[147].c_str(), nullptr, 10); }
    if (values.size() > 148) { LarzukMagicLvl = (int32_t) std::strtol(values[148].c_str(), nullptr, 10); }
    if (values.size() > 153) { MalahMagicLvl = (int32_t) std::strtol(values[153].c_str(), nullptr, 10); }
    if (values.size() > 154) { AnyaMin = (int32_t) std::strtol(values[154].c_str(), nullptr, 10); }
    if (values.size() > 155) { AnyaMax = (int32_t) std::strtol(values[155].c_str(), nullptr, 10); }
    if (values.size() > 156) { AnyaMagicMin = (int32_t) std::strtol(values[156].c_str(), nullptr, 10); }
    if (values.size() > 157) { AnyaMagicMax = (int32_t) std::strtol(values[157].c_str(), nullptr, 10); }
    if (values.size() > 158) { AnyaMagicLvl = (int32_t) std::strtol(values[158].c_str(), nullptr, 10); }
    if (values.size() > 159) { Transform = (int32_t) std::strtol(values[159].c_str(), nullptr, 10); }
    if (values.size() > 160) { InvTrans = (int32_t) std::strtol(values[160].c_str(), nullptr, 10); }
    if (values.size() > 161) { SkipName = (int32_t) std::strtol(values[161].c_str(), nullptr, 10); }
    if (values.size() > 162) { NightmareUpgrade = values[162]; }
    if (values.size() > 163) { HellUpgrade = values[163]; }
    if (values.size() > 164) { Nameable = (int32_t) std::strtol(values[164].c_str(), nullptr, 10); }
    if (values.size() > 165) { PermStoreItem = (int32_t) std::strtol(values[165].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_armor> t_armor::readfile(std::string filename) {
    std::vector<t_armor> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_armor v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_armtype::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Token = values[1]; }

    return values.size();
  }

  std::vector<t_armtype> t_armtype::readfile(std::string filename) {
    std::vector<t_armtype> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_armtype v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_automagic::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { version = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { spawnable = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { rare = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { level = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 6) { levelreq = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 10) { frequency = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { group = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { mod1code = values[12]; }
    if (values.size() > 13) { mod1param = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { mod1min = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { mod1max = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { mod2code = values[16]; }
    if (values.size() > 18) { mod2min = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { mod2max = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { mod3code = values[20]; }
    if (values.size() > 22) { mod3min = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { mod3max = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { transformcolor = values[24]; }
    if (values.size() > 25) { itype1 = values[25]; }
    if (values.size() > 26) { itype2 = values[26]; }
    if (values.size() > 37) { multiply = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { add = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_automagic> t_automagic::readfile(std::string filename) {
    std::vector<t_automagic> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_automagic v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_automap::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { LevelName = values[0]; }
    if (values.size() > 1) { TileName = values[1]; }
    if (values.size() > 2) { Style = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { StartSequence = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { EndSequence = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Type1 = values[5]; }
    if (values.size() > 6) { Cel1 = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Type2 = values[7]; }
    if (values.size() > 8) { Cel2 = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { Type3 = values[9]; }
    if (values.size() > 10) { Cel3 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Type4 = values[11]; }
    if (values.size() > 12) { Cel4 = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_automap> t_automap::readfile(std::string filename) {
    std::vector<t_automap> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_automap v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_belts::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { numboxes = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { box1left = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { box1right = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { box1top = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { box1bottom = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { box2left = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { box2right = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { box2top = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { box2bottom = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { box3left = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { box3right = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { box3top = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { box3bottom = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { box4left = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { box4right = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { box4top = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { box4bottom = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { box5left = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { box5right = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { box5top = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { box5bottom = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { box6left = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { box6right = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { box6top = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { box6bottom = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { box7left = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { box7right = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { box7top = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { box7bottom = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { box8left = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { box8right = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { box8top = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { box8bottom = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { box9left = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { box9right = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { box9top = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { box9bottom = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { box10left = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { box10right = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { box10top = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { box10bottom = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { box11left = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { box11right = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { box11top = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { box11bottom = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { box12left = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { box12right = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { box12top = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { box12bottom = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { box13left = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { box13right = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { box13top = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { box13bottom = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { box14left = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { box14right = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { box14top = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { box14bottom = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { box15left = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { box15right = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { box15top = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { box15bottom = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { box16left = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { box16right = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { box16top = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { box16bottom = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { defaultItemTypeCol1 = values[66]; }
    if (values.size() > 68) { defaultItemTypeCol2 = values[68]; }
    if (values.size() > 70) { defaultItemTypeCol3 = values[70]; }
    if (values.size() > 72) { defaultItemTypeCol4 = values[72]; }
    if (values.size() > 73) { defaultItemCodeCol4 = values[73]; }

    return values.size();
  }

  std::vector<t_belts> t_belts::readfile(std::string filename) {
    std::vector<t_belts> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_belts v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_bodylocs::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { BodyLocation = values[0]; }
    if (values.size() > 1) { Code = values[1]; }

    return values.size();
  }

  std::vector<t_bodylocs> t_bodylocs::readfile(std::string filename) {
    std::vector<t_bodylocs> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_bodylocs v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_books::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { ScrollSpellCode = values[1]; }
    if (values.size() > 2) { BookSpellCode = values[2]; }
    if (values.size() > 3) { pSpell = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { SpellIcon = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { ScrollSkill = values[5]; }
    if (values.size() > 6) { BookSkill = values[6]; }
    if (values.size() > 7) { BaseCost = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { CostPerCharge = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_books> t_books::readfile(std::string filename) {
    std::vector<t_books> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_books v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_charstats::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { _class = values[0]; }
    if (values.size() > 1) { str = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { dex = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { _int = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { vit = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { stamina = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { hpadd = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { ManaRegen = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { ToHitFactor = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { WalkVelocity = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { RunVelocity = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { RunDrain = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { Comment = values[12]; }
    if (values.size() > 13) { LifePerLevel = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { StaminaPerLevel = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { ManaPerLevel = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { LifePerVitality = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { StaminaPerVitality = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { ManaPerMagic = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { StatPerLevel = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { SkillsPerLevel = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { LightRadius = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { BlockFactor = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { MinimumCastingDelay = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { StartSkill = values[24]; }
    if (values.size() > 25) { Skill1 = values[25]; }
    if (values.size() > 26) { Skill2 = values[26]; }
    if (values.size() > 27) { Skill3 = values[27]; }
    if (values.size() > 28) { Skill4 = values[28]; }
    if (values.size() > 29) { Skill5 = values[29]; }
    if (values.size() > 30) { Skill6 = values[30]; }
    if (values.size() > 31) { Skill7 = values[31]; }
    if (values.size() > 32) { Skill8 = values[32]; }
    if (values.size() > 33) { Skill9 = values[33]; }
    if (values.size() > 35) { StrAllSkills = values[35]; }
    if (values.size() > 36) { StrSkillTab1 = values[36]; }
    if (values.size() > 37) { StrSkillTab2 = values[37]; }
    if (values.size() > 38) { StrSkillTab3 = values[38]; }
    if (values.size() > 39) { StrClassOnly = values[39]; }
    if (values.size() > 40) { HealthPotionPercent = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { ManaPotionPercent = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { baseWClass = values[42]; }
    if (values.size() > 43) { item1 = values[43]; }
    if (values.size() > 44) { item1loc = values[44]; }
    if (values.size() > 45) { item1count = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { item1quality = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { item2 = values[47]; }
    if (values.size() > 48) { item2loc = values[48]; }
    if (values.size() > 49) { item2count = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { item2quality = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { item3 = values[51]; }
    if (values.size() > 53) { item3count = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { item3quality = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { item4 = values[55]; }
    if (values.size() > 57) { item4count = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { item4quality = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { item5 = values[59]; }
    if (values.size() > 61) { item5count = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { item5quality = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { item6 = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 65) { item6count = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { item6quality = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { item7 = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 69) { item7count = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { item7quality = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 71) { item8 = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 73) { item8count = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { item8quality = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { item9 = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 77) { item9count = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { item9quality = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 79) { item10 = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 81) { item10count = (int32_t) std::strtol(values[81].c_str(), nullptr, 10); }
    if (values.size() > 82) { item10quality = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_charstats> t_charstats::readfile(std::string filename) {
    std::vector<t_charstats> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_charstats v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_colors::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { TransformColor = values[0]; }
    if (values.size() > 1) { Code = values[1]; }

    return values.size();
  }

  std::vector<t_colors> t_colors::readfile(std::string filename) {
    std::vector<t_colors> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_colors v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_compcode::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { component = values[0]; }
    if (values.size() > 1) { code = values[1]; }

    return values.size();
  }

  std::vector<t_compcode> t_compcode::readfile(std::string filename) {
    std::vector<t_compcode> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_compcode v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_composit::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Token = values[1]; }

    return values.size();
  }

  std::vector<t_composit> t_composit::readfile(std::string filename) {
    std::vector<t_composit> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_composit v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_cubemain::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { description = values[0]; }
    if (values.size() > 1) { enabled = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { firstLadderSeason = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { lastLadderSeason = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 5) { version = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { op = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 10) { numinputs = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { input1 = values[11]; }
    if (values.size() > 12) { input2 = values[12]; }
    if (values.size() > 13) { input3 = values[13]; }
    if (values.size() > 14) { input4 = values[14]; }
    if (values.size() > 15) { input5 = values[15]; }
    if (values.size() > 16) { input6 = values[16]; }
    if (values.size() > 17) { input7 = values[17]; }
    if (values.size() > 18) { output = values[18]; }
    if (values.size() > 19) { lvl = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { plvl = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { ilvl = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { mod1 = values[22]; }
    if (values.size() > 24) { mod1param = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { mod1min = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { mod1max = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { mod2 = values[27]; }
    if (values.size() > 30) { mod2min = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { mod2max = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { mod3 = values[32]; }
    if (values.size() > 35) { mod3min = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { mod3max = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { mod4 = values[37]; }
    if (values.size() > 40) { mod4min = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { mod4max = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 105) { eol = (int32_t) std::strtol(values[105].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_cubemain> t_cubemain::readfile(std::string filename) {
    std::vector<t_cubemain> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_cubemain v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_cubemod::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { cubemodifiertype = values[0]; }
    if (values.size() > 1) { Code = values[1]; }

    return values.size();
  }

  std::vector<t_cubemod> t_cubemod::readfile(std::string filename) {
    std::vector<t_cubemod> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_cubemod v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_difficultylevels::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { ResistPenalty = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { ResistPenaltyNonExpansion = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { DeathExpPenalty = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { MonsterSkillBonus = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { MonsterFreezeDivisor = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { MonsterColdDivisor = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { AiCurseDivisor = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { LifeStealDivisor = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { ManaStealDivisor = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { UniqueDamageBonus = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { ChampionDamageBonus = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { PlayerDamagePercentVSPlayer = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { PlayerDamagePercentVSMercenary = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { PlayerDamagePercentVSPrimeEvil = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { PlayerHitReactBufferVSPlayer = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { PlayerHitReactBufferVSMonster = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { MercenaryDamagePercentVSPlayer = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { MercenaryDamagePercentVSMercenary = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { MercenaryDamagePercentVSBoss = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { MercenaryMaxStunLength = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { PrimeEvilDamagePercentVSPlayer = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { PrimeEvilDamagePercentVSMercenary = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { PrimeEvilDamagePercentVSPet = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { PetDamagePercentVSPlayer = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { MonsterCEDamagePercent = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { MonsterFireEnchantExplosionDamagePercent = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { StaticFieldMin = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { GambleRare = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { GambleSet = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { GambleUnique = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { GambleUber = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { GambleUltra = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_difficultylevels> t_difficultylevels::readfile(std::string filename) {
    std::vector<t_difficultylevels> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_difficultylevels v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_elemtypes::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { ElementalType = values[0]; }
    if (values.size() > 1) { Code = values[1]; }

    return values.size();
  }

  std::vector<t_elemtypes> t_elemtypes::readfile(std::string filename) {
    std::vector<t_elemtypes> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_elemtypes v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_events::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { event = values[0]; }
    if (values.size() > 1) { description = values[1]; }

    return values.size();
  }

  std::vector<t_events> t_events::readfile(std::string filename) {
    std::vector<t_events> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_events v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_experience::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Level = values[0]; }
    if (values.size() > 1) { Amazon = std::strtoll(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Sorceress = std::strtoll(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Necromancer = std::strtoll(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Paladin = std::strtoll(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Barbarian = std::strtoll(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Druid = std::strtoll(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Assassin = std::strtoll(values[7].c_str(), nullptr, 10); }
    if (values.size() > 9) { ExpRatio = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_experience> t_experience::readfile(std::string filename) {
    std::vector<t_experience> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_experience v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_gamble::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { code = values[1]; }

    return values.size();
  }

  std::vector<t_gamble> t_gamble::readfile(std::string filename) {
    std::vector<t_gamble> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_gamble v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_gems::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { letter = values[1]; }
    if (values.size() > 2) { transform = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { code = values[3]; }
    if (values.size() > 4) { weaponMod1Code = values[4]; }
    if (values.size() > 5) { weaponMod1Param = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { weaponMod1Min = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { weaponMod1Max = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { weaponMod2Code = values[8]; }
    if (values.size() > 9) { weaponMod2Param = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { weaponMod2Min = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { weaponMod2Max = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { weaponMod3Code = values[12]; }
    if (values.size() > 13) { weaponMod3Param = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { weaponMod3Min = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { weaponMod3Max = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { helmMod1Code = values[16]; }
    if (values.size() > 17) { helmMod1Param = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { helmMod1Min = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { helmMod1Max = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { helmMod2Code = values[20]; }
    if (values.size() > 21) { helmMod2Param = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { helmMod2Min = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { helmMod2Max = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 25) { helmMod3Param = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { helmMod3Min = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { helmMod3Max = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { shieldMod1Code = values[28]; }
    if (values.size() > 29) { shieldMod1Param = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { shieldMod1Min = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { shieldMod1Max = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { shieldMod2Code = values[32]; }
    if (values.size() > 33) { shieldMod2Param = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { shieldMod2Min = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { shieldMod2Max = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 37) { shieldMod3Param = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { shieldMod3Min = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { shieldMod3Max = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_gems> t_gems::readfile(std::string filename) {
    std::vector<t_gems> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_gems v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_hireling::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Hireling = values[0]; }
    if (values.size() > 1) { SubType = values[1]; }
    if (values.size() > 2) { Version = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Id = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Class = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Act = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Difficulty = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Level = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { Seller = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { NameFirst = values[9]; }
    if (values.size() > 10) { NameLast = values[10]; }
    if (values.size() > 11) { Gold = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { ExpLvl = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { HP = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { HPLvl = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { Defense = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { DefLvl = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { Str = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { StrLvl = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { Dex = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { DexLvl = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { AR = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { ARLvl = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { DmgMin = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { DmgMax = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { DmgLvl = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { ResistFire = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { ResistFireLvl = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { ResistCold = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { ResistColdLvl = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { ResistLightning = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { ResistLightningLvl = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { ResistPoison = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { ResistPoisonLvl = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { HireDesc = values[34]; }
    if (values.size() > 35) { DefaultChance = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { Skill1 = values[36]; }
    if (values.size() > 37) { Mode1 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { Chance1 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { ChancePerLvl1 = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { Level1 = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { LvlPerLvl1 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { Skill2 = values[42]; }
    if (values.size() > 43) { Mode2 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { Chance2 = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { ChancePerLvl2 = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { Level2 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { LvlPerLvl2 = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { Skill3 = values[48]; }
    if (values.size() > 49) { Mode3 = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { Chance3 = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { ChancePerLvl3 = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { Level3 = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { LvlPerLvl3 = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 72) { HiringMaxLevelDifference = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { resurrectcostmultiplier = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { resurrectcostdivisor = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { resurrectcostmax = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 76) { equivalentcharclass = values[76]; }

    return values.size();
  }

  std::vector<t_hireling> t_hireling::readfile(std::string filename) {
    std::vector<t_hireling> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_hireling v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_hitclass::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { HitClass = values[0]; }
    if (values.size() > 1) { Code = values[1]; }

    return values.size();
  }

  std::vector<t_hitclass> t_hitclass::readfile(std::string filename) {
    std::vector<t_hitclass> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_hitclass v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_inventory::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { _class = values[0]; }
    if (values.size() > 1) { invLeft = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { invRight = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { invTop = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { invBottom = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { gridX = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { gridY = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { gridLeft = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { gridRight = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { gridTop = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { gridBottom = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { gridBoxWidth = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { gridBoxHeight = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { rArmLeft = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { rArmRight = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { rArmTop = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { rArmBottom = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { rArmWidth = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { rArmHeight = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { torsoLeft = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { torsoRight = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { torsoTop = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { torsoBottom = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { torsoWidth = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { torsoHeight = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { lArmLeft = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { lArmRight = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { lArmTop = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { lArmBottom = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { lArmWidth = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { lArmHeight = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { headLeft = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { headRight = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { headTop = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { headBottom = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { headWidth = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { headHeight = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { neckLeft = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { neckRight = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { neckTop = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { neckBottom = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { neckWidth = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { neckHeight = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { rHandLeft = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { rHandRight = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { rHandTop = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { rHandBottom = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { rHandWidth = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { rHandHeight = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { lHandLeft = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { lHandRight = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { lHandTop = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { lHandBottom = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { lHandWidth = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { lHandHeight = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { beltLeft = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { beltRight = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { beltTop = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { beltBottom = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { beltWidth = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { beltHeight = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { feetLeft = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { feetRight = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { feetTop = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { feetBottom = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { feetWidth = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { feetHeight = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { glovesLeft = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { glovesRight = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { glovesTop = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { glovesBottom = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 71) { glovesWidth = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { glovesHeight = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_inventory> t_inventory::readfile(std::string filename) {
    std::vector<t_inventory> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_inventory v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_itemratio::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Function = values[0]; }
    if (values.size() > 1) { Version = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Uber = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { ClassSpecific = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Unique = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { UniqueDivisor = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { UniqueMin = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Rare = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { RareDivisor = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { RareMin = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { Set = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { SetDivisor = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { SetMin = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Magic = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { MagicDivisor = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { MagicMin = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { HiQuality = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { HiQualityDivisor = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { Normal = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { NormalDivisor = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_itemratio> t_itemratio::readfile(std::string filename) {
    std::vector<t_itemratio> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_itemratio v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_itemstatcost::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Stat = values[0]; }
    if (values.size() > 1) { ID = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { SendOther = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Signed = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { SendBits = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { SendParamBits = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { UpdateAnimRate = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Saved = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { CSvSigned = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { CSvBits = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 11) { fCallback = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { fMin = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { MinAccr = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { Encode = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { Add = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { Multiply = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { ValShift = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { _109SaveBits = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { _109SaveAdd = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { SaveBits = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { SaveAdd = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { SaveParamBits = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { keepzero = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { op = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { opparam = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { opbase = values[26]; }
    if (values.size() > 27) { opstat1 = values[27]; }
    if (values.size() > 28) { opstat2 = values[28]; }
    if (values.size() > 29) { opstat3 = values[29]; }
    if (values.size() > 30) { direct = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { maxstat = values[31]; }
    if (values.size() > 32) { damagerelated = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { itemevent1 = values[33]; }
    if (values.size() > 34) { itemeventfunc1 = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { itemevent2 = values[35]; }
    if (values.size() > 36) { itemeventfunc2 = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { descpriority = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { descfunc = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { descval = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { descstrpos = values[40]; }
    if (values.size() > 41) { descstrneg = values[41]; }
    if (values.size() > 42) { descstr2 = values[42]; }
    if (values.size() > 43) { dgrp = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { dgrpfunc = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 46) { dgrpstrpos = values[46]; }
    if (values.size() > 47) { dgrpstrneg = values[47]; }
    if (values.size() > 49) { stuff = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { advdisplay = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { eol = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_itemstatcost> t_itemstatcost::readfile(std::string filename) {
    std::vector<t_itemstatcost> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_itemstatcost v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_itemtypes::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { ItemType = values[0]; }
    if (values.size() > 1) { Code = values[1]; }
    if (values.size() > 2) { Equiv1 = values[2]; }
    if (values.size() > 3) { Equiv2 = values[3]; }
    if (values.size() > 4) { Repair = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Body = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { BodyLoc1 = values[6]; }
    if (values.size() > 7) { BodyLoc2 = values[7]; }
    if (values.size() > 8) { Shoots = values[8]; }
    if (values.size() > 9) { Quiver = values[9]; }
    if (values.size() > 10) { Throwable = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Reload = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { ReEquip = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { AutoStack = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { Magic = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { Rare = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { Normal = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { Beltable = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { MaxSockets1 = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { MaxSocketsLevelThreshold1 = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { MaxSockets2 = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { MaxSocketsLevelThreshold2 = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { MaxSockets3 = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { TreasureClass = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { Rarity = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { StaffMods = values[25]; }
    if (values.size() > 26) { Class = values[26]; }
    if (values.size() > 27) { VarInvGfx = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { InvGfx1 = values[28]; }
    if (values.size() > 29) { InvGfx2 = values[29]; }
    if (values.size() > 30) { InvGfx3 = values[30]; }
    if (values.size() > 31) { InvGfx4 = values[31]; }
    if (values.size() > 32) { InvGfx5 = values[32]; }
    if (values.size() > 33) { InvGfx6 = values[33]; }
    if (values.size() > 34) { StorePage = values[34]; }
    if (values.size() > 35) { eol = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { UICategory = values[36]; }
    if (values.size() > 37) { RunewordCategory1 = values[37]; }
    if (values.size() > 38) { RunewordCategory2 = values[38]; }
    if (values.size() > 39) { Restricted = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_itemtypes> t_itemtypes::readfile(std::string filename) {
    std::vector<t_itemtypes> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_itemtypes v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_itemuicategories::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { isEquipment = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { ParentCategory = values[2]; }
    if (values.size() > 3) { QualityFilter = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { NumColumns = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_itemuicategories> t_itemuicategories::readfile(std::string filename) {
    std::vector<t_itemuicategories> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_itemuicategories v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_levelgroups::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { LevelGroupId = values[0]; }
    if (values.size() > 1) { ParentLevelGroupId = values[1]; }
    if (values.size() > 2) { CompleteThreshold = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Effect = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Name = values[4]; }
    if (values.size() > 5) { NameString = values[5]; }

    return values.size();
  }

  std::vector<t_levelgroups> t_levelgroups::readfile(std::string filename) {
    std::vector<t_levelgroups> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_levelgroups v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_levels::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { StringName = values[1]; }
    if (values.size() > 2) { Id = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Pal = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Act = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { QuestFlag = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { QuestFlagEx = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Layer = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { SizeX = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { SizeY = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { SizeXN = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { SizeYN = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { SizeXH = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { SizeYH = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { OffsetX = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { OffsetY = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { Depend = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { Teleport = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { Rain = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { Mud = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { NoPer = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { LOSDraw = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { FloorFilter = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { BlankScreen = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { DrawEdges = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { IsInside = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { DrlgType = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { LevelType = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { SubType = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { SubTheme = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { SubWaypoint = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { SubShrine = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { Vis0 = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { Vis1 = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { Vis2 = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { Vis3 = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { Vis4 = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { Vis5 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { Vis6 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { Vis7 = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { Warp0 = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { Warp1 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { Warp2 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { Warp3 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { Warp4 = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { Warp5 = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { Warp6 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { Warp7 = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { Intensity = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { Red = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { Green = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { Blue = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { Portal = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { Position = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { SaveMonsters = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { Quest = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { WarpDist = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { MonLvl = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { MonLvlN = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { MonLvlH = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { MonLvlEx = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { MonLvlExN = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { MonLvlExH = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { MonDen = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { MonDenN = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { MonDenH = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { MonUMin = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { MonUMax = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { MonUMinN = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { MonUMaxN = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { MonUMinH = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 71) { MonUMaxH = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { MonWndr = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { MonSpcWalk = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { NumMon = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { mon1 = values[75]; }
    if (values.size() > 76) { mon2 = values[76]; }
    if (values.size() > 77) { mon3 = values[77]; }
    if (values.size() > 78) { mon4 = values[78]; }
    if (values.size() > 79) { mon5 = values[79]; }
    if (values.size() > 80) { mon6 = values[80]; }
    if (values.size() > 81) { mon7 = values[81]; }
    if (values.size() > 82) { mon8 = values[82]; }
    if (values.size() > 100) { rangedspawn = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { nmon1 = values[101]; }
    if (values.size() > 102) { nmon2 = values[102]; }
    if (values.size() > 103) { nmon3 = values[103]; }
    if (values.size() > 104) { nmon4 = values[104]; }
    if (values.size() > 105) { nmon5 = values[105]; }
    if (values.size() > 106) { nmon6 = values[106]; }
    if (values.size() > 107) { nmon7 = values[107]; }
    if (values.size() > 108) { nmon8 = values[108]; }
    if (values.size() > 109) { nmon9 = values[109]; }
    if (values.size() > 110) { nmon10 = values[110]; }
    if (values.size() > 126) { umon1 = values[126]; }
    if (values.size() > 127) { umon2 = values[127]; }
    if (values.size() > 128) { umon3 = values[128]; }
    if (values.size() > 129) { umon4 = values[129]; }
    if (values.size() > 130) { umon5 = values[130]; }
    if (values.size() > 131) { umon6 = values[131]; }
    if (values.size() > 132) { umon7 = values[132]; }
    if (values.size() > 133) { umon8 = values[133]; }
    if (values.size() > 151) { cmon1 = values[151]; }
    if (values.size() > 152) { cmon2 = values[152]; }
    if (values.size() > 153) { cmon3 = values[153]; }
    if (values.size() > 154) { cmon4 = values[154]; }
    if (values.size() > 155) { cpct1 = (int32_t) std::strtol(values[155].c_str(), nullptr, 10); }
    if (values.size() > 156) { cpct2 = (int32_t) std::strtol(values[156].c_str(), nullptr, 10); }
    if (values.size() > 157) { cpct3 = (int32_t) std::strtol(values[157].c_str(), nullptr, 10); }
    if (values.size() > 158) { cpct4 = (int32_t) std::strtol(values[158].c_str(), nullptr, 10); }
    if (values.size() > 163) { Themes = (int32_t) std::strtol(values[163].c_str(), nullptr, 10); }
    if (values.size() > 164) { SoundEnv = (int32_t) std::strtol(values[164].c_str(), nullptr, 10); }
    if (values.size() > 165) { Waypoint = (int32_t) std::strtol(values[165].c_str(), nullptr, 10); }
    if (values.size() > 166) { LevelName = values[166]; }
    if (values.size() > 167) { LevelWarp = values[167]; }
    if (values.size() > 168) { LevelEntry = values[168]; }
    if (values.size() > 169) { ObjGrp0 = (int32_t) std::strtol(values[169].c_str(), nullptr, 10); }
    if (values.size() > 170) { ObjGrp1 = (int32_t) std::strtol(values[170].c_str(), nullptr, 10); }
    if (values.size() > 171) { ObjGrp2 = (int32_t) std::strtol(values[171].c_str(), nullptr, 10); }
    if (values.size() > 172) { ObjGrp3 = (int32_t) std::strtol(values[172].c_str(), nullptr, 10); }
    if (values.size() > 173) { ObjGrp4 = (int32_t) std::strtol(values[173].c_str(), nullptr, 10); }
    if (values.size() > 174) { ObjGrp5 = (int32_t) std::strtol(values[174].c_str(), nullptr, 10); }
    if (values.size() > 175) { ObjGrp6 = (int32_t) std::strtol(values[175].c_str(), nullptr, 10); }
    if (values.size() > 176) { ObjGrp7 = (int32_t) std::strtol(values[176].c_str(), nullptr, 10); }
    if (values.size() > 177) { ObjPrb0 = (int32_t) std::strtol(values[177].c_str(), nullptr, 10); }
    if (values.size() > 178) { ObjPrb1 = (int32_t) std::strtol(values[178].c_str(), nullptr, 10); }
    if (values.size() > 179) { ObjPrb2 = (int32_t) std::strtol(values[179].c_str(), nullptr, 10); }
    if (values.size() > 180) { ObjPrb3 = (int32_t) std::strtol(values[180].c_str(), nullptr, 10); }
    if (values.size() > 181) { ObjPrb4 = (int32_t) std::strtol(values[181].c_str(), nullptr, 10); }
    if (values.size() > 182) { ObjPrb5 = (int32_t) std::strtol(values[182].c_str(), nullptr, 10); }
    if (values.size() > 183) { ObjPrb6 = (int32_t) std::strtol(values[183].c_str(), nullptr, 10); }
    if (values.size() > 184) { ObjPrb7 = (int32_t) std::strtol(values[184].c_str(), nullptr, 10); }
    if (values.size() > 185) { LevelGroup = values[185]; }
    if (values.size() > 186) { PreventTownPortal = (int32_t) std::strtol(values[186].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_levels> t_levels::readfile(std::string filename) {
    std::vector<t_levels> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_levels v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_lowqualityitems::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }

    return values.size();
  }

  std::vector<t_lowqualityitems> t_lowqualityitems::readfile(std::string filename) {
    std::vector<t_lowqualityitems> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_lowqualityitems v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_lvlmaze::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Level = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Rooms = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { RoomsN = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { RoomsH = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { SizeX = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { SizeY = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Merge = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_lvlmaze> t_lvlmaze::readfile(std::string filename) {
    std::vector<t_lvlmaze> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_lvlmaze v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_lvlprest::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Def = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { LevelId = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Populate = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Logicals = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Outdoors = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Animate = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { KillEdge = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { FillBlanks = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { SizeX = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { SizeY = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { AutoMap = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { Scan = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Pops = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { PopPad = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { Files = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { File1 = values[16]; }
    if (values.size() > 17) { File2 = values[17]; }
    if (values.size() > 18) { File3 = values[18]; }
    if (values.size() > 19) { File4 = values[19]; }
    if (values.size() > 20) { File5 = values[20]; }
    if (values.size() > 21) { File6 = values[21]; }
    if (values.size() > 22) { Dt1Mask = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_lvlprest> t_lvlprest::readfile(std::string filename) {
    std::vector<t_lvlprest> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_lvlprest v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_lvlsub::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Type = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { File = values[2]; }
    if (values.size() > 3) { CheckAll = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { BordType = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { GridSize = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Dt1Mask = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Prob0 = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { Trials0 = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { Max0 = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { Prob1 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Trials1 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { Max1 = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Prob2 = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { Trials2 = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { Max2 = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { Prob3 = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { Trials3 = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { Max3 = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { Prob4 = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { Trials4 = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { Max4 = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_lvlsub> t_lvlsub::readfile(std::string filename) {
    std::vector<t_lvlsub> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_lvlsub v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_lvltypes::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Id = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { File1 = values[2]; }
    if (values.size() > 3) { File2 = values[3]; }
    if (values.size() > 4) { File3 = values[4]; }
    if (values.size() > 5) { File4 = values[5]; }
    if (values.size() > 6) { File5 = values[6]; }
    if (values.size() > 7) { File6 = values[7]; }
    if (values.size() > 8) { File7 = values[8]; }
    if (values.size() > 9) { File8 = values[9]; }
    if (values.size() > 10) { File9 = values[10]; }
    if (values.size() > 11) { File10 = values[11]; }
    if (values.size() > 12) { File11 = values[12]; }
    if (values.size() > 13) { File12 = values[13]; }
    if (values.size() > 14) { File13 = values[14]; }
    if (values.size() > 15) { File14 = values[15]; }
    if (values.size() > 16) { File15 = values[16]; }
    if (values.size() > 17) { File16 = values[17]; }
    if (values.size() > 18) { File17 = values[18]; }
    if (values.size() > 19) { File18 = values[19]; }
    if (values.size() > 20) { File19 = values[20]; }
    if (values.size() > 21) { File20 = values[21]; }
    if (values.size() > 22) { File21 = values[22]; }
    if (values.size() > 23) { File22 = values[23]; }
    if (values.size() > 24) { File23 = values[24]; }
    if (values.size() > 25) { File24 = values[25]; }
    if (values.size() > 26) { File25 = values[26]; }
    if (values.size() > 27) { File26 = values[27]; }
    if (values.size() > 28) { File27 = values[28]; }
    if (values.size() > 29) { File28 = values[29]; }
    if (values.size() > 30) { File29 = values[30]; }
    if (values.size() > 31) { File30 = values[31]; }
    if (values.size() > 32) { File31 = values[32]; }
    if (values.size() > 33) { File32 = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { Act = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_lvltypes> t_lvltypes::readfile(std::string filename) {
    std::vector<t_lvltypes> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_lvltypes v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_lvlwarp::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Id = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { SelectX = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { SelectY = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { SelectDX = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { SelectDY = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { ExitWalkX = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { ExitWalkY = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { OffsetX = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { OffsetY = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { LitVersion = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Tiles = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { NoInteract = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Direction = values[13]; }
    if (values.size() > 14) { UniqueId = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_lvlwarp> t_lvlwarp::readfile(std::string filename) {
    std::vector<t_lvlwarp> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_lvlwarp v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_magicprefix::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { version = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { spawnable = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { rare = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { level = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { maxlevel = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { levelreq = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { classspecific = values[7]; }
    if (values.size() > 10) { frequency = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { group = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { mod1code = values[12]; }
    if (values.size() > 13) { mod1param = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { mod1min = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { mod1max = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { mod2code = values[16]; }
    if (values.size() > 17) { mod2param = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { mod2min = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { mod2max = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { mod3code = values[20]; }
    if (values.size() > 22) { mod3min = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { mod3max = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { transformcolor = values[24]; }
    if (values.size() > 25) { itype1 = values[25]; }
    if (values.size() > 26) { itype2 = values[26]; }
    if (values.size() > 27) { itype3 = values[27]; }
    if (values.size() > 28) { itype4 = values[28]; }
    if (values.size() > 29) { itype5 = values[29]; }
    if (values.size() > 30) { itype6 = values[30]; }
    if (values.size() > 31) { itype7 = values[31]; }
    if (values.size() > 32) { etype1 = values[32]; }
    if (values.size() > 33) { etype2 = values[33]; }
    if (values.size() > 34) { etype3 = values[34]; }
    if (values.size() > 35) { etype4 = values[35]; }
    if (values.size() > 36) { etype5 = values[36]; }
    if (values.size() > 37) { multiply = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { add = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_magicprefix> t_magicprefix::readfile(std::string filename) {
    std::vector<t_magicprefix> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_magicprefix v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_magicsuffix::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { version = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { spawnable = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { rare = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { level = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { maxlevel = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { levelreq = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 8) { _class = values[8]; }
    if (values.size() > 9) { classlevelreq = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { frequency = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { group = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { mod1code = values[12]; }
    if (values.size() > 13) { mod1param = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { mod1min = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { mod1max = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { mod2code = values[16]; }
    if (values.size() > 17) { mod2param = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { mod2min = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { mod2max = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { mod3code = values[20]; }
    if (values.size() > 21) { mod3param = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { mod3min = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { mod3max = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { transformcolor = values[24]; }
    if (values.size() > 25) { itype1 = values[25]; }
    if (values.size() > 26) { itype2 = values[26]; }
    if (values.size() > 27) { itype3 = values[27]; }
    if (values.size() > 28) { itype4 = values[28]; }
    if (values.size() > 29) { itype5 = values[29]; }
    if (values.size() > 30) { itype6 = values[30]; }
    if (values.size() > 31) { itype7 = values[31]; }
    if (values.size() > 32) { etype1 = values[32]; }
    if (values.size() > 33) { etype2 = values[33]; }
    if (values.size() > 34) { etype3 = values[34]; }
    if (values.size() > 37) { multiply = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { add = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_magicsuffix> t_magicsuffix::readfile(std::string filename) {
    std::vector<t_magicsuffix> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_magicsuffix v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_misc::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { compactsave = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { version = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { level = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { ShowLevel = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { levelreq = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 8) { rarity = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { spawnable = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 11) { speed = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { nodurability = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { cost = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { gamblecost = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { code = values[15]; }
    if (values.size() > 16) { alternategfx = values[16]; }
    if (values.size() > 17) { namestr = values[17]; }
    if (values.size() > 18) { component = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { invwidth = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { invheight = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { hasinv = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { gemsockets = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { gemapplytype = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { flippyfile = values[24]; }
    if (values.size() > 25) { invfile = values[25]; }
    if (values.size() > 26) { uniqueinvfile = values[26]; }
    if (values.size() > 27) { Transmogrify = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { TMogType = values[28]; }
    if (values.size() > 29) { TMogMin = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { TMogMax = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { useable = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { type = values[32]; }
    if (values.size() > 33) { type2 = values[33]; }
    if (values.size() > 34) { dropsound = values[34]; }
    if (values.size() > 35) { dropsfxframe = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { usesound = values[36]; }
    if (values.size() > 37) { unique = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { transparent = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { transtbl = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { lightradius = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { belt = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { autobelt = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { stackable = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { minstack = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { maxstack = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { spawnstack = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { quest = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { questdiffcheck = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { missiletype = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { spellicon = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { pSpell = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { state = values[52]; }
    if (values.size() > 53) { cstate1 = values[53]; }
    if (values.size() > 54) { cstate2 = values[54]; }
    if (values.size() > 55) { len = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { stat1 = values[56]; }
    if (values.size() > 57) { calc1 = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { stat2 = values[58]; }
    if (values.size() > 59) { calc2 = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 62) { spelldesc = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { spelldescstr = values[63]; }
    if (values.size() > 64) { spelldescstr2 = values[64]; }
    if (values.size() > 65) { spelldesccalc = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { spelldesccolor = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { durwarning = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { qntwarning = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { gemoffset = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { BetterGem = values[70]; }
    if (values.size() > 71) { bitfield1 = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { CharsiMin = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { CharsiMax = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 76) { CharsiMagicLvl = (int32_t) std::strtol(values[76].c_str(), nullptr, 10); }
    if (values.size() > 77) { GheedMin = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { GheedMax = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 79) { GheedMagicMin = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 80) { GheedMagicMax = (int32_t) std::strtol(values[80].c_str(), nullptr, 10); }
    if (values.size() > 81) { GheedMagicLvl = (int32_t) std::strtol(values[81].c_str(), nullptr, 10); }
    if (values.size() > 82) { AkaraMin = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }
    if (values.size() > 83) { AkaraMax = (int32_t) std::strtol(values[83].c_str(), nullptr, 10); }
    if (values.size() > 84) { AkaraMagicMin = (int32_t) std::strtol(values[84].c_str(), nullptr, 10); }
    if (values.size() > 85) { AkaraMagicMax = (int32_t) std::strtol(values[85].c_str(), nullptr, 10); }
    if (values.size() > 86) { AkaraMagicLvl = (int32_t) std::strtol(values[86].c_str(), nullptr, 10); }
    if (values.size() > 87) { FaraMin = (int32_t) std::strtol(values[87].c_str(), nullptr, 10); }
    if (values.size() > 88) { FaraMax = (int32_t) std::strtol(values[88].c_str(), nullptr, 10); }
    if (values.size() > 89) { FaraMagicMin = (int32_t) std::strtol(values[89].c_str(), nullptr, 10); }
    if (values.size() > 90) { FaraMagicMax = (int32_t) std::strtol(values[90].c_str(), nullptr, 10); }
    if (values.size() > 91) { FaraMagicLvl = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }
    if (values.size() > 92) { LysanderMin = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { LysanderMax = (int32_t) std::strtol(values[93].c_str(), nullptr, 10); }
    if (values.size() > 94) { LysanderMagicMin = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 95) { LysanderMagicMax = (int32_t) std::strtol(values[95].c_str(), nullptr, 10); }
    if (values.size() > 96) { LysanderMagicLvl = (int32_t) std::strtol(values[96].c_str(), nullptr, 10); }
    if (values.size() > 97) { DrognanMin = (int32_t) std::strtol(values[97].c_str(), nullptr, 10); }
    if (values.size() > 98) { DrognanMax = (int32_t) std::strtol(values[98].c_str(), nullptr, 10); }
    if (values.size() > 99) { DrognanMagicMin = (int32_t) std::strtol(values[99].c_str(), nullptr, 10); }
    if (values.size() > 100) { DrognanMagicMax = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { DrognanMagicLvl = (int32_t) std::strtol(values[101].c_str(), nullptr, 10); }
    if (values.size() > 102) { HratliMin = (int32_t) std::strtol(values[102].c_str(), nullptr, 10); }
    if (values.size() > 103) { HratliMax = (int32_t) std::strtol(values[103].c_str(), nullptr, 10); }
    if (values.size() > 104) { HratliMagicMin = (int32_t) std::strtol(values[104].c_str(), nullptr, 10); }
    if (values.size() > 105) { HratliMagicMax = (int32_t) std::strtol(values[105].c_str(), nullptr, 10); }
    if (values.size() > 106) { HratliMagicLvl = (int32_t) std::strtol(values[106].c_str(), nullptr, 10); }
    if (values.size() > 107) { AlkorMin = (int32_t) std::strtol(values[107].c_str(), nullptr, 10); }
    if (values.size() > 108) { AlkorMax = (int32_t) std::strtol(values[108].c_str(), nullptr, 10); }
    if (values.size() > 111) { AlkorMagicLvl = (int32_t) std::strtol(values[111].c_str(), nullptr, 10); }
    if (values.size() > 112) { OrmusMin = (int32_t) std::strtol(values[112].c_str(), nullptr, 10); }
    if (values.size() > 113) { OrmusMax = (int32_t) std::strtol(values[113].c_str(), nullptr, 10); }
    if (values.size() > 114) { OrmusMagicMin = (int32_t) std::strtol(values[114].c_str(), nullptr, 10); }
    if (values.size() > 115) { OrmusMagicMax = (int32_t) std::strtol(values[115].c_str(), nullptr, 10); }
    if (values.size() > 116) { OrmusMagicLvl = (int32_t) std::strtol(values[116].c_str(), nullptr, 10); }
    if (values.size() > 117) { ElzixMin = (int32_t) std::strtol(values[117].c_str(), nullptr, 10); }
    if (values.size() > 118) { ElzixMax = (int32_t) std::strtol(values[118].c_str(), nullptr, 10); }
    if (values.size() > 121) { ElzixMagicLvl = (int32_t) std::strtol(values[121].c_str(), nullptr, 10); }
    if (values.size() > 122) { AshearaMin = (int32_t) std::strtol(values[122].c_str(), nullptr, 10); }
    if (values.size() > 123) { AshearaMax = (int32_t) std::strtol(values[123].c_str(), nullptr, 10); }
    if (values.size() > 126) { AshearaMagicLvl = (int32_t) std::strtol(values[126].c_str(), nullptr, 10); }
    if (values.size() > 127) { CainMin = (int32_t) std::strtol(values[127].c_str(), nullptr, 10); }
    if (values.size() > 128) { CainMax = (int32_t) std::strtol(values[128].c_str(), nullptr, 10); }
    if (values.size() > 131) { CainMagicLvl = (int32_t) std::strtol(values[131].c_str(), nullptr, 10); }
    if (values.size() > 132) { HalbuMin = (int32_t) std::strtol(values[132].c_str(), nullptr, 10); }
    if (values.size() > 133) { HalbuMax = (int32_t) std::strtol(values[133].c_str(), nullptr, 10); }
    if (values.size() > 136) { HalbuMagicLvl = (int32_t) std::strtol(values[136].c_str(), nullptr, 10); }
    if (values.size() > 137) { MalahMin = (int32_t) std::strtol(values[137].c_str(), nullptr, 10); }
    if (values.size() > 138) { MalahMax = (int32_t) std::strtol(values[138].c_str(), nullptr, 10); }
    if (values.size() > 141) { MalahMagicLvl = (int32_t) std::strtol(values[141].c_str(), nullptr, 10); }
    if (values.size() > 142) { LarzukMin = (int32_t) std::strtol(values[142].c_str(), nullptr, 10); }
    if (values.size() > 143) { LarzukMax = (int32_t) std::strtol(values[143].c_str(), nullptr, 10); }
    if (values.size() > 146) { LarzukMagicLvl = (int32_t) std::strtol(values[146].c_str(), nullptr, 10); }
    if (values.size() > 147) { AnyaMin = (int32_t) std::strtol(values[147].c_str(), nullptr, 10); }
    if (values.size() > 148) { AnyaMax = (int32_t) std::strtol(values[148].c_str(), nullptr, 10); }
    if (values.size() > 151) { AnyaMagicLvl = (int32_t) std::strtol(values[151].c_str(), nullptr, 10); }
    if (values.size() > 152) { JamellaMin = (int32_t) std::strtol(values[152].c_str(), nullptr, 10); }
    if (values.size() > 153) { JamellaMax = (int32_t) std::strtol(values[153].c_str(), nullptr, 10); }
    if (values.size() > 154) { JamellaMagicMin = (int32_t) std::strtol(values[154].c_str(), nullptr, 10); }
    if (values.size() > 155) { JamellaMagicMax = (int32_t) std::strtol(values[155].c_str(), nullptr, 10); }
    if (values.size() > 156) { JamellaMagicLvl = (int32_t) std::strtol(values[156].c_str(), nullptr, 10); }
    if (values.size() > 157) { Transform = (int32_t) std::strtol(values[157].c_str(), nullptr, 10); }
    if (values.size() > 158) { InvTrans = (int32_t) std::strtol(values[158].c_str(), nullptr, 10); }
    if (values.size() > 159) { SkipName = (int32_t) std::strtol(values[159].c_str(), nullptr, 10); }
    if (values.size() > 160) { NightmareUpgrade = values[160]; }
    if (values.size() > 161) { HellUpgrade = values[161]; }
    if (values.size() > 164) { PermStoreItem = (int32_t) std::strtol(values[164].c_str(), nullptr, 10); }
    if (values.size() > 165) { multibuy = (int32_t) std::strtol(values[165].c_str(), nullptr, 10); }
    if (values.size() > 167) { EventItem = (int32_t) std::strtol(values[167].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_misc> t_misc::readfile(std::string filename) {
    std::vector<t_misc> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_misc v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_misscalc::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { code = values[0]; }
    if (values.size() > 1) { description = values[1]; }

    return values.size();
  }

  std::vector<t_misscalc> t_misscalc::readfile(std::string filename) {
    std::vector<t_misscalc> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_misscalc v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_missiles::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Missile = values[0]; }
    if (values.size() > 1) { ID = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { pCltDoFunc = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { pCltHitFunc = values[3]; }
    if (values.size() > 4) { pSrvDoFunc = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { pSrvHitFunc = values[5]; }
    if (values.size() > 6) { pSrvDmgFunc = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { SrvCalc1 = values[7]; }
    if (values.size() > 8) { srvcalc1desc = values[8]; }
    if (values.size() > 9) { Param1 = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { param1desc = values[10]; }
    if (values.size() > 11) { Param2 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { param2desc = values[12]; }
    if (values.size() > 13) { Param3 = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { param3desc = values[14]; }
    if (values.size() > 15) { Param4 = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { param4desc = values[16]; }
    if (values.size() > 17) { Param5 = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { param5desc = values[18]; }
    if (values.size() > 19) { CltCalc1 = values[19]; }
    if (values.size() > 20) { clientcalc1desc = values[20]; }
    if (values.size() > 21) { CltParam1 = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { clientparam1desc = values[22]; }
    if (values.size() > 23) { CltParam2 = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { clientparam2desc = values[24]; }
    if (values.size() > 25) { CltParam3 = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { clientparam3desc = values[26]; }
    if (values.size() > 27) { CltParam4 = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { clientparam4desc = values[28]; }
    if (values.size() > 29) { CltParam5 = values[29]; }
    if (values.size() > 30) { clientparam5desc = values[30]; }
    if (values.size() > 31) { SHitCalc1 = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { serverhitcalc1desc = values[32]; }
    if (values.size() > 33) { sHitPar1 = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { serverhitparam1desc = values[34]; }
    if (values.size() > 35) { sHitPar2 = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { serverhitparam2desc = values[36]; }
    if (values.size() > 37) { sHitPar3 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { serverhitparam3desc = values[38]; }
    if (values.size() > 41) { cHitPar1 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { clienthitparam1desc = values[42]; }
    if (values.size() > 43) { cHitPar2 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { clienthitparam2desc = values[44]; }
    if (values.size() > 45) { cHitPar3 = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { clienthitparam3desc = values[46]; }
    if (values.size() > 47) { DmgCalc1 = values[47]; }
    if (values.size() > 48) { damagecalc1 = values[48]; }
    if (values.size() > 49) { dParam1 = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { damageparam1desc = values[50]; }
    if (values.size() > 51) { dParam2 = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { damageparam2desc = values[52]; }
    if (values.size() > 53) { Vel = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { MaxVel = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { VelLev = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { Accel = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { Range = values[57]; }
    if (values.size() > 59) { Light = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { Flicker = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { Red = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { Green = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { Blue = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { InitSteps = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { Activate = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { LoopAnim = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { CelFile = values[67]; }
    if (values.size() > 68) { animrate = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { AnimLen = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { AnimSpeed = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 71) { RandStart = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { SubLoop = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { SubStart = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { SubStop = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { CollideType = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 76) { CollideKill = (int32_t) std::strtol(values[76].c_str(), nullptr, 10); }
    if (values.size() > 77) { CollideFriend = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { LastCollide = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 79) { Collision = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 80) { ClientCol = (int32_t) std::strtol(values[80].c_str(), nullptr, 10); }
    if (values.size() > 82) { ClientSend = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }
    if (values.size() > 83) { NextHit = (int32_t) std::strtol(values[83].c_str(), nullptr, 10); }
    if (values.size() > 84) { NextDelay = (int32_t) std::strtol(values[84].c_str(), nullptr, 10); }
    if (values.size() > 86) { yoffset = (int32_t) std::strtol(values[86].c_str(), nullptr, 10); }
    if (values.size() > 87) { zoffset = (int32_t) std::strtol(values[87].c_str(), nullptr, 10); }
    if (values.size() > 88) { Size = (int32_t) std::strtol(values[88].c_str(), nullptr, 10); }
    if (values.size() > 89) { SrcTown = (int32_t) std::strtol(values[89].c_str(), nullptr, 10); }
    if (values.size() > 90) { CltSrcTown = (int32_t) std::strtol(values[90].c_str(), nullptr, 10); }
    if (values.size() > 91) { CanDestroy = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }
    if (values.size() > 92) { ToHit = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { AlwaysExplode = (int32_t) std::strtol(values[93].c_str(), nullptr, 10); }
    if (values.size() > 94) { Explosion = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 95) { Town = (int32_t) std::strtol(values[95].c_str(), nullptr, 10); }
    if (values.size() > 96) { NoUniqueMod = (int32_t) std::strtol(values[96].c_str(), nullptr, 10); }
    if (values.size() > 97) { NoMultiShot = (int32_t) std::strtol(values[97].c_str(), nullptr, 10); }
    if (values.size() > 98) { Holy = (int32_t) std::strtol(values[98].c_str(), nullptr, 10); }
    if (values.size() > 99) { CanSlow = (int32_t) std::strtol(values[99].c_str(), nullptr, 10); }
    if (values.size() > 100) { ReturnFire = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { GetHit = (int32_t) std::strtol(values[101].c_str(), nullptr, 10); }
    if (values.size() > 102) { SoftHit = (int32_t) std::strtol(values[102].c_str(), nullptr, 10); }
    if (values.size() > 103) { KnockBack = (int32_t) std::strtol(values[103].c_str(), nullptr, 10); }
    if (values.size() > 104) { Trans = (int32_t) std::strtol(values[104].c_str(), nullptr, 10); }
    if (values.size() > 105) { Pierce = (int32_t) std::strtol(values[105].c_str(), nullptr, 10); }
    if (values.size() > 106) { MissileSkill = (int32_t) std::strtol(values[106].c_str(), nullptr, 10); }
    if (values.size() > 107) { Skill = values[107]; }
    if (values.size() > 108) { ResultFlags = (int32_t) std::strtol(values[108].c_str(), nullptr, 10); }
    if (values.size() > 109) { HitFlags = (int32_t) std::strtol(values[109].c_str(), nullptr, 10); }
    if (values.size() > 110) { HitShift = (int32_t) std::strtol(values[110].c_str(), nullptr, 10); }
    if (values.size() > 111) { ApplyMastery = (int32_t) std::strtol(values[111].c_str(), nullptr, 10); }
    if (values.size() > 112) { SrcDamage = (int32_t) std::strtol(values[112].c_str(), nullptr, 10); }
    if (values.size() > 113) { Half2HSrc = (int32_t) std::strtol(values[113].c_str(), nullptr, 10); }
    if (values.size() > 115) { MinDamage = (int32_t) std::strtol(values[115].c_str(), nullptr, 10); }
    if (values.size() > 116) { MinLevDam1 = (int32_t) std::strtol(values[116].c_str(), nullptr, 10); }
    if (values.size() > 117) { MinLevDam2 = (int32_t) std::strtol(values[117].c_str(), nullptr, 10); }
    if (values.size() > 118) { MinLevDam3 = (int32_t) std::strtol(values[118].c_str(), nullptr, 10); }
    if (values.size() > 119) { MinLevDam4 = (int32_t) std::strtol(values[119].c_str(), nullptr, 10); }
    if (values.size() > 120) { MinLevDam5 = (int32_t) std::strtol(values[120].c_str(), nullptr, 10); }
    if (values.size() > 121) { MaxDamage = (int32_t) std::strtol(values[121].c_str(), nullptr, 10); }
    if (values.size() > 122) { MaxLevDam1 = (int32_t) std::strtol(values[122].c_str(), nullptr, 10); }
    if (values.size() > 123) { MaxLevDam2 = (int32_t) std::strtol(values[123].c_str(), nullptr, 10); }
    if (values.size() > 124) { MaxLevDam3 = (int32_t) std::strtol(values[124].c_str(), nullptr, 10); }
    if (values.size() > 125) { MaxLevDam4 = (int32_t) std::strtol(values[125].c_str(), nullptr, 10); }
    if (values.size() > 126) { MaxLevDam5 = (int32_t) std::strtol(values[126].c_str(), nullptr, 10); }
    if (values.size() > 128) { EType = values[128]; }
    if (values.size() > 129) { EMin = (int32_t) std::strtol(values[129].c_str(), nullptr, 10); }
    if (values.size() > 130) { MinELev1 = (int32_t) std::strtol(values[130].c_str(), nullptr, 10); }
    if (values.size() > 131) { MinELev2 = (int32_t) std::strtol(values[131].c_str(), nullptr, 10); }
    if (values.size() > 132) { MinELev3 = (int32_t) std::strtol(values[132].c_str(), nullptr, 10); }
    if (values.size() > 133) { MinELev4 = (int32_t) std::strtol(values[133].c_str(), nullptr, 10); }
    if (values.size() > 134) { MinELev5 = (int32_t) std::strtol(values[134].c_str(), nullptr, 10); }
    if (values.size() > 135) { EMax = (int32_t) std::strtol(values[135].c_str(), nullptr, 10); }
    if (values.size() > 136) { MaxELev1 = (int32_t) std::strtol(values[136].c_str(), nullptr, 10); }
    if (values.size() > 137) { MaxELev2 = (int32_t) std::strtol(values[137].c_str(), nullptr, 10); }
    if (values.size() > 138) { MaxELev3 = (int32_t) std::strtol(values[138].c_str(), nullptr, 10); }
    if (values.size() > 139) { MaxELev4 = (int32_t) std::strtol(values[139].c_str(), nullptr, 10); }
    if (values.size() > 140) { MaxELev5 = (int32_t) std::strtol(values[140].c_str(), nullptr, 10); }
    if (values.size() > 141) { EDmgSymPerCalc = values[141]; }
    if (values.size() > 142) { ELen = (int32_t) std::strtol(values[142].c_str(), nullptr, 10); }
    if (values.size() > 143) { ELevLen1 = (int32_t) std::strtol(values[143].c_str(), nullptr, 10); }
    if (values.size() > 144) { ELevLen2 = (int32_t) std::strtol(values[144].c_str(), nullptr, 10); }
    if (values.size() > 145) { ELevLen3 = (int32_t) std::strtol(values[145].c_str(), nullptr, 10); }
    if (values.size() > 146) { HitClass = (int32_t) std::strtol(values[146].c_str(), nullptr, 10); }
    if (values.size() > 147) { NumDirections = (int32_t) std::strtol(values[147].c_str(), nullptr, 10); }
    if (values.size() > 148) { LocalBlood = (int32_t) std::strtol(values[148].c_str(), nullptr, 10); }
    if (values.size() > 149) { DamageRate = (int32_t) std::strtol(values[149].c_str(), nullptr, 10); }
    if (values.size() > 150) { TravelSound = values[150]; }
    if (values.size() > 151) { HitSound = values[151]; }
    if (values.size() > 153) { ProgSound = values[153]; }
    if (values.size() > 154) { ProgOverlay = values[154]; }
    if (values.size() > 155) { ExplosionMissile = values[155]; }
    if (values.size() > 156) { SubMissile1 = values[156]; }
    if (values.size() > 157) { SubMissile2 = values[157]; }
    if (values.size() > 159) { HitSubMissile1 = values[159]; }
    if (values.size() > 163) { CltSubMissile1 = values[163]; }
    if (values.size() > 164) { CltSubMissile2 = values[164]; }
    if (values.size() > 165) { CltSubMissile3 = values[165]; }
    if (values.size() > 166) { CltHitSubMissile1 = values[166]; }
    if (values.size() > 167) { CltHitSubMissile2 = values[167]; }
    if (values.size() > 168) { CltHitSubMissile3 = values[168]; }
    if (values.size() > 169) { CltHitSubMissile4 = values[169]; }
    if (values.size() > 171) { eol = (int32_t) std::strtol(values[171].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_missiles> t_missiles::readfile(std::string filename) {
    std::vector<t_missiles> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_missiles v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monai::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { AI = values[0]; }
    if (values.size() > 1) { aip1 = values[1]; }
    if (values.size() > 2) { aip2 = values[2]; }
    if (values.size() > 3) { aip3 = values[3]; }
    if (values.size() > 4) { aip4 = values[4]; }
    if (values.size() > 5) { aip5 = values[5]; }
    if (values.size() > 6) { aip6 = values[6]; }
    if (values.size() > 7) { aip7 = values[7]; }
    if (values.size() > 8) { aip8 = values[8]; }
    if (values.size() > 9) { eol = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monai> t_monai::readfile(std::string filename) {
    std::vector<t_monai> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monai v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_moncalc::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { code = values[0]; }
    if (values.size() > 1) { description = values[1]; }

    return values.size();
  }

  std::vector<t_moncalc> t_moncalc::readfile(std::string filename) {
    std::vector<t_moncalc> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_moncalc v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monequip::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { monster = values[0]; }
    if (values.size() > 1) { oninit = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { level = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { item1 = values[3]; }
    if (values.size() > 4) { loc1 = values[4]; }
    if (values.size() > 5) { mod1 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { item2 = values[6]; }
    if (values.size() > 7) { loc2 = values[7]; }
    if (values.size() > 8) { mod2 = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { item3 = values[9]; }
    if (values.size() > 10) { loc3 = values[10]; }
    if (values.size() > 11) { mod3 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { eol = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monequip> t_monequip::readfile(std::string filename) {
    std::vector<t_monequip> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monequip v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monlvl::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Level = (int32_t) std::strtol(values[0].c_str(), nullptr, 10); }
    if (values.size() > 1) { AC = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { ACN = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { ACH = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { LAC = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { LACN = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { LACH = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { TH = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { THN = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { THH = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { LTH = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { LTHN = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { LTHH = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { HP = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { HPN = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { HPH = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { LHP = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { LHPN = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { LHPH = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { DM = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { DMN = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { DMH = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { LDM = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { LDMN = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { LDMH = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { XP = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { XPN = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { XPH = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { LXP = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { LXPN = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { LXPH = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monlvl> t_monlvl::readfile(std::string filename) {
    std::vector<t_monlvl> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monlvl v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monmode::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { token = values[1]; }
    if (values.size() > 2) { code = values[2]; }

    return values.size();
  }

  std::vector<t_monmode> t_monmode::readfile(std::string filename) {
    std::vector<t_monmode> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monmode v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monpet::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { monster = values[0]; }
    if (values.size() > 1) { index = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { hirelingAlternateVoice = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monpet> t_monpet::readfile(std::string filename) {
    std::vector<t_monpet> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monpet v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monplace::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { code = values[0]; }

    return values.size();
  }

  std::vector<t_monplace> t_monplace::readfile(std::string filename) {
    std::vector<t_monplace> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monplace v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monpreset::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Act = (int32_t) std::strtol(values[0].c_str(), nullptr, 10); }
    if (values.size() > 1) { Place = values[1]; }

    return values.size();
  }

  std::vector<t_monpreset> t_monpreset::readfile(std::string filename) {
    std::vector<t_monpreset> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monpreset v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monprop::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { prop1 = values[1]; }
    if (values.size() > 4) { min1 = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { max1 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 31) { prop1N = values[31]; }
    if (values.size() > 34) { min1N = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { max1N = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { prop2N = values[36]; }
    if (values.size() > 39) { min2N = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { max2N = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 61) { prop1H = values[61]; }
    if (values.size() > 64) { min1H = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { max1H = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { prop2H = values[66]; }
    if (values.size() > 69) { min2H = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { max2H = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 91) { eol = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monprop> t_monprop::readfile(std::string filename) {
    std::vector<t_monprop> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monprop v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monseq::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { sequence = values[0]; }
    if (values.size() > 1) { mode = values[1]; }
    if (values.size() > 2) { frame = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 4) { event = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { eol = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monseq> t_monseq::readfile(std::string filename) {
    std::vector<t_monseq> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monseq v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monsounds::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { Attack1 = values[1]; }
    if (values.size() > 2) { Weapon1 = values[2]; }
    if (values.size() > 3) { Att1Del = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Wea1Del = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Att1Prb = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Wea1Vol = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Attack2 = values[7]; }
    if (values.size() > 8) { Weapon2 = values[8]; }
    if (values.size() > 9) { Att2Del = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { Wea2Del = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Att2Prb = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { Wea2Vol = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { HitSound = values[13]; }
    if (values.size() > 14) { DeathSound = values[14]; }
    if (values.size() > 15) { HitDelay = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { DeaDelay = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { Skill1 = values[17]; }
    if (values.size() > 18) { Skill2 = values[18]; }
    if (values.size() > 19) { Skill3 = values[19]; }
    if (values.size() > 20) { Skill4 = values[20]; }
    if (values.size() > 21) { Footstep = values[21]; }
    if (values.size() > 22) { FootstepLayer = values[22]; }
    if (values.size() > 23) { FsCnt = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { FsOff = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { FsPrb = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { Neutral = values[26]; }
    if (values.size() > 27) { NeuTime = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { Init = values[28]; }
    if (values.size() > 29) { Taunt = values[29]; }
    if (values.size() > 30) { Flee = values[30]; }
    if (values.size() > 31) { CvtMo1 = values[31]; }
    if (values.size() > 32) { CvtSk1 = values[32]; }
    if (values.size() > 33) { CvtTgt1 = values[33]; }
    if (values.size() > 34) { CvtMo2 = values[34]; }
    if (values.size() > 35) { CvtSk2 = values[35]; }
    if (values.size() > 36) { CvtTgt2 = values[36]; }
    if (values.size() > 37) { CvtMo3 = values[37]; }
    if (values.size() > 38) { CvtSk3 = values[38]; }
    if (values.size() > 39) { CvtTgt3 = values[39]; }
    if (values.size() > 40) { EOL = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monsounds> t_monsounds::readfile(std::string filename) {
    std::vector<t_monsounds> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monsounds v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monstats::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { hcIdx = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { BaseId = values[2]; }
    if (values.size() > 3) { NextInClass = values[3]; }
    if (values.size() > 4) { TransLvl = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { NameStr = values[5]; }
    if (values.size() > 6) { MonStatsEx = values[6]; }
    if (values.size() > 7) { MonProp = values[7]; }
    if (values.size() > 8) { MonType = values[8]; }
    if (values.size() > 9) { AI = values[9]; }
    if (values.size() > 10) { DescStr = values[10]; }
    if (values.size() > 11) { Code = values[11]; }
    if (values.size() > 12) { enabled = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { rangedtype = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { placespawn = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { spawn = values[15]; }
    if (values.size() > 16) { spawnx = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { spawny = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { spawnmode = values[18]; }
    if (values.size() > 19) { minion1 = values[19]; }
    if (values.size() > 20) { minion2 = values[20]; }
    if (values.size() > 21) { SetBoss = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { BossXfer = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { PartyMin = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { PartyMax = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { MinGrp = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { MaxGrp = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { sparsePopulate = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { Velocity = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { Run = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { Rarity = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { Level = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { LevelN = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { LevelH = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { MonSound = values[34]; }
    if (values.size() > 35) { UMonSound = values[35]; }
    if (values.size() > 36) { threat = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { aidel = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { aidelN = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { aidelH = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 41) { aidistN = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { aidistH = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { aip1 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { aip1N = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { aip1H = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { aip2 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { aip2N = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { aip2H = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { aip3 = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { aip3N = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { aip3H = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { aip4 = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { aip4N = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { aip4H = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { aip5 = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { aip5N = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { aip5H = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { aip6 = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { aip6N = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { aip6H = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { aip7 = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { aip7N = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { aip7H = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { aip8 = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { aip8N = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { aip8H = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { MissA1 = values[67]; }
    if (values.size() > 68) { MissA2 = values[68]; }
    if (values.size() > 69) { MissS1 = values[69]; }
    if (values.size() > 70) { MissS2 = values[70]; }
    if (values.size() > 73) { MissC = values[73]; }
    if (values.size() > 74) { MissSQ = values[74]; }
    if (values.size() > 75) { Align = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 76) { isSpawn = (int32_t) std::strtol(values[76].c_str(), nullptr, 10); }
    if (values.size() > 77) { isMelee = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { npc = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 79) { interact = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 80) { inventory = (int32_t) std::strtol(values[80].c_str(), nullptr, 10); }
    if (values.size() > 81) { inTown = (int32_t) std::strtol(values[81].c_str(), nullptr, 10); }
    if (values.size() > 82) { lUndead = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }
    if (values.size() > 83) { hUndead = (int32_t) std::strtol(values[83].c_str(), nullptr, 10); }
    if (values.size() > 84) { demon = (int32_t) std::strtol(values[84].c_str(), nullptr, 10); }
    if (values.size() > 85) { flying = (int32_t) std::strtol(values[85].c_str(), nullptr, 10); }
    if (values.size() > 86) { opendoors = (int32_t) std::strtol(values[86].c_str(), nullptr, 10); }
    if (values.size() > 87) { boss = (int32_t) std::strtol(values[87].c_str(), nullptr, 10); }
    if (values.size() > 88) { primeevil = (int32_t) std::strtol(values[88].c_str(), nullptr, 10); }
    if (values.size() > 89) { killable = (int32_t) std::strtol(values[89].c_str(), nullptr, 10); }
    if (values.size() > 90) { switchai = (int32_t) std::strtol(values[90].c_str(), nullptr, 10); }
    if (values.size() > 91) { noAura = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }
    if (values.size() > 92) { nomultishot = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 94) { neverCount = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 95) { petIgnore = (int32_t) std::strtol(values[95].c_str(), nullptr, 10); }
    if (values.size() > 96) { deathDmg = (int32_t) std::strtol(values[96].c_str(), nullptr, 10); }
    if (values.size() > 97) { genericSpawn = (int32_t) std::strtol(values[97].c_str(), nullptr, 10); }
    if (values.size() > 98) { zoo = (int32_t) std::strtol(values[98].c_str(), nullptr, 10); }
    if (values.size() > 99) { CannotDesecrate = (int32_t) std::strtol(values[99].c_str(), nullptr, 10); }
    if (values.size() > 101) { rightArmItemType = values[101]; }
    if (values.size() > 102) { leftArmItemType = values[102]; }
    if (values.size() > 103) { canNotUseTwoHandedItems = (int32_t) std::strtol(values[103].c_str(), nullptr, 10); }
    if (values.size() > 104) { SendSkills = (int32_t) std::strtol(values[104].c_str(), nullptr, 10); }
    if (values.size() > 105) { Skill1 = values[105]; }
    if (values.size() > 106) { Sk1mode = values[106]; }
    if (values.size() > 107) { Sk1lvl = (int32_t) std::strtol(values[107].c_str(), nullptr, 10); }
    if (values.size() > 108) { Skill2 = values[108]; }
    if (values.size() > 109) { Sk2mode = values[109]; }
    if (values.size() > 110) { Sk2lvl = (int32_t) std::strtol(values[110].c_str(), nullptr, 10); }
    if (values.size() > 111) { Skill3 = values[111]; }
    if (values.size() > 112) { Sk3mode = values[112]; }
    if (values.size() > 113) { Sk3lvl = (int32_t) std::strtol(values[113].c_str(), nullptr, 10); }
    if (values.size() > 114) { Skill4 = values[114]; }
    if (values.size() > 115) { Sk4mode = values[115]; }
    if (values.size() > 116) { Sk4lvl = (int32_t) std::strtol(values[116].c_str(), nullptr, 10); }
    if (values.size() > 117) { Skill5 = values[117]; }
    if (values.size() > 118) { Sk5mode = values[118]; }
    if (values.size() > 119) { Sk5lvl = (int32_t) std::strtol(values[119].c_str(), nullptr, 10); }
    if (values.size() > 120) { Skill6 = values[120]; }
    if (values.size() > 121) { Sk6mode = values[121]; }
    if (values.size() > 122) { Sk6lvl = (int32_t) std::strtol(values[122].c_str(), nullptr, 10); }
    if (values.size() > 123) { Skill7 = values[123]; }
    if (values.size() > 124) { Sk7mode = values[124]; }
    if (values.size() > 125) { Sk7lvl = (int32_t) std::strtol(values[125].c_str(), nullptr, 10); }
    if (values.size() > 126) { Skill8 = values[126]; }
    if (values.size() > 127) { Sk8mode = values[127]; }
    if (values.size() > 128) { Sk8lvl = (int32_t) std::strtol(values[128].c_str(), nullptr, 10); }
    if (values.size() > 129) { Drain = (int32_t) std::strtol(values[129].c_str(), nullptr, 10); }
    if (values.size() > 130) { DrainN = (int32_t) std::strtol(values[130].c_str(), nullptr, 10); }
    if (values.size() > 131) { DrainH = (int32_t) std::strtol(values[131].c_str(), nullptr, 10); }
    if (values.size() > 132) { coldeffect = (int32_t) std::strtol(values[132].c_str(), nullptr, 10); }
    if (values.size() > 133) { coldeffectN = (int32_t) std::strtol(values[133].c_str(), nullptr, 10); }
    if (values.size() > 134) { coldeffectH = (int32_t) std::strtol(values[134].c_str(), nullptr, 10); }
    if (values.size() > 135) { ResDm = (int32_t) std::strtol(values[135].c_str(), nullptr, 10); }
    if (values.size() > 136) { ResMa = (int32_t) std::strtol(values[136].c_str(), nullptr, 10); }
    if (values.size() > 137) { ResFi = (int32_t) std::strtol(values[137].c_str(), nullptr, 10); }
    if (values.size() > 138) { ResLi = (int32_t) std::strtol(values[138].c_str(), nullptr, 10); }
    if (values.size() > 139) { ResCo = (int32_t) std::strtol(values[139].c_str(), nullptr, 10); }
    if (values.size() > 140) { ResPo = (int32_t) std::strtol(values[140].c_str(), nullptr, 10); }
    if (values.size() > 141) { ResDmN = (int32_t) std::strtol(values[141].c_str(), nullptr, 10); }
    if (values.size() > 142) { ResMaN = (int32_t) std::strtol(values[142].c_str(), nullptr, 10); }
    if (values.size() > 143) { ResFiN = (int32_t) std::strtol(values[143].c_str(), nullptr, 10); }
    if (values.size() > 144) { ResLiN = (int32_t) std::strtol(values[144].c_str(), nullptr, 10); }
    if (values.size() > 145) { ResCoN = (int32_t) std::strtol(values[145].c_str(), nullptr, 10); }
    if (values.size() > 146) { ResPoN = (int32_t) std::strtol(values[146].c_str(), nullptr, 10); }
    if (values.size() > 147) { ResDmH = (int32_t) std::strtol(values[147].c_str(), nullptr, 10); }
    if (values.size() > 148) { ResMaH = (int32_t) std::strtol(values[148].c_str(), nullptr, 10); }
    if (values.size() > 149) { ResFiH = (int32_t) std::strtol(values[149].c_str(), nullptr, 10); }
    if (values.size() > 150) { ResLiH = (int32_t) std::strtol(values[150].c_str(), nullptr, 10); }
    if (values.size() > 151) { ResCoH = (int32_t) std::strtol(values[151].c_str(), nullptr, 10); }
    if (values.size() > 152) { ResPoH = (int32_t) std::strtol(values[152].c_str(), nullptr, 10); }
    if (values.size() > 153) { DamageRegen = (int32_t) std::strtol(values[153].c_str(), nullptr, 10); }
    if (values.size() > 154) { SkillDamage = values[154]; }
    if (values.size() > 155) { noRatio = (int32_t) std::strtol(values[155].c_str(), nullptr, 10); }
    if (values.size() > 156) { ShieldBlockOverride = (int32_t) std::strtol(values[156].c_str(), nullptr, 10); }
    if (values.size() > 157) { ToBlock = (int32_t) std::strtol(values[157].c_str(), nullptr, 10); }
    if (values.size() > 158) { ToBlockN = (int32_t) std::strtol(values[158].c_str(), nullptr, 10); }
    if (values.size() > 159) { ToBlockH = (int32_t) std::strtol(values[159].c_str(), nullptr, 10); }
    if (values.size() > 160) { Crit = (int32_t) std::strtol(values[160].c_str(), nullptr, 10); }
    if (values.size() > 161) { minHP = (int32_t) std::strtol(values[161].c_str(), nullptr, 10); }
    if (values.size() > 162) { maxHP = (int32_t) std::strtol(values[162].c_str(), nullptr, 10); }
    if (values.size() > 163) { AC = (int32_t) std::strtol(values[163].c_str(), nullptr, 10); }
    if (values.size() > 164) { Exp = (int32_t) std::strtol(values[164].c_str(), nullptr, 10); }
    if (values.size() > 165) { A1MinD = (int32_t) std::strtol(values[165].c_str(), nullptr, 10); }
    if (values.size() > 166) { A1MaxD = (int32_t) std::strtol(values[166].c_str(), nullptr, 10); }
    if (values.size() > 167) { A1TH = (int32_t) std::strtol(values[167].c_str(), nullptr, 10); }
    if (values.size() > 168) { A2MinD = (int32_t) std::strtol(values[168].c_str(), nullptr, 10); }
    if (values.size() > 169) { A2MaxD = (int32_t) std::strtol(values[169].c_str(), nullptr, 10); }
    if (values.size() > 170) { A2TH = (int32_t) std::strtol(values[170].c_str(), nullptr, 10); }
    if (values.size() > 171) { S1MinD = (int32_t) std::strtol(values[171].c_str(), nullptr, 10); }
    if (values.size() > 172) { S1MaxD = (int32_t) std::strtol(values[172].c_str(), nullptr, 10); }
    if (values.size() > 173) { S1TH = (int32_t) std::strtol(values[173].c_str(), nullptr, 10); }
    if (values.size() > 174) { MinHPN = (int32_t) std::strtol(values[174].c_str(), nullptr, 10); }
    if (values.size() > 175) { MaxHPN = (int32_t) std::strtol(values[175].c_str(), nullptr, 10); }
    if (values.size() > 176) { ACN = (int32_t) std::strtol(values[176].c_str(), nullptr, 10); }
    if (values.size() > 177) { ExpN = (int32_t) std::strtol(values[177].c_str(), nullptr, 10); }
    if (values.size() > 178) { A1MinDN = (int32_t) std::strtol(values[178].c_str(), nullptr, 10); }
    if (values.size() > 179) { A1MaxDN = (int32_t) std::strtol(values[179].c_str(), nullptr, 10); }
    if (values.size() > 180) { A1THN = (int32_t) std::strtol(values[180].c_str(), nullptr, 10); }
    if (values.size() > 181) { A2MinDN = (int32_t) std::strtol(values[181].c_str(), nullptr, 10); }
    if (values.size() > 182) { A2MaxDN = (int32_t) std::strtol(values[182].c_str(), nullptr, 10); }
    if (values.size() > 183) { A2THN = (int32_t) std::strtol(values[183].c_str(), nullptr, 10); }
    if (values.size() > 184) { S1MinDN = (int32_t) std::strtol(values[184].c_str(), nullptr, 10); }
    if (values.size() > 185) { S1MaxDN = (int32_t) std::strtol(values[185].c_str(), nullptr, 10); }
    if (values.size() > 186) { S1THN = (int32_t) std::strtol(values[186].c_str(), nullptr, 10); }
    if (values.size() > 187) { MinHPH = (int32_t) std::strtol(values[187].c_str(), nullptr, 10); }
    if (values.size() > 188) { MaxHPH = (int32_t) std::strtol(values[188].c_str(), nullptr, 10); }
    if (values.size() > 189) { ACH = (int32_t) std::strtol(values[189].c_str(), nullptr, 10); }
    if (values.size() > 190) { ExpH = (int32_t) std::strtol(values[190].c_str(), nullptr, 10); }
    if (values.size() > 191) { A1MinDH = (int32_t) std::strtol(values[191].c_str(), nullptr, 10); }
    if (values.size() > 192) { A1MaxDH = (int32_t) std::strtol(values[192].c_str(), nullptr, 10); }
    if (values.size() > 193) { A1THH = (int32_t) std::strtol(values[193].c_str(), nullptr, 10); }
    if (values.size() > 194) { A2MinDH = (int32_t) std::strtol(values[194].c_str(), nullptr, 10); }
    if (values.size() > 195) { A2MaxDH = (int32_t) std::strtol(values[195].c_str(), nullptr, 10); }
    if (values.size() > 196) { A2THH = (int32_t) std::strtol(values[196].c_str(), nullptr, 10); }
    if (values.size() > 197) { S1MinDH = (int32_t) std::strtol(values[197].c_str(), nullptr, 10); }
    if (values.size() > 198) { S1MaxDH = (int32_t) std::strtol(values[198].c_str(), nullptr, 10); }
    if (values.size() > 199) { S1THH = (int32_t) std::strtol(values[199].c_str(), nullptr, 10); }
    if (values.size() > 200) { El1Mode = values[200]; }
    if (values.size() > 201) { El1Type = values[201]; }
    if (values.size() > 202) { El1Pct = (int32_t) std::strtol(values[202].c_str(), nullptr, 10); }
    if (values.size() > 203) { El1MinD = (int32_t) std::strtol(values[203].c_str(), nullptr, 10); }
    if (values.size() > 204) { El1MaxD = (int32_t) std::strtol(values[204].c_str(), nullptr, 10); }
    if (values.size() > 205) { El1Dur = (int32_t) std::strtol(values[205].c_str(), nullptr, 10); }
    if (values.size() > 206) { El1PctN = (int32_t) std::strtol(values[206].c_str(), nullptr, 10); }
    if (values.size() > 207) { El1MinDN = (int32_t) std::strtol(values[207].c_str(), nullptr, 10); }
    if (values.size() > 208) { El1MaxDN = (int32_t) std::strtol(values[208].c_str(), nullptr, 10); }
    if (values.size() > 209) { El1DurN = (int32_t) std::strtol(values[209].c_str(), nullptr, 10); }
    if (values.size() > 210) { El1PctH = (int32_t) std::strtol(values[210].c_str(), nullptr, 10); }
    if (values.size() > 211) { El1MinDH = (int32_t) std::strtol(values[211].c_str(), nullptr, 10); }
    if (values.size() > 212) { El1MaxDH = (int32_t) std::strtol(values[212].c_str(), nullptr, 10); }
    if (values.size() > 213) { El1DurH = (int32_t) std::strtol(values[213].c_str(), nullptr, 10); }
    if (values.size() > 214) { El2Mode = values[214]; }
    if (values.size() > 215) { El2Type = values[215]; }
    if (values.size() > 216) { El2Pct = (int32_t) std::strtol(values[216].c_str(), nullptr, 10); }
    if (values.size() > 217) { El2MinD = (int32_t) std::strtol(values[217].c_str(), nullptr, 10); }
    if (values.size() > 218) { El2MaxD = (int32_t) std::strtol(values[218].c_str(), nullptr, 10); }
    if (values.size() > 219) { El2Dur = (int32_t) std::strtol(values[219].c_str(), nullptr, 10); }
    if (values.size() > 220) { El2PctN = (int32_t) std::strtol(values[220].c_str(), nullptr, 10); }
    if (values.size() > 221) { El2MinDN = (int32_t) std::strtol(values[221].c_str(), nullptr, 10); }
    if (values.size() > 222) { El2MaxDN = (int32_t) std::strtol(values[222].c_str(), nullptr, 10); }
    if (values.size() > 223) { El2DurN = (int32_t) std::strtol(values[223].c_str(), nullptr, 10); }
    if (values.size() > 224) { El2PctH = (int32_t) std::strtol(values[224].c_str(), nullptr, 10); }
    if (values.size() > 225) { El2MinDH = (int32_t) std::strtol(values[225].c_str(), nullptr, 10); }
    if (values.size() > 226) { El2MaxDH = (int32_t) std::strtol(values[226].c_str(), nullptr, 10); }
    if (values.size() > 227) { El2DurH = (int32_t) std::strtol(values[227].c_str(), nullptr, 10); }
    if (values.size() > 242) { TreasureClass = values[242]; }
    if (values.size() > 243) { TreasureClassChamp = values[243]; }
    if (values.size() > 244) { TreasureClassUnique = values[244]; }
    if (values.size() > 245) { TreasureClassQuest = values[245]; }
    if (values.size() > 246) { TreasureClassDesecrated = values[246]; }
    if (values.size() > 247) { TreasureClassDesecratedChamp = values[247]; }
    if (values.size() > 248) { TreasureClassDesecratedUnique = values[248]; }
    if (values.size() > 250) { TreasureClassN = values[250]; }
    if (values.size() > 251) { TreasureClassChampN = values[251]; }
    if (values.size() > 252) { TreasureClassUniqueN = values[252]; }
    if (values.size() > 253) { TreasureClassQuestN = values[253]; }
    if (values.size() > 254) { TreasureClassDesecratedN = values[254]; }
    if (values.size() > 255) { TreasureClassDesecratedChampN = values[255]; }
    if (values.size() > 256) { TreasureClassDesecratedUniqueN = values[256]; }
    if (values.size() > 258) { TreasureClassH = values[258]; }
    if (values.size() > 259) { TreasureClassChampH = values[259]; }
    if (values.size() > 260) { TreasureClassUniqueH = values[260]; }
    if (values.size() > 261) { TreasureClassQuestH = values[261]; }
    if (values.size() > 262) { TreasureClassDesecratedH = values[262]; }
    if (values.size() > 263) { TreasureClassDesecratedChampH = values[263]; }
    if (values.size() > 264) { TreasureClassDesecratedUniqueH = values[264]; }
    if (values.size() > 266) { TCQuestId = (int32_t) std::strtol(values[266].c_str(), nullptr, 10); }
    if (values.size() > 267) { TCQuestCP = (int32_t) std::strtol(values[267].c_str(), nullptr, 10); }
    if (values.size() > 268) { SplEndDeath = (int32_t) std::strtol(values[268].c_str(), nullptr, 10); }
    if (values.size() > 269) { SplGetModeChart = (int32_t) std::strtol(values[269].c_str(), nullptr, 10); }
    if (values.size() > 270) { SplEndGeneric = (int32_t) std::strtol(values[270].c_str(), nullptr, 10); }
    if (values.size() > 271) { SplClientEnd = (int32_t) std::strtol(values[271].c_str(), nullptr, 10); }
    if (values.size() > 272) { eol = (int32_t) std::strtol(values[272].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monstats> t_monstats::readfile(std::string filename) {
    std::vector<t_monstats> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monstats v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monstats2::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { hcIdx = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Height = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { OverlayHeight = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { pixHeight = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { SizeX = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { SizeY = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { spawnCol = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { MeleeRng = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { BaseW = values[9]; }
    if (values.size() > 10) { HitClass = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { HDv = values[11]; }
    if (values.size() > 12) { TRv = values[12]; }
    if (values.size() > 13) { LGv = values[13]; }
    if (values.size() > 14) { Rav = values[14]; }
    if (values.size() > 15) { Lav = values[15]; }
    if (values.size() > 16) { RHv = values[16]; }
    if (values.size() > 17) { LHv = values[17]; }
    if (values.size() > 18) { SHv = values[18]; }
    if (values.size() > 19) { S1v = values[19]; }
    if (values.size() > 20) { S2v = values[20]; }
    if (values.size() > 21) { S3v = values[21]; }
    if (values.size() > 22) { S4v = values[22]; }
    if (values.size() > 23) { S5v = values[23]; }
    if (values.size() > 24) { S6v = values[24]; }
    if (values.size() > 25) { S7v = values[25]; }
    if (values.size() > 26) { S8v = values[26]; }
    if (values.size() > 27) { HD = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { TR = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { LG = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { RA = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { LA = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { RH = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { LH = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { SH = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { S1 = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { S2 = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { S3 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { S4 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { S5 = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { S6 = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { S7 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { S8 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { TotalPieces = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { mDT = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { mNU = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { mWL = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { mGH = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { mA1 = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { mA2 = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { mBL = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { mSC = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { mS1 = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { mS2 = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { mS3 = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { mS4 = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { mDD = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { mKB = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { mSQ = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { mRN = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { dDT = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { dNU = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { dWL = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { dGH = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { dA1 = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { dA2 = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { dBL = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { dSC = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { dS1 = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { dS2 = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { dS3 = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 71) { dS4 = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { dDD = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { dKB = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { dSQ = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { dRN = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 77) { A2mv = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 79) { S1mv = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 80) { S2mv = (int32_t) std::strtol(values[80].c_str(), nullptr, 10); }
    if (values.size() > 83) { noGfxHitTest = (int32_t) std::strtol(values[83].c_str(), nullptr, 10); }
    if (values.size() > 84) { htTop = (int32_t) std::strtol(values[84].c_str(), nullptr, 10); }
    if (values.size() > 85) { htLeft = (int32_t) std::strtol(values[85].c_str(), nullptr, 10); }
    if (values.size() > 86) { htWidth = (int32_t) std::strtol(values[86].c_str(), nullptr, 10); }
    if (values.size() > 87) { htHeight = (int32_t) std::strtol(values[87].c_str(), nullptr, 10); }
    if (values.size() > 88) { restore = (int32_t) std::strtol(values[88].c_str(), nullptr, 10); }
    if (values.size() > 89) { automapCel = (int32_t) std::strtol(values[89].c_str(), nullptr, 10); }
    if (values.size() > 90) { noMap = (int32_t) std::strtol(values[90].c_str(), nullptr, 10); }
    if (values.size() > 91) { noOvly = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }
    if (values.size() > 92) { isSel = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { alSel = (int32_t) std::strtol(values[93].c_str(), nullptr, 10); }
    if (values.size() > 94) { noSel = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 95) { shiftSel = (int32_t) std::strtol(values[95].c_str(), nullptr, 10); }
    if (values.size() > 96) { corpseSel = (int32_t) std::strtol(values[96].c_str(), nullptr, 10); }
    if (values.size() > 97) { isAtt = (int32_t) std::strtol(values[97].c_str(), nullptr, 10); }
    if (values.size() > 98) { revive = (int32_t) std::strtol(values[98].c_str(), nullptr, 10); }
    if (values.size() > 99) { limitCorpses = (int32_t) std::strtol(values[99].c_str(), nullptr, 10); }
    if (values.size() > 100) { critter = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { small = (int32_t) std::strtol(values[101].c_str(), nullptr, 10); }
    if (values.size() > 102) { large = (int32_t) std::strtol(values[102].c_str(), nullptr, 10); }
    if (values.size() > 103) { soft = (int32_t) std::strtol(values[103].c_str(), nullptr, 10); }
    if (values.size() > 104) { inert = (int32_t) std::strtol(values[104].c_str(), nullptr, 10); }
    if (values.size() > 105) { objCol = (int32_t) std::strtol(values[105].c_str(), nullptr, 10); }
    if (values.size() > 106) { deadCol = (int32_t) std::strtol(values[106].c_str(), nullptr, 10); }
    if (values.size() > 107) { unflatDead = (int32_t) std::strtol(values[107].c_str(), nullptr, 10); }
    if (values.size() > 108) { Shadow = (int32_t) std::strtol(values[108].c_str(), nullptr, 10); }
    if (values.size() > 109) { noUniqueShift = (int32_t) std::strtol(values[109].c_str(), nullptr, 10); }
    if (values.size() > 110) { compositeDeath = (int32_t) std::strtol(values[110].c_str(), nullptr, 10); }
    if (values.size() > 111) { localBlood = (int32_t) std::strtol(values[111].c_str(), nullptr, 10); }
    if (values.size() > 112) { Bleed = (int32_t) std::strtol(values[112].c_str(), nullptr, 10); }
    if (values.size() > 113) { Light = (int32_t) std::strtol(values[113].c_str(), nullptr, 10); }
    if (values.size() > 114) { lightr = (int32_t) std::strtol(values[114].c_str(), nullptr, 10); }
    if (values.size() > 115) { lightg = (int32_t) std::strtol(values[115].c_str(), nullptr, 10); }
    if (values.size() > 116) { lightb = (int32_t) std::strtol(values[116].c_str(), nullptr, 10); }
    if (values.size() > 117) { Utrans = (int32_t) std::strtol(values[117].c_str(), nullptr, 10); }
    if (values.size() > 118) { UtransN = (int32_t) std::strtol(values[118].c_str(), nullptr, 10); }
    if (values.size() > 119) { UtransH = (int32_t) std::strtol(values[119].c_str(), nullptr, 10); }
    if (values.size() > 120) { InfernoLen = (int32_t) std::strtol(values[120].c_str(), nullptr, 10); }
    if (values.size() > 121) { InfernoAnim = (int32_t) std::strtol(values[121].c_str(), nullptr, 10); }
    if (values.size() > 122) { InfernoRollback = (int32_t) std::strtol(values[122].c_str(), nullptr, 10); }
    if (values.size() > 123) { ResurrectMode = values[123]; }
    if (values.size() > 124) { ResurrectSkill = values[124]; }
    if (values.size() > 125) { SpawnUniqueMod = values[125]; }
    if (values.size() > 126) { eol = (int32_t) std::strtol(values[126].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monstats2> t_monstats2::readfile(std::string filename) {
    std::vector<t_monstats2> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monstats2 v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_montype::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { type = values[0]; }
    if (values.size() > 1) { equiv1 = values[1]; }
    if (values.size() > 2) { equiv2 = values[2]; }
    if (values.size() > 4) { strplur = values[4]; }
    if (values.size() > 6) { eol = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_montype> t_montype::readfile(std::string filename) {
    std::vector<t_montype> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_montype v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_monumod::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { uniquemod = values[0]; }
    if (values.size() > 1) { id = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { enabled = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { version = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { xfer = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { champion = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { fPick = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { exclude1 = values[7]; }
    if (values.size() > 9) { cpick = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { cpickN = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { cpickH = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { upick = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { upickN = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { upickH = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { constants = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { constantdesc = values[16]; }
    if (values.size() > 17) { eol = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_monumod> t_monumod::readfile(std::string filename) {
    std::vector<t_monumod> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_monumod v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_npc::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { npc = values[0]; }
    if (values.size() > 1) { buymult = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { sellmult = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { repmult = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { questflagA = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { questbuymultA = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { questsellmultA = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { questrepmultA = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 16) { maxbuy = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { maxbuyN = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { maxbuyH = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_npc> t_npc::readfile(std::string filename) {
    std::vector<t_npc> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_npc v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_objects::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Class = values[0]; }
    if (values.size() > 1) { Name = values[1]; }
    if (values.size() > 2) { Description = values[2]; }
    if (values.size() > 3) { ID = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Token = values[4]; }
    if (values.size() > 5) { Selectable0 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Selectable1 = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Selectable2 = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { Selectable3 = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { Selectable4 = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { Selectable5 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Selectable6 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { Selectable7 = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { SizeX = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { SizeY = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { FrameCnt0 = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { FrameCnt1 = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { FrameCnt2 = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { FrameCnt3 = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { FrameCnt4 = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { FrameCnt5 = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { FrameCnt6 = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { FrameCnt7 = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { FrameDelta0 = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { FrameDelta1 = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { FrameDelta2 = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { FrameDelta3 = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { FrameDelta4 = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { FrameDelta5 = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { FrameDelta6 = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { FrameDelta7 = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { CycleAnim0 = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { CycleAnim1 = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { CycleAnim2 = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { CycleAnim3 = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { CycleAnim4 = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { CycleAnim5 = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { CycleAnim6 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { CycleAnim7 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { Lit0 = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { Lit1 = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { Lit2 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { Lit3 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { Lit4 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { Lit5 = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { Lit6 = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { Lit7 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { BlocksLight0 = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { BlocksLight1 = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { BlocksLight2 = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { BlocksLight3 = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { BlocksLight4 = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { BlocksLight5 = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { BlocksLight6 = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { BlocksLight7 = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { HasCollision0 = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { HasCollision1 = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { HasCollision2 = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { HasCollision3 = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { HasCollision4 = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { HasCollision5 = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { HasCollision6 = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { HasCollision7 = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { IsAttackable0 = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { Start0 = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { Start1 = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { Start2 = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { Start3 = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { Start4 = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { Start5 = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { Start6 = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 71) { Start7 = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { EnvEffect = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { IsDoor = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { BlocksVis = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { Orientation = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 76) { OrderFlag0 = (int32_t) std::strtol(values[76].c_str(), nullptr, 10); }
    if (values.size() > 77) { OrderFlag1 = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { OrderFlag2 = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 79) { OrderFlag3 = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 80) { OrderFlag4 = (int32_t) std::strtol(values[80].c_str(), nullptr, 10); }
    if (values.size() > 81) { OrderFlag5 = (int32_t) std::strtol(values[81].c_str(), nullptr, 10); }
    if (values.size() > 82) { OrderFlag6 = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }
    if (values.size() > 83) { OrderFlag7 = (int32_t) std::strtol(values[83].c_str(), nullptr, 10); }
    if (values.size() > 84) { PreOperate = (int32_t) std::strtol(values[84].c_str(), nullptr, 10); }
    if (values.size() > 85) { Mode0 = (int32_t) std::strtol(values[85].c_str(), nullptr, 10); }
    if (values.size() > 86) { Mode1 = (int32_t) std::strtol(values[86].c_str(), nullptr, 10); }
    if (values.size() > 87) { Mode2 = (int32_t) std::strtol(values[87].c_str(), nullptr, 10); }
    if (values.size() > 88) { Mode3 = (int32_t) std::strtol(values[88].c_str(), nullptr, 10); }
    if (values.size() > 89) { Mode4 = (int32_t) std::strtol(values[89].c_str(), nullptr, 10); }
    if (values.size() > 90) { Mode5 = (int32_t) std::strtol(values[90].c_str(), nullptr, 10); }
    if (values.size() > 91) { Mode6 = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }
    if (values.size() > 92) { Mode7 = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { Yoffset = (int32_t) std::strtol(values[93].c_str(), nullptr, 10); }
    if (values.size() > 94) { Xoffset = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 95) { Draw = (int32_t) std::strtol(values[95].c_str(), nullptr, 10); }
    if (values.size() > 96) { Red = (int32_t) std::strtol(values[96].c_str(), nullptr, 10); }
    if (values.size() > 97) { Green = (int32_t) std::strtol(values[97].c_str(), nullptr, 10); }
    if (values.size() > 98) { Blue = (int32_t) std::strtol(values[98].c_str(), nullptr, 10); }
    if (values.size() > 99) { HD = (int32_t) std::strtol(values[99].c_str(), nullptr, 10); }
    if (values.size() > 100) { TR = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { LG = (int32_t) std::strtol(values[101].c_str(), nullptr, 10); }
    if (values.size() > 102) { RA = (int32_t) std::strtol(values[102].c_str(), nullptr, 10); }
    if (values.size() > 103) { LA = (int32_t) std::strtol(values[103].c_str(), nullptr, 10); }
    if (values.size() > 104) { RH = (int32_t) std::strtol(values[104].c_str(), nullptr, 10); }
    if (values.size() > 105) { LH = (int32_t) std::strtol(values[105].c_str(), nullptr, 10); }
    if (values.size() > 106) { SH = (int32_t) std::strtol(values[106].c_str(), nullptr, 10); }
    if (values.size() > 107) { S1 = (int32_t) std::strtol(values[107].c_str(), nullptr, 10); }
    if (values.size() > 108) { S2 = (int32_t) std::strtol(values[108].c_str(), nullptr, 10); }
    if (values.size() > 109) { S3 = (int32_t) std::strtol(values[109].c_str(), nullptr, 10); }
    if (values.size() > 110) { S4 = (int32_t) std::strtol(values[110].c_str(), nullptr, 10); }
    if (values.size() > 111) { S5 = (int32_t) std::strtol(values[111].c_str(), nullptr, 10); }
    if (values.size() > 112) { S6 = (int32_t) std::strtol(values[112].c_str(), nullptr, 10); }
    if (values.size() > 113) { S7 = (int32_t) std::strtol(values[113].c_str(), nullptr, 10); }
    if (values.size() > 114) { S8 = (int32_t) std::strtol(values[114].c_str(), nullptr, 10); }
    if (values.size() > 115) { TotalPieces = (int32_t) std::strtol(values[115].c_str(), nullptr, 10); }
    if (values.size() > 116) { SubClass = (int32_t) std::strtol(values[116].c_str(), nullptr, 10); }
    if (values.size() > 117) { Xspace = (int32_t) std::strtol(values[117].c_str(), nullptr, 10); }
    if (values.size() > 118) { Yspace = (int32_t) std::strtol(values[118].c_str(), nullptr, 10); }
    if (values.size() > 119) { NameOffset = (int32_t) std::strtol(values[119].c_str(), nullptr, 10); }
    if (values.size() > 120) { MonsterOK = (int32_t) std::strtol(values[120].c_str(), nullptr, 10); }
    if (values.size() > 121) { ShrineFunction = (int32_t) std::strtol(values[121].c_str(), nullptr, 10); }
    if (values.size() > 122) { Restore = (int32_t) std::strtol(values[122].c_str(), nullptr, 10); }
    if (values.size() > 123) { Parm0 = (int32_t) std::strtol(values[123].c_str(), nullptr, 10); }
    if (values.size() > 124) { Parm1 = (int32_t) std::strtol(values[124].c_str(), nullptr, 10); }
    if (values.size() > 125) { Parm2 = (int32_t) std::strtol(values[125].c_str(), nullptr, 10); }
    if (values.size() > 126) { Parm3 = (int32_t) std::strtol(values[126].c_str(), nullptr, 10); }
    if (values.size() > 127) { Parm4 = (int32_t) std::strtol(values[127].c_str(), nullptr, 10); }
    if (values.size() > 128) { Lockable = (int32_t) std::strtol(values[128].c_str(), nullptr, 10); }
    if (values.size() > 129) { Gore = (int32_t) std::strtol(values[129].c_str(), nullptr, 10); }
    if (values.size() > 130) { Sync = (int32_t) std::strtol(values[130].c_str(), nullptr, 10); }
    if (values.size() > 131) { Damage = (int32_t) std::strtol(values[131].c_str(), nullptr, 10); }
    if (values.size() > 132) { Overlay = (int32_t) std::strtol(values[132].c_str(), nullptr, 10); }
    if (values.size() > 133) { CollisionSubst = (int32_t) std::strtol(values[133].c_str(), nullptr, 10); }
    if (values.size() > 134) { Left = (int32_t) std::strtol(values[134].c_str(), nullptr, 10); }
    if (values.size() > 135) { Top = (int32_t) std::strtol(values[135].c_str(), nullptr, 10); }
    if (values.size() > 136) { Width = (int32_t) std::strtol(values[136].c_str(), nullptr, 10); }
    if (values.size() > 137) { Height = (int32_t) std::strtol(values[137].c_str(), nullptr, 10); }
    if (values.size() > 138) { OperateFn = (int32_t) std::strtol(values[138].c_str(), nullptr, 10); }
    if (values.size() > 139) { PopulateFn = (int32_t) std::strtol(values[139].c_str(), nullptr, 10); }
    if (values.size() > 140) { InitFn = (int32_t) std::strtol(values[140].c_str(), nullptr, 10); }
    if (values.size() > 141) { ClientFn = (int32_t) std::strtol(values[141].c_str(), nullptr, 10); }
    if (values.size() > 142) { RestoreVirgins = (int32_t) std::strtol(values[142].c_str(), nullptr, 10); }
    if (values.size() > 143) { BlockMissile = (int32_t) std::strtol(values[143].c_str(), nullptr, 10); }
    if (values.size() > 144) { DrawUnder = (int32_t) std::strtol(values[144].c_str(), nullptr, 10); }
    if (values.size() > 145) { OpenWarp = (int32_t) std::strtol(values[145].c_str(), nullptr, 10); }
    if (values.size() > 146) { AutoMap = (int32_t) std::strtol(values[146].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_objects> t_objects::readfile(std::string filename) {
    std::vector<t_objects> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_objects v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_objgroup::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { GroupName = values[0]; }
    if (values.size() > 1) { ID = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { ID0 = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { DENSITY0 = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { PROB0 = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { ID1 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { DENSITY1 = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { PROB1 = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { ID2 = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { DENSITY2 = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { PROB2 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { ID3 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { DENSITY3 = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { PROB3 = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { ID4 = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { DENSITY4 = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { PROB4 = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { ID5 = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { DENSITY5 = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { PROB5 = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { ID6 = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { DENSITY6 = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { PROB6 = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { ID7 = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { DENSITY7 = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { PROB7 = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_objgroup> t_objgroup::readfile(std::string filename) {
    std::vector<t_objgroup> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_objgroup v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_objmode::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Token = values[1]; }

    return values.size();
  }

  std::vector<t_objmode> t_objmode::readfile(std::string filename) {
    std::vector<t_objmode> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_objmode v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_objpreset::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Index = (int32_t) std::strtol(values[0].c_str(), nullptr, 10); }
    if (values.size() > 1) { Act = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { ObjectClass = values[2]; }
    if (values.size() > 3) { Notes = values[3]; }
    if (values.size() > 4) { eol = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_objpreset> t_objpreset::readfile(std::string filename) {
    std::vector<t_objpreset> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_objpreset v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_objtype::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Token = values[1]; }

    return values.size();
  }

  std::vector<t_objtype> t_objtype::readfile(std::string filename) {
    std::vector<t_objtype> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_objtype v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_overlay::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { overlay = values[0]; }
    if (values.size() > 1) { ID = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Filename = values[2]; }
    if (values.size() > 3) { version = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Frames = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Character = values[5]; }
    if (values.size() > 6) { PreDraw = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { _1ofN = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { Xoffset = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { Yoffset = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { Height1 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Height2 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { Height3 = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Height4 = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { AnimRate = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { LoopWaitTime = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { Trans = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { InitRadius = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { Radius = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { Red = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { Green = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { Blue = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { NumDirections = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { LocalBlood = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_overlay> t_overlay::readfile(std::string filename) {
    std::vector<t_overlay> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_overlay v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_pettype::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { pettype = values[0]; }
    if (values.size() > 3) { basemax = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { warp = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { range = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { partysend = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { unsummon = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { automap = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { name = values[9]; }
    if (values.size() > 10) { drawhp = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { icontype = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { baseicon = values[12]; }
    if (values.size() > 13) { mclass1 = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { micon1 = values[14]; }
    if (values.size() > 15) { mclass2 = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { micon2 = values[16]; }
    if (values.size() > 17) { mclass3 = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { micon3 = values[18]; }
    if (values.size() > 19) { mclass4 = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { micon4 = values[20]; }

    return values.size();
  }

  std::vector<t_pettype> t_pettype::readfile(std::string filename) {
    std::vector<t_pettype> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_pettype v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_playerclass::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { PlayerClass = values[0]; }
    if (values.size() > 1) { Code = values[1]; }

    return values.size();
  }

  std::vector<t_playerclass> t_playerclass::readfile(std::string filename) {
    std::vector<t_playerclass> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_playerclass v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_plrmode::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Token = values[1]; }
    if (values.size() > 2) { Code = values[2]; }

    return values.size();
  }

  std::vector<t_plrmode> t_plrmode::readfile(std::string filename) {
    std::vector<t_plrmode> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_plrmode v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_plrtype::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Token = values[1]; }

    return values.size();
  }

  std::vector<t_plrtype> t_plrtype::readfile(std::string filename) {
    std::vector<t_plrtype> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_plrtype v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_properties::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { code = values[0]; }
    if (values.size() > 1) { Id = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Enabled = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { func1 = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { stat1 = values[4]; }
    if (values.size() > 5) { set1 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { val1 = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { func2 = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { stat2 = values[8]; }
    if (values.size() > 11) { func3 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { stat3 = values[12]; }
    if (values.size() > 15) { func4 = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { stat4 = values[16]; }
    if (values.size() > 19) { func5 = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { stat5 = values[20]; }
    if (values.size() > 23) { func6 = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { stat6 = values[24]; }
    if (values.size() > 27) { func7 = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { stat7 = values[28]; }
    if (values.size() > 31) { Tooltip = values[31]; }
    if (values.size() > 32) { Parameter = values[32]; }
    if (values.size() > 33) { Min = values[33]; }
    if (values.size() > 34) { Max = values[34]; }
    if (values.size() > 35) { Notes = values[35]; }
    if (values.size() > 36) { eol = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_properties> t_properties::readfile(std::string filename) {
    std::vector<t_properties> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_properties v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_propertygroups::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { code = values[0]; }
    if (values.size() > 1) { Id = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { PickMode = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Prop1 = values[3]; }
    if (values.size() > 4) { ParMin1 = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { ParMax1 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { ModMin1 = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { ModMax1 = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { Chance1 = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { Prop2 = values[9]; }
    if (values.size() > 10) { ParMin2 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { ParMax2 = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { ModMin2 = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { ModMax2 = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { Chance2 = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { Prop3 = values[15]; }
    if (values.size() > 18) { ModMin3 = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { ModMax3 = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { Chance3 = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { Prop4 = values[21]; }
    if (values.size() > 24) { ModMin4 = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { ModMax4 = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { Chance4 = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { Prop5 = values[27]; }
    if (values.size() > 30) { ModMin5 = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { ModMax5 = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { Chance5 = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { Prop6 = values[33]; }
    if (values.size() > 36) { ModMin6 = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { ModMax6 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { Chance6 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 56) { eol = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_propertygroups> t_propertygroups::readfile(std::string filename) {
    std::vector<t_propertygroups> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_propertygroups v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_qualityitems::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { mod1code = values[0]; }
    if (values.size() > 1) { mod1param = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { mod1min = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { mod1max = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { mod2code = values[4]; }
    if (values.size() > 5) { mod2param = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { mod2min = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { mod2max = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { armor = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { weapon = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { shield = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { scepter = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { wand = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { staff = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { bow = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { boots = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { gloves = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { belt = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_qualityitems> t_qualityitems::readfile(std::string filename) {
    std::vector<t_qualityitems> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_qualityitems v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_rareprefix::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { version = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { itype1 = values[2]; }
    if (values.size() > 3) { itype2 = values[3]; }
    if (values.size() > 4) { itype3 = values[4]; }
    if (values.size() > 5) { itype4 = values[5]; }
    if (values.size() > 6) { itype5 = values[6]; }

    return values.size();
  }

  std::vector<t_rareprefix> t_rareprefix::readfile(std::string filename) {
    std::vector<t_rareprefix> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_rareprefix v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_raresuffix::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { version = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { itype1 = values[2]; }
    if (values.size() > 3) { itype2 = values[3]; }
    if (values.size() > 4) { itype3 = values[4]; }
    if (values.size() > 5) { itype4 = values[5]; }
    if (values.size() > 6) { itype5 = values[6]; }
    if (values.size() > 7) { itype6 = values[7]; }

    return values.size();
  }

  std::vector<t_raresuffix> t_raresuffix::readfile(std::string filename) {
    std::vector<t_raresuffix> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_raresuffix v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_runes::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { RuneName = values[1]; }
    if (values.size() > 2) { complete = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { disallowCraftingInLadder = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 5) { firstLadderSeason = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { lastLadderSeason = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { PatchRelease = values[7]; }
    if (values.size() > 8) { itype1 = values[8]; }
    if (values.size() > 9) { itype2 = values[9]; }
    if (values.size() > 10) { itype3 = values[10]; }
    if (values.size() > 17) { RunesUsed = values[17]; }
    if (values.size() > 18) { Rune1 = values[18]; }
    if (values.size() > 19) { Rune2 = values[19]; }
    if (values.size() > 20) { Rune3 = values[20]; }
    if (values.size() > 21) { Rune4 = values[21]; }
    if (values.size() > 22) { Rune5 = values[22]; }
    if (values.size() > 23) { Rune6 = values[23]; }
    if (values.size() > 24) { T1Code1 = values[24]; }
    if (values.size() > 25) { T1Param1 = values[25]; }
    if (values.size() > 26) { T1Min1 = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { T1Max1 = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { T1Code2 = values[28]; }
    if (values.size() > 29) { T1Param2 = values[29]; }
    if (values.size() > 30) { T1Min2 = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { T1Max2 = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { T1Code3 = values[32]; }
    if (values.size() > 33) { T1Param3 = values[33]; }
    if (values.size() > 34) { T1Min3 = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { T1Max3 = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { T1Code4 = values[36]; }
    if (values.size() > 37) { T1Param4 = values[37]; }
    if (values.size() > 38) { T1Min4 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { T1Max4 = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { T1Code5 = values[40]; }
    if (values.size() > 41) { T1Param5 = values[41]; }
    if (values.size() > 42) { T1Min5 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { T1Max5 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { T1Code6 = values[44]; }
    if (values.size() > 45) { T1Param6 = values[45]; }
    if (values.size() > 46) { T1Min6 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { T1Max6 = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { T1Code7 = values[48]; }
    if (values.size() > 49) { T1Param7 = values[49]; }
    if (values.size() > 50) { T1Min7 = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { T1Max7 = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { eol = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_runes> t_runes::readfile(std::string filename) {
    std::vector<t_runes> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_runes v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_runeworduicategories::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Category = values[1]; }

    return values.size();
  }

  std::vector<t_runeworduicategories> t_runeworduicategories::readfile(std::string filename) {
    std::vector<t_runeworduicategories> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_runeworduicategories v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_setitems::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { index = values[0]; }
    if (values.size() > 1) { ID = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { set = values[2]; }
    if (values.size() > 3) { disabled = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { spawnable = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 8) { item = values[8]; }
    if (values.size() > 9) { ItemName = values[9]; }
    if (values.size() > 10) { rarity = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { lvl = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { lvlreq = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { chrtransform = values[13]; }
    if (values.size() > 14) { invtransform = values[14]; }
    if (values.size() > 20) { costmult = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { costadd = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { addfunc = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { prop1 = values[23]; }
    if (values.size() > 24) { par1 = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { min1 = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { max1 = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { prop2 = values[27]; }
    if (values.size() > 28) { par2 = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { min2 = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { max2 = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { prop3 = values[31]; }
    if (values.size() > 32) { par3 = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { min3 = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { max3 = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { prop4 = values[35]; }
    if (values.size() > 36) { par4 = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { min4 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { max4 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { prop5 = values[39]; }
    if (values.size() > 40) { par5 = values[40]; }
    if (values.size() > 41) { min5 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { max5 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { prop6 = values[43]; }
    if (values.size() > 44) { par6 = values[44]; }
    if (values.size() > 45) { min6 = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { max6 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { prop7 = values[47]; }
    if (values.size() > 48) { par7 = values[48]; }
    if (values.size() > 49) { min7 = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { max7 = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 59) { aprop1a = values[59]; }
    if (values.size() > 60) { apar1a = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { amin1a = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { amax1a = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { aprop1b = values[63]; }
    if (values.size() > 64) { apar1b = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 67) { aprop2a = values[67]; }
    if (values.size() > 68) { apar2a = values[68]; }
    if (values.size() > 69) { amin2a = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { amax2a = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 75) { aprop3a = values[75]; }
    if (values.size() > 76) { apar3a = (int32_t) std::strtol(values[76].c_str(), nullptr, 10); }
    if (values.size() > 77) { amin3a = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { amax3a = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 83) { aprop4a = values[83]; }
    if (values.size() > 84) { apar4a = (int32_t) std::strtol(values[84].c_str(), nullptr, 10); }
    if (values.size() > 85) { amin4a = (int32_t) std::strtol(values[85].c_str(), nullptr, 10); }
    if (values.size() > 86) { amax4a = (int32_t) std::strtol(values[86].c_str(), nullptr, 10); }
    if (values.size() > 91) { aprop5a = values[91]; }
    if (values.size() > 92) { apar5a = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { amin5a = (int32_t) std::strtol(values[93].c_str(), nullptr, 10); }
    if (values.size() > 94) { amax5a = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 100) { eol = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_setitems> t_setitems::readfile(std::string filename) {
    std::vector<t_setitems> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_setitems v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_sets::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { index = values[0]; }
    if (values.size() > 1) { name = values[1]; }
    if (values.size() > 2) { version = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { PCode2a = values[3]; }
    if (values.size() > 4) { PParam2a = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { PMin2a = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { PMax2a = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { PCode2b = values[7]; }
    if (values.size() > 8) { PParam2b = values[8]; }
    if (values.size() > 9) { PMin2b = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { PMax2b = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { PCode3a = values[11]; }
    if (values.size() > 12) { PParam3a = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { PMin3a = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { PMax3a = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { PCode3b = values[15]; }
    if (values.size() > 16) { PParam3b = values[16]; }
    if (values.size() > 17) { PMin3b = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { PMax3b = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { PCode4a = values[19]; }
    if (values.size() > 21) { PMin4a = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { PMax4a = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { PCode4b = values[23]; }
    if (values.size() > 24) { PParam4b = values[24]; }
    if (values.size() > 25) { PMin4b = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { PMax4b = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { PCode5a = values[27]; }
    if (values.size() > 29) { PMin5a = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { PMax5a = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 35) { FCode1 = values[35]; }
    if (values.size() > 36) { FParam1 = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { FMin1 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { FMax1 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { FCode2 = values[39]; }
    if (values.size() > 40) { FParam2 = values[40]; }
    if (values.size() > 41) { FMin2 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { FMax2 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { FCode3 = values[43]; }
    if (values.size() > 44) { FParam3 = (int32_t) std::strtol(values[44].c_str(), nullptr, 10); }
    if (values.size() > 45) { FMin3 = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { FMax3 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { FCode4 = values[47]; }
    if (values.size() > 48) { FParam4 = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { FMin4 = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { FMax4 = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { FCode5 = values[51]; }
    if (values.size() > 52) { FParam5 = values[52]; }
    if (values.size() > 53) { FMin5 = (int32_t) std::strtol(values[53].c_str(), nullptr, 10); }
    if (values.size() > 54) { FMax5 = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { FCode6 = values[55]; }
    if (values.size() > 56) { FParam6 = values[56]; }
    if (values.size() > 57) { FMin6 = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { FMax6 = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { FCode7 = values[59]; }
    if (values.size() > 60) { FParam7 = values[60]; }
    if (values.size() > 61) { FMin7 = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { FMax7 = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { FCode8 = values[63]; }
    if (values.size() > 65) { FMin8 = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { FMax8 = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 68) { eol = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_sets> t_sets::readfile(std::string filename) {
    std::vector<t_sets> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_sets v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_shrines::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { ShrineType = values[1]; }
    if (values.size() > 2) { Effect = values[2]; }
    if (values.size() > 3) { Code = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Arg0 = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Arg1 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Durationinframes = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { resettimeinminutes = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { rarity = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { StringName = values[9]; }
    if (values.size() > 10) { StringPhrase = values[10]; }
    if (values.size() > 11) { effectclass = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { LevelMin = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_shrines> t_shrines::readfile(std::string filename) {
    std::vector<t_shrines> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_shrines v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_skillcalc::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { code = values[0]; }
    if (values.size() > 1) { Description = values[1]; }

    return values.size();
  }

  std::vector<t_skillcalc> t_skillcalc::readfile(std::string filename) {
    std::vector<t_skillcalc> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_skillcalc v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_skilldesc::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { skilldesc = values[0]; }
    if (values.size() > 1) { SkillPage = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { SkillRow = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { SkillColumn = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { ListRow = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { IconCel = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { HireableIconCel = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { strname = values[7]; }
    if (values.size() > 8) { strshort = values[8]; }
    if (values.size() > 9) { strlong = values[9]; }
    if (values.size() > 10) { stralt = values[10]; }
    if (values.size() > 11) { descdam = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { ddamcalc1 = values[12]; }
    if (values.size() > 13) { ddamcalc2 = values[13]; }
    if (values.size() > 14) { p1dmelem = values[14]; }
    if (values.size() > 15) { p1dmmin = values[15]; }
    if (values.size() > 16) { p1dmmax = values[16]; }
    if (values.size() > 17) { p2dmelem = values[17]; }
    if (values.size() > 18) { p2dmmin = values[18]; }
    if (values.size() > 19) { p2dmmax = values[19]; }
    if (values.size() > 20) { p3dmelem = values[20]; }
    if (values.size() > 21) { p3dmmin = values[21]; }
    if (values.size() > 22) { p3dmmax = values[22]; }
    if (values.size() > 23) { descatt = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { descmissile1 = values[24]; }
    if (values.size() > 25) { descmissile2 = values[25]; }
    if (values.size() > 26) { descmissile3 = values[26]; }
    if (values.size() > 27) { descline1 = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { desctexta1 = values[28]; }
    if (values.size() > 29) { desctextb1 = values[29]; }
    if (values.size() > 30) { desccalca1 = values[30]; }
    if (values.size() > 31) { desccalcb1 = values[31]; }
    if (values.size() > 32) { descline2 = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { desctexta2 = values[33]; }
    if (values.size() > 34) { desctextb2 = values[34]; }
    if (values.size() > 35) { desccalca2 = values[35]; }
    if (values.size() > 36) { desccalcb2 = values[36]; }
    if (values.size() > 37) { descline3 = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { desctexta3 = values[38]; }
    if (values.size() > 39) { desctextb3 = values[39]; }
    if (values.size() > 40) { desccalca3 = values[40]; }
    if (values.size() > 41) { desccalcb3 = values[41]; }
    if (values.size() > 42) { descline4 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { desctexta4 = values[43]; }
    if (values.size() > 44) { desctextb4 = values[44]; }
    if (values.size() > 45) { desccalca4 = values[45]; }
    if (values.size() > 46) { desccalcb4 = values[46]; }
    if (values.size() > 47) { descline5 = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { desctexta5 = values[48]; }
    if (values.size() > 49) { desctextb5 = values[49]; }
    if (values.size() > 50) { desccalca5 = values[50]; }
    if (values.size() > 51) { desccalcb5 = values[51]; }
    if (values.size() > 52) { descline6 = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { desctexta6 = values[53]; }
    if (values.size() > 55) { desccalca6 = values[55]; }
    if (values.size() > 56) { desccalcb6 = values[56]; }
    if (values.size() > 57) { dsc2line1 = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { dsc2texta1 = values[58]; }
    if (values.size() > 59) { dsc2textb1 = values[59]; }
    if (values.size() > 60) { dsc2calca1 = values[60]; }
    if (values.size() > 61) { dsc2calcb1 = values[61]; }
    if (values.size() > 62) { dsc2line2 = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { dsc2texta2 = values[63]; }
    if (values.size() > 64) { dsc2textb2 = values[64]; }
    if (values.size() > 65) { dsc2calca2 = values[65]; }
    if (values.size() > 66) { dsc2calcb2 = values[66]; }
    if (values.size() > 67) { dsc2line3 = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { dsc2texta3 = values[68]; }
    if (values.size() > 69) { dsc2textb3 = values[69]; }
    if (values.size() > 70) { dsc2calca3 = values[70]; }
    if (values.size() > 71) { dsc2calcb3 = values[71]; }
    if (values.size() > 72) { dsc2line4 = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { dsc2texta4 = values[73]; }
    if (values.size() > 75) { dsc2calca4 = values[75]; }
    if (values.size() > 77) { dsc2line5 = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { dsc2texta5 = values[78]; }
    if (values.size() > 80) { dsc2calca5 = values[80]; }
    if (values.size() > 82) { dsc3line1 = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }
    if (values.size() > 83) { dsc3texta1 = values[83]; }
    if (values.size() > 84) { dsc3textb1 = values[84]; }
    if (values.size() > 85) { dsc3calca1 = (int32_t) std::strtol(values[85].c_str(), nullptr, 10); }
    if (values.size() > 87) { dsc3line2 = (int32_t) std::strtol(values[87].c_str(), nullptr, 10); }
    if (values.size() > 88) { dsc3texta2 = values[88]; }
    if (values.size() > 89) { dsc3textb2 = values[89]; }
    if (values.size() > 90) { dsc3calca2 = values[90]; }
    if (values.size() > 91) { dsc3calcb2 = values[91]; }
    if (values.size() > 92) { dsc3line3 = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { dsc3texta3 = values[93]; }
    if (values.size() > 94) { dsc3textb3 = values[94]; }
    if (values.size() > 95) { dsc3calca3 = values[95]; }
    if (values.size() > 96) { dsc3calcb3 = values[96]; }
    if (values.size() > 97) { dsc3line4 = (int32_t) std::strtol(values[97].c_str(), nullptr, 10); }
    if (values.size() > 98) { dsc3texta4 = values[98]; }
    if (values.size() > 99) { dsc3textb4 = values[99]; }
    if (values.size() > 100) { dsc3calca4 = values[100]; }
    if (values.size() > 101) { dsc3calcb4 = (int32_t) std::strtol(values[101].c_str(), nullptr, 10); }
    if (values.size() > 102) { dsc3line5 = (int32_t) std::strtol(values[102].c_str(), nullptr, 10); }
    if (values.size() > 103) { dsc3texta5 = values[103]; }
    if (values.size() > 104) { dsc3textb5 = values[104]; }
    if (values.size() > 105) { dsc3calca5 = values[105]; }
    if (values.size() > 107) { dsc3line6 = (int32_t) std::strtol(values[107].c_str(), nullptr, 10); }
    if (values.size() > 108) { dsc3texta6 = values[108]; }
    if (values.size() > 109) { dsc3textb6 = values[109]; }
    if (values.size() > 110) { dsc3calca6 = values[110]; }
    if (values.size() > 112) { dsc3line7 = (int32_t) std::strtol(values[112].c_str(), nullptr, 10); }
    if (values.size() > 113) { dsc3texta7 = values[113]; }
    if (values.size() > 117) { itemproctext = values[117]; }
    if (values.size() > 118) { itemprocdesclinecount = (int32_t) std::strtol(values[118].c_str(), nullptr, 10); }
    if (values.size() > 119) { eol = (int32_t) std::strtol(values[119].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_skilldesc> t_skilldesc::readfile(std::string filename) {
    std::vector<t_skilldesc> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_skilldesc v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_skills::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { skill = values[0]; }
    if (values.size() > 1) { Id = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { charclass = values[2]; }
    if (values.size() > 3) { skilldesc = values[3]; }
    if (values.size() > 4) { srvstfunc = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { srvdofunc = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { srvstopfunc = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { prgstack = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { srvprgfunc1 = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { srvprgfunc2 = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { srvprgfunc3 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { prgcalc1 = values[11]; }
    if (values.size() > 12) { prgcalc2 = values[12]; }
    if (values.size() > 13) { prgcalc3 = values[13]; }
    if (values.size() > 14) { prgdam = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { srvmissile = values[15]; }
    if (values.size() > 16) { decquant = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { lob = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { srvmissilea = values[18]; }
    if (values.size() > 19) { srvmissileb = values[19]; }
    if (values.size() > 20) { srvmissilec = values[20]; }
    if (values.size() > 22) { srvoverlay = values[22]; }
    if (values.size() > 23) { aurafilter = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { aurastate = values[24]; }
    if (values.size() > 25) { auratargetstate = values[25]; }
    if (values.size() > 26) { auralencalc = values[26]; }
    if (values.size() > 27) { aurarangecalc = values[27]; }
    if (values.size() > 28) { aurastat1 = values[28]; }
    if (values.size() > 29) { aurastatcalc1 = values[29]; }
    if (values.size() > 30) { aurastat2 = values[30]; }
    if (values.size() > 31) { aurastatcalc2 = values[31]; }
    if (values.size() > 32) { aurastat3 = values[32]; }
    if (values.size() > 33) { aurastatcalc3 = values[33]; }
    if (values.size() > 34) { aurastat4 = values[34]; }
    if (values.size() > 35) { aurastatcalc4 = values[35]; }
    if (values.size() > 36) { aurastat5 = values[36]; }
    if (values.size() > 37) { aurastatcalc5 = values[37]; }
    if (values.size() > 38) { aurastat6 = values[38]; }
    if (values.size() > 39) { aurastatcalc6 = values[39]; }
    if (values.size() > 40) { auraevent1 = values[40]; }
    if (values.size() > 41) { auraeventfunc1 = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { auraevent2 = values[42]; }
    if (values.size() > 43) { auraeventfunc2 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { auraevent3 = values[44]; }
    if (values.size() > 45) { auraeventfunc3 = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 48) { passivestate = values[48]; }
    if (values.size() > 49) { passiveitype = values[49]; }
    if (values.size() > 51) { passivestat1 = values[51]; }
    if (values.size() > 52) { passivecalc1 = values[52]; }
    if (values.size() > 53) { passivestat2 = values[53]; }
    if (values.size() > 54) { passivecalc2 = values[54]; }
    if (values.size() > 55) { passivestat3 = values[55]; }
    if (values.size() > 56) { passivecalc3 = values[56]; }
    if (values.size() > 57) { passivestat4 = values[57]; }
    if (values.size() > 58) { passivecalc4 = values[58]; }
    if (values.size() > 59) { passivestat5 = values[59]; }
    if (values.size() > 60) { passivecalc5 = values[60]; }
    if (values.size() > 61) { passivestat6 = values[61]; }
    if (values.size() > 62) { passivecalc6 = values[62]; }
    if (values.size() > 63) { passivestat7 = values[63]; }
    if (values.size() > 64) { passivecalc7 = values[64]; }
    if (values.size() > 65) { passivestat8 = values[65]; }
    if (values.size() > 66) { passivecalc8 = values[66]; }
    if (values.size() > 67) { passivestat9 = values[67]; }
    if (values.size() > 68) { passivecalc9 = values[68]; }
    if (values.size() > 69) { passivestat10 = values[69]; }
    if (values.size() > 70) { passivecalc10 = values[70]; }
    if (values.size() > 71) { passivestat11 = values[71]; }
    if (values.size() > 72) { passivecalc11 = values[72]; }
    if (values.size() > 73) { passivestat12 = values[73]; }
    if (values.size() > 74) { passivecalc12 = values[74]; }
    if (values.size() > 75) { passivestat13 = values[75]; }
    if (values.size() > 76) { passivecalc13 = values[76]; }
    if (values.size() > 77) { passivestat14 = values[77]; }
    if (values.size() > 78) { passivecalc14 = values[78]; }
    if (values.size() > 79) { summon = values[79]; }
    if (values.size() > 80) { pettype = values[80]; }
    if (values.size() > 81) { petmax = values[81]; }
    if (values.size() > 83) { summode = values[83]; }
    if (values.size() > 84) { sumskill1 = values[84]; }
    if (values.size() > 85) { sumsk1calc = values[85]; }
    if (values.size() > 86) { sumskill2 = values[86]; }
    if (values.size() > 87) { sumsk2calc = values[87]; }
    if (values.size() > 88) { sumskill3 = values[88]; }
    if (values.size() > 89) { sumsk3calc = values[89]; }
    if (values.size() > 90) { sumskill4 = values[90]; }
    if (values.size() > 91) { sumsk4calc = values[91]; }
    if (values.size() > 92) { sumskill5 = values[92]; }
    if (values.size() > 93) { sumsk5calc = values[93]; }
    if (values.size() > 94) { sumumod = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 95) { sumoverlay = values[95]; }
    if (values.size() > 96) { stsuccessonly = (int32_t) std::strtol(values[96].c_str(), nullptr, 10); }
    if (values.size() > 97) { stsound = values[97]; }
    if (values.size() > 98) { stsoundclass = values[98]; }
    if (values.size() > 99) { stsounddelay = (int32_t) std::strtol(values[99].c_str(), nullptr, 10); }
    if (values.size() > 100) { weaponsnd = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { dosound = values[101]; }
    if (values.size() > 102) { dosounda = values[102]; }
    if (values.size() > 103) { dosoundb = values[103]; }
    if (values.size() > 104) { tgtoverlay = values[104]; }
    if (values.size() > 105) { tgtsound = values[105]; }
    if (values.size() > 106) { prgoverlay = values[106]; }
    if (values.size() > 107) { prgsound = values[107]; }
    if (values.size() > 108) { castoverlay = values[108]; }
    if (values.size() > 109) { cltoverlaya = values[109]; }
    if (values.size() > 110) { cltoverlayb = values[110]; }
    if (values.size() > 111) { cltstfunc = (int32_t) std::strtol(values[111].c_str(), nullptr, 10); }
    if (values.size() > 112) { cltdofunc = values[112]; }
    if (values.size() > 113) { cltstopfunc = (int32_t) std::strtol(values[113].c_str(), nullptr, 10); }
    if (values.size() > 114) { cltprgfunc1 = (int32_t) std::strtol(values[114].c_str(), nullptr, 10); }
    if (values.size() > 115) { cltprgfunc2 = (int32_t) std::strtol(values[115].c_str(), nullptr, 10); }
    if (values.size() > 116) { cltprgfunc3 = (int32_t) std::strtol(values[116].c_str(), nullptr, 10); }
    if (values.size() > 117) { cltmissile = values[117]; }
    if (values.size() > 118) { cltmissilea = values[118]; }
    if (values.size() > 119) { cltmissileb = values[119]; }
    if (values.size() > 120) { cltmissilec = values[120]; }
    if (values.size() > 121) { cltmissiled = values[121]; }
    if (values.size() > 122) { cltcalc1 = values[122]; }
    if (values.size() > 123) { cltcalc1desc = values[123]; }
    if (values.size() > 124) { cltcalc2 = values[124]; }
    if (values.size() > 125) { cltcalc2desc = values[125]; }
    if (values.size() > 126) { cltcalc3 = (int32_t) std::strtol(values[126].c_str(), nullptr, 10); }
    if (values.size() > 127) { cltcalc3desc = values[127]; }
    if (values.size() > 128) { warp = (int32_t) std::strtol(values[128].c_str(), nullptr, 10); }
    if (values.size() > 129) { immediate = (int32_t) std::strtol(values[129].c_str(), nullptr, 10); }
    if (values.size() > 130) { enhanceable = (int32_t) std::strtol(values[130].c_str(), nullptr, 10); }
    if (values.size() > 131) { attackrank = (int32_t) std::strtol(values[131].c_str(), nullptr, 10); }
    if (values.size() > 132) { noammo = (int32_t) std::strtol(values[132].c_str(), nullptr, 10); }
    if (values.size() > 133) { range = values[133]; }
    if (values.size() > 134) { weapsel = (int32_t) std::strtol(values[134].c_str(), nullptr, 10); }
    if (values.size() > 136) { itypea1 = values[136]; }
    if (values.size() > 137) { itypea2 = values[137]; }
    if (values.size() > 139) { etypea1 = values[139]; }
    if (values.size() > 141) { itypeb1 = values[141]; }
    if (values.size() > 146) { anim = values[146]; }
    if (values.size() > 147) { seqtrans = values[147]; }
    if (values.size() > 148) { monanim = values[148]; }
    if (values.size() > 149) { seqnum = (int32_t) std::strtol(values[149].c_str(), nullptr, 10); }
    if (values.size() > 150) { seqinput = (int32_t) std::strtol(values[150].c_str(), nullptr, 10); }
    if (values.size() > 151) { durability = (int32_t) std::strtol(values[151].c_str(), nullptr, 10); }
    if (values.size() > 152) { UseAttackRate = (int32_t) std::strtol(values[152].c_str(), nullptr, 10); }
    if (values.size() > 153) { LineOfSight = (int32_t) std::strtol(values[153].c_str(), nullptr, 10); }
    if (values.size() > 154) { TargetableOnly = (int32_t) std::strtol(values[154].c_str(), nullptr, 10); }
    if (values.size() > 155) { SearchEnemyXY = (int32_t) std::strtol(values[155].c_str(), nullptr, 10); }
    if (values.size() > 156) { SearchEnemyNear = (int32_t) std::strtol(values[156].c_str(), nullptr, 10); }
    if (values.size() > 157) { SearchOpenXY = (int32_t) std::strtol(values[157].c_str(), nullptr, 10); }
    if (values.size() > 158) { SelectProc = (int32_t) std::strtol(values[158].c_str(), nullptr, 10); }
    if (values.size() > 159) { TargetCorpse = (int32_t) std::strtol(values[159].c_str(), nullptr, 10); }
    if (values.size() > 160) { TargetPet = (int32_t) std::strtol(values[160].c_str(), nullptr, 10); }
    if (values.size() > 161) { TargetAlly = (int32_t) std::strtol(values[161].c_str(), nullptr, 10); }
    if (values.size() > 162) { TargetItem = (int32_t) std::strtol(values[162].c_str(), nullptr, 10); }
    if (values.size() > 163) { AttackNoMana = (int32_t) std::strtol(values[163].c_str(), nullptr, 10); }
    if (values.size() > 164) { TgtPlaceCheck = (int32_t) std::strtol(values[164].c_str(), nullptr, 10); }
    if (values.size() > 165) { KeepCursorStateOnKill = (int32_t) std::strtol(values[165].c_str(), nullptr, 10); }
    if (values.size() > 166) { ContinueCastUnselected = (int32_t) std::strtol(values[166].c_str(), nullptr, 10); }
    if (values.size() > 167) { ClearSelectedOnHold = (int32_t) std::strtol(values[167].c_str(), nullptr, 10); }
    if (values.size() > 168) { ItemEffect = (int32_t) std::strtol(values[168].c_str(), nullptr, 10); }
    if (values.size() > 169) { ItemCltEffect = (int32_t) std::strtol(values[169].c_str(), nullptr, 10); }
    if (values.size() > 170) { ItemTgtDo = (int32_t) std::strtol(values[170].c_str(), nullptr, 10); }
    if (values.size() > 171) { ItemTarget = (int32_t) std::strtol(values[171].c_str(), nullptr, 10); }
    if (values.size() > 172) { ItemUseRestrict = (int32_t) std::strtol(values[172].c_str(), nullptr, 10); }
    if (values.size() > 173) { ItemCheckStart = (int32_t) std::strtol(values[173].c_str(), nullptr, 10); }
    if (values.size() > 174) { ItemCltCheckStart = (int32_t) std::strtol(values[174].c_str(), nullptr, 10); }
    if (values.size() > 175) { ItemCastSound = values[175]; }
    if (values.size() > 176) { ItemCastOverlay = values[176]; }
    if (values.size() > 178) { reqlevel = (int32_t) std::strtol(values[178].c_str(), nullptr, 10); }
    if (values.size() > 179) { maxlvl = (int32_t) std::strtol(values[179].c_str(), nullptr, 10); }
    if (values.size() > 184) { reqskill1 = values[184]; }
    if (values.size() > 185) { reqskill2 = values[185]; }
    if (values.size() > 187) { restrict = (int32_t) std::strtol(values[187].c_str(), nullptr, 10); }
    if (values.size() > 188) { State1 = values[188]; }
    if (values.size() > 189) { State2 = values[189]; }
    if (values.size() > 191) { localdelay = (int32_t) std::strtol(values[191].c_str(), nullptr, 10); }
    if (values.size() > 192) { globaldelay = (int32_t) std::strtol(values[192].c_str(), nullptr, 10); }
    if (values.size() > 193) { leftskill = (int32_t) std::strtol(values[193].c_str(), nullptr, 10); }
    if (values.size() > 194) { rightskill = (int32_t) std::strtol(values[194].c_str(), nullptr, 10); }
    if (values.size() > 195) { repeat = (int32_t) std::strtol(values[195].c_str(), nullptr, 10); }
    if (values.size() > 196) { alwayshit = (int32_t) std::strtol(values[196].c_str(), nullptr, 10); }
    if (values.size() > 197) { usemanaondo = (int32_t) std::strtol(values[197].c_str(), nullptr, 10); }
    if (values.size() > 198) { startmana = (int32_t) std::strtol(values[198].c_str(), nullptr, 10); }
    if (values.size() > 199) { minmana = (int32_t) std::strtol(values[199].c_str(), nullptr, 10); }
    if (values.size() > 200) { manashift = (int32_t) std::strtol(values[200].c_str(), nullptr, 10); }
    if (values.size() > 201) { mana = (int32_t) std::strtol(values[201].c_str(), nullptr, 10); }
    if (values.size() > 202) { lvlmana = (int32_t) std::strtol(values[202].c_str(), nullptr, 10); }
    if (values.size() > 203) { interrupt = (int32_t) std::strtol(values[203].c_str(), nullptr, 10); }
    if (values.size() > 204) { InTown = (int32_t) std::strtol(values[204].c_str(), nullptr, 10); }
    if (values.size() > 205) { aura = (int32_t) std::strtol(values[205].c_str(), nullptr, 10); }
    if (values.size() > 206) { periodic = (int32_t) std::strtol(values[206].c_str(), nullptr, 10); }
    if (values.size() > 207) { perdelay = values[207]; }
    if (values.size() > 208) { finishing = (int32_t) std::strtol(values[208].c_str(), nullptr, 10); }
    if (values.size() > 209) { prgchargestocast = (int32_t) std::strtol(values[209].c_str(), nullptr, 10); }
    if (values.size() > 210) { prgchargesconsumed = (int32_t) std::strtol(values[210].c_str(), nullptr, 10); }
    if (values.size() > 211) { passive = (int32_t) std::strtol(values[211].c_str(), nullptr, 10); }
    if (values.size() > 212) { progressive = (int32_t) std::strtol(values[212].c_str(), nullptr, 10); }
    if (values.size() > 213) { scroll = values[213]; }
    if (values.size() > 214) { calc1 = values[214]; }
    if (values.size() > 215) { calc1desc = values[215]; }
    if (values.size() > 216) { calc2 = values[216]; }
    if (values.size() > 217) { calc2desc = values[217]; }
    if (values.size() > 218) { calc3 = values[218]; }
    if (values.size() > 219) { calc3desc = values[219]; }
    if (values.size() > 220) { calc4 = values[220]; }
    if (values.size() > 221) { calc4desc = values[221]; }
    if (values.size() > 222) { calc5 = values[222]; }
    if (values.size() > 223) { calc5desc = values[223]; }
    if (values.size() > 234) { Param1 = (int32_t) std::strtol(values[234].c_str(), nullptr, 10); }
    if (values.size() > 235) { Param1Description = values[235]; }
    if (values.size() > 236) { Param2 = (int32_t) std::strtol(values[236].c_str(), nullptr, 10); }
    if (values.size() > 237) { Param2Description = values[237]; }
    if (values.size() > 238) { Param3 = (int32_t) std::strtol(values[238].c_str(), nullptr, 10); }
    if (values.size() > 239) { Param3Description = values[239]; }
    if (values.size() > 240) { Param4 = (int32_t) std::strtol(values[240].c_str(), nullptr, 10); }
    if (values.size() > 241) { Param4Description = values[241]; }
    if (values.size() > 242) { Param5 = (int32_t) std::strtol(values[242].c_str(), nullptr, 10); }
    if (values.size() > 243) { Param5Description = values[243]; }
    if (values.size() > 244) { Param6 = (int32_t) std::strtol(values[244].c_str(), nullptr, 10); }
    if (values.size() > 245) { Param6Description = values[245]; }
    if (values.size() > 246) { Param7 = (int32_t) std::strtol(values[246].c_str(), nullptr, 10); }
    if (values.size() > 247) { Param7Description = values[247]; }
    if (values.size() > 248) { Param8 = (int32_t) std::strtol(values[248].c_str(), nullptr, 10); }
    if (values.size() > 249) { Param8Description = values[249]; }
    if (values.size() > 250) { Param9 = (int32_t) std::strtol(values[250].c_str(), nullptr, 10); }
    if (values.size() > 251) { Param9Description = values[251]; }
    if (values.size() > 252) { Param10 = (int32_t) std::strtol(values[252].c_str(), nullptr, 10); }
    if (values.size() > 253) { Param10Description2 = values[253]; }
    if (values.size() > 254) { Param11 = (int32_t) std::strtol(values[254].c_str(), nullptr, 10); }
    if (values.size() > 255) { Param11Description = values[255]; }
    if (values.size() > 256) { Param12 = (int32_t) std::strtol(values[256].c_str(), nullptr, 10); }
    if (values.size() > 257) { Param12Description = values[257]; }
    if (values.size() > 274) { InGame = (int32_t) std::strtol(values[274].c_str(), nullptr, 10); }
    if (values.size() > 275) { ToHit = (int32_t) std::strtol(values[275].c_str(), nullptr, 10); }
    if (values.size() > 276) { LevToHit = (int32_t) std::strtol(values[276].c_str(), nullptr, 10); }
    if (values.size() > 277) { ToHitCalc = values[277]; }
    if (values.size() > 278) { ResultFlags = (int32_t) std::strtol(values[278].c_str(), nullptr, 10); }
    if (values.size() > 279) { HitFlags = (int32_t) std::strtol(values[279].c_str(), nullptr, 10); }
    if (values.size() > 280) { HitClass = (int32_t) std::strtol(values[280].c_str(), nullptr, 10); }
    if (values.size() > 281) { Kick = (int32_t) std::strtol(values[281].c_str(), nullptr, 10); }
    if (values.size() > 282) { HitShift = (int32_t) std::strtol(values[282].c_str(), nullptr, 10); }
    if (values.size() > 283) { SrcDam = (int32_t) std::strtol(values[283].c_str(), nullptr, 10); }
    if (values.size() > 284) { MinDam = (int32_t) std::strtol(values[284].c_str(), nullptr, 10); }
    if (values.size() > 285) { MinLevDam1 = (int32_t) std::strtol(values[285].c_str(), nullptr, 10); }
    if (values.size() > 286) { MinLevDam2 = (int32_t) std::strtol(values[286].c_str(), nullptr, 10); }
    if (values.size() > 287) { MinLevDam3 = (int32_t) std::strtol(values[287].c_str(), nullptr, 10); }
    if (values.size() > 288) { MinLevDam4 = (int32_t) std::strtol(values[288].c_str(), nullptr, 10); }
    if (values.size() > 289) { MinLevDam5 = (int32_t) std::strtol(values[289].c_str(), nullptr, 10); }
    if (values.size() > 290) { MaxDam = (int32_t) std::strtol(values[290].c_str(), nullptr, 10); }
    if (values.size() > 291) { MaxLevDam1 = (int32_t) std::strtol(values[291].c_str(), nullptr, 10); }
    if (values.size() > 292) { MaxLevDam2 = (int32_t) std::strtol(values[292].c_str(), nullptr, 10); }
    if (values.size() > 293) { MaxLevDam3 = (int32_t) std::strtol(values[293].c_str(), nullptr, 10); }
    if (values.size() > 294) { MaxLevDam4 = (int32_t) std::strtol(values[294].c_str(), nullptr, 10); }
    if (values.size() > 295) { MaxLevDam5 = (int32_t) std::strtol(values[295].c_str(), nullptr, 10); }
    if (values.size() > 296) { DmgSymPerCalc = values[296]; }
    if (values.size() > 297) { EType = values[297]; }
    if (values.size() > 298) { EMin = (int32_t) std::strtol(values[298].c_str(), nullptr, 10); }
    if (values.size() > 299) { EMinLev1 = (int32_t) std::strtol(values[299].c_str(), nullptr, 10); }
    if (values.size() > 300) { EMinLev2 = (int32_t) std::strtol(values[300].c_str(), nullptr, 10); }
    if (values.size() > 301) { EMinLev3 = (int32_t) std::strtol(values[301].c_str(), nullptr, 10); }
    if (values.size() > 302) { EMinLev4 = (int32_t) std::strtol(values[302].c_str(), nullptr, 10); }
    if (values.size() > 303) { EMinLev5 = (int32_t) std::strtol(values[303].c_str(), nullptr, 10); }
    if (values.size() > 304) { EMax = (int32_t) std::strtol(values[304].c_str(), nullptr, 10); }
    if (values.size() > 305) { EMaxLev1 = (int32_t) std::strtol(values[305].c_str(), nullptr, 10); }
    if (values.size() > 306) { EMaxLev2 = (int32_t) std::strtol(values[306].c_str(), nullptr, 10); }
    if (values.size() > 307) { EMaxLev3 = (int32_t) std::strtol(values[307].c_str(), nullptr, 10); }
    if (values.size() > 308) { EMaxLev4 = (int32_t) std::strtol(values[308].c_str(), nullptr, 10); }
    if (values.size() > 309) { EMaxLev5 = (int32_t) std::strtol(values[309].c_str(), nullptr, 10); }
    if (values.size() > 310) { EDmgSymPerCalc = values[310]; }
    if (values.size() > 311) { ELen = (int32_t) std::strtol(values[311].c_str(), nullptr, 10); }
    if (values.size() > 312) { ELevLen1 = (int32_t) std::strtol(values[312].c_str(), nullptr, 10); }
    if (values.size() > 313) { ELevLen2 = (int32_t) std::strtol(values[313].c_str(), nullptr, 10); }
    if (values.size() > 314) { ELevLen3 = (int32_t) std::strtol(values[314].c_str(), nullptr, 10); }
    if (values.size() > 315) { ELenSymPerCalc = values[315]; }
    if (values.size() > 316) { aitype = (int32_t) std::strtol(values[316].c_str(), nullptr, 10); }
    if (values.size() > 317) { aibonus = (int32_t) std::strtol(values[317].c_str(), nullptr, 10); }
    if (values.size() > 318) { costmult = (int32_t) std::strtol(values[318].c_str(), nullptr, 10); }
    if (values.size() > 319) { costadd = (int32_t) std::strtol(values[319].c_str(), nullptr, 10); }
    if (values.size() > 320) { eol = (int32_t) std::strtol(values[320].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_skills> t_skills::readfile(std::string filename) {
    std::vector<t_skills> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_skills v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_soundenviron::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Handle = values[0]; }
    if (values.size() > 1) { Index = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Song = values[2]; }
    if (values.size() > 3) { DayAmbience = values[3]; }
    if (values.size() > 4) { HDDayAmbience = values[4]; }
    if (values.size() > 5) { NightAmbience = values[5]; }
    if (values.size() > 6) { HDNightAmbience = values[6]; }
    if (values.size() > 7) { DayEvent = values[7]; }
    if (values.size() > 8) { HDDayEvent = values[8]; }
    if (values.size() > 9) { NightEvent = values[9]; }
    if (values.size() > 10) { HDNightEvent = values[10]; }
    if (values.size() > 11) { EventDelay = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { HDEventDelay = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Indoors = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { Material1 = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { HDMaterial1 = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { Material2 = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { HDMaterial2 = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { SFXEAXEnviron = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { SFXEAXRoomVol = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { SFXEAXRoomHF = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { SFXEAXDecayTime = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { SFXEAXDecayHF = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { SFXEAXReflect = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { SFXEAXReflectDelay = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { SFXEAXReverb = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { SFXEAXRevDelay = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { VOXEAXEnviron = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { VOXEAXRoomVol = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { VOXEAXRoomHF = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { VOXEAXDecayTime = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { VOXEAXDecayHF = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { VOXEAXReflect = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { VOXEAXReflectDelay = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { VOXEAXReverb = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { VOXEAXRevDelay = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { InheritEnvrionment = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_soundenviron> t_soundenviron::readfile(std::string filename) {
    std::vector<t_soundenviron> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_soundenviron v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_sounds::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Sound = values[0]; }
    if (values.size() > 1) { Index = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { Redirect = values[2]; }
    if (values.size() > 3) { Channel = values[3]; }
    if (values.size() > 4) { FileName = values[4]; }
    if (values.size() > 5) { IsLocal = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { IsMusic = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { IsAmbientScene = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { IsAmbientEvent = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { IsUI = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { VolumeMin = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { VolumeMax = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { PitchMin = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { PitchMax = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { GroupSize = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { GroupWeight = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { Loop = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { FadeIn = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { FadeOut = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { DeferInst = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { StopInst = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { Duration = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { Compound = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { Falloff = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { LFEMix = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { _3dSpread = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { Priority = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { Stream = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { Is2D = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { Tracking = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { Solo = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { MusicVol = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { Block1 = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { Block2 = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { Block3 = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { HDOptOut = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { Delay = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_sounds> t_sounds::readfile(std::string filename) {
    std::vector<t_sounds> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_sounds v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_states::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { state = values[0]; }
    if (values.size() > 1) { ID = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { group = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { remhit = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { nosend = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { transform = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { aura = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { curable = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { curse = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { active = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { restrict = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { disguise = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { attblue = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { damblue = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { armblue = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { rfblue = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { rlblue = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { rcblue = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { stambarblue = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { rpblue = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 21) { damred = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { armred = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { rfred = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { rlred = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { rcred = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { rpred = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { exp = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { plrstaydeath = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { monstaydeath = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { bossstaydeath = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { hide = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { hidedead = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { shatter = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { udead = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { life = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { green = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { pgsv = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { nooverlays = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { noclear = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { bossinv = (int32_t) std::strtol(values[40].c_str(), nullptr, 10); }
    if (values.size() > 41) { meleeonly = (int32_t) std::strtol(values[41].c_str(), nullptr, 10); }
    if (values.size() > 42) { notondead = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { overlay1 = values[43]; }
    if (values.size() > 44) { overlay2 = values[44]; }
    if (values.size() > 45) { overlay3 = values[45]; }
    if (values.size() > 46) { overlay4 = values[46]; }
    if (values.size() > 47) { pgsvoverlay = values[47]; }
    if (values.size() > 48) { castoverlay = values[48]; }
    if (values.size() > 49) { removerlay = values[49]; }
    if (values.size() > 50) { stat = values[50]; }
    if (values.size() > 51) { setfunc = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { remfunc = (int32_t) std::strtol(values[52].c_str(), nullptr, 10); }
    if (values.size() > 53) { missile = values[53]; }
    if (values.size() > 54) { skill = values[54]; }
    if (values.size() > 55) { itemtype = values[55]; }
    if (values.size() > 56) { itemtrans = values[56]; }
    if (values.size() > 57) { colorpri = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { colorshift = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { lightr = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { lightg = (int32_t) std::strtol(values[60].c_str(), nullptr, 10); }
    if (values.size() > 61) { lightb = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { onsound = values[62]; }
    if (values.size() > 63) { offsound = values[63]; }
    if (values.size() > 64) { gfxtype = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { gfxclass = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { cltevent = values[66]; }
    if (values.size() > 67) { clteventfunc = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { cltactivefunc = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { srvactivefunc = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 71) { sunderfull = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { sunderresreduce = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 74) { eol = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_states> t_states::readfile(std::string filename) {
    std::vector<t_states> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_states v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_storepage::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { StorePage = values[0]; }
    if (values.size() > 1) { Code = values[1]; }

    return values.size();
  }

  std::vector<t_storepage> t_storepage::readfile(std::string filename) {
    std::vector<t_storepage> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_storepage v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_superuniques::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Superunique = values[0]; }
    if (values.size() > 1) { Name = values[1]; }
    if (values.size() > 2) { Class = values[2]; }
    if (values.size() > 3) { hcIdx = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { MonSound = values[4]; }
    if (values.size() > 5) { Mod1 = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Mod2 = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Mod3 = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { MinGrp = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { MaxGrp = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 10) { AutoPos = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Stacks = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { Replaceable = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Utrans = (int32_t) std::strtol(values[13].c_str(), nullptr, 10); }
    if (values.size() > 14) { UtransN = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { UtransH = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { TC = values[16]; }
    if (values.size() > 17) { TCDesecrated = values[17]; }
    if (values.size() > 18) { TCN = values[18]; }
    if (values.size() > 19) { TCNDesecrated = values[19]; }
    if (values.size() > 20) { TCH = values[20]; }
    if (values.size() > 21) { TCHDesecrated = values[21]; }
    if (values.size() > 22) { eol = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_superuniques> t_superuniques::readfile(std::string filename) {
    std::vector<t_superuniques> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_superuniques v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_treasureclassex::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { TreasureClass = values[0]; }
    if (values.size() > 1) { group = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { level = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { Picks = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { Unique = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 5) { Set = (int32_t) std::strtol(values[5].c_str(), nullptr, 10); }
    if (values.size() > 6) { Rare = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { Magic = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { NoDrop = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { Item1 = values[9]; }
    if (values.size() > 10) { Prob1 = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { Item2 = values[11]; }
    if (values.size() > 12) { Prob2 = (int32_t) std::strtol(values[12].c_str(), nullptr, 10); }
    if (values.size() > 13) { Item3 = values[13]; }
    if (values.size() > 14) { Prob3 = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { Item4 = values[15]; }
    if (values.size() > 16) { Prob4 = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { Item5 = values[17]; }
    if (values.size() > 18) { Prob5 = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { Item6 = values[19]; }
    if (values.size() > 20) { Prob6 = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { Item7 = values[21]; }
    if (values.size() > 22) { Prob7 = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { Item8 = values[23]; }
    if (values.size() > 24) { Prob8 = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { Item9 = values[25]; }
    if (values.size() > 26) { Prob9 = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 29) { ItemProbSum = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { ItemProbTotal = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { TreasureClassDropChance = std::strtod(values[31].c_str(), nullptr); }
    if (values.size() > 33) { firstLadderSeason = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { lastLadderSeason = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { noAlwaysSpawn = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 38) { eol = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_treasureclassex> t_treasureclassex::readfile(std::string filename) {
    std::vector<t_treasureclassex> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_treasureclassex v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_uniqueappellation::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }

    return values.size();
  }

  std::vector<t_uniqueappellation> t_uniqueappellation::readfile(std::string filename) {
    std::vector<t_uniqueappellation> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_uniqueappellation v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_uniqueitems::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { index = values[0]; }
    if (values.size() > 1) { ID = (int32_t) std::strtol(values[1].c_str(), nullptr, 10); }
    if (values.size() > 2) { version = (int32_t) std::strtol(values[2].c_str(), nullptr, 10); }
    if (values.size() > 3) { disabled = (int32_t) std::strtol(values[3].c_str(), nullptr, 10); }
    if (values.size() > 4) { spawnable = (int32_t) std::strtol(values[4].c_str(), nullptr, 10); }
    if (values.size() > 6) { firstLadderSeason = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 7) { lastLadderSeason = (int32_t) std::strtol(values[7].c_str(), nullptr, 10); }
    if (values.size() > 8) { rarity = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 10) { lvl = (int32_t) std::strtol(values[10].c_str(), nullptr, 10); }
    if (values.size() > 11) { lvlreq = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { code = values[12]; }
    if (values.size() > 13) { ItemName = values[13]; }
    if (values.size() > 14) { carry1 = (int32_t) std::strtol(values[14].c_str(), nullptr, 10); }
    if (values.size() > 15) { costmult = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { costadd = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { chrtransform = values[17]; }
    if (values.size() > 18) { invtransform = values[18]; }
    if (values.size() > 19) { flippyfile = values[19]; }
    if (values.size() > 20) { invfile = values[20]; }
    if (values.size() > 21) { dropsound = values[21]; }
    if (values.size() > 22) { dropsfxframe = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { usesound = values[23]; }
    if (values.size() > 24) { prop1 = values[24]; }
    if (values.size() > 25) { par1 = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { min1 = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { max1 = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { prop2 = values[28]; }
    if (values.size() > 29) { par2 = values[29]; }
    if (values.size() > 30) { min2 = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { max2 = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { prop3 = values[32]; }
    if (values.size() > 33) { par3 = values[33]; }
    if (values.size() > 34) { min3 = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { max3 = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { prop4 = values[36]; }
    if (values.size() > 37) { par4 = values[37]; }
    if (values.size() > 38) { min4 = (int32_t) std::strtol(values[38].c_str(), nullptr, 10); }
    if (values.size() > 39) { max4 = (int32_t) std::strtol(values[39].c_str(), nullptr, 10); }
    if (values.size() > 40) { prop5 = values[40]; }
    if (values.size() > 41) { par5 = values[41]; }
    if (values.size() > 42) { min5 = (int32_t) std::strtol(values[42].c_str(), nullptr, 10); }
    if (values.size() > 43) { max5 = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { prop6 = values[44]; }
    if (values.size() > 45) { par6 = values[45]; }
    if (values.size() > 46) { min6 = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { max6 = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { prop7 = values[48]; }
    if (values.size() > 49) { par7 = values[49]; }
    if (values.size() > 50) { min7 = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { max7 = (int32_t) std::strtol(values[51].c_str(), nullptr, 10); }
    if (values.size() > 52) { prop8 = values[52]; }
    if (values.size() > 53) { par8 = values[53]; }
    if (values.size() > 54) { min8 = (int32_t) std::strtol(values[54].c_str(), nullptr, 10); }
    if (values.size() > 55) { max8 = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { prop9 = values[56]; }
    if (values.size() > 57) { par9 = values[57]; }
    if (values.size() > 58) { min9 = (int32_t) std::strtol(values[58].c_str(), nullptr, 10); }
    if (values.size() > 59) { max9 = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { prop10 = values[60]; }
    if (values.size() > 61) { par10 = values[61]; }
    if (values.size() > 62) { min10 = (int32_t) std::strtol(values[62].c_str(), nullptr, 10); }
    if (values.size() > 63) { max10 = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 72) { diablocloneweight = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { eol = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_uniqueitems> t_uniqueitems::readfile(std::string filename) {
    std::vector<t_uniqueitems> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_uniqueitems v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_uniqueprefix::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }

    return values.size();
  }

  std::vector<t_uniqueprefix> t_uniqueprefix::readfile(std::string filename) {
    std::vector<t_uniqueprefix> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_uniqueprefix v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_uniquesuffix::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { Name = values[0]; }

    return values.size();
  }

  std::vector<t_uniquesuffix> t_uniquesuffix::readfile(std::string filename) {
    std::vector<t_uniquesuffix> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_uniquesuffix v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_wanderingmon::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { _class = values[0]; }

    return values.size();
  }

  std::vector<t_wanderingmon> t_wanderingmon::readfile(std::string filename) {
    std::vector<t_wanderingmon> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_wanderingmon v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

  size_t t_weapons::read(const char* line) {
    std::vector<std::string> values = splitline(line);

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { type = values[1]; }
    if (values.size() > 3) { code = values[3]; }
    if (values.size() > 4) { alternategfx = values[4]; }
    if (values.size() > 5) { namestr = values[5]; }
    if (values.size() > 6) { version = (int32_t) std::strtol(values[6].c_str(), nullptr, 10); }
    if (values.size() > 8) { rarity = (int32_t) std::strtol(values[8].c_str(), nullptr, 10); }
    if (values.size() > 9) { spawnable = (int32_t) std::strtol(values[9].c_str(), nullptr, 10); }
    if (values.size() > 11) { Transmogrify = (int32_t) std::strtol(values[11].c_str(), nullptr, 10); }
    if (values.size() > 12) { TMogType = values[12]; }
    if (values.size() > 15) { mindam = (int32_t) std::strtol(values[15].c_str(), nullptr, 10); }
    if (values.size() > 16) { maxdam = (int32_t) std::strtol(values[16].c_str(), nullptr, 10); }
    if (values.size() > 17) { _1or2handed = (int32_t) std::strtol(values[17].c_str(), nullptr, 10); }
    if (values.size() > 18) { _2handed = (int32_t) std::strtol(values[18].c_str(), nullptr, 10); }
    if (values.size() > 19) { _2handmindam = (int32_t) std::strtol(values[19].c_str(), nullptr, 10); }
    if (values.size() > 20) { _2handmaxdam = (int32_t) std::strtol(values[20].c_str(), nullptr, 10); }
    if (values.size() > 21) { minmisdam = (int32_t) std::strtol(values[21].c_str(), nullptr, 10); }
    if (values.size() > 22) { maxmisdam = (int32_t) std::strtol(values[22].c_str(), nullptr, 10); }
    if (values.size() > 23) { rangeadder = (int32_t) std::strtol(values[23].c_str(), nullptr, 10); }
    if (values.size() > 24) { speed = (int32_t) std::strtol(values[24].c_str(), nullptr, 10); }
    if (values.size() > 25) { StrBonus = (int32_t) std::strtol(values[25].c_str(), nullptr, 10); }
    if (values.size() > 26) { DexBonus = (int32_t) std::strtol(values[26].c_str(), nullptr, 10); }
    if (values.size() > 27) { reqstr = (int32_t) std::strtol(values[27].c_str(), nullptr, 10); }
    if (values.size() > 28) { reqdex = (int32_t) std::strtol(values[28].c_str(), nullptr, 10); }
    if (values.size() > 29) { durability = (int32_t) std::strtol(values[29].c_str(), nullptr, 10); }
    if (values.size() > 30) { nodurability = (int32_t) std::strtol(values[30].c_str(), nullptr, 10); }
    if (values.size() > 31) { level = (int32_t) std::strtol(values[31].c_str(), nullptr, 10); }
    if (values.size() > 32) { ShowLevel = (int32_t) std::strtol(values[32].c_str(), nullptr, 10); }
    if (values.size() > 33) { levelreq = (int32_t) std::strtol(values[33].c_str(), nullptr, 10); }
    if (values.size() > 34) { cost = (int32_t) std::strtol(values[34].c_str(), nullptr, 10); }
    if (values.size() > 35) { gamblecost = (int32_t) std::strtol(values[35].c_str(), nullptr, 10); }
    if (values.size() > 36) { magiclvl = (int32_t) std::strtol(values[36].c_str(), nullptr, 10); }
    if (values.size() > 37) { autoprefix = (int32_t) std::strtol(values[37].c_str(), nullptr, 10); }
    if (values.size() > 38) { normcode = values[38]; }
    if (values.size() > 39) { ubercode = values[39]; }
    if (values.size() > 40) { ultracode = values[40]; }
    if (values.size() > 41) { wclass = values[41]; }
    if (values.size() > 42) { _2handedwclass = values[42]; }
    if (values.size() > 43) { component = (int32_t) std::strtol(values[43].c_str(), nullptr, 10); }
    if (values.size() > 44) { hitclass = values[44]; }
    if (values.size() > 45) { invwidth = (int32_t) std::strtol(values[45].c_str(), nullptr, 10); }
    if (values.size() > 46) { invheight = (int32_t) std::strtol(values[46].c_str(), nullptr, 10); }
    if (values.size() > 47) { stackable = (int32_t) std::strtol(values[47].c_str(), nullptr, 10); }
    if (values.size() > 48) { minstack = (int32_t) std::strtol(values[48].c_str(), nullptr, 10); }
    if (values.size() > 49) { maxstack = (int32_t) std::strtol(values[49].c_str(), nullptr, 10); }
    if (values.size() > 50) { spawnstack = (int32_t) std::strtol(values[50].c_str(), nullptr, 10); }
    if (values.size() > 51) { flippyfile = values[51]; }
    if (values.size() > 52) { invfile = values[52]; }
    if (values.size() > 53) { uniqueinvfile = values[53]; }
    if (values.size() > 54) { setinvfile = values[54]; }
    if (values.size() > 55) { hasinv = (int32_t) std::strtol(values[55].c_str(), nullptr, 10); }
    if (values.size() > 56) { gemsockets = (int32_t) std::strtol(values[56].c_str(), nullptr, 10); }
    if (values.size() > 57) { gemapplytype = (int32_t) std::strtol(values[57].c_str(), nullptr, 10); }
    if (values.size() > 58) { comment = values[58]; }
    if (values.size() > 59) { useable = (int32_t) std::strtol(values[59].c_str(), nullptr, 10); }
    if (values.size() > 60) { dropsound = values[60]; }
    if (values.size() > 61) { dropsfxframe = (int32_t) std::strtol(values[61].c_str(), nullptr, 10); }
    if (values.size() > 62) { usesound = values[62]; }
    if (values.size() > 63) { unique = (int32_t) std::strtol(values[63].c_str(), nullptr, 10); }
    if (values.size() > 64) { transparent = (int32_t) std::strtol(values[64].c_str(), nullptr, 10); }
    if (values.size() > 65) { transtbl = (int32_t) std::strtol(values[65].c_str(), nullptr, 10); }
    if (values.size() > 66) { quivered = (int32_t) std::strtol(values[66].c_str(), nullptr, 10); }
    if (values.size() > 67) { lightradius = (int32_t) std::strtol(values[67].c_str(), nullptr, 10); }
    if (values.size() > 68) { belt = (int32_t) std::strtol(values[68].c_str(), nullptr, 10); }
    if (values.size() > 69) { quest = (int32_t) std::strtol(values[69].c_str(), nullptr, 10); }
    if (values.size() > 70) { questdiffcheck = (int32_t) std::strtol(values[70].c_str(), nullptr, 10); }
    if (values.size() > 71) { missiletype = (int32_t) std::strtol(values[71].c_str(), nullptr, 10); }
    if (values.size() > 72) { durwarning = (int32_t) std::strtol(values[72].c_str(), nullptr, 10); }
    if (values.size() > 73) { qntwarning = (int32_t) std::strtol(values[73].c_str(), nullptr, 10); }
    if (values.size() > 74) { gemoffset = (int32_t) std::strtol(values[74].c_str(), nullptr, 10); }
    if (values.size() > 75) { bitfield1 = (int32_t) std::strtol(values[75].c_str(), nullptr, 10); }
    if (values.size() > 76) { CharsiMin = (int32_t) std::strtol(values[76].c_str(), nullptr, 10); }
    if (values.size() > 77) { CharsiMax = (int32_t) std::strtol(values[77].c_str(), nullptr, 10); }
    if (values.size() > 78) { CharsiMagicMin = (int32_t) std::strtol(values[78].c_str(), nullptr, 10); }
    if (values.size() > 79) { CharsiMagicMax = (int32_t) std::strtol(values[79].c_str(), nullptr, 10); }
    if (values.size() > 80) { CharsiMagicLvl = (int32_t) std::strtol(values[80].c_str(), nullptr, 10); }
    if (values.size() > 81) { GheedMin = (int32_t) std::strtol(values[81].c_str(), nullptr, 10); }
    if (values.size() > 82) { GheedMax = (int32_t) std::strtol(values[82].c_str(), nullptr, 10); }
    if (values.size() > 83) { GheedMagicMin = (int32_t) std::strtol(values[83].c_str(), nullptr, 10); }
    if (values.size() > 84) { GheedMagicMax = (int32_t) std::strtol(values[84].c_str(), nullptr, 10); }
    if (values.size() > 85) { GheedMagicLvl = (int32_t) std::strtol(values[85].c_str(), nullptr, 10); }
    if (values.size() > 86) { AkaraMin = (int32_t) std::strtol(values[86].c_str(), nullptr, 10); }
    if (values.size() > 87) { AkaraMax = (int32_t) std::strtol(values[87].c_str(), nullptr, 10); }
    if (values.size() > 88) { AkaraMagicMin = (int32_t) std::strtol(values[88].c_str(), nullptr, 10); }
    if (values.size() > 89) { AkaraMagicMax = (int32_t) std::strtol(values[89].c_str(), nullptr, 10); }
    if (values.size() > 90) { AkaraMagicLvl = (int32_t) std::strtol(values[90].c_str(), nullptr, 10); }
    if (values.size() > 91) { FaraMin = (int32_t) std::strtol(values[91].c_str(), nullptr, 10); }
    if (values.size() > 92) { FaraMax = (int32_t) std::strtol(values[92].c_str(), nullptr, 10); }
    if (values.size() > 93) { FaraMagicMin = (int32_t) std::strtol(values[93].c_str(), nullptr, 10); }
    if (values.size() > 94) { FaraMagicMax = (int32_t) std::strtol(values[94].c_str(), nullptr, 10); }
    if (values.size() > 95) { FaraMagicLvl = (int32_t) std::strtol(values[95].c_str(), nullptr, 10); }
    if (values.size() > 100) { LysanderMagicLvl = (int32_t) std::strtol(values[100].c_str(), nullptr, 10); }
    if (values.size() > 101) { DrognanMin = (int32_t) std::strtol(values[101].c_str(), nullptr, 10); }
    if (values.size() > 102) { DrognanMax = (int32_t) std::strtol(values[102].c_str(), nullptr, 10); }
    if (values.size() > 103) { DrognanMagicMin = (int32_t) std::strtol(values[103].c_str(), nullptr, 10); }
    if (values.size() > 104) { DrognanMagicMax = (int32_t) std::strtol(values[104].c_str(), nullptr, 10); }
    if (values.size() > 105) { DrognanMagicLvl = (int32_t) std::strtol(values[105].c_str(), nullptr, 10); }
    if (values.size() > 106) { HratliMin = (int32_t) std::strtol(values[106].c_str(), nullptr, 10); }
    if (values.size() > 107) { HratliMax = (int32_t) std::strtol(values[107].c_str(), nullptr, 10); }
    if (values.size() > 108) { HratliMagicMin = (int32_t) std::strtol(values[108].c_str(), nullptr, 10); }
    if (values.size() > 109) { HratliMagicMax = (int32_t) std::strtol(values[109].c_str(), nullptr, 10); }
    if (values.size() > 110) { HratliMagicLvl = (int32_t) std::strtol(values[110].c_str(), nullptr, 10); }
    if (values.size() > 115) { AlkorMagicLvl = (int32_t) std::strtol(values[115].c_str(), nullptr, 10); }
    if (values.size() > 116) { OrmusMin = (int32_t) std::strtol(values[116].c_str(), nullptr, 10); }
    if (values.size() > 117) { OrmusMax = (int32_t) std::strtol(values[117].c_str(), nullptr, 10); }
    if (values.size() > 118) { OrmusMagicMin = (int32_t) std::strtol(values[118].c_str(), nullptr, 10); }
    if (values.size() > 119) { OrmusMagicMax = (int32_t) std::strtol(values[119].c_str(), nullptr, 10); }
    if (values.size() > 120) { OrmusMagicLvl = (int32_t) std::strtol(values[120].c_str(), nullptr, 10); }
    if (values.size() > 121) { ElzixMin = (int32_t) std::strtol(values[121].c_str(), nullptr, 10); }
    if (values.size() > 122) { ElzixMax = (int32_t) std::strtol(values[122].c_str(), nullptr, 10); }
    if (values.size() > 123) { ElzixMagicMin = (int32_t) std::strtol(values[123].c_str(), nullptr, 10); }
    if (values.size() > 124) { ElzixMagicMax = (int32_t) std::strtol(values[124].c_str(), nullptr, 10); }
    if (values.size() > 125) { ElzixMagicLvl = (int32_t) std::strtol(values[125].c_str(), nullptr, 10); }
    if (values.size() > 126) { AshearaMin = (int32_t) std::strtol(values[126].c_str(), nullptr, 10); }
    if (values.size() > 127) { AshearaMax = (int32_t) std::strtol(values[127].c_str(), nullptr, 10); }
    if (values.size() > 128) { AshearaMagicMin = (int32_t) std::strtol(values[128].c_str(), nullptr, 10); }
    if (values.size() > 129) { AshearaMagicMax = (int32_t) std::strtol(values[129].c_str(), nullptr, 10); }
    if (values.size() > 130) { AshearaMagicLvl = (int32_t) std::strtol(values[130].c_str(), nullptr, 10); }
    if (values.size() > 131) { CainMin = (int32_t) std::strtol(values[131].c_str(), nullptr, 10); }
    if (values.size() > 132) { CainMax = (int32_t) std::strtol(values[132].c_str(), nullptr, 10); }
    if (values.size() > 133) { CainMagicMin = (int32_t) std::strtol(values[133].c_str(), nullptr, 10); }
    if (values.size() > 134) { CainMagicMax = (int32_t) std::strtol(values[134].c_str(), nullptr, 10); }
    if (values.size() > 135) { CainMagicLvl = (int32_t) std::strtol(values[135].c_str(), nullptr, 10); }
    if (values.size() > 136) { HalbuMin = (int32_t) std::strtol(values[136].c_str(), nullptr, 10); }
    if (values.size() > 137) { HalbuMax = (int32_t) std::strtol(values[137].c_str(), nullptr, 10); }
    if (values.size() > 138) { HalbuMagicMin = (int32_t) std::strtol(values[138].c_str(), nullptr, 10); }
    if (values.size() > 139) { HalbuMagicMax = (int32_t) std::strtol(values[139].c_str(), nullptr, 10); }
    if (values.size() > 140) { HalbuMagicLvl = (int32_t) std::strtol(values[140].c_str(), nullptr, 10); }
    if (values.size() > 141) { JamellaMin = (int32_t) std::strtol(values[141].c_str(), nullptr, 10); }
    if (values.size() > 142) { JamellaMax = (int32_t) std::strtol(values[142].c_str(), nullptr, 10); }
    if (values.size() > 143) { JamellaMagicMin = (int32_t) std::strtol(values[143].c_str(), nullptr, 10); }
    if (values.size() > 144) { JamellaMagicMax = (int32_t) std::strtol(values[144].c_str(), nullptr, 10); }
    if (values.size() > 145) { JamellaMagicLvl = (int32_t) std::strtol(values[145].c_str(), nullptr, 10); }
    if (values.size() > 146) { LarzukMin = (int32_t) std::strtol(values[146].c_str(), nullptr, 10); }
    if (values.size() > 147) { LarzukMax = (int32_t) std::strtol(values[147].c_str(), nullptr, 10); }
    if (values.size() > 148) { LarzukMagicMin = (int32_t) std::strtol(values[148].c_str(), nullptr, 10); }
    if (values.size() > 149) { LarzukMagicMax = (int32_t) std::strtol(values[149].c_str(), nullptr, 10); }
    if (values.size() > 150) { LarzukMagicLvl = (int32_t) std::strtol(values[150].c_str(), nullptr, 10); }
    if (values.size() > 151) { AnyaMin = (int32_t) std::strtol(values[151].c_str(), nullptr, 10); }
    if (values.size() > 152) { AnyaMax = (int32_t) std::strtol(values[152].c_str(), nullptr, 10); }
    if (values.size() > 153) { AnyaMagicMin = (int32_t) std::strtol(values[153].c_str(), nullptr, 10); }
    if (values.size() > 154) { AnyaMagicMax = (int32_t) std::strtol(values[154].c_str(), nullptr, 10); }
    if (values.size() > 155) { AnyaMagicLvl = (int32_t) std::strtol(values[155].c_str(), nullptr, 10); }
    if (values.size() > 156) { MalahMin = (int32_t) std::strtol(values[156].c_str(), nullptr, 10); }
    if (values.size() > 157) { MalahMax = (int32_t) std::strtol(values[157].c_str(), nullptr, 10); }
    if (values.size() > 158) { MalahMagicMin = (int32_t) std::strtol(values[158].c_str(), nullptr, 10); }
    if (values.size() > 159) { MalahMagicMax = (int32_t) std::strtol(values[159].c_str(), nullptr, 10); }
    if (values.size() > 160) { MalahMagicLvl = (int32_t) std::strtol(values[160].c_str(), nullptr, 10); }
    if (values.size() > 161) { Transform = (int32_t) std::strtol(values[161].c_str(), nullptr, 10); }
    if (values.size() > 162) { InvTrans = (int32_t) std::strtol(values[162].c_str(), nullptr, 10); }
    if (values.size() > 163) { SkipName = (int32_t) std::strtol(values[163].c_str(), nullptr, 10); }
    if (values.size() > 164) { NightmareUpgrade = values[164]; }
    if (values.size() > 165) { HellUpgrade = values[165]; }
    if (values.size() > 166) { Nameable = (int32_t) std::strtol(values[166].c_str(), nullptr, 10); }
    if (values.size() > 167) { PermStoreItem = (int32_t) std::strtol(values[167].c_str(), nullptr, 10); }

    return values.size();
  }

  std::vector<t_weapons> t_weapons::readfile(std::string filename) {
    std::vector<t_weapons> ret;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return ret; // Return empty vector if file cannot be opened
    }

    std::string line;
    if (!std::getline(file, line)) {
      return ret; // Return empty vector if file is empty
    }
    while (std::getline(file, line)) {
      t_weapons v;
      v.read(line.c_str());
      ret.push_back(v);
    }

    return ret;
  }

}
