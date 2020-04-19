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
#include "intermediate_code.h"
#include "code_gen.h"
#include <time.h>

/* Main function called on execting the program
   Continuous choice given to user on what function to perform. Details below
*/
int main(int argc, char* argv[]) {
    int choice;
    int flag = 0;
    int tokens;
    int parsed = 0;

    /*Checking if execution is done properly, passing appropriate arguments
    */
    if(argc != 3) {
        printf("Incorrect number of parameters\n");
        printf("Sample call: ./compiler  testcase.txt  code.asm\n");
        exit(0);
    }

    /*Printing status of work
    */
    printf("\nStatus of work: \n");
    printf("LEVEL 4: AST / Symbol table / Type checking / Semantic Rules / Intermediate code / Code generation modules work\n\n");

    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;
    while(1) {
        /* Giving option choices to user
        */
        printf("\nPress:\n\n");
        printf("0: For exit\n");
        printf("1: For invoking only lexer\n");
        printf("2: For invoking both lexer and parser and printing parse tree in-order\n");
        printf("3: For printing AST in-order \n");
        printf("4: For displaying amount of memory used\n");
        printf("5: For printing symbol table \n");
        printf("6: For printing activation record sizes of functions \n");
        printf("7: For printing the type expressions and width of array variables \n");
        printf("8: For verifying syntactic and semantic correctness and printing total time taken\n");
        printf("9: For producing assembly code\n");
        scanf("%d", &choice);

        Node ** token_stream = NULL;
        lookup_table *table = NULL;
        t_node** parse_tree_ptr;
        AST root;
        ErrorList* err;
        Symbol_Table_Tree tree;
        tuple_list* list;

        switch(choice) {
            case 0: //Program exit
                flag = 1;
                break;

            case 1: //Print only the output of lexical_analyzer
                printf("\n");
                tokens = lexical_analyzer(argv[1], &token_stream, &table, 1);
                break;

            case 2: // Invoke only parser and check for lexical and syntax errors
                printf("\n");
                parse_tree_ptr = parser(argv[1], "", &parsed, 1);
                break;

            case 3: // Print AST in-order
                printf("\n");
                parse_tree_ptr = parser(argv[1], "", &parsed, 0);
                if(!parsed) {
                    break;
                }
                root = generate_AST(*parse_tree_ptr, 1);
                break;

            case 4: // Calculate total allocated memory to parse tree and AST
                printf("\n");
                parse_tree_ptr = parser(argv[1], "", &parsed, 0);
                if(!parsed) {
                    break;
                }
                root = generate_AST(*parse_tree_ptr, 0);
                calculate_allocated_memory(*parse_tree_ptr, root);
                
                break;

            case 5: // Print symbol table
                printf("\n");
                parse_tree_ptr = parser(argv[1], "", &parsed, 0);
                if(!parsed) {
                    break;
                }
                
                root = generate_AST(*parse_tree_ptr, 0);
                err = initialize_errors();
                tree = create_symbol_table_tree(root, err, 1);
                break;
            
            case 6: // Print activation record sizes
                printf("\n");
                parse_tree_ptr = parser(argv[1], "", &parsed, 0);
                if(!parsed) {
                    break;
                }
                
                root = generate_AST(*parse_tree_ptr, 0);
                err = initialize_errors();
                tree = create_symbol_table_tree(root, err, 3);
                break;
                
            case 7: // Print array variables' information
                printf("\n");
                parse_tree_ptr = parser(argv[1], "", &parsed, 0);
                if(!parsed) {
                    break;
                }
                
                root = generate_AST(*parse_tree_ptr, 0);
                err = initialize_errors();
                tree = create_symbol_table_tree(root, err, 2);
                break;

            case 8: // Print syntax and semantic errors, if any, and print total time taken
                printf("\n");
                start_time = clock();
                parse_tree_ptr = parser(argv[1], "", &parsed, 0);
                if(!parsed) {
                    end_time = clock();
                    total_CPU_time = (double)(end_time - start_time);
                    total_CPU_time_in_seconds = total_CPU_time/CLOCKS_PER_SEC;
                    printf("\n\n*****\n");
                    printf("Total_CPU_time for only parser with syntax errors: %lf\n", total_CPU_time);
                    printf("Total_CPU_time_in_seconds for only parser with syntax errors: %lf\n", total_CPU_time_in_seconds);
                    printf("*****\n\n");
                    break;
                }
                root = generate_AST(*parse_tree_ptr, 0);
                err = initialize_errors();
                tree = create_symbol_table_tree(root, err, 0);
                
                type_checker(root, err, tree);
                sort_errors(err);
                if((err->head) != NULL) {
                    printf("Semantic errors occurred\n\n");
                    print_errors(err);
                }
                else {
                    printf("No semantic errors occurred\n\n");
                    printf("Code compiles successfully\n\n");
                }

                end_time = clock();
                total_CPU_time = (double)(end_time - start_time);
                total_CPU_time_in_seconds = total_CPU_time/CLOCKS_PER_SEC;
                printf("\n\n*****\n");
                printf("Total_CPU_time for parser and semantic analyser: %lf\n", total_CPU_time);
                printf("Total_CPU_time_in_seconds for parser and semantic analyser: %lf\n", total_CPU_time_in_seconds);
                printf("*****\n\n");
                break;

            case 9: //Print syntax and semantic errors, if any, and generate asm code
                printf("\n");
                parse_tree_ptr = parser(argv[1], "", &parsed, 0);
                if(!parsed) {
                    break;
                }
                
                root = generate_AST(*parse_tree_ptr, 0);
                err = initialize_errors();
                tree = create_symbol_table_tree(root, err, 0);
                
                type_checker(root, err, tree);
                sort_errors(err);

                if((err->head) != NULL) {
                    printf("Semantic error occurred\n\n");
                    print_errors(err);
                }
                else {
                    printf("No semantic errors occurred\n\n");
                    printf("Code compiles successfully\n\n");
                    list = generate_ir(root);
                    generate_code(list, tree, argv[2]);
                }
                break;

            default: printf("\nInvalid Choice\n\n");
        }
        printf("\n\n");

        if(flag)
            break;

    }
    return 0;
}