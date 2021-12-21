import os
import dataclasses
import json
import itertools
import re

outdir="output"

@dataclasses.dataclass
class CodesRef:
    name: str = None
    #code: str = None
    display_name: str = None
    #type: str = None
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class PropString:
    #name: str = None
    pos: str = None
    neg: str = None
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class Item:
    code: str = None # 3 digit code
    type: str = None # lookup [code] from item_types
    display_name: str = None # lookup [code] -> strings
    uniques: list[str] = None
    sets: list[str] = None

@dataclasses.dataclass
class ItemBase(Item):
    item_class: str = None # computed from ["normcode", etc.]
    quality: str = None # normal for base item
    reqstr: int = 0
    durability: int = None
    level: int = 0
    levelreq: int = 0
    gemsockets: int = 0

@dataclasses.dataclass
class ItemArmor(ItemBase): # name = "Grand Crown" -> convert
    defense: list[int] = None
    def __getitem__(self, key):
        return super().__getattribute__(key)

@dataclasses.dataclass
class ItemWeapon(ItemBase):
    damage: list[list[int]] = None
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
class ItemType:
    #id: int = None
    #aliases: list[str] = None
    code: str = None
    display_name: str = None
    items: list[str] = None
    category: str = None
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

        with open("../json/armor.json", "r",encoding = 'utf-8') as f:
            self.f_armor = json.load((f))
        with open("../json/gems.json", "r",encoding = 'utf-8') as f:
            self.f_gems = json.load((f))
        with open("../json/ItemTypes.json", "r",encoding = 'utf-8') as f:
            self.f_item_types = json.load((f))
        with open("../json/misc.json", "r",encoding = 'utf-8') as f:
            self.f_misc = json.load((f))
        with open("../json/properties.json", "r",encoding = 'utf-8') as f:
            self.f_properties = json.load((f))
        with open("../json/weapons.json", "r",encoding = 'utf-8') as f:
            self.f_weapons = json.load((f))
        with open("../json/SetItems.json", "r",encoding = 'utf-8') as f:
            self.f_set_items = json.load((f))
        with open("../json/sets.json", "r",encoding = 'utf-8') as f:
            self.f_sets = json.load((f))
        with open("../json/UniqueItems.json", "r",encoding = 'utf-8') as f:
            self.f_unique_items = json.load((f))
        with open("../json/LocaleStringsEn.json", "r",encoding = 'utf-8') as f:
            self.f_strings = json.load((f))
        with open("../json/ItemStatCost.json", "r",encoding = 'utf-8') as f:
            self.f_stats = json.load((f))

        # with open("NTItemAlias.ntl.cpp", "r",encoding = 'utf-8') as f:
        #     self.f_nit = f.readlines()

        # NEED TO PATCH "SAPHIRE"

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

if __name__ == "__main__":

    item_parser = ItemParser()

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
                code = file[key]["code"] if "code" in file[key] else key
                obj.display_name = item_parser.f_strings[key]
                obj.name = item_parser.full_to_short(obj.display_name)
                #obj.type = file[key]["type"] if "type" in file[key] else None
                #print(obj)
                if code not in ref_codes:
                    ref_codes[code] = obj
    # add item types to this reference
    file = item_parser.f_item_types
    for key in file:
        obj = CodesRef()
        code = file[key]["Code"]
        obj.display_name = file[key]["ItemType"]
        obj.name = item_parser.full_to_short(obj.display_name)
        if code not in ref_codes:
            ref_codes[code] = obj
    # add unique items to this reference
    file = item_parser.f_unique_items
    for key in file:
        try:
            obj = CodesRef()
            code = file[key]["index"]
            obj.display_name = item_parser.f_strings[code]
            obj.name = item_parser.full_to_short(obj.display_name)
            if code not in ref_codes:
                ref_codes[code] = obj
        except:
            #print(f"failed on uniq {key}")
            pass
    with open('output/ref_codes.json', 'w', encoding='utf-8') as f:
        json.dump(ref_codes, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # construct reference to get item strings corresponding to properties
    ref_property_strings={}
    for key in item_parser.f_stats:
        if "descstrpos" in item_parser.f_stats[key]:
            obj = PropString()
            #obj.name = key
            descrPos=item_parser.f_stats[key]["descstrpos"]
            descrNeg=item_parser.f_stats[key]["descstrneg"]
            obj.pos=item_parser.f_strings[descrPos]
            obj.neg=item_parser.f_strings[descrNeg]
            #print(f"{key}: {descrPosStr}, {descrNegStr}")
            ref_property_strings[key] = obj
    with open('output/ref_property_strings.json', 'w', encoding='utf-8') as f:
        json.dump(ref_property_strings, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # create types file
    types={}
    for key in item_parser.f_item_types:
        obj = ItemType()
        obj.display_name = ref_codes[key].display_name
        name = ref_codes[key].name
        obj.code = key
        try:
            cat = item_parser.f_item_types[obj.code]["StorePage"]
            obj.category = ref_codes[cat].name
        except: pass
        obj.items=[]
        for file in [item_parser.f_armor, item_parser.f_misc, item_parser.f_weapons, item_parser.f_gems]:
            for key2 in file.keys():
                if key2 in ref_codes:
                    for typ_no in [ "type", "type2" ]:
                        if typ_no in file[key2] and file[key2][typ_no] == obj.code and ref_codes[key2] not in obj.items:
                            obj.items.append(ref_codes[key2].name)
        obj.items = None if obj.items==[] else obj.items
        types[name] = obj
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
        name = ref_codes[key]["name"]
        try: obj.display_name = ref_codes[key]["display_name"]
        except: pass

        damage = []
        if "1or2handed" in item_parser.f_weapons[key]:
            obj.hands="both"
            try:
                damage.append([int(file[key]["mindam"]), int(file[key]["maxdam"])])
                damage.append([int(file[key]["2handmindam"]), int(file[key]["2handmaxdam"])])
            except: pass
        else:
            if "2handed" in file[key]:
                obj.hands = "two"
                try: damage.append([int(file[key]["2handmindam"]), int(file[key]["2handmaxdam"])])
                except: pass
            else:
                obj.hands = "one"
                try: damage.append([int(file[key]["mindam"]), int(file[key]["maxdam"])])
                except: pass
        obj.damage = None if damage==[] else damage

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

        weapons[name] = obj
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
        name = ref_codes[key]["name"]
        try: obj.display_name = ref_codes[key]["display_name"]
        except: pass

        if "minac" in item_parser.f_armor[key]:
            try: obj.defense = ([int(file[key]["minac"]), int(file[key]["maxac"])])
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

        armor[name] = obj
        #print(armor[name])
    with open('output/item_armor.json', 'w', encoding='utf-8') as f:
        json.dump(armor, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # create misc file
    misc={}
    file = item_parser.f_misc
    for key in file:
        obj = ItemMisc()
        obj.code = key
        try: name = ref_codes[key]["name"]
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

        misc[name] = obj
        #print(misc[name])
    with open('output/item_misc.json', 'w', encoding='utf-8') as f:
        json.dump(misc, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder, indent=2)

    # create sets file



    # create uniques file