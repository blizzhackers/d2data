import json

with open("output/item_armor.json", "r",encoding = 'utf-8') as f:
    f_armor = json.load(f)

with open("output/item_misc.json", "r",encoding = 'utf-8') as f:
    f_misc = json.load(f)

with open("output/item_weapons.json", "r",encoding = 'utf-8') as f:
    f_weapons = json.load(f)

with open("output/item_list.txt", "w") as f:
    for key in f_armor.keys():
        f.write(f"{f_armor[key]['display_name']}  ")
    for key in f_weapons.keys():
        f.write(f"{f_weapons[key]['display_name']}  ")
    for key in f_misc.keys():
        f.write(f"{f_misc[key]['display_name']}  ")
