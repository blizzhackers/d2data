import os
import dataclasses
import json
import itertools
import re
import parse


outdir="output"

@dataclasses.dataclass
class PropertyBase():
    code: str = None
    #code_clean: str = None
    aliases: list = dataclasses.field(default_factory=list)
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class ItemProperty():
    min: int = None
    max: int = None
    par: str = None
    prop: str = None
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class PropertyDef(PropertyBase):
    within: list = dataclasses.field(default_factory=list)
    children: list = dataclasses.field(default_factory=list)
    patterns: list = dataclasses.field(default_factory=list)
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class CodesRef:
    name: str = None
    display_name: str = None
    code: str = None
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class Item(CodesRef):
    type: str = None # lookup [code] from item_types
    uniques: list[str] = None
    sets: list[str] = None

@dataclasses.dataclass
class PropString:
    pos_code: str = None
    neg_code: str = None
    pos_str: str = None
    neg_str: str = None
    second_code: str = None
    second_str: str = None
    descval: int = 0
    descfunc: int = None
    pos_pattern: str = None
    neg_pattern: str = None
    dgrp: int = None
    dgrpfunc: int = None
    dgrpstrpos: str = None
    dgrpstrneg: str = None
    code: str = None
    par_pos: int = None

@dataclasses.dataclass
class ItemBase(Item):
    item_class: str = None # computed from ["normcode", etc.]
    quality: str = None # normal for base item
    reqstr: int = 0
    durability: int = None
    level: int = 0
    levelreq: int = 0
    gemsockets: int = 0
    props: list[ItemProperty] = None

@dataclasses.dataclass
class ItemArmor(ItemBase): # name = "Grand Crown" -> convert
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class ItemWeapon(ItemBase):
    hands: str = None
    range: int = 0
    speed: int = 0
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class ItemMisc(Item):
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class ItemType(CodesRef):
    items: list[str] = None
    category: str = None
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class SpecialItem(CodesRef):
    base: str = None
    level: int = 0
    levelreq: int = 0
    props: list[ItemProperty] = None

@dataclasses.dataclass
class SetItem(SpecialItem):
    set: str = None
    def __getitem__(self, key):
        return super().__getattribute__(key)


class EnhancedJSONEncoder(json.JSONEncoder):
        def default(self, o):
            if dataclasses.is_dataclass(o):
                return dataclasses.asdict(o)
            return super().default(o)

