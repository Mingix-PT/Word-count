#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree_c.h"
#include "traversal.h"

FILE *file=NULL;
tree_t tree=NULL;
char filename[100000];
int count1=0;

typedef struct {
    char name[10000];
    int (*func)();
} MenuItem;

int NhapFile () {
    count1++;
    printf("\nNhap ten file: ");
    scanf("%s",filename);
    getchar();
    file=fopen(filename,"r");
    if (file==NULL) {
        printf("Loi. Khont the mo file %s.\nThoat chuong trinh...\n");
        exit(1);
    }
    char buffer[100000];
    printf("\nFile %s co noi dung nhu sau:\n",filename);
    while (fgets(buffer,sizeof(buffer),file)!=NULL) {
        printf("%s",buffer);
    }
    printf("\n\n");
    fclose(file);
    if (tree!=NULL) {
        freeTree(tree);
    }
    file=fopen(filename,"r");
    elmType temp;
    while (fscanf(file,"%s",temp.word)!=EOF) {
        InsertandCount(temp,&tree);
    }
    fclose(file);
    return 0;
}

int TimTu() {
    printf("\nNhap tu ban muon tim: ");
    elmType find;
    scanf("%s",find.word);
    getchar();
    tree_t result = search(find,tree);
    if (result==NULL) {
        printf("Khong co tu ban tim kiem.\n\n");
    }
    else {
        printf("Tu %s xuat hien %d lan.\n\n",result->element.word,result->element.count);
    }
    return 0;
}

int ThongKe () {
    printf("\nDanh sach cac tu xuat hien trong file %s:\n",filename);
    inorderprint(tree);
    printf("\n");
    return 0;
}

int Exit() {
    printf("\nCam on ban da su dung chuong trinh cua chung toi.\nThoat chuong trinh...\n\n");
    return 1;
}

int main () {
    MenuItem item[]={   {"Nhap file va hien ra man hinh.",NhapFile},
                        {"Tim tu trong file.",TimTu},
                        {"Thong ke cac tu xuat hien trong file.",ThongKe},
                        {"Thoat chuong trinh.",Exit}};
    int choice;
    int size = sizeof(item)/sizeof(item[0]);
    for (;;) {
        printf("Menu cac tinh nang cua chuong trinh:\n");
        for (int i = 0; i < size; i++) {
            printf("%d.%s\n",i+1,item[i].name);
        }
        printf("\nMoi ban nhap tinh nang ban muon dung: ");
        scanf("%d",&choice);
        getchar();
        if (choice<1 || choice>size) {
            printf("Loi. Vui long chon 1 so tu 1 den %d.\n\n",size);
            continue;
        }
        if (choice != 1 && count1 == 0 && choice != 4) {
            printf("Loi. Vui long su dung tinh nang 1 truoc khi dung cac tinh nang khac!\n\n");
            continue;
        }
        else if (item[choice-1].func()) {
            break;
        }
    }
}