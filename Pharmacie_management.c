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
int search (product* stock, int nn, long long int code);

int main () {
    int menu, p = 0, o, nn, lk, amount;
    long long int cd;
    char enter;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    product* stock = (product*) malloc(sizeof(product));
    //printf("Size of stock: %d\n", sizeof(product)); //delete

    if (stock == NULL) {
        printf("Error! Memory not allocated.");
        sleep(3);
        exit(0);
    }

    do
    {
        printf("|============================= Pharmacy Management =============================|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t1 - Add a new product.\t\t\t\t\t|\n");
        printf("|\t\t\t2 - Add multiple new products.\t\t\t\t|\n");
        printf("|\t\t\t3 - Show list of all products.\t\t\t\t|\n");
        printf("|\t\t\t4 - Buy a product.\t\t\t\t\t|\n");
        printf("|\t\t\t5 - Search for a product.\t\t\t\t|\n");
        printf("|\t\t\t6 - Stock status.\t\t\t\t\t|\n");
        printf("|\t\t\t7 - Add an existing product.\t\t\t\t|\n");
        printf("|\t\t\t8 - Delete a product.\t\t\t\t\t|\n");
        printf("|\t\t\t9 - Show the statistics.\t\t\t\t|\n");
        printf("|\t\t\t0 - Quit the program.\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|===============================================================================|\n");
        scanf("%d", &menu);

        system("cls");

        switch (menu)
        {
        case 1: // Adding one new product
            stock = realloc(stock, (p + 1) * sizeof(product));
            //printf("Size of stock: %d\n", sizeof(product)); //delete
            printf("|========================== Registering a new product ==========================|\n\n");
            printf("Enter the code of the product: ");
            fflush(stdin);
            scanf("%lld", &stock[p].code);
            printf("Enter the name of the product: ");
            fflush(stdin);
            scanf("%[^\n]s", stock[p].name);
            printf("Enter the quantity of the product: ");
            fflush(stdin);
            scanf("%d", &stock[p].quantity);
            printf("Enter the price of the product: ");
            fflush(stdin);
            scanf("%f", &stock[p].price);
            stock[p].sold = 0;
            stock[p].priceTax = stock[p].price + stock[p].price * 0.15;
            printf("\n");
            p++;
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;
            
        case 2: ; // Adding multiple new product
            int n = 0, count = 0;
            printf("|========================== Registering new products ===========================|\n\n");
            printf("Enter the amount of products that you want to add: ");
            scanf("%d", &n);
            printf("\n");
            stock = realloc(stock, (p + n) * sizeof(product));
            n += p;
            for (p; p < n; p++)
            {
                count++;
                printf("|-------------------------------- Product N: %02d --------------------------------|\n", count);
                printf("Enter the code of the product: ");
                fflush(stdin);
                scanf("%lld", &stock[p].code);
                printf("Enter the name of the product: ");
                fflush(stdin);
                scanf("%[^\n]s", stock[p].name);
                printf("Enter the quantity of the product: ");
                fflush(stdin);
                scanf("%d", &stock[p].quantity);
                printf("Enter the price of the product: ");
                fflush(stdin);
                scanf("%f", &stock[p].price);
                stock[p].sold = 0;
                stock[p].priceTax = stock[p].price + stock[p].price * 0.15;
                printf("\n");
            }
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;
        
        case 3: ; // List of products in order
            nn = p;
            do
            {
                sortingAlph (stock, nn);
                printf("|========= Display the list of products in ascending alphabetical order ========|\n");
                printf("|\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|=========== Name /\\ =================== Price ============== Price + Tax ======|\n");
                for (int j = 0; j < p; j++) {
                    printf("# %d\t    %s\n", j + 1, stock[j].name);
                    printf("\t\t\t\t\t %.2f\n", stock[j].price);
                    printf("\t\t\t\t\t\t\t      %.2f\n", stock[j].priceTax);
                    if (stock[j].sold > 0) {
                        printf("\t Sold %d unit of this product on %02d/%02d/%d, at %02d:%02d:%02d\n", stock[j].sold, stock[j].date.day, stock[j].date.month + 1, stock[j].date.year + 1900, stock[j].date.hour, stock[j].date.min, stock[j].date.sec);
                    }
                    printf("|-------------------------------------------------------------------------------|\n");
                }
                printf("|\t\t\t1 - To show descending price order.\t\t\t|\n");
                printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
                scanf("%d", &o);
                system("cls");

                if ( o == 1) {
                    sortingPrice (stock, nn);
                    printf("|========= Display the list of products in descending price order ==============|\n");
                    printf("|\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("|=========== Name ====================== Price \\/ =========== Price + Tax ======|\n");
                    for (int j = 0; j < p; j++) {
                        printf("# %d\t    %s\n", j + 1, stock[j].name);
                        printf("\t\t\t\t\t %.2f\n", stock[j].price);
                        printf("\t\t\t\t\t\t\t      %.2f\n", stock[j].priceTax);
                        if (stock[j].sold > 0) {
                            printf("\t Sold %d unit(s) of this product on %02d/%02d/%d, at %02d:%02d:%02d\n", stock[j].sold, stock[j].date.day, stock[j].date.month + 1, stock[j].date.year + 1900, stock[j].date.hour, stock[j].date.min, stock[j].date.sec);
                        }
                        printf("|-------------------------------------------------------------------------------|\n");
                    }
                    printf("|\t\t\t1 - To show ascending alphabetical order.\t\t|\n");
                    printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
                    scanf("%d", &o);
                    system("cls");
                }
            } while (o == 1);
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;
        
        case 4: ; // buying product
            nn = p;
            printf("|============================== Buying a product ===============================|\n\n");
            do {
                printf("Enter the code of the product sold: ");
                scanf("%lld", &cd);

                lk = search (stock, nn, cd);

                if (lk == -1) {
                    printf("Product not found!\n");
                    sleep(1);
                }else {
                    printf("Enter the quantity of the product sold: ");
                    scanf("%d", &amount);

                    if (stock[lk].quantity < amount) {
                        printf("There is not enough quantity!\n");
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
                        printf("Product sold was successfully registered!\n");
                    }
                }
                printf("|-------------------------------------------------------------------------------|\n");
                printf("|\t\t\t1 - To sell another product.\t\t\t\t|\n");
                printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
                scanf("%d", &o);
            } while (o == 1);
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;

        case 5: ; // searching for a product
            nn = p;
            printf("|=========================== Searching for products ============================|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t1 - To search for a product using code.\t\t\t|\n");
            printf("|\t\t\t2 - To search for products using quantity.\t\t|\n");
            printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
            scanf("%d", &o);
            do
            {
                if (o == 1) {
                    printf("Enter the code of the product: ");
                    scanf("%lld", &cd);

                    lk = search (stock, nn, cd);
                    
                    if (lk == -1)
                    {
                        printf("Product not found!\n");
                        sleep(1);
                    }else {
                        printf("|-------------------------------------------------------------------------------|\n");
                        printf(" Product's code:\t\t\"%lld\"\n", stock[lk].code);
                        printf(" Product's name:\t\t%s\n", stock[lk].name);
                        printf(" Product's quantity:\t\t%d\n", stock[lk].quantity);
                        printf(" Product's price including tax: %.2f\n", stock[lk].priceTax);
                    }
                }else if (o == 2) {
                    printf("Enter the quantity that you are looking for: ");
                    scanf("%d", &amount);
                    int cnt = 0;

                    for (int i = 0; i < nn; i++)
                    {
                        if (stock[i].quantity == amount) {
                            printf("|-------------------------------------------------------------------------------|\n");
                            printf(" Product's code:\t\t%lld\n", stock[i].code);
                            printf(" Product's name:\t\t%s\n", stock[i].name);
                            printf(" Product's quantity:\t\t\"%d\"\n", stock[i].quantity);
                            printf(" Product's price including tax: %.2f\n", stock[i].priceTax);
                            cnt++;
                        }else if (cnt == 0) {
                            printf("|-------------------------------------------------------------------------------|\n");
                            printf(" No products found with this quantity.\n");
                            sleep(1);
                        }
                    } 
                }
                printf("|-------------------------------------------------------------------------------|\n");
                printf("|\t\t\t\t\t\t\t\t\t\t|\n");
                printf("|\t\t\t1 - To search for a product using code.\t\t\t|\n");
                printf("|\t\t\t2 - To search for products using quantity.\t\t|\n");
                printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
                scanf("%d", &o);
            } while (o != 0);
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;

        case 6: ; // Stock status
            nn = p;
            int count2 = 0;
            printf("|================================ Stock status =================================|\n");
            printf("| List of products with quantity below 3 ---------------------------------------|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|== Code ============== Name ============= Price + Tax ========= Quantity ======|\n");

            for (int i = 0; i < nn; i++)
            {
                if (stock[i].quantity < 3)
                {
                    printf("    %lld\n", stock[i].code);
                    printf("\t\t\t%s\n", stock[i].name);
                    printf("\t\t\t\t\t     %.2f\n", stock[i].priceTax);
                    printf("\t\t\t\t\t\t\t\t    %d\n", stock[i].quantity);
                    printf("|-------------------------------------------------------------------------------|\n");
                    count2++;
                }
            }
            if (count2 == 0) {
                sleep(1);
                printf("|\t\t\t\t\t\t\t\t\t\t|\n");
                sleep(1);
                printf("| No products below the quantity of 3 ------------------------------------------|\n");
            }
            printf("Press Enter to go back to the main menu.");
            fflush(stdin);
            scanf("%c", &enter);
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;

        case 7: ; // Stock update
            nn = p;
            printf("|========================= Updating products quantity ==========================|\n\n");
            do {
                printf("Enter the code of the product: ");
                scanf("%lld", &cd);

                lk = search (stock, nn, cd);

                if (lk == -1) {
                    printf("Product not found!\n");
                    sleep(1);
                }else {
                    printf("Enter the quantity of the product sold: ");
                    scanf("%d", &amount);
                    stock[lk].quantity += amount;
                    sleep(1);
                    printf("Product's quantity was successfully updated!\n");                
                }
                printf("|-------------------------------------------------------------------------------|\n");
                printf("|\t\t\t1 - To update another product's quantity.\t\t|\n");
                printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
                scanf("%d", &o);
            } while (o == 1);
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;

        case 8: // deleting a product
            printf("|============================= Deleting products ===============================|\n\n");
            do {
                char confirm;
                printf("Enter the code of the product: ");
                scanf("%lld", &cd);

                lk = search (stock, nn, cd);

                if (lk == -1) {
                    printf("Product not found!\n");
                    sleep(1);
                }else {
                    printf("|-------------------------------------------------------------------------------|\n");
                    printf(" Product's code:\t\t%lld\n", stock[lk].code);
                    printf(" Product's name:\t\t%s\n", stock[lk].name);
                    printf(" Product's quantity:\t\t%d\n", stock[lk].quantity);
                    printf(" Product's price including tax: %.2f\n", stock[lk].priceTax);
                    printf(" Quantity of the sold product:  %d\n", stock[lk].sold);
                    printf("|-------------------------------------------------------------------------------|\n");
                    printf("Are you sure that you want to delete this product?\n(Enter y/Y to confirm, enter any other character to skip)\n");
                    fflush(stdin);
                    scanf("%c", &confirm);
                    if (confirm == 'y' || confirm == 'Y') {
                        for (int i = lk; i < p; i++)
                        {
                            stock[i] = stock[i + 1];
                        }
                        p--;
                        stock = realloc(stock, (p + 1) * sizeof(product));
                        printf("The product was successfully removed.\n");
                        sleep(1);
                    }
                }
                printf("|-------------------------------------------------------------------------------|\n");
                printf("|\t\t\t1 - To delete another product.\t\t\t\t|\n");
                printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
                scanf("%d", &o);
            } while (o == 1);
            printf("Going back to the main menu...\n");
            sleep(1);
            //system("cls");  remove comment mark later
            break;

        case 9: ; // Statictics
            float S = 0, avr;
            int count3 = 0;
            printf("|============================= Sales statistics ================================|\n");
            printf("| Displaying the statistics for %02d/%02d/%d -------------------------------------|\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            printf("|\t\t\t\t\t\t\t\t\t\t|\n");
            do
            {
                printf("|\t\t\t1 - Display total prices of products sold today.\t|\n");
                printf("|\t\t\t2 - Display average price of products sold today.\t|\n");
                printf("|\t\t\t3 - Display maximum price of products sold today.\t|\n");
                printf("|\t\t\t4 - Display minimum price of products sold today.\t|\n");
                printf("|\t\t\t5 - Display ALL the statistics.\t\t\t\t|\n");
                printf("|\t\t\t0 - To go back to main menu.\t\t\t\t|\n");
                fflush(stdin);
                scanf("%d", o);
                // system("cls"); remove
                switch (o)
                {
                case 1: // Total prices
                    printf("|= Code ========== Name ========== Q. sold = Q. left === Unit P. === Total P. ==|\n");
                    for (int i = 0; i < p; i++)
                    {
                        if (stock[i].sold > 0)
                        {
                            stock[i].totalPriceTax = stock[i].priceTax * stock[i].sold;
                            printf("   %lld\n", stock[i].code);
                            printf("\t\t   %s\n", stock[i].name);
                            printf("\t\t\t\t   %d\n", stock[i].sold);
                            printf("\t\t\t\t\t     %d\n", stock[i].quantity);
                            printf("\t\t\t\t\t\t         %.2f\n", stock[i].priceTax);
                            printf("\t\t\t\t\t\t\t\t     %.2f\n", stock[i].totalPriceTax);
                            printf("|-------------------------------------------------------------------------------|\n");
                            S += stock[i].totalPriceTax;
                            count3++;
                        }
                    }
                    if (count3 != 0) {
                        printf("| Total price of all products sold: --------------------------------------------|\n");
                        printf("\t\t\t\t\t\t\t      Total: %.2f\n", S);
                        printf("|\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| Q = Quantity, P = Price.  All taxes are included -----------------------------|\n\n");
                    }else {
                        printf("| No products have been sold today ---------------------------------------------|\n\n");
                    }
                    S = 0;
                    count3 = 0;
                    printf("Press Enter to go back to the statistics menu.\n");
                    fflush(stdin);
                    scanf("%c", &enter);
                    system("cls");
                    break;
                
                case 2: // Average price
                    for (int i = 0; i < p; i++)
                    {
                        if (stock[i].sold > 0)
                        {
                            stock[i].totalPriceTax = stock[i].priceTax * stock[i].sold;
                            S += stock[i].totalPriceTax;
                            count3++;
                        }
                    }
                    if (count3 > 0) {
                        avr = S / count3;
                        printf("| Average price of all products sold: ------------------------------------------|\n");
                        printf("\t\t\t\t\t\t\t    Average: %.2f\n", avr);
                        printf("|\t\t\t\t\t\t\t\t\t\t|\n");
                        printf("| All taxes are included -------------------------------------------------------|\n\n");
                    }
                    avr = 0;
                    S = 0;
                    count3 = 0;
                    printf("Press Enter to go back to the statistics menu.\n");
                    fflush(stdin);
                    scanf("%c", &enter);
                    system("cls");
                    break;
                
                case 3: // Max price
                    break;
                
                default:
                    break;
                }
            } while (0);
            
            
            break;

        case 0:
            printf("|================= Quitting Pharmacy Management. See you soon! =================|\n");
            sleep(2);
            exit(0);
            break;

        default:
            printf("You can only choose from 0 to 9!!\n");
            sleep(4);
            system("cls");
            break;
        
        }
    } while (menu != 0);

    return 0;
}

void sortingPrice (product* stock, int nn) {
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

void sortingAlph (product* stock, int nn) {
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

int search (product* stock, int nn, long long int cd) {
    int count = 0;
    for (int i = 0; i < nn; i++)
    {
        if (stock[i].code == cd) {
            return i;
            count ++;
        }
    }
    if (count == 0) {
        return -1;
    }
}