class ItemParser:
    def __init__(self):

        # NTITemAlias lines. third item in list is line number where the nit linenumber needs +1
        self.lines_type = [3, 103, 59]
        self.lines_name_short = [106, 765]
        self.lines_class = [767, 769]
        self.lines_quality = [772, 779]
        self.lines_flag = [782, 784]
        self.lines_properties = [787, 1422]
        self.lines_display_name = [1425, 2083]

        self.item_classes = ["normcode", "ubercode", "ultracode"]
        self.item_classes_names = [ "normal", "exceptional", "elite"]

        self.classes = [ "Amazon", "Sorceress", "Assassin", "Paladin", "Druid", "Barbarian", "Necromancer" ]
        self.classes_short = [ "ama", "sor", "ass", "pal", "dru", "bar", "nec" ]

        self.clean_prop_strings = [
            { "o": re.escape('%'), "r": '-percent' },
            { "o": re.escape('/lvl'), "r": '-perlevel' },
            { "o": re.escape('/time'), "r": '-bytime' }
        ]
        self.string_spec_repl = [
            { "o": re.escape('%d%'), "r": '{:d}' },
            { "o": re.escape('%d'), "r": '{:d}' },
            { "o": re.escape('%s%'), "r": '{}' },
            { "o": re.escape('%s'), "r": '{}' }
        ]

        with open("../json/armor.json", "r",encoding = 'utf-8') as f:
            self.f_armor = json.load(f)
        with open("../json/gems.json", "r",encoding = 'utf-8') as f:
            self.f_gems = json.load(f)
        with open("../json/ItemTypes.json", "r",encoding = 'utf-8') as f:
            self.f_item_types = json.load(f)
        with open("../json/misc.json", "r",encoding = 'utf-8') as f:
            self.f_misc = json.load(f)
        with open("../json/properties.json", "r",encoding = 'utf-8') as f:
            self.f_properties = json.load(f)
        with open("../json/weapons.json", "r",encoding = 'utf-8') as f:
            self.f_weapons = json.load(f)
        with open("../json/SetItems.json", "r",encoding = 'utf-8') as f:
            self.f_set_items = json.load(f)
        with open("../json/sets.json", "r",encoding = 'utf-8') as f:
            self.f_sets = json.load(f)
        with open("../json/UniqueItems.json", "r",encoding = 'utf-8') as f:
            self.f_unique_items = json.load(f)
        with open("../json/LocaleStringsEn.json", "r",encoding = 'utf-8') as f:
            self.f_strings = json.load(f)
        with open("../json/ItemStatCost.json", "r",encoding = 'utf-8') as f:
            self.f_stats = json.load(f)
        with open("../json/skills.json", "r",encoding = 'utf-8') as f:
            self.f_skills = json.load(f)

        # with open("NTItemAlias.ntl.cpp", "r",encoding = 'utf-8') as f:
        #     self.f_nit = f.readlines()

        # NEED TO PATCH "SAPHIRE"?

    def gen_from_descval(self, param_in: str = None, str_in: str = None, descval: int = None):
        # descval
        # 0 = no stat
        # 1 = stat before description
        # 2 = stat after
        if not descval:
            return str_in
        elif descval == 1:
            return param_in + " " + str_in
        elif descval == 2:
            return str_in + " " + param_in
        return None

    def string_spec(self, string_obj: PropString = None):
        # descfunc:
        # 1. "+{:d} to Mana after each Kill"
        # 2. "{:d}% life stolen per hit"
        # 3.  "magic damage reduced by {:d}"
        # 4. "magic resist +{:d}%"
        # 5. "hit causes monster to flee {:d}%"
        # 6. "+{:d} to Life (Based on Character Level)"
        # 7. "{:d}% chance of open wounds (Based on Character Level)"
        # 8. "heal stamina plus {:d}% (based on character level)"
        # 9. "attacker takes damage of {:d} (based on character level)"
        # 11. "Repairs %d durability per second"
        # 12. "hit blinds target +{:d}"
        # 13. "+{:d} to {} skill levels"
        # 14. "+{:d} to {} ({} only)"
        # 15. "{:d}% chance to cast level {:d} {} on attack"
        # 16. "level {:d} {} aura when equipped"
        # 17. "+{:d} to attack rating against undead"
        # 18. "+{:d} Absorbs Cold Damage"
        # 19. this is a special sprintf blizzard function, only used in one case, so manually ent
        #     "All Resistances +%d"
        # 20. "-{:d}% target defense"
        # 22. "+{:d} to Attack Rating versus {}"
        # 23. "{:d}% reanimate as: {}"
        # 24. "level {:d} {} ({:d}/{:d} charges)"
        # 27. "+{:d} to {} ({} only)"
        # 28. "+{:d} to {}"

        try: string_obj.second_str = self.f_strings[string_obj.second_code]
        except: pass
        try: string_obj.pos_str = self.f_strings[string_obj.pos_code]
        except: pass
        try: string_obj.neg_str = self.f_strings[string_obj.neg_code]
        except: pass

        if string_obj.pos_code:
            for i in self.string_spec_repl:
                string_obj.pos_str = string_obj.pos_str.replace(i['o'], i['r'])
                string_obj.neg_str = string_obj.neg_str.replace(i['o'], i['r'])

        if string_obj.descfunc == 0:
            pass
        elif string_obj.descfunc in [1, 6, 12, 17, 18]:
            string_obj.pos_pattern = self.gen_from_descval("+{:d}", string_obj.pos_str, string_obj.descval)
            string_obj.neg_pattern = self.gen_from_descval("-{:d}", string_obj.neg_str, string_obj.descval)
        elif string_obj.descfunc in [2, 5, 7, 8]:
            string_obj.pos_pattern = self.gen_from_descval("{:d}%", string_obj.pos_str, string_obj.descval)
            string_obj.neg_pattern = self.gen_from_descval("{:d}%", string_obj.neg_str, string_obj.descval)
        elif string_obj.descfunc in [3, 9]:
            string_obj.pos_pattern = self.gen_from_descval("{:d}", string_obj.pos_str, string_obj.descval)
            string_obj.neg_pattern = self.gen_from_descval("{:d}", string_obj.neg_str, string_obj.descval)
        elif string_obj.descfunc in [4, 20]:
            string_obj.pos_pattern = self.gen_from_descval("+{:d}%", string_obj.pos_str, string_obj.descval)
            string_obj.neg_pattern = self.gen_from_descval("-{:d}%", string_obj.neg_str, string_obj.descval)
        elif string_obj.descfunc in [11, 15, 16, 19]:
            string_obj.pos_pattern = string_obj.pos_str
            string_obj.neg_pattern = string_obj.neg_str
        elif string_obj.descfunc in [13]:
            repl="{}"
            for count, i in enumerate(self.classes_short):
                if string_obj.code == i:
                    repl = self.classes[count]
            for i in self.classes:
                string_obj.pos_str = string_obj.pos_str.replace(i, repl)
                string_obj.neg_str = string_obj.neg_str.replace(i, repl)
            string_obj.pos_pattern = self.gen_from_descval("+{:d}", string_obj.pos_str, string_obj.descval)
            string_obj.neg_pattern = self.gen_from_descval("-{:d}", string_obj.neg_str, string_obj.descval)
        elif string_obj.descfunc in [14]:
            string_obj.pos_pattern = "+{:d} to {} ({} only)"
            string_obj.neg_pattern = "-{:d} to {} ({} only)"
        elif string_obj.descfunc in [22]:
            string_obj.pos_pattern = "+{:d} to Attack Rating versus {}"
            string_obj.neg_pattern = "-{:d} to Attack Rating versus {}"
        elif string_obj.descfunc in [23]:
            string_obj.pos_pattern = string_obj.neg_pattern = "{:d}% Reanimate as: {}"
        elif string_obj.descfunc in [24]:
            string_obj.pos_pattern = string_obj.neg_pattern = "Level {:d} {} ({:d}/{:d} Charges)"
        elif string_obj.descfunc in [27]:
            string_obj.pos_pattern = string_obj.neg_pattern = "+{:d} to {} ({} only)"
        elif string_obj.descfunc in [28]:
            string_obj.pos_pattern = string_obj.neg_pattern = "+{:d} to {}"
        else:
            print("fail")

        # add based on character level
        # if string_obj.descfunc in [6, 7, 8, 9]:
        if string_obj.second_code:
            string_obj.pos_pattern = string_obj.pos_pattern + " " + string_obj.second_str
            string_obj.neg_pattern = string_obj.neg_pattern + " " + string_obj.second_str

        return string_obj

    def parse_line(self, line: str = None):
        aliases = re.findall(r'"(.*?)"', line)
        values = re.findall(r'=([0-9]*?);', line)
        return aliases, values

    def find_by_line_number(self, name: str = None, dic: dict = None, nit_line: int = None):
        for key in dic.keys():
            #print(dic[key])
            if int(dic[key]["lineNumber"]) == nit_line:
                return key
        return None

    def full_to_short(self, full_name: str = None):
        return re.sub('[^A-Za-z0-9 ]+', '', full_name).replace(' ','_').lower()

    def clean_prop_code(self, code: str = None):
        for i in self.clean_prop_strings:
            #print(i)
            code = code.replace(i['o'], i['r'])
        return code

    def conv_statname_propname(self, alias: str = None):
        for key in self.f_properties:
            if "stat1" in self.f_properties[key] and "stat2" not in self.f_properties[key] and self.f_properties[key]["stat1"] == alias:
                return key
        return False

    def get_magic_props(self, item: dict):
        props = []
        for i in range(1,31):
            key = "prop" + str(i)
            obj = ItemProperty()
            try:
                obj.prop = item[key]
            except:
                break
            par_key = "par" + str(i)
            min_key = "min" + str(i)
            max_key = "max" + str(i)
            try: obj.par = int(item[par_key])
            except: pass
            try: obj.min = int(item[min_key])
            except: pass
            try: obj.max = int(item[max_key])
            except: pass
            props.append(obj)
        props = None if props == [] else props
        return props

