#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree_c.h"
#include "traversal.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Qua it tham so dau vao.\nThoat chuong trinh...\n\n");
        exit(1);
    }
    else if (argc > 2) {
        printf("Qua nhieu tham so dau vao.\nThoat chuong trinh...\n\n");
        exit(1);
    }
    char filename[10000];
    strcpy(filename, argv[1]);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s.\nThoat chuong trinh...\n\n");
        exit(1);
    }
    char line[10000];
    printf("\nNoi dung file %s nhu sau:\n", filename);
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s",line);
    }
    printf("\n\n");
    fclose(file);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s.\nThoat chuong trinh...\n\n");
        exit(1);
    }
    tree_t tree=NULL;
    elmType temp;
    int count_word=0;
    while (fscanf(file, "%s",temp.word)!= EOF) {
        InsertandCount(temp, &tree);
        count_word++;
    }
    
    elmType find;
    printf("Nhap vao 1 tu: ");
    scanf("%s",find.word);
    tree_t result = search(find,tree);
    if (result==NULL) {
        printf("\nKhong co tu ban tim kiem.\n\n");
    }
    else {
        printf("\nTu %s xuat hien %d lan.\n\n",result->element.word,result->element.count);
    }
    printf("Danh sach cac tu xuat hien trong van ban:\n");
    inorderprint(tree);
    freeTree(tree);
    fclose(file);
}