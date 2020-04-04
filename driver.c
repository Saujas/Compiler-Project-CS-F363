// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include "symbol_table.h"
#include "type_extractor.h"
#include "semantic_analyzer.h"
#include <time.h>

/* Main function called on execting the program
   Continuous choice given to user on what function to perform. Details below
*/
int main(int argc, char* argv[]) {
    int choice;
    int flag = 0;
    int tokens;

    /*Checking if execution is done properly, passing appropriate arguments
    */
    if(argc != 3) {
        printf("Incorrect number of parameters\n");
        printf("Sample call: ./stage1exe   test.txt   parsetreeOutFile.txt\n");
        exit(0);
    }

    /*Printing status of work
    */
    printf("\nStatus of work: \n");
    printf("\t (a) FIRST and FOLLOW set computation has been automated\n");
    printf("\t (b) Both lexical and syntax analysis modules implemented\n");
    printf("\t (c) Modules compile and run successfully\n");
    printf("\t (d) Modules run with all the test cases\n");
    printf("\t (e) Parse tree can be constructed and viewed on the file\n");
    printf("\t (f) Lexical and syntactic errors can be viewed on the console\n");

    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;
    while(1) {
        /* Giving option choices to user
        */
        printf("\nPress:\n\n");
        printf("0: For exit\n");
        printf("1: For removal of comments\n");
        printf("2: For invoking only lexer\n");
        printf("3: For invoking both lexer and parser\n");
        printf("4: For printing total time for lexer and parser\n");
        printf("5: For creating AST and symbol table, type checking\n");
        scanf("%d", &choice);

        Node ** token_stream = NULL;
        lookup_table *table = NULL;
        t_node** parse_tree_ptr;

        switch(choice) {
            case 0: //Program exit
                flag = 1;
                break;

            case 1: //Print source code without comments
                printf("\n\nSource code after removing comments:\n");
                print_without_comments(argv[1]);
                printf("\n");
                break;

            case 2: //Print only the output of lexical_analyzer
                printf("\n");
                tokens = lexical_analyzer(argv[1], &token_stream, &table, 1);
                break;

            case 3: //Call lexer and parser, and print both lexical and syntactic errors if any
                printf("\n");
                parser(argv[1], argv[2]);
                break;

            case 4: //Call lexer and parser, and print the total time taken until parse tree is generated
                start_time = clock();
                parser(argv[1], argv[2]);
                end_time = clock();
                total_CPU_time = (double)(end_time - start_time);
                total_CPU_time_in_seconds = total_CPU_time/CLOCKS_PER_SEC;
                printf("\n\n*****\n");
                printf("Total_CPU_time: %lf\n", total_CPU_time);
                printf("Total_CPU_time_in_seconds: %lf\n", total_CPU_time_in_seconds);
                printf("*****\n\n");
                break;

            case 5:
                printf("\n");
                parse_tree_ptr = parser(argv[1], argv[2]);
                AST root = generate_AST(*parse_tree_ptr);
                create_symbol_table_tree(root);
                //print_ast(root);
                printf("Type checker invoked\n");
                type_checker(root);
                break;

            default: printf("\nInvalid Choice\n\n");
        }
        printf("\n\n");

        if(flag)
            break;

    }
    return 0;
}