#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "weapon.h"

using namespace std;

/**
*Default constructor
*/
weapon::weapon()
{

}

/**
*Constructor that takes a txt file as input and populates the weapon's statistics line by line
*/
weapon::weapon(string specs)
{
    pop_weapon_specs(specs);
}

weapon::~weapon()
{

}

/**
*Function that fills the weapons array from a file passed in by the constructor
*Returns nothing
*/
void weapon::pop_weapon_specs(string specs)
{
    string stats[5]; // each weapon has 5 attributes, this array stores them as they are read in as strings
    int i = 0;
    stringstream ss (specs);
    string stat = "";
        while (getline(ss, stat, '\t')) // each attribute is separated by a tab character
        {
            stats[i] = stat; // fills the stats array
            i++;
        }
    weapon_name = stats[0]; // populates the weapon_name variable from stats
    damage_out = stoi(stats[1]); // populates the damage_out variable from stats and performs the appropriate stoi call
    heat_gen = stoi(stats[2]);
    hit_chance = stof(stats[3]);
    quantity = stoi(stats[4]);
}

/**
*Function that returns the weapon_name variable when called.
*/
string weapon::get_weapon_name()
{
    return weapon_name;
}

/**
*Function that returns the hit_chance variable when called.
*/
float weapon::get_weapon_hit_chance()
{
    return hit_chance;
}

/**
*Function that returns the damage_out variable when called.
*/
int weapon::get_weapon_damage()
{
    return damage_out;
}

/**
*Function that returns the heat_gen variable when called.
*/
int weapon::get_weapon_heat()
{
    return heat_gen;
}

/**
*Function that returns the weapon_quantity variable when called.
*/
int weapon::get_weapon_quantity()
{
    return quantity;
}













