import os
import dataclasses
import json
import itertools
import re

outdir="output"

@dataclasses.dataclass
class PropString:
    name: str = None
    pos: str = None
    neg: str = None

@dataclasses.dataclass
class ItemArmor:
    regexp: str = None
    base_text: str = None
    prop_name: str = None

@dataclasses.dataclass
class ItemWeapon:
    regexp: str = None
    base_text: str = None
    prop_name: str = None

@dataclasses.dataclass
class ItemMisc:
    regexp: str = None
    base_text: str = None
    prop_name: str = None

@dataclasses.dataclass
class ItemType:
    id: int = None
    name: str = None
    aliases: list[str] = None
    code: str = None
    nit_val: int = None
    description: str = None
    contains: list[str] = None
    category: str = None

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

        with open("NTItemAlias.ntl.cpp", "r",encoding = 'utf-8') as f:
            self.f_nit = f.readlines()

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

if __name__ == "__main__":

    item_parser = ItemParser()

    # construct reference to get item strings corresponding to properties
    property_name_to_string={}
    for key in item_parser.f_stats.keys():
        if "descstrpos" in item_parser.f_stats[key]:
            obj = PropString()
            obj.name = key
            descrPos=item_parser.f_stats[key]["descstrpos"]
            descrNeg=item_parser.f_stats[key]["descstrneg"]
            obj.pos=item_parser.f_strings[descrPos]
            obj.neg=item_parser.f_strings[descrNeg]
            #print(f"{key}: {descrPosStr}, {descrNegStr}")
            property_name_to_string[key] = obj
    with open('output/translate_itemProps.json', 'w', encoding='utf-8') as f:
        json.dump(property_name_to_string, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder)

    # # construct reference to translate 3-char codes to names
    # code_to_name={}
    # line_range=[x-1 for x in item_parser.lines_name_short]
    # for line in itertools.islice(item_parser.f_nit, line_range[0], line_range[1]):
    #     try: aliases, values = item_parser.parse_line(line)
    #     except: continue
    #     code = aliases[0]
    #     name = aliases[-1]
    #     code_to_name[code]=name
    # #print(json.dumps(types, sort_keys=True, cls=EnhancedJSONEncoder))
    # with open('output/translate_codes.json', 'w', encoding='utf-8') as f:
    #     json.dump(code_to_name, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder)

    #start with item types (i.e., sword, auricshields, etc.)
    types={}
    count_id=0
    line_range=[x-1 for x in item_parser.lines_type]
    for count, line in enumerate(itertools.islice(item_parser.f_nit, line_range[0], line_range[1])):
        try: aliases, values = item_parser.parse_line(line)
        except: continue
        obj = ItemType()
        obj.id = count_id
        obj.name = aliases[-1]
        obj.aliases = aliases
        if line_range[2]:
            obj.nit_val = int(values[0]) if count < (line_range[2] - line_range[0]) else int(values[0]) +1
        else:
            obj.nit_val = int(values[0])
        key = item_parser.find_by_line_number(aliases[0], item_parser.f_item_types, obj.nit_val)
        obj.code = key
        try: obj.description = item_parser.f_item_types[key]["ItemType"]
        except: pass
        try: obj.category = item_parser.f_item_types[key]["StorePage"]
        except: pass
        obj.contains=[]
        for file in [item_parser.f_armor, item_parser.f_misc, item_parser.f_weapons, item_parser.f_gems]:
            for key in file.keys():
                if key in item_parser.f_strings:
                    for typ_no in [ "type", "type2" ]:
                        if typ_no in file[key] and file[key][typ_no] == obj.code and item_parser.f_strings[key] not in obj.contains:
                            obj.contains.append(item_parser.f_strings[key])
        obj.contains = None if obj.contains==[] else obj.contains
        types[obj.name] = obj
        count_id += 1
    with open('output/item_types.json', 'w', encoding='utf-8') as f:
        json.dump(types, f, ensure_ascii=False, sort_keys=False, cls=EnhancedJSONEncoder)

#        obj.contains=[]
#        for file in [item_parser.f_armor, item_parser.f_misc, item_parser.f_armor]:
#            for key in file.keys():
#                #print(file[key])
#                if "type" in file[key] and file[key]["type"] == obj.code:
#                    obj.contains.append(file[key]["code"])


#    for filename in ["json/armor.json","json/misc.json","json/weapons.json"]:
#        f = open(filename)
#        data = json.load(f)
#        for key in data:
#            value = data[key]['name']
#            file2.write(f"{value}\n")
#
#
#    file1 = open('myfile.txt', 'r')
#    Lines = file1.readlines()
#
#    count = 0
#    # Strips the newline character
#    for line in Lines:
#        count += 1
#        print("Line{}: {}".format(count, line.strip()))