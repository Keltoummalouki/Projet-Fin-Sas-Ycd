#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

    // Colors code
    #define BBLK "\e[1;30m"
    #define BRED "\e[1;31m"
    #define BGRN "\e[1;32m"
    #define BYEL "\e[1;33m"
    #define BBLU "\e[1;34m"
    #define Rest "\e[0m"

    #define MAX_RESERVATIONS 100 //Max des reservations

    struct Reservation //Structure de Reservation
    {
        int ID;
        char LastName[100];
        char FirstName[100];
        long PhoneNumber;
        int Age;
        char Statut[20];
        char Date[11];
    };

    struct Reservation reservations[MAX_RESERVATIONS];
    int RSC = 0;  // Reservations count
    int currentID = 1; 

    
    void ClearBuffer() // clear input buffer
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    
    int VDI(int min, int max) // Validate integer input
    {
        int input;
        while (scanf("%d", &input) != 1 || input < min || input > max)
        {
            printf(BRED "Erreur: Entrez un nombre valide entre %d et %d.\n" Rest, min, max);
            ClearBuffer();
            printf(BYEL"Reessayez : "Rest);
        }
        ClearBuffer();
        return input;
    }

    
    long VPN() // Validate phone number
    {
        long phone;
        while (scanf("%ld", &phone) != 1 || phone < 600000000 || phone > 699999999 && phone < 700000000 || phone > 799999999)
        {
            printf(BRED "Erreur: Le numero  est invalide .\n" Rest);
            ClearBuffer();
            printf(BYEL"Reessayez :\e[0m +212 ");
        }
        ClearBuffer();
        return phone;
    }

    
    void VDate(char *date) // Validate date format
    {
        int day, month, year;

        while (true) // Continue until a valid date is entered
        {
            printf("Entrez la date (DD/MM/YYYY) : ");
            if (scanf("%2d/%2d/%4d", &day, &month, &year) != 3) // Check for input format
            {
                printf(BRED "Erreur: Format invalide. Utilisez le format DD/MM/YYYY.\n" Rest);
                ClearBuffer(); 
                continue; // Retry the loop
            }
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2023 || year > 2100) // Validate day, month, and year
            {
                printf(BRED "Erreur: Date invalide. Veuillez entrer une date valide.\n" Rest);
                continue;
            }
            if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) // Specific months(30days)
            {
                printf(BRED "Erreur: Le mois %d ne peut pas avoir plus de 30 jours.\n" Rest, month);
                continue;
            }
            else if (month == 2) // February
            {
                bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                if (isLeap && day > 29)
                {
                    printf(BRED "Erreur: Le mois de Fevrier d'une annee bissextile a seulement 29 jours.\n" Rest);
                    continue;
                }
                if (!isLeap && day > 28)
                {
                    printf(BRED "Erreur: Le mois de Fevrier a seulement 28 jours.\n" Rest);
                    continue;
                }
            }
        }

            
            sprintf(date, "%02d/%02d/%04d", day, month, year); //Store the date
            ClearBuffer(); // Clear input buffer after successful entry
            break; 
    }


    void Statuts(char *statut) // Reservation status
    {
        printf(BGRN "1 - Valide\n" Rest);
        printf(BYEL "2 - Reporte\n" Rest);
        printf(BRED "3 - Annule\n" Rest);
        printf(BBLU "4 - Traite\n" Rest);
        printf("Entrez le numero correspondant au statut : ");

        int choice = VDI(1, 4); //Get Validated IntInput

        switch (choice)
        {
            case 1:
                strcpy(statut, "valide");
                break;
            case 2:
                strcpy(statut, "reporte");
                break;
            case 3:
                strcpy(statut, "annule");
                break;
            case 4:
                strcpy(statut, "traite");
                break;
        }
    }

    void TestData() //Data test
    {
        const char *FirstNames[] = {"Keltoum", "Marwa", "Salma", "Aya", "Zinb", "Sara", "Anass", "Othmane", "Mohamed", "Ali"};
        const char *LastNames[] = {"Bensalem", "ElMouradi", "Fekhar", "Almofakir", "Ouazzani", "Benzakour", "Alaoui", "El Yousfi", "Belkadi", "El Idrissi"};
        long phoneNumbers[] = {623456789, 623456788, 687654321, 611111111, 622222222, 633333333, 663333333, 633233333, 633322333, 633353339};
        int ages[] = {18, 9, 15, 20, 54, 43, 22, 15, 18, 12};
        const char *statuts[] = {"valide", "reporte", "annule", "traite", "valide", "annule", "valide", "reporte", "traite", "valide"};
        const char *date[] = {"22/06/2024", "01/01/2024", "07/07/2024", "27/02/2024", "18/08/2024", "03/03/2024", "15/07/2024", "26/02/2024", "01/08/2024", "20/07/2024"};

        for (int i = 0; i < 10; i++)
        {
            reservations[i].ID = currentID++;
            strcpy(reservations[i].FirstName, FirstNames[i]);
            strcpy(reservations[i].LastName, LastNames[i]);
            reservations[i].PhoneNumber = phoneNumbers[i];
            reservations[i].Age = ages[i];
            strcpy(reservations[i].Statut, statuts[i]);
            strcpy(reservations[i].Date, date[i]);
            RSC++;
        }
    }

    
    bool PNE(long PhoneNumber) // Function to check if phone number already exists
    {
        for (int i = 0; i < RSC; i++)
        {
            if (reservations[i].PhoneNumber == PhoneNumber)
            {
                return true;
            }
        }
        return false;
    }
    void Add() // Add a new reservation
    {
        if (RSC < MAX_RESERVATIONS)
        {
            struct Reservation NewRS; // New reservation
            NewRS.ID = currentID++;

            printf(BBLU "\n---------- Ajouter une reservation ----------\n" Rest);

            printf("Entrez le prenom : ");
            scanf("%s", NewRS.FirstName);
            printf("Entrez le nom : ");
            scanf("%s", NewRS.LastName);
            printf("Entrez le numero de telephone : +212 ");
            NewRS.PhoneNumber = VPN();

            if (PNE(NewRS.PhoneNumber))
            {
                printf(BRED "\nErreur : Ce numero de telephone existe deja.\n" Rest);
                return;
            }

            printf("Entrez l'age : ");
            NewRS.Age = VDI(0, 99); 

            Statuts(NewRS.Statut);

            
            VDate(NewRS.Date);

            
            reservations[RSC++] = NewRS; // Add new reservation to array
            printf(BGRN "\nReservation ajoutee avec succes!\n" Rest);
        }
        else
        {
            printf(BRED "\nErreur : Nombre maximal de reservations atteint.\n" Rest);
        }
    }
    void ModifyOrDelete()
    {
        int ID;
        printf("\nEntrez l'ID de la reservation a modifier ou supprimer : ");
        scanf("%d", &ID);

        for (int i = 0; i < RSC; i++) 
        {
            if (reservations[i].ID == ID) 
            {
                int choiceMD;
                printf(BGRN "1 - Modifier\n" Rest);
                printf(BYEL "2 - Supprimer\n" Rest);
                printf("Entrez votre choix : ");

                while (scanf("%d", &choiceMD) != 1 || (choiceMD != 1 && choiceMD != 2))
                {
                    printf(BRED "Choix invalide. Entrez 1 pour Modifier ou 2 pour Supprimer.\n" Rest);
                    ClearBuffer();
                    printf("Reessayez : ");
                }
                ClearBuffer(); 

                if (choiceMD == 1) // Modify reservation
                {
                    printf("\n---------- Modifier les informations ----------\n");

                    printf("Entrez le nouveau prenom : ");
                    scanf("%s", reservations[i].FirstName);

                    printf("Entrez le nouveau nom : ");
                    scanf("%s", reservations[i].LastName);

                    printf("Entrez le nouveau numero de telephone : +212 ");
                    reservations[i].PhoneNumber = VPN(); 

                    printf("Entrez le nouvel age : ");
                    reservations[i].Age = VDI(0, 120); 

                    Statuts(reservations[i].Statut); 

                    VDate(reservations[i].Date); 

                    printf(BGRN "\nLes informations de la reservation ont ete modifiees avec succes !\n" Rest);
                } 
                else if (choiceMD == 2) // Delete reservation
                {
                    for (int j = i; j < RSC - 1; j++)
                    {
                        reservations[j] = reservations[j + 1];
                    }
                    RSC--; 
                    printf(BGRN "\nLa reservation a ete supprimee avec succes !\n" Rest);
                }
                return; 
            }
        }
        printf(BRED "Aucune reservation trouvee avec cet ID.\n" Rest);
    }

    void DisplayAll()
    {
            if (RSC == 0) 
            {
                printf(BRED"\nAucune reservation n'a ete trouvee.\n"Rest);
            } 
            else 
            {
                printf(BYEL"--------------------------------------------------------------------------------------------------------------------------\n"Rest);
                printf(BYEL"| ID | Nom\t        | Prenom           | Telephone\t\t      | Age  \e[1;33m| Statut      | Date de Reservation          |\n"Rest);
                printf(BYEL"--------------------------------------------------------------------------------------------------------------------------\n"Rest);
                for (int i = 0; i < RSC ; i++) 
                {
                printf("\e[1;33m|\e[0m %-2d \e[1;33m|\e[0m %-10s       \e[1;33m|\e[0m %-10s       \e[1;33m|\e[0m +212 %9ld           \e[1;33m|\e[0m %-3d  \e[1;33m|\e[0m %-8s    \e[1;33m|\e[0m %-8s                   \e[1;33m|\e[0m\n", 
                        reservations[i].ID, reservations[i].LastName, reservations[i].FirstName, reservations[i].PhoneNumber, reservations[i].Age, reservations[i].Statut , reservations[i].Date);
                printf(BYEL"--------------------------------------------------------------------------------------------------------------------------\n"Rest);
                }
            }
    }


    void Display()
    {
        int choice;
        
        printf("Choisissez une option:\n");
        printf("1. Afficher tous les details des reservations\n");
        printf("2. Afficher les details d'une reservation specifique\n");
        printf("Entrez votre choix (1 ou 2): ");
        scanf("%d", &choice);
        
        if (choice == 1) 
        {
            DisplayAll();
        } 
        else if (choice == 2) 
        {
            int id;
            printf("Entrez l'ID de la reservation: ");
            scanf("%d", &id);
            
            int found = 0; // To track if the reservation is found
            for (int i = 0; i < RSC; i++) 
            {
                if (reservations[i].ID == id)
                {
                    found = 1;
                    printf(BYEL "---------- Details de la reservation ----------\n" Rest);
                    printf("ID: %d\n", reservations[i].ID);
                    printf("Nom: %s\n", reservations[i].LastName);
                    printf("Prenom: %s\n", reservations[i].FirstName);
                    printf("Telephone: +212%ld\n", reservations[i].PhoneNumber);
                    printf("Age: %d\n", reservations[i].Age);
                    printf("Statut: %s\n", reservations[i].Statut);
                    printf("Date de reservation: %s\n", reservations[i].Date);
                    printf("------------------------------------------\n");
                    break;
                }
            }
            
            if (!found)
            {
                printf("Aucune reservation trouvee avec l'ID %d.\n", id);
            }
        } 
        else 
        {
            printf("Choix invalide. Veuillez entrer 1 ou 2.\n");
        }
    }

    void Sort() //Bubble sort
    {
        int choice;
        printf("1 - Trier par nom\n" );
        printf("2 - Trier par statut\n");
        printf(BBLU "Entrez votre choix : " Rest);
        choice = VDI(1, 2);

        if (choice == 1) // Sort by Last Name
        {
            for (int i = 0; i < RSC - 1; i++) 
            {
                for (int j = i + 1; j < RSC; j++) 
                {
                    if (strcmp(reservations[i].LastName, reservations[j].LastName) > 0) 
                    {
                        struct Reservation temp = reservations[i];
                        reservations[i] = reservations[j];
                        reservations[j] = temp;
                    }
                }
            }
            printf(BGRN "Reservations triees par nom avec succes !\n" Rest);
        } 
        else if (choice == 2) // Sort by Status
        {
            for (int i = 0; i < RSC - 1; i++) 
            {
                for (int j = i + 1; j < RSC; j++) 
                {
                    if (strcmp(reservations[i].Statut, reservations[j].Statut) > 0) 
                    {
                        struct Reservation temp = reservations[i];
                        reservations[i] = reservations[j];
                        reservations[j] = temp;
                    }
                }
            }
            printf(BGRN "Reservations triees par statut avec succes !\n" Rest);
        }
        
        DisplayAll();
    }


    void Search()
    {
        int choice;
        printf("1 - Rechercher par ID\n");
        printf("2 - Rechercher par nom\n");
        printf(BBLU "Entrez votre choix : " Rest);
        choice = VDI(1, 2);

        if (choice == 1) // Search for the reservation with the given ID
        {
            int ID;
            printf("Entrez la reference de la reservation a rechercher : ");
            scanf("%d", &ID);
            for (int i = 0; i < RSC; i++) 
            {
                if (reservations[i].ID == ID) 
                {
                    printf(BYEL"\n---------- Details de la reservation ----------\n"Rest);
                    printf("Nom: %s\n", reservations[i].LastName);
                    printf("Prenom: %s\n", reservations[i].FirstName);
                    printf("Telephone: +212%ld\n", reservations[i].PhoneNumber);
                    printf("Age: %d\n", reservations[i].Age);
                    printf("Statut: %s\n", reservations[i].Statut);
                    printf("Date de reservation: %s\n", reservations[i].Date);
                    return;
                }
            }
            printf(BRED "Aucune reservation trouvee avec cet ID.\n" Rest);
        } 
        else if (choice == 2) // Search for the reservation with the given last name
        {
            char lastName[100];
            printf("Entrez le nom de la reservation a rechercher : ");
            scanf("%s", lastName);
            bool found = false; 
            for (int i = 0; i < RSC; i++) 
            {
                if (strcasecmp(reservations[i].LastName, lastName) == 0) // case insensitive comparison
                {
                    printf(BYEL"\n---------- Details de la reservation ----------\n"Rest);
                    printf("ID: %d\n", reservations[i].ID);
                    printf("Nom: %s\n", reservations[i].LastName);
                    printf("Prenom: %s\n", reservations[i].FirstName);
                    printf("Telephone: +212%ld\n", reservations[i].PhoneNumber);
                    printf("Age: %d\n", reservations[i].Age);
                    printf("Statut: %s\n", reservations[i].Statut);
                    printf("Date de reservation: %s\n", reservations[i].Date);
                    found = true;
                }
            }

            if (!found) 
            {
                printf(BRED "Aucune reservation trouvee avec ce nom.\n" Rest);
            }
        }
    }

    void Statistics() 
    {
        if (RSC == 0) 
        {
            printf(BRED "Aucune reservation disponible pour les statistiques.\n" Rest);
            return;
        }
        int sommeAge = 0;
        int ReservationsMoins18 = 0, Reservations19_35 = 0, Reservations36Plus = 0;
        int valideCount = 0, reporteCount = 0, annuleCount = 0, traiteCount = 0;
        for (int i = 0; i < RSC; i++) 
        {
            sommeAge += reservations[i].Age;

            // Age statistics
            if (reservations[i].Age < 19) 
            {
                ReservationsMoins18++;
            } 
            else if (reservations[i].Age <= 35) 
            {
                Reservations19_35++;
            } 
            else 
            {
                Reservations36Plus++;
            }

            // Status statistics
            if (strcmp(reservations[i].Statut, "valide") == 0) 
            {
                valideCount++;
            } 
            else if (strcmp(reservations[i].Statut, "reporte") == 0) 
            {
                reporteCount++;
            } 
            else if (strcmp(reservations[i].Statut, "annule") == 0) 
            {
                annuleCount++;
            } 
            else if (strcmp(reservations[i].Statut, "traite") == 0) 
            {
                traiteCount++;
            }
        }

        // Calculate and display average age
        float moyenneAge = (float)sommeAge / RSC;
        printf(BBLU "\n---------- Statistiques d'age ----------\n" Rest);
        printf("Moyenne d'age des patients: %.2f\n", moyenneAge);
        printf("Nombre de patients 0-18 ans: %d\n", ReservationsMoins18);
        printf("Nombre de patients 19-35 ans: %d\n", Reservations19_35);
        printf("Nombre de patients 36+ ans: %d\n", Reservations36Plus);

        // Display status statistics
        printf(BBLU "\n---------- Statistiques de statut ----------\n" Rest);
        printf("Nombre de reservations 'valide': %d\n", valideCount);
        printf("Nombre de reservations 'reporte': %d\n", reporteCount);
        printf("Nombre de reservations 'annule': %d\n", annuleCount);
        printf("Nombre de reservations 'traite': %d\n", traiteCount);
    }

    void Menu()
    {
        int choice;
        do 
        {
            printf(BBLU "\n---------- Gestion des reservations ----------\n" Rest);
            printf("1 - Ajouter une reservation\n");
            printf("2 - Modifier ou supprimer une reservation\n");
            printf("3 - Afficher les details d'une reservation\n");
            printf("4 - Tri des reservations\n");
            printf("5 - Recherche des reservations\n");
            printf("6 - Statistiques\n");
            printf("7 - Quitter\n");
            printf(BBLU "Entrez votre choix : " Rest);
            choice = VDI(1, 7); // Get Validated IntInput

            switch (choice)
            {
                case 1:
                    Add();
                    break;
                case 2:
                    ModifyOrDelete();
                    break;
                case 3:
                    Display();
                    break;
                case 4:
                    Sort();
                    break;
                case 5:
                    Search();
                    break;
                case 6:
                    Statistics();
                    break;
                case 7:
                    printf(BGRN "Au revoir!\n" Rest);
                    break;
            }
        } while (choice != 7);
    }

    int main()
    {
        TestData();
        Menu();
        return 0;
    }