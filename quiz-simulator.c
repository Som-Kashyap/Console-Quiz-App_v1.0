#include<stdio.h>
#include<string.h>
#include<time.h>

struct answer {

    float ans;

    char status[100];

};


void get_questions() {

    FILE* fp;

    char Buffer[100];

    fp = fopen ("questions.txt" , "r");

    if ( !fp ) printf("ERROR opening file for displaying question set!");

    while ( fgets ( Buffer , 100 , fp )!=NULL ) {
        printf ( "%s" , Buffer );
    }

    fclose ( fp );
}

void check_answers( float answer_array[] , struct answer ans[] , int *score , int *correct , int *incorrect ) {

  

    for ( int i = 0; i < 2; i++ ) {


        if ( ans[i].ans == answer_array[i] ) {
            
            (*score)++; (*correct)++;
            strcpy( ans[i].status , "CORRECT" );

        }

        else{

            (*incorrect)++;
            strcpy( ans[i].status , "INCORRECT" );

        }
    }
}

void calculate_result( float answer_array[] , struct answer ans[] , int score , int *correct , int *incorrect , char name[]) {

    FILE* fp;
    char buffer[100];

    time_t curr_time;
    time(&curr_time);

    fp = fopen ( "result.txt" , "a" );

    if (!fp) printf("ERROR- writing to result file!");

    fprintf(fp ,"\n----------------------------");
    fprintf( fp , "\nAttempted on :- %s" , ctime(&curr_time) );
    fprintf(fp , "Username: %s" , name);

    for ( int i = 0; i < 2; i++ ) {

        fprintf ( fp , "\nanswer-%d : %s" , i+1 ,ans[i].status );

    }

    fprintf (fp,"\n overall score: (%d/2)" , score);
    fprintf (fp , "\ncorrect:%d | incorrect:%d" , *correct , *incorrect);

    printf ("Results written to file succesfully!\n");

    fclose(fp);

}

void display_history() {

    FILE* fp;

    char buffer[100];

    fp = fopen( "result.txt" , "r" );

    if (!fp) printf("ERROR- opening file for displaying results!");

    while ( fgets( buffer , 500 , fp)!=NULL ) {

        printf ( "%s" , buffer );

    }

    fclose( fp );

}

int main () {

    float answer_array[] = { 14 , 12 };

     char name[50];

    printf( "\nEnter your Name:- ");
    fgets (name , 50 , stdin);

    name[strcspn(name, "\n")] = 0; //for clearing the input buffer

    get_questions();

    struct answer ans[2];

    int score = 0;
    int correct = 0 ; int incorrect = 0;
   

    for ( int i = 0; i < 2; i++ ) {

        printf ( "\nEnter answer of question-%d:- " , i+1 );

        scanf("%f" , &ans[i].ans);

    }

    check_answers(  answer_array , ans , &score , &correct , &incorrect );
    calculate_result( answer_array , ans , score , &correct , &incorrect , name);

    char choice;

    printf( "\nDisplay past attempts? (Y/N): ");
    
    while ((getchar()) != '\n');
    
    scanf( "%c" , &choice );

    if (  choice == 'Y' ) {

        display_history();

     }

    return 0;
}

