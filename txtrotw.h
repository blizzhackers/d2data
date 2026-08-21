#include <cstdint>
#include <string>
#include <vector>

namespace D2::ROTW {

  struct t_actinfo {
    int32_t act = 0;	// Column 0
    std::string town = "";	// Column 1
    std::string start = "";	// Column 2
    int32_t maxnpcitemlevel = 0;	// Column 3
    std::string classlevelrangestart = "";	// Column 4
    std::string classlevelrangeend = "";	// Column 5
    int32_t wanderingnpcstart = 0;	// Column 6
    int32_t wanderingnpcrange = 0;	// Column 7
    std::string commonactcof = "";	// Column 8
    std::string waypoint1 = "";	// Column 9
    std::string waypoint2 = "";	// Column 10
    std::string waypoint3 = "";	// Column 11
    std::string waypoint4 = "";	// Column 12
    std::string waypoint5 = "";	// Column 13
    std::string waypoint6 = "";	// Column 14
    std::string waypoint7 = "";	// Column 15
    std::string waypoint8 = "";	// Column 16
    std::string waypoint9 = "";	// Column 17
    int32_t wanderingMonsterPopulateChance = 0;	// Column 18
    int32_t wanderingMonsterRegionTotal = 0;	// Column 19
    int32_t wanderingPopulateRandomChance = 0;	// Column 20

    size_t read(const char* line);
    static std::vector<t_actinfo> readfile(std::string filename);
  };

  struct t_armor {
    std::string name = "";	// Column 0
    int32_t version = 0;	// Column 1
    int32_t compactsave = 0;	// Column 2
    int32_t rarity = 0;	// Column 3
    int32_t spawnable = 0;	// Column 4
    // Unused column: DropConditionCalc
    int32_t minac = 0;	// Column 6
    int32_t maxac = 0;	// Column 7
    int32_t speed = 0;	// Column 8
    int32_t reqstr = 0;	// Column 9
    int32_t reqdex = 0;	// Column 10
    int32_t block = 0;	// Column 11
    int32_t durability = 0;	// Column 12
    int32_t nodurability = 0;	// Column 13
    int32_t level = 0;	// Column 14
    int32_t ShowLevel = 0;	// Column 15
    int32_t levelreq = 0;	// Column 16
    int32_t cost = 0;	// Column 17
    int32_t gamblecost = 0;	// Column 18
    std::string code = "";	// Column 19
    std::string namestr = "";	// Column 20
    int32_t magiclvl = 0;	// Column 21
    int32_t autoprefix = 0;	// Column 22
    std::string alternategfx = "";	// Column 23
    std::string normcode = "";	// Column 24
    std::string ubercode = "";	// Column 25
    std::string ultracode = "";	// Column 26
    int32_t component = 0;	// Column 27
    int32_t invwidth = 0;	// Column 28
    int32_t invheight = 0;	// Column 29
    int32_t hasinv = 0;	// Column 30
    int32_t gemsockets = 0;	// Column 31
    int32_t gemapplytype = 0;	// Column 32
    std::string flippyfile = "";	// Column 33
    std::string invfile = "";	// Column 34
    std::string uniqueinvfile = "";	// Column 35
    std::string setinvfile = "";	// Column 36
    int32_t rArm = 0;	// Column 37
    int32_t lArm = 0;	// Column 38
    int32_t Torso = 0;	// Column 39
    int32_t Legs = 0;	// Column 40
    int32_t rSPad = 0;	// Column 41
    int32_t lSPad = 0;	// Column 42
    int32_t useable = 0;	// Column 43
    // Unused column: stackable
    // Unused column: minstack
    // Unused column: maxstack
    // Unused column: spawnstack
    int32_t Transmogrify = 0;	// Column 48
    std::string TMogType = "";	// Column 49
    // Unused column: TMogMin
    // Unused column: TMogMax
    std::string type = "";	// Column 52
    // Unused column: type2
    std::string dropsound = "";	// Column 54
    int32_t dropsfxframe = 0;	// Column 55
    std::string usesound = "";	// Column 56
    int32_t unique = 0;	// Column 57
    int32_t transparent = 0;	// Column 58
    int32_t transtbl = 0;	// Column 59
    int32_t quivered = 0;	// Column 60
    int32_t lightradius = 0;	// Column 61
    int32_t belt = 0;	// Column 62
    // Unused column: quest
    // Unused column: questdiffcheck
    int32_t missiletype = 0;	// Column 65
    int32_t durwarning = 0;	// Column 66
    int32_t qntwarning = 0;	// Column 67
    int32_t mindam = 0;	// Column 68
    int32_t maxdam = 0;	// Column 69
    int32_t StrBonus = 0;	// Column 70
    // Unused column: DexBonus
    int32_t gemoffset = 0;	// Column 72
    int32_t bitfield1 = 0;	// Column 73
    int32_t CharsiMin = 0;	// Column 74
    int32_t CharsiMax = 0;	// Column 75
    int32_t CharsiMagicMin = 0;	// Column 76
    int32_t CharsiMagicMax = 0;	// Column 77
    int32_t CharsiMagicLvl = 0;	// Column 78
    int32_t GheedMin = 0;	// Column 79
    int32_t GheedMax = 0;	// Column 80
    // Unused column: GheedMagicMin
    int32_t GheedMagicMax = 0;	// Column 82
    int32_t GheedMagicLvl = 0;	// Column 83
    // Unused column: AkaraMin
    // Unused column: AkaraMax
    // Unused column: AkaraMagicMin
    // Unused column: AkaraMagicMax
    int32_t AkaraMagicLvl = 0;	// Column 88
    int32_t FaraMin = 0;	// Column 89
    int32_t FaraMax = 0;	// Column 90
    int32_t FaraMagicMin = 0;	// Column 91
    int32_t FaraMagicMax = 0;	// Column 92
    int32_t FaraMagicLvl = 0;	// Column 93
    // Unused column: LysanderMin
    // Unused column: LysanderMax
    // Unused column: LysanderMagicMin
    // Unused column: LysanderMagicMax
    int32_t LysanderMagicLvl = 0;	// Column 98
    int32_t DrognanMin = 0;	// Column 99
    int32_t DrognanMax = 0;	// Column 100
    int32_t DrognanMagicMin = 0;	// Column 101
    int32_t DrognanMagicMax = 0;	// Column 102
    int32_t DrognanMagicLvl = 0;	// Column 103
    int32_t HratliMin = 0;	// Column 104
    int32_t HratliMax = 0;	// Column 105
    int32_t HratliMagicMin = 0;	// Column 106
    int32_t HratliMagicMax = 0;	// Column 107
    int32_t HratliMagicLvl = 0;	// Column 108
    // Unused column: AlkorMin
    // Unused column: AlkorMax
    // Unused column: AlkorMagicMin
    // Unused column: AlkorMagicMax
    int32_t AlkorMagicLvl = 0;	// Column 113
    // Unused column: OrmusMin
    int32_t OrmusMax = 0;	// Column 115
    // Unused column: OrmusMagicMin
    int32_t OrmusMagicMax = 0;	// Column 117
    int32_t OrmusMagicLvl = 0;	// Column 118
    int32_t ElzixMin = 0;	// Column 119
    int32_t ElzixMax = 0;	// Column 120
    int32_t ElzixMagicMin = 0;	// Column 121
    int32_t ElzixMagicMax = 0;	// Column 122
    int32_t ElzixMagicLvl = 0;	// Column 123
    int32_t AshearaMin = 0;	// Column 124
    int32_t AshearaMax = 0;	// Column 125
    int32_t AshearaMagicMin = 0;	// Column 126
    int32_t AshearaMagicMax = 0;	// Column 127
    int32_t AshearaMagicLvl = 0;	// Column 128
    int32_t CainMin = 0;	// Column 129
    int32_t CainMax = 0;	// Column 130
    int32_t CainMagicMin = 0;	// Column 131
    int32_t CainMagicMax = 0;	// Column 132
    int32_t CainMagicLvl = 0;	// Column 133
    int32_t HalbuMin = 0;	// Column 134
    int32_t HalbuMax = 0;	// Column 135
    int32_t HalbuMagicMin = 0;	// Column 136
    int32_t HalbuMagicMax = 0;	// Column 137
    int32_t HalbuMagicLvl = 0;	// Column 138
    int32_t JamellaMin = 0;	// Column 139
    int32_t JamellaMax = 0;	// Column 140
    int32_t JamellaMagicMin = 0;	// Column 141
    int32_t JamellaMagicMax = 0;	// Column 142
    int32_t JamellaMagicLvl = 0;	// Column 143
    int32_t LarzukMin = 0;	// Column 144
    int32_t LarzukMax = 0;	// Column 145
    int32_t LarzukMagicMin = 0;	// Column 146
    int32_t LarzukMagicMax = 0;	// Column 147
    int32_t LarzukMagicLvl = 0;	// Column 148
    // Unused column: MalahMin
    // Unused column: MalahMax
    // Unused column: MalahMagicMin
    // Unused column: MalahMagicMax
    int32_t MalahMagicLvl = 0;	// Column 153
    int32_t AnyaMin = 0;	// Column 154
    int32_t AnyaMax = 0;	// Column 155
    int32_t AnyaMagicMin = 0;	// Column 156
    int32_t AnyaMagicMax = 0;	// Column 157
    int32_t AnyaMagicLvl = 0;	// Column 158
    int32_t Transform = 0;	// Column 159
    int32_t InvTrans = 0;	// Column 160
    int32_t SkipName = 0;	// Column 161
    std::string NightmareUpgrade = "";	// Column 162
    std::string HellUpgrade = "";	// Column 163
    int32_t Nameable = 0;	// Column 164
    int32_t PermStoreItem = 0;	// Column 165
    // Unused column: UICatOverride
    // Unused column: diablocloneweight

    size_t read(const char* line);
    static std::vector<t_armor> readfile(std::string filename);
  };

  struct t_armtype {
    std::string Name = "";	// Column 0
    std::string Token = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_armtype> readfile(std::string filename);
  };

  struct t_automagic {
    std::string Name = "";	// Column 0
    int32_t version = 0;	// Column 1
    int32_t spawnable = 0;	// Column 2
    int32_t rare = 0;	// Column 3
    int32_t level = 0;	// Column 4
    // Unused column: maxlevel
    int32_t levelreq = 0;	// Column 6
    // Unused column: classspecific
    // Unused column: class
    // Unused column: classlevelreq
    int32_t frequency = 0;	// Column 10
    int32_t group = 0;	// Column 11
    std::string mod1code = "";	// Column 12
    int32_t mod1param = 0;	// Column 13
    int32_t mod1min = 0;	// Column 14
    int32_t mod1max = 0;	// Column 15
    std::string mod2code = "";	// Column 16
    // Unused column: mod2param
    int32_t mod2min = 0;	// Column 18
    int32_t mod2max = 0;	// Column 19
    std::string mod3code = "";	// Column 20
    // Unused column: mod3param
    int32_t mod3min = 0;	// Column 22
    int32_t mod3max = 0;	// Column 23
    std::string transformcolor = "";	// Column 24
    std::string itype1 = "";	// Column 25
    std::string itype2 = "";	// Column 26
    // Unused column: itype3
    // Unused column: itype4
    // Unused column: itype5
    // Unused column: itype6
    // Unused column: itype7
    // Unused column: etype1
    // Unused column: etype2
    // Unused column: etype3
    // Unused column: etype4
    // Unused column: etype5
    int32_t multiply = 0;	// Column 37
    int32_t add = 0;	// Column 38

    size_t read(const char* line);
    static std::vector<t_automagic> readfile(std::string filename);
  };

  struct t_automap {
    std::string LevelName = "";	// Column 0
    std::string TileName = "";	// Column 1
    int32_t Style = 0;	// Column 2
    int32_t StartSequence = 0;	// Column 3
    int32_t EndSequence = 0;	// Column 4
    std::string Type1 = "";	// Column 5
    int32_t Cel1 = 0;	// Column 6
    std::string Type2 = "";	// Column 7
    int32_t Cel2 = 0;	// Column 8
    std::string Type3 = "";	// Column 9
    int32_t Cel3 = 0;	// Column 10
    std::string Type4 = "";	// Column 11
    int32_t Cel4 = 0;	// Column 12

    size_t read(const char* line);
    static std::vector<t_automap> readfile(std::string filename);
  };

  struct t_belts {
    std::string name = "";	// Column 0
    int32_t numboxes = 0;	// Column 1
    int32_t box1left = 0;	// Column 2
    int32_t box1right = 0;	// Column 3
    int32_t box1top = 0;	// Column 4
    int32_t box1bottom = 0;	// Column 5
    int32_t box2left = 0;	// Column 6
    int32_t box2right = 0;	// Column 7
    int32_t box2top = 0;	// Column 8
    int32_t box2bottom = 0;	// Column 9
    int32_t box3left = 0;	// Column 10
    int32_t box3right = 0;	// Column 11
    int32_t box3top = 0;	// Column 12
    int32_t box3bottom = 0;	// Column 13
    int32_t box4left = 0;	// Column 14
    int32_t box4right = 0;	// Column 15
    int32_t box4top = 0;	// Column 16
    int32_t box4bottom = 0;	// Column 17
    int32_t box5left = 0;	// Column 18
    int32_t box5right = 0;	// Column 19
    int32_t box5top = 0;	// Column 20
    int32_t box5bottom = 0;	// Column 21
    int32_t box6left = 0;	// Column 22
    int32_t box6right = 0;	// Column 23
    int32_t box6top = 0;	// Column 24
    int32_t box6bottom = 0;	// Column 25
    int32_t box7left = 0;	// Column 26
    int32_t box7right = 0;	// Column 27
    int32_t box7top = 0;	// Column 28
    int32_t box7bottom = 0;	// Column 29
    int32_t box8left = 0;	// Column 30
    int32_t box8right = 0;	// Column 31
    int32_t box8top = 0;	// Column 32
    int32_t box8bottom = 0;	// Column 33
    int32_t box9left = 0;	// Column 34
    int32_t box9right = 0;	// Column 35
    int32_t box9top = 0;	// Column 36
    int32_t box9bottom = 0;	// Column 37
    int32_t box10left = 0;	// Column 38
    int32_t box10right = 0;	// Column 39
    int32_t box10top = 0;	// Column 40
    int32_t box10bottom = 0;	// Column 41
    int32_t box11left = 0;	// Column 42
    int32_t box11right = 0;	// Column 43
    int32_t box11top = 0;	// Column 44
    int32_t box11bottom = 0;	// Column 45
    int32_t box12left = 0;	// Column 46
    int32_t box12right = 0;	// Column 47
    int32_t box12top = 0;	// Column 48
    int32_t box12bottom = 0;	// Column 49
    int32_t box13left = 0;	// Column 50
    int32_t box13right = 0;	// Column 51
    int32_t box13top = 0;	// Column 52
    int32_t box13bottom = 0;	// Column 53
    int32_t box14left = 0;	// Column 54
    int32_t box14right = 0;	// Column 55
    int32_t box14top = 0;	// Column 56
    int32_t box14bottom = 0;	// Column 57
    int32_t box15left = 0;	// Column 58
    int32_t box15right = 0;	// Column 59
    int32_t box15top = 0;	// Column 60
    int32_t box15bottom = 0;	// Column 61
    int32_t box16left = 0;	// Column 62
    int32_t box16right = 0;	// Column 63
    int32_t box16top = 0;	// Column 64
    int32_t box16bottom = 0;	// Column 65
    std::string defaultItemTypeCol1 = "";	// Column 66
    // Unused column: defaultItemCodeCol1
    std::string defaultItemTypeCol2 = "";	// Column 68
    // Unused column: defaultItemCodeCol2
    std::string defaultItemTypeCol3 = "";	// Column 70
    // Unused column: defaultItemCodeCol3
    std::string defaultItemTypeCol4 = "";	// Column 72
    std::string defaultItemCodeCol4 = "";	// Column 73

    size_t read(const char* line);
    static std::vector<t_belts> readfile(std::string filename);
  };

  struct t_bodylocs {
    std::string BodyLocation = "";	// Column 0
    std::string Code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_bodylocs> readfile(std::string filename);
  };

  struct t_books {
    std::string Name = "";	// Column 0
    std::string ScrollSpellCode = "";	// Column 1
    std::string BookSpellCode = "";	// Column 2
    int32_t pSpell = 0;	// Column 3
    int32_t SpellIcon = 0;	// Column 4
    std::string ScrollSkill = "";	// Column 5
    std::string BookSkill = "";	// Column 6
    int32_t BaseCost = 0;	// Column 7
    int32_t CostPerCharge = 0;	// Column 8

    size_t read(const char* line);
    static std::vector<t_books> readfile(std::string filename);
  };

  struct t_charstats {
    std::string _class = "";	// Column 0
    int32_t str = 0;	// Column 1
    int32_t dex = 0;	// Column 2
    int32_t _int = 0;	// Column 3
    int32_t vit = 0;	// Column 4
    int32_t stamina = 0;	// Column 5
    int32_t hpadd = 0;	// Column 6
    int32_t ManaRegen = 0;	// Column 7
    int32_t ToHitFactor = 0;	// Column 8
    int32_t WalkVelocity = 0;	// Column 9
    int32_t RunVelocity = 0;	// Column 10
    int32_t RunDrain = 0;	// Column 11
    std::string Comment = "";	// Column 12
    int32_t LifePerLevel = 0;	// Column 13
    int32_t StaminaPerLevel = 0;	// Column 14
    int32_t ManaPerLevel = 0;	// Column 15
    int32_t LifePerVitality = 0;	// Column 16
    int32_t StaminaPerVitality = 0;	// Column 17
    int32_t ManaPerMagic = 0;	// Column 18
    int32_t StatPerLevel = 0;	// Column 19
    int32_t SkillsPerLevel = 0;	// Column 20
    int32_t LightRadius = 0;	// Column 21
    int32_t BlockFactor = 0;	// Column 22
    int32_t MinimumCastingDelay = 0;	// Column 23
    std::string StartSkill = "";	// Column 24
    std::string Skill1 = "";	// Column 25
    std::string Skill2 = "";	// Column 26
    std::string Skill3 = "";	// Column 27
    std::string Skill4 = "";	// Column 28
    std::string Skill5 = "";	// Column 29
    std::string Skill6 = "";	// Column 30
    std::string Skill7 = "";	// Column 31
    std::string Skill8 = "";	// Column 32
    std::string Skill9 = "";	// Column 33
    // Unused column: Skill 10
    std::string StrAllSkills = "";	// Column 35
    std::string StrSkillTab1 = "";	// Column 36
    std::string StrSkillTab2 = "";	// Column 37
    std::string StrSkillTab3 = "";	// Column 38
    std::string StrClassOnly = "";	// Column 39
    int32_t HealthPotionPercent = 0;	// Column 40
    int32_t ManaPotionPercent = 0;	// Column 41
    std::string baseWClass = "";	// Column 42
    std::string item1 = "";	// Column 43
    std::string item1loc = "";	// Column 44
    int32_t item1count = 0;	// Column 45
    int32_t item1quality = 0;	// Column 46
    std::string item2 = "";	// Column 47
    std::string item2loc = "";	// Column 48
    int32_t item2count = 0;	// Column 49
    int32_t item2quality = 0;	// Column 50
    std::string item3 = "";	// Column 51
    // Unused column: item3loc
    int32_t item3count = 0;	// Column 53
    int32_t item3quality = 0;	// Column 54
    std::string item4 = "";	// Column 55
    // Unused column: item4loc
    int32_t item4count = 0;	// Column 57
    int32_t item4quality = 0;	// Column 58
    std::string item5 = "";	// Column 59
    // Unused column: item5loc
    int32_t item5count = 0;	// Column 61
    int32_t item5quality = 0;	// Column 62
    int32_t item6 = 0;	// Column 63
    // Unused column: item6loc
    int32_t item6count = 0;	// Column 65
    int32_t item6quality = 0;	// Column 66
    int32_t item7 = 0;	// Column 67
    // Unused column: item7loc
    int32_t item7count = 0;	// Column 69
    int32_t item7quality = 0;	// Column 70
    int32_t item8 = 0;	// Column 71
    // Unused column: item8loc
    int32_t item8count = 0;	// Column 73
    int32_t item8quality = 0;	// Column 74
    int32_t item9 = 0;	// Column 75
    // Unused column: item9loc
    int32_t item9count = 0;	// Column 77
    int32_t item9quality = 0;	// Column 78
    int32_t item10 = 0;	// Column 79
    // Unused column: item10loc
    int32_t item10count = 0;	// Column 81
    int32_t item10quality = 0;	// Column 82
    std::string TwoHandedOffHandRestrictItemType = "";	// Column 83
    // Unused column: TwoHandedDamageAsOneHanded

    size_t read(const char* line);
    static std::vector<t_charstats> readfile(std::string filename);
  };

  struct t_colors {
    std::string TransformColor = "";	// Column 0
    std::string Code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_colors> readfile(std::string filename);
  };

  struct t_compcode {
    std::string component = "";	// Column 0
    std::string code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_compcode> readfile(std::string filename);
  };

  struct t_composit {
    std::string Name = "";	// Column 0
    std::string Token = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_composit> readfile(std::string filename);
  };

  struct t_cubemain {
    std::string description = "";	// Column 0
    int32_t enabled = 0;	// Column 1
    int32_t firstLadderSeason = 0;	// Column 2
    int32_t lastLadderSeason = 0;	// Column 3
    int32_t mindiff = 0;	// Column 4
    int32_t version = 0;	// Column 5
    int32_t op = 0;	// Column 6
    // Unused column: param
    // Unused column: value
    // Unused column: class
    int32_t numinputs = 0;	// Column 10
    std::string input1 = "";	// Column 11
    std::string input2 = "";	// Column 12
    std::string input3 = "";	// Column 13
    std::string input4 = "";	// Column 14
    std::string input5 = "";	// Column 15
    std::string input6 = "";	// Column 16
    std::string input7 = "";	// Column 17
    std::string output = "";	// Column 18
    int32_t lvl = 0;	// Column 19
    int32_t plvl = 0;	// Column 20
    int32_t ilvl = 0;	// Column 21
    std::string mod1 = "";	// Column 22
    // Unused column: mod 1 chance
    int32_t mod1param = 0;	// Column 24
    int32_t mod1min = 0;	// Column 25
    int32_t mod1max = 0;	// Column 26
    std::string mod2 = "";	// Column 27
    // Unused column: mod 2 chance
    // Unused column: mod 2 param
    int32_t mod2min = 0;	// Column 30
    int32_t mod2max = 0;	// Column 31
    std::string mod3 = "";	// Column 32
    // Unused column: mod 3 chance
    // Unused column: mod 3 param
    int32_t mod3min = 0;	// Column 35
    int32_t mod3max = 0;	// Column 36
    std::string mod4 = "";	// Column 37
    // Unused column: mod 4 chance
    // Unused column: mod 4 param
    int32_t mod4min = 0;	// Column 40
    int32_t mod4max = 0;	// Column 41
    // Unused column: mod 5
    // Unused column: mod 5 chance
    // Unused column: mod 5 param
    // Unused column: mod 5 min
    // Unused column: mod 5 max
    // Unused column: output b
    // Unused column: b lvl
    // Unused column: b plvl
    // Unused column: b ilvl
    // Unused column: b mod 1
    // Unused column: b mod 1 chance
    // Unused column: b mod 1 param
    // Unused column: b mod 1 min
    // Unused column: b mod 1 max
    // Unused column: b mod 2
    // Unused column: b mod 2 chance
    // Unused column: b mod 2 param
    // Unused column: b mod 2 min
    // Unused column: b mod 2 max
    // Unused column: b mod 3
    // Unused column: b mod 3 chance
    // Unused column: b mod 3 param
    // Unused column: b mod 3 min
    // Unused column: b mod 3 max
    // Unused column: b mod 4
    // Unused column: b mod 4 chance
    // Unused column: b mod 4 param
    // Unused column: b mod 4 min
    // Unused column: b mod 4 max
    // Unused column: b mod 5
    // Unused column: b mod 5 chance
    // Unused column: b mod 5 param
    // Unused column: b mod 5 min
    // Unused column: b mod 5 max
    // Unused column: output c
    // Unused column: c lvl
    // Unused column: c plvl
    // Unused column: c ilvl
    // Unused column: c mod 1
    // Unused column: c mod 1 chance
    // Unused column: c mod 1 param
    // Unused column: c mod 1 min
    // Unused column: c mod 1 max
    // Unused column: c mod 2
    // Unused column: c mod 2 chance
    // Unused column: c mod 2 param
    // Unused column: c mod 2 min
    // Unused column: c mod 2 max
    // Unused column: c mod 3
    // Unused column: c mod 3 chance
    // Unused column: c mod 3 param
    // Unused column: c mod 3 min
    // Unused column: c mod 3 max
    // Unused column: c mod 4
    // Unused column: c mod 4 chance
    // Unused column: c mod 4 param
    // Unused column: c mod 4 min
    // Unused column: c mod 4 max
    // Unused column: c mod 5
    // Unused column: c mod 5 chance
    // Unused column: c mod 5 param
    // Unused column: c mod 5 min
    // Unused column: c mod 5 max
    int32_t eol = 0;	// Column 105

