#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Mech.h"
#include "weapon.h"

using namespace std;

/**
*Default constructor
*/
mech::mech()
{

}

/**
*Constructor with two txt files as input used for debugging
*/
mech::mech(string wfile, string cfile)
{
    popWeapons(wfile);
    popComponents(cfile);
}

/**
*Full mech constructor with all necessary variables
*/
mech::mech(string wfile, string cfile, string dfile, int th, int hs)
{
    popWeapons(wfile);
    popComponents(cfile);
    heat = 0;
    heatsinks = hs;
    toHit = th;
    description = popDescription(dfile);
}

/**
*Deconstructor
*/
mech::~mech()
{

}

/**
*Random number generator. Same as RNG function in Mechwarrior_Main but used for Mech.cpp functions
*Returns the randomly generated number
*/
int mech::rngMech(int sides)
{
    int random = (rand()%sides)+1; // returns a number between 1 and sides
    return random;
}

/**
*Function that checks to see if the 0, 3 or 6 and 7 values in components have reached 0. One of these conditions
*is met the mech is considered destroyed. True = destroyed false = alive
*/
bool mech::mechDestroyed()
{
    bool destroyed = false;
        if (components[0] <= 0 || components[3] <= 0)
            destroyed = true; // if the head or center torso is destroyed the mech is dead
        else if (components[6] <= 0 && components[7] <= 0)
            destroyed = true; // if both legs are destroyed the mech is dead
    return destroyed;
}

/**
*Function that reads in the weapon specification filename and populates the weapons vector of the mech
*Returns nothing
*/
void mech::popWeapons(string wep)
{
    ifstream infile;
    infile.open(wep);
    string line = "";
        while(getline(infile, line))
        {
            weapons.push_back(weapon(line)); // fills the weapons vector with the lines from the input file
        }
    infile.close(); // good practice
}

/**
*Function that reads in the component values from a txt file and populates the array
*Returns nothing
*/
void mech::popComponents(string comp)
{
    ifstream infile;
    infile.open(comp);
    string line = "";
    int i = 0;
        while(getline(infile, line))
        {
            components[i] = stoi(line); // populates the current component position i with the last line that was read. because components is an integer array stoi is ised
            i++;
        }
    infile.close();
}

/**
*Function that fills the description string for a given mech with the text read from an input file.
*Returns the description string
*/
string mech::popDescription(string des)
{
    ifstream infile;
    infile.open(des);
    string description = "";
        while(getline(infile, description)) // read the description from the file, which is a single line, into the description variable
            return description;
}

/**
*Function that takes a component and a damage value and subtracts the damage amount from the value found in the corresponding component
*in the components array
*Returns nothing
*/
void mech::recordDamage (int comp_pos, int damageAmount)
{
    components[comp_pos] -= damageAmount; // subtracting the damage amount from the value found in the components array
}

/**
*Function that changes negative values within the components array to 0 because it looks better.
*Returns nothing
*/
void mech::setToZero()
{
    for (int i = 0; i < 8; i++)
    {
        if (components[i] < 0)
            components[i] = 0;
    }
}

/**
*Weapon firing function. Takes the weapon's position, the number fired and the to hit chance for the mech being targeted as inputs
*rolls a 20 sided 'dice', multiplies that number by the weapon's hit chance and compares it to the target's speed. if the product is
*higher than speed a hit is scored.
*Returns the number of a given weapon system that hit
*/
int mech::fireWeapon (int pos, int quant, int rth)
{
    int hitRoll = 0;
    int h = getWeaponHeat(pos); // heat will be added to the mech for each weapon fired
    int numHits = 0;
    float hc = getWeaponHitChance(pos); // hit chance will be needed to determine if a roll is high enough for a hit
    for (int i = 0; i < quant; i++) // runs a loop for the number of weapons fired
    {
        hitRoll = rngMech(20); // rolls a 20 sided 'dice'
            if (hitRoll*hc >= rth) // if the roll times the hit chance (a fraction) is higher than the target's speed a hit is recorded
            {
                numHits++; // keeps track of the number of hits
            }
        heat += h; // applies heat for each weapon fired
    }
    return numHits; // returns the number of hits recorded
}

/**
*Function that outputs a mech's armor values to the user.
*Returns nothing.
*/
void mech::getHealth()
{
    cout << "Head         " << components[0] << endl;
    cout << "Left Arm     " << components[1] << endl;
    cout << "Left Torso   " << components[2] << endl;
    cout << "Center Torso " << components[3] << endl;
    cout << "Right Torso  " << components[4] << endl;
    cout << "Right Arm    " << components[5] << endl;
    cout << "Left Leg     " << components[6] << endl;
    cout << "Right Leg    " << components[7] << endl;
}

/**
*Function that returns a mech's to hit value to the user
*/
int mech::getToHit()
{
    return toHit;
}

/**
*Function that returns a mech's heat value to the user
*/
int mech::getHeat()
{
    return heat;
}

/**
*Function that takes a mech's heatsinks as an input and subtracts that number from the mech's current heat.
*Returns nothing
*/
void mech::heatSinkEffect(int h)
{
    heat -= h; // heat equals heat minus the number of heatsinks
}

/**
*Function that allows the user or program to set the heat of a mech.
*Returns nothing
*/
void mech::setHeat(int h)
{
    heat = h;
}

/**
*Function that returns the number of heatsink on the mech which was specified in the function call.
*/
int mech::getHeatsinks()
{
    return heatsinks;
}

/**
*Function that returns a description of the mech which was specified in the function call
*/
string mech::getDescription()
{
    return description;
}

/**
*Function that takes a given position as an input variable and returns the name of the weapon in the weapons array that corresponds to that position
*/
string mech::getWeaponName(int a)
{
    string WN = "";
    WN = weapons[a].get_weapon_name();
    return WN;
}

/**
*Function that takes a given position as an input variable and returns the hit chance of the weapon in the weapons array that corresponds to that position
*/
float mech::getWeaponHitChance(int a)
{
    float HC = 0.0;
    HC = weapons[a].get_weapon_hit_chance();
    return HC;
}

/**
*Function that takes a given position as an input variable and returns the damage of the weapon in the weapons array that corresponds to that position
*/
int mech::getWeaponDamage(int a)
{
    int WD = 0;
    WD = weapons[a].get_weapon_damage();
    return WD;
}

/**
*Function that takes a given position as an input variable and returns the heat of the weapon in the weapons array that corresponds to that position
*/
int mech::getWeaponHeat(int a)
{
    int WH = 0;
    WH = weapons[a].get_weapon_heat();
    return WH;
}

/**
*Function that takes a given position as an input variable and returns the quantity of the weapon in the weapons array that corresponds to that position
*/
int mech::getWeaponQuantity(int a)
{
    int WQ = 0;
    WQ = weapons[a].get_weapon_quantity();
    return WQ;
}
