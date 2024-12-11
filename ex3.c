/******************
Name: Chen Bujor
ID: 322996976
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7
#define INITIALIZING_VALUE -1

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
//sets all values in the array to -1
void initializer(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int initializeValue)
{
    for (int i = 0; i < DAYS_IN_YEAR; i++)
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            for (int k = 0; k < NUM_OF_TYPES; k++)
            {
                cube[i][j][k] = initializeValue;
            }
}
//checks if there's brands with missing data and prints their names
int noData (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    //A check if there's a brand with missing data and the number to return if we require a loop
    int notComplete = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            if (notComplete == 0 && cube[day][i][j] == INITIALIZING_VALUE)
            {
                printf("No data for brands ");
                notComplete = 1;
            }
            if (cube[day][i][j] == INITIALIZING_VALUE)
            {
                    printf("%s ", brands[i]);
            }
            break;
        }
    }
    if(notComplete == 1)
        printf("\nPlease complete the data.\n");
    return notComplete;
}
//Gets an array of cars and a day and outputs the total amount of sales total on that day
int totalSalesInDay (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int sales;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
        for(int j = 0; j < NUM_OF_TYPES; j++)
            sales += cube[day][i][j];
    return sales;
}
//Gets the cube, the day that needs to be checked and a pointer for a variable in the main that will be used to get the amount of sales
//And returns the index of the best selling brand in the Brands variable, and changes the Sales variable from the main accordingly
int bestSoldBrandInDay (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int* bestSales)
{
    int bestSoldBrand = 0;
    int maxSalesBrand = 0;
    int currentSalesBrand = 0;
    int num_of_brands = sizeof(cube[0])/sizeof(cube[0][0]);
    int num_of_types = sizeof(cube[0][0])/sizeof(cube[0][0][0]);
    for (int i = 0; i < num_of_brands ; i++)
    {
        currentSalesBrand = 0;
        for(int j = 0; j < num_of_types; j++)
            currentSalesBrand += cube[day][i][j];
        if (currentSalesBrand > maxSalesBrand)
        {
            maxSalesBrand = currentSalesBrand;
            bestSoldBrand = i;
        }
    }
    *bestSales = maxSalesBrand;
    return bestSoldBrand;
}
//Gets the cube,the day that needs to be checked and a pointer for a variable in the main that will be used to get the amount of sales
//And returns the index of the best selling brand in the Types variable, and changes the Sales variable from the main accordingly
int bestSoldTypeInDay (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int* bestSales)
{
    int bestSoldType;
    int maxSalesType = 0;
    int currentSalesType = 0;
    int num_of_brands = sizeof(cube[0])/sizeof(cube[0][0]);
    int num_of_types = sizeof(cube[0][0])/sizeof(cube[0][0][0]);
    for (int i = 0; i < num_of_types ; i++)
    {
        currentSalesType = 0;
        for(int j = 0; j < num_of_brands; j++)
            currentSalesType += cube[day][j][i];
        if (currentSalesType > maxSalesType)
        {
            maxSalesType = currentSalesType;
            bestSoldType = i;
        }
    }
    *bestSales = maxSalesType;
    return bestSoldType;

}
//Function that recieves a 3D array of car info and the latest day that wasn't filled with information yet, and prints it
void printCube (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay)
{
    int num_of_brands = sizeof(cube[0])/sizeof(cube[0][0]);
    int num_of_types = sizeof(cube[0][0])/sizeof(cube[0][0][0]);
    printf("brands %d, sales %d \n",num_of_brands,num_of_types);
    printf("*****************************************\n");
    for (int i = 0; i < num_of_brands; i++)
    {
        printf("\nSales for %s:", brands[i]);
        for (int day = 0; day < currentDay; day++)
        {
            printf("\nDay %d-", day + 1);//days start at zero, so add one for user experience
            for (int k = 0; k < num_of_types; k++)
            {
                printf(" %s: %d",types[k], cube[day][i][k]);
            }
        }
    }
    printf("\n*****************************************\n");

}

//gets an array of cars, the type that we wish to check and the day we want to check and return the sales of cars from that type

int typeSalesInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int type, int day)
{
    int sales = 0;
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            sales += cube[day][j][type];
    return sales;
}

//gets an array of cars, the brand that we wish to check and the day we want to check and return the sales of cars from that brand

int brandSalesInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brand, int day)
{
    int sales = 0;
        for (int j = 0; j < NUM_OF_TYPES; j++)
            sales += cube[day][brand][j];
    return sales;
}
//Gets an int Array and the size of the Array, and returns the index of the biggest int value within the array
int biggestInArray(int Arr[], int size)
{
    int max = 0;
    int i = 0;
    for (; i < size; i++)
        if (Arr[i] > max)
        {
            max = Arr[i];
        }
    return i;
}
//gets a 3D array of cars and a brand index, and calculates and prints the delta of the requested brand
void deltaPrinter(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int currentDay)
{
    float delta = 0;
    if (currentDay < 1)
    {
        printf("Brand: %s, Average Delta: %f\n",brands[brand], delta);
        return;
    }
    int deltaNumerator = 0;
    int denominator = currentDay+1; // the day counter starts at 0, hence one must be added in order to get to the day count
    int day1 = 0;
    int day2 = 0;
    //iterates over every day and adds the delta between each day and the one after it
    for (int i = 0; i < currentDay; i++)
    {
        day2 = brandSalesInDay(cube, brand, i);
        deltaNumerator = deltaNumerator + day2 - day1;
        day1 = day2;
    }
    //calculates the average delta
    delta = deltaNumerator / denominator;
    printf("Brand: %s, Average Delta: %f\n",brands[brand], delta);
    return;
}
int main() {
    int num = 1;
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int choice;
    int day = 0;
    initializer(cube, INITIALIZING_VALUE);
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
        case addOne:
                {
                    int temp;
                    int DailySales[NUM_OF_BRANDS][NUM_OF_TYPES];
                    printf("Enter Car Brand\n");
                    scanf("%d", &temp);
                    if (temp < NUM_OF_BRANDS || temp > NUM_OF_BRANDS)
                        break;
                    printf("Enter Daily Sales per brand\n");
                    scanf("%d %d %d %d",DailySales[temp][0],DailySales[temp][1],DailySales[temp][2],DailySales[temp][3]);
                    break;
                }
        case addAll:
                {
                    //the car brand that we want to give sales info about
                    int Brand;
                    //function that says which car brands have missing info, and returns the amount of brands that lack data/
                    while (noData(cube, day))
                    {
                        scanf("%d", &Brand);
                        scanf(" %d %d %d %d",&cube[day][Brand][0],&cube[day][Brand][1],&cube[day][Brand][2],&cube[day][Brand][3]);
                    }
                    day++;
                        break;
                }
        case stats:
                {
                int bestBrandSales = 0;
                int bestTypeSales = 0;
                int bestBrand;
                int chosenDay;
                int totalSales;
                int bestType;
                //checks if the inputted day is valid
                do
                {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &chosenDay);
                    if (chosenDay < 0 || chosenDay > day || chosenDay > 364)
                        printf("Please enter a valid day.\n");
                } while (chosenDay < 0 || chosenDay > day || chosenDay > 364);
                //Gets the total amount of sales in the inputted day and prints it
                totalSales = totalSalesInDay(cube, chosenDay);
                printf("In day number %d:\n",chosenDay);
                printf("The sales total was %d\n", totalSales);

                //gets the index for the best selling brand and changes the bestBrandSales variable to the amount it sold
                bestBrand = bestSoldBrandInDay(cube, chosenDay, &bestBrandSales);
                printf("The best sold brand with %d sales was %s\n", bestBrandSales, brands[bestBrand]);
                bestType = bestSoldTypeInDay(cube, day, &bestTypeSales);
                printf("The best sold type with %d sales was %s\n", bestTypeSales, types[bestType]);
                }
        case print:
            {
                //gets the car array and the day which marks how many days we have filled with information and prints it
                printCube(cube, day);

                break;
            }
        case insights:
            {
                int BrandSales[NUM_OF_BRANDS] = {0,0,0,0,0};
                int TypeSales[NUM_OF_TYPES] = {0,0,0,0};
                int temp = 0;
                int bestDay = 0;
                int bestDaySales = 0;
                int bestBrandSales = 0;
                int bestBrand = 0;
                int bestTypeSales = 0;
                int bestType = 0;

                for (int i = 0; i < day; i++)
                {
                    temp = totalSalesInDay(cube, i);
                    //checks if the current day's sales are higher than the previous highest, and assigns the biggest value to a variable
                    if (temp > bestDay)
                    {
                        bestDaySales = temp;
                        bestDay = i+1;
                    }
                    //fills an array of the total brand sales per each brand
                    for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
                        BrandSales[brand] += brandSalesInDay(cube, brand, i);
                    //fills an array of the total sales of each type
                    for (int type = 0; type < NUM_OF_TYPES; type++)
                        TypeSales[type] += typeSalesInDay(cube, type, i);
                }
                //functions that find the index within the array of the biggest sales value per brand/type
                bestBrand = biggestInArray(BrandSales, NUM_OF_BRANDS);
                bestType = biggestInArray(TypeSales, NUM_OF_TYPES);
                printf("The best-selling brand overall is %s:%d$\n", brands[bestBrand], BrandSales[bestBrand]);
                printf("The best-selling type of car is %s:%d$\n",types[bestType], TypeSales[bestType]);
                printf("The most profitable day was day number %d:%d$",bestDay,bestDaySales);
            }
        case deltas:
            {
                //iterates over all the brands
                for (int i = 0; i < NUM_OF_BRANDS; i++)
                {
                    //function that prints the delta of the current brand
                    deltaPrinter(cube, i, day);
                }
                break;
            }
        case done:
            break;
        default:
            printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