    size_t read(const char* line);
    static std::vector<t_cubemain> readfile(std::string filename);
  };

  struct t_cubemod {
    std::string cubemodifiertype = "";	// Column 0
    std::string Code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_cubemod> readfile(std::string filename);
  };

  struct t_difficultylevels {
    std::string Name = "";	// Column 0
    int32_t ResistPenalty = 0;	// Column 1
    int32_t ResistPenaltyNonExpansion = 0;	// Column 2
    int32_t DeathExpPenalty = 0;	// Column 3
    int32_t MonsterSkillBonus = 0;	// Column 4
    int32_t MonsterFreezeDivisor = 0;	// Column 5
    int32_t MonsterColdDivisor = 0;	// Column 6
    int32_t AiCurseDivisor = 0;	// Column 7
    int32_t LifeStealDivisor = 0;	// Column 8
    int32_t ManaStealDivisor = 0;	// Column 9
    int32_t UniqueDamageBonus = 0;	// Column 10
    int32_t ChampionDamageBonus = 0;	// Column 11
    int32_t PlayerDamagePercentVSPlayer = 0;	// Column 12
    int32_t PlayerDamagePercentVSMercenary = 0;	// Column 13
    int32_t PlayerDamagePercentVSPrimeEvil = 0;	// Column 14
    int32_t PlayerHitReactBufferVSPlayer = 0;	// Column 15
    int32_t PlayerHitReactBufferVSMonster = 0;	// Column 16
    int32_t MercenaryDamagePercentVSPlayer = 0;	// Column 17
    int32_t MercenaryDamagePercentVSMercenary = 0;	// Column 18
    int32_t MercenaryDamagePercentVSBoss = 0;	// Column 19
    int32_t MercenaryMaxStunLength = 0;	// Column 20
    int32_t PrimeEvilDamagePercentVSPlayer = 0;	// Column 21
    int32_t PrimeEvilDamagePercentVSMercenary = 0;	// Column 22
    int32_t PrimeEvilDamagePercentVSPet = 0;	// Column 23
    int32_t PetDamagePercentVSPlayer = 0;	// Column 24
    int32_t MonsterCEDamagePercent = 0;	// Column 25
    int32_t MonsterFireEnchantExplosionDamagePercent = 0;	// Column 26
    int32_t StaticFieldMin = 0;	// Column 27
    int32_t GambleRare = 0;	// Column 28
    int32_t GambleSet = 0;	// Column 29
    int32_t GambleUnique = 0;	// Column 30
    int32_t GambleUber = 0;	// Column 31
    int32_t GambleUltra = 0;	// Column 32
    int32_t ResistFloor = 0;	// Column 33

    size_t read(const char* line);
    static std::vector<t_difficultylevels> readfile(std::string filename);
  };

  struct t_elemtypes {
    std::string ElementalType = "";	// Column 0
    std::string Code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_elemtypes> readfile(std::string filename);
  };

  struct t_events {
    std::string event = "";	// Column 0
    std::string description = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_events> readfile(std::string filename);
  };

  struct t_experience {
    std::string Level = "";	// Column 0
    int32_t Amazon = 0;	// Column 1
    int32_t Sorceress = 0;	// Column 2
    int32_t Necromancer = 0;	// Column 3
    int32_t Paladin = 0;	// Column 4
    int32_t Barbarian = 0;	// Column 5
    int32_t Druid = 0;	// Column 6
    int32_t Assassin = 0;	// Column 7
    int32_t Warlock = 0;	// Column 8
    int32_t ExpRatio = 0;	// Column 9

    size_t read(const char* line);
    static std::vector<t_experience> readfile(std::string filename);
  };

  struct t_gamble {
    std::string name = "";	// Column 0
    std::string code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_gamble> readfile(std::string filename);
  };

  struct t_gems {
    std::string name = "";	// Column 0
    std::string letter = "";	// Column 1
    int32_t transform = 0;	// Column 2
    std::string code = "";	// Column 3
    std::string weaponMod1Code = "";	// Column 4
    int32_t weaponMod1Param = 0;	// Column 5
    int32_t weaponMod1Min = 0;	// Column 6
    int32_t weaponMod1Max = 0;	// Column 7
    std::string weaponMod2Code = "";	// Column 8
    int32_t weaponMod2Param = 0;	// Column 9
    int32_t weaponMod2Min = 0;	// Column 10
    int32_t weaponMod2Max = 0;	// Column 11
    std::string weaponMod3Code = "";	// Column 12
    int32_t weaponMod3Param = 0;	// Column 13
    int32_t weaponMod3Min = 0;	// Column 14
    int32_t weaponMod3Max = 0;	// Column 15
    std::string helmMod1Code = "";	// Column 16
    int32_t helmMod1Param = 0;	// Column 17
    int32_t helmMod1Min = 0;	// Column 18
    int32_t helmMod1Max = 0;	// Column 19
    std::string helmMod2Code = "";	// Column 20
    int32_t helmMod2Param = 0;	// Column 21
    int32_t helmMod2Min = 0;	// Column 22
    int32_t helmMod2Max = 0;	// Column 23
    // Unused column: helmMod3Code
    int32_t helmMod3Param = 0;	// Column 25
    int32_t helmMod3Min = 0;	// Column 26
    int32_t helmMod3Max = 0;	// Column 27
    std::string shieldMod1Code = "";	// Column 28
    int32_t shieldMod1Param = 0;	// Column 29
    int32_t shieldMod1Min = 0;	// Column 30
    int32_t shieldMod1Max = 0;	// Column 31
    std::string shieldMod2Code = "";	// Column 32
    int32_t shieldMod2Param = 0;	// Column 33
    int32_t shieldMod2Min = 0;	// Column 34
    int32_t shieldMod2Max = 0;	// Column 35
    // Unused column: shieldMod3Code
    int32_t shieldMod3Param = 0;	// Column 37
    int32_t shieldMod3Min = 0;	// Column 38
    int32_t shieldMod3Max = 0;	// Column 39

    size_t read(const char* line);
    static std::vector<t_gems> readfile(std::string filename);
  };

  struct t_hireling {
    std::string Hireling = "";	// Column 0
    std::string SubType = "";	// Column 1
    int32_t Version = 0;	// Column 2
    int32_t Id = 0;	// Column 3
    int32_t Class = 0;	// Column 4
    int32_t Act = 0;	// Column 5
    int32_t Difficulty = 0;	// Column 6
    int32_t Level = 0;	// Column 7
    int32_t Seller = 0;	// Column 8
    std::string NameFirst = "";	// Column 9
    std::string NameLast = "";	// Column 10
    int32_t Gold = 0;	// Column 11
    int32_t ExpLvl = 0;	// Column 12
    int32_t HP = 0;	// Column 13
    int32_t HPLvl = 0;	// Column 14
    int32_t Defense = 0;	// Column 15
    int32_t DefLvl = 0;	// Column 16
    int32_t Str = 0;	// Column 17
    int32_t StrLvl = 0;	// Column 18
    int32_t Dex = 0;	// Column 19
    int32_t DexLvl = 0;	// Column 20
    int32_t AR = 0;	// Column 21
    int32_t ARLvl = 0;	// Column 22
    int32_t DmgMin = 0;	// Column 23
    int32_t DmgMax = 0;	// Column 24
    int32_t DmgLvl = 0;	// Column 25
    int32_t ResistFire = 0;	// Column 26
    int32_t ResistFireLvl = 0;	// Column 27
    int32_t ResistCold = 0;	// Column 28
    int32_t ResistColdLvl = 0;	// Column 29
    int32_t ResistLightning = 0;	// Column 30
    int32_t ResistLightningLvl = 0;	// Column 31
    int32_t ResistPoison = 0;	// Column 32
    int32_t ResistPoisonLvl = 0;	// Column 33
    std::string HireDesc = "";	// Column 34
    int32_t DefaultChance = 0;	// Column 35
    std::string Skill1 = "";	// Column 36
    int32_t Mode1 = 0;	// Column 37
    int32_t Chance1 = 0;	// Column 38
    int32_t ChancePerLvl1 = 0;	// Column 39
    int32_t Level1 = 0;	// Column 40
    int32_t LvlPerLvl1 = 0;	// Column 41
    std::string Skill2 = "";	// Column 42
    int32_t Mode2 = 0;	// Column 43
    int32_t Chance2 = 0;	// Column 44
    int32_t ChancePerLvl2 = 0;	// Column 45
    int32_t Level2 = 0;	// Column 46
    int32_t LvlPerLvl2 = 0;	// Column 47
    std::string Skill3 = "";	// Column 48
    int32_t Mode3 = 0;	// Column 49
    int32_t Chance3 = 0;	// Column 50
    int32_t ChancePerLvl3 = 0;	// Column 51
    int32_t Level3 = 0;	// Column 52
    int32_t LvlPerLvl3 = 0;	// Column 53
    // Unused column: Skill4
    // Unused column: Mode4
    // Unused column: Chance4
    // Unused column: ChancePerLvl4
    // Unused column: Level4
    // Unused column: LvlPerLvl4
    // Unused column: Skill5
    // Unused column: Mode5
    // Unused column: Chance5
    // Unused column: ChancePerLvl5
    // Unused column: Level5
    // Unused column: LvlPerLvl5
    // Unused column: Skill6
    // Unused column: Mode6
    // Unused column: Chance6
    // Unused column: ChancePerLvl6
    // Unused column: Level6
    // Unused column: LvlPerLvl6
    int32_t HiringMaxLevelDifference = 0;	// Column 72
    int32_t resurrectcostmultiplier = 0;	// Column 73
    int32_t resurrectcostdivisor = 0;	// Column 74
    int32_t resurrectcostmax = 0;	// Column 75
    std::string equivalentcharclass = "";	// Column 76

    size_t read(const char* line);
    static std::vector<t_hireling> readfile(std::string filename);
  };

  struct t_hitclass {
    std::string HitClass = "";	// Column 0
    std::string Code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_hitclass> readfile(std::string filename);
  };

  struct t_inventory {
    std::string _class = "";	// Column 0
    int32_t invLeft = 0;	// Column 1
    int32_t invRight = 0;	// Column 2
    int32_t invTop = 0;	// Column 3
    int32_t invBottom = 0;	// Column 4
    int32_t gridX = 0;	// Column 5
    int32_t gridY = 0;	// Column 6
    int32_t gridLeft = 0;	// Column 7
    int32_t gridRight = 0;	// Column 8
    int32_t gridTop = 0;	// Column 9
    int32_t gridBottom = 0;	// Column 10
    int32_t gridBoxWidth = 0;	// Column 11
    int32_t gridBoxHeight = 0;	// Column 12
    int32_t rArmLeft = 0;	// Column 13
    int32_t rArmRight = 0;	// Column 14
    int32_t rArmTop = 0;	// Column 15
    int32_t rArmBottom = 0;	// Column 16
    int32_t rArmWidth = 0;	// Column 17
    int32_t rArmHeight = 0;	// Column 18
    int32_t torsoLeft = 0;	// Column 19
    int32_t torsoRight = 0;	// Column 20
    int32_t torsoTop = 0;	// Column 21
    int32_t torsoBottom = 0;	// Column 22
    int32_t torsoWidth = 0;	// Column 23
    int32_t torsoHeight = 0;	// Column 24
    int32_t lArmLeft = 0;	// Column 25
    int32_t lArmRight = 0;	// Column 26
    int32_t lArmTop = 0;	// Column 27
    int32_t lArmBottom = 0;	// Column 28
    int32_t lArmWidth = 0;	// Column 29
    int32_t lArmHeight = 0;	// Column 30
    int32_t headLeft = 0;	// Column 31
    int32_t headRight = 0;	// Column 32
    int32_t headTop = 0;	// Column 33
    int32_t headBottom = 0;	// Column 34
    int32_t headWidth = 0;	// Column 35
    int32_t headHeight = 0;	// Column 36
    int32_t neckLeft = 0;	// Column 37
    int32_t neckRight = 0;	// Column 38
    int32_t neckTop = 0;	// Column 39
    int32_t neckBottom = 0;	// Column 40
    int32_t neckWidth = 0;	// Column 41
    int32_t neckHeight = 0;	// Column 42
    int32_t rHandLeft = 0;	// Column 43
    int32_t rHandRight = 0;	// Column 44
    int32_t rHandTop = 0;	// Column 45
    int32_t rHandBottom = 0;	// Column 46
    int32_t rHandWidth = 0;	// Column 47
    int32_t rHandHeight = 0;	// Column 48
    int32_t lHandLeft = 0;	// Column 49
    int32_t lHandRight = 0;	// Column 50
    int32_t lHandTop = 0;	// Column 51
    int32_t lHandBottom = 0;	// Column 52
    int32_t lHandWidth = 0;	// Column 53
    int32_t lHandHeight = 0;	// Column 54
    int32_t beltLeft = 0;	// Column 55
    int32_t beltRight = 0;	// Column 56
    int32_t beltTop = 0;	// Column 57
    int32_t beltBottom = 0;	// Column 58
    int32_t beltWidth = 0;	// Column 59
    int32_t beltHeight = 0;	// Column 60
    int32_t feetLeft = 0;	// Column 61
    int32_t feetRight = 0;	// Column 62
    int32_t feetTop = 0;	// Column 63
    int32_t feetBottom = 0;	// Column 64
    int32_t feetWidth = 0;	// Column 65
    int32_t feetHeight = 0;	// Column 66
    int32_t glovesLeft = 0;	// Column 67
    int32_t glovesRight = 0;	// Column 68
    int32_t glovesTop = 0;	// Column 69
    int32_t glovesBottom = 0;	// Column 70
    int32_t glovesWidth = 0;	// Column 71
    int32_t glovesHeight = 0;	// Column 72

    size_t read(const char* line);
    static std::vector<t_inventory> readfile(std::string filename);
  };

  struct t_itemratio {
    std::string Function = "";	// Column 0
    int32_t Version = 0;	// Column 1
    int32_t Uber = 0;	// Column 2
    int32_t ClassSpecific = 0;	// Column 3
    int32_t Unique = 0;	// Column 4
    int32_t UniqueDivisor = 0;	// Column 5
    int32_t UniqueMin = 0;	// Column 6
    int32_t Rare = 0;	// Column 7
    int32_t RareDivisor = 0;	// Column 8
    int32_t RareMin = 0;	// Column 9
    int32_t Set = 0;	// Column 10
    int32_t SetDivisor = 0;	// Column 11
    int32_t SetMin = 0;	// Column 12
    int32_t Magic = 0;	// Column 13
    int32_t MagicDivisor = 0;	// Column 14
    int32_t MagicMin = 0;	// Column 15
    int32_t HiQuality = 0;	// Column 16
    int32_t HiQualityDivisor = 0;	// Column 17
    int32_t Normal = 0;	// Column 18
    int32_t NormalDivisor = 0;	// Column 19

    size_t read(const char* line);
    static std::vector<t_itemratio> readfile(std::string filename);
  };

  struct t_itemstatcost {
    std::string Stat = "";	// Column 0
    int32_t ID = 0;	// Column 1
    int32_t SendOther = 0;	// Column 2
    int32_t Signed = 0;	// Column 3
    int32_t SendBits = 0;	// Column 4
    int32_t SendParamBits = 0;	// Column 5
    int32_t UpdateAnimRate = 0;	// Column 6
    int32_t Saved = 0;	// Column 7
    int32_t CSvSigned = 0;	// Column 8
    int32_t CSvBits = 0;	// Column 9
    // Unused column: CSvParam
    int32_t fCallback = 0;	// Column 11
    int32_t fMin = 0;	// Column 12
    int32_t MinAccr = 0;	// Column 13
    int32_t Encode = 0;	// Column 14
    int32_t Add = 0;	// Column 15
    int32_t Multiply = 0;	// Column 16
    int32_t ValShift = 0;	// Column 17
    int32_t _109SaveBits = 0;	// Column 18
    int32_t _109SaveAdd = 0;	// Column 19
    int32_t SaveBits = 0;	// Column 20
    int32_t SaveAdd = 0;	// Column 21
    int32_t SaveParamBits = 0;	// Column 22
    int32_t keepzero = 0;	// Column 23
    int32_t op = 0;	// Column 24
    int32_t opparam = 0;	// Column 25
    std::string opbase = "";	// Column 26
    std::string opstat1 = "";	// Column 27
    std::string opstat2 = "";	// Column 28
    std::string opstat3 = "";	// Column 29
    int32_t direct = 0;	// Column 30
    std::string maxstat = "";	// Column 31
    int32_t damagerelated = 0;	// Column 32
    std::string itemevent1 = "";	// Column 33
    int32_t itemeventfunc1 = 0;	// Column 34
    std::string itemevent2 = "";	// Column 35
    int32_t itemeventfunc2 = 0;	// Column 36
    int32_t descpriority = 0;	// Column 37
    int32_t descfunc = 0;	// Column 38
    int32_t descval = 0;	// Column 39
    std::string descstrpos = "";	// Column 40
    std::string descstrneg = "";	// Column 41
    std::string descstr2 = "";	// Column 42
    int32_t dgrp = 0;	// Column 43
    int32_t dgrpfunc = 0;	// Column 44
    // Unused column: dgrpval
    std::string dgrpstrpos = "";	// Column 46
    std::string dgrpstrneg = "";	// Column 47
    // Unused column: dgrpstr2
    int32_t stuff = 0;	// Column 49
    int32_t advdisplay = 0;	// Column 50
    int32_t eol = 0;	// Column 51

    size_t read(const char* line);
    static std::vector<t_itemstatcost> readfile(std::string filename);
  };

  struct t_itemtypes {
    std::string ItemType = "";	// Column 0
    std::string Code = "";	// Column 1
    std::string Equiv1 = "";	// Column 2
    std::string Equiv2 = "";	// Column 3
    int32_t Repair = 0;	// Column 4
    int32_t Body = 0;	// Column 5
    std::string BodyLoc1 = "";	// Column 6
    std::string BodyLoc2 = "";	// Column 7
    std::string Shoots = "";	// Column 8
    std::string Quiver = "";	// Column 9
    int32_t Throwable = 0;	// Column 10
    int32_t Reload = 0;	// Column 11
    int32_t ReEquip = 0;	// Column 12
    int32_t AutoStack = 0;	// Column 13
    int32_t Magic = 0;	// Column 14
    int32_t Rare = 0;	// Column 15
    int32_t Normal = 0;	// Column 16
    int32_t Beltable = 0;	// Column 17
    int32_t MaxSockets1 = 0;	// Column 18
    int32_t MaxSocketsLevelThreshold1 = 0;	// Column 19
    int32_t MaxSockets2 = 0;	// Column 20
    int32_t MaxSocketsLevelThreshold2 = 0;	// Column 21
    int32_t MaxSockets3 = 0;	// Column 22
    int32_t TreasureClass = 0;	// Column 23
    int32_t Rarity = 0;	// Column 24
    std::string StaffMods = "";	// Column 25
    std::string Class = "";	// Column 26
    int32_t VarInvGfx = 0;	// Column 27
    std::string InvGfx1 = "";	// Column 28
    std::string InvGfx2 = "";	// Column 29
    std::string InvGfx3 = "";	// Column 30
    std::string InvGfx4 = "";	// Column 31
    std::string InvGfx5 = "";	// Column 32
    std::string InvGfx6 = "";	// Column 33
    std::string StorePage = "";	// Column 34
    int32_t eol = 0;	// Column 35
    std::string UICategory = "";	// Column 36
    std::string RunewordCategory1 = "";	// Column 37
    std::string RunewordCategory2 = "";	// Column 38
    int32_t Restricted = 0;	// Column 39

    size_t read(const char* line);
    static std::vector<t_itemtypes> readfile(std::string filename);
  };

  struct t_itemuicategories {
    std::string Name = "";	// Column 0
    int32_t isEquipment = 0;	// Column 1
    std::string ParentCategory = "";	// Column 2
    int32_t QualityFilter = 0;	// Column 3
    int32_t NumColumns = 0;	// Column 4

    size_t read(const char* line);
    static std::vector<t_itemuicategories> readfile(std::string filename);
  };

  struct t_levelgroups {
    std::string LevelGroupId = "";	// Column 0
    std::string ParentLevelGroupId = "";	// Column 1
    int32_t CompleteThreshold = 0;	// Column 2
    int32_t Effect = 0;	// Column 3
    std::string Name = "";	// Column 4
    std::string NameString = "";	// Column 5

    size_t read(const char* line);
    static std::vector<t_levelgroups> readfile(std::string filename);
  };

