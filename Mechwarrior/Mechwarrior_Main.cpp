#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "weapon.cpp"
#include "Mech.cpp"

using namespace std;

/**
*Function that reads in a file line by line and displays the rules of the game when called.
*Returns nothing.
*/
void Rules (string filename)
{
    string line = "";
    ifstream infile;
    infile.open(filename);
        while(getline(infile, line))
        {
            cout << line << endl;
        }
}

/**
*Function that displays the opening page, prompts the user to see if they want to read the rules, gets the user's sex. Also
reads a file line by line depending on the user's selected sex and displays the opening storyline.
*/
string OpeningSequence (string filenameM, string filenameF)
{
    string junk = ""; // user's selected sex
    string line = "";
    char rules = 'n'; // variable to determine if the user wants rules to be displayed
    cout << endl;
    cout << "                   DECISION AT THUNDER RIFT!" << endl;
    cout << endl;
    cout << "                              A" << endl;
    cout << endl;
    cout << "****   " << "  *    " << "*****  " << "*****  " << "*      " << "*****  " << "*****  " << "*****  " << "  ***  " << "*   *" << endl;
    cout << "*  *   " << " * *   " << "  *    " << "  *    " << "*      " << "*      " << "  *    " << "*      " << " *     " << "*   *" << endl;
    cout << "****   " << "*****  " << "  *    " << "  *    " << "*      " << "*****  " << "  *    " << "*****  " << "*      " << "*****" << endl;
    cout << "*   *  " << "*   *  " << "  *    " << "  *    " << "*      " << "*      " << "  *    " << "*      " << " *     " << "*   *" << endl;
    cout << "*****  " << "*   *  " << "  *    " << "  *    " << "*****  " << "*****  " << "  *    " << "*****  " << "  ***  " << "*   *" << endl;
    cout << endl;
    cout << "                             GAME" << endl;
    cout << endl;
    cout << "              Copywrite 2019 -- Loverboy Studios" << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << endl;
        }
    cout << "Would you like to read the rules of the game?" << endl;
    cout << "(press y/n followed by ENTER)" << endl;
    cin >> rules; //y = see the rules n = skip the rules
    cout << endl;
        while (rules != 'y' && rules != 'n') //prevents an invalid input
        {
            cout << "INVALID ENTRY. Please press y or n followed by enter" << endl;
            cin >> rules;
        }
        if (rules == 'y')
            Rules("rules.txt"); // if the user selects y rules are displayed
    cout << endl;
    cout << "Press m or f followed by ENTER to begin" << endl; // prompts the user for their preferred sex
    cin >> junk; // sex
        while (junk != "m" && junk != "f") // prevents an invalid input
        {
            cout << "INVALID INPUT. Please press m or f followed by the ENTER key to begin" << endl;
            cin >> junk;
        }
    cout << endl;
        if (junk == "m") // if the user selects m then the male oriented filename is opened and displayed
        {
            ifstream infile;
            infile.open(filenameM);
                while (getline(infile, line))
                {
                    cout << line << endl;
                }
            infile.close();
        }
        else if (junk == "f") // if the user selects f then the female oriented filename is opened and displayed
        {
            ifstream infile;
            infile.open(filenameF);
                while (getline(infile, line))
                {
                    cout << line << endl;
                }
            infile.close();
        }
    return junk; // returns user's preferred sex to be used for the closing storyline

}

/**
*Simple Function that reads in the "prelude.txt" file and displays it to the user line by line
*Returns nothing
*/
void preludeToBattle(string filename)
{
    string line = "";
    ifstream infile;
    infile.open(filename);
        for (int i = 0; i < 5; i++) // some space before the text
        {
            cout << endl;
        }
        while (getline(infile, line))
        {
            cout << line << endl;
        }
        for (int i = 0; i < 5; i++) // and some space after the text
        {
            cout << endl;
        }
}

/**
*Function that reads in 3 possible endings, whether the user won or lost and their sex to determine
*the closing storyline to be displayed.
*Returns nothing.
*/
void victoryDefeat (string victoryM, string victoryF, string defeat, char wl, string mf)
{
    for (int i = 0; i < 5; i++) // space
        cout << endl;
    if (wl == 'l') // if the user loses there is only one possible end text
    {
        ifstream infile;
        infile.open(defeat);
        string line = "";
            while (getline(infile, line))
            {
                cout << line << endl;
            }
        cout << endl;
        cout << endl;
    }
    else if (wl == 'w' && mf == "m") // end text for the user winning and being male
    {
        ifstream infile;
        infile.open(victoryM);
        string line = "";
            while (getline(infile, line))
            {
                cout << line << endl;
            }
        cout << endl;
        cout << endl;
    }
    else if (wl == 'w' && mf == "f") // end text for the user winning and being female
    {
        ifstream infile;
        infile.open(victoryF);
        string line = "";
            while (getline(infile, line))
            {
                cout << line << endl;
            }
        cout << endl;
        cout << endl;
    }
}