if __name__ == "__main__":

    item_parser = ItemParser()

    f_properties = item_parser.f_properties
    f_stats = item_parser.f_stats
    f_strings = item_parser.f_strings
    f_skills = item_parser.f_skills

    # str = "+3 to Cold Skills (Sorceress only)"
    # print(str)
    # form="+{:d} to {} ({} only)"
    # print(parse.search(form,str))

    # create reference of names/codes/etc from LocaleStringsEn.json
    ref_codes={}
    itemFiles = [
        item_parser.f_armor,
        item_parser.f_misc,
        item_parser.f_weapons,
        item_parser.f_gems,
        item_parser.f_sets,
        item_parser.f_set_items,
    ]
    for key in item_parser.f_strings:
        for file in itemFiles:
            if key in file:
                obj = CodesRef()
                obj.code = file[key]["code"] if "code" in file[key] else key
                obj.display_name = item_parser.f_strings[key]
                obj.name = item_parser.full_to_short(obj.display_name)
                #obj.type = file[key]["type"] if "type" in file[key] else None
                #print(obj)
                if obj.code not in ref_codes:
                    ref_codes[obj.code] = obj
    # add item types to this reference
    file = item_parser.f_item_types
    for key in file:
        obj = CodesRef()
        obj.code = file[key]["Code"]
        obj.display_name = file[key]["ItemType"]
        obj.name = item_parser.full_to_short(obj.display_name)
        if obj.code not in ref_codes:
            ref_codes[obj.code] = obj
    # add unique items to this reference
    file = item_parser.f_unique_items
    for key in file:
        try:
            obj = CodesRef()
            obj.code = file[key]["index"]
            obj.display_name = item_parser.f_strings[obj.code]
            obj.name = item_parser.full_to_short(obj.display_name)
            if obj.code not in ref_codes:
                ref_codes[obj.code] = obj
        except:
            #print(f"failed on uniq {key}")
            pass
    with open('output/ref_codes.json', 'w', encoding='utf-8') as f:
        json.dump(ref_codes, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)


    # construct properties file
    properties={}
    within={}
    for key in f_properties:
        obj = PropertyDef()
        obj.code = key
        if "stat2" in f_properties[key]:

            for i in range(1,31):
                stat = "stat" + str(i)
                if stat in f_properties[key]:
                    alias = f_properties[key][stat]
                    sub_code = item_parser.conv_statname_propname(alias)
                    if sub_code:
                        obj.children.append(sub_code)
                        if sub_code in within:
                            within[sub_code].append(key)
                        else:
                            within[sub_code] = [key]
            obj.aliases = None
        properties[obj.code]=obj
    for key in f_properties:
        if "stat2" not in f_properties[key]:
            obj = PropertyDef()
            obj.code = key
            strings = PropString()
            for key2 in f_stats:
                if "stat1" in f_properties[key] and key2 == f_properties[key]["stat1"]:
                    obj.aliases.append(key2)
                    break
            #obj.aliases = None if obj.aliases == [] else obj.aliases
            try: strings.descfunc = f_stats[obj.aliases[0]]["descfunc"]
            except: pass
            try: strings.descval = f_stats[obj.aliases[0]]["descval"]
            except: pass
            try: strings.pos_code = f_stats[obj.aliases[0]]["descstrpos"]
            except: pass
            try: strings.neg_code = f_stats[obj.aliases[0]]["descstrneg"]
            except: pass
            try: strings.second_code = f_stats[obj.aliases[0]]["descstr2"]
            except: pass
            try: strings.code = obj.code
            except: pass

            if strings.descfunc:
                strings = item_parser.string_spec(strings)
            if strings.pos_pattern:
                obj.patterns.append({
                    "pos": strings.pos_pattern,
                    "neg": strings.neg_pattern,
                    "par_pos": strings.par_pos })

        properties[obj.code]=obj
    for key in f_stats:
        if "dgrpstrpos" in f_stats[key]:
            strings = PropString()
            alias = key

            try: strings.descfunc = f_stats[key]["dgrpfunc"]
            except: pass
            try: strings.descval = f_stats[key]["dgrp"]
            except: pass
            try: strings.pos_code = f_stats[key]["dgrpstrpos"]
            except: pass
            try: strings.neg_code = f_stats[key]["dgrpstrneg"]
            except: pass
            if strings.descfunc:
                strings = item_parser.string_spec(strings)

            code = item_parser.conv_statname_propname(alias)
            if code:
                for key2 in properties:
                    if code in properties[key2]["children"]:
                        group_code = key2
                        break
                if strings.pos_pattern:
                    val = { "pos": strings.pos_pattern, "neg": strings.neg_pattern }
                    if val not in properties[group_code]["patterns"]:
                        properties[group_code]["patterns"].append(val)
    for key in properties:
        if len(properties[key]["children"]) > 1 and not properties[key]["patterns"]:
            for x in properties[key]["children"]:
                try:
                    pattern = properties[x]["patterns"][0]
                    properties[key]["patterns"].append(pattern)
                except: pass

    with open('output/item_properties.json', 'w', encoding='utf-8') as f:
        json.dump(properties, f, ensure_ascii=False, sort_keys=True, cls=EnhancedJSONEncoder, indent=2)

    # create types file
    types={}
    for key in item_parser.f_item_types:
        obj = ItemType()
        obj.display_name = ref_codes[key]["display_name"]
        obj.name = ref_codes[key]["name"]
        obj.code = key
        try:
            cat = item_parser.f_item_types[obj.code]["StorePage"]
            obj.category = ref_codes[cat]["name"]
        except: pass
        obj.items=[]
        for file in [item_parser.f_armor, item_parser.f_misc, item_parser.f_weapons, item_parser.f_gems]:
            for key2 in file.keys():
                if key2 in ref_codes:
                    for typ_no in [ "type", "type2" ]:
                        if typ_no in file[key2] and file[key2][typ_no] == obj.code and ref_codes[key2] not in obj.items:
                            obj.items.append(ref_codes[key2].name)
        obj.items = None if obj.items==[] else obj.items
        types[obj.name] = obj
        #print(types[name])
    with open('output/item_types.json', 'w', encoding='utf-8') as f:
        json.dump(types, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # create weapons file
    weapons={}
    file = item_parser.f_weapons
    for key in file:
        obj = ItemWeapon()
        obj.code = key
        obj.quality = "normal"
        obj.name = ref_codes[key]["name"]
        try: obj.display_name = ref_codes[key]["display_name"]
        except: pass

        props = []
        if "1or2handed" in item_parser.f_weapons[key]:
            obj.hands="both"
            try:
                prop_obj = ItemProperty()
                prop_obj.prop = "base_damage_1hand"
                prop_obj.min = int(file[key]["mindam"])
                prop_obj.max = int(file[key]["maxdam"])
                props.append(prop_obj)
                prop_obj = ItemProperty()
                prop_obj.prop = "base_damage_2hand"
                prop_obj.min = int(file[key]["2handmindam"])
                prop_obj.max = int(file[key]["2handmaxdam"])
                props.append(prop_obj)
            except: pass
        else:
            if "2handed" in file[key]:
                obj.hands = "two"
                try:
                    prop_obj = ItemProperty()
                    prop_obj.prop = "base_damage_2hand"
                    prop_obj.min = int(file[key]["2handmindam"])
                    prop_obj.max = int(file[key]["2handmaxdam"])
                    props.append(prop_obj)
                except: pass
            else:
                obj.hands = "one"
                try:
                    prop_obj = ItemProperty()
                    prop_obj.prop = "base_damage_1hand"
                    prop_obj.min = int(file[key]["mindam"])
                    prop_obj.max = int(file[key]["maxdam"])
                    props.append(prop_obj)
                except: pass
        obj.props = None if props==[] else props

        try: obj.range = int(file[key]["rangeadder"])
        except: pass
        try: obj.speed = int(file[key]["speed"])
        except: pass
        try: obj.reqstr = int(file[key]["reqstr"])
        except: pass
        try: obj.durability = int(file[key]["durability"])
        except: pass
        try: obj.level = int(file[key]["level"])
        except: pass
        try: obj.levelreq = int(file[key]["levelreq"])
        except: pass
        try: obj.gemsockets = int(file[key]["gemsockets"])
        except: pass

        for key2 in types:
            if types[key2]["code"] == file[key]["type"]:
                obj.type = key2
                break

        for count,class_name in enumerate(item_parser.item_classes):
            if class_name in file[key] and file[key][class_name] == obj.code:
                obj.item_class = item_parser.item_classes_names[count]
                break

        obj.sets = []
        for key2 in item_parser.f_set_items:
            item_code=item_parser.f_set_items[key2]["item"]
            if item_code == obj.code:
                obj.sets.append(ref_codes[key2]["name"])
        obj.sets = None if obj.sets==[] else obj.sets

        obj.uniques = []
        for key2 in item_parser.f_unique_items:
            try:
                item_code=item_parser.f_unique_items[key2]["code"]
                item_index=item_parser.f_unique_items[key2]["index"]
                if item_code == obj.code:
                    obj.uniques.append(ref_codes[item_index]["name"])
            except: pass
        obj.uniques = None if obj.uniques==[] else obj.uniques

        weapons[obj.name] = obj
        #print(weapons[name])
    with open('output/item_weapons.json', 'w', encoding='utf-8') as f:
        json.dump(weapons, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # create armor file
    armor={}
    file = item_parser.f_armor
    for key in file:
        obj = ItemArmor()
        obj.code = key
        obj.quality = "normal"
        obj.name = ref_codes[key]["name"]
        try: obj.display_name = ref_codes[key]["display_name"]
        except: pass

        if "minac" in item_parser.f_armor[key]:
            try:
                prop_obj = ItemProperty()
                prop_obj.prop = "base_defense"
                prop_obj.min = int(file[key]["minac"])
                prop_obj.max = int(file[key]["maxac"])
                obj.props = [prop_obj]
            except: pass

        try: obj.reqstr = int(file[key]["reqstr"])
        except: pass
        try: obj.durability = int(file[key]["durability"])
        except: pass
        try: obj.level = int(file[key]["level"])
        except: pass
        try: obj.levelreq = int(file[key]["levelreq"])
        except: pass
        try: obj.gemsockets = int(file[key]["gemsockets"])
        except: pass

        for key2 in types:
            if types[key2]["code"] == file[key]["type"]:
                obj.type = key2
                break

        for count,class_name in enumerate(item_parser.item_classes):
            if class_name in file[key] and file[key][class_name] == obj.code:
                obj.item_class = item_parser.item_classes_names[count]
                break

        obj.sets = []
        for key2 in item_parser.f_set_items:
            item_code=item_parser.f_set_items[key2]["item"]
            if item_code == obj.code:
                obj.sets.append(ref_codes[key2]["name"])
        obj.sets = None if obj.sets==[] else obj.sets

        obj.uniques = []
        for key2 in item_parser.f_unique_items:
            try:
                item_code=item_parser.f_unique_items[key2]["code"]
                item_index=item_parser.f_unique_items[key2]["index"]
                if item_code == obj.code:
                    obj.uniques.append(ref_codes[item_index]["name"])
            except: pass
        obj.uniques = None if obj.uniques==[] else obj.uniques

        armor[obj.name] = obj
        #print(armor[name])
    with open('output/item_armor.json', 'w', encoding='utf-8') as f:
        json.dump(armor, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # create misc file
    misc={}
    file = item_parser.f_misc
    for key in file:
        obj = ItemMisc()
        obj.code = key
        try: obj.name = ref_codes[key]["name"]
        except: continue
        try: obj.display_name = ref_codes[key]["display_name"]
        except: pass

        for key2 in types:
            if types[key2]["code"] == file[key]["type"]:
                obj.type = key2
                break

        obj.sets = []
        for key2 in item_parser.f_set_items:
            item_code=item_parser.f_set_items[key2]["item"]
            if item_code == obj.code:
                obj.sets.append(ref_codes[key2]["name"])
        obj.sets = None if obj.sets==[] else obj.sets

        obj.uniques = []
        for key2 in item_parser.f_unique_items:
            try:
                item_code=item_parser.f_unique_items[key2]["code"]
                item_index=item_parser.f_unique_items[key2]["index"]
                if item_code == obj.code:
                    obj.uniques.append(ref_codes[item_index]["name"])
            except: pass
        obj.uniques = None if obj.uniques==[] else obj.uniques

        misc[obj.name] = obj
        #print(misc[name])
    with open('output/item_misc.json', 'w', encoding='utf-8') as f:
        json.dump(misc, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # create sets file
    set_items={}
    file = item_parser.f_set_items
    for key in file:
        obj = SetItem()
        obj.code = file[key]["item"]
        obj.name = ref_codes[key]["name"]
        obj.display_name = ref_codes[key]["display_name"]
        try: obj.base = ref_codes[obj.code]["name"]
        except: pass
        try: obj.set = file[key]["set"]
        except: pass
        try: obj.level = file[key]["lvl"]
        except: pass
        try: obj.levelreq = file[key]["lvl req"]
        except: pass
        obj.props = item_parser.get_magic_props(file[key])

        set_items[obj.name] = obj
    with open('output/item_set_items.json', 'w', encoding='utf-8') as f:
        json.dump(set_items, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)



    # create uniques file