  struct t_levels {
    std::string Name = "";	// Column 0
    std::string StringName = "";	// Column 1
    int32_t Id = 0;	// Column 2
    int32_t Pal = 0;	// Column 3
    int32_t Act = 0;	// Column 4
    int32_t QuestFlag = 0;	// Column 5
    int32_t QuestFlagEx = 0;	// Column 6
    int32_t Layer = 0;	// Column 7
    int32_t SizeX = 0;	// Column 8
    int32_t SizeY = 0;	// Column 9
    int32_t SizeXN = 0;	// Column 10
    int32_t SizeYN = 0;	// Column 11
    int32_t SizeXH = 0;	// Column 12
    int32_t SizeYH = 0;	// Column 13
    int32_t OffsetX = 0;	// Column 14
    int32_t OffsetY = 0;	// Column 15
    int32_t CompletionTotalRoomsOverride = 0;	// Column 16
    int32_t Depend = 0;	// Column 17
    int32_t Teleport = 0;	// Column 18
    int32_t Rain = 0;	// Column 19
    int32_t Mud = 0;	// Column 20
    int32_t NoPer = 0;	// Column 21
    int32_t LOSDraw = 0;	// Column 22
    int32_t FloorFilter = 0;	// Column 23
    int32_t BlankScreen = 0;	// Column 24
    int32_t DrawEdges = 0;	// Column 25
    int32_t IsInside = 0;	// Column 26
    int32_t DrlgType = 0;	// Column 27
    int32_t LevelType = 0;	// Column 28
    int32_t SubType = 0;	// Column 29
    int32_t SubTheme = 0;	// Column 30
    int32_t SubWaypoint = 0;	// Column 31
    int32_t SubShrine = 0;	// Column 32
    int32_t Vis0 = 0;	// Column 33
    int32_t Vis1 = 0;	// Column 34
    int32_t Vis2 = 0;	// Column 35
    int32_t Vis3 = 0;	// Column 36
    int32_t Vis4 = 0;	// Column 37
    int32_t Vis5 = 0;	// Column 38
    int32_t Vis6 = 0;	// Column 39
    int32_t Vis7 = 0;	// Column 40
    int32_t Warp0 = 0;	// Column 41
    int32_t Warp1 = 0;	// Column 42
    int32_t Warp2 = 0;	// Column 43
    int32_t Warp3 = 0;	// Column 44
    int32_t Warp4 = 0;	// Column 45
    int32_t Warp5 = 0;	// Column 46
    int32_t Warp6 = 0;	// Column 47
    int32_t Warp7 = 0;	// Column 48
    int32_t Intensity = 0;	// Column 49
    int32_t Red = 0;	// Column 50
    int32_t Green = 0;	// Column 51
    int32_t Blue = 0;	// Column 52
    int32_t Portal = 0;	// Column 53
    int32_t Position = 0;	// Column 54
    int32_t SaveMonsters = 0;	// Column 55
    int32_t Quest = 0;	// Column 56
    int32_t WarpDist = 0;	// Column 57
    int32_t MonLvl = 0;	// Column 58
    int32_t MonLvlN = 0;	// Column 59
    int32_t MonLvlH = 0;	// Column 60
    int32_t MonLvlEx = 0;	// Column 61
    int32_t MonLvlExN = 0;	// Column 62
    int32_t MonLvlExH = 0;	// Column 63
    int32_t MonDen = 0;	// Column 64
    int32_t MonDenN = 0;	// Column 65
    int32_t MonDenH = 0;	// Column 66
    int32_t MonUMin = 0;	// Column 67
    int32_t MonUMax = 0;	// Column 68
    int32_t MonUMinN = 0;	// Column 69
    int32_t MonUMaxN = 0;	// Column 70
    int32_t MonUMinH = 0;	// Column 71
    int32_t MonUMaxH = 0;	// Column 72
    int32_t MonWndr = 0;	// Column 73
    int32_t MonSpcWalk = 0;	// Column 74
    int32_t NumMon = 0;	// Column 75
    std::string mon1 = "";	// Column 76
    std::string mon2 = "";	// Column 77
    std::string mon3 = "";	// Column 78
    std::string mon4 = "";	// Column 79
    std::string mon5 = "";	// Column 80
    std::string mon6 = "";	// Column 81
    std::string mon7 = "";	// Column 82
    std::string mon8 = "";	// Column 83
    // Unused column: mon9
    // Unused column: mon10
    // Unused column: mon11
    // Unused column: mon12
    // Unused column: mon13
    // Unused column: mon14
    // Unused column: mon15
    // Unused column: mon16
    // Unused column: mon17
    // Unused column: mon18
    // Unused column: mon19
    // Unused column: mon20
    // Unused column: mon21
    // Unused column: mon22
    // Unused column: mon23
    // Unused column: mon24
    // Unused column: mon25
    int32_t rangedspawn = 0;	// Column 101
    std::string nmon1 = "";	// Column 102
    std::string nmon2 = "";	// Column 103
    std::string nmon3 = "";	// Column 104
    std::string nmon4 = "";	// Column 105
    std::string nmon5 = "";	// Column 106
    std::string nmon6 = "";	// Column 107
    std::string nmon7 = "";	// Column 108
    std::string nmon8 = "";	// Column 109
    std::string nmon9 = "";	// Column 110
    std::string nmon10 = "";	// Column 111
    // Unused column: nmon11
    // Unused column: nmon12
    // Unused column: nmon13
    // Unused column: nmon14
    // Unused column: nmon15
    // Unused column: nmon16
    // Unused column: nmon17
    // Unused column: nmon18
    // Unused column: nmon19
    // Unused column: nmon20
    // Unused column: nmon21
    // Unused column: nmon22
    // Unused column: nmon23
    // Unused column: nmon24
    // Unused column: nmon25
    std::string umon1 = "";	// Column 127
    std::string umon2 = "";	// Column 128
    std::string umon3 = "";	// Column 129
    std::string umon4 = "";	// Column 130
    std::string umon5 = "";	// Column 131
    std::string umon6 = "";	// Column 132
    std::string umon7 = "";	// Column 133
    std::string umon8 = "";	// Column 134
    // Unused column: umon9
    // Unused column: umon10
    // Unused column: umon11
    // Unused column: umon12
    // Unused column: umon13
    // Unused column: umon14
    // Unused column: umon15
    // Unused column: umon16
    // Unused column: umon17
    // Unused column: umon18
    // Unused column: umon19
    // Unused column: umon20
    // Unused column: umon21
    // Unused column: umon22
    // Unused column: umon23
    // Unused column: umon24
    // Unused column: umon25
    std::string cmon1 = "";	// Column 152
    std::string cmon2 = "";	// Column 153
    std::string cmon3 = "";	// Column 154
    std::string cmon4 = "";	// Column 155
    int32_t cpct1 = 0;	// Column 156
    int32_t cpct2 = 0;	// Column 157
    int32_t cpct3 = 0;	// Column 158
    int32_t cpct4 = 0;	// Column 159
    // Unused column: camt1
    // Unused column: camt2
    // Unused column: camt3
    // Unused column: camt4
    int32_t Themes = 0;	// Column 164
    int32_t SoundEnv = 0;	// Column 165
    int32_t Waypoint = 0;	// Column 166
    std::string LevelName = "";	// Column 167
    std::string LevelWarp = "";	// Column 168
    std::string LevelEntry = "";	// Column 169
    int32_t ObjGrp0 = 0;	// Column 170
    int32_t ObjGrp1 = 0;	// Column 171
    int32_t ObjGrp2 = 0;	// Column 172
    int32_t ObjGrp3 = 0;	// Column 173
    int32_t ObjGrp4 = 0;	// Column 174
    int32_t ObjGrp5 = 0;	// Column 175
    int32_t ObjGrp6 = 0;	// Column 176
    int32_t ObjGrp7 = 0;	// Column 177
    int32_t ObjPrb0 = 0;	// Column 178
    int32_t ObjPrb1 = 0;	// Column 179
    int32_t ObjPrb2 = 0;	// Column 180
    int32_t ObjPrb3 = 0;	// Column 181
    int32_t ObjPrb4 = 0;	// Column 182
    int32_t ObjPrb5 = 0;	// Column 183
    int32_t ObjPrb6 = 0;	// Column 184
    int32_t ObjPrb7 = 0;	// Column 185
    std::string LevelGroup = "";	// Column 186
    int32_t PreventTownPortal = 0;	// Column 187

    size_t read(const char* line);
    static std::vector<t_levels> readfile(std::string filename);
  };

  struct t_lowqualityitems {
    std::string Name = "";	// Column 0

    size_t read(const char* line);
    static std::vector<t_lowqualityitems> readfile(std::string filename);
  };

  struct t_lvlmaze {
    std::string Name = "";	// Column 0
    int32_t Level = 0;	// Column 1
    int32_t Rooms = 0;	// Column 2
    int32_t RoomsN = 0;	// Column 3
    int32_t RoomsH = 0;	// Column 4
    int32_t SizeX = 0;	// Column 5
    int32_t SizeY = 0;	// Column 6
    int32_t Merge = 0;	// Column 7

    size_t read(const char* line);
    static std::vector<t_lvlmaze> readfile(std::string filename);
  };

  struct t_lvlprest {
    std::string Name = "";	// Column 0
    int32_t Def = 0;	// Column 1
    int32_t LevelId = 0;	// Column 2
    int32_t Populate = 0;	// Column 3
    int32_t Logicals = 0;	// Column 4
    int32_t Outdoors = 0;	// Column 5
    int32_t Animate = 0;	// Column 6
    int32_t KillEdge = 0;	// Column 7
    int32_t FillBlanks = 0;	// Column 8
    int32_t SizeX = 0;	// Column 9
    int32_t SizeY = 0;	// Column 10
    int32_t AutoMap = 0;	// Column 11
    int32_t Scan = 0;	// Column 12
    int32_t Pops = 0;	// Column 13
    int32_t PopPad = 0;	// Column 14
    int32_t Files = 0;	// Column 15
    std::string File1 = "";	// Column 16
    std::string File2 = "";	// Column 17
    std::string File3 = "";	// Column 18
    std::string File4 = "";	// Column 19
    std::string File5 = "";	// Column 20
    std::string File6 = "";	// Column 21
    int32_t Dt1Mask = 0;	// Column 22

    size_t read(const char* line);
    static std::vector<t_lvlprest> readfile(std::string filename);
  };

  struct t_lvlsub {
    std::string Name = "";	// Column 0
    int32_t Type = 0;	// Column 1
    std::string File = "";	// Column 2
    int32_t CheckAll = 0;	// Column 3
    int32_t BordType = 0;	// Column 4
    int32_t GridSize = 0;	// Column 5
    int32_t Dt1Mask = 0;	// Column 6
    int32_t Prob0 = 0;	// Column 7
    int32_t Trials0 = 0;	// Column 8
    int32_t Max0 = 0;	// Column 9
    int32_t Prob1 = 0;	// Column 10
    int32_t Trials1 = 0;	// Column 11
    int32_t Max1 = 0;	// Column 12
    int32_t Prob2 = 0;	// Column 13
    int32_t Trials2 = 0;	// Column 14
    int32_t Max2 = 0;	// Column 15
    int32_t Prob3 = 0;	// Column 16
    int32_t Trials3 = 0;	// Column 17
    int32_t Max3 = 0;	// Column 18
    int32_t Prob4 = 0;	// Column 19
    int32_t Trials4 = 0;	// Column 20
    int32_t Max4 = 0;	// Column 21

    size_t read(const char* line);
    static std::vector<t_lvlsub> readfile(std::string filename);
  };

  struct t_lvltypes {
    std::string Name = "";	// Column 0
    int32_t Id = 0;	// Column 1
    std::string File1 = "";	// Column 2
    std::string File2 = "";	// Column 3
    std::string File3 = "";	// Column 4
    std::string File4 = "";	// Column 5
    std::string File5 = "";	// Column 6
    std::string File6 = "";	// Column 7
    std::string File7 = "";	// Column 8
    std::string File8 = "";	// Column 9
    std::string File9 = "";	// Column 10
    std::string File10 = "";	// Column 11
    std::string File11 = "";	// Column 12
    std::string File12 = "";	// Column 13
    std::string File13 = "";	// Column 14
    std::string File14 = "";	// Column 15
    std::string File15 = "";	// Column 16
    std::string File16 = "";	// Column 17
    std::string File17 = "";	// Column 18
    std::string File18 = "";	// Column 19
    std::string File19 = "";	// Column 20
    std::string File20 = "";	// Column 21
    std::string File21 = "";	// Column 22
    std::string File22 = "";	// Column 23
    std::string File23 = "";	// Column 24
    std::string File24 = "";	// Column 25
    std::string File25 = "";	// Column 26
    std::string File26 = "";	// Column 27
    std::string File27 = "";	// Column 28
    std::string File28 = "";	// Column 29
    std::string File29 = "";	// Column 30
    std::string File30 = "";	// Column 31
    std::string File31 = "";	// Column 32
    int32_t File32 = 0;	// Column 33
    int32_t Act = 0;	// Column 34

    size_t read(const char* line);
    static std::vector<t_lvltypes> readfile(std::string filename);
  };

  struct t_lvlwarp {
    std::string Name = "";	// Column 0
    int32_t Id = 0;	// Column 1
    int32_t SelectX = 0;	// Column 2
    int32_t SelectY = 0;	// Column 3
    int32_t SelectDX = 0;	// Column 4
    int32_t SelectDY = 0;	// Column 5
    int32_t ExitWalkX = 0;	// Column 6
    int32_t ExitWalkY = 0;	// Column 7
    int32_t OffsetX = 0;	// Column 8
    int32_t OffsetY = 0;	// Column 9
    int32_t LitVersion = 0;	// Column 10
    int32_t Tiles = 0;	// Column 11
    int32_t NoInteract = 0;	// Column 12
    std::string Direction = "";	// Column 13
    int32_t UniqueId = 0;	// Column 14

    size_t read(const char* line);
    static std::vector<t_lvlwarp> readfile(std::string filename);
  };

  struct t_magicprefix {
    std::string Name = "";	// Column 0
    int32_t version = 0;	// Column 1
    int32_t spawnable = 0;	// Column 2
    int32_t rare = 0;	// Column 3
    int32_t level = 0;	// Column 4
    int32_t maxlevel = 0;	// Column 5
    int32_t levelreq = 0;	// Column 6
    std::string classspecific = "";	// Column 7
    // Unused column: class
    // Unused column: classlevelreq
    int32_t frequency = 0;	// Column 10
    int32_t group = 0;	// Column 11
    std::string mod1code = "";	// Column 12
    int32_t mod1param = 0;	// Column 13
    int32_t mod1min = 0;	// Column 14
    int32_t mod1max = 0;	// Column 15
    std::string mod2code = "";	// Column 16
    int32_t mod2param = 0;	// Column 17
    int32_t mod2min = 0;	// Column 18
    int32_t mod2max = 0;	// Column 19
    std::string mod3code = "";	// Column 20
    // Unused column: mod3param
    int32_t mod3min = 0;	// Column 22
    int32_t mod3max = 0;	// Column 23
    std::string transformcolor = "";	// Column 24
    std::string itype1 = "";	// Column 25
    std::string itype2 = "";	// Column 26
    std::string itype3 = "";	// Column 27
    std::string itype4 = "";	// Column 28
    std::string itype5 = "";	// Column 29
    std::string itype6 = "";	// Column 30
    std::string itype7 = "";	// Column 31
    std::string etype1 = "";	// Column 32
    std::string etype2 = "";	// Column 33
    std::string etype3 = "";	// Column 34
    std::string etype4 = "";	// Column 35
    std::string etype5 = "";	// Column 36
    int32_t multiply = 0;	// Column 37
    int32_t add = 0;	// Column 38

    size_t read(const char* line);
    static std::vector<t_magicprefix> readfile(std::string filename);
  };

  struct t_magicsuffix {
    std::string Name = "";	// Column 0
    int32_t version = 0;	// Column 1
    int32_t spawnable = 0;	// Column 2
    int32_t rare = 0;	// Column 3
    int32_t level = 0;	// Column 4
    int32_t maxlevel = 0;	// Column 5
    int32_t levelreq = 0;	// Column 6
    // Unused column: classspecific
    std::string _class = "";	// Column 8
    int32_t classlevelreq = 0;	// Column 9
    int32_t frequency = 0;	// Column 10
    int32_t group = 0;	// Column 11
    std::string mod1code = "";	// Column 12
    int32_t mod1param = 0;	// Column 13
    int32_t mod1min = 0;	// Column 14
    int32_t mod1max = 0;	// Column 15
    std::string mod2code = "";	// Column 16
    int32_t mod2param = 0;	// Column 17
    int32_t mod2min = 0;	// Column 18
    int32_t mod2max = 0;	// Column 19
    std::string mod3code = "";	// Column 20
    int32_t mod3param = 0;	// Column 21
    int32_t mod3min = 0;	// Column 22
    int32_t mod3max = 0;	// Column 23
    std::string transformcolor = "";	// Column 24
    std::string itype1 = "";	// Column 25
    std::string itype2 = "";	// Column 26
    std::string itype3 = "";	// Column 27
    std::string itype4 = "";	// Column 28
    std::string itype5 = "";	// Column 29
    std::string itype6 = "";	// Column 30
    std::string itype7 = "";	// Column 31
    std::string etype1 = "";	// Column 32
    std::string etype2 = "";	// Column 33
    std::string etype3 = "";	// Column 34
    int32_t etype4 = 0;	// Column 35
    int32_t etype5 = 0;	// Column 36
    int32_t multiply = 0;	// Column 37
    int32_t add = 0;	// Column 38

    size_t read(const char* line);
    static std::vector<t_magicsuffix> readfile(std::string filename);
  };

  struct t_misc {
    std::string name = "";	// Column 0
    int32_t compactsave = 0;	// Column 1
    int32_t version = 0;	// Column 2
    int32_t level = 0;	// Column 3
    int32_t ShowLevel = 0;	// Column 4
    int32_t levelreq = 0;	// Column 5
    // Unused column: reqstr
    // Unused column: reqdex
    int32_t rarity = 0;	// Column 8
    int32_t spawnable = 0;	// Column 9
    // Unused column: DropConditionCalc
    int32_t speed = 0;	// Column 11
    int32_t nodurability = 0;	// Column 12
    int32_t cost = 0;	// Column 13
    int32_t gamblecost = 0;	// Column 14
    std::string code = "";	// Column 15
    std::string alternategfx = "";	// Column 16
    std::string namestr = "";	// Column 17
    int32_t component = 0;	// Column 18
    int32_t invwidth = 0;	// Column 19
    int32_t invheight = 0;	// Column 20
    int32_t hasinv = 0;	// Column 21
    int32_t gemsockets = 0;	// Column 22
    int32_t gemapplytype = 0;	// Column 23
    std::string flippyfile = "";	// Column 24
    std::string invfile = "";	// Column 25
    std::string uniqueinvfile = "";	// Column 26
    int32_t Transmogrify = 0;	// Column 27
    std::string TMogType = "";	// Column 28
    int32_t TMogMin = 0;	// Column 29
    int32_t TMogMax = 0;	// Column 30
    int32_t useable = 0;	// Column 31
    std::string type = "";	// Column 32
    std::string type2 = "";	// Column 33
    std::string dropsound = "";	// Column 34
    int32_t dropsfxframe = 0;	// Column 35
    std::string usesound = "";	// Column 36
    int32_t unique = 0;	// Column 37
    int32_t transparent = 0;	// Column 38
    int32_t transtbl = 0;	// Column 39
    int32_t lightradius = 0;	// Column 40
    int32_t belt = 0;	// Column 41
    int32_t autobelt = 0;	// Column 42
    int32_t stackable = 0;	// Column 43
    int32_t minstack = 0;	// Column 44
    int32_t maxstack = 0;	// Column 45
    int32_t spawnstack = 0;	// Column 46
    int32_t quest = 0;	// Column 47
    int32_t questdiffcheck = 0;	// Column 48
    int32_t missiletype = 0;	// Column 49
    int32_t spellicon = 0;	// Column 50
    int32_t pSpell = 0;	// Column 51
    std::string state = "";	// Column 52
    std::string cstate1 = "";	// Column 53
    std::string cstate2 = "";	// Column 54
    int32_t len = 0;	// Column 55
    std::string stat1 = "";	// Column 56
    int32_t calc1 = 0;	// Column 57
    std::string stat2 = "";	// Column 58
    int32_t calc2 = 0;	// Column 59
    // Unused column: stat3
    // Unused column: calc3
    int32_t spelldesc = 0;	// Column 62
    std::string spelldescstr = "";	// Column 63
    std::string spelldescstr2 = "";	// Column 64
    int32_t spelldesccalc = 0;	// Column 65
    int32_t spelldesccolor = 0;	// Column 66
    int32_t durwarning = 0;	// Column 67
    int32_t qntwarning = 0;	// Column 68
    int32_t gemoffset = 0;	// Column 69
    std::string BetterGem = "";	// Column 70
    int32_t bitfield1 = 0;	// Column 71
    int32_t CharsiMin = 0;	// Column 72
    int32_t CharsiMax = 0;	// Column 73
    // Unused column: CharsiMagicMin
    // Unused column: CharsiMagicMax
    int32_t CharsiMagicLvl = 0;	// Column 76
    int32_t GheedMin = 0;	// Column 77
    int32_t GheedMax = 0;	// Column 78
    int32_t GheedMagicMin = 0;	// Column 79
    int32_t GheedMagicMax = 0;	// Column 80
    int32_t GheedMagicLvl = 0;	// Column 81
    int32_t AkaraMin = 0;	// Column 82
    int32_t AkaraMax = 0;	// Column 83
    int32_t AkaraMagicMin = 0;	// Column 84
    int32_t AkaraMagicMax = 0;	// Column 85
    int32_t AkaraMagicLvl = 0;	// Column 86
    int32_t FaraMin = 0;	// Column 87
    int32_t FaraMax = 0;	// Column 88
    int32_t FaraMagicMin = 0;	// Column 89
    int32_t FaraMagicMax = 0;	// Column 90
    int32_t FaraMagicLvl = 0;	// Column 91
    int32_t LysanderMin = 0;	// Column 92
    int32_t LysanderMax = 0;	// Column 93
    int32_t LysanderMagicMin = 0;	// Column 94
    int32_t LysanderMagicMax = 0;	// Column 95
    int32_t LysanderMagicLvl = 0;	// Column 96
    int32_t DrognanMin = 0;	// Column 97
    int32_t DrognanMax = 0;	// Column 98
    int32_t DrognanMagicMin = 0;	// Column 99
    int32_t DrognanMagicMax = 0;	// Column 100
    int32_t DrognanMagicLvl = 0;	// Column 101
    int32_t HratliMin = 0;	// Column 102
    int32_t HratliMax = 0;	// Column 103
    int32_t HratliMagicMin = 0;	// Column 104
    int32_t HratliMagicMax = 0;	// Column 105
    int32_t HratliMagicLvl = 0;	// Column 106
    int32_t AlkorMin = 0;	// Column 107
    int32_t AlkorMax = 0;	// Column 108
    // Unused column: AlkorMagicMin
    // Unused column: AlkorMagicMax
    int32_t AlkorMagicLvl = 0;	// Column 111
    int32_t OrmusMin = 0;	// Column 112
    int32_t OrmusMax = 0;	// Column 113
    int32_t OrmusMagicMin = 0;	// Column 114
    int32_t OrmusMagicMax = 0;	// Column 115
    int32_t OrmusMagicLvl = 0;	// Column 116
    int32_t ElzixMin = 0;	// Column 117
    int32_t ElzixMax = 0;	// Column 118
    // Unused column: ElzixMagicMin
    // Unused column: ElzixMagicMax
    int32_t ElzixMagicLvl = 0;	// Column 121
    int32_t AshearaMin = 0;	// Column 122
    int32_t AshearaMax = 0;	// Column 123
    // Unused column: AshearaMagicMin
    // Unused column: AshearaMagicMax
    int32_t AshearaMagicLvl = 0;	// Column 126
    int32_t CainMin = 0;	// Column 127
    int32_t CainMax = 0;	// Column 128
    // Unused column: CainMagicMin
    // Unused column: CainMagicMax
    int32_t CainMagicLvl = 0;	// Column 131
    int32_t HalbuMin = 0;	// Column 132
    int32_t HalbuMax = 0;	// Column 133
    // Unused column: HalbuMagicMin
    // Unused column: HalbuMagicMax
    int32_t HalbuMagicLvl = 0;	// Column 136
    int32_t MalahMin = 0;	// Column 137
    int32_t MalahMax = 0;	// Column 138
    // Unused column: MalahMagicMin
    // Unused column: MalahMagicMax
    int32_t MalahMagicLvl = 0;	// Column 141
    int32_t LarzukMin = 0;	// Column 142
    int32_t LarzukMax = 0;	// Column 143
    // Unused column: LarzukMagicMin
    // Unused column: LarzukMagicMax
    int32_t LarzukMagicLvl = 0;	// Column 146
    int32_t AnyaMin = 0;	// Column 147
    int32_t AnyaMax = 0;	// Column 148
    // Unused column: AnyaMagicMin
    // Unused column: AnyaMagicMax
    int32_t AnyaMagicLvl = 0;	// Column 151
    int32_t JamellaMin = 0;	// Column 152
    int32_t JamellaMax = 0;	// Column 153
    int32_t JamellaMagicMin = 0;	// Column 154
    int32_t JamellaMagicMax = 0;	// Column 155
    int32_t JamellaMagicLvl = 0;	// Column 156
    int32_t Transform = 0;	// Column 157
    int32_t InvTrans = 0;	// Column 158
    int32_t SkipName = 0;	// Column 159
    std::string NightmareUpgrade = "";	// Column 160
    std::string HellUpgrade = "";	// Column 161
    // Unused column: mindam
    // Unused column: maxdam
    int32_t PermStoreItem = 0;	// Column 164
    int32_t multibuy = 0;	// Column 165
    // Unused column: Nameable
    int32_t EventItem = 0;	// Column 167
    std::string UICatOverride = "";	// Column 168
    // Unused column: diablocloneweight
    int32_t AdvancedStashStackable = 0;	// Column 170
    std::string UsageConditionCalc = "";	// Column 171

