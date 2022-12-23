#include <stdio.h>
#include <mysql.h>
#include <string.h>

struct BUYER{
    int NUMBER[10];
    char NAME[100];
};

void buy_car(){

    int choice;

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "Kutulu@2210x"; /* set me first */
    char *database = "car_db";

    conn = mysql_init(NULL);
    
    printf("Lets start buying a new car\n");

    if (!mysql_real_connect(conn, server, user, password,
                                    database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "select * from cars")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    int fields = mysql_num_fields(res);

    printf("ID\t MAKE\t MODEL\t KMS_DRIVEN\t MFG_YEAR\t PRICE\t QUANTITY\t RATING\t CONDITION\t ISSUES\n");

    while ((row = mysql_fetch_row(res)) != NULL){
        for (int i=0; i<fields; i++) 
		    printf("%s\t", row[i]);
	printf("\n");
    }
    
    printf("Which car do you want to buy: ");
    scanf("%d", &choice);

    printf("The dealership has been notified of your interest in the product\n");

	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);

}

void sell_car(){
    char MAKE[20], MODEL[30], ISSUES[100], REASON[100];
    int MANUFACTURE_YEAR, KMD, PRICE;
    float SCORE = 100, CONDITION;

    printf("We are excited to buy a car from you\nLets gets started\n");

    printf("We will start with the basic information about the car\n");

    printf("Enter the make of the car: ");
    scanf("%s", MAKE);
    printf("Enter the model of the car: ");
    scanf("%s", MODEL);
    printf("Enter the year of manufacture of the car: ");
    scanf("%d", &MANUFACTURE_YEAR);
    printf("Enter the kilometers driven: ");
    scanf("%d", &KMD);
    printf("Rate the condition of the car out of 10: ");
    scanf("%f", &CONDITION);
    printf("Any issues with the car the buyer should be aware of: ");
    scanf("%s", ISSUES);
    printf("Reason to sell the car: ");
    scanf("%s", REASON);

    SCORE = CONDITION*10;
    SCORE = SCORE - ((2022 - MANUFACTURE_YEAR)*2);
    SCORE = SCORE - (KMD/10000);

    printf("We rate your car: %.1f/100", SCORE);

    if (MODEL[0] == 'i'){
        printf("\nThe price which we would offer is: %.1f \n", ((SCORE/100)*3000000));
    }
    else{
        printf("Enter the onroad price of the car \n");
        scanf("%d", &PRICE);
        printf("The price which we would offer is: %.1f\n", ((SCORE/100)*3000000));
    }

    printf("The dealership has been notified of your car and you will shotly be contacted\n");

}

void information(){

    struct BUYER B1;

    printf("Enter your name: ");
    scanf("%s", B1.NAME);
    printf("Enter your mobile number: ");
    scanf("%d", B1.NUMBER);


}

int main(){
    int CHOICE;

    information();

    printf("1.Buy a Car \n2.Sell a Car \nEnter your choice: ");
    scanf("%d", &CHOICE);

    switch(CHOICE){
        case 1: buy_car();
                break;

        case 2: sell_car();
                break;

        default: printf("Invalid choice");
    }
}
