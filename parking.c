#include <stdio.h>

// variables

int main(){
    char plateNumber[20][20];
    char timeIn[20][10];
    char timeOut[20][10];
    char Type_of_the_vehicle[20][20];
    char vehicleColor[20][20];
    char contactNumber[20][20];
    int Handicap[20];
    int slotTaken[20];
    int z;
    int choice = 0;
    char Handicapped;

    // Initialize slots
    // this loop run 20 times
    for (int z = 0; z < 20; z++){
        // slot is  freee no parked yet!!!! , marks all slots are empty at the start
        slotTaken[z] = 0;
        Handicap[z] = 0;
    }
  
    Handicap[0] = 1;
    Handicap[19] = 1;

    // if command is not = 4 program will continue to run until you press 4 for exit
    while (choice != 4){
        // parking menu

        printf("\n=============================================\n");
        printf("   Hi there! Welcome to your Parking Assistant -_-  \n");
        printf("     Efficient | Secure | User-Friendly       \n");
        printf("=============================================\n");
        printf("\n 1. Park a Vehicle");
        printf("\n 2. Remove a Vehicle");
        printf("\n 3. View Parking Slots");
        printf("\n 4. Exit");
        printf("\n Enter your choice: ");
        scanf("%d", &choice);

        // choice 1

        // if user press on choice 1 will ask for information
        if (choice == 1){
            int parked = 0;

            // will ask information like is the driver handicapped or not.
            printf("Is the driver handicapped!! (y/n): ");
            scanf(" %c", &Handicapped);

            // goes through all the 20 parking (z  represnet 0 to 19)
            for (z = 0; z < 20; z++){
                if (parked == 0) {
                    // check if the slot is free or not
                    if (slotTaken[z] == 0) {
                        // handicap[i]==1 is presented as yes   handicap[i]==0 is presented as no
                        if ((Handicapped == 'y' && Handicap[z] == 1) || (Handicapped == 'n' && Handicap[z] == 0)) {

                            printf("Enter Plate Number: ");
                            scanf("%s", plateNumber[z]);
                            printf("Enter Time In (e.g: 00:00): ");
                            scanf("%s", timeIn[z]);
                            printf("Enter Vehicle Type: ");
                            scanf("%s", Type_of_the_vehicle[z]);
                            printf("Enter your Vehicle Color: ");
                            scanf("%s", vehicleColor[z]);
                            printf("Enter your Contact Number: ");
                            scanf("%s", contactNumber[z]);

                            // This marks the parking slot z as taken (occupied).
                            slotTaken[z] = 1;
                            printf("Your Vehicle is parked at slot %d\n", z + 1);
                            // car sucessfull parked
                            parked = 1;
                        }
                    }
                }
            }

            // After checking all slots, if parked is still 0, it means no free and no suitable slot was found.
            if (parked == 0) {
                printf("=============================================\n");
                printf("\nNo suitable parking slots are available at the moment.");
                printf("\nWe apologize for the inconvenience. Please try again later.");
                printf("\n=============================================");
            }
        }

        // choice 2

        else if (choice == 2) {
            // will store plate number by  the user
            char plate[20];
            // to check if car is found or not
            int no_plate_found = 0;

            printf("Kindly enter the vehicle's plate number for removal: ");
            scanf("%s", plate);

            // to check slot one by one
            for (z = 0; z < 20; z++) {

                // Is the slot occupied (slotTaken[z] == 1)
                // Hav'nt remove car yet no_plate == 0
                if (slotTaken[z] == 1 && no_plate_found == 0){
                    // check character by cahracter
                    int i = 0;
                    int match = 1; // assume match

                    // to check the sotred plate and the enter plate num by user
                    for (i = 0; i < 20; i++) {

                        if (plate[i] != plateNumber[z][i]) {
                            match = 0; // characters differ
                        }
                        if (plate[i] == 0 && plateNumber[z][i] == 0) {
                           
                            i = 20;
                        }
                    }

                    //  the plate matches
                    if (match == 1) {
                        printf("Enter Time Out (e.g: 13:00): ");
                        scanf("%s", timeOut[z]);

                        slotTaken[z] = 0;
                        printf("Vehicle with plate %s removed from slot %d\n", plate, z + 1);
                        printf("Time In: %s | Time Out: %s\n", timeIn[z], timeOut[z]);

                        no_plate_found = 1; // mark as found to stop further checks
                    }
                }
            }

            // file section  (append)
            FILE *fptr;
            fptr = fopen("removal.csv", "a");
            fprintf(fptr, "\nPlate Number : %s,Slot %d", plate, z + 1);
            fclose(fptr);

            // If the vehicle was not found in any slot, print a message .
            if (no_plate_found == 0)
            {
                printf("Vehicle not found.\n");
            }
        }

        // choice 3

        else if (choice == 3)
        {
            printf("\n--- Parking Slots Reports ---\n");
            for (z = 0; z < 20; z++)
            {
                printf("Slot %d ", z + 1);

                if (Handicap[z] == 1)
                {
                    printf("Handicap: ");
                }

                else
                {
                    printf("Normal: ");
                }

                if (slotTaken[z] == 1)
                {
                    printf("Taken | Plate: %s | Type: %s | Color: %s | Contact: %s | Time In: %s\n", plateNumber[z], Type_of_the_vehicle[z], vehicleColor[z], contactNumber[z], timeIn[z]);
                }

                else{
                    printf("\nEmpty");
                }
            }
        }

        // choice 4
        else if (choice == 4) {
            printf("\nSystem is shutting down. Goodbye!");
        }

        else{
            printf("\nInvalid  Selection, Select a valid option.");
        }
    }

    return 0;
}