    size_t read(const char* line);
    static std::vector<t_misc> readfile(std::string filename);
  };

  struct t_misscalc {
    std::string code = "";	// Column 0
    std::string description = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_misscalc> readfile(std::string filename);
  };

  struct t_missiles {
    std::string Missile = "";	// Column 0
    int32_t ID = 0;	// Column 1
    int32_t pCltDoFunc = 0;	// Column 2
    int32_t pCltHitFunc = 0;	// Column 3
    int32_t pSrvDoFunc = 0;	// Column 4
    int32_t pSrvHitFunc = 0;	// Column 5
    int32_t pSrvDmgFunc = 0;	// Column 6
    std::string SrvCalc1 = "";	// Column 7
    std::string srvcalc1desc = "";	// Column 8
    int32_t Param1 = 0;	// Column 9
    std::string param1desc = "";	// Column 10
    int32_t Param2 = 0;	// Column 11
    std::string param2desc = "";	// Column 12
    int32_t Param3 = 0;	// Column 13
    std::string param3desc = "";	// Column 14
    int32_t Param4 = 0;	// Column 15
    std::string param4desc = "";	// Column 16
    int32_t Param5 = 0;	// Column 17
    std::string param5desc = "";	// Column 18
    std::string CltCalc1 = "";	// Column 19
    std::string clientcalc1desc = "";	// Column 20
    int32_t CltParam1 = 0;	// Column 21
    std::string clientparam1desc = "";	// Column 22
    int32_t CltParam2 = 0;	// Column 23
    std::string clientparam2desc = "";	// Column 24
    int32_t CltParam3 = 0;	// Column 25
    std::string clientparam3desc = "";	// Column 26
    int32_t CltParam4 = 0;	// Column 27
    std::string clientparam4desc = "";	// Column 28
    std::string CltParam5 = "";	// Column 29
    std::string clientparam5desc = "";	// Column 30
    int32_t SHitCalc1 = 0;	// Column 31
    std::string serverhitcalc1desc = "";	// Column 32
    int32_t sHitPar1 = 0;	// Column 33
    std::string serverhitparam1desc = "";	// Column 34
    int32_t sHitPar2 = 0;	// Column 35
    std::string serverhitparam2desc = "";	// Column 36
    int32_t sHitPar3 = 0;	// Column 37
    std::string serverhitparam3desc = "";	// Column 38
    // Unused column: CHitCalc1
    // Unused column: *client hit calc1 desc
    int32_t cHitPar1 = 0;	// Column 41
    std::string clienthitparam1desc = "";	// Column 42
    int32_t cHitPar2 = 0;	// Column 43
    std::string clienthitparam2desc = "";	// Column 44
    int32_t cHitPar3 = 0;	// Column 45
    std::string clienthitparam3desc = "";	// Column 46
    std::string DmgCalc1 = "";	// Column 47
    std::string damagecalc1 = "";	// Column 48
    int32_t dParam1 = 0;	// Column 49
    std::string damageparam1desc = "";	// Column 50
    int32_t dParam2 = 0;	// Column 51
    std::string damageparam2desc = "";	// Column 52
    int32_t Vel = 0;	// Column 53
    int32_t MaxVel = 0;	// Column 54
    int32_t VelLev = 0;	// Column 55
    int32_t Accel = 0;	// Column 56
    std::string Range = "";	// Column 57
    std::string Radius = "";	// Column 58
    int32_t Light = 0;	// Column 59
    int32_t Flicker = 0;	// Column 60
    int32_t Red = 0;	// Column 61
    int32_t Green = 0;	// Column 62
    int32_t Blue = 0;	// Column 63
    int32_t InitSteps = 0;	// Column 64
    int32_t Activate = 0;	// Column 65
    int32_t LoopAnim = 0;	// Column 66
    std::string CelFile = "";	// Column 67
    int32_t animrate = 0;	// Column 68
    int32_t AnimLen = 0;	// Column 69
    int32_t AnimSpeed = 0;	// Column 70
    int32_t RandStart = 0;	// Column 71
    int32_t SubLoop = 0;	// Column 72
    int32_t SubStart = 0;	// Column 73
    int32_t SubStop = 0;	// Column 74
    int32_t CollideType = 0;	// Column 75
    int32_t CollideKill = 0;	// Column 76
    int32_t CollideFriend = 0;	// Column 77
    int32_t LastCollide = 0;	// Column 78
    int32_t Collision = 0;	// Column 79
    int32_t ClientCol = 0;	// Column 80
    int32_t CollisionOverlap = 0;	// Column 81
    int32_t ClientSend = 0;	// Column 82
    int32_t NextHit = 0;	// Column 83
    int32_t NextDelay = 0;	// Column 84
    // Unused column: xoffset
    int32_t yoffset = 0;	// Column 86
    int32_t zoffset = 0;	// Column 87
    int32_t Size = 0;	// Column 88
    int32_t SrcTown = 0;	// Column 89
    int32_t CltSrcTown = 0;	// Column 90
    int32_t CanDestroy = 0;	// Column 91
    int32_t ToHit = 0;	// Column 92
    int32_t AlwaysExplode = 0;	// Column 93
    int32_t Explosion = 0;	// Column 94
    int32_t Town = 0;	// Column 95
    int32_t NoUniqueMod = 0;	// Column 96
    int32_t NoMultiShot = 0;	// Column 97
    int32_t Holy = 0;	// Column 98
    int32_t CanSlow = 0;	// Column 99
    int32_t ReturnFire = 0;	// Column 100
    int32_t GetHit = 0;	// Column 101
    int32_t SoftHit = 0;	// Column 102
    int32_t KnockBack = 0;	// Column 103
    int32_t Trans = 0;	// Column 104
    int32_t Pierce = 0;	// Column 105
    int32_t MissileSkill = 0;	// Column 106
    std::string Skill = "";	// Column 107
    int32_t ResultFlags = 0;	// Column 108
    int32_t HitFlags = 0;	// Column 109
    int32_t HitShift = 0;	// Column 110
    int32_t ApplyMastery = 0;	// Column 111
    int32_t SrcDamage = 0;	// Column 112
    int32_t Half2HSrc = 0;	// Column 113
    // Unused column: SrcMissDmg
    int32_t MinDamage = 0;	// Column 115
    int32_t MinLevDam1 = 0;	// Column 116
    int32_t MinLevDam2 = 0;	// Column 117
    int32_t MinLevDam3 = 0;	// Column 118
    int32_t MinLevDam4 = 0;	// Column 119
    int32_t MinLevDam5 = 0;	// Column 120
    int32_t MaxDamage = 0;	// Column 121
    int32_t MaxLevDam1 = 0;	// Column 122
    int32_t MaxLevDam2 = 0;	// Column 123
    int32_t MaxLevDam3 = 0;	// Column 124
    int32_t MaxLevDam4 = 0;	// Column 125
    int32_t MaxLevDam5 = 0;	// Column 126
    // Unused column: DmgSymPerCalc
    std::string EType = "";	// Column 128
    int32_t EMin = 0;	// Column 129
    int32_t MinELev1 = 0;	// Column 130
    int32_t MinELev2 = 0;	// Column 131
    int32_t MinELev3 = 0;	// Column 132
    int32_t MinELev4 = 0;	// Column 133
    int32_t MinELev5 = 0;	// Column 134
    int32_t EMax = 0;	// Column 135
    int32_t MaxELev1 = 0;	// Column 136
    int32_t MaxELev2 = 0;	// Column 137
    int32_t MaxELev3 = 0;	// Column 138
    int32_t MaxELev4 = 0;	// Column 139
    int32_t MaxELev5 = 0;	// Column 140
    std::string EDmgSymPerCalc = "";	// Column 141
    int32_t ELen = 0;	// Column 142
    int32_t ELevLen1 = 0;	// Column 143
    int32_t ELevLen2 = 0;	// Column 144
    int32_t ELevLen3 = 0;	// Column 145
    int32_t HitClass = 0;	// Column 146
    int32_t NumDirections = 0;	// Column 147
    int32_t LocalBlood = 0;	// Column 148
    int32_t DamageRate = 0;	// Column 149
    std::string TravelSound = "";	// Column 150
    std::string HitSound = "";	// Column 151
    std::string OnDiedSound = "";	// Column 152
    std::string ProgSound = "";	// Column 153
    std::string ProgOverlay = "";	// Column 154
    std::string ExplosionMissile = "";	// Column 155
    std::string SubMissile1 = "";	// Column 156
    std::string SubMissile2 = "";	// Column 157
    // Unused column: SubMissile3
    std::string HitSubMissile1 = "";	// Column 159
    // Unused column: HitSubMissile2
    // Unused column: HitSubMissile3
    // Unused column: HitSubMissile4
    std::string CltSubMissile1 = "";	// Column 163
    std::string CltSubMissile2 = "";	// Column 164
    std::string CltSubMissile3 = "";	// Column 165
    std::string CltHitSubMissile1 = "";	// Column 166
    std::string CltHitSubMissile2 = "";	// Column 167
    std::string CltHitSubMissile3 = "";	// Column 168
    std::string CltHitSubMissile4 = "";	// Column 169
    int32_t MissileWeaponVFX = 0;	// Column 170
    int32_t eol = 0;	// Column 171

    size_t read(const char* line);
    static std::vector<t_missiles> readfile(std::string filename);
  };

  struct t_monai {
    std::string AI = "";	// Column 0
    std::string aip1 = "";	// Column 1
    std::string aip2 = "";	// Column 2
    std::string aip3 = "";	// Column 3
    std::string aip4 = "";	// Column 4
    std::string aip5 = "";	// Column 5
    std::string aip6 = "";	// Column 6
    std::string aip7 = "";	// Column 7
    std::string aip8 = "";	// Column 8
    int32_t eol = 0;	// Column 9

    size_t read(const char* line);
    static std::vector<t_monai> readfile(std::string filename);
  };

  struct t_moncalc {
    std::string code = "";	// Column 0
    std::string description = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_moncalc> readfile(std::string filename);
  };

  struct t_monequip {
    std::string monster = "";	// Column 0
    int32_t oninit = 0;	// Column 1
    int32_t level = 0;	// Column 2
    std::string item1 = "";	// Column 3
    std::string loc1 = "";	// Column 4
    int32_t mod1 = 0;	// Column 5
    std::string item2 = "";	// Column 6
    std::string loc2 = "";	// Column 7
    int32_t mod2 = 0;	// Column 8
    std::string item3 = "";	// Column 9
    std::string loc3 = "";	// Column 10
    int32_t mod3 = 0;	// Column 11
    int32_t eol = 0;	// Column 12

    size_t read(const char* line);
    static std::vector<t_monequip> readfile(std::string filename);
  };

  struct t_monlvl {
    int32_t Level = 0;	// Column 0
    int32_t AC = 0;	// Column 1
    int32_t ACN = 0;	// Column 2
    int32_t ACH = 0;	// Column 3
    int32_t LAC = 0;	// Column 4
    int32_t LACN = 0;	// Column 5
    int32_t LACH = 0;	// Column 6
    int32_t TH = 0;	// Column 7
    int32_t THN = 0;	// Column 8
    int32_t THH = 0;	// Column 9
    int32_t LTH = 0;	// Column 10
    int32_t LTHN = 0;	// Column 11
    int32_t LTHH = 0;	// Column 12
    int32_t HP = 0;	// Column 13
    int32_t HPN = 0;	// Column 14
    int32_t HPH = 0;	// Column 15
    int32_t LHP = 0;	// Column 16
    int32_t LHPN = 0;	// Column 17
    int32_t LHPH = 0;	// Column 18
    int32_t DM = 0;	// Column 19
    int32_t DMN = 0;	// Column 20
    int32_t DMH = 0;	// Column 21
    int32_t LDM = 0;	// Column 22
    int32_t LDMN = 0;	// Column 23
    int32_t LDMH = 0;	// Column 24
    int32_t XP = 0;	// Column 25
    int32_t XPN = 0;	// Column 26
    int32_t XPH = 0;	// Column 27
    int32_t LXP = 0;	// Column 28
    int32_t LXPN = 0;	// Column 29
    int32_t LXPH = 0;	// Column 30

    size_t read(const char* line);
    static std::vector<t_monlvl> readfile(std::string filename);
  };

  struct t_monmode {
    std::string name = "";	// Column 0
    std::string token = "";	// Column 1
    std::string code = "";	// Column 2

    size_t read(const char* line);
    static std::vector<t_monmode> readfile(std::string filename);
  };

  struct t_monpet {
    std::string monster = "";	// Column 0
    int32_t index = 0;	// Column 1
    int32_t hirelingAlternateVoice = 0;	// Column 2
    std::string calc1 = "";	// Column 3
    std::string calc1desc = "";	// Column 4
    std::string calc2 = "";	// Column 5
    std::string calc2desc = "";	// Column 6
    std::string calc3 = "";	// Column 7
    std::string calc3desc = "";	// Column 8
    std::string calc4 = "";	// Column 9
    std::string calc4desc = "";	// Column 10
    std::string calc5 = "";	// Column 11
    std::string calc5desc = "";	// Column 12
    std::string consumestat1 = "";	// Column 13
    // Unused column: consumepar1
    std::string consumecalc1 = "";	// Column 15
    std::string consumestat2 = "";	// Column 16
    // Unused column: consumepar2
    std::string consumecalc2 = "";	// Column 18
    std::string consumestat3 = "";	// Column 19
    std::string consumepar3 = "";	// Column 20
    std::string consumecalc3 = "";	// Column 21
    // Unused column: consumestat4
    // Unused column: consumepar4
    // Unused column: consumecalc4
    // Unused column: consumestat5
    // Unused column: consumepar5
    // Unused column: consumecalc5
    int32_t numunderlingcalc = 0;	// Column 28
    std::string bindchancecalc = "";	// Column 29
    std::string BoundStat1 = "";	// Column 30
    std::string BoundCalc1 = "";	// Column 31
    // Unused column: BoundStat2
    // Unused column: BoundCalc2
    // Unused column: BoundStat3
    // Unused column: BoundCalc3
    // Unused column: BoundStat4
    // Unused column: BoundCalc4
    // Unused column: BoundStat5
    // Unused column: BoundCalc5

    size_t read(const char* line);
    static std::vector<t_monpet> readfile(std::string filename);
  };

  struct t_monplace {
    std::string code = "";	// Column 0

    size_t read(const char* line);
    static std::vector<t_monplace> readfile(std::string filename);
  };

  struct t_monpreset {
    int32_t Act = 0;	// Column 0
    std::string Place = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_monpreset> readfile(std::string filename);
  };

  struct t_monprop {
    std::string Id = "";	// Column 0
    std::string prop1 = "";	// Column 1
    // Unused column: chance1
    // Unused column: par1
    int32_t min1 = 0;	// Column 4
    int32_t max1 = 0;	// Column 5
    // Unused column: prop2
    // Unused column: chance2
    // Unused column: par2
    // Unused column: min2
    // Unused column: max2
    // Unused column: prop3
    // Unused column: chance3
    // Unused column: par3
    // Unused column: min3
    // Unused column: max3
    // Unused column: prop4
    // Unused column: chance4
    // Unused column: par4
    // Unused column: min4
    // Unused column: max4
    // Unused column: prop5
    // Unused column: chance5
    // Unused column: par5
    // Unused column: min5
    // Unused column: max5
    // Unused column: prop6
    // Unused column: chance6
    // Unused column: par6
    // Unused column: min6
    // Unused column: max6
    std::string prop1N = "";	// Column 31
    // Unused column: chance1 (N)
    // Unused column: par1 (N)
    int32_t min1N = 0;	// Column 34
    int32_t max1N = 0;	// Column 35
    std::string prop2N = "";	// Column 36
    // Unused column: chance2 (N)
    // Unused column: par2 (N)
    int32_t min2N = 0;	// Column 39
    int32_t max2N = 0;	// Column 40
    // Unused column: prop3 (N)
    // Unused column: chance3 (N)
    // Unused column: par3 (N)
    // Unused column: min3 (N)
    // Unused column: max3 (N)
    // Unused column: prop4 (N)
    // Unused column: chance4 (N)
    // Unused column: par4 (N)
    // Unused column: min4 (N)
    // Unused column: max4 (N)
    // Unused column: prop5 (N)
    // Unused column: chance5 (N)
    // Unused column: par5 (N)
    // Unused column: min5 (N)
    // Unused column: max5 (N)
    // Unused column: prop6 (N)
    // Unused column: chance6 (N)
    // Unused column: par6 (N)
    // Unused column: min6 (N)
    // Unused column: max6 (N)
    std::string prop1H = "";	// Column 61
    // Unused column: chance1 (H)
    // Unused column: par1 (H)
    int32_t min1H = 0;	// Column 64
    int32_t max1H = 0;	// Column 65
    std::string prop2H = "";	// Column 66
    // Unused column: chance2 (H)
    // Unused column: par2 (H)
    int32_t min2H = 0;	// Column 69
    int32_t max2H = 0;	// Column 70
    // Unused column: prop3 (H)
    // Unused column: chance3 (H)
    // Unused column: par3 (H)
    // Unused column: min3 (H)
    // Unused column: max3 (H)
    // Unused column: prop4 (H)
    // Unused column: chance4 (H)
    // Unused column: par4 (H)
    // Unused column: min4 (H)
    // Unused column: max4 (H)
    // Unused column: prop5 (H)
    // Unused column: chance5 (H)
    // Unused column: par5 (H)
    // Unused column: min5 (H)
    // Unused column: max5 (H)
    // Unused column: prop6 (H)
    // Unused column: chance6 (H)
    // Unused column: par6 (H)
    // Unused column: min6 (H)
    // Unused column: max6 (H)
    int32_t eol = 0;	// Column 91

    size_t read(const char* line);
    static std::vector<t_monprop> readfile(std::string filename);
  };

  struct t_monseq {
    std::string sequence = "";	// Column 0
    std::string mode = "";	// Column 1
    int32_t frame = 0;	// Column 2
    // Unused column: dir
    int32_t event = 0;	// Column 4
    int32_t eol = 0;	// Column 5

    size_t read(const char* line);
    static std::vector<t_monseq> readfile(std::string filename);
  };

  struct t_monsounds {
    std::string Id = "";	// Column 0
    std::string Attack1 = "";	// Column 1
    std::string Weapon1 = "";	// Column 2
    int32_t Att1Del = 0;	// Column 3
    int32_t Wea1Del = 0;	// Column 4
    int32_t Att1Prb = 0;	// Column 5
    int32_t Wea1Vol = 0;	// Column 6
    std::string Attack2 = "";	// Column 7
    std::string Weapon2 = "";	// Column 8
    int32_t Att2Del = 0;	// Column 9
    int32_t Wea2Del = 0;	// Column 10
    int32_t Att2Prb = 0;	// Column 11
    int32_t Wea2Vol = 0;	// Column 12
    std::string HitSound = "";	// Column 13
    std::string DeathSound = "";	// Column 14
    int32_t HitDelay = 0;	// Column 15
    int32_t DeaDelay = 0;	// Column 16
    std::string Skill1 = "";	// Column 17
    std::string Skill2 = "";	// Column 18
    std::string Skill3 = "";	// Column 19
    std::string Skill4 = "";	// Column 20
    std::string Footstep = "";	// Column 21
    std::string FootstepLayer = "";	// Column 22
    int32_t FsCnt = 0;	// Column 23
    int32_t FsOff = 0;	// Column 24
    int32_t FsPrb = 0;	// Column 25
    std::string Neutral = "";	// Column 26
    int32_t NeuTime = 0;	// Column 27
    std::string Init = "";	// Column 28
    std::string Taunt = "";	// Column 29
    std::string Flee = "";	// Column 30
    std::string CvtMo1 = "";	// Column 31
    std::string CvtSk1 = "";	// Column 32
    std::string CvtTgt1 = "";	// Column 33
    std::string CvtMo2 = "";	// Column 34
    std::string CvtSk2 = "";	// Column 35
    std::string CvtTgt2 = "";	// Column 36
    std::string CvtMo3 = "";	// Column 37
    std::string CvtSk3 = "";	// Column 38
    std::string CvtTgt3 = "";	// Column 39
    int32_t EOL = 0;	// Column 40

    size_t read(const char* line);
    static std::vector<t_monsounds> readfile(std::string filename);
  };

