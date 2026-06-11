#include<stdio.h>
#include<string.h>

struct Questions {

    char Q[100];

    float correct_ans;

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

int main () {

    get_questions();
    

    return 0;
}

