import parse
import json

class Test:
    def __init__(self):

        self.drop = { "val": "Lacquered Plate", "color": "green" }

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

        self.quality_to_color = [
            {"normal": ["white", "gray"]},
            {"set": ["green"]},
            {"unique": ["gold"]},
            {"magic": ["blue"]},
            {"rune": ["orange"]},
            {"rare": ["yellow"]}
        ]

        with open("pickit.json", "r",encoding = 'utf-8') as f:
            self.f_pickit = json.load(f)
        with open("../output/item_armor.json", "r",encoding = 'utf-8') as f:
            self.f_armor = json.load(f)
        with open("../output/item_misc.json", "r",encoding = 'utf-8') as f:
            self.f_misc = json.load(f)
        with open("../output/item_weapons.json", "r",encoding = 'utf-8') as f:
            self.f_weapons = json.load(f)

        with open("../output/item_properties.json", "r",encoding = 'utf-8') as f:
            self.f_properties = json.load(f)
        with open("../output/item_types.json", "r",encoding = 'utf-8') as f:
            self.f_types = json.load(f)

        with open("../output/item_set_items.json", "r",encoding = 'utf-8') as f:
            self.f_set_items = json.load(f)
        with open("../output/item_unique_items.json", "r",encoding = 'utf-8') as f:
            self.f_unique_items = json.load(f)

        with open("../output/ref_codes.json", "r",encoding = 'utf-8') as f:
            self.f_ref_codes = json.load(f)

    def get_base_name(self, name: str, code_type: str):
        for key in self.f_ref_codes:
            if name == self.f_ref_codes[key][code_type]:
                return self.f_ref_codes[key]["display_name"]
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

    drop_list = []
    for item in test.f_pickit["items"]:
        colors = []
    # 1. handle "name"
        if "name" in item:
            base_name = test.get_base_name(item["name"],"name")
            if item["name"] in test.f_unique_items:
                if "gold" not in colors:
                    colors.append("gold")
            elif item["name"] in test.f_set_items:
                if "green" not in colors:
                    colors.append("green")
            elif any(item["name"] in d for d in [test.f_weapons, test.f_armor, test.f_misc]):
                if "white" not in colors:
                    colors.append("white")
                if "gray" not in colors:
                    colors.append("gray")
    # 2. handle "display_name"
        # loop through files to find key name
        if "display_name" in item:
            for key in test.f_unique_items:
                if test.f_unique_items[key]["display_name"] == item["display_name"]:
                    colors.append("gold")
                    break
            for key in test.f_set_items:
                if test.f_set_items[key]["display_name"] == item["display_name"]:
                    colors.append("green")
                    break
            for file in [test.f_misc, test.f_weapons, test.f_armor]:
                for key in file:
                    if file[key]["display_name"] == item["display_name"]:
                        colors.append("white")
                        colors.append("gray")
                        break
            # elif any(("display_name") in d for d in [test.f_weapons, test.f_armor, test.f_misc]):
            #     if "white" not in colors:
            #         colors.append("white")
            #     if "gray" not in colors:
            #         colors.append("gray")
    # 3. handle "type"
    # 4. handle "base"
    # 5. handle "item_class"
    # 6. handle "props" ethereal / socketed
        for color in colors:




    exit()

    for line in test.item:
        print("a")

    form="+{:d} to {} ({} only)"
    print(parse.search(form,line))