  struct t_monstats {
    std::string Id = "";	// Column 0
    int32_t hcIdx = 0;	// Column 1
    std::string BaseId = "";	// Column 2
    std::string NextInClass = "";	// Column 3
    int32_t TransLvl = 0;	// Column 4
    std::string NameStr = "";	// Column 5
    std::string MonStatsEx = "";	// Column 6
    std::string MonProp = "";	// Column 7
    std::string MonType = "";	// Column 8
    std::string AI = "";	// Column 9
    std::string DescStr = "";	// Column 10
    std::string Code = "";	// Column 11
    int32_t enabled = 0;	// Column 12
    int32_t rangedtype = 0;	// Column 13
    int32_t placespawn = 0;	// Column 14
    std::string spawn = "";	// Column 15
    int32_t spawnx = 0;	// Column 16
    int32_t spawny = 0;	// Column 17
    std::string spawnmode = "";	// Column 18
    std::string minion1 = "";	// Column 19
    std::string minion2 = "";	// Column 20
    int32_t SetBoss = 0;	// Column 21
    int32_t BossXfer = 0;	// Column 22
    int32_t PartyMin = 0;	// Column 23
    int32_t PartyMax = 0;	// Column 24
    int32_t MinGrp = 0;	// Column 25
    int32_t MaxGrp = 0;	// Column 26
    int32_t sparsePopulate = 0;	// Column 27
    int32_t Velocity = 0;	// Column 28
    int32_t Run = 0;	// Column 29
    int32_t Rarity = 0;	// Column 30
    int32_t Level = 0;	// Column 31
    int32_t LevelN = 0;	// Column 32
    int32_t LevelH = 0;	// Column 33
    std::string MonSound = "";	// Column 34
    std::string UMonSound = "";	// Column 35
    int32_t threat = 0;	// Column 36
    int32_t aidel = 0;	// Column 37
    int32_t aidelN = 0;	// Column 38
    int32_t aidelH = 0;	// Column 39
    // Unused column: aidist
    int32_t aidistN = 0;	// Column 41
    int32_t aidistH = 0;	// Column 42
    int32_t aip1 = 0;	// Column 43
    int32_t aip1N = 0;	// Column 44
    int32_t aip1H = 0;	// Column 45
    int32_t aip2 = 0;	// Column 46
    int32_t aip2N = 0;	// Column 47
    int32_t aip2H = 0;	// Column 48
    int32_t aip3 = 0;	// Column 49
    int32_t aip3N = 0;	// Column 50
    int32_t aip3H = 0;	// Column 51
    int32_t aip4 = 0;	// Column 52
    int32_t aip4N = 0;	// Column 53
    int32_t aip4H = 0;	// Column 54
    int32_t aip5 = 0;	// Column 55
    int32_t aip5N = 0;	// Column 56
    int32_t aip5H = 0;	// Column 57
    int32_t aip6 = 0;	// Column 58
    int32_t aip6N = 0;	// Column 59
    int32_t aip6H = 0;	// Column 60
    int32_t aip7 = 0;	// Column 61
    int32_t aip7N = 0;	// Column 62
    int32_t aip7H = 0;	// Column 63
    int32_t aip8 = 0;	// Column 64
    int32_t aip8N = 0;	// Column 65
    int32_t aip8H = 0;	// Column 66
    std::string MissA1 = "";	// Column 67
    std::string MissA2 = "";	// Column 68
    std::string MissS1 = "";	// Column 69
    std::string MissS2 = "";	// Column 70
    // Unused column: MissS3
    // Unused column: MissS4
    std::string MissC = "";	// Column 73
    std::string MissSQ = "";	// Column 74
    int32_t Align = 0;	// Column 75
    int32_t isSpawn = 0;	// Column 76
    int32_t isMelee = 0;	// Column 77
    int32_t npc = 0;	// Column 78
    int32_t interact = 0;	// Column 79
    int32_t inventory = 0;	// Column 80
    int32_t inTown = 0;	// Column 81
    int32_t lUndead = 0;	// Column 82
    int32_t hUndead = 0;	// Column 83
    int32_t demon = 0;	// Column 84
    int32_t flying = 0;	// Column 85
    int32_t opendoors = 0;	// Column 86
    int32_t boss = 0;	// Column 87
    int32_t primeevil = 0;	// Column 88
    int32_t killable = 0;	// Column 89
    int32_t switchai = 0;	// Column 90
    int32_t noAura = 0;	// Column 91
    int32_t nomultishot = 0;	// Column 92
    int32_t nopreventmonsterheal = 0;	// Column 93
    int32_t neverCount = 0;	// Column 94
    int32_t petIgnore = 0;	// Column 95
    int32_t deathDmg = 0;	// Column 96
    int32_t genericSpawn = 0;	// Column 97
    int32_t zoo = 0;	// Column 98
    int32_t CannotDesecrate = 0;	// Column 99
    int32_t CannotHerald = 0;	// Column 100
    std::string rightArmItemType = "";	// Column 101
    std::string leftArmItemType = "";	// Column 102
    int32_t canNotUseTwoHandedItems = 0;	// Column 103
    int32_t SendSkills = 0;	// Column 104
    std::string Skill1 = "";	// Column 105
    std::string Sk1mode = "";	// Column 106
    int32_t Sk1lvl = 0;	// Column 107
    std::string Skill2 = "";	// Column 108
    std::string Sk2mode = "";	// Column 109
    int32_t Sk2lvl = 0;	// Column 110
    std::string Skill3 = "";	// Column 111
    std::string Sk3mode = "";	// Column 112
    int32_t Sk3lvl = 0;	// Column 113
    std::string Skill4 = "";	// Column 114
    std::string Sk4mode = "";	// Column 115
    int32_t Sk4lvl = 0;	// Column 116
    std::string Skill5 = "";	// Column 117
    std::string Sk5mode = "";	// Column 118
    int32_t Sk5lvl = 0;	// Column 119
    std::string Skill6 = "";	// Column 120
    std::string Sk6mode = "";	// Column 121
    int32_t Sk6lvl = 0;	// Column 122
    std::string Skill7 = "";	// Column 123
    std::string Sk7mode = "";	// Column 124
    int32_t Sk7lvl = 0;	// Column 125
    std::string Skill8 = "";	// Column 126
    std::string Sk8mode = "";	// Column 127
    int32_t Sk8lvl = 0;	// Column 128
    int32_t Drain = 0;	// Column 129
    int32_t DrainN = 0;	// Column 130
    int32_t DrainH = 0;	// Column 131
    int32_t coldeffect = 0;	// Column 132
    int32_t coldeffectN = 0;	// Column 133
    int32_t coldeffectH = 0;	// Column 134
    int32_t ResDm = 0;	// Column 135
    int32_t ResMa = 0;	// Column 136
    int32_t ResFi = 0;	// Column 137
    int32_t ResLi = 0;	// Column 138
    int32_t ResCo = 0;	// Column 139
    int32_t ResPo = 0;	// Column 140
    int32_t ResDmN = 0;	// Column 141
    int32_t ResMaN = 0;	// Column 142
    int32_t ResFiN = 0;	// Column 143
    int32_t ResLiN = 0;	// Column 144
    int32_t ResCoN = 0;	// Column 145
    int32_t ResPoN = 0;	// Column 146
    int32_t ResDmH = 0;	// Column 147
    int32_t ResMaH = 0;	// Column 148
    int32_t ResFiH = 0;	// Column 149
    int32_t ResLiH = 0;	// Column 150
    int32_t ResCoH = 0;	// Column 151
    int32_t ResPoH = 0;	// Column 152
    int32_t DamageRegen = 0;	// Column 153
    std::string SkillDamage = "";	// Column 154
    int32_t noRatio = 0;	// Column 155
    int32_t ShieldBlockOverride = 0;	// Column 156
    int32_t ToBlock = 0;	// Column 157
    int32_t ToBlockN = 0;	// Column 158
    int32_t ToBlockH = 0;	// Column 159
    int32_t Crit = 0;	// Column 160
    int32_t minHP = 0;	// Column 161
    int32_t maxHP = 0;	// Column 162
    int32_t AC = 0;	// Column 163
    int32_t Exp = 0;	// Column 164
    int32_t A1MinD = 0;	// Column 165
    int32_t A1MaxD = 0;	// Column 166
    int32_t A1TH = 0;	// Column 167
    int32_t A2MinD = 0;	// Column 168
    int32_t A2MaxD = 0;	// Column 169
    int32_t A2TH = 0;	// Column 170
    int32_t S1MinD = 0;	// Column 171
    int32_t S1MaxD = 0;	// Column 172
    int32_t S1TH = 0;	// Column 173
    int32_t MinHPN = 0;	// Column 174
    int32_t MaxHPN = 0;	// Column 175
    int32_t ACN = 0;	// Column 176
    int32_t ExpN = 0;	// Column 177
    int32_t A1MinDN = 0;	// Column 178
    int32_t A1MaxDN = 0;	// Column 179
    int32_t A1THN = 0;	// Column 180
    int32_t A2MinDN = 0;	// Column 181
    int32_t A2MaxDN = 0;	// Column 182
    int32_t A2THN = 0;	// Column 183
    int32_t S1MinDN = 0;	// Column 184
    int32_t S1MaxDN = 0;	// Column 185
    int32_t S1THN = 0;	// Column 186
    int32_t MinHPH = 0;	// Column 187
    int32_t MaxHPH = 0;	// Column 188
    int32_t ACH = 0;	// Column 189
    int32_t ExpH = 0;	// Column 190
    int32_t A1MinDH = 0;	// Column 191
    int32_t A1MaxDH = 0;	// Column 192
    int32_t A1THH = 0;	// Column 193
    int32_t A2MinDH = 0;	// Column 194
    int32_t A2MaxDH = 0;	// Column 195
    int32_t A2THH = 0;	// Column 196
    int32_t S1MinDH = 0;	// Column 197
    int32_t S1MaxDH = 0;	// Column 198
    int32_t S1THH = 0;	// Column 199
    std::string El1Mode = "";	// Column 200
    std::string El1Type = "";	// Column 201
    int32_t El1Pct = 0;	// Column 202
    int32_t El1MinD = 0;	// Column 203
    int32_t El1MaxD = 0;	// Column 204
    int32_t El1Dur = 0;	// Column 205
    int32_t El1PctN = 0;	// Column 206
    int32_t El1MinDN = 0;	// Column 207
    int32_t El1MaxDN = 0;	// Column 208
    int32_t El1DurN = 0;	// Column 209
    int32_t El1PctH = 0;	// Column 210
    int32_t El1MinDH = 0;	// Column 211
    int32_t El1MaxDH = 0;	// Column 212
    int32_t El1DurH = 0;	// Column 213
    std::string El2Mode = "";	// Column 214
    std::string El2Type = "";	// Column 215
    int32_t El2Pct = 0;	// Column 216
    int32_t El2MinD = 0;	// Column 217
    int32_t El2MaxD = 0;	// Column 218
    int32_t El2Dur = 0;	// Column 219
    int32_t El2PctN = 0;	// Column 220
    int32_t El2MinDN = 0;	// Column 221
    int32_t El2MaxDN = 0;	// Column 222
    int32_t El2DurN = 0;	// Column 223
    int32_t El2PctH = 0;	// Column 224
    int32_t El2MinDH = 0;	// Column 225
    int32_t El2MaxDH = 0;	// Column 226
    int32_t El2DurH = 0;	// Column 227
    // Unused column: El3Mode
    // Unused column: El3Type
    // Unused column: El3Pct
    // Unused column: El3MinD
    // Unused column: El3MaxD
    // Unused column: El3Dur
    // Unused column: El3Pct(N)
    // Unused column: El3MinD(N)
    // Unused column: El3MaxD(N)
    // Unused column: El3Dur(N)
    // Unused column: El3Pct(H)
    // Unused column: El3MinD(H)
    // Unused column: El3MaxD(H)
    // Unused column: El3Dur(H)
    std::string TreasureClass = "";	// Column 242
    std::string TreasureClassChamp = "";	// Column 243
    std::string TreasureClassUnique = "";	// Column 244
    std::string TreasureClassQuest = "";	// Column 245
    std::string TreasureClassDesecrated = "";	// Column 246
    std::string TreasureClassDesecratedChamp = "";	// Column 247
    std::string TreasureClassDesecratedUnique = "";	// Column 248
    // Unused column: TreasureClassHerald
    std::string TreasureClassN = "";	// Column 250
    std::string TreasureClassChampN = "";	// Column 251
    std::string TreasureClassUniqueN = "";	// Column 252
    std::string TreasureClassQuestN = "";	// Column 253
    std::string TreasureClassDesecratedN = "";	// Column 254
    std::string TreasureClassDesecratedChampN = "";	// Column 255
    std::string TreasureClassDesecratedUniqueN = "";	// Column 256
    // Unused column: TreasureClassHerald(N)
    std::string TreasureClassH = "";	// Column 258
    std::string TreasureClassChampH = "";	// Column 259
    std::string TreasureClassUniqueH = "";	// Column 260
    std::string TreasureClassQuestH = "";	// Column 261
    std::string TreasureClassDesecratedH = "";	// Column 262
    std::string TreasureClassDesecratedChampH = "";	// Column 263
    std::string TreasureClassDesecratedUniqueH = "";	// Column 264
    std::string TreasureClassHeraldH = "";	// Column 265
    int32_t TCQuestId = 0;	// Column 266
    int32_t TCQuestCP = 0;	// Column 267
    int32_t SplEndDeath = 0;	// Column 268
    int32_t SplGetModeChart = 0;	// Column 269
    int32_t SplEndGeneric = 0;	// Column 270
    int32_t SplClientEnd = 0;	// Column 271
    int32_t eol = 0;	// Column 272

    size_t read(const char* line);
    static std::vector<t_monstats> readfile(std::string filename);
  };

  struct t_monstats2 {
    std::string Id = "";	// Column 0
    int32_t hcIdx = 0;	// Column 1
    int32_t Height = 0;	// Column 2
    int32_t OverlayHeight = 0;	// Column 3
    int32_t pixHeight = 0;	// Column 4
    int32_t SizeX = 0;	// Column 5
    int32_t SizeY = 0;	// Column 6
    int32_t spawnCol = 0;	// Column 7
    int32_t MeleeRng = 0;	// Column 8
    std::string BaseW = "";	// Column 9
    int32_t HitClass = 0;	// Column 10
    std::string HDv = "";	// Column 11
    std::string TRv = "";	// Column 12
    std::string LGv = "";	// Column 13
    std::string Rav = "";	// Column 14
    std::string Lav = "";	// Column 15
    std::string RHv = "";	// Column 16
    std::string LHv = "";	// Column 17
    std::string SHv = "";	// Column 18
    std::string S1v = "";	// Column 19
    std::string S2v = "";	// Column 20
    std::string S3v = "";	// Column 21
    std::string S4v = "";	// Column 22
    std::string S5v = "";	// Column 23
    std::string S6v = "";	// Column 24
    std::string S7v = "";	// Column 25
    std::string S8v = "";	// Column 26
    int32_t HD = 0;	// Column 27
    int32_t TR = 0;	// Column 28
    int32_t LG = 0;	// Column 29
    int32_t RA = 0;	// Column 30
    int32_t LA = 0;	// Column 31
    int32_t RH = 0;	// Column 32
    int32_t LH = 0;	// Column 33
    int32_t SH = 0;	// Column 34
    int32_t S1 = 0;	// Column 35
    int32_t S2 = 0;	// Column 36
    int32_t S3 = 0;	// Column 37
    int32_t S4 = 0;	// Column 38
    int32_t S5 = 0;	// Column 39
    int32_t S6 = 0;	// Column 40
    int32_t S7 = 0;	// Column 41
    int32_t S8 = 0;	// Column 42
    int32_t TotalPieces = 0;	// Column 43
    int32_t mDT = 0;	// Column 44
    int32_t mNU = 0;	// Column 45
    int32_t mWL = 0;	// Column 46
    int32_t mGH = 0;	// Column 47
    int32_t mA1 = 0;	// Column 48
    int32_t mA2 = 0;	// Column 49
    int32_t mBL = 0;	// Column 50
    int32_t mSC = 0;	// Column 51
    int32_t mS1 = 0;	// Column 52
    int32_t mS2 = 0;	// Column 53
    int32_t mS3 = 0;	// Column 54
    int32_t mS4 = 0;	// Column 55
    int32_t mDD = 0;	// Column 56
    int32_t mKB = 0;	// Column 57
    int32_t mSQ = 0;	// Column 58
    int32_t mRN = 0;	// Column 59
    int32_t dDT = 0;	// Column 60
    int32_t dNU = 0;	// Column 61
    int32_t dWL = 0;	// Column 62
    int32_t dGH = 0;	// Column 63
    int32_t dA1 = 0;	// Column 64
    int32_t dA2 = 0;	// Column 65
    int32_t dBL = 0;	// Column 66
    int32_t dSC = 0;	// Column 67
    int32_t dS1 = 0;	// Column 68
    int32_t dS2 = 0;	// Column 69
    int32_t dS3 = 0;	// Column 70
    int32_t dS4 = 0;	// Column 71
    int32_t dDD = 0;	// Column 72
    int32_t dKB = 0;	// Column 73
    int32_t dSQ = 0;	// Column 74
    int32_t dRN = 0;	// Column 75
    // Unused column: A1mv
    int32_t A2mv = 0;	// Column 77
    // Unused column: SCmv
    int32_t S1mv = 0;	// Column 79
    int32_t S2mv = 0;	// Column 80
    // Unused column: S3mv
    // Unused column: S4mv
    int32_t noGfxHitTest = 0;	// Column 83
    int32_t htTop = 0;	// Column 84
    int32_t htLeft = 0;	// Column 85
    int32_t htWidth = 0;	// Column 86
    int32_t htHeight = 0;	// Column 87
    int32_t restore = 0;	// Column 88
    int32_t automapCel = 0;	// Column 89
    int32_t noMap = 0;	// Column 90
    int32_t noOvly = 0;	// Column 91
    int32_t isSel = 0;	// Column 92
    int32_t alSel = 0;	// Column 93
    int32_t noSel = 0;	// Column 94
    int32_t shiftSel = 0;	// Column 95
    int32_t corpseSel = 0;	// Column 96
    int32_t isAtt = 0;	// Column 97
    int32_t revive = 0;	// Column 98
    int32_t limitCorpses = 0;	// Column 99
    int32_t critter = 0;	// Column 100
    int32_t small = 0;	// Column 101
    int32_t large = 0;	// Column 102
    int32_t soft = 0;	// Column 103
    int32_t inert = 0;	// Column 104
    int32_t objCol = 0;	// Column 105
    int32_t deadCol = 0;	// Column 106
    int32_t unflatDead = 0;	// Column 107
    int32_t Shadow = 0;	// Column 108
    int32_t noUniqueShift = 0;	// Column 109
    int32_t compositeDeath = 0;	// Column 110
    int32_t localBlood = 0;	// Column 111
    int32_t Bleed = 0;	// Column 112
    int32_t Light = 0;	// Column 113
    int32_t lightr = 0;	// Column 114
    int32_t lightg = 0;	// Column 115
    int32_t lightb = 0;	// Column 116
    int32_t Utrans = 0;	// Column 117
    int32_t UtransN = 0;	// Column 118
    int32_t UtransH = 0;	// Column 119
    int32_t InfernoLen = 0;	// Column 120
    int32_t InfernoAnim = 0;	// Column 121
    int32_t InfernoRollback = 0;	// Column 122
    std::string ResurrectMode = "";	// Column 123
    std::string ResurrectSkill = "";	// Column 124
    std::string SpawnUniqueMod = "";	// Column 125
    int32_t eol = 0;	// Column 126

    size_t read(const char* line);
    static std::vector<t_monstats2> readfile(std::string filename);
  };

  struct t_montype {
    std::string type = "";	// Column 0
    std::string equiv1 = "";	// Column 1
    std::string equiv2 = "";	// Column 2
    // Unused column: equiv3
    std::string strplur = "";	// Column 4
    // Unused column: element
    int32_t eol = 0;	// Column 6

    size_t read(const char* line);
    static std::vector<t_montype> readfile(std::string filename);
  };

  struct t_monumod {
    std::string uniquemod = "";	// Column 0
    int32_t id = 0;	// Column 1
    int32_t enabled = 0;	// Column 2
    int32_t version = 0;	// Column 3
    int32_t xfer = 0;	// Column 4
    int32_t champion = 0;	// Column 5
    int32_t fPick = 0;	// Column 6
    std::string exclude1 = "";	// Column 7
    // Unused column: exclude2
    int32_t cpick = 0;	// Column 9
    int32_t cpickN = 0;	// Column 10
    int32_t cpickH = 0;	// Column 11
    int32_t upick = 0;	// Column 12
    int32_t upickN = 0;	// Column 13
    int32_t upickH = 0;	// Column 14
    int32_t constants = 0;	// Column 15
    std::string constantdesc = "";	// Column 16
    int32_t eol = 0;	// Column 17

    size_t read(const char* line);
    static std::vector<t_monumod> readfile(std::string filename);
  };

  struct t_npc {
    std::string npc = "";	// Column 0
    int32_t buymult = 0;	// Column 1
    int32_t sellmult = 0;	// Column 2
    int32_t repmult = 0;	// Column 3
    int32_t questflagA = 0;	// Column 4
    int32_t questbuymultA = 0;	// Column 5
    int32_t questsellmultA = 0;	// Column 6
    int32_t questrepmultA = 0;	// Column 7
    // Unused column: questflag B
    // Unused column: questbuymult B
    // Unused column: questsellmult B
    // Unused column: questrepmult B
    // Unused column: questflag C
    // Unused column: questbuymult C
    // Unused column: questsellmult C
    // Unused column: questrepmult C
    int32_t maxbuy = 0;	// Column 16
    int32_t maxbuyN = 0;	// Column 17
    int32_t maxbuyH = 0;	// Column 18

    size_t read(const char* line);
    static std::vector<t_npc> readfile(std::string filename);
  };

  struct t_objects {
    std::string Class = "";	// Column 0
    std::string Name = "";	// Column 1
    std::string Description = "";	// Column 2
    int32_t ID = 0;	// Column 3
    std::string Token = "";	// Column 4
    int32_t Selectable0 = 0;	// Column 5
    int32_t Selectable1 = 0;	// Column 6
    int32_t Selectable2 = 0;	// Column 7
    int32_t Selectable3 = 0;	// Column 8
    int32_t Selectable4 = 0;	// Column 9
    int32_t Selectable5 = 0;	// Column 10
    int32_t Selectable6 = 0;	// Column 11
    int32_t Selectable7 = 0;	// Column 12
    int32_t SizeX = 0;	// Column 13
    int32_t SizeY = 0;	// Column 14
    int32_t FrameCnt0 = 0;	// Column 15
    int32_t FrameCnt1 = 0;	// Column 16
    int32_t FrameCnt2 = 0;	// Column 17
    int32_t FrameCnt3 = 0;	// Column 18
    int32_t FrameCnt4 = 0;	// Column 19
    int32_t FrameCnt5 = 0;	// Column 20
    int32_t FrameCnt6 = 0;	// Column 21
    int32_t FrameCnt7 = 0;	// Column 22
    int32_t FrameDelta0 = 0;	// Column 23
    int32_t FrameDelta1 = 0;	// Column 24
    int32_t FrameDelta2 = 0;	// Column 25
    int32_t FrameDelta3 = 0;	// Column 26
    int32_t FrameDelta4 = 0;	// Column 27
    int32_t FrameDelta5 = 0;	// Column 28
    int32_t FrameDelta6 = 0;	// Column 29
    int32_t FrameDelta7 = 0;	// Column 30
    int32_t CycleAnim0 = 0;	// Column 31
    int32_t CycleAnim1 = 0;	// Column 32
    int32_t CycleAnim2 = 0;	// Column 33
    int32_t CycleAnim3 = 0;	// Column 34
    int32_t CycleAnim4 = 0;	// Column 35
    int32_t CycleAnim5 = 0;	// Column 36
    int32_t CycleAnim6 = 0;	// Column 37
    int32_t CycleAnim7 = 0;	// Column 38
    int32_t Lit0 = 0;	// Column 39
    int32_t Lit1 = 0;	// Column 40
    int32_t Lit2 = 0;	// Column 41
    int32_t Lit3 = 0;	// Column 42
    int32_t Lit4 = 0;	// Column 43
    int32_t Lit5 = 0;	// Column 44
    int32_t Lit6 = 0;	// Column 45
    int32_t Lit7 = 0;	// Column 46
    int32_t BlocksLight0 = 0;	// Column 47
    int32_t BlocksLight1 = 0;	// Column 48
    int32_t BlocksLight2 = 0;	// Column 49
    int32_t BlocksLight3 = 0;	// Column 50
    int32_t BlocksLight4 = 0;	// Column 51
    int32_t BlocksLight5 = 0;	// Column 52
    int32_t BlocksLight6 = 0;	// Column 53
    int32_t BlocksLight7 = 0;	// Column 54
    int32_t HasCollision0 = 0;	// Column 55
    int32_t HasCollision1 = 0;	// Column 56
    int32_t HasCollision2 = 0;	// Column 57
    int32_t HasCollision3 = 0;	// Column 58
    int32_t HasCollision4 = 0;	// Column 59
    int32_t HasCollision5 = 0;	// Column 60
    int32_t HasCollision6 = 0;	// Column 61
    int32_t HasCollision7 = 0;	// Column 62
    int32_t IsAttackable0 = 0;	// Column 63
    int32_t Start0 = 0;	// Column 64
    int32_t Start1 = 0;	// Column 65
    int32_t Start2 = 0;	// Column 66
    int32_t Start3 = 0;	// Column 67
    int32_t Start4 = 0;	// Column 68
    int32_t Start5 = 0;	// Column 69
    int32_t Start6 = 0;	// Column 70
    int32_t Start7 = 0;	// Column 71
    int32_t EnvEffect = 0;	// Column 72
    int32_t IsDoor = 0;	// Column 73
    int32_t BlocksVis = 0;	// Column 74
    int32_t Orientation = 0;	// Column 75
    int32_t OrderFlag0 = 0;	// Column 76
    int32_t OrderFlag1 = 0;	// Column 77
    int32_t OrderFlag2 = 0;	// Column 78
    int32_t OrderFlag3 = 0;	// Column 79
    int32_t OrderFlag4 = 0;	// Column 80
    int32_t OrderFlag5 = 0;	// Column 81
    int32_t OrderFlag6 = 0;	// Column 82
    int32_t OrderFlag7 = 0;	// Column 83
    int32_t PreOperate = 0;	// Column 84
    int32_t Mode0 = 0;	// Column 85
    int32_t Mode1 = 0;	// Column 86
    int32_t Mode2 = 0;	// Column 87
    int32_t Mode3 = 0;	// Column 88
    int32_t Mode4 = 0;	// Column 89
    int32_t Mode5 = 0;	// Column 90
    int32_t Mode6 = 0;	// Column 91
    int32_t Mode7 = 0;	// Column 92
    int32_t Yoffset = 0;	// Column 93
    int32_t Xoffset = 0;	// Column 94
    int32_t Draw = 0;	// Column 95
    int32_t Red = 0;	// Column 96
    int32_t Green = 0;	// Column 97
    int32_t Blue = 0;	// Column 98
    int32_t HD = 0;	// Column 99
    int32_t TR = 0;	// Column 100
    int32_t LG = 0;	// Column 101
    int32_t RA = 0;	// Column 102
    int32_t LA = 0;	// Column 103
    int32_t RH = 0;	// Column 104
    int32_t LH = 0;	// Column 105
    int32_t SH = 0;	// Column 106
    int32_t S1 = 0;	// Column 107
    int32_t S2 = 0;	// Column 108
    int32_t S3 = 0;	// Column 109
    int32_t S4 = 0;	// Column 110
    int32_t S5 = 0;	// Column 111
    int32_t S6 = 0;	// Column 112
    int32_t S7 = 0;	// Column 113
    int32_t S8 = 0;	// Column 114
    int32_t TotalPieces = 0;	// Column 115
    int32_t SubClass = 0;	// Column 116
    int32_t Xspace = 0;	// Column 117
    int32_t Yspace = 0;	// Column 118
    int32_t NameOffset = 0;	// Column 119
    int32_t MonsterOK = 0;	// Column 120
    int32_t ShrineFunction = 0;	// Column 121
    int32_t Restore = 0;	// Column 122
    int32_t Parm0 = 0;	// Column 123
    int32_t Parm1 = 0;	// Column 124
    int32_t Parm2 = 0;	// Column 125
    int32_t Parm3 = 0;	// Column 126
    int32_t Parm4 = 0;	// Column 127
    int32_t Lockable = 0;	// Column 128
    int32_t Gore = 0;	// Column 129
    int32_t Sync = 0;	// Column 130
    int32_t Damage = 0;	// Column 131
    int32_t Overlay = 0;	// Column 132
    int32_t CollisionSubst = 0;	// Column 133
    int32_t Left = 0;	// Column 134
    int32_t Top = 0;	// Column 135
    int32_t Width = 0;	// Column 136
    int32_t Height = 0;	// Column 137
    int32_t OperateFn = 0;	// Column 138
    int32_t PopulateFn = 0;	// Column 139
    int32_t InitFn = 0;	// Column 140
    int32_t ClientFn = 0;	// Column 141
    int32_t RestoreVirgins = 0;	// Column 142
    int32_t BlockMissile = 0;	// Column 143
    int32_t DrawUnder = 0;	// Column 144
    int32_t OpenWarp = 0;	// Column 145
    int32_t AutoMap = 0;	// Column 146

