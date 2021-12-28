import parse
import json

class Test:
    def __init__(self):

        self.drop = { "val": "lacquered plate", "color": "green" }

        self.identified_item = [
            "Tal Rasha's Guardianship",
            "Lacquered Plate",
            "Defense: 925",
            "Durability: 55 of 55",
            "Required Strength: 84",
            "Required Level: 71",
            "+400 Defense",
            "Cold Resist +40%",
            "Lightning Resist +40%",
            "Fire Resist +40%",
            "Magic Damage Reduced by 15",
            "112% Better Chance of Getting Magic Items",
            "Requirements -60%",
            "Socketed (1)"
        ]

        self.quality_to_color = {
            "normal": ["white", "gray"],
            "superior": ["gray"],
            "set": ["green"],
            "unique": ["gold"],
            "magic": ["blue"],
            "special": ["orange"],
            "rare": ["yellow"]
        }

        # to do, orange color support for runes, tokens, keys, essences

        with open("pickit.json", "r",encoding = 'utf-8') as f:
            self.f_pickit = json.loads(json.dumps(json.loads(json.dumps(json.load(f)).lower())).lower())

        with open("../output/item_armor.json", "r",encoding = 'utf-8') as f:
            self.f_armor = json.loads(json.dumps(json.load(f)).lower())
        with open("../output/item_misc.json", "r",encoding = 'utf-8') as f:
            self.f_misc = json.loads(json.dumps(json.load(f)).lower())
        with open("../output/item_weapons.json", "r",encoding = 'utf-8') as f:
            self.f_weapons = json.loads(json.dumps(json.load(f)).lower())

        with open("../output/item_properties.json", "r",encoding = 'utf-8') as f:
            self.f_properties = json.loads(json.dumps(json.load(f)).lower())
        with open("../output/item_types.json", "r",encoding = 'utf-8') as f:
            self.f_types = json.loads(json.dumps(json.load(f)).lower())

        with open("../output/item_set_items.json", "r",encoding = 'utf-8') as f:
            self.f_set_items = json.loads(json.dumps(json.load(f)).lower())
        with open("../output/item_unique_items.json", "r",encoding = 'utf-8') as f:
            self.f_unique_items = json.loads(json.dumps(json.load(f)).lower())

        with open("../output/ref_codes.json", "r",encoding = 'utf-8') as f:
            self.f_ref_codes = json.loads(json.dumps(json.load(f)).lower())

    def all_colors(self):
        colors=[]
        for key in self.quality_to_color:
            for i in self.quality_to_color[key]:
                colors.append(i)
        return list(set(colors))

    def name_to_code(self, inp_str: str, in_type: str = "name", out_type: str = "code"):
        for key in self.f_ref_codes:
            if inp_str == self.f_ref_codes[key][in_type]:
                return self.f_ref_codes[key][out_type]
        return False

    def get_base_name_and_col(self, inp_str: str, inp_type: str):
        #print(f"inp_str: {inp_str}, inp_type: {inp_type}")
        items=[]
        if inp_type == "quality":
            # for "paf" in ref_codes
            for key in self.f_ref_codes:
                #if ref_codes["paf"]["quality"] == "normal"
                if self.f_ref_codes[key]["quality"] == inp_str:
                    # convert "paf" to "name" -> "vortex_shield"
                    # code --> lycanders_aim
                    item_name = self.name_to_code(key, "code", "name")
                    item_display_name = self.name_to_code(key, "code", "display_name")
                    if inp_str == "set":
                        file = self.f_set_items
                    elif inp_str == "unique":
                        file = self.f_unique_items
                    else:
                        items.append(item_display_name)
                        continue
                    if item_name in file:
                        if "base" in file[item_name]:
                            items.append(self.name_to_code(file[item_name]["base"], "name", "display_name"))
            return items, self.quality_to_color[inp_str]
        if inp_type == "type":
            colors=[]
            for key in self.f_ref_codes:
                if self.f_ref_codes[key]["display_name"] == inp_str or self.f_ref_codes[key]["name"] == inp_str:
                    type_name = self.f_ref_codes[key]["name"]
                    break
            for item in self.f_types[type_name]["items"]:
                item_display_name = self.name_to_code(item, "name", "display_name")
                items.append(item_display_name)
                item_code = self.name_to_code(item, "name", "code")
                item_quality = self.f_ref_codes[item_code]["quality"]
                if "special" in item_quality:
                    item_colors = self.quality_to_color[item_quality]
                    for item_color in item_colors:
                        if item_color not in colors:
                            colors.append(item_color)
                else:
                    colors = self.all_colors()
            return items, list(set(colors))
        else:
            item_display_name = self.name_to_code(inp_str, inp_type, "display_name")
            item_code = self.name_to_code(inp_str, inp_type, "code")
            item_name = self.name_to_code(inp_str, inp_type, "name")
            # print(f"disp_name: {item_display_name}, code: {item_code}, name: {item_name}")
            colors = self.quality_to_color[self.f_ref_codes[item_code]["quality"]]
            for file in [ self.f_unique_items, self.f_set_items ]:
                if item_name in file:
                    if "base" in file[item_name]:
                        return [self.name_to_code(file[item_name]["base"], "name", "display_name")], colors
            return [item_display_name], colors
        return False


