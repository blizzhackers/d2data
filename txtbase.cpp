#include "txtbase.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace D2::BASE {

  size_t t_actinfo::read(const char* line) {
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { act = values[0][0] == '\0' ? 0 : std::stoi(values[0]); }
    if (values.size() > 1) { town = values[1]; }
    if (values.size() > 2) { start = values[2]; }
    if (values.size() > 3) { maxnpcitemlevel = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { classlevelrangestart = values[4]; }
    if (values.size() > 5) { classlevelrangeend = values[5]; }
    if (values.size() > 6) { wanderingnpcstart = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { wanderingnpcrange = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
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
    if (values.size() > 18) { wanderingMonsterPopulateChance = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { wanderingMonsterRegionTotal = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { wanderingPopulateRandomChance = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { version = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { compactsave = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { rarity = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { spawnable = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 6) { minac = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { maxac = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { speed = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { reqstr = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { reqdex = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { block = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { durability = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { nodurability = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { level = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { ShowLevel = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { levelreq = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { cost = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { gamblecost = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { code = values[19]; }
    if (values.size() > 20) { namestr = values[20]; }
    if (values.size() > 21) { magiclvl = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { autoprefix = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { alternategfx = values[23]; }
    if (values.size() > 24) { normcode = values[24]; }
    if (values.size() > 25) { ubercode = values[25]; }
    if (values.size() > 26) { ultracode = values[26]; }
    if (values.size() > 27) { component = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { invwidth = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { invheight = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { hasinv = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { gemsockets = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { gemapplytype = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { flippyfile = values[33]; }
    if (values.size() > 34) { invfile = values[34]; }
    if (values.size() > 35) { uniqueinvfile = values[35]; }
    if (values.size() > 36) { setinvfile = values[36]; }
    if (values.size() > 37) { rArm = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { lArm = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { Torso = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { Legs = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { rSPad = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { lSPad = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { useable = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 48) { Transmogrify = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { TMogType = values[49]; }
    if (values.size() > 52) { type = values[52]; }
    if (values.size() > 54) { dropsound = values[54]; }
    if (values.size() > 55) { dropsfxframe = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { usesound = values[56]; }
    if (values.size() > 57) { unique = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { transparent = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { transtbl = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { quivered = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { lightradius = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { belt = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 65) { missiletype = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { durwarning = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { qntwarning = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { mindam = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { maxdam = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { StrBonus = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 72) { gemoffset = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { bitfield1 = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { CharsiMin = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { CharsiMax = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
    if (values.size() > 76) { CharsiMagicMin = values[76][0] == '\0' ? 0 : std::stoi(values[76]); }
    if (values.size() > 77) { CharsiMagicMax = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { CharsiMagicLvl = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 79) { GheedMin = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 80) { GheedMax = values[80][0] == '\0' ? 0 : std::stoi(values[80]); }
    if (values.size() > 82) { GheedMagicMax = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }
    if (values.size() > 83) { GheedMagicLvl = values[83][0] == '\0' ? 0 : std::stoi(values[83]); }
    if (values.size() > 88) { AkaraMagicLvl = values[88][0] == '\0' ? 0 : std::stoi(values[88]); }
    if (values.size() > 89) { FaraMin = values[89][0] == '\0' ? 0 : std::stoi(values[89]); }
    if (values.size() > 90) { FaraMax = values[90][0] == '\0' ? 0 : std::stoi(values[90]); }
    if (values.size() > 91) { FaraMagicMin = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }
    if (values.size() > 92) { FaraMagicMax = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { FaraMagicLvl = values[93][0] == '\0' ? 0 : std::stoi(values[93]); }
    if (values.size() > 98) { LysanderMagicLvl = values[98][0] == '\0' ? 0 : std::stoi(values[98]); }
    if (values.size() > 99) { DrognanMin = values[99][0] == '\0' ? 0 : std::stoi(values[99]); }
    if (values.size() > 100) { DrognanMax = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
    if (values.size() > 101) { DrognanMagicMin = values[101][0] == '\0' ? 0 : std::stoi(values[101]); }
    if (values.size() > 102) { DrognanMagicMax = values[102][0] == '\0' ? 0 : std::stoi(values[102]); }
    if (values.size() > 103) { DrognanMagicLvl = values[103][0] == '\0' ? 0 : std::stoi(values[103]); }
    if (values.size() > 104) { HratliMin = values[104][0] == '\0' ? 0 : std::stoi(values[104]); }
    if (values.size() > 105) { HratliMax = values[105][0] == '\0' ? 0 : std::stoi(values[105]); }
    if (values.size() > 106) { HratliMagicMin = values[106][0] == '\0' ? 0 : std::stoi(values[106]); }
    if (values.size() > 107) { HratliMagicMax = values[107][0] == '\0' ? 0 : std::stoi(values[107]); }
    if (values.size() > 108) { HratliMagicLvl = values[108][0] == '\0' ? 0 : std::stoi(values[108]); }
    if (values.size() > 113) { AlkorMagicLvl = values[113][0] == '\0' ? 0 : std::stoi(values[113]); }
    if (values.size() > 115) { OrmusMax = values[115][0] == '\0' ? 0 : std::stoi(values[115]); }
    if (values.size() > 117) { OrmusMagicMax = values[117][0] == '\0' ? 0 : std::stoi(values[117]); }
    if (values.size() > 118) { OrmusMagicLvl = values[118][0] == '\0' ? 0 : std::stoi(values[118]); }
    if (values.size() > 119) { ElzixMin = values[119][0] == '\0' ? 0 : std::stoi(values[119]); }
    if (values.size() > 120) { ElzixMax = values[120][0] == '\0' ? 0 : std::stoi(values[120]); }
    if (values.size() > 121) { ElzixMagicMin = values[121][0] == '\0' ? 0 : std::stoi(values[121]); }
    if (values.size() > 122) { ElzixMagicMax = values[122][0] == '\0' ? 0 : std::stoi(values[122]); }
    if (values.size() > 123) { ElzixMagicLvl = values[123][0] == '\0' ? 0 : std::stoi(values[123]); }
    if (values.size() > 124) { AshearaMin = values[124][0] == '\0' ? 0 : std::stoi(values[124]); }
    if (values.size() > 125) { AshearaMax = values[125][0] == '\0' ? 0 : std::stoi(values[125]); }
    if (values.size() > 126) { AshearaMagicMin = values[126][0] == '\0' ? 0 : std::stoi(values[126]); }
    if (values.size() > 127) { AshearaMagicMax = values[127][0] == '\0' ? 0 : std::stoi(values[127]); }
    if (values.size() > 128) { AshearaMagicLvl = values[128][0] == '\0' ? 0 : std::stoi(values[128]); }
    if (values.size() > 129) { CainMin = values[129][0] == '\0' ? 0 : std::stoi(values[129]); }
    if (values.size() > 130) { CainMax = values[130][0] == '\0' ? 0 : std::stoi(values[130]); }
    if (values.size() > 131) { CainMagicMin = values[131][0] == '\0' ? 0 : std::stoi(values[131]); }
    if (values.size() > 132) { CainMagicMax = values[132][0] == '\0' ? 0 : std::stoi(values[132]); }
    if (values.size() > 133) { CainMagicLvl = values[133][0] == '\0' ? 0 : std::stoi(values[133]); }
    if (values.size() > 134) { HalbuMin = values[134][0] == '\0' ? 0 : std::stoi(values[134]); }
    if (values.size() > 135) { HalbuMax = values[135][0] == '\0' ? 0 : std::stoi(values[135]); }
    if (values.size() > 136) { HalbuMagicMin = values[136][0] == '\0' ? 0 : std::stoi(values[136]); }
    if (values.size() > 137) { HalbuMagicMax = values[137][0] == '\0' ? 0 : std::stoi(values[137]); }
    if (values.size() > 138) { HalbuMagicLvl = values[138][0] == '\0' ? 0 : std::stoi(values[138]); }
    if (values.size() > 139) { JamellaMin = values[139][0] == '\0' ? 0 : std::stoi(values[139]); }
    if (values.size() > 140) { JamellaMax = values[140][0] == '\0' ? 0 : std::stoi(values[140]); }
    if (values.size() > 141) { JamellaMagicMin = values[141][0] == '\0' ? 0 : std::stoi(values[141]); }
    if (values.size() > 142) { JamellaMagicMax = values[142][0] == '\0' ? 0 : std::stoi(values[142]); }
    if (values.size() > 143) { JamellaMagicLvl = values[143][0] == '\0' ? 0 : std::stoi(values[143]); }
    if (values.size() > 144) { LarzukMin = values[144][0] == '\0' ? 0 : std::stoi(values[144]); }
    if (values.size() > 145) { LarzukMax = values[145][0] == '\0' ? 0 : std::stoi(values[145]); }
    if (values.size() > 146) { LarzukMagicMin = values[146][0] == '\0' ? 0 : std::stoi(values[146]); }
    if (values.size() > 147) { LarzukMagicMax = values[147][0] == '\0' ? 0 : std::stoi(values[147]); }
    if (values.size() > 148) { LarzukMagicLvl = values[148][0] == '\0' ? 0 : std::stoi(values[148]); }
    if (values.size() > 153) { MalahMagicLvl = values[153][0] == '\0' ? 0 : std::stoi(values[153]); }
    if (values.size() > 154) { AnyaMin = values[154][0] == '\0' ? 0 : std::stoi(values[154]); }
    if (values.size() > 155) { AnyaMax = values[155][0] == '\0' ? 0 : std::stoi(values[155]); }
    if (values.size() > 156) { AnyaMagicMin = values[156][0] == '\0' ? 0 : std::stoi(values[156]); }
    if (values.size() > 157) { AnyaMagicMax = values[157][0] == '\0' ? 0 : std::stoi(values[157]); }
    if (values.size() > 158) { AnyaMagicLvl = values[158][0] == '\0' ? 0 : std::stoi(values[158]); }
    if (values.size() > 159) { Transform = values[159][0] == '\0' ? 0 : std::stoi(values[159]); }
    if (values.size() > 160) { InvTrans = values[160][0] == '\0' ? 0 : std::stoi(values[160]); }
    if (values.size() > 161) { SkipName = values[161][0] == '\0' ? 0 : std::stoi(values[161]); }
    if (values.size() > 162) { NightmareUpgrade = values[162]; }
    if (values.size() > 163) { HellUpgrade = values[163]; }
    if (values.size() > 164) { Nameable = values[164][0] == '\0' ? 0 : std::stoi(values[164]); }
    if (values.size() > 165) { PermStoreItem = values[165][0] == '\0' ? 0 : std::stoi(values[165]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { version = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { spawnable = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { rare = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { level = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 6) { levelreq = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 10) { frequency = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { group = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { mod1code = values[12]; }
    if (values.size() > 13) { mod1param = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { mod1min = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { mod1max = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { mod2code = values[16]; }
    if (values.size() > 18) { mod2min = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { mod2max = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { mod3code = values[20]; }
    if (values.size() > 22) { mod3min = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { mod3max = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { transformcolor = values[24]; }
    if (values.size() > 25) { itype1 = values[25]; }
    if (values.size() > 26) { itype2 = values[26]; }
    if (values.size() > 37) { multiply = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { add = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { LevelName = values[0]; }
    if (values.size() > 1) { TileName = values[1]; }
    if (values.size() > 2) { Style = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { StartSequence = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { EndSequence = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Type1 = values[5]; }
    if (values.size() > 6) { Cel1 = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Type2 = values[7]; }
    if (values.size() > 8) { Cel2 = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { Type3 = values[9]; }
    if (values.size() > 10) { Cel3 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Type4 = values[11]; }
    if (values.size() > 12) { Cel4 = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { numboxes = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { box1left = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { box1right = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { box1top = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { box1bottom = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { box2left = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { box2right = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { box2top = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { box2bottom = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { box3left = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { box3right = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { box3top = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { box3bottom = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { box4left = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { box4right = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { box4top = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { box4bottom = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { box5left = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { box5right = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { box5top = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { box5bottom = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { box6left = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { box6right = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { box6top = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { box6bottom = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { box7left = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { box7right = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { box7top = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { box7bottom = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { box8left = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { box8right = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { box8top = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { box8bottom = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { box9left = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { box9right = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { box9top = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { box9bottom = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { box10left = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { box10right = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { box10top = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { box10bottom = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { box11left = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { box11right = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { box11top = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { box11bottom = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { box12left = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { box12right = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { box12top = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { box12bottom = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { box13left = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { box13right = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { box13top = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { box13bottom = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { box14left = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { box14right = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { box14top = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { box14bottom = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { box15left = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { box15right = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { box15top = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { box15bottom = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { box16left = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { box16right = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { box16top = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { box16bottom = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { ScrollSpellCode = values[1]; }
    if (values.size() > 2) { BookSpellCode = values[2]; }
    if (values.size() > 3) { pSpell = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { SpellIcon = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { ScrollSkill = values[5]; }
    if (values.size() > 6) { BookSkill = values[6]; }
    if (values.size() > 7) { BaseCost = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { CostPerCharge = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { _class = values[0]; }
    if (values.size() > 1) { str = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { dex = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { _int = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { vit = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { stamina = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { hpadd = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { ManaRegen = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { ToHitFactor = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { WalkVelocity = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { RunVelocity = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { RunDrain = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { Comment = values[12]; }
    if (values.size() > 13) { LifePerLevel = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { StaminaPerLevel = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { ManaPerLevel = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { LifePerVitality = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { StaminaPerVitality = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { ManaPerMagic = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { StatPerLevel = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { SkillsPerLevel = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { LightRadius = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { BlockFactor = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { MinimumCastingDelay = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
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
    if (values.size() > 40) { HealthPotionPercent = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { ManaPotionPercent = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { baseWClass = values[42]; }
    if (values.size() > 43) { item1 = values[43]; }
    if (values.size() > 44) { item1loc = values[44]; }
    if (values.size() > 45) { item1count = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { item1quality = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { item2 = values[47]; }
    if (values.size() > 48) { item2loc = values[48]; }
    if (values.size() > 49) { item2count = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { item2quality = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { item3 = values[51]; }
    if (values.size() > 53) { item3count = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { item3quality = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { item4 = values[55]; }
    if (values.size() > 57) { item4count = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { item4quality = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { item5 = values[59]; }
    if (values.size() > 61) { item5count = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { item5quality = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { item6 = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 65) { item6count = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { item6quality = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { item7 = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 69) { item7count = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { item7quality = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 71) { item8 = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 73) { item8count = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { item8quality = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { item9 = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
    if (values.size() > 77) { item9count = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { item9quality = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 79) { item10 = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 81) { item10count = values[81][0] == '\0' ? 0 : std::stoi(values[81]); }
    if (values.size() > 82) { item10quality = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { description = values[0]; }
    if (values.size() > 1) { enabled = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { firstLadderSeason = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { lastLadderSeason = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 5) { version = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { op = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 10) { numinputs = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { input1 = values[11]; }
    if (values.size() > 12) { input2 = values[12]; }
    if (values.size() > 13) { input3 = values[13]; }
    if (values.size() > 14) { input4 = values[14]; }
    if (values.size() > 15) { input5 = values[15]; }
    if (values.size() > 16) { input6 = values[16]; }
    if (values.size() > 17) { input7 = values[17]; }
    if (values.size() > 18) { output = values[18]; }
    if (values.size() > 19) { lvl = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { plvl = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { ilvl = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { mod1 = values[22]; }
    if (values.size() > 24) { mod1param = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { mod1min = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { mod1max = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { mod2 = values[27]; }
    if (values.size() > 30) { mod2min = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { mod2max = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { mod3 = values[32]; }
    if (values.size() > 35) { mod3min = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { mod3max = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { mod4 = values[37]; }
    if (values.size() > 40) { mod4min = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { mod4max = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 105) { eol = values[105][0] == '\0' ? 0 : std::stoi(values[105]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { ResistPenalty = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { ResistPenaltyNonExpansion = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { DeathExpPenalty = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { MonsterSkillBonus = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { MonsterFreezeDivisor = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { MonsterColdDivisor = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { AiCurseDivisor = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { LifeStealDivisor = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { ManaStealDivisor = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { UniqueDamageBonus = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { ChampionDamageBonus = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { PlayerDamagePercentVSPlayer = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { PlayerDamagePercentVSMercenary = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { PlayerDamagePercentVSPrimeEvil = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { PlayerHitReactBufferVSPlayer = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { PlayerHitReactBufferVSMonster = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { MercenaryDamagePercentVSPlayer = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { MercenaryDamagePercentVSMercenary = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { MercenaryDamagePercentVSBoss = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { MercenaryMaxStunLength = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { PrimeEvilDamagePercentVSPlayer = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { PrimeEvilDamagePercentVSMercenary = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { PrimeEvilDamagePercentVSPet = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { PetDamagePercentVSPlayer = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { MonsterCEDamagePercent = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { MonsterFireEnchantExplosionDamagePercent = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { StaticFieldMin = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { GambleRare = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { GambleSet = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { GambleUnique = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { GambleUber = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { GambleUltra = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Level = values[0]; }
    if (values.size() > 1) { Amazon = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Sorceress = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Necromancer = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Paladin = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Barbarian = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Druid = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Assassin = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 9) { ExpRatio = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { letter = values[1]; }
    if (values.size() > 2) { transform = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { code = values[3]; }
    if (values.size() > 4) { weaponMod1Code = values[4]; }
    if (values.size() > 5) { weaponMod1Param = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { weaponMod1Min = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { weaponMod1Max = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { weaponMod2Code = values[8]; }
    if (values.size() > 9) { weaponMod2Param = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { weaponMod2Min = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { weaponMod2Max = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { weaponMod3Code = values[12]; }
    if (values.size() > 13) { weaponMod3Param = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { weaponMod3Min = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { weaponMod3Max = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { helmMod1Code = values[16]; }
    if (values.size() > 17) { helmMod1Param = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { helmMod1Min = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { helmMod1Max = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { helmMod2Code = values[20]; }
    if (values.size() > 21) { helmMod2Param = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { helmMod2Min = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { helmMod2Max = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 25) { helmMod3Param = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { helmMod3Min = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { helmMod3Max = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { shieldMod1Code = values[28]; }
    if (values.size() > 29) { shieldMod1Param = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { shieldMod1Min = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { shieldMod1Max = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { shieldMod2Code = values[32]; }
    if (values.size() > 33) { shieldMod2Param = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { shieldMod2Min = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { shieldMod2Max = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 37) { shieldMod3Param = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { shieldMod3Min = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { shieldMod3Max = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Hireling = values[0]; }
    if (values.size() > 1) { SubType = values[1]; }
    if (values.size() > 2) { Version = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Id = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Class = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Act = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Difficulty = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Level = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { Seller = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { NameFirst = values[9]; }
    if (values.size() > 10) { NameLast = values[10]; }
    if (values.size() > 11) { Gold = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { ExpLvl = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { HP = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { HPLvl = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { Defense = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { DefLvl = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { Str = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { StrLvl = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { Dex = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { DexLvl = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { AR = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { ARLvl = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { DmgMin = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { DmgMax = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { DmgLvl = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { ResistFire = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { ResistFireLvl = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { ResistCold = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { ResistColdLvl = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { ResistLightning = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { ResistLightningLvl = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { ResistPoison = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { ResistPoisonLvl = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { HireDesc = values[34]; }
    if (values.size() > 35) { DefaultChance = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { Skill1 = values[36]; }
    if (values.size() > 37) { Mode1 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { Chance1 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { ChancePerLvl1 = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { Level1 = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { LvlPerLvl1 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { Skill2 = values[42]; }
    if (values.size() > 43) { Mode2 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { Chance2 = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { ChancePerLvl2 = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { Level2 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { LvlPerLvl2 = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { Skill3 = values[48]; }
    if (values.size() > 49) { Mode3 = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { Chance3 = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { ChancePerLvl3 = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { Level3 = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { LvlPerLvl3 = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 72) { HiringMaxLevelDifference = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { resurrectcostmultiplier = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { resurrectcostdivisor = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { resurrectcostmax = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { _class = values[0]; }
    if (values.size() > 1) { invLeft = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { invRight = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { invTop = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { invBottom = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { gridX = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { gridY = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { gridLeft = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { gridRight = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { gridTop = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { gridBottom = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { gridBoxWidth = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { gridBoxHeight = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { rArmLeft = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { rArmRight = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { rArmTop = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { rArmBottom = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { rArmWidth = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { rArmHeight = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { torsoLeft = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { torsoRight = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { torsoTop = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { torsoBottom = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { torsoWidth = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { torsoHeight = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { lArmLeft = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { lArmRight = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { lArmTop = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { lArmBottom = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { lArmWidth = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { lArmHeight = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { headLeft = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { headRight = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { headTop = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { headBottom = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { headWidth = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { headHeight = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { neckLeft = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { neckRight = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { neckTop = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { neckBottom = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { neckWidth = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { neckHeight = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { rHandLeft = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { rHandRight = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { rHandTop = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { rHandBottom = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { rHandWidth = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { rHandHeight = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { lHandLeft = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { lHandRight = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { lHandTop = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { lHandBottom = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { lHandWidth = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { lHandHeight = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { beltLeft = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { beltRight = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { beltTop = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { beltBottom = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { beltWidth = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { beltHeight = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { feetLeft = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { feetRight = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { feetTop = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { feetBottom = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { feetWidth = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { feetHeight = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { glovesLeft = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { glovesRight = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { glovesTop = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { glovesBottom = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 71) { glovesWidth = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { glovesHeight = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Function = values[0]; }
    if (values.size() > 1) { Version = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Uber = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { ClassSpecific = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Unique = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { UniqueDivisor = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { UniqueMin = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Rare = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { RareDivisor = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { RareMin = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { Set = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { SetDivisor = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { SetMin = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Magic = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { MagicDivisor = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { MagicMin = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { HiQuality = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { HiQualityDivisor = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { Normal = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { NormalDivisor = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Stat = values[0]; }
    if (values.size() > 1) { ID = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { SendOther = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Signed = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { SendBits = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { SendParamBits = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { UpdateAnimRate = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Saved = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { CSvSigned = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { CSvBits = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 11) { fCallback = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { fMin = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { MinAccr = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { Encode = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { Add = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { Multiply = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { ValShift = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { _109SaveBits = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { _109SaveAdd = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { SaveBits = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { SaveAdd = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { SaveParamBits = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { keepzero = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { op = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { opparam = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { opbase = values[26]; }
    if (values.size() > 27) { opstat1 = values[27]; }
    if (values.size() > 28) { opstat2 = values[28]; }
    if (values.size() > 29) { opstat3 = values[29]; }
    if (values.size() > 30) { direct = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { maxstat = values[31]; }
    if (values.size() > 32) { damagerelated = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { itemevent1 = values[33]; }
    if (values.size() > 34) { itemeventfunc1 = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { itemevent2 = values[35]; }
    if (values.size() > 36) { itemeventfunc2 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { descpriority = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { descfunc = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { descval = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { descstrpos = values[40]; }
    if (values.size() > 41) { descstrneg = values[41]; }
    if (values.size() > 42) { descstr2 = values[42]; }
    if (values.size() > 43) { dgrp = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { dgrpfunc = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 46) { dgrpstrpos = values[46]; }
    if (values.size() > 47) { dgrpstrneg = values[47]; }
    if (values.size() > 49) { stuff = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { advdisplay = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { eol = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { ItemType = values[0]; }
    if (values.size() > 1) { Code = values[1]; }
    if (values.size() > 2) { Equiv1 = values[2]; }
    if (values.size() > 3) { Equiv2 = values[3]; }
    if (values.size() > 4) { Repair = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Body = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { BodyLoc1 = values[6]; }
    if (values.size() > 7) { BodyLoc2 = values[7]; }
    if (values.size() > 8) { Shoots = values[8]; }
    if (values.size() > 9) { Quiver = values[9]; }
    if (values.size() > 10) { Throwable = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Reload = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { ReEquip = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { AutoStack = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { Magic = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { Rare = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { Normal = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { Beltable = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { MaxSockets1 = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { MaxSocketsLevelThreshold1 = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { MaxSockets2 = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { MaxSocketsLevelThreshold2 = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { MaxSockets3 = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { TreasureClass = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { Rarity = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { StaffMods = values[25]; }
    if (values.size() > 26) { Class = values[26]; }
    if (values.size() > 27) { VarInvGfx = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { InvGfx1 = values[28]; }
    if (values.size() > 29) { InvGfx2 = values[29]; }
    if (values.size() > 30) { InvGfx3 = values[30]; }
    if (values.size() > 31) { InvGfx4 = values[31]; }
    if (values.size() > 32) { InvGfx5 = values[32]; }
    if (values.size() > 33) { InvGfx6 = values[33]; }
    if (values.size() > 34) { StorePage = values[34]; }
    if (values.size() > 35) { eol = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { UICategory = values[36]; }
    if (values.size() > 37) { RunewordCategory1 = values[37]; }
    if (values.size() > 38) { RunewordCategory2 = values[38]; }
    if (values.size() > 39) { Restricted = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { isEquipment = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { ParentCategory = values[2]; }
    if (values.size() > 3) { QualityFilter = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { NumColumns = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { LevelGroupId = values[0]; }
    if (values.size() > 1) { ParentLevelGroupId = values[1]; }
    if (values.size() > 2) { CompleteThreshold = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Effect = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { StringName = values[1]; }
    if (values.size() > 2) { Id = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Pal = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Act = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { QuestFlag = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { QuestFlagEx = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Layer = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { SizeX = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { SizeY = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { SizeXN = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { SizeYN = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { SizeXH = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { SizeYH = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { OffsetX = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { OffsetY = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { Depend = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { Teleport = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { Rain = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { Mud = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { NoPer = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { LOSDraw = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { FloorFilter = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { BlankScreen = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { DrawEdges = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { IsInside = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { DrlgType = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { LevelType = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { SubType = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { SubTheme = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { SubWaypoint = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { SubShrine = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { Vis0 = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { Vis1 = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { Vis2 = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { Vis3 = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { Vis4 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { Vis5 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { Vis6 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { Vis7 = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { Warp0 = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { Warp1 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { Warp2 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { Warp3 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { Warp4 = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { Warp5 = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { Warp6 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { Warp7 = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { Intensity = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { Red = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { Green = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { Blue = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { Portal = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { Position = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { SaveMonsters = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { Quest = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { WarpDist = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { MonLvl = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { MonLvlN = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { MonLvlH = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { MonLvlEx = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { MonLvlExN = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { MonLvlExH = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { MonDen = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { MonDenN = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { MonDenH = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { MonUMin = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { MonUMax = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { MonUMinN = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { MonUMaxN = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { MonUMinH = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 71) { MonUMaxH = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { MonWndr = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { MonSpcWalk = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { NumMon = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { mon1 = values[75]; }
    if (values.size() > 76) { mon2 = values[76]; }
    if (values.size() > 77) { mon3 = values[77]; }
    if (values.size() > 78) { mon4 = values[78]; }
    if (values.size() > 79) { mon5 = values[79]; }
    if (values.size() > 80) { mon6 = values[80]; }
    if (values.size() > 81) { mon7 = values[81]; }
    if (values.size() > 82) { mon8 = values[82]; }
    if (values.size() > 100) { rangedspawn = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
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
    if (values.size() > 155) { cpct1 = values[155][0] == '\0' ? 0 : std::stoi(values[155]); }
    if (values.size() > 156) { cpct2 = values[156][0] == '\0' ? 0 : std::stoi(values[156]); }
    if (values.size() > 157) { cpct3 = values[157][0] == '\0' ? 0 : std::stoi(values[157]); }
    if (values.size() > 158) { cpct4 = values[158][0] == '\0' ? 0 : std::stoi(values[158]); }
    if (values.size() > 163) { Themes = values[163][0] == '\0' ? 0 : std::stoi(values[163]); }
    if (values.size() > 164) { SoundEnv = values[164][0] == '\0' ? 0 : std::stoi(values[164]); }
    if (values.size() > 165) { Waypoint = values[165][0] == '\0' ? 0 : std::stoi(values[165]); }
    if (values.size() > 166) { LevelName = values[166]; }
    if (values.size() > 167) { LevelWarp = values[167]; }
    if (values.size() > 168) { LevelEntry = values[168]; }
    if (values.size() > 169) { ObjGrp0 = values[169][0] == '\0' ? 0 : std::stoi(values[169]); }
    if (values.size() > 170) { ObjGrp1 = values[170][0] == '\0' ? 0 : std::stoi(values[170]); }
    if (values.size() > 171) { ObjGrp2 = values[171][0] == '\0' ? 0 : std::stoi(values[171]); }
    if (values.size() > 172) { ObjGrp3 = values[172][0] == '\0' ? 0 : std::stoi(values[172]); }
    if (values.size() > 173) { ObjGrp4 = values[173][0] == '\0' ? 0 : std::stoi(values[173]); }
    if (values.size() > 174) { ObjGrp5 = values[174][0] == '\0' ? 0 : std::stoi(values[174]); }
    if (values.size() > 175) { ObjGrp6 = values[175][0] == '\0' ? 0 : std::stoi(values[175]); }
    if (values.size() > 176) { ObjGrp7 = values[176][0] == '\0' ? 0 : std::stoi(values[176]); }
    if (values.size() > 177) { ObjPrb0 = values[177][0] == '\0' ? 0 : std::stoi(values[177]); }
    if (values.size() > 178) { ObjPrb1 = values[178][0] == '\0' ? 0 : std::stoi(values[178]); }
    if (values.size() > 179) { ObjPrb2 = values[179][0] == '\0' ? 0 : std::stoi(values[179]); }
    if (values.size() > 180) { ObjPrb3 = values[180][0] == '\0' ? 0 : std::stoi(values[180]); }
    if (values.size() > 181) { ObjPrb4 = values[181][0] == '\0' ? 0 : std::stoi(values[181]); }
    if (values.size() > 182) { ObjPrb5 = values[182][0] == '\0' ? 0 : std::stoi(values[182]); }
    if (values.size() > 183) { ObjPrb6 = values[183][0] == '\0' ? 0 : std::stoi(values[183]); }
    if (values.size() > 184) { ObjPrb7 = values[184][0] == '\0' ? 0 : std::stoi(values[184]); }
    if (values.size() > 185) { LevelGroup = values[185]; }
    if (values.size() > 186) { PreventTownPortal = values[186][0] == '\0' ? 0 : std::stoi(values[186]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Level = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Rooms = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { RoomsN = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { RoomsH = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { SizeX = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { SizeY = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Merge = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Def = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { LevelId = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Populate = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Logicals = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Outdoors = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Animate = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { KillEdge = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { FillBlanks = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { SizeX = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { SizeY = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { AutoMap = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { Scan = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Pops = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { PopPad = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { Files = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { File1 = values[16]; }
    if (values.size() > 17) { File2 = values[17]; }
    if (values.size() > 18) { File3 = values[18]; }
    if (values.size() > 19) { File4 = values[19]; }
    if (values.size() > 20) { File5 = values[20]; }
    if (values.size() > 21) { File6 = values[21]; }
    if (values.size() > 22) { Dt1Mask = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Type = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { File = values[2]; }
    if (values.size() > 3) { CheckAll = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { BordType = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { GridSize = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Dt1Mask = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Prob0 = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { Trials0 = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { Max0 = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { Prob1 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Trials1 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { Max1 = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Prob2 = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { Trials2 = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { Max2 = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { Prob3 = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { Trials3 = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { Max3 = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { Prob4 = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { Trials4 = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { Max4 = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Id = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
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
    if (values.size() > 33) { File32 = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { Act = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { Id = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { SelectX = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { SelectY = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { SelectDX = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { SelectDY = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { ExitWalkX = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { ExitWalkY = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { OffsetX = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { OffsetY = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { LitVersion = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Tiles = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { NoInteract = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Direction = values[13]; }
    if (values.size() > 14) { UniqueId = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { version = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { spawnable = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { rare = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { level = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { maxlevel = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { levelreq = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { classspecific = values[7]; }
    if (values.size() > 10) { frequency = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { group = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { mod1code = values[12]; }
    if (values.size() > 13) { mod1param = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { mod1min = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { mod1max = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { mod2code = values[16]; }
    if (values.size() > 17) { mod2param = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { mod2min = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { mod2max = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { mod3code = values[20]; }
    if (values.size() > 22) { mod3min = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { mod3max = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
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
    if (values.size() > 37) { multiply = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { add = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { version = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { spawnable = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { rare = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { level = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { maxlevel = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { levelreq = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 8) { _class = values[8]; }
    if (values.size() > 9) { classlevelreq = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { frequency = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { group = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { mod1code = values[12]; }
    if (values.size() > 13) { mod1param = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { mod1min = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { mod1max = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { mod2code = values[16]; }
    if (values.size() > 17) { mod2param = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { mod2min = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { mod2max = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { mod3code = values[20]; }
    if (values.size() > 21) { mod3param = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { mod3min = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { mod3max = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
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
    if (values.size() > 35) { etype4 = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { etype5 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { multiply = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { add = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { compactsave = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { version = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { level = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { ShowLevel = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { levelreq = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 8) { rarity = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { spawnable = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 11) { speed = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { nodurability = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { cost = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { gamblecost = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { code = values[15]; }
    if (values.size() > 16) { alternategfx = values[16]; }
    if (values.size() > 17) { namestr = values[17]; }
    if (values.size() > 18) { component = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { invwidth = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { invheight = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { hasinv = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { gemsockets = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { gemapplytype = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { flippyfile = values[24]; }
    if (values.size() > 25) { invfile = values[25]; }
    if (values.size() > 26) { uniqueinvfile = values[26]; }
    if (values.size() > 27) { Transmogrify = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { TMogType = values[28]; }
    if (values.size() > 29) { TMogMin = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { TMogMax = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { useable = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { type = values[32]; }
    if (values.size() > 33) { type2 = values[33]; }
    if (values.size() > 34) { dropsound = values[34]; }
    if (values.size() > 35) { dropsfxframe = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { usesound = values[36]; }
    if (values.size() > 37) { unique = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { transparent = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { transtbl = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { lightradius = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { belt = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { autobelt = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { stackable = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { minstack = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { maxstack = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { spawnstack = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { quest = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { questdiffcheck = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { missiletype = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { spellicon = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { pSpell = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { state = values[52]; }
    if (values.size() > 53) { cstate1 = values[53]; }
    if (values.size() > 54) { cstate2 = values[54]; }
    if (values.size() > 55) { len = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { stat1 = values[56]; }
    if (values.size() > 57) { calc1 = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { stat2 = values[58]; }
    if (values.size() > 59) { calc2 = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 62) { spelldesc = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { spelldescstr = values[63]; }
    if (values.size() > 64) { spelldescstr2 = values[64]; }
    if (values.size() > 65) { spelldesccalc = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { spelldesccolor = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { durwarning = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { qntwarning = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { gemoffset = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { BetterGem = values[70]; }
    if (values.size() > 71) { bitfield1 = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { CharsiMin = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { CharsiMax = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 76) { CharsiMagicLvl = values[76][0] == '\0' ? 0 : std::stoi(values[76]); }
    if (values.size() > 77) { GheedMin = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { GheedMax = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 79) { GheedMagicMin = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 80) { GheedMagicMax = values[80][0] == '\0' ? 0 : std::stoi(values[80]); }
    if (values.size() > 81) { GheedMagicLvl = values[81][0] == '\0' ? 0 : std::stoi(values[81]); }
    if (values.size() > 82) { AkaraMin = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }
    if (values.size() > 83) { AkaraMax = values[83][0] == '\0' ? 0 : std::stoi(values[83]); }
    if (values.size() > 84) { AkaraMagicMin = values[84][0] == '\0' ? 0 : std::stoi(values[84]); }
    if (values.size() > 85) { AkaraMagicMax = values[85][0] == '\0' ? 0 : std::stoi(values[85]); }
    if (values.size() > 86) { AkaraMagicLvl = values[86][0] == '\0' ? 0 : std::stoi(values[86]); }
    if (values.size() > 87) { FaraMin = values[87][0] == '\0' ? 0 : std::stoi(values[87]); }
    if (values.size() > 88) { FaraMax = values[88][0] == '\0' ? 0 : std::stoi(values[88]); }
    if (values.size() > 89) { FaraMagicMin = values[89][0] == '\0' ? 0 : std::stoi(values[89]); }
    if (values.size() > 90) { FaraMagicMax = values[90][0] == '\0' ? 0 : std::stoi(values[90]); }
    if (values.size() > 91) { FaraMagicLvl = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }
    if (values.size() > 92) { LysanderMin = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { LysanderMax = values[93][0] == '\0' ? 0 : std::stoi(values[93]); }
    if (values.size() > 94) { LysanderMagicMin = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 95) { LysanderMagicMax = values[95][0] == '\0' ? 0 : std::stoi(values[95]); }
    if (values.size() > 96) { LysanderMagicLvl = values[96][0] == '\0' ? 0 : std::stoi(values[96]); }
    if (values.size() > 97) { DrognanMin = values[97][0] == '\0' ? 0 : std::stoi(values[97]); }
    if (values.size() > 98) { DrognanMax = values[98][0] == '\0' ? 0 : std::stoi(values[98]); }
    if (values.size() > 99) { DrognanMagicMin = values[99][0] == '\0' ? 0 : std::stoi(values[99]); }
    if (values.size() > 100) { DrognanMagicMax = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
    if (values.size() > 101) { DrognanMagicLvl = values[101][0] == '\0' ? 0 : std::stoi(values[101]); }
    if (values.size() > 102) { HratliMin = values[102][0] == '\0' ? 0 : std::stoi(values[102]); }
    if (values.size() > 103) { HratliMax = values[103][0] == '\0' ? 0 : std::stoi(values[103]); }
    if (values.size() > 104) { HratliMagicMin = values[104][0] == '\0' ? 0 : std::stoi(values[104]); }
    if (values.size() > 105) { HratliMagicMax = values[105][0] == '\0' ? 0 : std::stoi(values[105]); }
    if (values.size() > 106) { HratliMagicLvl = values[106][0] == '\0' ? 0 : std::stoi(values[106]); }
    if (values.size() > 107) { AlkorMin = values[107][0] == '\0' ? 0 : std::stoi(values[107]); }
    if (values.size() > 108) { AlkorMax = values[108][0] == '\0' ? 0 : std::stoi(values[108]); }
    if (values.size() > 111) { AlkorMagicLvl = values[111][0] == '\0' ? 0 : std::stoi(values[111]); }
    if (values.size() > 112) { OrmusMin = values[112][0] == '\0' ? 0 : std::stoi(values[112]); }
    if (values.size() > 113) { OrmusMax = values[113][0] == '\0' ? 0 : std::stoi(values[113]); }
    if (values.size() > 114) { OrmusMagicMin = values[114][0] == '\0' ? 0 : std::stoi(values[114]); }
    if (values.size() > 115) { OrmusMagicMax = values[115][0] == '\0' ? 0 : std::stoi(values[115]); }
    if (values.size() > 116) { OrmusMagicLvl = values[116][0] == '\0' ? 0 : std::stoi(values[116]); }
    if (values.size() > 117) { ElzixMin = values[117][0] == '\0' ? 0 : std::stoi(values[117]); }
    if (values.size() > 118) { ElzixMax = values[118][0] == '\0' ? 0 : std::stoi(values[118]); }
    if (values.size() > 121) { ElzixMagicLvl = values[121][0] == '\0' ? 0 : std::stoi(values[121]); }
    if (values.size() > 122) { AshearaMin = values[122][0] == '\0' ? 0 : std::stoi(values[122]); }
    if (values.size() > 123) { AshearaMax = values[123][0] == '\0' ? 0 : std::stoi(values[123]); }
    if (values.size() > 126) { AshearaMagicLvl = values[126][0] == '\0' ? 0 : std::stoi(values[126]); }
    if (values.size() > 127) { CainMin = values[127][0] == '\0' ? 0 : std::stoi(values[127]); }
    if (values.size() > 128) { CainMax = values[128][0] == '\0' ? 0 : std::stoi(values[128]); }
    if (values.size() > 131) { CainMagicLvl = values[131][0] == '\0' ? 0 : std::stoi(values[131]); }
    if (values.size() > 132) { HalbuMin = values[132][0] == '\0' ? 0 : std::stoi(values[132]); }
    if (values.size() > 133) { HalbuMax = values[133][0] == '\0' ? 0 : std::stoi(values[133]); }
    if (values.size() > 136) { HalbuMagicLvl = values[136][0] == '\0' ? 0 : std::stoi(values[136]); }
    if (values.size() > 137) { MalahMin = values[137][0] == '\0' ? 0 : std::stoi(values[137]); }
    if (values.size() > 138) { MalahMax = values[138][0] == '\0' ? 0 : std::stoi(values[138]); }
    if (values.size() > 141) { MalahMagicLvl = values[141][0] == '\0' ? 0 : std::stoi(values[141]); }
    if (values.size() > 142) { LarzukMin = values[142][0] == '\0' ? 0 : std::stoi(values[142]); }
    if (values.size() > 143) { LarzukMax = values[143][0] == '\0' ? 0 : std::stoi(values[143]); }
    if (values.size() > 146) { LarzukMagicLvl = values[146][0] == '\0' ? 0 : std::stoi(values[146]); }
    if (values.size() > 147) { AnyaMin = values[147][0] == '\0' ? 0 : std::stoi(values[147]); }
    if (values.size() > 148) { AnyaMax = values[148][0] == '\0' ? 0 : std::stoi(values[148]); }
    if (values.size() > 151) { AnyaMagicLvl = values[151][0] == '\0' ? 0 : std::stoi(values[151]); }
    if (values.size() > 152) { JamellaMin = values[152][0] == '\0' ? 0 : std::stoi(values[152]); }
    if (values.size() > 153) { JamellaMax = values[153][0] == '\0' ? 0 : std::stoi(values[153]); }
    if (values.size() > 154) { JamellaMagicMin = values[154][0] == '\0' ? 0 : std::stoi(values[154]); }
    if (values.size() > 155) { JamellaMagicMax = values[155][0] == '\0' ? 0 : std::stoi(values[155]); }
    if (values.size() > 156) { JamellaMagicLvl = values[156][0] == '\0' ? 0 : std::stoi(values[156]); }
    if (values.size() > 157) { Transform = values[157][0] == '\0' ? 0 : std::stoi(values[157]); }
    if (values.size() > 158) { InvTrans = values[158][0] == '\0' ? 0 : std::stoi(values[158]); }
    if (values.size() > 159) { SkipName = values[159][0] == '\0' ? 0 : std::stoi(values[159]); }
    if (values.size() > 160) { NightmareUpgrade = values[160]; }
    if (values.size() > 161) { HellUpgrade = values[161]; }
    if (values.size() > 164) { PermStoreItem = values[164][0] == '\0' ? 0 : std::stoi(values[164]); }
    if (values.size() > 165) { multibuy = values[165][0] == '\0' ? 0 : std::stoi(values[165]); }
    if (values.size() > 167) { EventItem = values[167][0] == '\0' ? 0 : std::stoi(values[167]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Missile = values[0]; }
    if (values.size() > 1) { ID = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { pCltDoFunc = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { pCltHitFunc = values[3]; }
    if (values.size() > 4) { pSrvDoFunc = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { pSrvHitFunc = values[5]; }
    if (values.size() > 6) { pSrvDmgFunc = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { SrvCalc1 = values[7]; }
    if (values.size() > 8) { srvcalc1desc = values[8]; }
    if (values.size() > 9) { Param1 = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { param1desc = values[10]; }
    if (values.size() > 11) { Param2 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { param2desc = values[12]; }
    if (values.size() > 13) { Param3 = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { param3desc = values[14]; }
    if (values.size() > 15) { Param4 = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { param4desc = values[16]; }
    if (values.size() > 17) { Param5 = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { param5desc = values[18]; }
    if (values.size() > 19) { CltCalc1 = values[19]; }
    if (values.size() > 20) { clientcalc1desc = values[20]; }
    if (values.size() > 21) { CltParam1 = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { clientparam1desc = values[22]; }
    if (values.size() > 23) { CltParam2 = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { clientparam2desc = values[24]; }
    if (values.size() > 25) { CltParam3 = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { clientparam3desc = values[26]; }
    if (values.size() > 27) { CltParam4 = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { clientparam4desc = values[28]; }
    if (values.size() > 29) { CltParam5 = values[29]; }
    if (values.size() > 30) { clientparam5desc = values[30]; }
    if (values.size() > 31) { SHitCalc1 = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { serverhitcalc1desc = values[32]; }
    if (values.size() > 33) { sHitPar1 = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { serverhitparam1desc = values[34]; }
    if (values.size() > 35) { sHitPar2 = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { serverhitparam2desc = values[36]; }
    if (values.size() > 37) { sHitPar3 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { serverhitparam3desc = values[38]; }
    if (values.size() > 41) { cHitPar1 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { clienthitparam1desc = values[42]; }
    if (values.size() > 43) { cHitPar2 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { clienthitparam2desc = values[44]; }
    if (values.size() > 45) { cHitPar3 = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { clienthitparam3desc = values[46]; }
    if (values.size() > 47) { DmgCalc1 = values[47]; }
    if (values.size() > 48) { damagecalc1 = values[48]; }
    if (values.size() > 49) { dParam1 = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { damageparam1desc = values[50]; }
    if (values.size() > 51) { dParam2 = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { damageparam2desc = values[52]; }
    if (values.size() > 53) { Vel = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { MaxVel = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { VelLev = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { Accel = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { Range = values[57]; }
    if (values.size() > 59) { Light = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { Flicker = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { Red = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { Green = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { Blue = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { InitSteps = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { Activate = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { LoopAnim = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { CelFile = values[67]; }
    if (values.size() > 68) { animrate = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { AnimLen = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { AnimSpeed = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 71) { RandStart = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { SubLoop = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { SubStart = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { SubStop = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { CollideType = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
    if (values.size() > 76) { CollideKill = values[76][0] == '\0' ? 0 : std::stoi(values[76]); }
    if (values.size() > 77) { CollideFriend = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { LastCollide = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 79) { Collision = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 80) { ClientCol = values[80][0] == '\0' ? 0 : std::stoi(values[80]); }
    if (values.size() > 82) { ClientSend = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }
    if (values.size() > 83) { NextHit = values[83][0] == '\0' ? 0 : std::stoi(values[83]); }
    if (values.size() > 84) { NextDelay = values[84][0] == '\0' ? 0 : std::stoi(values[84]); }
    if (values.size() > 86) { yoffset = values[86][0] == '\0' ? 0 : std::stoi(values[86]); }
    if (values.size() > 87) { zoffset = values[87][0] == '\0' ? 0 : std::stoi(values[87]); }
    if (values.size() > 88) { Size = values[88][0] == '\0' ? 0 : std::stoi(values[88]); }
    if (values.size() > 89) { SrcTown = values[89][0] == '\0' ? 0 : std::stoi(values[89]); }
    if (values.size() > 90) { CltSrcTown = values[90][0] == '\0' ? 0 : std::stoi(values[90]); }
    if (values.size() > 91) { CanDestroy = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }
    if (values.size() > 92) { ToHit = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { AlwaysExplode = values[93][0] == '\0' ? 0 : std::stoi(values[93]); }
    if (values.size() > 94) { Explosion = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 95) { Town = values[95][0] == '\0' ? 0 : std::stoi(values[95]); }
    if (values.size() > 96) { NoUniqueMod = values[96][0] == '\0' ? 0 : std::stoi(values[96]); }
    if (values.size() > 97) { NoMultiShot = values[97][0] == '\0' ? 0 : std::stoi(values[97]); }
    if (values.size() > 98) { Holy = values[98][0] == '\0' ? 0 : std::stoi(values[98]); }
    if (values.size() > 99) { CanSlow = values[99][0] == '\0' ? 0 : std::stoi(values[99]); }
    if (values.size() > 100) { ReturnFire = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
    if (values.size() > 101) { GetHit = values[101][0] == '\0' ? 0 : std::stoi(values[101]); }
    if (values.size() > 102) { SoftHit = values[102][0] == '\0' ? 0 : std::stoi(values[102]); }
    if (values.size() > 103) { KnockBack = values[103][0] == '\0' ? 0 : std::stoi(values[103]); }
    if (values.size() > 104) { Trans = values[104][0] == '\0' ? 0 : std::stoi(values[104]); }
    if (values.size() > 105) { Pierce = values[105][0] == '\0' ? 0 : std::stoi(values[105]); }
    if (values.size() > 106) { MissileSkill = values[106][0] == '\0' ? 0 : std::stoi(values[106]); }
    if (values.size() > 107) { Skill = values[107]; }
    if (values.size() > 108) { ResultFlags = values[108][0] == '\0' ? 0 : std::stoi(values[108]); }
    if (values.size() > 109) { HitFlags = values[109][0] == '\0' ? 0 : std::stoi(values[109]); }
    if (values.size() > 110) { HitShift = values[110][0] == '\0' ? 0 : std::stoi(values[110]); }
    if (values.size() > 111) { ApplyMastery = values[111][0] == '\0' ? 0 : std::stoi(values[111]); }
    if (values.size() > 112) { SrcDamage = values[112][0] == '\0' ? 0 : std::stoi(values[112]); }
    if (values.size() > 113) { Half2HSrc = values[113][0] == '\0' ? 0 : std::stoi(values[113]); }
    if (values.size() > 115) { MinDamage = values[115][0] == '\0' ? 0 : std::stoi(values[115]); }
    if (values.size() > 116) { MinLevDam1 = values[116][0] == '\0' ? 0 : std::stoi(values[116]); }
    if (values.size() > 117) { MinLevDam2 = values[117][0] == '\0' ? 0 : std::stoi(values[117]); }
    if (values.size() > 118) { MinLevDam3 = values[118][0] == '\0' ? 0 : std::stoi(values[118]); }
    if (values.size() > 119) { MinLevDam4 = values[119][0] == '\0' ? 0 : std::stoi(values[119]); }
    if (values.size() > 120) { MinLevDam5 = values[120][0] == '\0' ? 0 : std::stoi(values[120]); }
    if (values.size() > 121) { MaxDamage = values[121][0] == '\0' ? 0 : std::stoi(values[121]); }
    if (values.size() > 122) { MaxLevDam1 = values[122][0] == '\0' ? 0 : std::stoi(values[122]); }
    if (values.size() > 123) { MaxLevDam2 = values[123][0] == '\0' ? 0 : std::stoi(values[123]); }
    if (values.size() > 124) { MaxLevDam3 = values[124][0] == '\0' ? 0 : std::stoi(values[124]); }
    if (values.size() > 125) { MaxLevDam4 = values[125][0] == '\0' ? 0 : std::stoi(values[125]); }
    if (values.size() > 126) { MaxLevDam5 = values[126][0] == '\0' ? 0 : std::stoi(values[126]); }
    if (values.size() > 128) { EType = values[128]; }
    if (values.size() > 129) { EMin = values[129][0] == '\0' ? 0 : std::stoi(values[129]); }
    if (values.size() > 130) { MinELev1 = values[130][0] == '\0' ? 0 : std::stoi(values[130]); }
    if (values.size() > 131) { MinELev2 = values[131][0] == '\0' ? 0 : std::stoi(values[131]); }
    if (values.size() > 132) { MinELev3 = values[132][0] == '\0' ? 0 : std::stoi(values[132]); }
    if (values.size() > 133) { MinELev4 = values[133][0] == '\0' ? 0 : std::stoi(values[133]); }
    if (values.size() > 134) { MinELev5 = values[134][0] == '\0' ? 0 : std::stoi(values[134]); }
    if (values.size() > 135) { EMax = values[135][0] == '\0' ? 0 : std::stoi(values[135]); }
    if (values.size() > 136) { MaxELev1 = values[136][0] == '\0' ? 0 : std::stoi(values[136]); }
    if (values.size() > 137) { MaxELev2 = values[137][0] == '\0' ? 0 : std::stoi(values[137]); }
    if (values.size() > 138) { MaxELev3 = values[138][0] == '\0' ? 0 : std::stoi(values[138]); }
    if (values.size() > 139) { MaxELev4 = values[139][0] == '\0' ? 0 : std::stoi(values[139]); }
    if (values.size() > 140) { MaxELev5 = values[140][0] == '\0' ? 0 : std::stoi(values[140]); }
    if (values.size() > 141) { EDmgSymPerCalc = values[141]; }
    if (values.size() > 142) { ELen = values[142][0] == '\0' ? 0 : std::stoi(values[142]); }
    if (values.size() > 143) { ELevLen1 = values[143][0] == '\0' ? 0 : std::stoi(values[143]); }
    if (values.size() > 144) { ELevLen2 = values[144][0] == '\0' ? 0 : std::stoi(values[144]); }
    if (values.size() > 145) { ELevLen3 = values[145][0] == '\0' ? 0 : std::stoi(values[145]); }
    if (values.size() > 146) { HitClass = values[146][0] == '\0' ? 0 : std::stoi(values[146]); }
    if (values.size() > 147) { NumDirections = values[147][0] == '\0' ? 0 : std::stoi(values[147]); }
    if (values.size() > 148) { LocalBlood = values[148][0] == '\0' ? 0 : std::stoi(values[148]); }
    if (values.size() > 149) { DamageRate = values[149][0] == '\0' ? 0 : std::stoi(values[149]); }
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
    if (values.size() > 171) { eol = values[171][0] == '\0' ? 0 : std::stoi(values[171]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { AI = values[0]; }
    if (values.size() > 1) { aip1 = values[1]; }
    if (values.size() > 2) { aip2 = values[2]; }
    if (values.size() > 3) { aip3 = values[3]; }
    if (values.size() > 4) { aip4 = values[4]; }
    if (values.size() > 5) { aip5 = values[5]; }
    if (values.size() > 6) { aip6 = values[6]; }
    if (values.size() > 7) { aip7 = values[7]; }
    if (values.size() > 8) { aip8 = values[8]; }
    if (values.size() > 9) { eol = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { monster = values[0]; }
    if (values.size() > 1) { oninit = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { level = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { item1 = values[3]; }
    if (values.size() > 4) { loc1 = values[4]; }
    if (values.size() > 5) { mod1 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { item2 = values[6]; }
    if (values.size() > 7) { loc2 = values[7]; }
    if (values.size() > 8) { mod2 = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { item3 = values[9]; }
    if (values.size() > 10) { loc3 = values[10]; }
    if (values.size() > 11) { mod3 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { eol = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Level = values[0][0] == '\0' ? 0 : std::stoi(values[0]); }
    if (values.size() > 1) { AC = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { ACN = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { ACH = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { LAC = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { LACN = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { LACH = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { TH = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { THN = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { THH = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { LTH = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { LTHN = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { LTHH = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { HP = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { HPN = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { HPH = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { LHP = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { LHPN = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { LHPH = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { DM = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { DMN = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { DMH = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { LDM = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { LDMN = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { LDMH = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { XP = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { XPN = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { XPH = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { LXP = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { LXPN = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { LXPH = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { monster = values[0]; }
    if (values.size() > 1) { index = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { hirelingAlternateVoice = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Act = values[0][0] == '\0' ? 0 : std::stoi(values[0]); }
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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { prop1 = values[1]; }
    if (values.size() > 4) { min1 = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { max1 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 31) { prop1N = values[31]; }
    if (values.size() > 34) { min1N = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { max1N = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { prop2N = values[36]; }
    if (values.size() > 39) { min2N = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { max2N = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 61) { prop1H = values[61]; }
    if (values.size() > 64) { min1H = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { max1H = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { prop2H = values[66]; }
    if (values.size() > 69) { min2H = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { max2H = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 91) { eol = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { sequence = values[0]; }
    if (values.size() > 1) { mode = values[1]; }
    if (values.size() > 2) { frame = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 4) { event = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { eol = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { Attack1 = values[1]; }
    if (values.size() > 2) { Weapon1 = values[2]; }
    if (values.size() > 3) { Att1Del = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Wea1Del = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Att1Prb = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Wea1Vol = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Attack2 = values[7]; }
    if (values.size() > 8) { Weapon2 = values[8]; }
    if (values.size() > 9) { Att2Del = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { Wea2Del = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Att2Prb = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { Wea2Vol = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { HitSound = values[13]; }
    if (values.size() > 14) { DeathSound = values[14]; }
    if (values.size() > 15) { HitDelay = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { DeaDelay = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { Skill1 = values[17]; }
    if (values.size() > 18) { Skill2 = values[18]; }
    if (values.size() > 19) { Skill3 = values[19]; }
    if (values.size() > 20) { Skill4 = values[20]; }
    if (values.size() > 21) { Footstep = values[21]; }
    if (values.size() > 22) { FootstepLayer = values[22]; }
    if (values.size() > 23) { FsCnt = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { FsOff = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { FsPrb = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { Neutral = values[26]; }
    if (values.size() > 27) { NeuTime = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
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
    if (values.size() > 40) { EOL = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { hcIdx = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { BaseId = values[2]; }
    if (values.size() > 3) { NextInClass = values[3]; }
    if (values.size() > 4) { TransLvl = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { NameStr = values[5]; }
    if (values.size() > 6) { MonStatsEx = values[6]; }
    if (values.size() > 7) { MonProp = values[7]; }
    if (values.size() > 8) { MonType = values[8]; }
    if (values.size() > 9) { AI = values[9]; }
    if (values.size() > 10) { DescStr = values[10]; }
    if (values.size() > 11) { Code = values[11]; }
    if (values.size() > 12) { enabled = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { rangedtype = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { placespawn = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { spawn = values[15]; }
    if (values.size() > 16) { spawnx = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { spawny = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { spawnmode = values[18]; }
    if (values.size() > 19) { minion1 = values[19]; }
    if (values.size() > 20) { minion2 = values[20]; }
    if (values.size() > 21) { SetBoss = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { BossXfer = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { PartyMin = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { PartyMax = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { MinGrp = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { MaxGrp = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { sparsePopulate = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { Velocity = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { Run = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { Rarity = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { Level = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { LevelN = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { LevelH = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { MonSound = values[34]; }
    if (values.size() > 35) { UMonSound = values[35]; }
    if (values.size() > 36) { threat = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { aidel = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { aidelN = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { aidelH = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 41) { aidistN = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { aidistH = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { aip1 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { aip1N = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { aip1H = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { aip2 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { aip2N = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { aip2H = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { aip3 = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { aip3N = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { aip3H = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { aip4 = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { aip4N = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { aip4H = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { aip5 = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { aip5N = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { aip5H = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { aip6 = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { aip6N = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { aip6H = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { aip7 = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { aip7N = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { aip7H = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { aip8 = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { aip8N = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { aip8H = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { MissA1 = values[67]; }
    if (values.size() > 68) { MissA2 = values[68]; }
    if (values.size() > 69) { MissS1 = values[69]; }
    if (values.size() > 70) { MissS2 = values[70]; }
    if (values.size() > 73) { MissC = values[73]; }
    if (values.size() > 74) { MissSQ = values[74]; }
    if (values.size() > 75) { Align = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
    if (values.size() > 76) { isSpawn = values[76][0] == '\0' ? 0 : std::stoi(values[76]); }
    if (values.size() > 77) { isMelee = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { npc = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 79) { interact = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 80) { inventory = values[80][0] == '\0' ? 0 : std::stoi(values[80]); }
    if (values.size() > 81) { inTown = values[81][0] == '\0' ? 0 : std::stoi(values[81]); }
    if (values.size() > 82) { lUndead = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }
    if (values.size() > 83) { hUndead = values[83][0] == '\0' ? 0 : std::stoi(values[83]); }
    if (values.size() > 84) { demon = values[84][0] == '\0' ? 0 : std::stoi(values[84]); }
    if (values.size() > 85) { flying = values[85][0] == '\0' ? 0 : std::stoi(values[85]); }
    if (values.size() > 86) { opendoors = values[86][0] == '\0' ? 0 : std::stoi(values[86]); }
    if (values.size() > 87) { boss = values[87][0] == '\0' ? 0 : std::stoi(values[87]); }
    if (values.size() > 88) { primeevil = values[88][0] == '\0' ? 0 : std::stoi(values[88]); }
    if (values.size() > 89) { killable = values[89][0] == '\0' ? 0 : std::stoi(values[89]); }
    if (values.size() > 90) { switchai = values[90][0] == '\0' ? 0 : std::stoi(values[90]); }
    if (values.size() > 91) { noAura = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }
    if (values.size() > 92) { nomultishot = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 94) { neverCount = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 95) { petIgnore = values[95][0] == '\0' ? 0 : std::stoi(values[95]); }
    if (values.size() > 96) { deathDmg = values[96][0] == '\0' ? 0 : std::stoi(values[96]); }
    if (values.size() > 97) { genericSpawn = values[97][0] == '\0' ? 0 : std::stoi(values[97]); }
    if (values.size() > 98) { zoo = values[98][0] == '\0' ? 0 : std::stoi(values[98]); }
    if (values.size() > 99) { CannotDesecrate = values[99][0] == '\0' ? 0 : std::stoi(values[99]); }
    if (values.size() > 101) { rightArmItemType = values[101]; }
    if (values.size() > 102) { leftArmItemType = values[102]; }
    if (values.size() > 103) { canNotUseTwoHandedItems = values[103][0] == '\0' ? 0 : std::stoi(values[103]); }
    if (values.size() > 104) { SendSkills = values[104][0] == '\0' ? 0 : std::stoi(values[104]); }
    if (values.size() > 105) { Skill1 = values[105]; }
    if (values.size() > 106) { Sk1mode = values[106]; }
    if (values.size() > 107) { Sk1lvl = values[107][0] == '\0' ? 0 : std::stoi(values[107]); }
    if (values.size() > 108) { Skill2 = values[108]; }
    if (values.size() > 109) { Sk2mode = values[109]; }
    if (values.size() > 110) { Sk2lvl = values[110][0] == '\0' ? 0 : std::stoi(values[110]); }
    if (values.size() > 111) { Skill3 = values[111]; }
    if (values.size() > 112) { Sk3mode = values[112]; }
    if (values.size() > 113) { Sk3lvl = values[113][0] == '\0' ? 0 : std::stoi(values[113]); }
    if (values.size() > 114) { Skill4 = values[114]; }
    if (values.size() > 115) { Sk4mode = values[115]; }
    if (values.size() > 116) { Sk4lvl = values[116][0] == '\0' ? 0 : std::stoi(values[116]); }
    if (values.size() > 117) { Skill5 = values[117]; }
    if (values.size() > 118) { Sk5mode = values[118]; }
    if (values.size() > 119) { Sk5lvl = values[119][0] == '\0' ? 0 : std::stoi(values[119]); }
    if (values.size() > 120) { Skill6 = values[120]; }
    if (values.size() > 121) { Sk6mode = values[121]; }
    if (values.size() > 122) { Sk6lvl = values[122][0] == '\0' ? 0 : std::stoi(values[122]); }
    if (values.size() > 123) { Skill7 = values[123]; }
    if (values.size() > 124) { Sk7mode = values[124]; }
    if (values.size() > 125) { Sk7lvl = values[125][0] == '\0' ? 0 : std::stoi(values[125]); }
    if (values.size() > 126) { Skill8 = values[126]; }
    if (values.size() > 127) { Sk8mode = values[127]; }
    if (values.size() > 128) { Sk8lvl = values[128][0] == '\0' ? 0 : std::stoi(values[128]); }
    if (values.size() > 129) { Drain = values[129][0] == '\0' ? 0 : std::stoi(values[129]); }
    if (values.size() > 130) { DrainN = values[130][0] == '\0' ? 0 : std::stoi(values[130]); }
    if (values.size() > 131) { DrainH = values[131][0] == '\0' ? 0 : std::stoi(values[131]); }
    if (values.size() > 132) { coldeffect = values[132][0] == '\0' ? 0 : std::stoi(values[132]); }
    if (values.size() > 133) { coldeffectN = values[133][0] == '\0' ? 0 : std::stoi(values[133]); }
    if (values.size() > 134) { coldeffectH = values[134][0] == '\0' ? 0 : std::stoi(values[134]); }
    if (values.size() > 135) { ResDm = values[135][0] == '\0' ? 0 : std::stoi(values[135]); }
    if (values.size() > 136) { ResMa = values[136][0] == '\0' ? 0 : std::stoi(values[136]); }
    if (values.size() > 137) { ResFi = values[137][0] == '\0' ? 0 : std::stoi(values[137]); }
    if (values.size() > 138) { ResLi = values[138][0] == '\0' ? 0 : std::stoi(values[138]); }
    if (values.size() > 139) { ResCo = values[139][0] == '\0' ? 0 : std::stoi(values[139]); }
    if (values.size() > 140) { ResPo = values[140][0] == '\0' ? 0 : std::stoi(values[140]); }
    if (values.size() > 141) { ResDmN = values[141][0] == '\0' ? 0 : std::stoi(values[141]); }
    if (values.size() > 142) { ResMaN = values[142][0] == '\0' ? 0 : std::stoi(values[142]); }
    if (values.size() > 143) { ResFiN = values[143][0] == '\0' ? 0 : std::stoi(values[143]); }
    if (values.size() > 144) { ResLiN = values[144][0] == '\0' ? 0 : std::stoi(values[144]); }
    if (values.size() > 145) { ResCoN = values[145][0] == '\0' ? 0 : std::stoi(values[145]); }
    if (values.size() > 146) { ResPoN = values[146][0] == '\0' ? 0 : std::stoi(values[146]); }
    if (values.size() > 147) { ResDmH = values[147][0] == '\0' ? 0 : std::stoi(values[147]); }
    if (values.size() > 148) { ResMaH = values[148][0] == '\0' ? 0 : std::stoi(values[148]); }
    if (values.size() > 149) { ResFiH = values[149][0] == '\0' ? 0 : std::stoi(values[149]); }
    if (values.size() > 150) { ResLiH = values[150][0] == '\0' ? 0 : std::stoi(values[150]); }
    if (values.size() > 151) { ResCoH = values[151][0] == '\0' ? 0 : std::stoi(values[151]); }
    if (values.size() > 152) { ResPoH = values[152][0] == '\0' ? 0 : std::stoi(values[152]); }
    if (values.size() > 153) { DamageRegen = values[153][0] == '\0' ? 0 : std::stoi(values[153]); }
    if (values.size() > 154) { SkillDamage = values[154]; }
    if (values.size() > 155) { noRatio = values[155][0] == '\0' ? 0 : std::stoi(values[155]); }
    if (values.size() > 156) { ShieldBlockOverride = values[156][0] == '\0' ? 0 : std::stoi(values[156]); }
    if (values.size() > 157) { ToBlock = values[157][0] == '\0' ? 0 : std::stoi(values[157]); }
    if (values.size() > 158) { ToBlockN = values[158][0] == '\0' ? 0 : std::stoi(values[158]); }
    if (values.size() > 159) { ToBlockH = values[159][0] == '\0' ? 0 : std::stoi(values[159]); }
    if (values.size() > 160) { Crit = values[160][0] == '\0' ? 0 : std::stoi(values[160]); }
    if (values.size() > 161) { minHP = values[161][0] == '\0' ? 0 : std::stoi(values[161]); }
    if (values.size() > 162) { maxHP = values[162][0] == '\0' ? 0 : std::stoi(values[162]); }
    if (values.size() > 163) { AC = values[163][0] == '\0' ? 0 : std::stoi(values[163]); }
    if (values.size() > 164) { Exp = values[164][0] == '\0' ? 0 : std::stoi(values[164]); }
    if (values.size() > 165) { A1MinD = values[165][0] == '\0' ? 0 : std::stoi(values[165]); }
    if (values.size() > 166) { A1MaxD = values[166][0] == '\0' ? 0 : std::stoi(values[166]); }
    if (values.size() > 167) { A1TH = values[167][0] == '\0' ? 0 : std::stoi(values[167]); }
    if (values.size() > 168) { A2MinD = values[168][0] == '\0' ? 0 : std::stoi(values[168]); }
    if (values.size() > 169) { A2MaxD = values[169][0] == '\0' ? 0 : std::stoi(values[169]); }
    if (values.size() > 170) { A2TH = values[170][0] == '\0' ? 0 : std::stoi(values[170]); }
    if (values.size() > 171) { S1MinD = values[171][0] == '\0' ? 0 : std::stoi(values[171]); }
    if (values.size() > 172) { S1MaxD = values[172][0] == '\0' ? 0 : std::stoi(values[172]); }
    if (values.size() > 173) { S1TH = values[173][0] == '\0' ? 0 : std::stoi(values[173]); }
    if (values.size() > 174) { MinHPN = values[174][0] == '\0' ? 0 : std::stoi(values[174]); }
    if (values.size() > 175) { MaxHPN = values[175][0] == '\0' ? 0 : std::stoi(values[175]); }
    if (values.size() > 176) { ACN = values[176][0] == '\0' ? 0 : std::stoi(values[176]); }
    if (values.size() > 177) { ExpN = values[177][0] == '\0' ? 0 : std::stoi(values[177]); }
    if (values.size() > 178) { A1MinDN = values[178][0] == '\0' ? 0 : std::stoi(values[178]); }
    if (values.size() > 179) { A1MaxDN = values[179][0] == '\0' ? 0 : std::stoi(values[179]); }
    if (values.size() > 180) { A1THN = values[180][0] == '\0' ? 0 : std::stoi(values[180]); }
    if (values.size() > 181) { A2MinDN = values[181][0] == '\0' ? 0 : std::stoi(values[181]); }
    if (values.size() > 182) { A2MaxDN = values[182][0] == '\0' ? 0 : std::stoi(values[182]); }
    if (values.size() > 183) { A2THN = values[183][0] == '\0' ? 0 : std::stoi(values[183]); }
    if (values.size() > 184) { S1MinDN = values[184][0] == '\0' ? 0 : std::stoi(values[184]); }
    if (values.size() > 185) { S1MaxDN = values[185][0] == '\0' ? 0 : std::stoi(values[185]); }
    if (values.size() > 186) { S1THN = values[186][0] == '\0' ? 0 : std::stoi(values[186]); }
    if (values.size() > 187) { MinHPH = values[187][0] == '\0' ? 0 : std::stoi(values[187]); }
    if (values.size() > 188) { MaxHPH = values[188][0] == '\0' ? 0 : std::stoi(values[188]); }
    if (values.size() > 189) { ACH = values[189][0] == '\0' ? 0 : std::stoi(values[189]); }
    if (values.size() > 190) { ExpH = values[190][0] == '\0' ? 0 : std::stoi(values[190]); }
    if (values.size() > 191) { A1MinDH = values[191][0] == '\0' ? 0 : std::stoi(values[191]); }
    if (values.size() > 192) { A1MaxDH = values[192][0] == '\0' ? 0 : std::stoi(values[192]); }
    if (values.size() > 193) { A1THH = values[193][0] == '\0' ? 0 : std::stoi(values[193]); }
    if (values.size() > 194) { A2MinDH = values[194][0] == '\0' ? 0 : std::stoi(values[194]); }
    if (values.size() > 195) { A2MaxDH = values[195][0] == '\0' ? 0 : std::stoi(values[195]); }
    if (values.size() > 196) { A2THH = values[196][0] == '\0' ? 0 : std::stoi(values[196]); }
    if (values.size() > 197) { S1MinDH = values[197][0] == '\0' ? 0 : std::stoi(values[197]); }
    if (values.size() > 198) { S1MaxDH = values[198][0] == '\0' ? 0 : std::stoi(values[198]); }
    if (values.size() > 199) { S1THH = values[199][0] == '\0' ? 0 : std::stoi(values[199]); }
    if (values.size() > 200) { El1Mode = values[200]; }
    if (values.size() > 201) { El1Type = values[201]; }
    if (values.size() > 202) { El1Pct = values[202][0] == '\0' ? 0 : std::stoi(values[202]); }
    if (values.size() > 203) { El1MinD = values[203][0] == '\0' ? 0 : std::stoi(values[203]); }
    if (values.size() > 204) { El1MaxD = values[204][0] == '\0' ? 0 : std::stoi(values[204]); }
    if (values.size() > 205) { El1Dur = values[205][0] == '\0' ? 0 : std::stoi(values[205]); }
    if (values.size() > 206) { El1PctN = values[206][0] == '\0' ? 0 : std::stoi(values[206]); }
    if (values.size() > 207) { El1MinDN = values[207][0] == '\0' ? 0 : std::stoi(values[207]); }
    if (values.size() > 208) { El1MaxDN = values[208][0] == '\0' ? 0 : std::stoi(values[208]); }
    if (values.size() > 209) { El1DurN = values[209][0] == '\0' ? 0 : std::stoi(values[209]); }
    if (values.size() > 210) { El1PctH = values[210][0] == '\0' ? 0 : std::stoi(values[210]); }
    if (values.size() > 211) { El1MinDH = values[211][0] == '\0' ? 0 : std::stoi(values[211]); }
    if (values.size() > 212) { El1MaxDH = values[212][0] == '\0' ? 0 : std::stoi(values[212]); }
    if (values.size() > 213) { El1DurH = values[213][0] == '\0' ? 0 : std::stoi(values[213]); }
    if (values.size() > 214) { El2Mode = values[214]; }
    if (values.size() > 215) { El2Type = values[215]; }
    if (values.size() > 216) { El2Pct = values[216][0] == '\0' ? 0 : std::stoi(values[216]); }
    if (values.size() > 217) { El2MinD = values[217][0] == '\0' ? 0 : std::stoi(values[217]); }
    if (values.size() > 218) { El2MaxD = values[218][0] == '\0' ? 0 : std::stoi(values[218]); }
    if (values.size() > 219) { El2Dur = values[219][0] == '\0' ? 0 : std::stoi(values[219]); }
    if (values.size() > 220) { El2PctN = values[220][0] == '\0' ? 0 : std::stoi(values[220]); }
    if (values.size() > 221) { El2MinDN = values[221][0] == '\0' ? 0 : std::stoi(values[221]); }
    if (values.size() > 222) { El2MaxDN = values[222][0] == '\0' ? 0 : std::stoi(values[222]); }
    if (values.size() > 223) { El2DurN = values[223][0] == '\0' ? 0 : std::stoi(values[223]); }
    if (values.size() > 224) { El2PctH = values[224][0] == '\0' ? 0 : std::stoi(values[224]); }
    if (values.size() > 225) { El2MinDH = values[225][0] == '\0' ? 0 : std::stoi(values[225]); }
    if (values.size() > 226) { El2MaxDH = values[226][0] == '\0' ? 0 : std::stoi(values[226]); }
    if (values.size() > 227) { El2DurH = values[227][0] == '\0' ? 0 : std::stoi(values[227]); }
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
    if (values.size() > 266) { TCQuestId = values[266][0] == '\0' ? 0 : std::stoi(values[266]); }
    if (values.size() > 267) { TCQuestCP = values[267][0] == '\0' ? 0 : std::stoi(values[267]); }
    if (values.size() > 268) { SplEndDeath = values[268][0] == '\0' ? 0 : std::stoi(values[268]); }
    if (values.size() > 269) { SplGetModeChart = values[269][0] == '\0' ? 0 : std::stoi(values[269]); }
    if (values.size() > 270) { SplEndGeneric = values[270][0] == '\0' ? 0 : std::stoi(values[270]); }
    if (values.size() > 271) { SplClientEnd = values[271][0] == '\0' ? 0 : std::stoi(values[271]); }
    if (values.size() > 272) { eol = values[272][0] == '\0' ? 0 : std::stoi(values[272]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Id = values[0]; }
    if (values.size() > 1) { hcIdx = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Height = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { OverlayHeight = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { pixHeight = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { SizeX = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { SizeY = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { spawnCol = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { MeleeRng = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { BaseW = values[9]; }
    if (values.size() > 10) { HitClass = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
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
    if (values.size() > 27) { HD = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { TR = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { LG = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { RA = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { LA = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { RH = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { LH = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { SH = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { S1 = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { S2 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { S3 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { S4 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { S5 = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { S6 = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { S7 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { S8 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { TotalPieces = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { mDT = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { mNU = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { mWL = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { mGH = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { mA1 = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { mA2 = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { mBL = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { mSC = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { mS1 = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { mS2 = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { mS3 = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { mS4 = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { mDD = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { mKB = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { mSQ = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { mRN = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { dDT = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { dNU = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { dWL = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { dGH = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { dA1 = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { dA2 = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { dBL = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { dSC = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { dS1 = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { dS2 = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { dS3 = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 71) { dS4 = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { dDD = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { dKB = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { dSQ = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { dRN = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
    if (values.size() > 77) { A2mv = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 79) { S1mv = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 80) { S2mv = values[80][0] == '\0' ? 0 : std::stoi(values[80]); }
    if (values.size() > 83) { noGfxHitTest = values[83][0] == '\0' ? 0 : std::stoi(values[83]); }
    if (values.size() > 84) { htTop = values[84][0] == '\0' ? 0 : std::stoi(values[84]); }
    if (values.size() > 85) { htLeft = values[85][0] == '\0' ? 0 : std::stoi(values[85]); }
    if (values.size() > 86) { htWidth = values[86][0] == '\0' ? 0 : std::stoi(values[86]); }
    if (values.size() > 87) { htHeight = values[87][0] == '\0' ? 0 : std::stoi(values[87]); }
    if (values.size() > 88) { restore = values[88][0] == '\0' ? 0 : std::stoi(values[88]); }
    if (values.size() > 89) { automapCel = values[89][0] == '\0' ? 0 : std::stoi(values[89]); }
    if (values.size() > 90) { noMap = values[90][0] == '\0' ? 0 : std::stoi(values[90]); }
    if (values.size() > 91) { noOvly = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }
    if (values.size() > 92) { isSel = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { alSel = values[93][0] == '\0' ? 0 : std::stoi(values[93]); }
    if (values.size() > 94) { noSel = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 95) { shiftSel = values[95][0] == '\0' ? 0 : std::stoi(values[95]); }
    if (values.size() > 96) { corpseSel = values[96][0] == '\0' ? 0 : std::stoi(values[96]); }
    if (values.size() > 97) { isAtt = values[97][0] == '\0' ? 0 : std::stoi(values[97]); }
    if (values.size() > 98) { revive = values[98][0] == '\0' ? 0 : std::stoi(values[98]); }
    if (values.size() > 99) { limitCorpses = values[99][0] == '\0' ? 0 : std::stoi(values[99]); }
    if (values.size() > 100) { critter = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
    if (values.size() > 101) { small = values[101][0] == '\0' ? 0 : std::stoi(values[101]); }
    if (values.size() > 102) { large = values[102][0] == '\0' ? 0 : std::stoi(values[102]); }
    if (values.size() > 103) { soft = values[103][0] == '\0' ? 0 : std::stoi(values[103]); }
    if (values.size() > 104) { inert = values[104][0] == '\0' ? 0 : std::stoi(values[104]); }
    if (values.size() > 105) { objCol = values[105][0] == '\0' ? 0 : std::stoi(values[105]); }
    if (values.size() > 106) { deadCol = values[106][0] == '\0' ? 0 : std::stoi(values[106]); }
    if (values.size() > 107) { unflatDead = values[107][0] == '\0' ? 0 : std::stoi(values[107]); }
    if (values.size() > 108) { Shadow = values[108][0] == '\0' ? 0 : std::stoi(values[108]); }
    if (values.size() > 109) { noUniqueShift = values[109][0] == '\0' ? 0 : std::stoi(values[109]); }
    if (values.size() > 110) { compositeDeath = values[110][0] == '\0' ? 0 : std::stoi(values[110]); }
    if (values.size() > 111) { localBlood = values[111][0] == '\0' ? 0 : std::stoi(values[111]); }
    if (values.size() > 112) { Bleed = values[112][0] == '\0' ? 0 : std::stoi(values[112]); }
    if (values.size() > 113) { Light = values[113][0] == '\0' ? 0 : std::stoi(values[113]); }
    if (values.size() > 114) { lightr = values[114][0] == '\0' ? 0 : std::stoi(values[114]); }
    if (values.size() > 115) { lightg = values[115][0] == '\0' ? 0 : std::stoi(values[115]); }
    if (values.size() > 116) { lightb = values[116][0] == '\0' ? 0 : std::stoi(values[116]); }
    if (values.size() > 117) { Utrans = values[117][0] == '\0' ? 0 : std::stoi(values[117]); }
    if (values.size() > 118) { UtransN = values[118][0] == '\0' ? 0 : std::stoi(values[118]); }
    if (values.size() > 119) { UtransH = values[119][0] == '\0' ? 0 : std::stoi(values[119]); }
    if (values.size() > 120) { InfernoLen = values[120][0] == '\0' ? 0 : std::stoi(values[120]); }
    if (values.size() > 121) { InfernoAnim = values[121][0] == '\0' ? 0 : std::stoi(values[121]); }
    if (values.size() > 122) { InfernoRollback = values[122][0] == '\0' ? 0 : std::stoi(values[122]); }
    if (values.size() > 123) { ResurrectMode = values[123]; }
    if (values.size() > 124) { ResurrectSkill = values[124]; }
    if (values.size() > 125) { SpawnUniqueMod = values[125]; }
    if (values.size() > 126) { eol = values[126][0] == '\0' ? 0 : std::stoi(values[126]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { type = values[0]; }
    if (values.size() > 1) { equiv1 = values[1]; }
    if (values.size() > 2) { equiv2 = values[2]; }
    if (values.size() > 4) { strplur = values[4]; }
    if (values.size() > 6) { eol = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { uniquemod = values[0]; }
    if (values.size() > 1) { id = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { enabled = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { version = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { xfer = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { champion = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { fPick = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { exclude1 = values[7]; }
    if (values.size() > 9) { cpick = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { cpickN = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { cpickH = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { upick = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { upickN = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { upickH = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { constants = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { constantdesc = values[16]; }
    if (values.size() > 17) { eol = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { npc = values[0]; }
    if (values.size() > 1) { buymult = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { sellmult = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { repmult = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { questflagA = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { questbuymultA = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { questsellmultA = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { questrepmultA = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 16) { maxbuy = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { maxbuyN = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { maxbuyH = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Class = values[0]; }
    if (values.size() > 1) { Name = values[1]; }
    if (values.size() > 2) { Description = values[2]; }
    if (values.size() > 3) { ID = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Token = values[4]; }
    if (values.size() > 5) { Selectable0 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Selectable1 = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Selectable2 = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { Selectable3 = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { Selectable4 = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { Selectable5 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Selectable6 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { Selectable7 = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { SizeX = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { SizeY = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { FrameCnt0 = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { FrameCnt1 = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { FrameCnt2 = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { FrameCnt3 = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { FrameCnt4 = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { FrameCnt5 = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { FrameCnt6 = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { FrameCnt7 = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { FrameDelta0 = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { FrameDelta1 = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { FrameDelta2 = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { FrameDelta3 = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { FrameDelta4 = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { FrameDelta5 = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { FrameDelta6 = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { FrameDelta7 = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { CycleAnim0 = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { CycleAnim1 = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { CycleAnim2 = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { CycleAnim3 = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { CycleAnim4 = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { CycleAnim5 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { CycleAnim6 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { CycleAnim7 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { Lit0 = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { Lit1 = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { Lit2 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { Lit3 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { Lit4 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { Lit5 = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { Lit6 = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { Lit7 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { BlocksLight0 = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { BlocksLight1 = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { BlocksLight2 = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { BlocksLight3 = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { BlocksLight4 = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { BlocksLight5 = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { BlocksLight6 = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { BlocksLight7 = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { HasCollision0 = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { HasCollision1 = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { HasCollision2 = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { HasCollision3 = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { HasCollision4 = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { HasCollision5 = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { HasCollision6 = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { HasCollision7 = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { IsAttackable0 = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { Start0 = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { Start1 = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { Start2 = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { Start3 = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { Start4 = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { Start5 = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { Start6 = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 71) { Start7 = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { EnvEffect = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { IsDoor = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { BlocksVis = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { Orientation = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
    if (values.size() > 76) { OrderFlag0 = values[76][0] == '\0' ? 0 : std::stoi(values[76]); }
    if (values.size() > 77) { OrderFlag1 = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { OrderFlag2 = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 79) { OrderFlag3 = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 80) { OrderFlag4 = values[80][0] == '\0' ? 0 : std::stoi(values[80]); }
    if (values.size() > 81) { OrderFlag5 = values[81][0] == '\0' ? 0 : std::stoi(values[81]); }
    if (values.size() > 82) { OrderFlag6 = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }
    if (values.size() > 83) { OrderFlag7 = values[83][0] == '\0' ? 0 : std::stoi(values[83]); }
    if (values.size() > 84) { PreOperate = values[84][0] == '\0' ? 0 : std::stoi(values[84]); }
    if (values.size() > 85) { Mode0 = values[85][0] == '\0' ? 0 : std::stoi(values[85]); }
    if (values.size() > 86) { Mode1 = values[86][0] == '\0' ? 0 : std::stoi(values[86]); }
    if (values.size() > 87) { Mode2 = values[87][0] == '\0' ? 0 : std::stoi(values[87]); }
    if (values.size() > 88) { Mode3 = values[88][0] == '\0' ? 0 : std::stoi(values[88]); }
    if (values.size() > 89) { Mode4 = values[89][0] == '\0' ? 0 : std::stoi(values[89]); }
    if (values.size() > 90) { Mode5 = values[90][0] == '\0' ? 0 : std::stoi(values[90]); }
    if (values.size() > 91) { Mode6 = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }
    if (values.size() > 92) { Mode7 = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { Yoffset = values[93][0] == '\0' ? 0 : std::stoi(values[93]); }
    if (values.size() > 94) { Xoffset = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 95) { Draw = values[95][0] == '\0' ? 0 : std::stoi(values[95]); }
    if (values.size() > 96) { Red = values[96][0] == '\0' ? 0 : std::stoi(values[96]); }
    if (values.size() > 97) { Green = values[97][0] == '\0' ? 0 : std::stoi(values[97]); }
    if (values.size() > 98) { Blue = values[98][0] == '\0' ? 0 : std::stoi(values[98]); }
    if (values.size() > 99) { HD = values[99][0] == '\0' ? 0 : std::stoi(values[99]); }
    if (values.size() > 100) { TR = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
    if (values.size() > 101) { LG = values[101][0] == '\0' ? 0 : std::stoi(values[101]); }
    if (values.size() > 102) { RA = values[102][0] == '\0' ? 0 : std::stoi(values[102]); }
    if (values.size() > 103) { LA = values[103][0] == '\0' ? 0 : std::stoi(values[103]); }
    if (values.size() > 104) { RH = values[104][0] == '\0' ? 0 : std::stoi(values[104]); }
    if (values.size() > 105) { LH = values[105][0] == '\0' ? 0 : std::stoi(values[105]); }
    if (values.size() > 106) { SH = values[106][0] == '\0' ? 0 : std::stoi(values[106]); }
    if (values.size() > 107) { S1 = values[107][0] == '\0' ? 0 : std::stoi(values[107]); }
    if (values.size() > 108) { S2 = values[108][0] == '\0' ? 0 : std::stoi(values[108]); }
    if (values.size() > 109) { S3 = values[109][0] == '\0' ? 0 : std::stoi(values[109]); }
    if (values.size() > 110) { S4 = values[110][0] == '\0' ? 0 : std::stoi(values[110]); }
    if (values.size() > 111) { S5 = values[111][0] == '\0' ? 0 : std::stoi(values[111]); }
    if (values.size() > 112) { S6 = values[112][0] == '\0' ? 0 : std::stoi(values[112]); }
    if (values.size() > 113) { S7 = values[113][0] == '\0' ? 0 : std::stoi(values[113]); }
    if (values.size() > 114) { S8 = values[114][0] == '\0' ? 0 : std::stoi(values[114]); }
    if (values.size() > 115) { TotalPieces = values[115][0] == '\0' ? 0 : std::stoi(values[115]); }
    if (values.size() > 116) { SubClass = values[116][0] == '\0' ? 0 : std::stoi(values[116]); }
    if (values.size() > 117) { Xspace = values[117][0] == '\0' ? 0 : std::stoi(values[117]); }
    if (values.size() > 118) { Yspace = values[118][0] == '\0' ? 0 : std::stoi(values[118]); }
    if (values.size() > 119) { NameOffset = values[119][0] == '\0' ? 0 : std::stoi(values[119]); }
    if (values.size() > 120) { MonsterOK = values[120][0] == '\0' ? 0 : std::stoi(values[120]); }
    if (values.size() > 121) { ShrineFunction = values[121][0] == '\0' ? 0 : std::stoi(values[121]); }
    if (values.size() > 122) { Restore = values[122][0] == '\0' ? 0 : std::stoi(values[122]); }
    if (values.size() > 123) { Parm0 = values[123][0] == '\0' ? 0 : std::stoi(values[123]); }
    if (values.size() > 124) { Parm1 = values[124][0] == '\0' ? 0 : std::stoi(values[124]); }
    if (values.size() > 125) { Parm2 = values[125][0] == '\0' ? 0 : std::stoi(values[125]); }
    if (values.size() > 126) { Parm3 = values[126][0] == '\0' ? 0 : std::stoi(values[126]); }
    if (values.size() > 127) { Parm4 = values[127][0] == '\0' ? 0 : std::stoi(values[127]); }
    if (values.size() > 128) { Lockable = values[128][0] == '\0' ? 0 : std::stoi(values[128]); }
    if (values.size() > 129) { Gore = values[129][0] == '\0' ? 0 : std::stoi(values[129]); }
    if (values.size() > 130) { Sync = values[130][0] == '\0' ? 0 : std::stoi(values[130]); }
    if (values.size() > 131) { Damage = values[131][0] == '\0' ? 0 : std::stoi(values[131]); }
    if (values.size() > 132) { Overlay = values[132][0] == '\0' ? 0 : std::stoi(values[132]); }
    if (values.size() > 133) { CollisionSubst = values[133][0] == '\0' ? 0 : std::stoi(values[133]); }
    if (values.size() > 134) { Left = values[134][0] == '\0' ? 0 : std::stoi(values[134]); }
    if (values.size() > 135) { Top = values[135][0] == '\0' ? 0 : std::stoi(values[135]); }
    if (values.size() > 136) { Width = values[136][0] == '\0' ? 0 : std::stoi(values[136]); }
    if (values.size() > 137) { Height = values[137][0] == '\0' ? 0 : std::stoi(values[137]); }
    if (values.size() > 138) { OperateFn = values[138][0] == '\0' ? 0 : std::stoi(values[138]); }
    if (values.size() > 139) { PopulateFn = values[139][0] == '\0' ? 0 : std::stoi(values[139]); }
    if (values.size() > 140) { InitFn = values[140][0] == '\0' ? 0 : std::stoi(values[140]); }
    if (values.size() > 141) { ClientFn = values[141][0] == '\0' ? 0 : std::stoi(values[141]); }
    if (values.size() > 142) { RestoreVirgins = values[142][0] == '\0' ? 0 : std::stoi(values[142]); }
    if (values.size() > 143) { BlockMissile = values[143][0] == '\0' ? 0 : std::stoi(values[143]); }
    if (values.size() > 144) { DrawUnder = values[144][0] == '\0' ? 0 : std::stoi(values[144]); }
    if (values.size() > 145) { OpenWarp = values[145][0] == '\0' ? 0 : std::stoi(values[145]); }
    if (values.size() > 146) { AutoMap = values[146][0] == '\0' ? 0 : std::stoi(values[146]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { GroupName = values[0]; }
    if (values.size() > 1) { ID = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { ID0 = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { DENSITY0 = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { PROB0 = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { ID1 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { DENSITY1 = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { PROB1 = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { ID2 = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { DENSITY2 = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { PROB2 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { ID3 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { DENSITY3 = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { PROB3 = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { ID4 = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { DENSITY4 = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { PROB4 = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { ID5 = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { DENSITY5 = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { PROB5 = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { ID6 = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { DENSITY6 = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { PROB6 = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { ID7 = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { DENSITY7 = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { PROB7 = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Index = values[0][0] == '\0' ? 0 : std::stoi(values[0]); }
    if (values.size() > 1) { Act = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { ObjectClass = values[2]; }
    if (values.size() > 3) { Notes = values[3]; }
    if (values.size() > 4) { eol = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { overlay = values[0]; }
    if (values.size() > 1) { ID = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Filename = values[2]; }
    if (values.size() > 3) { version = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Frames = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Character = values[5]; }
    if (values.size() > 6) { PreDraw = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { _1ofN = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { Xoffset = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { Yoffset = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { Height1 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Height2 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { Height3 = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Height4 = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { AnimRate = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { LoopWaitTime = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { Trans = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { InitRadius = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { Radius = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { Red = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { Green = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { Blue = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { NumDirections = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { LocalBlood = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { pettype = values[0]; }
    if (values.size() > 3) { basemax = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { warp = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { range = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { partysend = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { unsummon = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { automap = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { name = values[9]; }
    if (values.size() > 10) { drawhp = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { icontype = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { baseicon = values[12]; }
    if (values.size() > 13) { mclass1 = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { micon1 = values[14]; }
    if (values.size() > 15) { mclass2 = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { micon2 = values[16]; }
    if (values.size() > 17) { mclass3 = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { micon3 = values[18]; }
    if (values.size() > 19) { mclass4 = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { code = values[0]; }
    if (values.size() > 1) { Id = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Enabled = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { func1 = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { stat1 = values[4]; }
    if (values.size() > 5) { set1 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { val1 = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { func2 = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { stat2 = values[8]; }
    if (values.size() > 11) { func3 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { stat3 = values[12]; }
    if (values.size() > 15) { func4 = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { stat4 = values[16]; }
    if (values.size() > 19) { func5 = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { stat5 = values[20]; }
    if (values.size() > 23) { func6 = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { stat6 = values[24]; }
    if (values.size() > 27) { func7 = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { stat7 = values[28]; }
    if (values.size() > 31) { Tooltip = values[31]; }
    if (values.size() > 32) { Parameter = values[32]; }
    if (values.size() > 33) { Min = values[33]; }
    if (values.size() > 34) { Max = values[34]; }
    if (values.size() > 35) { Notes = values[35]; }
    if (values.size() > 36) { eol = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { code = values[0]; }
    if (values.size() > 1) { Id = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { PickMode = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Prop1 = values[3]; }
    if (values.size() > 4) { ParMin1 = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { ParMax1 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { ModMin1 = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { ModMax1 = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { Chance1 = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { Prop2 = values[9]; }
    if (values.size() > 10) { ParMin2 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { ParMax2 = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { ModMin2 = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { ModMax2 = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { Chance2 = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { Prop3 = values[15]; }
    if (values.size() > 18) { ModMin3 = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { ModMax3 = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { Chance3 = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { Prop4 = values[21]; }
    if (values.size() > 24) { ModMin4 = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { ModMax4 = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { Chance4 = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { Prop5 = values[27]; }
    if (values.size() > 30) { ModMin5 = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { ModMax5 = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { Chance5 = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { Prop6 = values[33]; }
    if (values.size() > 36) { ModMin6 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { ModMax6 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { Chance6 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 56) { eol = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { mod1code = values[0]; }
    if (values.size() > 1) { mod1param = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { mod1min = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { mod1max = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { mod2code = values[4]; }
    if (values.size() > 5) { mod2param = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { mod2min = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { mod2max = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { armor = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { weapon = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { shield = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { scepter = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { wand = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { staff = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { bow = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { boots = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { gloves = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { belt = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { version = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { version = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { RuneName = values[1]; }
    if (values.size() > 2) { complete = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { disallowCraftingInLadder = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 5) { firstLadderSeason = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { lastLadderSeason = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
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
    if (values.size() > 26) { T1Min1 = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { T1Max1 = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { T1Code2 = values[28]; }
    if (values.size() > 29) { T1Param2 = values[29]; }
    if (values.size() > 30) { T1Min2 = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { T1Max2 = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { T1Code3 = values[32]; }
    if (values.size() > 33) { T1Param3 = values[33]; }
    if (values.size() > 34) { T1Min3 = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { T1Max3 = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { T1Code4 = values[36]; }
    if (values.size() > 37) { T1Param4 = values[37]; }
    if (values.size() > 38) { T1Min4 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { T1Max4 = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { T1Code5 = values[40]; }
    if (values.size() > 41) { T1Param5 = values[41]; }
    if (values.size() > 42) { T1Min5 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { T1Max5 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { T1Code6 = values[44]; }
    if (values.size() > 45) { T1Param6 = values[45]; }
    if (values.size() > 46) { T1Min6 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { T1Max6 = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { T1Code7 = values[48]; }
    if (values.size() > 49) { T1Param7 = values[49]; }
    if (values.size() > 50) { T1Min7 = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { T1Max7 = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { eol = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { index = values[0]; }
    if (values.size() > 1) { ID = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { set = values[2]; }
    if (values.size() > 3) { disabled = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { spawnable = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 8) { item = values[8]; }
    if (values.size() > 9) { ItemName = values[9]; }
    if (values.size() > 10) { rarity = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { lvl = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { lvlreq = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { chrtransform = values[13]; }
    if (values.size() > 14) { invtransform = values[14]; }
    if (values.size() > 20) { costmult = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { costadd = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { addfunc = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { prop1 = values[23]; }
    if (values.size() > 24) { par1 = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { min1 = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { max1 = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { prop2 = values[27]; }
    if (values.size() > 28) { par2 = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { min2 = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { max2 = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { prop3 = values[31]; }
    if (values.size() > 32) { par3 = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { min3 = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { max3 = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { prop4 = values[35]; }
    if (values.size() > 36) { par4 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { min4 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { max4 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { prop5 = values[39]; }
    if (values.size() > 40) { par5 = values[40]; }
    if (values.size() > 41) { min5 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { max5 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { prop6 = values[43]; }
    if (values.size() > 44) { par6 = values[44]; }
    if (values.size() > 45) { min6 = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { max6 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { prop7 = values[47]; }
    if (values.size() > 48) { par7 = values[48]; }
    if (values.size() > 49) { min7 = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { max7 = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 59) { aprop1a = values[59]; }
    if (values.size() > 60) { apar1a = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { amin1a = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { amax1a = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { aprop1b = values[63]; }
    if (values.size() > 64) { apar1b = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 67) { aprop2a = values[67]; }
    if (values.size() > 68) { apar2a = values[68]; }
    if (values.size() > 69) { amin2a = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { amax2a = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 75) { aprop3a = values[75]; }
    if (values.size() > 76) { apar3a = values[76][0] == '\0' ? 0 : std::stoi(values[76]); }
    if (values.size() > 77) { amin3a = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { amax3a = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 83) { aprop4a = values[83]; }
    if (values.size() > 84) { apar4a = values[84][0] == '\0' ? 0 : std::stoi(values[84]); }
    if (values.size() > 85) { amin4a = values[85][0] == '\0' ? 0 : std::stoi(values[85]); }
    if (values.size() > 86) { amax4a = values[86][0] == '\0' ? 0 : std::stoi(values[86]); }
    if (values.size() > 91) { aprop5a = values[91]; }
    if (values.size() > 92) { apar5a = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { amin5a = values[93][0] == '\0' ? 0 : std::stoi(values[93]); }
    if (values.size() > 94) { amax5a = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 100) { eol = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { index = values[0]; }
    if (values.size() > 1) { name = values[1]; }
    if (values.size() > 2) { version = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { PCode2a = values[3]; }
    if (values.size() > 4) { PParam2a = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { PMin2a = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { PMax2a = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { PCode2b = values[7]; }
    if (values.size() > 8) { PParam2b = values[8]; }
    if (values.size() > 9) { PMin2b = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { PMax2b = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { PCode3a = values[11]; }
    if (values.size() > 12) { PParam3a = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { PMin3a = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { PMax3a = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { PCode3b = values[15]; }
    if (values.size() > 16) { PParam3b = values[16]; }
    if (values.size() > 17) { PMin3b = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { PMax3b = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { PCode4a = values[19]; }
    if (values.size() > 21) { PMin4a = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { PMax4a = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { PCode4b = values[23]; }
    if (values.size() > 24) { PParam4b = values[24]; }
    if (values.size() > 25) { PMin4b = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { PMax4b = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { PCode5a = values[27]; }
    if (values.size() > 29) { PMin5a = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { PMax5a = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 35) { FCode1 = values[35]; }
    if (values.size() > 36) { FParam1 = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { FMin1 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { FMax1 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { FCode2 = values[39]; }
    if (values.size() > 40) { FParam2 = values[40]; }
    if (values.size() > 41) { FMin2 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { FMax2 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { FCode3 = values[43]; }
    if (values.size() > 44) { FParam3 = values[44][0] == '\0' ? 0 : std::stoi(values[44]); }
    if (values.size() > 45) { FMin3 = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { FMax3 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { FCode4 = values[47]; }
    if (values.size() > 48) { FParam4 = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { FMin4 = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { FMax4 = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { FCode5 = values[51]; }
    if (values.size() > 52) { FParam5 = values[52]; }
    if (values.size() > 53) { FMin5 = values[53][0] == '\0' ? 0 : std::stoi(values[53]); }
    if (values.size() > 54) { FMax5 = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { FCode6 = values[55]; }
    if (values.size() > 56) { FParam6 = values[56]; }
    if (values.size() > 57) { FMin6 = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { FMax6 = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { FCode7 = values[59]; }
    if (values.size() > 60) { FParam7 = values[60]; }
    if (values.size() > 61) { FMin7 = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { FMax7 = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { FCode8 = values[63]; }
    if (values.size() > 65) { FMin8 = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { FMax8 = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 68) { eol = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Name = values[0]; }
    if (values.size() > 1) { ShrineType = values[1]; }
    if (values.size() > 2) { Effect = values[2]; }
    if (values.size() > 3) { Code = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Arg0 = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Arg1 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Durationinframes = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { resettimeinminutes = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { rarity = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { StringName = values[9]; }
    if (values.size() > 10) { StringPhrase = values[10]; }
    if (values.size() > 11) { effectclass = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { LevelMin = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { skilldesc = values[0]; }
    if (values.size() > 1) { SkillPage = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { SkillRow = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { SkillColumn = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { ListRow = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { IconCel = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { HireableIconCel = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { strname = values[7]; }
    if (values.size() > 8) { strshort = values[8]; }
    if (values.size() > 9) { strlong = values[9]; }
    if (values.size() > 10) { stralt = values[10]; }
    if (values.size() > 11) { descdam = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
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
    if (values.size() > 23) { descatt = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { descmissile1 = values[24]; }
    if (values.size() > 25) { descmissile2 = values[25]; }
    if (values.size() > 26) { descmissile3 = values[26]; }
    if (values.size() > 27) { descline1 = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { desctexta1 = values[28]; }
    if (values.size() > 29) { desctextb1 = values[29]; }
    if (values.size() > 30) { desccalca1 = values[30]; }
    if (values.size() > 31) { desccalcb1 = values[31]; }
    if (values.size() > 32) { descline2 = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { desctexta2 = values[33]; }
    if (values.size() > 34) { desctextb2 = values[34]; }
    if (values.size() > 35) { desccalca2 = values[35]; }
    if (values.size() > 36) { desccalcb2 = values[36]; }
    if (values.size() > 37) { descline3 = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { desctexta3 = values[38]; }
    if (values.size() > 39) { desctextb3 = values[39]; }
    if (values.size() > 40) { desccalca3 = values[40]; }
    if (values.size() > 41) { desccalcb3 = values[41]; }
    if (values.size() > 42) { descline4 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { desctexta4 = values[43]; }
    if (values.size() > 44) { desctextb4 = values[44]; }
    if (values.size() > 45) { desccalca4 = values[45]; }
    if (values.size() > 46) { desccalcb4 = values[46]; }
    if (values.size() > 47) { descline5 = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { desctexta5 = values[48]; }
    if (values.size() > 49) { desctextb5 = values[49]; }
    if (values.size() > 50) { desccalca5 = values[50]; }
    if (values.size() > 51) { desccalcb5 = values[51]; }
    if (values.size() > 52) { descline6 = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { desctexta6 = values[53]; }
    if (values.size() > 55) { desccalca6 = values[55]; }
    if (values.size() > 56) { desccalcb6 = values[56]; }
    if (values.size() > 57) { dsc2line1 = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { dsc2texta1 = values[58]; }
    if (values.size() > 59) { dsc2textb1 = values[59]; }
    if (values.size() > 60) { dsc2calca1 = values[60]; }
    if (values.size() > 61) { dsc2calcb1 = values[61]; }
    if (values.size() > 62) { dsc2line2 = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { dsc2texta2 = values[63]; }
    if (values.size() > 64) { dsc2textb2 = values[64]; }
    if (values.size() > 65) { dsc2calca2 = values[65]; }
    if (values.size() > 66) { dsc2calcb2 = values[66]; }
    if (values.size() > 67) { dsc2line3 = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { dsc2texta3 = values[68]; }
    if (values.size() > 69) { dsc2textb3 = values[69]; }
    if (values.size() > 70) { dsc2calca3 = values[70]; }
    if (values.size() > 71) { dsc2calcb3 = values[71]; }
    if (values.size() > 72) { dsc2line4 = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { dsc2texta4 = values[73]; }
    if (values.size() > 75) { dsc2calca4 = values[75]; }
    if (values.size() > 77) { dsc2line5 = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { dsc2texta5 = values[78]; }
    if (values.size() > 80) { dsc2calca5 = values[80]; }
    if (values.size() > 82) { dsc3line1 = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }
    if (values.size() > 83) { dsc3texta1 = values[83]; }
    if (values.size() > 84) { dsc3textb1 = values[84]; }
    if (values.size() > 85) { dsc3calca1 = values[85][0] == '\0' ? 0 : std::stoi(values[85]); }
    if (values.size() > 87) { dsc3line2 = values[87][0] == '\0' ? 0 : std::stoi(values[87]); }
    if (values.size() > 88) { dsc3texta2 = values[88]; }
    if (values.size() > 89) { dsc3textb2 = values[89]; }
    if (values.size() > 90) { dsc3calca2 = values[90]; }
    if (values.size() > 91) { dsc3calcb2 = values[91]; }
    if (values.size() > 92) { dsc3line3 = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { dsc3texta3 = values[93]; }
    if (values.size() > 94) { dsc3textb3 = values[94]; }
    if (values.size() > 95) { dsc3calca3 = values[95]; }
    if (values.size() > 96) { dsc3calcb3 = values[96]; }
    if (values.size() > 97) { dsc3line4 = values[97][0] == '\0' ? 0 : std::stoi(values[97]); }
    if (values.size() > 98) { dsc3texta4 = values[98]; }
    if (values.size() > 99) { dsc3textb4 = values[99]; }
    if (values.size() > 100) { dsc3calca4 = values[100]; }
    if (values.size() > 101) { dsc3calcb4 = values[101][0] == '\0' ? 0 : std::stoi(values[101]); }
    if (values.size() > 102) { dsc3line5 = values[102][0] == '\0' ? 0 : std::stoi(values[102]); }
    if (values.size() > 103) { dsc3texta5 = values[103]; }
    if (values.size() > 104) { dsc3textb5 = values[104]; }
    if (values.size() > 105) { dsc3calca5 = values[105]; }
    if (values.size() > 107) { dsc3line6 = values[107][0] == '\0' ? 0 : std::stoi(values[107]); }
    if (values.size() > 108) { dsc3texta6 = values[108]; }
    if (values.size() > 109) { dsc3textb6 = values[109]; }
    if (values.size() > 110) { dsc3calca6 = values[110]; }
    if (values.size() > 112) { dsc3line7 = values[112][0] == '\0' ? 0 : std::stoi(values[112]); }
    if (values.size() > 113) { dsc3texta7 = values[113]; }
    if (values.size() > 117) { itemproctext = values[117]; }
    if (values.size() > 118) { itemprocdesclinecount = values[118][0] == '\0' ? 0 : std::stoi(values[118]); }
    if (values.size() > 119) { eol = values[119][0] == '\0' ? 0 : std::stoi(values[119]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { skill = values[0]; }
    if (values.size() > 1) { Id = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { charclass = values[2]; }
    if (values.size() > 3) { skilldesc = values[3]; }
    if (values.size() > 4) { srvstfunc = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { srvdofunc = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { srvstopfunc = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { prgstack = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { srvprgfunc1 = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { srvprgfunc2 = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { srvprgfunc3 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { prgcalc1 = values[11]; }
    if (values.size() > 12) { prgcalc2 = values[12]; }
    if (values.size() > 13) { prgcalc3 = values[13]; }
    if (values.size() > 14) { prgdam = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { srvmissile = values[15]; }
    if (values.size() > 16) { decquant = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { lob = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { srvmissilea = values[18]; }
    if (values.size() > 19) { srvmissileb = values[19]; }
    if (values.size() > 20) { srvmissilec = values[20]; }
    if (values.size() > 22) { srvoverlay = values[22]; }
    if (values.size() > 23) { aurafilter = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
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
    if (values.size() > 41) { auraeventfunc1 = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { auraevent2 = values[42]; }
    if (values.size() > 43) { auraeventfunc2 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { auraevent3 = values[44]; }
    if (values.size() > 45) { auraeventfunc3 = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
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
    if (values.size() > 94) { sumumod = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 95) { sumoverlay = values[95]; }
    if (values.size() > 96) { stsuccessonly = values[96][0] == '\0' ? 0 : std::stoi(values[96]); }
    if (values.size() > 97) { stsound = values[97]; }
    if (values.size() > 98) { stsoundclass = values[98]; }
    if (values.size() > 99) { stsounddelay = values[99][0] == '\0' ? 0 : std::stoi(values[99]); }
    if (values.size() > 100) { weaponsnd = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
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
    if (values.size() > 111) { cltstfunc = values[111][0] == '\0' ? 0 : std::stoi(values[111]); }
    if (values.size() > 112) { cltdofunc = values[112]; }
    if (values.size() > 113) { cltstopfunc = values[113][0] == '\0' ? 0 : std::stoi(values[113]); }
    if (values.size() > 114) { cltprgfunc1 = values[114][0] == '\0' ? 0 : std::stoi(values[114]); }
    if (values.size() > 115) { cltprgfunc2 = values[115][0] == '\0' ? 0 : std::stoi(values[115]); }
    if (values.size() > 116) { cltprgfunc3 = values[116][0] == '\0' ? 0 : std::stoi(values[116]); }
    if (values.size() > 117) { cltmissile = values[117]; }
    if (values.size() > 118) { cltmissilea = values[118]; }
    if (values.size() > 119) { cltmissileb = values[119]; }
    if (values.size() > 120) { cltmissilec = values[120]; }
    if (values.size() > 121) { cltmissiled = values[121]; }
    if (values.size() > 122) { cltcalc1 = values[122]; }
    if (values.size() > 123) { cltcalc1desc = values[123]; }
    if (values.size() > 124) { cltcalc2 = values[124]; }
    if (values.size() > 125) { cltcalc2desc = values[125]; }
    if (values.size() > 126) { cltcalc3 = values[126][0] == '\0' ? 0 : std::stoi(values[126]); }
    if (values.size() > 127) { cltcalc3desc = values[127]; }
    if (values.size() > 128) { warp = values[128][0] == '\0' ? 0 : std::stoi(values[128]); }
    if (values.size() > 129) { immediate = values[129][0] == '\0' ? 0 : std::stoi(values[129]); }
    if (values.size() > 130) { enhanceable = values[130][0] == '\0' ? 0 : std::stoi(values[130]); }
    if (values.size() > 131) { attackrank = values[131][0] == '\0' ? 0 : std::stoi(values[131]); }
    if (values.size() > 132) { noammo = values[132][0] == '\0' ? 0 : std::stoi(values[132]); }
    if (values.size() > 133) { range = values[133]; }
    if (values.size() > 134) { weapsel = values[134][0] == '\0' ? 0 : std::stoi(values[134]); }
    if (values.size() > 136) { itypea1 = values[136]; }
    if (values.size() > 137) { itypea2 = values[137]; }
    if (values.size() > 139) { etypea1 = values[139]; }
    if (values.size() > 141) { itypeb1 = values[141]; }
    if (values.size() > 146) { anim = values[146]; }
    if (values.size() > 147) { seqtrans = values[147]; }
    if (values.size() > 148) { monanim = values[148]; }
    if (values.size() > 149) { seqnum = values[149][0] == '\0' ? 0 : std::stoi(values[149]); }
    if (values.size() > 150) { seqinput = values[150][0] == '\0' ? 0 : std::stoi(values[150]); }
    if (values.size() > 151) { durability = values[151][0] == '\0' ? 0 : std::stoi(values[151]); }
    if (values.size() > 152) { UseAttackRate = values[152][0] == '\0' ? 0 : std::stoi(values[152]); }
    if (values.size() > 153) { LineOfSight = values[153][0] == '\0' ? 0 : std::stoi(values[153]); }
    if (values.size() > 154) { TargetableOnly = values[154][0] == '\0' ? 0 : std::stoi(values[154]); }
    if (values.size() > 155) { SearchEnemyXY = values[155][0] == '\0' ? 0 : std::stoi(values[155]); }
    if (values.size() > 156) { SearchEnemyNear = values[156][0] == '\0' ? 0 : std::stoi(values[156]); }
    if (values.size() > 157) { SearchOpenXY = values[157][0] == '\0' ? 0 : std::stoi(values[157]); }
    if (values.size() > 158) { SelectProc = values[158][0] == '\0' ? 0 : std::stoi(values[158]); }
    if (values.size() > 159) { TargetCorpse = values[159][0] == '\0' ? 0 : std::stoi(values[159]); }
    if (values.size() > 160) { TargetPet = values[160][0] == '\0' ? 0 : std::stoi(values[160]); }
    if (values.size() > 161) { TargetAlly = values[161][0] == '\0' ? 0 : std::stoi(values[161]); }
    if (values.size() > 162) { TargetItem = values[162][0] == '\0' ? 0 : std::stoi(values[162]); }
    if (values.size() > 163) { AttackNoMana = values[163][0] == '\0' ? 0 : std::stoi(values[163]); }
    if (values.size() > 164) { TgtPlaceCheck = values[164][0] == '\0' ? 0 : std::stoi(values[164]); }
    if (values.size() > 165) { KeepCursorStateOnKill = values[165][0] == '\0' ? 0 : std::stoi(values[165]); }
    if (values.size() > 166) { ContinueCastUnselected = values[166][0] == '\0' ? 0 : std::stoi(values[166]); }
    if (values.size() > 167) { ClearSelectedOnHold = values[167][0] == '\0' ? 0 : std::stoi(values[167]); }
    if (values.size() > 168) { ItemEffect = values[168][0] == '\0' ? 0 : std::stoi(values[168]); }
    if (values.size() > 169) { ItemCltEffect = values[169][0] == '\0' ? 0 : std::stoi(values[169]); }
    if (values.size() > 170) { ItemTgtDo = values[170][0] == '\0' ? 0 : std::stoi(values[170]); }
    if (values.size() > 171) { ItemTarget = values[171][0] == '\0' ? 0 : std::stoi(values[171]); }
    if (values.size() > 172) { ItemUseRestrict = values[172][0] == '\0' ? 0 : std::stoi(values[172]); }
    if (values.size() > 173) { ItemCheckStart = values[173][0] == '\0' ? 0 : std::stoi(values[173]); }
    if (values.size() > 174) { ItemCltCheckStart = values[174][0] == '\0' ? 0 : std::stoi(values[174]); }
    if (values.size() > 175) { ItemCastSound = values[175]; }
    if (values.size() > 176) { ItemCastOverlay = values[176]; }
    if (values.size() > 178) { reqlevel = values[178][0] == '\0' ? 0 : std::stoi(values[178]); }
    if (values.size() > 179) { maxlvl = values[179][0] == '\0' ? 0 : std::stoi(values[179]); }
    if (values.size() > 184) { reqskill1 = values[184]; }
    if (values.size() > 185) { reqskill2 = values[185]; }
    if (values.size() > 187) { restrict = values[187][0] == '\0' ? 0 : std::stoi(values[187]); }
    if (values.size() > 188) { State1 = values[188]; }
    if (values.size() > 189) { State2 = values[189]; }
    if (values.size() > 191) { localdelay = values[191][0] == '\0' ? 0 : std::stoi(values[191]); }
    if (values.size() > 192) { globaldelay = values[192][0] == '\0' ? 0 : std::stoi(values[192]); }
    if (values.size() > 193) { leftskill = values[193][0] == '\0' ? 0 : std::stoi(values[193]); }
    if (values.size() > 194) { rightskill = values[194][0] == '\0' ? 0 : std::stoi(values[194]); }
    if (values.size() > 195) { repeat = values[195][0] == '\0' ? 0 : std::stoi(values[195]); }
    if (values.size() > 196) { alwayshit = values[196][0] == '\0' ? 0 : std::stoi(values[196]); }
    if (values.size() > 197) { usemanaondo = values[197][0] == '\0' ? 0 : std::stoi(values[197]); }
    if (values.size() > 198) { startmana = values[198][0] == '\0' ? 0 : std::stoi(values[198]); }
    if (values.size() > 199) { minmana = values[199][0] == '\0' ? 0 : std::stoi(values[199]); }
    if (values.size() > 200) { manashift = values[200][0] == '\0' ? 0 : std::stoi(values[200]); }
    if (values.size() > 201) { mana = values[201][0] == '\0' ? 0 : std::stoi(values[201]); }
    if (values.size() > 202) { lvlmana = values[202][0] == '\0' ? 0 : std::stoi(values[202]); }
    if (values.size() > 203) { interrupt = values[203][0] == '\0' ? 0 : std::stoi(values[203]); }
    if (values.size() > 204) { InTown = values[204][0] == '\0' ? 0 : std::stoi(values[204]); }
    if (values.size() > 205) { aura = values[205][0] == '\0' ? 0 : std::stoi(values[205]); }
    if (values.size() > 206) { periodic = values[206][0] == '\0' ? 0 : std::stoi(values[206]); }
    if (values.size() > 207) { perdelay = values[207]; }
    if (values.size() > 208) { finishing = values[208][0] == '\0' ? 0 : std::stoi(values[208]); }
    if (values.size() > 209) { prgchargestocast = values[209][0] == '\0' ? 0 : std::stoi(values[209]); }
    if (values.size() > 210) { prgchargesconsumed = values[210][0] == '\0' ? 0 : std::stoi(values[210]); }
    if (values.size() > 211) { passive = values[211][0] == '\0' ? 0 : std::stoi(values[211]); }
    if (values.size() > 212) { progressive = values[212][0] == '\0' ? 0 : std::stoi(values[212]); }
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
    if (values.size() > 234) { Param1 = values[234][0] == '\0' ? 0 : std::stoi(values[234]); }
    if (values.size() > 235) { Param1Description = values[235]; }
    if (values.size() > 236) { Param2 = values[236][0] == '\0' ? 0 : std::stoi(values[236]); }
    if (values.size() > 237) { Param2Description = values[237]; }
    if (values.size() > 238) { Param3 = values[238][0] == '\0' ? 0 : std::stoi(values[238]); }
    if (values.size() > 239) { Param3Description = values[239]; }
    if (values.size() > 240) { Param4 = values[240][0] == '\0' ? 0 : std::stoi(values[240]); }
    if (values.size() > 241) { Param4Description = values[241]; }
    if (values.size() > 242) { Param5 = values[242][0] == '\0' ? 0 : std::stoi(values[242]); }
    if (values.size() > 243) { Param5Description = values[243]; }
    if (values.size() > 244) { Param6 = values[244][0] == '\0' ? 0 : std::stoi(values[244]); }
    if (values.size() > 245) { Param6Description = values[245]; }
    if (values.size() > 246) { Param7 = values[246][0] == '\0' ? 0 : std::stoi(values[246]); }
    if (values.size() > 247) { Param7Description = values[247]; }
    if (values.size() > 248) { Param8 = values[248][0] == '\0' ? 0 : std::stoi(values[248]); }
    if (values.size() > 249) { Param8Description = values[249]; }
    if (values.size() > 250) { Param9 = values[250][0] == '\0' ? 0 : std::stoi(values[250]); }
    if (values.size() > 251) { Param9Description = values[251]; }
    if (values.size() > 252) { Param10 = values[252][0] == '\0' ? 0 : std::stoi(values[252]); }
    if (values.size() > 253) { Param10Description2 = values[253]; }
    if (values.size() > 254) { Param11 = values[254][0] == '\0' ? 0 : std::stoi(values[254]); }
    if (values.size() > 255) { Param11Description = values[255]; }
    if (values.size() > 256) { Param12 = values[256][0] == '\0' ? 0 : std::stoi(values[256]); }
    if (values.size() > 257) { Param12Description = values[257]; }
    if (values.size() > 274) { InGame = values[274][0] == '\0' ? 0 : std::stoi(values[274]); }
    if (values.size() > 275) { ToHit = values[275][0] == '\0' ? 0 : std::stoi(values[275]); }
    if (values.size() > 276) { LevToHit = values[276][0] == '\0' ? 0 : std::stoi(values[276]); }
    if (values.size() > 277) { ToHitCalc = values[277]; }
    if (values.size() > 278) { ResultFlags = values[278][0] == '\0' ? 0 : std::stoi(values[278]); }
    if (values.size() > 279) { HitFlags = values[279][0] == '\0' ? 0 : std::stoi(values[279]); }
    if (values.size() > 280) { HitClass = values[280][0] == '\0' ? 0 : std::stoi(values[280]); }
    if (values.size() > 281) { Kick = values[281][0] == '\0' ? 0 : std::stoi(values[281]); }
    if (values.size() > 282) { HitShift = values[282][0] == '\0' ? 0 : std::stoi(values[282]); }
    if (values.size() > 283) { SrcDam = values[283][0] == '\0' ? 0 : std::stoi(values[283]); }
    if (values.size() > 284) { MinDam = values[284][0] == '\0' ? 0 : std::stoi(values[284]); }
    if (values.size() > 285) { MinLevDam1 = values[285][0] == '\0' ? 0 : std::stoi(values[285]); }
    if (values.size() > 286) { MinLevDam2 = values[286][0] == '\0' ? 0 : std::stoi(values[286]); }
    if (values.size() > 287) { MinLevDam3 = values[287][0] == '\0' ? 0 : std::stoi(values[287]); }
    if (values.size() > 288) { MinLevDam4 = values[288][0] == '\0' ? 0 : std::stoi(values[288]); }
    if (values.size() > 289) { MinLevDam5 = values[289][0] == '\0' ? 0 : std::stoi(values[289]); }
    if (values.size() > 290) { MaxDam = values[290][0] == '\0' ? 0 : std::stoi(values[290]); }
    if (values.size() > 291) { MaxLevDam1 = values[291][0] == '\0' ? 0 : std::stoi(values[291]); }
    if (values.size() > 292) { MaxLevDam2 = values[292][0] == '\0' ? 0 : std::stoi(values[292]); }
    if (values.size() > 293) { MaxLevDam3 = values[293][0] == '\0' ? 0 : std::stoi(values[293]); }
    if (values.size() > 294) { MaxLevDam4 = values[294][0] == '\0' ? 0 : std::stoi(values[294]); }
    if (values.size() > 295) { MaxLevDam5 = values[295][0] == '\0' ? 0 : std::stoi(values[295]); }
    if (values.size() > 296) { DmgSymPerCalc = values[296]; }
    if (values.size() > 297) { EType = values[297]; }
    if (values.size() > 298) { EMin = values[298][0] == '\0' ? 0 : std::stoi(values[298]); }
    if (values.size() > 299) { EMinLev1 = values[299][0] == '\0' ? 0 : std::stoi(values[299]); }
    if (values.size() > 300) { EMinLev2 = values[300][0] == '\0' ? 0 : std::stoi(values[300]); }
    if (values.size() > 301) { EMinLev3 = values[301][0] == '\0' ? 0 : std::stoi(values[301]); }
    if (values.size() > 302) { EMinLev4 = values[302][0] == '\0' ? 0 : std::stoi(values[302]); }
    if (values.size() > 303) { EMinLev5 = values[303][0] == '\0' ? 0 : std::stoi(values[303]); }
    if (values.size() > 304) { EMax = values[304][0] == '\0' ? 0 : std::stoi(values[304]); }
    if (values.size() > 305) { EMaxLev1 = values[305][0] == '\0' ? 0 : std::stoi(values[305]); }
    if (values.size() > 306) { EMaxLev2 = values[306][0] == '\0' ? 0 : std::stoi(values[306]); }
    if (values.size() > 307) { EMaxLev3 = values[307][0] == '\0' ? 0 : std::stoi(values[307]); }
    if (values.size() > 308) { EMaxLev4 = values[308][0] == '\0' ? 0 : std::stoi(values[308]); }
    if (values.size() > 309) { EMaxLev5 = values[309][0] == '\0' ? 0 : std::stoi(values[309]); }
    if (values.size() > 310) { EDmgSymPerCalc = values[310]; }
    if (values.size() > 311) { ELen = values[311][0] == '\0' ? 0 : std::stoi(values[311]); }
    if (values.size() > 312) { ELevLen1 = values[312][0] == '\0' ? 0 : std::stoi(values[312]); }
    if (values.size() > 313) { ELevLen2 = values[313][0] == '\0' ? 0 : std::stoi(values[313]); }
    if (values.size() > 314) { ELevLen3 = values[314][0] == '\0' ? 0 : std::stoi(values[314]); }
    if (values.size() > 315) { ELenSymPerCalc = values[315]; }
    if (values.size() > 316) { aitype = values[316][0] == '\0' ? 0 : std::stoi(values[316]); }
    if (values.size() > 317) { aibonus = values[317][0] == '\0' ? 0 : std::stoi(values[317]); }
    if (values.size() > 318) { costmult = values[318][0] == '\0' ? 0 : std::stoi(values[318]); }
    if (values.size() > 319) { costadd = values[319][0] == '\0' ? 0 : std::stoi(values[319]); }
    if (values.size() > 320) { eol = values[320][0] == '\0' ? 0 : std::stoi(values[320]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Handle = values[0]; }
    if (values.size() > 1) { Index = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Song = values[2]; }
    if (values.size() > 3) { DayAmbience = values[3]; }
    if (values.size() > 4) { HDDayAmbience = values[4]; }
    if (values.size() > 5) { NightAmbience = values[5]; }
    if (values.size() > 6) { HDNightAmbience = values[6]; }
    if (values.size() > 7) { DayEvent = values[7]; }
    if (values.size() > 8) { HDDayEvent = values[8]; }
    if (values.size() > 9) { NightEvent = values[9]; }
    if (values.size() > 10) { HDNightEvent = values[10]; }
    if (values.size() > 11) { EventDelay = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { HDEventDelay = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Indoors = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { Material1 = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { HDMaterial1 = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { Material2 = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { HDMaterial2 = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { SFXEAXEnviron = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { SFXEAXRoomVol = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { SFXEAXRoomHF = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { SFXEAXDecayTime = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { SFXEAXDecayHF = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { SFXEAXReflect = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { SFXEAXReflectDelay = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { SFXEAXReverb = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { SFXEAXRevDelay = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { VOXEAXEnviron = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { VOXEAXRoomVol = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { VOXEAXRoomHF = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { VOXEAXDecayTime = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { VOXEAXDecayHF = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { VOXEAXReflect = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { VOXEAXReflectDelay = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { VOXEAXReverb = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { VOXEAXRevDelay = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { InheritEnvrionment = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Sound = values[0]; }
    if (values.size() > 1) { Index = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { Redirect = values[2]; }
    if (values.size() > 3) { Channel = values[3]; }
    if (values.size() > 4) { FileName = values[4]; }
    if (values.size() > 5) { IsLocal = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { IsMusic = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { IsAmbientScene = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { IsAmbientEvent = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { IsUI = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { VolumeMin = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { VolumeMax = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { PitchMin = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { PitchMax = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { GroupSize = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { GroupWeight = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { Loop = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { FadeIn = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { FadeOut = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { DeferInst = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { StopInst = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { Duration = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { Compound = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { Falloff = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { LFEMix = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { _3dSpread = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { Priority = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { Stream = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { Is2D = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { Tracking = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { Solo = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { MusicVol = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { Block1 = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { Block2 = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { Block3 = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { HDOptOut = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { Delay = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { state = values[0]; }
    if (values.size() > 1) { ID = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { group = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { remhit = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { nosend = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { transform = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { aura = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { curable = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { curse = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { active = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { restrict = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { disguise = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { attblue = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { damblue = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { armblue = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { rfblue = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { rlblue = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { rcblue = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { stambarblue = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { rpblue = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 21) { damred = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { armred = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { rfred = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { rlred = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { rcred = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { rpred = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { exp = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { plrstaydeath = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { monstaydeath = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { bossstaydeath = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { hide = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { hidedead = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { shatter = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { udead = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { life = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { green = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { pgsv = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { nooverlays = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { noclear = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { bossinv = values[40][0] == '\0' ? 0 : std::stoi(values[40]); }
    if (values.size() > 41) { meleeonly = values[41][0] == '\0' ? 0 : std::stoi(values[41]); }
    if (values.size() > 42) { notondead = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { overlay1 = values[43]; }
    if (values.size() > 44) { overlay2 = values[44]; }
    if (values.size() > 45) { overlay3 = values[45]; }
    if (values.size() > 46) { overlay4 = values[46]; }
    if (values.size() > 47) { pgsvoverlay = values[47]; }
    if (values.size() > 48) { castoverlay = values[48]; }
    if (values.size() > 49) { removerlay = values[49]; }
    if (values.size() > 50) { stat = values[50]; }
    if (values.size() > 51) { setfunc = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { remfunc = values[52][0] == '\0' ? 0 : std::stoi(values[52]); }
    if (values.size() > 53) { missile = values[53]; }
    if (values.size() > 54) { skill = values[54]; }
    if (values.size() > 55) { itemtype = values[55]; }
    if (values.size() > 56) { itemtrans = values[56]; }
    if (values.size() > 57) { colorpri = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { colorshift = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { lightr = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { lightg = values[60][0] == '\0' ? 0 : std::stoi(values[60]); }
    if (values.size() > 61) { lightb = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { onsound = values[62]; }
    if (values.size() > 63) { offsound = values[63]; }
    if (values.size() > 64) { gfxtype = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { gfxclass = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { cltevent = values[66]; }
    if (values.size() > 67) { clteventfunc = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { cltactivefunc = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { srvactivefunc = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 71) { sunderfull = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { sunderresreduce = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 74) { eol = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { Superunique = values[0]; }
    if (values.size() > 1) { Name = values[1]; }
    if (values.size() > 2) { Class = values[2]; }
    if (values.size() > 3) { hcIdx = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { MonSound = values[4]; }
    if (values.size() > 5) { Mod1 = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Mod2 = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Mod3 = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { MinGrp = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { MaxGrp = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 10) { AutoPos = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Stacks = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { Replaceable = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Utrans = values[13][0] == '\0' ? 0 : std::stoi(values[13]); }
    if (values.size() > 14) { UtransN = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { UtransH = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { TC = values[16]; }
    if (values.size() > 17) { TCDesecrated = values[17]; }
    if (values.size() > 18) { TCN = values[18]; }
    if (values.size() > 19) { TCNDesecrated = values[19]; }
    if (values.size() > 20) { TCH = values[20]; }
    if (values.size() > 21) { TCHDesecrated = values[21]; }
    if (values.size() > 22) { eol = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { TreasureClass = values[0]; }
    if (values.size() > 1) { group = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { level = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { Picks = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { Unique = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 5) { Set = values[5][0] == '\0' ? 0 : std::stoi(values[5]); }
    if (values.size() > 6) { Rare = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { Magic = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { NoDrop = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { Item1 = values[9]; }
    if (values.size() > 10) { Prob1 = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { Item2 = values[11]; }
    if (values.size() > 12) { Prob2 = values[12][0] == '\0' ? 0 : std::stoi(values[12]); }
    if (values.size() > 13) { Item3 = values[13]; }
    if (values.size() > 14) { Prob3 = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { Item4 = values[15]; }
    if (values.size() > 16) { Prob4 = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { Item5 = values[17]; }
    if (values.size() > 18) { Prob5 = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { Item6 = values[19]; }
    if (values.size() > 20) { Prob6 = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { Item7 = values[21]; }
    if (values.size() > 22) { Prob7 = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { Item8 = values[23]; }
    if (values.size() > 24) { Prob8 = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { Item9 = values[25]; }
    if (values.size() > 26) { Prob9 = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 29) { ItemProbSum = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { ItemProbTotal = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { TreasureClassDropChance = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 33) { firstLadderSeason = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { lastLadderSeason = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { noAlwaysSpawn = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 38) { eol = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { index = values[0]; }
    if (values.size() > 1) { ID = values[1][0] == '\0' ? 0 : std::stoi(values[1]); }
    if (values.size() > 2) { version = values[2][0] == '\0' ? 0 : std::stoi(values[2]); }
    if (values.size() > 3) { disabled = values[3][0] == '\0' ? 0 : std::stoi(values[3]); }
    if (values.size() > 4) { spawnable = values[4][0] == '\0' ? 0 : std::stoi(values[4]); }
    if (values.size() > 6) { firstLadderSeason = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 7) { lastLadderSeason = values[7][0] == '\0' ? 0 : std::stoi(values[7]); }
    if (values.size() > 8) { rarity = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 10) { lvl = values[10][0] == '\0' ? 0 : std::stoi(values[10]); }
    if (values.size() > 11) { lvlreq = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { code = values[12]; }
    if (values.size() > 13) { ItemName = values[13]; }
    if (values.size() > 14) { carry1 = values[14][0] == '\0' ? 0 : std::stoi(values[14]); }
    if (values.size() > 15) { costmult = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { costadd = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { chrtransform = values[17]; }
    if (values.size() > 18) { invtransform = values[18]; }
    if (values.size() > 19) { flippyfile = values[19]; }
    if (values.size() > 20) { invfile = values[20]; }
    if (values.size() > 21) { dropsound = values[21]; }
    if (values.size() > 22) { dropsfxframe = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { usesound = values[23]; }
    if (values.size() > 24) { prop1 = values[24]; }
    if (values.size() > 25) { par1 = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { min1 = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { max1 = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { prop2 = values[28]; }
    if (values.size() > 29) { par2 = values[29]; }
    if (values.size() > 30) { min2 = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { max2 = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { prop3 = values[32]; }
    if (values.size() > 33) { par3 = values[33]; }
    if (values.size() > 34) { min3 = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { max3 = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { prop4 = values[36]; }
    if (values.size() > 37) { par4 = values[37]; }
    if (values.size() > 38) { min4 = values[38][0] == '\0' ? 0 : std::stoi(values[38]); }
    if (values.size() > 39) { max4 = values[39][0] == '\0' ? 0 : std::stoi(values[39]); }
    if (values.size() > 40) { prop5 = values[40]; }
    if (values.size() > 41) { par5 = values[41]; }
    if (values.size() > 42) { min5 = values[42][0] == '\0' ? 0 : std::stoi(values[42]); }
    if (values.size() > 43) { max5 = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { prop6 = values[44]; }
    if (values.size() > 45) { par6 = values[45]; }
    if (values.size() > 46) { min6 = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { max6 = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { prop7 = values[48]; }
    if (values.size() > 49) { par7 = values[49]; }
    if (values.size() > 50) { min7 = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { max7 = values[51][0] == '\0' ? 0 : std::stoi(values[51]); }
    if (values.size() > 52) { prop8 = values[52]; }
    if (values.size() > 53) { par8 = values[53]; }
    if (values.size() > 54) { min8 = values[54][0] == '\0' ? 0 : std::stoi(values[54]); }
    if (values.size() > 55) { max8 = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { prop9 = values[56]; }
    if (values.size() > 57) { par9 = values[57]; }
    if (values.size() > 58) { min9 = values[58][0] == '\0' ? 0 : std::stoi(values[58]); }
    if (values.size() > 59) { max9 = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { prop10 = values[60]; }
    if (values.size() > 61) { par10 = values[61]; }
    if (values.size() > 62) { min10 = values[62][0] == '\0' ? 0 : std::stoi(values[62]); }
    if (values.size() > 63) { max10 = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 72) { diablocloneweight = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { eol = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

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
    std::vector<std::string> values;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, '\t')) {
      values.push_back(value);
    }

    if (values.size() > 0) { name = values[0]; }
    if (values.size() > 1) { type = values[1]; }
    if (values.size() > 3) { code = values[3]; }
    if (values.size() > 4) { alternategfx = values[4]; }
    if (values.size() > 5) { namestr = values[5]; }
    if (values.size() > 6) { version = values[6][0] == '\0' ? 0 : std::stoi(values[6]); }
    if (values.size() > 8) { rarity = values[8][0] == '\0' ? 0 : std::stoi(values[8]); }
    if (values.size() > 9) { spawnable = values[9][0] == '\0' ? 0 : std::stoi(values[9]); }
    if (values.size() > 11) { Transmogrify = values[11][0] == '\0' ? 0 : std::stoi(values[11]); }
    if (values.size() > 12) { TMogType = values[12]; }
    if (values.size() > 15) { mindam = values[15][0] == '\0' ? 0 : std::stoi(values[15]); }
    if (values.size() > 16) { maxdam = values[16][0] == '\0' ? 0 : std::stoi(values[16]); }
    if (values.size() > 17) { _1or2handed = values[17][0] == '\0' ? 0 : std::stoi(values[17]); }
    if (values.size() > 18) { _2handed = values[18][0] == '\0' ? 0 : std::stoi(values[18]); }
    if (values.size() > 19) { _2handmindam = values[19][0] == '\0' ? 0 : std::stoi(values[19]); }
    if (values.size() > 20) { _2handmaxdam = values[20][0] == '\0' ? 0 : std::stoi(values[20]); }
    if (values.size() > 21) { minmisdam = values[21][0] == '\0' ? 0 : std::stoi(values[21]); }
    if (values.size() > 22) { maxmisdam = values[22][0] == '\0' ? 0 : std::stoi(values[22]); }
    if (values.size() > 23) { rangeadder = values[23][0] == '\0' ? 0 : std::stoi(values[23]); }
    if (values.size() > 24) { speed = values[24][0] == '\0' ? 0 : std::stoi(values[24]); }
    if (values.size() > 25) { StrBonus = values[25][0] == '\0' ? 0 : std::stoi(values[25]); }
    if (values.size() > 26) { DexBonus = values[26][0] == '\0' ? 0 : std::stoi(values[26]); }
    if (values.size() > 27) { reqstr = values[27][0] == '\0' ? 0 : std::stoi(values[27]); }
    if (values.size() > 28) { reqdex = values[28][0] == '\0' ? 0 : std::stoi(values[28]); }
    if (values.size() > 29) { durability = values[29][0] == '\0' ? 0 : std::stoi(values[29]); }
    if (values.size() > 30) { nodurability = values[30][0] == '\0' ? 0 : std::stoi(values[30]); }
    if (values.size() > 31) { level = values[31][0] == '\0' ? 0 : std::stoi(values[31]); }
    if (values.size() > 32) { ShowLevel = values[32][0] == '\0' ? 0 : std::stoi(values[32]); }
    if (values.size() > 33) { levelreq = values[33][0] == '\0' ? 0 : std::stoi(values[33]); }
    if (values.size() > 34) { cost = values[34][0] == '\0' ? 0 : std::stoi(values[34]); }
    if (values.size() > 35) { gamblecost = values[35][0] == '\0' ? 0 : std::stoi(values[35]); }
    if (values.size() > 36) { magiclvl = values[36][0] == '\0' ? 0 : std::stoi(values[36]); }
    if (values.size() > 37) { autoprefix = values[37][0] == '\0' ? 0 : std::stoi(values[37]); }
    if (values.size() > 38) { normcode = values[38]; }
    if (values.size() > 39) { ubercode = values[39]; }
    if (values.size() > 40) { ultracode = values[40]; }
    if (values.size() > 41) { wclass = values[41]; }
    if (values.size() > 42) { _2handedwclass = values[42]; }
    if (values.size() > 43) { component = values[43][0] == '\0' ? 0 : std::stoi(values[43]); }
    if (values.size() > 44) { hitclass = values[44]; }
    if (values.size() > 45) { invwidth = values[45][0] == '\0' ? 0 : std::stoi(values[45]); }
    if (values.size() > 46) { invheight = values[46][0] == '\0' ? 0 : std::stoi(values[46]); }
    if (values.size() > 47) { stackable = values[47][0] == '\0' ? 0 : std::stoi(values[47]); }
    if (values.size() > 48) { minstack = values[48][0] == '\0' ? 0 : std::stoi(values[48]); }
    if (values.size() > 49) { maxstack = values[49][0] == '\0' ? 0 : std::stoi(values[49]); }
    if (values.size() > 50) { spawnstack = values[50][0] == '\0' ? 0 : std::stoi(values[50]); }
    if (values.size() > 51) { flippyfile = values[51]; }
    if (values.size() > 52) { invfile = values[52]; }
    if (values.size() > 53) { uniqueinvfile = values[53]; }
    if (values.size() > 54) { setinvfile = values[54]; }
    if (values.size() > 55) { hasinv = values[55][0] == '\0' ? 0 : std::stoi(values[55]); }
    if (values.size() > 56) { gemsockets = values[56][0] == '\0' ? 0 : std::stoi(values[56]); }
    if (values.size() > 57) { gemapplytype = values[57][0] == '\0' ? 0 : std::stoi(values[57]); }
    if (values.size() > 58) { comment = values[58]; }
    if (values.size() > 59) { useable = values[59][0] == '\0' ? 0 : std::stoi(values[59]); }
    if (values.size() > 60) { dropsound = values[60]; }
    if (values.size() > 61) { dropsfxframe = values[61][0] == '\0' ? 0 : std::stoi(values[61]); }
    if (values.size() > 62) { usesound = values[62]; }
    if (values.size() > 63) { unique = values[63][0] == '\0' ? 0 : std::stoi(values[63]); }
    if (values.size() > 64) { transparent = values[64][0] == '\0' ? 0 : std::stoi(values[64]); }
    if (values.size() > 65) { transtbl = values[65][0] == '\0' ? 0 : std::stoi(values[65]); }
    if (values.size() > 66) { quivered = values[66][0] == '\0' ? 0 : std::stoi(values[66]); }
    if (values.size() > 67) { lightradius = values[67][0] == '\0' ? 0 : std::stoi(values[67]); }
    if (values.size() > 68) { belt = values[68][0] == '\0' ? 0 : std::stoi(values[68]); }
    if (values.size() > 69) { quest = values[69][0] == '\0' ? 0 : std::stoi(values[69]); }
    if (values.size() > 70) { questdiffcheck = values[70][0] == '\0' ? 0 : std::stoi(values[70]); }
    if (values.size() > 71) { missiletype = values[71][0] == '\0' ? 0 : std::stoi(values[71]); }
    if (values.size() > 72) { durwarning = values[72][0] == '\0' ? 0 : std::stoi(values[72]); }
    if (values.size() > 73) { qntwarning = values[73][0] == '\0' ? 0 : std::stoi(values[73]); }
    if (values.size() > 74) { gemoffset = values[74][0] == '\0' ? 0 : std::stoi(values[74]); }
    if (values.size() > 75) { bitfield1 = values[75][0] == '\0' ? 0 : std::stoi(values[75]); }
    if (values.size() > 76) { CharsiMin = values[76][0] == '\0' ? 0 : std::stoi(values[76]); }
    if (values.size() > 77) { CharsiMax = values[77][0] == '\0' ? 0 : std::stoi(values[77]); }
    if (values.size() > 78) { CharsiMagicMin = values[78][0] == '\0' ? 0 : std::stoi(values[78]); }
    if (values.size() > 79) { CharsiMagicMax = values[79][0] == '\0' ? 0 : std::stoi(values[79]); }
    if (values.size() > 80) { CharsiMagicLvl = values[80][0] == '\0' ? 0 : std::stoi(values[80]); }
    if (values.size() > 81) { GheedMin = values[81][0] == '\0' ? 0 : std::stoi(values[81]); }
    if (values.size() > 82) { GheedMax = values[82][0] == '\0' ? 0 : std::stoi(values[82]); }
    if (values.size() > 83) { GheedMagicMin = values[83][0] == '\0' ? 0 : std::stoi(values[83]); }
    if (values.size() > 84) { GheedMagicMax = values[84][0] == '\0' ? 0 : std::stoi(values[84]); }
    if (values.size() > 85) { GheedMagicLvl = values[85][0] == '\0' ? 0 : std::stoi(values[85]); }
    if (values.size() > 86) { AkaraMin = values[86][0] == '\0' ? 0 : std::stoi(values[86]); }
    if (values.size() > 87) { AkaraMax = values[87][0] == '\0' ? 0 : std::stoi(values[87]); }
    if (values.size() > 88) { AkaraMagicMin = values[88][0] == '\0' ? 0 : std::stoi(values[88]); }
    if (values.size() > 89) { AkaraMagicMax = values[89][0] == '\0' ? 0 : std::stoi(values[89]); }
    if (values.size() > 90) { AkaraMagicLvl = values[90][0] == '\0' ? 0 : std::stoi(values[90]); }
    if (values.size() > 91) { FaraMin = values[91][0] == '\0' ? 0 : std::stoi(values[91]); }
    if (values.size() > 92) { FaraMax = values[92][0] == '\0' ? 0 : std::stoi(values[92]); }
    if (values.size() > 93) { FaraMagicMin = values[93][0] == '\0' ? 0 : std::stoi(values[93]); }
    if (values.size() > 94) { FaraMagicMax = values[94][0] == '\0' ? 0 : std::stoi(values[94]); }
    if (values.size() > 95) { FaraMagicLvl = values[95][0] == '\0' ? 0 : std::stoi(values[95]); }
    if (values.size() > 100) { LysanderMagicLvl = values[100][0] == '\0' ? 0 : std::stoi(values[100]); }
    if (values.size() > 101) { DrognanMin = values[101][0] == '\0' ? 0 : std::stoi(values[101]); }
    if (values.size() > 102) { DrognanMax = values[102][0] == '\0' ? 0 : std::stoi(values[102]); }
    if (values.size() > 103) { DrognanMagicMin = values[103][0] == '\0' ? 0 : std::stoi(values[103]); }
    if (values.size() > 104) { DrognanMagicMax = values[104][0] == '\0' ? 0 : std::stoi(values[104]); }
    if (values.size() > 105) { DrognanMagicLvl = values[105][0] == '\0' ? 0 : std::stoi(values[105]); }
    if (values.size() > 106) { HratliMin = values[106][0] == '\0' ? 0 : std::stoi(values[106]); }
    if (values.size() > 107) { HratliMax = values[107][0] == '\0' ? 0 : std::stoi(values[107]); }
    if (values.size() > 108) { HratliMagicMin = values[108][0] == '\0' ? 0 : std::stoi(values[108]); }
    if (values.size() > 109) { HratliMagicMax = values[109][0] == '\0' ? 0 : std::stoi(values[109]); }
    if (values.size() > 110) { HratliMagicLvl = values[110][0] == '\0' ? 0 : std::stoi(values[110]); }
    if (values.size() > 115) { AlkorMagicLvl = values[115][0] == '\0' ? 0 : std::stoi(values[115]); }
    if (values.size() > 116) { OrmusMin = values[116][0] == '\0' ? 0 : std::stoi(values[116]); }
    if (values.size() > 117) { OrmusMax = values[117][0] == '\0' ? 0 : std::stoi(values[117]); }
    if (values.size() > 118) { OrmusMagicMin = values[118][0] == '\0' ? 0 : std::stoi(values[118]); }
    if (values.size() > 119) { OrmusMagicMax = values[119][0] == '\0' ? 0 : std::stoi(values[119]); }
    if (values.size() > 120) { OrmusMagicLvl = values[120][0] == '\0' ? 0 : std::stoi(values[120]); }
    if (values.size() > 121) { ElzixMin = values[121][0] == '\0' ? 0 : std::stoi(values[121]); }
    if (values.size() > 122) { ElzixMax = values[122][0] == '\0' ? 0 : std::stoi(values[122]); }
    if (values.size() > 123) { ElzixMagicMin = values[123][0] == '\0' ? 0 : std::stoi(values[123]); }
    if (values.size() > 124) { ElzixMagicMax = values[124][0] == '\0' ? 0 : std::stoi(values[124]); }
    if (values.size() > 125) { ElzixMagicLvl = values[125][0] == '\0' ? 0 : std::stoi(values[125]); }
    if (values.size() > 126) { AshearaMin = values[126][0] == '\0' ? 0 : std::stoi(values[126]); }
    if (values.size() > 127) { AshearaMax = values[127][0] == '\0' ? 0 : std::stoi(values[127]); }
    if (values.size() > 128) { AshearaMagicMin = values[128][0] == '\0' ? 0 : std::stoi(values[128]); }
    if (values.size() > 129) { AshearaMagicMax = values[129][0] == '\0' ? 0 : std::stoi(values[129]); }
    if (values.size() > 130) { AshearaMagicLvl = values[130][0] == '\0' ? 0 : std::stoi(values[130]); }
    if (values.size() > 131) { CainMin = values[131][0] == '\0' ? 0 : std::stoi(values[131]); }
    if (values.size() > 132) { CainMax = values[132][0] == '\0' ? 0 : std::stoi(values[132]); }
    if (values.size() > 133) { CainMagicMin = values[133][0] == '\0' ? 0 : std::stoi(values[133]); }
    if (values.size() > 134) { CainMagicMax = values[134][0] == '\0' ? 0 : std::stoi(values[134]); }
    if (values.size() > 135) { CainMagicLvl = values[135][0] == '\0' ? 0 : std::stoi(values[135]); }
    if (values.size() > 136) { HalbuMin = values[136][0] == '\0' ? 0 : std::stoi(values[136]); }
    if (values.size() > 137) { HalbuMax = values[137][0] == '\0' ? 0 : std::stoi(values[137]); }
    if (values.size() > 138) { HalbuMagicMin = values[138][0] == '\0' ? 0 : std::stoi(values[138]); }
    if (values.size() > 139) { HalbuMagicMax = values[139][0] == '\0' ? 0 : std::stoi(values[139]); }
    if (values.size() > 140) { HalbuMagicLvl = values[140][0] == '\0' ? 0 : std::stoi(values[140]); }
    if (values.size() > 141) { JamellaMin = values[141][0] == '\0' ? 0 : std::stoi(values[141]); }
    if (values.size() > 142) { JamellaMax = values[142][0] == '\0' ? 0 : std::stoi(values[142]); }
    if (values.size() > 143) { JamellaMagicMin = values[143][0] == '\0' ? 0 : std::stoi(values[143]); }
    if (values.size() > 144) { JamellaMagicMax = values[144][0] == '\0' ? 0 : std::stoi(values[144]); }
    if (values.size() > 145) { JamellaMagicLvl = values[145][0] == '\0' ? 0 : std::stoi(values[145]); }
    if (values.size() > 146) { LarzukMin = values[146][0] == '\0' ? 0 : std::stoi(values[146]); }
    if (values.size() > 147) { LarzukMax = values[147][0] == '\0' ? 0 : std::stoi(values[147]); }
    if (values.size() > 148) { LarzukMagicMin = values[148][0] == '\0' ? 0 : std::stoi(values[148]); }
    if (values.size() > 149) { LarzukMagicMax = values[149][0] == '\0' ? 0 : std::stoi(values[149]); }
    if (values.size() > 150) { LarzukMagicLvl = values[150][0] == '\0' ? 0 : std::stoi(values[150]); }
    if (values.size() > 151) { AnyaMin = values[151][0] == '\0' ? 0 : std::stoi(values[151]); }
    if (values.size() > 152) { AnyaMax = values[152][0] == '\0' ? 0 : std::stoi(values[152]); }
    if (values.size() > 153) { AnyaMagicMin = values[153][0] == '\0' ? 0 : std::stoi(values[153]); }
    if (values.size() > 154) { AnyaMagicMax = values[154][0] == '\0' ? 0 : std::stoi(values[154]); }
    if (values.size() > 155) { AnyaMagicLvl = values[155][0] == '\0' ? 0 : std::stoi(values[155]); }
    if (values.size() > 156) { MalahMin = values[156][0] == '\0' ? 0 : std::stoi(values[156]); }
    if (values.size() > 157) { MalahMax = values[157][0] == '\0' ? 0 : std::stoi(values[157]); }
    if (values.size() > 158) { MalahMagicMin = values[158][0] == '\0' ? 0 : std::stoi(values[158]); }
    if (values.size() > 159) { MalahMagicMax = values[159][0] == '\0' ? 0 : std::stoi(values[159]); }
    if (values.size() > 160) { MalahMagicLvl = values[160][0] == '\0' ? 0 : std::stoi(values[160]); }
    if (values.size() > 161) { Transform = values[161][0] == '\0' ? 0 : std::stoi(values[161]); }
    if (values.size() > 162) { InvTrans = values[162][0] == '\0' ? 0 : std::stoi(values[162]); }
    if (values.size() > 163) { SkipName = values[163][0] == '\0' ? 0 : std::stoi(values[163]); }
    if (values.size() > 164) { NightmareUpgrade = values[164]; }
    if (values.size() > 165) { HellUpgrade = values[165]; }
    if (values.size() > 166) { Nameable = values[166][0] == '\0' ? 0 : std::stoi(values[166]); }
    if (values.size() > 167) { PermStoreItem = values[167][0] == '\0' ? 0 : std::stoi(values[167]); }

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