    size_t read(const char* line);
    static std::vector<t_objects> readfile(std::string filename);
  };

  struct t_objgroup {
    std::string GroupName = "";	// Column 0
    int32_t ID = 0;	// Column 1
    int32_t ID0 = 0;	// Column 2
    int32_t DENSITY0 = 0;	// Column 3
    int32_t PROB0 = 0;	// Column 4
    int32_t ID1 = 0;	// Column 5
    int32_t DENSITY1 = 0;	// Column 6
    int32_t PROB1 = 0;	// Column 7
    int32_t ID2 = 0;	// Column 8
    int32_t DENSITY2 = 0;	// Column 9
    int32_t PROB2 = 0;	// Column 10
    int32_t ID3 = 0;	// Column 11
    int32_t DENSITY3 = 0;	// Column 12
    int32_t PROB3 = 0;	// Column 13
    int32_t ID4 = 0;	// Column 14
    int32_t DENSITY4 = 0;	// Column 15
    int32_t PROB4 = 0;	// Column 16
    int32_t ID5 = 0;	// Column 17
    int32_t DENSITY5 = 0;	// Column 18
    int32_t PROB5 = 0;	// Column 19
    int32_t ID6 = 0;	// Column 20
    int32_t DENSITY6 = 0;	// Column 21
    int32_t PROB6 = 0;	// Column 22
    int32_t ID7 = 0;	// Column 23
    int32_t DENSITY7 = 0;	// Column 24
    int32_t PROB7 = 0;	// Column 25

    size_t read(const char* line);
    static std::vector<t_objgroup> readfile(std::string filename);
  };

  struct t_objmode {
    std::string Name = "";	// Column 0
    std::string Token = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_objmode> readfile(std::string filename);
  };

  struct t_objpreset {
    int32_t Index = 0;	// Column 0
    int32_t Act = 0;	// Column 1
    std::string ObjectClass = "";	// Column 2
    std::string Notes = "";	// Column 3
    int32_t eol = 0;	// Column 4

    size_t read(const char* line);
    static std::vector<t_objpreset> readfile(std::string filename);
  };

  struct t_objtype {
    std::string Name = "";	// Column 0
    std::string Token = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_objtype> readfile(std::string filename);
  };

  struct t_overlay {
    std::string overlay = "";	// Column 0
    std::string ID = "";	// Column 1
    std::string Filename = "";	// Column 2
    int32_t version = 0;	// Column 3
    int32_t Frames = 0;	// Column 4
    std::string Character = "";	// Column 5
    int32_t PreDraw = 0;	// Column 6
    int32_t _1ofN = 0;	// Column 7
    int32_t Xoffset = 0;	// Column 8
    int32_t Yoffset = 0;	// Column 9
    int32_t Height1 = 0;	// Column 10
    int32_t Height2 = 0;	// Column 11
    int32_t Height3 = 0;	// Column 12
    int32_t Height4 = 0;	// Column 13
    int32_t AnimRate = 0;	// Column 14
    int32_t LoopWaitTime = 0;	// Column 15
    int32_t Trans = 0;	// Column 16
    int32_t InitRadius = 0;	// Column 17
    int32_t Radius = 0;	// Column 18
    int32_t Red = 0;	// Column 19
    int32_t Green = 0;	// Column 20
    int32_t Blue = 0;	// Column 21
    int32_t NumDirections = 0;	// Column 22
    int32_t LocalBlood = 0;	// Column 23
    int32_t WeaponStateFlags = 0;	// Column 24
    int32_t WeaponStateGroup = 0;	// Column 25
    std::string StartSound = "";	// Column 26

    size_t read(const char* line);
    static std::vector<t_overlay> readfile(std::string filename);
  };

  struct t_pettype {
    std::string pettype = "";	// Column 0
    // Unused column: group
    int32_t pool = 0;	// Column 2
    int32_t basemax = 0;	// Column 3
    int32_t warp = 0;	// Column 4
    int32_t range = 0;	// Column 5
    int32_t partysend = 0;	// Column 6
    int32_t unsummon = 0;	// Column 7
    int32_t automap = 0;	// Column 8
    std::string name = "";	// Column 9
    int32_t drawhp = 0;	// Column 10
    int32_t icontype = 0;	// Column 11
    std::string baseicon = "";	// Column 12
    int32_t mclass1 = 0;	// Column 13
    std::string micon1 = "";	// Column 14
    std::string overridename1 = "";	// Column 15
    int32_t mclass2 = 0;	// Column 16
    std::string micon2 = "";	// Column 17
    std::string overridename2 = "";	// Column 18
    int32_t mclass3 = 0;	// Column 19
    std::string micon3 = "";	// Column 20
    std::string overridename3 = "";	// Column 21
    int32_t mclass4 = 0;	// Column 22
    std::string micon4 = "";	// Column 23
    // Unused column: overridename4

    size_t read(const char* line);
    static std::vector<t_pettype> readfile(std::string filename);
  };

  struct t_playerclass {
    std::string PlayerClass = "";	// Column 0
    std::string Code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_playerclass> readfile(std::string filename);
  };

  struct t_plrmode {
    std::string Name = "";	// Column 0
    std::string Token = "";	// Column 1
    std::string Code = "";	// Column 2

    size_t read(const char* line);
    static std::vector<t_plrmode> readfile(std::string filename);
  };

  struct t_plrtype {
    std::string Name = "";	// Column 0
    std::string Token = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_plrtype> readfile(std::string filename);
  };

  struct t_properties {
    std::string code = "";	// Column 0
    int32_t Id = 0;	// Column 1
    int32_t Enabled = 0;	// Column 2
    int32_t func1 = 0;	// Column 3
    std::string stat1 = "";	// Column 4
    int32_t set1 = 0;	// Column 5
    int32_t val1 = 0;	// Column 6
    int32_t func2 = 0;	// Column 7
    std::string stat2 = "";	// Column 8
    // Unused column: set2
    int32_t val2 = 0;	// Column 10
    int32_t func3 = 0;	// Column 11
    std::string stat3 = "";	// Column 12
    // Unused column: set3
    int32_t val3 = 0;	// Column 14
    int32_t func4 = 0;	// Column 15
    std::string stat4 = "";	// Column 16
    // Unused column: set4
    // Unused column: val4
    int32_t func5 = 0;	// Column 19
    std::string stat5 = "";	// Column 20
    // Unused column: set5
    // Unused column: val5
    int32_t func6 = 0;	// Column 23
    std::string stat6 = "";	// Column 24
    // Unused column: set6
    // Unused column: val6
    int32_t func7 = 0;	// Column 27
    std::string stat7 = "";	// Column 28
    // Unused column: set7
    // Unused column: val7
    int32_t uiRangeType = 0;	// Column 31
    std::string Tooltip = "";	// Column 32
    std::string Parameter = "";	// Column 33
    std::string Min = "";	// Column 34
    std::string Max = "";	// Column 35
    std::string Notes = "";	// Column 36
    int32_t eol = 0;	// Column 37

    size_t read(const char* line);
    static std::vector<t_properties> readfile(std::string filename);
  };

  struct t_propertygroups {
    std::string code = "";	// Column 0
    int32_t Id = 0;	// Column 1
    int32_t PickMode = 0;	// Column 2
    std::string Prop1 = "";	// Column 3
    std::string ParMin1 = "";	// Column 4
    std::string ParMax1 = "";	// Column 5
    int32_t ModMin1 = 0;	// Column 6
    int32_t ModMax1 = 0;	// Column 7
    int32_t Chance1 = 0;	// Column 8
    std::string Prop2 = "";	// Column 9
    std::string ParMin2 = "";	// Column 10
    std::string ParMax2 = "";	// Column 11
    int32_t ModMin2 = 0;	// Column 12
    int32_t ModMax2 = 0;	// Column 13
    int32_t Chance2 = 0;	// Column 14
    std::string Prop3 = "";	// Column 15
    // Unused column: ParMin3
    // Unused column: ParMax3
    int32_t ModMin3 = 0;	// Column 18
    int32_t ModMax3 = 0;	// Column 19
    int32_t Chance3 = 0;	// Column 20
    std::string Prop4 = "";	// Column 21
    // Unused column: ParMin4
    // Unused column: ParMax4
    int32_t ModMin4 = 0;	// Column 24
    int32_t ModMax4 = 0;	// Column 25
    int32_t Chance4 = 0;	// Column 26
    std::string Prop5 = "";	// Column 27
    // Unused column: ParMin5
    // Unused column: ParMax5
    int32_t ModMin5 = 0;	// Column 30
    int32_t ModMax5 = 0;	// Column 31
    int32_t Chance5 = 0;	// Column 32
    std::string Prop6 = "";	// Column 33
    // Unused column: ParMin6
    // Unused column: ParMax6
    int32_t ModMin6 = 0;	// Column 36
    int32_t ModMax6 = 0;	// Column 37
    int32_t Chance6 = 0;	// Column 38
    // Unused column: Prop7
    // Unused column: ParMin7
    // Unused column: ParMax7
    // Unused column: ModMin7
    // Unused column: ModMax7
    // Unused column: Chance7
    // Unused column: Prop8
    // Unused column: ParMin8
    // Unused column: ParMax8
    // Unused column: ModMin8
    // Unused column: ModMax8
    // Unused column: Chance8
    // Unused column: *Tooltip
    // Unused column: *Parameter
    // Unused column: *Min
    // Unused column: *Max
    // Unused column: *Notes
    int32_t eol = 0;	// Column 56

    size_t read(const char* line);
    static std::vector<t_propertygroups> readfile(std::string filename);
  };

  struct t_qualityitems {
    std::string mod1code = "";	// Column 0
    int32_t mod1param = 0;	// Column 1
    int32_t mod1min = 0;	// Column 2
    int32_t mod1max = 0;	// Column 3
    std::string mod2code = "";	// Column 4
    int32_t mod2param = 0;	// Column 5
    int32_t mod2min = 0;	// Column 6
    int32_t mod2max = 0;	// Column 7
    int32_t armor = 0;	// Column 8
    int32_t weapon = 0;	// Column 9
    int32_t shield = 0;	// Column 10
    int32_t scepter = 0;	// Column 11
    int32_t wand = 0;	// Column 12
    int32_t staff = 0;	// Column 13
    int32_t bow = 0;	// Column 14
    int32_t boots = 0;	// Column 15
    int32_t gloves = 0;	// Column 16
    int32_t belt = 0;	// Column 17

    size_t read(const char* line);
    static std::vector<t_qualityitems> readfile(std::string filename);
  };

  struct t_rareprefix {
    std::string name = "";	// Column 0
    int32_t version = 0;	// Column 1
    std::string itype1 = "";	// Column 2
    std::string itype2 = "";	// Column 3
    std::string itype3 = "";	// Column 4
    std::string itype4 = "";	// Column 5
    std::string itype5 = "";	// Column 6
    // Unused column: itype6
    // Unused column: itype7
    // Unused column: etype1
    // Unused column: etype2
    // Unused column: etype3
    // Unused column: etype4

    size_t read(const char* line);
    static std::vector<t_rareprefix> readfile(std::string filename);
  };

  struct t_raresuffix {
    std::string name = "";	// Column 0
    int32_t version = 0;	// Column 1
    std::string itype1 = "";	// Column 2
    std::string itype2 = "";	// Column 3
    std::string itype3 = "";	// Column 4
    std::string itype4 = "";	// Column 5
    std::string itype5 = "";	// Column 6
    std::string itype6 = "";	// Column 7
    // Unused column: itype7
    // Unused column: etype1
    // Unused column: etype2
    // Unused column: etype3
    // Unused column: etype4

    size_t read(const char* line);
    static std::vector<t_raresuffix> readfile(std::string filename);
  };

  struct t_runes {
    std::string Name = "";	// Column 0
    std::string RuneName = "";	// Column 1
    int32_t complete = 0;	// Column 2
    int32_t disallowCraftingInLadder = 0;	// Column 3
    // Unused column: disallowCraftingInNonLadder
    int32_t firstLadderSeason = 0;	// Column 5
    int32_t lastLadderSeason = 0;	// Column 6
    std::string PatchRelease = "";	// Column 7
    std::string itype1 = "";	// Column 8
    std::string itype2 = "";	// Column 9
    std::string itype3 = "";	// Column 10
    std::string itype4 = "";	// Column 11
    // Unused column: itype5
    // Unused column: itype6
    // Unused column: etype1
    // Unused column: etype2
    // Unused column: etype3
    std::string RunesUsed = "";	// Column 17
    std::string Rune1 = "";	// Column 18
    std::string Rune2 = "";	// Column 19
    std::string Rune3 = "";	// Column 20
    std::string Rune4 = "";	// Column 21
    std::string Rune5 = "";	// Column 22
    std::string Rune6 = "";	// Column 23
    std::string T1Code1 = "";	// Column 24
    std::string T1Param1 = "";	// Column 25
    int32_t T1Min1 = 0;	// Column 26
    int32_t T1Max1 = 0;	// Column 27
    std::string T1Code2 = "";	// Column 28
    std::string T1Param2 = "";	// Column 29
    int32_t T1Min2 = 0;	// Column 30
    int32_t T1Max2 = 0;	// Column 31
    std::string T1Code3 = "";	// Column 32
    std::string T1Param3 = "";	// Column 33
    int32_t T1Min3 = 0;	// Column 34
    int32_t T1Max3 = 0;	// Column 35
    std::string T1Code4 = "";	// Column 36
    std::string T1Param4 = "";	// Column 37
    int32_t T1Min4 = 0;	// Column 38
    int32_t T1Max4 = 0;	// Column 39
    std::string T1Code5 = "";	// Column 40
    std::string T1Param5 = "";	// Column 41
    int32_t T1Min5 = 0;	// Column 42
    int32_t T1Max5 = 0;	// Column 43
    std::string T1Code6 = "";	// Column 44
    std::string T1Param6 = "";	// Column 45
    int32_t T1Min6 = 0;	// Column 46
    int32_t T1Max6 = 0;	// Column 47
    std::string T1Code7 = "";	// Column 48
    std::string T1Param7 = "";	// Column 49
    int32_t T1Min7 = 0;	// Column 50
    int32_t T1Max7 = 0;	// Column 51
    int32_t eol = 0;	// Column 52

    size_t read(const char* line);
    static std::vector<t_runes> readfile(std::string filename);
  };

  struct t_runeworduicategories {
    std::string Name = "";	// Column 0
    std::string Category = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_runeworduicategories> readfile(std::string filename);
  };

  struct t_setitems {
    std::string index = "";	// Column 0
    int32_t ID = 0;	// Column 1
    std::string set = "";	// Column 2
    // Unused column: disabled
    int32_t spawnable = 0;	// Column 4
    int32_t disableChronicle = 0;	// Column 5
    // Unused column: DropConditionCalc
    int32_t firstLadderSeason = 0;	// Column 7
    int32_t lastLadderSeason = 0;	// Column 8
    std::string item = "";	// Column 9
    std::string ItemName = "";	// Column 10
    int32_t rarity = 0;	// Column 11
    int32_t lvl = 0;	// Column 12
    int32_t lvlreq = 0;	// Column 13
    std::string chrtransform = "";	// Column 14
    std::string invtransform = "";	// Column 15
    std::string invfile = "";	// Column 16
    // Unused column: flippyfile
    // Unused column: dropsound
    // Unused column: dropsfxframe
    // Unused column: usesound
    int32_t costmult = 0;	// Column 21
    int32_t costadd = 0;	// Column 22
    int32_t addfunc = 0;	// Column 23
    std::string prop1 = "";	// Column 24
    int32_t par1 = 0;	// Column 25
    int32_t min1 = 0;	// Column 26
    int32_t max1 = 0;	// Column 27
    std::string prop2 = "";	// Column 28
    int32_t par2 = 0;	// Column 29
    int32_t min2 = 0;	// Column 30
    int32_t max2 = 0;	// Column 31
    std::string prop3 = "";	// Column 32
    int32_t par3 = 0;	// Column 33
    int32_t min3 = 0;	// Column 34
    int32_t max3 = 0;	// Column 35
    std::string prop4 = "";	// Column 36
    int32_t par4 = 0;	// Column 37
    int32_t min4 = 0;	// Column 38
    int32_t max4 = 0;	// Column 39
    std::string prop5 = "";	// Column 40
    std::string par5 = "";	// Column 41
    int32_t min5 = 0;	// Column 42
    int32_t max5 = 0;	// Column 43
    std::string prop6 = "";	// Column 44
    std::string par6 = "";	// Column 45
    int32_t min6 = 0;	// Column 46
    int32_t max6 = 0;	// Column 47
    std::string prop7 = "";	// Column 48
    std::string par7 = "";	// Column 49
    int32_t min7 = 0;	// Column 50
    int32_t max7 = 0;	// Column 51
    // Unused column: prop8
    // Unused column: par8
    // Unused column: min8
    // Unused column: max8
    // Unused column: prop9
    // Unused column: par9
    // Unused column: min9
    // Unused column: max9
    std::string aprop1a = "";	// Column 60
    int32_t apar1a = 0;	// Column 61
    int32_t amin1a = 0;	// Column 62
    int32_t amax1a = 0;	// Column 63
    std::string aprop1b = "";	// Column 64
    int32_t apar1b = 0;	// Column 65
    // Unused column: amin1b
    // Unused column: amax1b
    std::string aprop2a = "";	// Column 68
    std::string apar2a = "";	// Column 69
    int32_t amin2a = 0;	// Column 70
    int32_t amax2a = 0;	// Column 71
    std::string aprop2b = "";	// Column 72
    // Unused column: apar2b
    int32_t amin2b = 0;	// Column 74
    int32_t amax2b = 0;	// Column 75
    std::string aprop3a = "";	// Column 76
    int32_t apar3a = 0;	// Column 77
    int32_t amin3a = 0;	// Column 78
    int32_t amax3a = 0;	// Column 79
    // Unused column: aprop3b
    // Unused column: apar3b
    // Unused column: amin3b
    // Unused column: amax3b
    std::string aprop4a = "";	// Column 84
    int32_t apar4a = 0;	// Column 85
    int32_t amin4a = 0;	// Column 86
    int32_t amax4a = 0;	// Column 87
    // Unused column: aprop4b
    // Unused column: apar4b
    // Unused column: amin4b
    // Unused column: amax4b
    std::string aprop5a = "";	// Column 92
    int32_t apar5a = 0;	// Column 93
    int32_t amin5a = 0;	// Column 94
    int32_t amax5a = 0;	// Column 95
    // Unused column: aprop5b
    // Unused column: apar5b
    // Unused column: amin5b
    // Unused column: amax5b
    // Unused column: diablocloneweight
    int32_t eol = 0;	// Column 101

    size_t read(const char* line);
    static std::vector<t_setitems> readfile(std::string filename);
  };

  struct t_sets {
    std::string index = "";	// Column 0
    std::string name = "";	// Column 1
    int32_t version = 0;	// Column 2
    std::string PCode2a = "";	// Column 3
    int32_t PParam2a = 0;	// Column 4
    int32_t PMin2a = 0;	// Column 5
    int32_t PMax2a = 0;	// Column 6
    std::string PCode2b = "";	// Column 7
    std::string PParam2b = "";	// Column 8
    int32_t PMin2b = 0;	// Column 9
    int32_t PMax2b = 0;	// Column 10
    std::string PCode3a = "";	// Column 11
    int32_t PParam3a = 0;	// Column 12
    int32_t PMin3a = 0;	// Column 13
    int32_t PMax3a = 0;	// Column 14
    std::string PCode3b = "";	// Column 15
    std::string PParam3b = "";	// Column 16
    int32_t PMin3b = 0;	// Column 17
    int32_t PMax3b = 0;	// Column 18
    std::string PCode4a = "";	// Column 19
    // Unused column: PParam4a
    int32_t PMin4a = 0;	// Column 21
    int32_t PMax4a = 0;	// Column 22
    std::string PCode4b = "";	// Column 23
    std::string PParam4b = "";	// Column 24
    int32_t PMin4b = 0;	// Column 25
    int32_t PMax4b = 0;	// Column 26
    std::string PCode5a = "";	// Column 27
    // Unused column: PParam5a
    int32_t PMin5a = 0;	// Column 29
    int32_t PMax5a = 0;	// Column 30
    // Unused column: PCode5b
    // Unused column: PParam5b
    // Unused column: PMin5b
    // Unused column: PMax5b
    std::string FCode1 = "";	// Column 35
    int32_t FParam1 = 0;	// Column 36
    int32_t FMin1 = 0;	// Column 37
    int32_t FMax1 = 0;	// Column 38
    std::string FCode2 = "";	// Column 39
    std::string FParam2 = "";	// Column 40
    int32_t FMin2 = 0;	// Column 41
    int32_t FMax2 = 0;	// Column 42
    std::string FCode3 = "";	// Column 43
    int32_t FParam3 = 0;	// Column 44
    int32_t FMin3 = 0;	// Column 45
    int32_t FMax3 = 0;	// Column 46
    std::string FCode4 = "";	// Column 47
    int32_t FParam4 = 0;	// Column 48
    int32_t FMin4 = 0;	// Column 49
    int32_t FMax4 = 0;	// Column 50
    std::string FCode5 = "";	// Column 51
    std::string FParam5 = "";	// Column 52
    int32_t FMin5 = 0;	// Column 53
    int32_t FMax5 = 0;	// Column 54
    std::string FCode6 = "";	// Column 55
    std::string FParam6 = "";	// Column 56
    int32_t FMin6 = 0;	// Column 57
    int32_t FMax6 = 0;	// Column 58
    std::string FCode7 = "";	// Column 59
    std::string FParam7 = "";	// Column 60
    int32_t FMin7 = 0;	// Column 61
    int32_t FMax7 = 0;	// Column 62
    std::string FCode8 = "";	// Column 63
    // Unused column: FParam8
    int32_t FMin8 = 0;	// Column 65
    int32_t FMax8 = 0;	// Column 66
    std::string UIClass = "";	// Column 67
    int32_t eol = 0;	// Column 68