/**
*Function that outputs a header and displays the input mech's weapons and their statistics.
*Returns nothing
*/
void displayMechWeapons (mech mechName)
{
    cout << "NAME\t" << "DAMAGE\t" << "HEAT\t" << "H_CHNCE\t" << "QUANTITY\t" << endl;
        for (int i = 0; i < 3; i++) // each mech has 3 weapon systems hence the 3 step for loop
        {
            cout << mechName.getWeaponName(i) << "\t" << mechName.getWeaponDamage(i) << "\t" << mechName.getWeaponHeat(i) << "\t" << mechName.getWeaponHitChance(i) << "\t" << mechName.getWeaponQuantity(i) << endl; // calls getters to display the given weapon's statistics
        }
}

/**
*Function that displays to the user which component of their mech was hit by enemy fire or which component of the enemy mech they hit.
*Takes an integer as input that is the result of an RNG roll and returns the location of the mech that was hit so that it can be entered
*into the recordDamage function. Input value will be between 0 and 14. output will be between 0 and 7.
*/
int componentLocation(int loc)
{
    if (loc == 0) // head only has one possible number to score a hit so headshots will be less frequent
        cout << "HEAD" << endl;
    else if (loc == 1 || loc == 2) // every other component has 2 possibilities again, so headshots will be less frequent
    {
        cout << "LEFT ARM" << endl;
        loc = 1; // changes the 15 sided 'dice' roll from the input to an 8 sided format so that it can be applied to one of the eight components
    }
    else if (loc == 3 || loc == 4)
    {
        cout << "LEFT TORSO" << endl;
        loc = 2;
    }
    else if (loc == 5 || loc == 6)
    {
        cout << "CENTER TORSO" << endl;
        loc = 3;
    }
    else if (loc == 7 || loc == 8)
    {
        cout << "RIGHT TORSO" << endl;
        loc = 4;
    }
    else if (loc == 9 || loc == 10)
    {
        cout << "RIGHT ARM" << endl;
        loc = 5;
    }
    else if (loc == 11 || loc == 12)
    {
        cout << "LEFT LEG" << endl;
        loc = 6;
    }
    else if (loc == 13 || loc == 14)
    {
        cout << "RIGHT LEG" << endl;
        loc = 7;
    }
    return loc; // returns the number that will correspond to the component that gets hit

}

/**
*Function that acts as a Random Number Generator. Take the maximum number possible as input. Randomly generated number
*will fall between 1 and the input number. Returns the randomly generated number.
*/
int RNG(int sides)
{
    int random = (rand()%sides)+1; // generates a random number between 1 and the user provided input
    return random; // returns the randomly generated number
}

/**
*Function that takes a mech as input and outputs its description, weapons, armor, and speed. Used for the mech selection process
*'Returns' nothing.
*/
void mechOverview(mech mechName)
{
    cout << mechName.description << endl; // calls the mechs description function to output an overview of the mech
    cout << endl;
    cout << "WEAPONS:" << endl;
    displayMechWeapons(mechName); // calls a function to display the mechs weapons as their statistics
    cout << endl;
    cout << "ARMOR VALUES:" << endl;
    mechName.getHealth(); // calls a function that displays the armor values for the mech
    cout << endl;
    cout << "SPEED: " << mechName.toHit << endl; // calls a function that displays the mechs speed which determines how hard it is to hit
    cout << "HEATSINKS: " << mechName.heatsinks << endl; //// calls a function that displays the number of heatsinks a mech has which are used to lower heat at the end of a combat round
}

/**
*Similar to the mechOverview function but used for reference during combat. gets rid of the speed and heatsink values but displays the mech's
*current heat. 'Returns' nothing.
*/
void combatOverview(mech mechName)
{
    int heat = mechName.getHeat(); // gets the mech's current heat so the user knows their or Ricol's heat is
    cout << endl;
    mechName.getHealth(); // gets the current health of the player mech or Ricol's mech.
    cout << endl;
    cout << "CURRENT HEAT: " << heat << endl; // displays current heat
    cout << endl;
    cout << "WEAPONS:" << endl;
    displayMechWeapons(mechName); // calls a function to display the mech's weapons for reference
}

