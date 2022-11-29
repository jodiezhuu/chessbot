#include <iostream>
#include <string>
#include "game.h"

using namespace std;

int main() {
    string command;
    while (cin >> command) {
        if (command == "game") {

        } else if (command == "resign") {

        } else if (command == "move") {

        } else if (command == "setup") {
            string subCommand;
            while (cin >> subCommand) {
                if (subCommand == "+") {

                } else if (subCommand == "-") {

                } else if (subCommand == "=") {

                } else if (subCommand == "done") {

                }
            }
        }
    }
    // Print final score here

    // Delete all objects
}