    size_t read(const char* line);
    static std::vector<t_sets> readfile(std::string filename);
  };

  struct t_shrines {
    std::string Name = "";	// Column 0
    std::string ShrineType = "";	// Column 1
    std::string Effect = "";	// Column 2
    int32_t Code = 0;	// Column 3
    int32_t Arg0 = 0;	// Column 4
    int32_t Arg1 = 0;	// Column 5
    int32_t Durationinframes = 0;	// Column 6
    int32_t resettimeinminutes = 0;	// Column 7
    int32_t rarity = 0;	// Column 8
    std::string StringName = "";	// Column 9
    std::string StringPhrase = "";	// Column 10
    int32_t effectclass = 0;	// Column 11
    int32_t LevelMin = 0;	// Column 12

    size_t read(const char* line);
    static std::vector<t_shrines> readfile(std::string filename);
  };

  struct t_skillcalc {
    std::string code = "";	// Column 0
    std::string Description = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_skillcalc> readfile(std::string filename);
  };

  struct t_skilldesc {
    std::string skilldesc = "";	// Column 0
    int32_t SkillPage = 0;	// Column 1
    int32_t SkillRow = 0;	// Column 2
    int32_t SkillColumn = 0;	// Column 3
    int32_t ListRow = 0;	// Column 4
    int32_t IconCel = 0;	// Column 5
    int32_t HireableIconCel = 0;	// Column 6
    std::string strname = "";	// Column 7
    std::string strshort = "";	// Column 8
    std::string strlong = "";	// Column 9
    std::string stralt = "";	// Column 10
    int32_t descdam = 0;	// Column 11
    std::string ddamcalc1 = "";	// Column 12
    std::string ddamcalc2 = "";	// Column 13
    std::string p1dmelem = "";	// Column 14
    std::string p1dmmin = "";	// Column 15
    std::string p1dmmax = "";	// Column 16
    std::string p2dmelem = "";	// Column 17
    std::string p2dmmin = "";	// Column 18
    std::string p2dmmax = "";	// Column 19
    std::string p3dmelem = "";	// Column 20
    std::string p3dmmin = "";	// Column 21
    std::string p3dmmax = "";	// Column 22
    int32_t descatt = 0;	// Column 23
    std::string descmissile1 = "";	// Column 24
    std::string descmissile2 = "";	// Column 25
    std::string descmissile3 = "";	// Column 26
    int32_t descline1 = 0;	// Column 27
    std::string desctexta1 = "";	// Column 28
    std::string desctextb1 = "";	// Column 29
    std::string desccalca1 = "";	// Column 30
    std::string desccalcb1 = "";	// Column 31
    int32_t descline2 = 0;	// Column 32
    std::string desctexta2 = "";	// Column 33
    std::string desctextb2 = "";	// Column 34
    std::string desccalca2 = "";	// Column 35
    std::string desccalcb2 = "";	// Column 36
    int32_t descline3 = 0;	// Column 37
    std::string desctexta3 = "";	// Column 38
    std::string desctextb3 = "";	// Column 39
    std::string desccalca3 = "";	// Column 40
    std::string desccalcb3 = "";	// Column 41
    int32_t descline4 = 0;	// Column 42
    std::string desctexta4 = "";	// Column 43
    std::string desctextb4 = "";	// Column 44
    std::string desccalca4 = "";	// Column 45
    std::string desccalcb4 = "";	// Column 46
    int32_t descline5 = 0;	// Column 47
    std::string desctexta5 = "";	// Column 48
    std::string desctextb5 = "";	// Column 49
    std::string desccalca5 = "";	// Column 50
    std::string desccalcb5 = "";	// Column 51
    int32_t descline6 = 0;	// Column 52
    std::string desctexta6 = "";	// Column 53
    // Unused column: desctextb6
    std::string desccalca6 = "";	// Column 55
    std::string desccalcb6 = "";	// Column 56
    int32_t dsc2line1 = 0;	// Column 57
    std::string dsc2texta1 = "";	// Column 58
    std::string dsc2textb1 = "";	// Column 59
    std::string dsc2calca1 = "";	// Column 60
    std::string dsc2calcb1 = "";	// Column 61
    int32_t dsc2line2 = 0;	// Column 62
    std::string dsc2texta2 = "";	// Column 63
    std::string dsc2textb2 = "";	// Column 64
    std::string dsc2calca2 = "";	// Column 65
    std::string dsc2calcb2 = "";	// Column 66
    int32_t dsc2line3 = 0;	// Column 67
    std::string dsc2texta3 = "";	// Column 68
    std::string dsc2textb3 = "";	// Column 69
    std::string dsc2calca3 = "";	// Column 70
    std::string dsc2calcb3 = "";	// Column 71
    int32_t dsc2line4 = 0;	// Column 72
    std::string dsc2texta4 = "";	// Column 73
    // Unused column: dsc2textb4
    std::string dsc2calca4 = "";	// Column 75
    // Unused column: dsc2calcb4
    int32_t dsc2line5 = 0;	// Column 77
    std::string dsc2texta5 = "";	// Column 78
    // Unused column: dsc2textb5
    std::string dsc2calca5 = "";	// Column 80
    // Unused column: dsc2calcb5
    int32_t dsc3line1 = 0;	// Column 82
    std::string dsc3texta1 = "";	// Column 83
    std::string dsc3textb1 = "";	// Column 84
    int32_t dsc3calca1 = 0;	// Column 85
    // Unused column: dsc3calcb1
    int32_t dsc3line2 = 0;	// Column 87
    std::string dsc3texta2 = "";	// Column 88
    std::string dsc3textb2 = "";	// Column 89
    std::string dsc3calca2 = "";	// Column 90
    std::string dsc3calcb2 = "";	// Column 91
    int32_t dsc3line3 = 0;	// Column 92
    std::string dsc3texta3 = "";	// Column 93
    std::string dsc3textb3 = "";	// Column 94
    std::string dsc3calca3 = "";	// Column 95
    std::string dsc3calcb3 = "";	// Column 96
    int32_t dsc3line4 = 0;	// Column 97
    std::string dsc3texta4 = "";	// Column 98
    std::string dsc3textb4 = "";	// Column 99
    std::string dsc3calca4 = "";	// Column 100
    int32_t dsc3calcb4 = 0;	// Column 101
    int32_t dsc3line5 = 0;	// Column 102
    std::string dsc3texta5 = "";	// Column 103
    std::string dsc3textb5 = "";	// Column 104
    std::string dsc3calca5 = "";	// Column 105
    int32_t dsc3calcb5 = 0;	// Column 106
    int32_t dsc3line6 = 0;	// Column 107
    std::string dsc3texta6 = "";	// Column 108
    std::string dsc3textb6 = "";	// Column 109
    std::string dsc3calca6 = "";	// Column 110
    int32_t dsc3calcb6 = 0;	// Column 111
    int32_t dsc3line7 = 0;	// Column 112
    std::string dsc3texta7 = "";	// Column 113
    // Unused column: dsc3textb7
    // Unused column: dsc3calca7
    // Unused column: dsc3calcb7
    std::string itemproctext = "";	// Column 117
    int32_t itemprocdesclinecount = 0;	// Column 118
    int32_t eol = 0;	// Column 119

    size_t read(const char* line);
    static std::vector<t_skilldesc> readfile(std::string filename);
  };

  struct t_skills {
    std::string skill = "";	// Column 0
    int32_t Id = 0;	// Column 1
    std::string charclass = "";	// Column 2
    std::string skilldesc = "";	// Column 3
    int32_t srvstfunc = 0;	// Column 4
    int32_t srvdofunc = 0;	// Column 5
    int32_t srvstopfunc = 0;	// Column 6
    int32_t prgstack = 0;	// Column 7
    int32_t srvprgfunc1 = 0;	// Column 8
    int32_t srvprgfunc2 = 0;	// Column 9
    int32_t srvprgfunc3 = 0;	// Column 10
    std::string prgcalc1 = "";	// Column 11
    std::string prgcalc2 = "";	// Column 12
    std::string prgcalc3 = "";	// Column 13
    int32_t prgdam = 0;	// Column 14
    std::string srvmissile = "";	// Column 15
    int32_t decquant = 0;	// Column 16
    int32_t lob = 0;	// Column 17
    std::string srvmissilea = "";	// Column 18
    std::string srvmissileb = "";	// Column 19
    std::string srvmissilec = "";	// Column 20
    // Unused column: useServerMissilesOnRemoteClients
    std::string srvoverlay = "";	// Column 22
    int32_t aurafilter = 0;	// Column 23
    std::string aurastate = "";	// Column 24
    std::string auratargetstate = "";	// Column 25
    std::string auralencalc = "";	// Column 26
    std::string aurarangecalc = "";	// Column 27
    std::string aurastat1 = "";	// Column 28
    std::string aurastatcalc1 = "";	// Column 29
    std::string aurastat2 = "";	// Column 30
    std::string aurastatcalc2 = "";	// Column 31
    std::string aurastat3 = "";	// Column 32
    std::string aurastatcalc3 = "";	// Column 33
    std::string aurastat4 = "";	// Column 34
    std::string aurastatcalc4 = "";	// Column 35
    std::string aurastat5 = "";	// Column 36
    std::string aurastatcalc5 = "";	// Column 37
    std::string aurastat6 = "";	// Column 38
    std::string aurastatcalc6 = "";	// Column 39
    std::string auraevent1 = "";	// Column 40
    int32_t auraeventfunc1 = 0;	// Column 41
    std::string auraevent2 = "";	// Column 42
    int32_t auraeventfunc2 = 0;	// Column 43
    std::string auraevent3 = "";	// Column 44
    int32_t auraeventfunc3 = 0;	// Column 45
    std::string auraevent4 = "";	// Column 46
    int32_t auraeventfunc4 = 0;	// Column 47
    std::string passivestate = "";	// Column 48
    std::string passiveitype = "";	// Column 49
    int32_t passivereqweaponcount = 0;	// Column 50
    std::string passivestat1 = "";	// Column 51
    std::string passivecalc1 = "";	// Column 52
    std::string passivestat2 = "";	// Column 53
    std::string passivecalc2 = "";	// Column 54
    std::string passivestat3 = "";	// Column 55
    std::string passivecalc3 = "";	// Column 56
    std::string passivestat4 = "";	// Column 57
    std::string passivecalc4 = "";	// Column 58
    std::string passivestat5 = "";	// Column 59
    std::string passivecalc5 = "";	// Column 60
    std::string passivestat6 = "";	// Column 61
    std::string passivecalc6 = "";	// Column 62
    std::string passivestat7 = "";	// Column 63
    std::string passivecalc7 = "";	// Column 64
    std::string passivestat8 = "";	// Column 65
    std::string passivecalc8 = "";	// Column 66
    std::string passivestat9 = "";	// Column 67
    std::string passivecalc9 = "";	// Column 68
    std::string passivestat10 = "";	// Column 69
    std::string passivecalc10 = "";	// Column 70
    std::string passivestat11 = "";	// Column 71
    std::string passivecalc11 = "";	// Column 72
    std::string passivestat12 = "";	// Column 73
    std::string passivecalc12 = "";	// Column 74
    std::string passivestat13 = "";	// Column 75
    std::string passivecalc13 = "";	// Column 76
    std::string passivestat14 = "";	// Column 77
    std::string passivecalc14 = "";	// Column 78
    std::string summon = "";	// Column 79
    std::string pettype = "";	// Column 80
    std::string petmax = "";	// Column 81
    int32_t requirespettype = 0;	// Column 82
    std::string summode = "";	// Column 83
    std::string sumskill1 = "";	// Column 84
    std::string sumsk1calc = "";	// Column 85
    std::string sumskill2 = "";	// Column 86
    std::string sumsk2calc = "";	// Column 87
    std::string sumskill3 = "";	// Column 88
    std::string sumsk3calc = "";	// Column 89
    std::string sumskill4 = "";	// Column 90
    std::string sumsk4calc = "";	// Column 91
    std::string sumskill5 = "";	// Column 92
    std::string sumsk5calc = "";	// Column 93
    int32_t sumumod = 0;	// Column 94
    std::string sumoverlay = "";	// Column 95
    int32_t stsuccessonly = 0;	// Column 96
    std::string stsound = "";	// Column 97
    std::string stsoundclass = "";	// Column 98
    int32_t stsounddelay = 0;	// Column 99
    int32_t weaponsnd = 0;	// Column 100
    std::string dosound = "";	// Column 101
    std::string dosounda = "";	// Column 102
    std::string dosoundb = "";	// Column 103
    std::string tgtoverlay = "";	// Column 104
    std::string tgtsound = "";	// Column 105
    std::string prgoverlay = "";	// Column 106
    std::string prgsound = "";	// Column 107
    std::string castoverlay = "";	// Column 108
    std::string cltoverlaya = "";	// Column 109
    std::string cltoverlayb = "";	// Column 110
    int32_t cltstfunc = 0;	// Column 111
    int32_t cltdofunc = 0;	// Column 112
    int32_t cltstopfunc = 0;	// Column 113
    int32_t cltprgfunc1 = 0;	// Column 114
    int32_t cltprgfunc2 = 0;	// Column 115
    int32_t cltprgfunc3 = 0;	// Column 116
    std::string cltmissile = "";	// Column 117
    std::string cltmissilea = "";	// Column 118
    std::string cltmissileb = "";	// Column 119
    std::string cltmissilec = "";	// Column 120
    std::string cltmissiled = "";	// Column 121
    std::string cltcalc1 = "";	// Column 122
    std::string cltcalc1desc = "";	// Column 123
    std::string cltcalc2 = "";	// Column 124
    std::string cltcalc2desc = "";	// Column 125
    int32_t cltcalc3 = 0;	// Column 126
    std::string cltcalc3desc = "";	// Column 127
    int32_t warp = 0;	// Column 128
    int32_t immediate = 0;	// Column 129
    int32_t enhanceable = 0;	// Column 130
    int32_t attackrank = 0;	// Column 131
    int32_t noammo = 0;	// Column 132
    std::string range = "";	// Column 133
    int32_t weapsel = 0;	// Column 134
    int32_t requiresweapon = 0;	// Column 135
    std::string itypea1 = "";	// Column 136
    std::string itypea2 = "";	// Column 137
    // Unused column: itypea3
    std::string etypea1 = "";	// Column 139
    // Unused column: etypea2
    std::string itypeb1 = "";	// Column 141
    // Unused column: itypeb2
    // Unused column: itypeb3
    // Unused column: etypeb1
    // Unused column: etypeb2
    std::string anim = "";	// Column 146
    std::string seqtrans = "";	// Column 147
    std::string monanim = "";	// Column 148
    int32_t seqnum = 0;	// Column 149
    int32_t seqinput = 0;	// Column 150
    int32_t durability = 0;	// Column 151
    int32_t UseAttackRate = 0;	// Column 152
    int32_t LineOfSight = 0;	// Column 153
    int32_t TargetableOnly = 0;	// Column 154
    int32_t SearchEnemyXY = 0;	// Column 155
    int32_t SearchEnemyNear = 0;	// Column 156
    int32_t SearchOpenXY = 0;	// Column 157
    int32_t SelectProc = 0;	// Column 158
    int32_t TargetCorpse = 0;	// Column 159
    int32_t TargetPet = 0;	// Column 160
    int32_t TargetAlly = 0;	// Column 161
    int32_t TargetItem = 0;	// Column 162
    int32_t AttackNoMana = 0;	// Column 163
    int32_t TgtPlaceCheck = 0;	// Column 164
    int32_t KeepCursorStateOnKill = 0;	// Column 165
    int32_t ContinueCastUnselected = 0;	// Column 166
    int32_t ClearSelectedOnHold = 0;	// Column 167
    int32_t ItemEffect = 0;	// Column 168
    int32_t ItemCltEffect = 0;	// Column 169
    int32_t ItemTgtDo = 0;	// Column 170
    int32_t ItemTarget = 0;	// Column 171
    int32_t ItemUseRestrict = 0;	// Column 172
    int32_t ItemCheckStart = 0;	// Column 173
    int32_t ItemCltCheckStart = 0;	// Column 174
    std::string ItemCastSound = "";	// Column 175
    std::string ItemCastOverlay = "";	// Column 176
    // Unused column: skpoints
    int32_t reqlevel = 0;	// Column 178
    int32_t maxlvl = 0;	// Column 179
    // Unused column: reqstr
    // Unused column: reqdex
    // Unused column: reqint
    // Unused column: reqvit
    std::string reqskill1 = "";	// Column 184
    std::string reqskill2 = "";	// Column 185
    // Unused column: reqskill3
    int32_t restrict = 0;	// Column 187
    std::string State1 = "";	// Column 188
    std::string State2 = "";	// Column 189
    // Unused column: State3
    int32_t localdelay = 0;	// Column 191
    int32_t globaldelay = 0;	// Column 192
    int32_t leftskill = 0;	// Column 193
    int32_t rightskill = 0;	// Column 194
    int32_t repeat = 0;	// Column 195
    int32_t alwayshit = 0;	// Column 196
    int32_t usemanaondo = 0;	// Column 197
    int32_t startmana = 0;	// Column 198
    int32_t minmana = 0;	// Column 199
    int32_t manashift = 0;	// Column 200
    int32_t mana = 0;	// Column 201
    int32_t lvlmana = 0;	// Column 202
    int32_t interrupt = 0;	// Column 203
    int32_t InTown = 0;	// Column 204
    int32_t aura = 0;	// Column 205
    int32_t periodic = 0;	// Column 206
    std::string perdelay = "";	// Column 207
    int32_t periodicClearAura = 0;	// Column 208
    int32_t finishing = 0;	// Column 209
    int32_t prgchargestocast = 0;	// Column 210
    int32_t prgchargesconsumed = 0;	// Column 211
    int32_t passive = 0;	// Column 212
    int32_t progressive = 0;	// Column 213
    std::string scroll = "";	// Column 214
    std::string calc1 = "";	// Column 215
    std::string calc1desc = "";	// Column 216
    std::string calc2 = "";	// Column 217
    std::string calc2desc = "";	// Column 218
    std::string calc3 = "";	// Column 219
    std::string calc3desc = "";	// Column 220
    std::string calc4 = "";	// Column 221
    std::string calc4desc = "";	// Column 222
    std::string calc5 = "";	// Column 223
    std::string calc5desc = "";	// Column 224
    std::string calc6 = "";	// Column 225
    std::string calc6desc = "";	// Column 226
    std::string calc7 = "";	// Column 227
    std::string calc7desc = "";	// Column 228
    std::string calc8 = "";	// Column 229
    std::string calc8desc = "";	// Column 230
    std::string calc9 = "";	// Column 231
    std::string calc9desc = "";	// Column 232
    std::string calc10 = "";	// Column 233
    std::string calc10desc = "";	// Column 234
    int32_t Param1 = 0;	// Column 235
    std::string Param1Description = "";	// Column 236
    int32_t Param2 = 0;	// Column 237
    std::string Param2Description = "";	// Column 238
    int32_t Param3 = 0;	// Column 239
    std::string Param3Description = "";	// Column 240
    int32_t Param4 = 0;	// Column 241
    std::string Param4Description = "";	// Column 242
    int32_t Param5 = 0;	// Column 243
    std::string Param5Description = "";	// Column 244
    int32_t Param6 = 0;	// Column 245
    std::string Param6Description = "";	// Column 246
    int32_t Param7 = 0;	// Column 247
    std::string Param7Description = "";	// Column 248
    int32_t Param8 = 0;	// Column 249
    std::string Param8Description = "";	// Column 250
    int32_t Param9 = 0;	// Column 251
    std::string Param9Description = "";	// Column 252
    int32_t Param10 = 0;	// Column 253
    std::string Param10Description2 = "";	// Column 254
    int32_t Param11 = 0;	// Column 255
    std::string Param11Description = "";	// Column 256
    int32_t Param12 = 0;	// Column 257
    std::string Param12Description = "";	// Column 258
    int32_t Param13 = 0;	// Column 259
    std::string Param13Description = "";	// Column 260
    int32_t Param14 = 0;	// Column 261
    std::string Param14Description = "";	// Column 262
    // Unused column: Param15
    // Unused column: *Param15Description
    // Unused column: Param16
    // Unused column: *Param16Description
    // Unused column: Param17
    // Unused column: *Param17Description
    // Unused column: Param18
    // Unused column: *Param18Description
    // Unused column: Param19
    // Unused column: *Param19Description
    // Unused column: Param20
    // Unused column: *Param20Description
    int32_t InGame = 0;	// Column 275
    int32_t ToHit = 0;	// Column 276
    int32_t LevToHit = 0;	// Column 277
    std::string ToHitCalc = "";	// Column 278
    int32_t ResultFlags = 0;	// Column 279
    int32_t HitFlags = 0;	// Column 280
    int32_t HitClass = 0;	// Column 281
    int32_t Kick = 0;	// Column 282
    int32_t HitShift = 0;	// Column 283
    int32_t SrcDam = 0;	// Column 284
    int32_t MinDam = 0;	// Column 285
    int32_t MinLevDam1 = 0;	// Column 286
    int32_t MinLevDam2 = 0;	// Column 287
    int32_t MinLevDam3 = 0;	// Column 288
    int32_t MinLevDam4 = 0;	// Column 289
    int32_t MinLevDam5 = 0;	// Column 290
    int32_t MaxDam = 0;	// Column 291
    int32_t MaxLevDam1 = 0;	// Column 292
    int32_t MaxLevDam2 = 0;	// Column 293
    int32_t MaxLevDam3 = 0;	// Column 294
    int32_t MaxLevDam4 = 0;	// Column 295
    int32_t MaxLevDam5 = 0;	// Column 296
    std::string DmgSymPerCalc = "";	// Column 297
    std::string EType = "";	// Column 298
    int32_t EMin = 0;	// Column 299
    int32_t EMinLev1 = 0;	// Column 300
    int32_t EMinLev2 = 0;	// Column 301
    int32_t EMinLev3 = 0;	// Column 302
    int32_t EMinLev4 = 0;	// Column 303
    int32_t EMinLev5 = 0;	// Column 304
    int32_t EMax = 0;	// Column 305
    int32_t EMaxLev1 = 0;	// Column 306
    int32_t EMaxLev2 = 0;	// Column 307
    int32_t EMaxLev3 = 0;	// Column 308
    int32_t EMaxLev4 = 0;	// Column 309
    int32_t EMaxLev5 = 0;	// Column 310
    std::string EDmgSymPerCalc = "";	// Column 311
    int32_t ELen = 0;	// Column 312
    int32_t ELevLen1 = 0;	// Column 313
    int32_t ELevLen2 = 0;	// Column 314
    int32_t ELevLen3 = 0;	// Column 315
    std::string ELenSymPerCalc = "";	// Column 316
    int32_t aitype = 0;	// Column 317
    int32_t aibonus = 0;	// Column 318
    int32_t costmult = 0;	// Column 319
    int32_t costadd = 0;	// Column 320
    int32_t eol = 0;	// Column 321

    size_t read(const char* line);
    static std::vector<t_skills> readfile(std::string filename);
  };

