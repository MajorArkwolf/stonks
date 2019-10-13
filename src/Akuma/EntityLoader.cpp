#include "EntityLoader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Dice.hpp"

using std::ifstream;
using std::string;
using std::stringstream;

void EntityLoader::LoadEntity(string filename) {
    auto path        = string("entities/");
    filename         = path + filename;
    auto fileinput   = ifstream();
    auto currentLine = string();
    fileinput.open(filename);
    if (!fileinput.is_open()) {
        std::cout << "Read failure on " << path << std::endl;
        return;
    }

    auto command = string();
    while (std::getline(fileinput >> std::ws, currentLine)) {
        auto value = stringstream(currentLine);
        value >> command;
        if (command == "Name:") {
            std::getline(value >> std::ws, entity.name);
        } else if (command == "Faction:") {
            std::getline(value >> std::ws, entity.faction);
        } else if (command == "AI:") {
            std::getline(value >> std::ws, entity.AI);
        } else if (command == "Model:") {
            std::getline(value >> std::ws, entity.model);
        } else if (command == "Texture:") {
            std::getline(value >> std::ws, entity.texture);
        } else if (command == "Health:") {
            value >> entity.HP;
            entity.assignedHP = true;
        } else if (command == "Strength:") {
            value >> entity.strength;
        } else if (command == "Dexterity:") {
            value >> entity.dexterity;
        } else if (command == "Luck:") {
            value >> entity.luck;
        } else if (command == "Vitality:") {
            value >> entity.vitality;
        } else if (command == "Intelligence:") {
            value >> entity.intelligence;
        } else if (command == "Armor:") {
            value >> entity.armor;
        } else if (command == "ArmorStat:") {
            value >> entity.armorStats;
        } else if (command == "Weapon1:") {
            value >> entity.nameWeapon1;
        } else if (command == "Damage1:") {
            value >> entity.weapon1;
        } else if (command == "Weapon2:") {
            value >> entity.nameWeapon2;
        } else if (command == "Damage2:") {
            value >> entity.weapon2;
        } else if (command == "Weapon3:") {
            value >> entity.nameWeapon3;
        } else if (command == "Damage3:") {
            value >> entity.weapon3;
        } else if (command == "Weapon4:") {
            value >> entity.nameWeapon4;
        } else if (command == "Damage4:") {
            value >> entity.weapon4;
        } else if (command == "Shield:") {
            value >> entity.nameWeapon4;
        } else if (command == "ShieldStat:") {
            value >> entity.weapon4;
		} else if (command == "Level:") {
			value >> entity.level;
        } else if (command == "HD:") {
			value >> entity.level;
		} else {
            std::cout << "Value not used" << command << std::endl;
        }        
    }
    CheckStats();
}

void EntityLoader::CheckStats() {
    auto diceRoller = Dice();
    if (!entity.assignedHP) {
        for (auto i = 0; i < entity.level; ++i) {
            if (i = 0) {
                entity.HP = entity.HD + GetMod(entity.vitality)
            } else {
                entity.HP += diceRoller.Roll(entity.HD) + GetMod(entity.vitality);
			}
			
		}
        entity.assignedHP = true;
	}
}

void EntityLoader::GetMod(int stat) {
    if (stat < 10) {
        return (((11 - 1) / 2) * -1);
	}else {
        return ((stat - 10) / 2);
	}
}