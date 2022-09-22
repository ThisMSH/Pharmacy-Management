#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct registering_date
{
    int sec;
    int min;
    int hour;
    int day;
    int month;
    int year;
}da;

typedef struct product_details
{
    long long int code;
    char name[50];
    int quantity;
    float price;
    int sold;
    float priceTax;
    da date;
    float totalPriceTax;
}product;

void sortingPrice (product* stock, int nn);
void sortingAlph (product* stock, int nn);
void sortingTotalPrice (product* stock, int nn);
int search (product* stock, int nn, long long int code);

int main () {
    int menu, p = 0, o, nn, lk, amount;
    long long int cd;
    char enter;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    product* stock = (product*) malloc(sizeof(product));

    if (stock == NULL) {
        printf("Error! Memory not allocated.");
        sleep(3);
        exit(0);
    }
    
    system("color 2");
    system("cls");
    printf("|=======================================================================================================================|\n");
    printf("|             -*-                                                                                                       |\n");
    printf("|        $$$$/  .($$$$                                                                        _________________________ |\n");
    printf("|    $$#               $$*           _____  _                                                /                         /|\n");
    printf("|  #$       ($$$$$       .$,        |  __ \\| |                                               /             -           /|\n");
    printf("| $$        ($$$$$         $$       | |__) | |__   __ _ _ __ _ __ ___   __ _  ___ _   _      /         #########       /|\n");
    printf("|,$   .$$$$$$$$$$$$$$$$$    $       |  ___/| '_ \\ / _` | '__| '_ ` _ \\ / _` |/ __| | | |     /      #####       `      /|\n");
    printf("|$$   .$$$$$$$$$$$$$$$$$    $$      | |    | | | | (_| | |  | | | | | | (_| | (__| |_| |     /     ####                /|\n");
    printf("|.$   .$$$$$$$$$$$$$$$$$    $       |_|    |_| |_|\\__,_|_|  |_| |_| |_|\\__,_|\\___|\\__, |     /     ####                /|\n");
    printf("| $$        ($$$$$         $$                                                      __/ |     /     ####                /|\n");
    printf("|  /$       ($$$$$       *$                                                       |___/      /      ####.        .     /|\n");
    printf("|    /$#               $$                                                                    /        ###########      /|\n");
    printf("|        $$$$$/*/$$$$$                                                                       /            ----         /|\n");
    printf("|              -                                                                             /_________________________/|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|        __  __                                                   _     _____                                           |\n");
    printf("|       |  \\/  |                                                 | |   |  __ \\                                          |\n");
    printf("|       | \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_  | |__) | __ ___   __ _ _ __ __ _ _ __ ___        |\n");
    printf("|       | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __| |  ___/ '__/ _ \\ / _` | '__/ _` | '_ ` _ \\       |\n");
    printf("|       | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_  | |   | | | (_) | (_| | | | (_| | | | | | |      |\n");
    printf("|       |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |_|   |_|  \\___/ \\__, |_|  \\__,_|_| |_| |_|      |\n");
    printf("|                                  __/ |                                                 __/ |                          |\n");
    printf("|                                 |___/                                                 |___/                           |\n");
    printf("|=======================================================================================================================|\n");
    sleep(3);
    system("cls");
    system("color F");
    do
    {
        printf("|============================================[ Pharmacy Management Program ]============================================|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 1 - Add a new product.\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 2 - Add multiple new products.\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 3 - Show list of all products.\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 4 - Buy a product.\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 5 - Search for a product.\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 6 - Stock status.\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 7 - Add an existing product.\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 8 - Delete a product.\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 9 - Show the statistics.\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t# 0 - Quit the program.\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|=======================================================================================================================|\n\n");
        scanf("%d", &menu);
        system("cls");

        switch (menu)
        {
        case 1: // Adding one new product
            stock = realloc(stock, (p + 1) * sizeof(product));
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("| ( Registering a new product )-----------------------------------------------------------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("  Enter the code of the product: ");
            fflush(stdin);
            scanf("%lld", &stock[p].code);
            printf("  Enter the name of the product: ");
            fflush(stdin);
            scanf("%[^\n]s", stock[p].name);
            printf("  Enter the quantity of the product: ");
            fflush(stdin);
            scanf("%d", &stock[p].quantity);
            printf("  Enter the price of the product: ");
            fflush(stdin);
            scanf("%f", &stock[p].price);
            stock[p].sold = 0;
            stock[p].priceTax = stock[p].price + stock[p].price * 0.15;
            p++;
            printf("| Product was successfully added to the program!\t\t\t\t\t\t\t\t\t|\n");
            sleep(1);
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;
            
        case 2: ; // Adding multiple new product
            int n = 0, count = 0;
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("| ( Registering new products )------------------------------------------------------------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("  Enter the amount of products that you want to add: ");
            scanf("%d", &n);
            printf("\n");
            n += p;
            stock = realloc(stock, n * sizeof(product));
            for (p; p < n; p++)
            {
                count++;
                printf("|.................................................... Product N: %02d ....................................................|\n", count);
                printf("  Enter the code of the product: ");
                fflush(stdin);
                scanf("%lld", &stock[p].code);
                printf("  Enter the name of the product: ");
                fflush(stdin);
                scanf("%[^\n]s", stock[p].name);
                printf("  Enter the quantity of the product: ");
                fflush(stdin);
                scanf("%d", &stock[p].quantity);
                printf("  Enter the price of the product: ");
                fflush(stdin);
                scanf("%f", &stock[p].price);
                stock[p].sold = 0;
                stock[p].priceTax = stock[p].price + stock[p].price * 0.15;
                printf("\n");
            }
            printf("| All product were successfully added to the program!\t\t\t\t\t\t\t\t\t|\n");
            sleep(1);
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;
        
        case 3: ; // List of products in order
            nn = p;
            do
            {
                sortingAlph (stock, nn);
                printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                printf("| ( Display the list of products in ascending alphabetical order )------------------------------------------------------|\n");
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|_________ Code _______________ Name /\\ _____________ Quantity ________________ Price _____________ Price + Tax ________|\n");
                for (int j = 0; j < p; j++) {
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("# %d\t   %lld\n", j + 1, stock[j].code);
                    printf("\t\t\t\t%s\n", stock[j].name);
                    printf("\t\t\t\t\t\t      %d\n", stock[j].quantity);
                    printf("\t\t\t\t\t\t\t\t\t\t%.2f\n", stock[j].price);
                    printf("\t\t\t\t\t\t\t\t\t\t\t\t    %.2f\n", stock[j].priceTax);
                    if (stock[j].sold > 0) {
                        printf("\tSold %d unit(s) of this product on %02d/%02d/%d, at %02d:%02d:%02d\n", stock[j].sold, stock[j].date.day, stock[j].date.month + 1, stock[j].date.year + 1900, stock[j].date.hour, stock[j].date.min, stock[j].date.sec);
                    }
                    printf("|_______________________________________________________________________________________________________________________|\n");
                }
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t1 - To show descending price order.\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                printf("|.......................................................................................................................|\n");
                scanf("%d", &o);
                system("cls");

                if ( o == 1) {
                    sortingPrice (stock, nn);
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( Display the list of products in descending price order )------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|_________ Code _______________ Name _____________ Quantity ________________ Price \\/ _____________ Price + Tax ________|\n");
                    for (int j = 0; j < p; j++) {
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("# %d\t   %lld\n", j + 1, stock[j].code);
                        printf("\t\t\t\t%s\n", stock[j].name);
                        printf("\t\t\t\t\t\t      %d\n", stock[j].quantity);
                        printf("\t\t\t\t\t\t\t\t\t\t%.2f\n", stock[j].price);
                        printf("\t\t\t\t\t\t\t\t\t\t\t\t    %.2f\n", stock[j].priceTax);
                        if (stock[j].sold > 0) {
                            printf("\tSold %d unit(s) of this product on %02d/%02d/%d, at %02d:%02d:%02d\n", stock[j].sold, stock[j].date.day, stock[j].date.month + 1, stock[j].date.year + 1900, stock[j].date.hour, stock[j].date.min, stock[j].date.sec);
                        }
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t1 - To show descending price order.\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                    printf("|.......................................................................................................................|\n");
                    scanf("%d", &o);
                    system("cls");
                }
                if (o != 0 && o != 1) {
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( List of products )--------------------------------------------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Please enter either 1 or 0.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|.......................................................................................................................|\n");
                    sleep(2);
                    system("cls");
                }
            } while (o != 0);
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;
        
        case 4: ; // buying product
            nn = p;
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("| ( Buying a product )--------------------------------------------------------------------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            do {
                printf("  Enter the code of the product sold: ");
                scanf("%lld", &cd);

                lk = search (stock, nn, cd);

                if (lk == -1) {
                    printf("| Product was not found!\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    sleep(1);
                }else {
                    printf("  Enter the quantity of the product sold: ");
                    scanf("%d", &amount);

                    if (stock[lk].quantity < amount) {
                        printf("| There is not enough quantity!\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        sleep(1);
                    }else {
                        stock[lk].sold += amount;
                        stock[lk].quantity -= amount;
                        stock[lk].date.sec = tm.tm_sec;
                        stock[lk].date.min = tm.tm_min;
                        stock[lk].date.hour = tm.tm_hour;
                        stock[lk].date.day = tm.tm_mday;
                        stock[lk].date.month = tm.tm_mon;
                        stock[lk].date.year = tm.tm_year;
                        printf("| Product sold was successfully registered!\t\t\t\t\t\t\t\t\t\t|\n");
                    }
                }
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t1 - To sell another product.\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                printf("|.......................................................................................................................|\n");
                scanf("%d", &o);
                if (o != 0 && o != 1) {  // test
                    while (o != 0 && o != 1) {
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| Please enter either 1 or 0.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|.......................................................................................................................|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|\t\t\t\t\t1 - To sell another product.\t\t\t\t\t\t\t|\n");
                        printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                        printf("|.......................................................................................................................|\n");
                        scanf("%d", &o);
                    }
                }
            } while (o != 0);
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;

        case 5: ; // searching for a product
            nn = p;
            do
            {
                printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                printf("| ( Searching for products )--------------------------------------------------------------------------------------------|\n");
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t1 - To search for a product using code.\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t2 - To search for products using quantity.\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                printf("|.......................................................................................................................|\n");
                scanf("%d", &o);
                if (o == 1) {
                    printf("  Enter the code of the product: ");
                    scanf("%lld", &cd);

                    lk = search (stock, nn, cd);
                    
                    if (lk == -1)
                    {
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| No product was found with this code!\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                        sleep(2);
                    }else {
                        printf("|_______________________________________________________________________________________________________________________|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("  Product's code:\t\t \"%lld\"\n", stock[lk].code);
                        printf("  Product's name:\t\t %s\n", stock[lk].name);
                        printf("  Product's quantity:\t\t %d\n", stock[lk].quantity);
                        printf("  Product's price including tax: %.2f\n", stock[lk].priceTax);
                        printf("|_______________________________________________________________________________________________________________________|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| Press Enter to continue.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        fflush(stdin);
                        scanf("%c", &enter);
                    }
                }else if (o == 2) {
                    printf("  Enter the quantity that you are looking for: ");
                    scanf("%d", &amount);
                    int cnt = 0;

                    for (int i = 0; i < nn; i++)
                    {
                        if (stock[i].quantity == amount) {
                            printf("|_______________________________________________________________________________________________________________________|\n");
                            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                            printf("  Product's code:\t\t %lld\n", stock[i].code);
                            printf("  Product's name:\t\t %s\n", stock[i].name);
                            printf("  Product's quantity:\t\t \"%d\"\n", stock[i].quantity);
                            printf("  Product's price including tax: %.2f\n", stock[i].priceTax);
                            cnt++;
                        }
                    }
                    if (cnt == 0) {
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| No product was found with this quantity!\t\t\t\t\t\t\t\t\t\t|\n");
                    }
                    printf("|_______________________________________________________________________________________________________________________|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Press Enter to continue.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    fflush(stdin);
                    scanf("%c", &enter);
                }else if (o != 0 && o != 1) {
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Please choose from option 0 to 2.\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|.......................................................................................................................|\n");
                    sleep(2);
                }
                system("cls");
            } while (o != 0);
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("| ( Searching for products )--------------------------------------------------------------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;

        case 6: ; // Stock status
            nn = p;
            int count2 = 0;
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("| ( Stock status )------------------------------------------------------------------------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| List of products with quantity below 3................................................................................|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|_________ Code ________________ Name ______________ Price + Tax _________________ Quantity ______________ Sold ________|\n");
            for (int i = 0; i < nn; i++)
            {
                if (stock[i].quantity < 3)
                {
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t   %lld\n", stock[i].code);
                    printf("\t\t\t\t %s\n", stock[i].name);
                    printf("\t\t\t\t\t\t     %.2f\n", stock[i].priceTax);
                    printf("\t\t\t\t\t\t\t\t\t\t   %d\n", stock[i].quantity);
                    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t   %d\n", stock[i].sold);
                    printf("|_______________________________________________________________________________________________________________________|\n");
                    count2 = 1;
                }
            }
            if (count2 == 0) {
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("| No product was found below the quantity of 3.\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|_______________________________________________________________________________________________________________________|\n");
            }
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Press Enter to continue.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            fflush(stdin);
            scanf("%c", &enter);
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;

        case 7: ; // Stock update
            nn = p;
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("| ( Updating products quantity )----------------------------------------------------------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            do {
                printf("  Enter the code of the product: ");
                scanf("%lld", &cd);

                lk = search (stock, nn, cd);

                if (lk == -1) {
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| No product was found with this code!\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|_______________________________________________________________________________________________________________________|\n");
                    sleep(1);
                }else {
                    printf("  Enter the quantity of the product: ");
                    scanf("%d", &amount);
                    stock[lk].quantity += amount;
                    sleep(1);
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Product's quantity was successfully updated!\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|_______________________________________________________________________________________________________________________|\n");
                }
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t1 - To update another product's quantity.\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                printf("|.......................................................................................................................|\n");
                scanf("%d", &o);
                if (o != 0 && o != 1) {  // test
                    while (o != 0 && o != 1) {
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| Please enter either 1 or 0.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|.......................................................................................................................|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|\t\t\t\t\t1 - To update another product's quantity.\t\t\t\t\t|\n");
                        printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                        printf("|.......................................................................................................................|\n");
                        scanf("%d", &o);
                    }
                }
                
            } while (o != 0);
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;

        case 8: // deleting a product
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("| ( Deleting products )-------------------------------------------------------------------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            do {
                char confirm;
                printf("  Enter the code of the product: ");
                scanf("%lld", &cd);

                lk = search (stock, nn, cd);

                if (lk == -1) {
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| No product was found with this code!\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|_______________________________________________________________________________________________________________________|\n");
                    sleep(1);
                }else {
                    printf("|#######################################################################################################################|\n");
                    printf("  Product's code:\t\t %lld\n", stock[lk].code);
                    printf("  Product's name:\t\t %s\n", stock[lk].name);
                    printf("  Product's quantity:\t\t %d\n", stock[lk].quantity);
                    printf("  Product's price including tax: %.2f\n", stock[lk].priceTax);
                    printf("  Quantity of the product sold:  %d\n", stock[lk].sold);
                    printf("|#######################################################################################################################|\n");
                    printf("| Are you sure that you want to delete this product?\t\t\t\t\t\t\t\t\t|\n");
                    printf("| (Enter y/Y to confirm, enter any other character to skip)\t\t\t\t\t\t\t\t|\n");
                    fflush(stdin);
                    scanf("%c", &confirm);
                    if (confirm == 'y' || confirm == 'Y') {
                        for (int i = lk; i < p; i++)
                        {
                            stock[i] = stock[i + 1];
                        }
                        p--;
                        stock = realloc(stock, (p + 1) * sizeof(product));
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| The product was successfully removed.\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                        sleep(1);
                    }
                }
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t1 - To delete another product.\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                printf("|.......................................................................................................................|\n");
                scanf("%d", &o);
                if (o != 0 && o != 1) {  // test
                    while (o != 0 && o != 1) {
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| Please enter either 1 or 0.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|.......................................................................................................................|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|\t\t\t\t\t1 - To delete another product.\t\t\t\t\t\t\t|\n");
                        printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                        printf("|.......................................................................................................................|\n");
                        scanf("%d", &o);
                    }
                }
            } while (o != 0);
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(1);
            system("cls");
            break;

        case 9: ; // Statictics
            float S = 0, avr;
            int count3 = 0;
            for (int i = 0; i < p; i++)
            {
                stock[i].totalPriceTax = stock[i].priceTax * stock[i].sold;
            }
            
            do
            {
                printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                printf("| ( Sales statistics )--------------------------------------------------------------------------------------------------|\n");
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t1 - Display total prices of products sold today.\t\t\t\t|\n");
                printf("|\t\t\t\t\t2 - Display average price of products sold today.\t\t\t\t|\n");
                printf("|\t\t\t\t\t3 - Display maximum price of products sold today.\t\t\t\t|\n");
                printf("|\t\t\t\t\t4 - Display minimum price of products sold today.\t\t\t\t|\n");
                printf("|\t\t\t\t\t0 - To go back to main menu.\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|.......................................................................................................................|\n");
                fflush(stdin);
                scanf("%d", &o);
                system("cls");
                switch (o)
                {
                case 1: // Total prices
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( Sales statistics )--------------------------------------------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|__ Code _____________ Name _____________ Quantity Sold ____ Quantity Left ______ Unit Price* ________ Total Price* ____|\n");
                    for (int i = 0; i < p; i++)
                    {
                        if (stock[i].sold > 0)
                        {
                            printf("    %lld\n", stock[i].code);
                            printf("\t\t       %s\n", stock[i].name);
                            printf("\t\t\t\t\t  %d\n", stock[i].sold);
                            printf("\t\t\t\t\t\t\t     %d\n", stock[i].quantity);
                            printf("\t\t\t\t\t\t\t\t\t\t  %.2f\n", stock[i].priceTax);
                            printf("\t\t\t\t\t\t\t\t\t\t\t\t       %.2f\n", stock[i].totalPriceTax);
                            printf("|_______________________________________________________________________________________________________________________|\n");
                            S += stock[i].totalPriceTax;
                            count3++;
                        }
                    }
                    if (count3 > 0) {
                        printf("| Total price of all products sold:.....................................................................................|\n");
                        printf("\t\t\t\t\t\t\t\t\t\t\t\tTotal: %.2f\n", S);
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| *All taxes are included.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }else {
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| No product sold today.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }
                    S = 0;
                    count3 = 0;
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Press Enter to continue.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    fflush(stdin);
                    scanf("%c", &enter);
                    system("cls");
                    break;
                
                case 2: // Average price
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( Sales statistics )--------------------------------------------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    for (int i = 0; i < p; i++)
                    {
                        if (stock[i].sold > 0)
                        {
                            S += stock[i].totalPriceTax;
                            count3++;
                        }
                    }
                    if (count3 > 0) {
                        avr = S / count3;
                        printf("| Average price of all products sold:...................................................................................|\n");
                        printf("\t\t\t\t\t\t\t\t\t\t\t      Average: %.2f\n", avr);
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| All taxes are included.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }else {
                        printf("| Average price of all products sold:...................................................................................|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| No product sold today.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }
                    avr = 0;
                    S = 0;
                    count3 = 0;
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Press Enter to continue.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    fflush(stdin);
                    scanf("%c", &enter);
                    system("cls");
                    break;
                
                case 3: ; // Max price
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( Sales statistics )--------------------------------------------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    nn = p;
                    sortingTotalPrice(stock, nn);
                    for (int i = 0; i < p; i++)
                    {
                        if (stock[i].sold > 0)
                        {
                            count3 = 1;
                            break;
                        }
                    }
                    if (count3 == 1) {
                        printf("| Maximum total price of products sold:.................................................................................|\n");
                        printf("\t\t\t\t\t\t\t\t\t\t\t\tTotal: %.2f\n", stock[0].totalPriceTax);
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| Product information:..................................................................................................|\n");
                        printf("|__ Code _____________ Name _____________ Quantity Sold ____ Quantity Left ______ Unit Price* ________ Total Price* ____|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("    %lld\n", stock[0].code);
                        printf("\t\t       %s\n", stock[0].name);
                        printf("\t\t\t\t\t  %d\n", stock[0].sold);
                        printf("\t\t\t\t\t\t\t     %d\n", stock[0].quantity);
                        printf("\t\t\t\t\t\t\t\t\t\t  %.2f\n", stock[0].priceTax);
                        printf("\t\t\t\t\t\t\t\t\t\t\t\t       %.2f\n", stock[0].totalPriceTax);
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }else {
                        printf("| Maximum total price of products sold:.................................................................................|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| No product sold today.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }
                    count3 = 0;
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Press Enter to continue.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    fflush(stdin);
                    scanf("%c", &enter);
                    system("cls");
                    break;
                
                case 4: ; // Min price
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( Sales statistics )--------------------------------------------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    nn = p;
                    sortingTotalPrice(stock, nn);
                    for (int i = p - 1; i >= 0; i--)
                    {
                        if (stock[i].sold > 0)
                        {
                            lk = i;
                            count3 = 1;
                            break;
                        }
                    }
                    if (count3 == 1) {
                        printf("| Minimum total price of products sold:.................................................................................|\n");
                        printf("\t\t\t\t\t\t\t\t\t\t\t\tTotal: %.2f\n", stock[lk].totalPriceTax);
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| Product information:..................................................................................................|\n");
                        printf("|__ Code _____________ Name _____________ Quantity Sold ____ Quantity Left ______ Unit Price* ________ Total Price* ____|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("    %lld\n", stock[lk].code);
                        printf("\t\t       %s\n", stock[lk].name);
                        printf("\t\t\t\t\t  %d\n", stock[lk].sold);
                        printf("\t\t\t\t\t\t\t     %d\n", stock[lk].quantity);
                        printf("\t\t\t\t\t\t\t\t\t\t  %.2f\n", stock[lk].priceTax);
                        printf("\t\t\t\t\t\t\t\t\t\t\t\t       %.2f\n", stock[lk].totalPriceTax);
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }else {
                        printf("| Minimum total price of products sold:.................................................................................|\n");
                        printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| No product sold today.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("|_______________________________________________________________________________________________________________________|\n");
                    }
                    count3 = 0;
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Press Enter to continue.\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    fflush(stdin);
                    scanf("%c", &enter);
                    system("cls");
                    break;

                case 0:
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( Sales statistics )--------------------------------------------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Going back to the main menu...\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|.......................................................................................................................|\n");
                    sleep(2);
                    system("cls");
                    break;

                default:
                    printf("|============================================[ Pharmacy Management Program ]============================================|\n");
                    printf("| ( Sales statistics )--------------------------------------------------------------------------------------------------|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("| Please choose from option 0 to 4.\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|.......................................................................................................................|\n");
                    sleep(2);
                    system("cls");
                    break;
                }
            } while (o != 0);
            break;

        case 0:
            system("color 9");
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t .--.        _  .-.  .-.  _                .-. .-.                                                       \t|\n");
            printf("|\t: ,. :      :_;.' `..' `.:_;              .' `.: :                                                       \t|\n");
            printf("|\t: :: :.-..-..-.`. .'`. .'.-.,-.,-. .--.   `. .': `-.  .--.   .---. .--.  .--.  .--. .--.  .--.  ,-.,-.,-.\t|\n");
            printf("|\t: :;_:: :; :: : : :  : : : :: ,. :' .; :   : : : .. :' '_.'  : .; `: ..'' .; :' .; :: ..'' .; ; : ,. ,. :\t|\n");
            printf("|\t`._:_;`.__.':_; :_;  :_; :_;:_;:_;`._. ;   :_; :_;:_;`.__.'  : ._.':_;  `.__.'`._. ;:_;  `.__,_;:_;:_;:_;\t|\n");
            printf("|\t                                   .-. :                     : :               .-. :                     \t|\n");
            printf("|\t                                   `._.'                     :_;               `._.'                     \t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t .--.                                                           .-.\t\t\t\t|\n");
            printf("|\t\t\t: .--'                                                          : :\t\t\t\t|\n");
            printf("|\t\t\t`. `.  .--.  .--.   .-..-. .--. .-..-.   .--.  .--.  .--. ,-.,-.: :\t\t\t\t|\n");
            printf("|\t\t\t _`, :' '_.'' '_.'  : :; :' .; :: :; :  `._-.'' .; :' .; :: ,. ::_;\t\t\t\t|\n");
            printf("|\t\t\t`.__.'`.__.'`.__.'  `._. ;`.__.'`.__.'  `.__.'`.__.'`.__.':_;:_;:_;\t\t\t\t|\n");
            printf("|\t\t\t                     .-. :                                         \t\t\t\t|\n");
            printf("|\t\t\t                     `._.'                                         \t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|=======================================================================================================================|\n");
            sleep(3);
            exit(0);
            break;

        default:
            printf("|============================================[ Pharmacy Management Program ]============================================|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("| Please choose from option 0 to 9.\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|.......................................................................................................................|\n");
            sleep(2);
            system("cls");
            break;
        
        }
    } while (menu != 0);

    return 0;
}

void sortingPrice (product* stock, int nn) { // Sorting prices in descending order
    product a;
    for (int i = 0; i < nn; i++)
    {
        int swap = 0;
        for (int j = 0; j < nn - 1 - i; j++)
        {
            if (stock[j].price < stock[j + 1].price)
            {
                a = stock[j];
                stock[j] = stock[j + 1];
                stock[j + 1] = a;
                swap = 1;
            }
        }
        if (swap == 0) {
            break;
        }
    }
}

void sortingAlph (product* stock, int nn) { // Sorting names in ascending order
    product a;
    for (int i = 0; i < nn; i++)
    {
        int swap = 0;
        for (int j = 0; j < nn - 1 - i; j++)
        {
            if (strcmp(stock[j].name,stock[j + 1].name) > 0)
            {
                a = stock[j];
                stock[j] = stock[j + 1];
                stock[j + 1] = a;
                swap = 1;
            }
        }
        if (swap == 0) {
            break;
        }
    }
}

void sortingTotalPrice (product* stock, int nn) { // Sorting by total price+tax of each product in descending order
    product a;
    for (int i = 0; i < nn; i++)
    {
        int swap = 0;
        for (int j = 0; j < nn - 1 - i; j++)
        {
            if (stock[j].totalPriceTax < stock[j + 1].totalPriceTax) {
                a = stock[j];
                stock[j] = stock[j + 1];
                stock[j + 1] = a;
                swap = 1;
            }
        }
        if (swap == 0) {
            break;
        }
    }
}

int search (product* stock, int nn, long long int cd) { // Searching for product by code
    int count = 0;
    for (int i = 0; i < nn; i++)
    {
        if (stock[i].code == cd) {
            return i;
            count++;
        }
    }
    if (count == 0) {
        return -1;
    }
}