/**
*Function that takes in the 4 mech types as input and returns the mech the user would like to play the game with.
*Gives a complete rundown of the mech with the mechOverview function.
*/
mech mechSelect(mech Wasp, mech ShadowHawk, mech Marauder, mech Atlas)
{
    mech userMech;
    int choice = 0;
    char confirm = 'n';
        while (confirm == 'n') // while loop that allows the user to see a mech overview without having to select that mech for the game
        {
            cout << "Which mech will you take into battle?" << endl;
            cout << "(Select a mech for a full overview)" << endl;
            cout << endl;
            cout << "1: WSP-1A 'WASP'" << endl;
            cout << "2: SHK-5C 'SHADOW HAWK'" << endl;
            cout << "3: MAD-3R 'MARAUDER'" << endl;
            cout << "4: ATL-9T 'ATLAS'" << endl;
            cin >> choice; // user inputs the value for the mech they want to see more information on
                while (choice != 1 && choice != 2 && choice != 3 && choice != 4) // prevents against invalid inputs
                {
                    cout << endl;
                    cout << "INVALID ENTRY. Please select a number between 1 and 4 and press ENTER" << endl;
                    cin >> choice;
                }
            cout << endl;
                if (choice == 1)
                {
                    mechOverview(Wasp); // displays the overview for the Wasp mech
                    userMech = Wasp; // saves this value as the return value in case the user confirms that this is the mech they want to use
                    cout << endl;
                    cout << "Face Ricol in a WASP? (press y/n and ENTER)" << endl;
                    cin >> confirm; // a confirm value of y will end the while loop
                        while (confirm != 'y' && confirm != 'n') // prevents against invalid inputs
                        {
                            cout << endl;
                            cout << "INVALID ENTRY. Please press y or n followed by ENTER" << endl;
                            cin >> confirm;
                        }
                }
                else if (choice == 2) // same as choice == 1 with the Shadow Hawk in place of the Wasp
                {
                    mechOverview(ShadowHawk);
                    userMech = ShadowHawk;
                    cout << endl;
                    cout << "Face Ricol in a SHADOW HAWK? (press y/n and ENTER)" << endl;
                    cin >> confirm;
                        while (confirm != 'y' && confirm != 'n')
                        {
                            cout << endl;
                            cout << "INVALID ENTRY. Please press y or n followed by ENTER" << endl;
                            cin >> confirm;
                        }
                }
                else if (choice == 3) // same as choice == 1 with the Marauder in place of the wasp
                {
                    mechOverview(Marauder);
                    userMech = Marauder;
                    cout << endl;
                    cout << "Face Ricol in a MARAUDER? (press y/n and ENTER)" << endl;
                    cin >> confirm;
                        while (confirm != 'y' && confirm != 'n')
                        {
                            cout << endl;
                            cout << "INVALID ENTRY. Please press y or n followed by ENTER" << endl;
                            cin >> confirm;
                        }
                }
                else if (choice == 4) // same as choice == 1 with the Atlas in place of the Wasp
                {
                    mechOverview(Atlas);
                    userMech = Atlas;
                    cout << endl;
                    cout << "Face Ricol in an ATLAS? (press y/n and ENTER)" << endl;
                    cin >> confirm;
                        while (confirm != 'y' && confirm != 'n')
                        {
                            cout << endl;
                            cout << "INVALID ENTRY. Please press y or n followed by ENTER" << endl;
                            cin >> confirm;
                        }
                }
        }

    return userMech; // when the while loop is broken the last mech the user looked at, and confirmed selection of, will be saved and returned to be used in the combat rounds

}