if __name__ == "__main__":

    test = Test()

    # generate a file containing all the items that should be picked up

    # item and type properties:
    # name (key name): auric_shields, lacquered_plate, tal_rashas_guardianship
    # display_name: Auric Shields, Lacquered Plate, Tal-Rasha's Guardianship
    # type: auric_shields, armor, __
    # base: ___, ____, lacquered_plate
    # item_class: ____. Elite, ____
    # props: [{ "max": 5, "min": 2, "par": 0, "prop": "sock" }, ...]
    # set: "Tal Rasha's Wrappings"
    # hands: one/two/both

    full_drop_list = []
    for item in test.f_pickit["items"]:
        current_drop_list = []
        current_colors = []
    # 1. handle "name"
        if "name" in item:
            base_names, result_colors = test.get_base_name_and_col(item["name"],"name")
            for col in result_colors:
                current_colors.append(col)
            for base_name in base_names:
                current_drop_list.append(base_name)
            #print(f"name {item['name']}: current_drop_list: {current_drop_list}")
            #print(f"name {item['name']}: current_colors: {current_colors}")
    # 2. handle "display_name"
        if "display_name" in item:
            base_names, result_colors = test.get_base_name_and_col(item["display_name"],"display_name")
            if current_drop_list:
                current_drop_list = [x for x in current_drop_list if x in set(base_names)]
                current_colors = [x for x in current_colors if x in set(result_colors)]
            else:
                current_drop_list = base_names
                current_colors = result_colors
            #print(f"display_name {item['display_name']}: sub_list: {base_names}")
            #print(f"display_name {item['display_name']}: sub_colors: {result_colors}")
            #print(f"display_name {item['display_name']}: current_drop_list: {current_drop_list}")
            #print(f"display_name {item['display_name']}: current_colors: {current_colors}")
    # 3. handle "type"
        if "type" in item:
            base_names, result_colors = test.get_base_name_and_col(item["type"],"type")
            if current_drop_list:
                current_drop_list = [x for x in current_drop_list if x in set(base_names)]
                current_colors = [x for x in current_colors if x in set(result_colors)]
            else:
                current_drop_list = base_names
                current_colors = result_colors
            #print(f"type {item['type']}: sub_list: {base_names}")
            #print(f"type {item['type']}: sub_colors: {result_colors}")
            #print(f"type {item['type']}: current_drop_list: {current_drop_list}")
            #print(f"type {item['type']}: current_colors: {current_colors}")
    # 4. handle "quality"
        if "quality" in item:
            base_names, result_colors = test.get_base_name_and_col(item["quality"],"quality")
            if current_drop_list:
                current_drop_list = [x for x in current_drop_list if x in set(base_names)]
                current_colors = [x for x in current_colors if x in set(result_colors)]
            else:
                current_drop_list = base_names
                current_colors = result_colors
            #print(f"quality {item['quality']}: sub_list: {base_names}")
            #print(f"quality {item['quality']}: sub_colors: {result_colors}")
            #print(f"quality {item['quality']}: current_drop_list: {current_drop_list}")
            #print(f"quality {item['quality']}: current_colors: {current_colors}")
    # 5. handle "item_class"
        if "item_class" in item:
            sub_list = []
            for file in [ test.f_armor, test.f_weapons ]:
                for key in file:
                    if "item_class" in file[key] and file[key]["item_class"] == item["item_class"]:
                        sub_list.append(test.name_to_code(key, "name", "display_name"))
            sub_colors = test.all_colors()
            if current_drop_list:
                current_drop_list = [x for x in current_drop_list if x in set(sub_list)]
                current_colors = current_colors
                # current_colors = [x for x in current_colors if x in set(sub_colors)]
            else:
                current_drop_list = sub_list
                current_colors = sub_colors
            #print(f"class {item['item_class']}: sub_list: {sub_list}")
            #print(f"class {item['item_class']}: sub_colors: {sub_colors}")
            #print(f"class {item['item_class']}: current_drop_list: {current_drop_list}")
            #print(f"class {item['item_class']}: current_colors: {current_colors}")
    # 6. handle "props" ethereal
        sub_colors = test.all_colors()
        eth = -1
        soc = -1
        if "props" in item:
            for i, prop in enumerate(item["props"]):
                #print(item["props"][i])
                if "name" in item["props"][i]:
                    if item["props"][i]["name"] == "ethereal":
                        eth = 1
                        if "arg1" in item["props"][i]:
                            if int(item["props"][i]["arg1"]) == 0:
                                eth = 0
                    elif item["props"][i]["name"] == "socketed":
                        soc = 1
                        if "arg1" in item["props"][i]:
                            if int(item["props"][i]["arg1"]) == 0:
                                soc = 0
        if (soc == -1 and eth == 0) or (soc == 0 and eth == -1):
            sub_colors.remove("gray")
        if (soc == 1) or (eth == 1):
            sub_colors.remove("white")
        current_colors = [x for x in current_colors if x in set(sub_colors)]

        for drop in current_drop_list:
            for col in current_colors:
                obj = {"name": drop, "color": col}
                print(obj)


    exit()

    for line in test.item:
        print("a")

    form="+{:d} to {} ({} only)"
    print(parse.search(form,line))