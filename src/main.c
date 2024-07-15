#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "helpers.h"

int main() {

    // Start main menu
    while(true) {
        switch(startMenu()) {
            case 1: // LOAD_A

                break;
            case 2: // LOAD_M

                break;
            case 3: // LOAD_H

                break;
            case 4: // CLEAR

                break;
            case 0: // QUIT

                return 0;
            default:
                printf("Invalid number, press any key to try again.");
                getchar();
        }
    }

    return EXIT_SUCCESS;
}