/**
*Function that performs the user's combat round. Takes the user's mech and Ricol's mech as inputs and returns both mechs in a mech vector so that
*damage and heat incurred during this round are saved and applied to the next round.
*/
vector<mech> combatRound(mech userMech, mech Ricol)
{
    vector<mech> m; // the vector that will be used to return both input mechs.
    int ricolToHit = Ricol.getToHit(); // ricol's speed number to be used it hit calculations
    int heatDis = userMech.getHeatsinks(); // users heatsinks. this number will be deducted from the user's heat at the end of the combat round.
    int userHeat = userMech.getHeat(); // gets the user's current heat so a shutdown check can be performed.
        if (userHeat < 0)
        {
            int heatReset = 0;
            userMech.setHeat(heatReset); // if the user's heat has gone into negative numbers this resets it back to 0. essentially, heat can never go below 0
        }
    bool alreadyFired = false; // bool value that will prevent weapons from being fired more than once per round
    bool continueCombat = true; // will end a while loop when the user decides that they want their round to be over
        if (userHeat < 30) // if heat is under 30 the user can fire weapons and use sensors
        {
            cout << endl;
            cout << "With Duke Ricol's mech in your sights you prepare for combat!" << endl;
            cout << endl;
                while (continueCombat == true)
                {
                    bool RD = Ricol.mechDestroyed(); // checks to see if Ricol is dead. this is so the game ends immediately after weapons have been fired and Ricol has been destroyed rather than continuing to prompt the user to use their sensors
                    if (RD == true)
                        break; // if Ricol is dead break out of the while loop
                    int userSelection = 0; // value that corresponds to an action 1-4
                    cout << endl;
                    cout << endl;
                    cout << "What will you do next? (make selection and press ENTER)" << endl;
                    cout << endl;
                    cout << "1: Get Mech Status" << endl;
                    cout << "2: Scan Ricol's Mech" << endl;
                    cout << "3: Fire Weapons" << endl;
                    cout << "4: End Combat Round" << endl;
                    cout << endl;
                    cin >> userSelection; // user selects the action they want to perform next
                        while (userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4) // makes sure a valid number has been selected
                        {
                            cout << "INVALID SELECTION: Please choose a number between 1 and 4 and press ENTER";
                            cin >> userSelection;
                        }
                        if (userSelection == 1)
                        {
                            cout << endl;
                            cout << "YOUR CURRENT MECH STATUS:" << endl;
                            combatOverview(userMech); // if 1 is selected then the combatoverview for the user mech is called
                        }
                        else if (userSelection == 2)
                        {
                            cout << endl;
                            cout << "RICOL'S CURRENT STATUS:" << endl;
                            combatOverview(Ricol); // if 2 is selected the combatOverview for Ricol's mech is called
                        }
                        else if (userSelection == 3)
                        {
                            if (alreadyFired == false) // checks to make sure user hasn't already fired weapons this round
                            {
                                int weaponChoice = 0; // variable to save the weapons types that were fired
                                int weaponChoice2 = 0;
                                int weaponChoice3 = 0;
                                int weaponsFired = 0; // variables to save the number of each weapon type that was fired
                                int weaponsFired2 = 0;
                                int weaponsFired3 = 0;
                                string selectedWeapon = ""; // variables to save the name of each weapon that was fired
                                string selectedWeapon2 = "";
                                string selectedWeapon3 = "";
                                char yn = 'y'; // when changed to n the game stops prompting the user to select which weapon system they want to fire
                                    while (yn == 'y')
                                    {
                                        cout << endl;
                                        cout << "Which weapon system would you like to fire? (make selection and press ENTER)" << endl;
                                        cout << endl;
                                            for (int i = 0; i < 3; i++)
                                            {
                                                cout << (i+1) << ": " << userMech.getWeaponName(i) << endl; // displays the names of the weapons in the user's weapons vector
                                            }
                                        cout << endl;
                                        cin >> weaponChoice; // the first weapon system the user will fire
                                            while (weaponChoice != 1 && weaponChoice != 2 && weaponChoice != 3) // prevents against invalid inputs
                                            {
                                                cout << "Invalid Selection! Please try again:" << endl;
                                                cout << endl;
                                                cin >> weaponChoice;
                                            }
                                        selectedWeapon = userMech.getWeaponName(weaponChoice-1); // saves the weapon name so it can be outputted to the screen
                                        cout << endl;
                                        cout << "how many " << selectedWeapon << "s would you like to fire? (select a number 1-" << userMech.getWeaponQuantity(weaponChoice-1) << " and press ENTER)" << endl; // asks the user how many weapons they want to fire based on how many of that weapon type they have
                                        cin >> weaponsFired; // user's input for the quantity of weapons they want to fire
                                            while ((weaponsFired > userMech.getWeaponQuantity(weaponChoice-1)) || (weaponsFired <= 0)) // protects against invalid inputs
                                            {
                                                cout << "You dont have that many " << selectedWeapon << "s! Try again " << endl;
                                                cin >> weaponsFired;
                                            }
                                        cout << endl;
                                        cout << "Would you like to fire any other weapon systems? (y/n and press ENTER)" << endl;
                                        cin >> yn; // y will result in the loop continuing and more weapon systems being inputted. n will break the while loop
                                            if (yn == 'y') // same as above but will save values in the second weaponsChoice weaponFired and selectedWeapon variables
                                            {
                                                cout << endl;
                                                cout << "Which weapon system would you like to fire? (make selection and press ENTER)" << endl;
                                                cout << endl;
                                                    for (int i = 0; i < 3; i++)
                                                    {
                                                        if (i+1 != weaponChoice)
                                                        cout << (i+1) << ": " << userMech.getWeaponName(i) << endl;
                                                    }
                                                cout << endl;
                                                cin >> weaponChoice2;
                                                    while ((weaponChoice2 != 1 && weaponChoice2 != 2 && weaponChoice2 != 3) || (weaponChoice2 == weaponChoice))
                                                    {
                                                        cout << "Invalid Selection! Please try again:" << endl;
                                                        cout << endl;
                                                        cin >> weaponChoice2;
                                                    }
                                                selectedWeapon2 = userMech.getWeaponName(weaponChoice2-1);
                                                cout << endl;
                                                cout << "how many " << selectedWeapon2 << "s would you like to fire? (select a number 1-" << userMech.getWeaponQuantity(weaponChoice2-1) << " and press ENTER)" << endl;
                                                cin >> weaponsFired2;
                                                    while ((weaponsFired2 > userMech.getWeaponQuantity(weaponChoice2-1)) || (weaponsFired2 <= 0))
                                                    {
                                                        cout << "You dont have that many " << selectedWeapon2 << "s! Try again " << endl;
                                                        cin >> weaponsFired2;
                                                    }
                                                cout << endl;
                                                cout << "Would you like to fire any other weapon systems? (y/n and press ENTER)" << endl;
                                                cin >> yn;
                                            }
                                            if (yn == 'y') // each mech has three weapon systems so this will be the last time through the loop
                                            {
                                                cout << endl;
                                                cout << "Which weapon system would you like to fire? (make selection and press ENTER)" << endl;
                                                cout << endl;
                                                    for (int i = 0; i < 3; i++)
                                                    {
                                                        if (i+1 != weaponChoice && i+1 != weaponChoice2)
                                                            cout << (i+1) << ": " << userMech.getWeaponName(i) << endl;
                                                    }
                                                    cout << endl;
                                                    cin >> weaponChoice3;
                                                        while ((weaponChoice3 != 1 && weaponChoice3 != 2 && weaponChoice3 != 3) || (weaponChoice3 == weaponChoice) || (weaponChoice3 == weaponChoice2))
                                                        {
                                                            cout << "Invalid Selection! Please try again:" << endl;
                                                            cout << endl;
                                                            cin >> weaponChoice3;
                                                        }
                                                    selectedWeapon3 = userMech.getWeaponName(weaponChoice3-1);
                                                    cout << endl;
                                                    cout << "how many " << selectedWeapon3 << "s would you like to fire? (select a number 1-" << userMech.getWeaponQuantity(weaponChoice3-1) << " and press ENTER)" << endl;
                                                    cin >> weaponsFired3;
                                                        while ((weaponsFired3 > userMech.getWeaponQuantity(weaponChoice3-1)) || (weaponsFired3 <= 0))
                                                        {
                                                            cout << "You dont have that many " << selectedWeapon3 << "s! Try again " << endl;
                                                            cin >> weaponsFired3;
                                                        }
                                                    cout << endl;
                                                    yn = 'n';
                                            }
                                    }
                                    if (weaponChoice != 0) // if the user selected one weapon system to fire it will be stored in this variable
                                    {
                                        cout << endl;
                                        cout << "You line Ricol up in your crosshairs and fire your " << selectedWeapon; // text that tells the user what weapon is firing
                                            if (weaponsFired > 1)
                                                cout << "s";
                                        cout << "!" << endl;
                                        int hits = userMech.fireWeapon(weaponChoice-1, weaponsFired, ricolToHit); // runs the fireWeapon function to determine the number of hits that are scored with the given weapon system
                                            if (hits > 0) // detemines output to the screen based on how many hits were scored
                                                cout << "You score " << hits << " hits to Ricol's Mech in the following locations!" << endl;
                                            else
                                                cout << "Your aim is off and your shots all go wide. No hits..." << endl;
                                        int d = userMech.getWeaponDamage(weaponChoice-1); // gets the damage value for the weapon system that was fired so it can be applied to the appropriate component
                                            for (int i = 0; i < hits; i++)
                                            {
                                                int r = RNG(15)-1; // rolls a random number for each hit.
                                                int compLoc = componentLocation(r); // random number is fed to the function that determines which component was hit
                                                Ricol.recordDamage(compLoc, d); // once a component has been determined the damage is recorded using this function. the component hit and the amount of damage dealt are the input values
                                            }
                                        }
                                    if (weaponChoice2 != 0) // if the user selected a second weapon system to fire the process from the above if statement repeats
                                    {
                                        cout << endl;
                                        cout << "You line Ricol up in your crosshairs and fire your " << selectedWeapon2;
                                            if (weaponsFired2 > 1)
                                                cout << "s";
                                        cout << "!" << endl;
                                        int hits = userMech.fireWeapon(weaponChoice2-1, weaponsFired2, ricolToHit);
                                            if (hits > 0)
                                                cout << "You score " << hits << " hits to Ricol's Mech in the following locations!" << endl;
                                            else
                                                cout << "Your aim is off and your shots all go wide. No hits..." << endl;
                                        int d = userMech.getWeaponDamage(weaponChoice2-1);
                                            for (int i = 0; i < hits; i++)
                                            {
                                                int r = RNG(15)-1;
                                                int compLoc = componentLocation(r);
                                                Ricol.recordDamage(compLoc, d);
                                            }
                                    }
                                    if (weaponChoice3 != 0) // if the user selected a third weapon system to fire the process from the above if statement repeats
                                    {
                                        cout << endl;
                                        cout << "You line Ricol up in your crosshairs and fire your " << selectedWeapon3;
                                            if (weaponsFired3 > 1)
                                                cout << "s";
                                        cout << "!" << endl;
                                        int hits = userMech.fireWeapon(weaponChoice3-1, weaponsFired3, ricolToHit);
                                            if (hits > 0)
                                                cout << "You score " << hits << " hits to Ricol's Mech in the following locations!" << endl;
                                            else
                                                cout << "Your aim is off and your shots all go wide. No hits..." << endl;
                                        int d = userMech.getWeaponDamage(weaponChoice3-1);
                                            for (int i = 0; i < hits; i++)
                                            {
                                                int r = RNG(15)-1;
                                                int compLoc = componentLocation(r);
                                                Ricol.recordDamage(compLoc, d);
                                            }
                                    }
                                alreadyFired = true; // once weapons have been fired this value sets to true so weapons can not be fired again this round
                            }
                            else
                                cout << "Sorry, you've already fired your weapons this round" << endl;
                            Ricol.setToZero(); // function that sets any component values which have gone into negative numbers to 0 because it looks nicer
                        }
                        else if (userSelection == 4)
                        {
                            continueCombat = false; // end combat round option. this... well... ends the combat round
                        }
                }

        }
        else // if heat is 30 or over a combat round is missed
        {
            cout << "YOUR MECH IS OVERHEATED!!!" << endl;
            cout << "Ricol lines you up for another volley while you frantically attempt" << endl;
            cout << "to restart your machine!" << endl;
            cout << endl;
        }
    userMech.heatSinkEffect(heatDis); // essentially a setter that sets the mech's heat to its current heat minus the number of heatsinks before the mech is returned at the end of the combat round
    m.push_back(Ricol); // places Ricol into the return vector
    m.push_back(userMech); // places the user mech into the return vector
    return m; // returns the two mechs
}