  struct t_soundenviron {
    std::string Handle = "";	// Column 0
    int32_t Index = 0;	// Column 1
    std::string Song = "";	// Column 2
    std::string DayAmbience = "";	// Column 3
    std::string HDDayAmbience = "";	// Column 4
    std::string NightAmbience = "";	// Column 5
    std::string HDNightAmbience = "";	// Column 6
    std::string DayEvent = "";	// Column 7
    std::string HDDayEvent = "";	// Column 8
    std::string NightEvent = "";	// Column 9
    std::string HDNightEvent = "";	// Column 10
    int32_t EventDelay = 0;	// Column 11
    int32_t HDEventDelay = 0;	// Column 12
    int32_t Indoors = 0;	// Column 13
    int32_t Material1 = 0;	// Column 14
    int32_t HDMaterial1 = 0;	// Column 15
    int32_t Material2 = 0;	// Column 16
    int32_t HDMaterial2 = 0;	// Column 17
    int32_t SFXEAXEnviron = 0;	// Column 18
    int32_t SFXEAXRoomVol = 0;	// Column 19
    int32_t SFXEAXRoomHF = 0;	// Column 20
    int32_t SFXEAXDecayTime = 0;	// Column 21
    int32_t SFXEAXDecayHF = 0;	// Column 22
    int32_t SFXEAXReflect = 0;	// Column 23
    int32_t SFXEAXReflectDelay = 0;	// Column 24
    int32_t SFXEAXReverb = 0;	// Column 25
    int32_t SFXEAXRevDelay = 0;	// Column 26
    int32_t VOXEAXEnviron = 0;	// Column 27
    int32_t VOXEAXRoomVol = 0;	// Column 28
    int32_t VOXEAXRoomHF = 0;	// Column 29
    int32_t VOXEAXDecayTime = 0;	// Column 30
    int32_t VOXEAXDecayHF = 0;	// Column 31
    int32_t VOXEAXReflect = 0;	// Column 32
    int32_t VOXEAXReflectDelay = 0;	// Column 33
    int32_t VOXEAXReverb = 0;	// Column 34
    int32_t VOXEAXRevDelay = 0;	// Column 35
    int32_t InheritEnvrionment = 0;	// Column 36

    size_t read(const char* line);
    static std::vector<t_soundenviron> readfile(std::string filename);
  };

  struct t_sounds {
    std::string Sound = "";	// Column 0
    int32_t Index = 0;	// Column 1
    std::string Redirect = "";	// Column 2
    std::string Channel = "";	// Column 3
    std::string FileName = "";	// Column 4
    int32_t IsLocal = 0;	// Column 5
    int32_t IsMusic = 0;	// Column 6
    int32_t IsAmbientScene = 0;	// Column 7
    int32_t IsAmbientEvent = 0;	// Column 8
    int32_t IsUI = 0;	// Column 9
    int32_t VolumeMin = 0;	// Column 10
    int32_t VolumeMax = 0;	// Column 11
    int32_t PitchMin = 0;	// Column 12
    int32_t PitchMax = 0;	// Column 13
    int32_t GroupSize = 0;	// Column 14
    int32_t GroupWeight = 0;	// Column 15
    int32_t Loop = 0;	// Column 16
    int32_t FadeIn = 0;	// Column 17
    int32_t FadeOut = 0;	// Column 18
    int32_t DeferInst = 0;	// Column 19
    int32_t StopInst = 0;	// Column 20
    int32_t Duration = 0;	// Column 21
    int32_t Compound = 0;	// Column 22
    int32_t Falloff = 0;	// Column 23
    int32_t LFEMix = 0;	// Column 24
    int32_t _3dSpread = 0;	// Column 25
    int32_t Priority = 0;	// Column 26
    int32_t Stream = 0;	// Column 27
    int32_t Is2D = 0;	// Column 28
    int32_t Tracking = 0;	// Column 29
    int32_t Solo = 0;	// Column 30
    int32_t MusicVol = 0;	// Column 31
    int32_t Block1 = 0;	// Column 32
    int32_t Block2 = 0;	// Column 33
    int32_t Block3 = 0;	// Column 34
    int32_t HDOptOut = 0;	// Column 35
    int32_t Delay = 0;	// Column 36
    // Unused column: 4841

    size_t read(const char* line);
    static std::vector<t_sounds> readfile(std::string filename);
  };

  struct t_states {
    std::string state = "";	// Column 0
    int32_t ID = 0;	// Column 1
    int32_t group = 0;	// Column 2
    int32_t remhit = 0;	// Column 3
    int32_t nosend = 0;	// Column 4
    int32_t transform = 0;	// Column 5
    int32_t aura = 0;	// Column 6
    int32_t curable = 0;	// Column 7
    int32_t curse = 0;	// Column 8
    int32_t active = 0;	// Column 9
    int32_t restrict = 0;	// Column 10
    int32_t disguise = 0;	// Column 11
    int32_t attblue = 0;	// Column 12
    int32_t damblue = 0;	// Column 13
    int32_t armblue = 0;	// Column 14
    int32_t rfblue = 0;	// Column 15
    int32_t rlblue = 0;	// Column 16
    int32_t rcblue = 0;	// Column 17
    int32_t stambarblue = 0;	// Column 18
    int32_t rpblue = 0;	// Column 19
    // Unused column: attred
    int32_t damred = 0;	// Column 21
    int32_t armred = 0;	// Column 22
    int32_t rfred = 0;	// Column 23
    int32_t rlred = 0;	// Column 24
    int32_t rcred = 0;	// Column 25
    int32_t rpred = 0;	// Column 26
    int32_t exp = 0;	// Column 27
    int32_t plrstaydeath = 0;	// Column 28
    int32_t monstaydeath = 0;	// Column 29
    int32_t bossstaydeath = 0;	// Column 30
    int32_t hide = 0;	// Column 31
    int32_t hidedead = 0;	// Column 32
    int32_t shatter = 0;	// Column 33
    int32_t udead = 0;	// Column 34
    int32_t life = 0;	// Column 35
    int32_t green = 0;	// Column 36
    int32_t pgsv = 0;	// Column 37
    int32_t nooverlays = 0;	// Column 38
    int32_t noclear = 0;	// Column 39
    int32_t bossinv = 0;	// Column 40
    int32_t meleeonly = 0;	// Column 41
    int32_t notondead = 0;	// Column 42
    std::string overlay1 = "";	// Column 43
    std::string overlay2 = "";	// Column 44
    std::string overlay3 = "";	// Column 45
    std::string overlay4 = "";	// Column 46
    std::string pgsvoverlay = "";	// Column 47
    std::string castoverlay = "";	// Column 48
    std::string removerlay = "";	// Column 49
    std::string stat = "";	// Column 50
    int32_t setfunc = 0;	// Column 51
    int32_t remfunc = 0;	// Column 52
    std::string missile = "";	// Column 53
    std::string skill = "";	// Column 54
    std::string itemtype = "";	// Column 55
    std::string itemtrans = "";	// Column 56
    int32_t colorpri = 0;	// Column 57
    int32_t colorshift = 0;	// Column 58
    int32_t lightr = 0;	// Column 59
    int32_t lightg = 0;	// Column 60
    int32_t lightb = 0;	// Column 61
    std::string onsound = "";	// Column 62
    std::string offsound = "";	// Column 63
    int32_t gfxtype = 0;	// Column 64
    int32_t gfxclass = 0;	// Column 65
    std::string cltevent = "";	// Column 66
    int32_t clteventfunc = 0;	// Column 67
    int32_t cltactivefunc = 0;	// Column 68
    int32_t srvactivefunc = 0;	// Column 69
    // Unused column: canstack
    int32_t sunderfull = 0;	// Column 71
    int32_t sunderresreduce = 0;	// Column 72
    int32_t vfxweaponstate = 0;	// Column 73
    int32_t eol = 0;	// Column 74

    size_t read(const char* line);
    static std::vector<t_states> readfile(std::string filename);
  };

  struct t_storepage {
    std::string StorePage = "";	// Column 0
    std::string Code = "";	// Column 1

    size_t read(const char* line);
    static std::vector<t_storepage> readfile(std::string filename);
  };

  struct t_superuniques {
    std::string Superunique = "";	// Column 0
    std::string Name = "";	// Column 1
    std::string Class = "";	// Column 2
    int32_t hcIdx = 0;	// Column 3
    std::string MonSound = "";	// Column 4
    int32_t Mod1 = 0;	// Column 5
    int32_t Mod2 = 0;	// Column 6
    int32_t Mod3 = 0;	// Column 7
    int32_t MinGrp = 0;	// Column 8
    int32_t MaxGrp = 0;	// Column 9
    int32_t AutoPos = 0;	// Column 10
    int32_t Stacks = 0;	// Column 11
    int32_t Replaceable = 0;	// Column 12
    int32_t Utrans = 0;	// Column 13
    int32_t UtransN = 0;	// Column 14
    int32_t UtransH = 0;	// Column 15
    std::string TC = "";	// Column 16
    std::string TCDesecrated = "";	// Column 17
    std::string TCN = "";	// Column 18
    std::string TCNDesecrated = "";	// Column 19
    std::string TCH = "";	// Column 20
    std::string TCHDesecrated = "";	// Column 21
    int32_t eol = 0;	// Column 22

    size_t read(const char* line);
    static std::vector<t_superuniques> readfile(std::string filename);
  };

  struct t_treasureclassex {
    std::string TreasureClass = "";	// Column 0
    int32_t group = 0;	// Column 1
    int32_t level = 0;	// Column 2
    int32_t Picks = 0;	// Column 3
    int32_t Unique = 0;	// Column 4
    int32_t Set = 0;	// Column 5
    int32_t Rare = 0;	// Column 6
    int32_t Magic = 0;	// Column 7
    int32_t NoDrop = 0;	// Column 8
    std::string Item1 = "";	// Column 9
    int32_t Prob1 = 0;	// Column 10
    std::string Item2 = "";	// Column 11
    int32_t Prob2 = 0;	// Column 12
    std::string Item3 = "";	// Column 13
    int32_t Prob3 = 0;	// Column 14
    std::string Item4 = "";	// Column 15
    int32_t Prob4 = 0;	// Column 16
    std::string Item5 = "";	// Column 17
    int32_t Prob5 = 0;	// Column 18
    std::string Item6 = "";	// Column 19
    int32_t Prob6 = 0;	// Column 20
    std::string Item7 = "";	// Column 21
    int32_t Prob7 = 0;	// Column 22
    std::string Item8 = "";	// Column 23
    int32_t Prob8 = 0;	// Column 24
    std::string Item9 = "";	// Column 25
    int32_t Prob9 = 0;	// Column 26
    // Unused column: Item10
    // Unused column: Prob10
    int32_t ItemProbSum = 0;	// Column 29
    int32_t ItemProbTotal = 0;	// Column 30
    int32_t TreasureClassDropChance = 0;	// Column 31
    std::string ConditionCalc = "";	// Column 32
    int32_t firstLadderSeason = 0;	// Column 33
    int32_t lastLadderSeason = 0;	// Column 34
    int32_t noAlwaysSpawn = 0;	// Column 35
    // Unused column: QuestFlag
    int32_t QuestFlagEx = 0;	// Column 37
    int32_t eol = 0;	// Column 38

    size_t read(const char* line);
    static std::vector<t_treasureclassex> readfile(std::string filename);
  };

  struct t_uniqueappellation {
    std::string Name = "";	// Column 0

    size_t read(const char* line);
    static std::vector<t_uniqueappellation> readfile(std::string filename);
  };

  struct t_uniqueitems {
    std::string index = "";	// Column 0
    int32_t ID = 0;	// Column 1
    int32_t version = 0;	// Column 2
    // Unused column: disabled
    int32_t spawnable = 0;	// Column 4
    int32_t disableChronicle = 0;	// Column 5
    std::string DropConditionCalc = "";	// Column 6
    int32_t firstLadderSeason = 0;	// Column 7
    int32_t lastLadderSeason = 0;	// Column 8
    int32_t rarity = 0;	// Column 9
    // Unused column: nolimit
    int32_t lvl = 0;	// Column 11
    int32_t lvlreq = 0;	// Column 12
    std::string code = "";	// Column 13
    std::string ItemName = "";	// Column 14
    int32_t carry1 = 0;	// Column 15
    int32_t costmult = 0;	// Column 16
    int32_t costadd = 0;	// Column 17
    std::string chrtransform = "";	// Column 18
    std::string invtransform = "";	// Column 19
    std::string flippyfile = "";	// Column 20
    std::string invfile = "";	// Column 21
    std::string dropsound = "";	// Column 22
    int32_t dropsfxframe = 0;	// Column 23
    std::string usesound = "";	// Column 24
    std::string prop1 = "";	// Column 25
    std::string par1 = "";	// Column 26
    int32_t min1 = 0;	// Column 27
    int32_t max1 = 0;	// Column 28
    std::string prop2 = "";	// Column 29
    std::string par2 = "";	// Column 30
    int32_t min2 = 0;	// Column 31
    int32_t max2 = 0;	// Column 32
    std::string prop3 = "";	// Column 33
    std::string par3 = "";	// Column 34
    int32_t min3 = 0;	// Column 35
    int32_t max3 = 0;	// Column 36
    std::string prop4 = "";	// Column 37
    std::string par4 = "";	// Column 38
    int32_t min4 = 0;	// Column 39
    int32_t max4 = 0;	// Column 40
    std::string prop5 = "";	// Column 41
    std::string par5 = "";	// Column 42
    int32_t min5 = 0;	// Column 43
    int32_t max5 = 0;	// Column 44
    std::string prop6 = "";	// Column 45
    std::string par6 = "";	// Column 46
    int32_t min6 = 0;	// Column 47
    int32_t max6 = 0;	// Column 48
    std::string prop7 = "";	// Column 49
    std::string par7 = "";	// Column 50
    int32_t min7 = 0;	// Column 51
    int32_t max7 = 0;	// Column 52
    std::string prop8 = "";	// Column 53
    std::string par8 = "";	// Column 54
    int32_t min8 = 0;	// Column 55
    int32_t max8 = 0;	// Column 56
    std::string prop9 = "";	// Column 57
    std::string par9 = "";	// Column 58
    int32_t min9 = 0;	// Column 59
    int32_t max9 = 0;	// Column 60
    std::string prop10 = "";	// Column 61
    std::string par10 = "";	// Column 62
    int32_t min10 = 0;	// Column 63
    int32_t max10 = 0;	// Column 64
    // Unused column: prop11
    // Unused column: par11
    // Unused column: min11
    // Unused column: max11
    // Unused column: prop12
    // Unused column: par12
    // Unused column: min12
    // Unused column: max12
    int32_t diablocloneweight = 0;	// Column 73
    int32_t eol = 0;	// Column 74

    size_t read(const char* line);
    static std::vector<t_uniqueitems> readfile(std::string filename);
  };

  struct t_uniqueprefix {
    std::string Name = "";	// Column 0

    size_t read(const char* line);
    static std::vector<t_uniqueprefix> readfile(std::string filename);
  };

  struct t_uniquesuffix {
    std::string Name = "";	// Column 0

    size_t read(const char* line);
    static std::vector<t_uniquesuffix> readfile(std::string filename);
  };

  struct t_wanderingmon {
    std::string _class = "";	// Column 0

    size_t read(const char* line);
    static std::vector<t_wanderingmon> readfile(std::string filename);
  };

  struct t_weapons {
    std::string name = "";	// Column 0
    std::string type = "";	// Column 1
    // Unused column: type2
    std::string code = "";	// Column 3
    std::string alternategfx = "";	// Column 4
    std::string namestr = "";	// Column 5
    int32_t version = 0;	// Column 6
    // Unused column: compactsave
    int32_t rarity = 0;	// Column 8
    int32_t spawnable = 0;	// Column 9
    // Unused column: DropConditionCalc
    int32_t Transmogrify = 0;	// Column 11
    std::string TMogType = "";	// Column 12
    // Unused column: TMogMin
    // Unused column: TMogMax
    int32_t mindam = 0;	// Column 15
    int32_t maxdam = 0;	// Column 16
    int32_t _1or2handed = 0;	// Column 17
    int32_t _2handed = 0;	// Column 18
    int32_t _2handmindam = 0;	// Column 19
    int32_t _2handmaxdam = 0;	// Column 20
    int32_t minmisdam = 0;	// Column 21
    int32_t maxmisdam = 0;	// Column 22
    int32_t rangeadder = 0;	// Column 23
    int32_t speed = 0;	// Column 24
    int32_t StrBonus = 0;	// Column 25
    int32_t DexBonus = 0;	// Column 26
    int32_t reqstr = 0;	// Column 27
    int32_t reqdex = 0;	// Column 28
    int32_t durability = 0;	// Column 29
    int32_t nodurability = 0;	// Column 30
    int32_t level = 0;	// Column 31
    int32_t ShowLevel = 0;	// Column 32
    int32_t levelreq = 0;	// Column 33
    int32_t cost = 0;	// Column 34
    int32_t gamblecost = 0;	// Column 35
    int32_t magiclvl = 0;	// Column 36
    int32_t autoprefix = 0;	// Column 37
    std::string normcode = "";	// Column 38
    std::string ubercode = "";	// Column 39
    std::string ultracode = "";	// Column 40
    std::string wclass = "";	// Column 41
    std::string _2handedwclass = "";	// Column 42
    int32_t component = 0;	// Column 43
    std::string hitclass = "";	// Column 44
    int32_t invwidth = 0;	// Column 45
    int32_t invheight = 0;	// Column 46
    int32_t stackable = 0;	// Column 47
    int32_t minstack = 0;	// Column 48
    int32_t maxstack = 0;	// Column 49
    int32_t spawnstack = 0;	// Column 50
    std::string flippyfile = "";	// Column 51
    std::string invfile = "";	// Column 52
    std::string uniqueinvfile = "";	// Column 53
    std::string setinvfile = "";	// Column 54
    int32_t hasinv = 0;	// Column 55
    int32_t gemsockets = 0;	// Column 56
    int32_t gemapplytype = 0;	// Column 57
    std::string comment = "";	// Column 58
    int32_t useable = 0;	// Column 59
    std::string dropsound = "";	// Column 60
    int32_t dropsfxframe = 0;	// Column 61
    std::string usesound = "";	// Column 62
    int32_t unique = 0;	// Column 63
    int32_t transparent = 0;	// Column 64
    int32_t transtbl = 0;	// Column 65
    int32_t quivered = 0;	// Column 66
    int32_t lightradius = 0;	// Column 67
    int32_t belt = 0;	// Column 68
    int32_t quest = 0;	// Column 69
    int32_t questdiffcheck = 0;	// Column 70
    int32_t missiletype = 0;	// Column 71
    int32_t durwarning = 0;	// Column 72
    int32_t qntwarning = 0;	// Column 73
    int32_t gemoffset = 0;	// Column 74
    int32_t bitfield1 = 0;	// Column 75
    int32_t CharsiMin = 0;	// Column 76
    int32_t CharsiMax = 0;	// Column 77
    int32_t CharsiMagicMin = 0;	// Column 78
    int32_t CharsiMagicMax = 0;	// Column 79
    int32_t CharsiMagicLvl = 0;	// Column 80
    int32_t GheedMin = 0;	// Column 81
    int32_t GheedMax = 0;	// Column 82
    int32_t GheedMagicMin = 0;	// Column 83
    int32_t GheedMagicMax = 0;	// Column 84
    int32_t GheedMagicLvl = 0;	// Column 85
    int32_t AkaraMin = 0;	// Column 86
    int32_t AkaraMax = 0;	// Column 87
    int32_t AkaraMagicMin = 0;	// Column 88
    int32_t AkaraMagicMax = 0;	// Column 89
    int32_t AkaraMagicLvl = 0;	// Column 90
    int32_t FaraMin = 0;	// Column 91
    int32_t FaraMax = 0;	// Column 92
    int32_t FaraMagicMin = 0;	// Column 93
    int32_t FaraMagicMax = 0;	// Column 94
    int32_t FaraMagicLvl = 0;	// Column 95
    // Unused column: LysanderMin
    // Unused column: LysanderMax
    // Unused column: LysanderMagicMin
    // Unused column: LysanderMagicMax
    int32_t LysanderMagicLvl = 0;	// Column 100
    int32_t DrognanMin = 0;	// Column 101
    int32_t DrognanMax = 0;	// Column 102
    int32_t DrognanMagicMin = 0;	// Column 103
    int32_t DrognanMagicMax = 0;	// Column 104
    int32_t DrognanMagicLvl = 0;	// Column 105
    int32_t HratliMin = 0;	// Column 106
    int32_t HratliMax = 0;	// Column 107
    int32_t HratliMagicMin = 0;	// Column 108
    int32_t HratliMagicMax = 0;	// Column 109
    int32_t HratliMagicLvl = 0;	// Column 110
    // Unused column: AlkorMin
    // Unused column: AlkorMax
    // Unused column: AlkorMagicMin
    // Unused column: AlkorMagicMax
    int32_t AlkorMagicLvl = 0;	// Column 115
    int32_t OrmusMin = 0;	// Column 116
    int32_t OrmusMax = 0;	// Column 117
    int32_t OrmusMagicMin = 0;	// Column 118
    int32_t OrmusMagicMax = 0;	// Column 119
    int32_t OrmusMagicLvl = 0;	// Column 120
    int32_t ElzixMin = 0;	// Column 121
    int32_t ElzixMax = 0;	// Column 122
    int32_t ElzixMagicMin = 0;	// Column 123
    int32_t ElzixMagicMax = 0;	// Column 124
    int32_t ElzixMagicLvl = 0;	// Column 125
    int32_t AshearaMin = 0;	// Column 126
    int32_t AshearaMax = 0;	// Column 127
    int32_t AshearaMagicMin = 0;	// Column 128
    int32_t AshearaMagicMax = 0;	// Column 129
    int32_t AshearaMagicLvl = 0;	// Column 130
    int32_t CainMin = 0;	// Column 131
    int32_t CainMax = 0;	// Column 132
    int32_t CainMagicMin = 0;	// Column 133
    int32_t CainMagicMax = 0;	// Column 134
    int32_t CainMagicLvl = 0;	// Column 135
    int32_t HalbuMin = 0;	// Column 136
    int32_t HalbuMax = 0;	// Column 137
    int32_t HalbuMagicMin = 0;	// Column 138
    int32_t HalbuMagicMax = 0;	// Column 139
    int32_t HalbuMagicLvl = 0;	// Column 140
    int32_t JamellaMin = 0;	// Column 141
    int32_t JamellaMax = 0;	// Column 142
    int32_t JamellaMagicMin = 0;	// Column 143
    int32_t JamellaMagicMax = 0;	// Column 144
    int32_t JamellaMagicLvl = 0;	// Column 145
    int32_t LarzukMin = 0;	// Column 146
    int32_t LarzukMax = 0;	// Column 147
    int32_t LarzukMagicMin = 0;	// Column 148
    int32_t LarzukMagicMax = 0;	// Column 149
    int32_t LarzukMagicLvl = 0;	// Column 150
    int32_t AnyaMin = 0;	// Column 151
    int32_t AnyaMax = 0;	// Column 152
    int32_t AnyaMagicMin = 0;	// Column 153
    int32_t AnyaMagicMax = 0;	// Column 154
    int32_t AnyaMagicLvl = 0;	// Column 155
    int32_t MalahMin = 0;	// Column 156
    int32_t MalahMax = 0;	// Column 157
    int32_t MalahMagicMin = 0;	// Column 158
    int32_t MalahMagicMax = 0;	// Column 159
    int32_t MalahMagicLvl = 0;	// Column 160
    int32_t Transform = 0;	// Column 161
    int32_t InvTrans = 0;	// Column 162
    int32_t SkipName = 0;	// Column 163
    std::string NightmareUpgrade = "";	// Column 164
    std::string HellUpgrade = "";	// Column 165
    int32_t Nameable = 0;	// Column 166
    int32_t PermStoreItem = 0;	// Column 167
    // Unused column: UICatOverride
    // Unused column: diablocloneweight

    size_t read(const char* line);
    static std::vector<t_weapons> readfile(std::string filename);
  };

}