/**
*Function that takes the user's mech and Ricol's mech as input and returns a vector containing the two mechs. Uses a basic 'AI' to perform attacks
*by Ricol against the user.
*/
vector<mech> ricolCombatRound(mech userMech, mech Ricol)
{
    cout << endl;
    cout << "Ricol repositions his mech and lines up for a barrage of weapons fire!" << endl;
    cout << endl;
    vector<mech> m; // return vector
    int heat = Ricol.getHeat(); // Ricol's current heat so a overheat check can be performed
    int heatDis = Ricol.getHeatsinks(); // number of heatsinks on Ricol's mech. value will be used to dissipate heat at the end of the round
    float userToHit = userMech.getToHit(); // user's speed. will be used to determine if weapons hit
        if (heat < 0)
        {
            int heatReset = 0; // resets Ricol's heat to 0 if it has gone below 0 because it looks nicer
            Ricol.setHeat(heatReset);
        }
        if (heat < 30) // checks to make sure Ricol isn't overheated
        {
            if (heat <= 10) // there are 3 heat ranges that will be used to determine Ricol's behavior
            {
                int lowHeat = RNG(2); // returns a random number to determine what Ricol will do
                    if (lowHeat == 1)
                    {
                        int hits = Ricol.fireWeapon(1, 2, userToHit); // if a 1 is returned from the RNG Ricol fires 2 PPCs and hits are determined using the fireWeapon function
                            if (hits > 0)
                                cout << "Ricol fires 2 PPCs at your mech hitting with " << hits << " of them!" << endl;
                            else
                                cout << "Ricol fires 2 PPCs at your mech but misses with both shots!" << endl;
                            int d = Ricol.getWeaponDamage(1); // damage for the fired weapon system is stored so it can be fed into the recordDamage function
                                for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1; // random number for each hit is determined
                                    int compLoc = componentLocation(r); // location that was hit is determined using the r value as input
                                    userMech.recordDamage(compLoc, d); // damage is allocated based on the d value that was gathered earlier and the component that is stored in compLoc
                                }
                            hits = Ricol.fireWeapon(2, 1, userToHit); // variation of the same process with an autocannon.
                                if (hits == 1)
                                    cout << "Ricol fires his Autocannon! Your teeth chatter as his shells hit home." << endl;
                                else
                                    cout << "Ricol fires his Autocannon but misses you completely!" << endl;
                                d = Ricol.getWeaponDamage(2);
                                for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1;
                                    int compLoc = componentLocation(r);
                                    userMech.recordDamage(compLoc, d);
                                }
                    }
                    if(lowHeat == 2) // variation of the above process with different weapons fired so Ricol doesn't always do the same thing in the same situation
                    {
                        int hits = Ricol.fireWeapon(0, 1, userToHit);
                            if (hits > 0)
                                cout << "Ricol snaps off 2 LASER shots at you, hitting with " << hits << " of them!" << endl;
                            else
                                cout << "Ricol wildly fires 2 LASERs in attempt to end this fight. Luckily for you they both miss" << endl;
                            int d = Ricol.getWeaponDamage(0);
                                for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1;
                                    int compLoc = componentLocation(r);
                                    userMech.recordDamage(compLoc, d);
                                }
                        hits = Ricol.fireWeapon(1, 2, userToHit);
                            if (hits > 0)
                                cout << "Ricol continues his onslaught, hitting you with " << hits << " PPC!" << endl;
                            else
                                cout << "Ricol blasts away with both PPCs but only destroys the guard post behind you." << endl;
                            d = Ricol.getWeaponDamage(1);
                                for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1;
                                    int compLoc = componentLocation(r);
                                    userMech.recordDamage(compLoc, d);
                                }
                        hits = Ricol.fireWeapon(2, 1, userToHit);
                            if (hits == 1)
                                cout << "Ricol fires his Autocannon! Armor flies from your mech as 120mm shells hit home" << endl;
                            else
                                cout << "Ricol fires his Autocannon but your quick reflexes allow you to evade his shots." << endl;
                            d = Ricol.getWeaponDamage(2);
                            for (int i = 0; i < hits; i++)
                            {
                                int r = RNG(15)-1;
                                int compLoc = componentLocation(r);
                                userMech.recordDamage(compLoc, d);
                            }
                    }
            }
            else if (heat <= 20 && heat > 10) // mid range heat bracket. exact same idea as above but the weapons fired will generate slightly less heat so Ricol is not constantly overheating
            {
                int medHeat = RNG(2);
                    if (medHeat == 1)
                    {
                        int hits = Ricol.fireWeapon(0, 2, userToHit);
                            if (hits > 0)
                                cout << "Ricol lets loose with 2 LASER beams and " << hits << " hit your mech in the " << endl;
                            else
                                cout << "Ricol lets loose with 2 LASER beams but his aim is flawed and he misses with both" << endl;
                        int d = Ricol.getWeaponDamage(0);
                            for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1;
                                    int compLoc = componentLocation(r);
                                    userMech.recordDamage(compLoc, d);
                                }
                        hits = Ricol.fireWeapon(2, 1, userToHit);
                            if (hits == 1)
                                cout << "Recoil pummels your mech with a burst of Autocannon fire stripping your 'mech's armor " <<  endl;
                            else
                                cout << "Ricol's Autocannon shot passes harmlessly over your mech's shoulder" << endl;
                            d = Ricol.getWeaponDamage(2);
                                for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1;
                                    int compLoc = componentLocation(r);
                                    userMech.recordDamage(compLoc, d);
                                }
                    }
                    if (medHeat == 2)
                    {
                        int hits = Ricol.fireWeapon(1, 1, userToHit);
                            if (hits > 0)
                                cout << "Ricol fires a single PPC. The shot slams into your 'mech's armor!" << endl;
                            else
                                cout << "Trying to keep his heat in check, Ricol fires a single PPC, the shot goes wide." << endl;
                        int d = Ricol.getWeaponDamage(1);
                            for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1;
                                    int compLoc = componentLocation(r);
                                    userMech.recordDamage(compLoc, d);
                                }
                        hits = Ricol.fireWeapon(2, 1, userToHit);
                            if (hits == 1)
                                cout << "Autocannon shells shake your 'mech to its core. Alarm Klaxons begin to wail! " << endl;
                            else
                                cout << "Ricol's Aim is spoiled, possibly by your good looks. He misses his autocannon shot." << endl;
                            d = Ricol.getWeaponDamage(2);
                                for (int i = 0; i < hits; i++)
                                {
                                    int r = RNG(15)-1;
                                    int compLoc = componentLocation(r);
                                    userMech.recordDamage(compLoc, d);
                                }
                    }
            }
            else if (heat <= 29 && heat > 20) // same process again with even less heat generated by the options
            {
                int highHeat = RNG(4); // this heat bracket has one option for Ricol that results in him cooling and one that results in him overheating. 4 possible numbers are returned here so that the likelihood of him overheating can be lower than him cooling
                    if (highHeat < 4) // if a 1-3 is returned by the RNG Ricol performs this action, causing his heat to drop
                    {
                        int hits = Ricol.fireWeapon(2, 1, userToHit);
                            if (hits == 1)
                                cout << "Keeping an eye on his heat, Ricol only fires his Autocannon but he hits your" << endl;
                            else
                                cout << "The heat inside the cockpit spoils Ricol's aim and his Autocannon shot goes wide" << endl;
                        int d = Ricol.getWeaponDamage(2);
                            for (int i = 0; i < hits; i++)
                            {
                                int r = RNG(15)-1;
                                int compLoc = componentLocation(r);
                                userMech.recordDamage(compLoc, d);
                            }
                    }
                    if (highHeat == 4) // if a 4 is returned by the RNG Ricol fires more weapons than his heatsinks can handle and he overheats
                    {
                        int hits = Ricol.fireWeapon(1, 2, userToHit);
                            if (hits > 0)
                                cout << "With blatent disregard for his heat, Ricol fires both PPCs hitting with " << hits << endl;
                            else
                                cout << "Despite his high heat Ricol fires both PPCs. Luckily for you, he misses." << endl;
                        int d = Ricol.getWeaponDamage(1);
                            for (int i = 0; i < hits; i++)
                            {
                                int r = RNG(15)-1;
                                int compLoc = componentLocation(r);
                                userMech.recordDamage(compLoc, d);
                            }
                        hits = Ricol.fireWeapon(2, 1, userToHit);
                            if (hits == 1)
                                cout << "Ricol brings a burst of Autocannon fire to the party hitting your" << endl;
                            else
                                cout << "Intense heat causes sweat to drip into Recoils eyes as he fires. His autocannon shot misses your mech" << endl;
                        d = Ricol.getWeaponDamage(2);
                            for (int i = 0; i < hits; i++)
                            {
                                int r = RNG(15)-1;
                                int compLoc = componentLocation(r);
                                userMech.recordDamage(compLoc, d);
                            }
                    }
            }
            userMech.setToZero(); // sets all negative values in the user's mechs component array to 0 because it looks better
        }
        else
        {
            cout << "RICOL HAS OVERHEATED!!!" << endl;
            cout << "As he desperately attempts to restart his 'mech" << endl;
            cout << "you pull your guns in line with his cockpit" << endl;
            cout << endl;
        }
    cout << endl;
    cout << endl;
    cout << endl;
    Ricol.heatSinkEffect(heatDis); // lowers Ricol's heat by the number of heatsinks on his mech
    m.push_back(Ricol); // puts Ricol into the return array
    m.push_back(userMech); // puts the user's mech into the return array
    return m; // returns the two mechs
}






int main (void)
{
    srand((unsigned)time(0)); // seed for the random number generator. uses the system clock
    mech Atlas("AtlasWeapons.txt", "AtlasComponents.txt", "AtlasDescription.txt", 4, 20); // builds the Atlas
    mech Marauder("MarauderWeapons.txt", "MarauderComponents.txt", "MarauderDescription.txt", 6, 18); // builds the Marauder
    mech ShadowHawk("ShadowHawkWeapons.txt", "ShadowHawkComponents.txt", "ShadowHawkDescription.txt", 8, 15); // builds the Shadow Hawk
    mech Wasp("WaspWeapons.txt", "WaspComponents.txt", "WaspDescription.txt", 10, 10); // builds the Wasp

    mech userMech; // mech used by the player
    mech Ricol = Marauder; // Ricol pilots a Marauder

    string sex = OpeningSequence("open_m.txt", "open_f.txt"); //saves the sex chosen by the user so the closing sequence will be appropriate and runs the opening sequence
    userMech = mechSelect(Wasp, ShadowHawk, Marauder, Atlas); // runs the mech select function with the 4 mechs that the user can choose from
    preludeToBattle("prelude.txt"); // runs the prelude to battle text

    vector<mech> mechs; // vetor that will store the mechs when they return from each combat round

    bool playerDead = userMech.mechDestroyed(); // bool value that uses the mechDestroyed function to determine if the user has been destroyed
    bool ricolDead = Ricol.mechDestroyed(); // bool value that uses the mechDestroyed function to determine if Ricol has been destroyed

    while (playerDead == false) // if the player is still alive...
    {
        mechs = combatRound(userMech, Ricol); // player combat round goes first
        Ricol = mechs[0]; // ricol's mech is updated after combat
        userMech = mechs[1]; // user's mech is updated after combat
        ricolDead = Ricol.mechDestroyed(); // checks to see if Ricol is dead
        playerDead = userMech.mechDestroyed(); // checks to see if the player is dead
            if (playerDead == true) // if user is dead after combat round...
            {
                victoryDefeat("victory_m.txt", "victory_f.txt", "defeat.txt", 'l', sex); // defeat function is run and the player gets one of 3 possible closing sequences
                break; // breaks the while loop so nothing else happens after the player is dead
            }
            if (ricolDead == false) // if ricol is still alive
            {
                mechs = ricolCombatRound(userMech, Ricol); // feeds user and ricol mechs into ricol's combat round
                Ricol = mechs[0]; // updates ricol's mech after ricol combat round
                userMech = mechs[1]; // updates user mech after ricol combat round
                playerDead = userMech.mechDestroyed(); // checks to see if the player has been killed
                    if (playerDead == true)
                    {
                        victoryDefeat("victory_m.txt", "victory_f.txt", "defeat.txt", 'l', sex); // if the user has been defeated l is fed into the victoryDefeat function so the user will see the defeat closing sequence
                    }
            }
            else if (ricolDead == true) // if ricol is dead...
            {
                victoryDefeat("victory_m.txt", "victory_f.txt", "defeat.txt", 'w', sex); // w is fed into the function along with the user's sex. will display the VICTORY closing sequence!
                break; // breaks the loop so nothing else happens
            }
    }
}
