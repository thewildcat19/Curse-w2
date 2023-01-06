#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#pragma warning(disable:4996)

typedef struct {
    int number;
    char name[21];
    int stages[5];
    int penalty;
    int total;
    int place;
} cyclist;


int check_size(char[30]);
int file_write(cyclist*, int, char[30]);
int file_read(cyclist*, char[30], int);
void arr_print_data(cyclist*, int,int);
void arr_print_results(cyclist*, int, int);
cyclist* arr_calc_res(cyclist*, int);
int arr_change(cyclist*, int, int, int, int);
cyclist* arr_search(cyclist*, int, int, int, int*);
int add_el(cyclist*, int, int, char[20]);
int el_swap(cyclist*, int, int);
int del_el(cyclist*, int, int);
int comp(cyclist*, cyclist*);



int main() {
    setlocale(LC_ALL, "Russian");
    int size;
    char  extension[6] = { ".txt" };
    char file_name[30];
    puts("Ââåäèòå íàçâàíèå ôàéëà â ïðåäåëàõ 30 ñèìâîëîâ (áåç óêàçàíèÿ ðàñøèðåíèÿ ôàéëà)");
    scanf("%s", file_name);
    strcat(file_name, extension);
    printf("Èìÿ ôàéëà: %s\n", file_name);
  
    size = check_size(file_name);
    cyclist* array = (cyclist*)malloc(size * sizeof(cyclist));
    file_read(array, file_name, size);
    char inp;
    int  choice = 1;

    while (choice != 9) {
        printf("Ïðîãðàììà îöåíêè ñîðåâíîâàíèé ïî âåëîñïîðòó\n"
            "Äëÿ âûâîäà èñõîäíîé òàáëèöû íàæìèòå - 1\n"
            "Äëÿ âûâîäà îòñîðòèðîâàííîãî ïî ñðåäíåìó çíà÷åíèþ ñïèñêà íàæìèòå - 2\n"
            "Äëÿ âûâîäà ðåçóëüòèðóþùåé òàáëèöû, ñîäåðæàùåé î÷êè è ìåñòà íàæìèòå - 3\n"
            "Äëÿ ïîèñêà ñïîðòñìåíà ïî øòðàôíûì î÷êàì â äèàïàçîíå íàæìèòå - 4\n"
            "Äëÿ èçìåíåíèÿ çíà÷åíèé ýòàïà èãðîêà íàæìèòå - 5\n"
            "Äëÿ çàïèñè çíà÷åíèé â ôàéë íàæìèòå - 6\n"
            "Äëÿ äîáàâëåíèÿ ýëåìåíòà íàæìèòå - 7\n"
            "Äëÿ óäàëåíèÿ ýëåìåíòà íàæìèòå - 8\n"
            "Äëÿ âûõîäà èç ïðîãðàììû íàæìèòå - 9\n"
        );
        scanf_s("\n%c", &inp);
        
        choice = atoi(&inp);
      
        if (choice > 0 && choice <= 9) {
            switch (choice) {
            case 1:
                system("cls");
                arr_print_data(array, size, 0);
                break;
            case 2:
                system("cls");
                qsort(array, size, sizeof(cyclist), comp);
                arr_print_data(array, size, 1);
                break;
            case 3:
                system("cls");
                arr_print_results(arr_calc_res(array, size), size, 0);
                break;
            case 4:
                system("cls");
                printf("Ââåäèòå çíà÷åíèÿ íèæíåãî è âåðõíåãî ïðåäåëîâ äèàïàçîíà:");
                int ub = 0, lb = 0;
                int sz = 0;
                scanf("%d", &lb);
                scanf("%d", &ub);
                arr_print_results(arr_search(array, size, lb, ub, &sz), sz, 1);
                printf("Ïîêàçàíî %d çàïèñåé\n", sz);
                break;
            case 5:
                system("cls");
                printf("Íàïèøèòå íîìåð èãðîêà , ýòàïà(äëÿ øòðàôíûõ î÷êîâ ââåäèòå - 6) è íîâîå çíà÷åíèå:");
                int pl_numb, pl_st, pl_val, result;
                scanf("%d %d %d", &pl_numb, &pl_st, &pl_val);
                (pl_numb > 0 && pl_st > 0 && pl_st < 6 && pl_val>0) ? (arr_change(array, size, pl_numb, pl_st, pl_val) == 1 ? printf("Èçìåíåíèå âûïîëíåíî óñïåøíî!\n") : printf("Çíà÷åíèå íå íàéäåíî!\n")) : printf("Íåâåðíûé ââîä!");
                break;
            case 6:
                file_write(array, size, file_name);
                printf("Ñîõðàíåíî óñïåøíî!\n");
                break;

            case 7:
                system("cls");
                printf("Íàïèøèòå íîìåð íîâîãî èãðîêà è èìÿ:");
                char pl_name[20] = { 0 }; pl_numb;
                scanf("%d", &pl_numb);
                fgets(pl_name, 20, stdin);
                pl_name[strlen(pl_name) - 1] = 0;
                if (pl_numb > 0 && ((strlen(pl_name)) > 1)) {
                    array = (cyclist*)realloc(array, ++size * sizeof(cyclist));
                    add_el(array, size, pl_numb, pl_name);
                }
                else { printf("Îøèáêà!ïîâòîðèòå îïåðàöèþ\n"); }
                break;
            case 8:
                system("cls");
                arr_print_data(array, size, 0);
                printf("Íàïèøèòå íîìåð èãðîêà, êîòîðîãî òðåáóåòñÿ óäàëèòü:");
                scanf("%d", &pl_numb);
                for (int i = 0; i < size; i++) {
                    if (array[i].number == pl_numb) {
                        size > 0 && pl_numb > 0 ? del_el(array, size, pl_numb) : printf("Ðàçìåð ìàññèâà - 0, óäàëÿòü íå÷åãî!\n");
                        size > 0 && pl_numb > 0 ? array = (cyclist*)realloc(array, --size * sizeof(cyclist)) : printf("Îøèáêà!ïîâòîðèòå îïåðàöèþ\n");
                    }
                }
                system("cls");
                break;
            }
        }
        else {
            system("cls");
            printf("Îøèáêà! Ïîâòîðèòå ââîä!\n");
        }
    };
    free(array);
    exit(0);
}


int check_size(char fname[30])
{
    FILE* S2 = fopen(fname, "rt");
    if (S2 == NULL) {
        puts("Íå óäàëîñü îòêðûòü ôàéë");
        exit(0);
    }
    int size;
    int k = 0;
    while (!feof(S2)) {
        if (fgetc(S2) == '\n') {
            k++;
        }
    }
    size = k;
    fclose(S2);
    return size;
}

int file_read(cyclist* array, char fname[30], int size)
{
    system("cls");
    FILE* S2 = fopen(fname, "rt");
    if (S2 == NULL) {
        puts("Íå óäàëîñü îòêðûòü ôàéë");
        exit(0);
    }
    int i = 0;
    int k = 0;
    fseek(S2, 0, SEEK_SET);
    while (!feof(S2)) {
        fscanf(S2, "|%5d|", &(array + i)->number);
        char c[21];
        fgets(c, 21, S2);
        strcpy(&array[i].name, c);
        fscanf(S2, "|%5d|%5d|%5d|%5d|%5d|%13d|\n", &(array + i)->stages[0], &(array + i)->stages[1], &(array + i)->stages[2], &(array + i)->stages[3], &(array + i)->stages[4], &(array + i)->penalty);
        i++;
    }
    fclose(S2);
    printf("Óñïåøíî èìïîðòèðîâàíî %d çàïèñåé!\n", i);
    return i;
}

int file_write(cyclist* array, int size, char fname[30])
{
    //çàïèñü â ôàéë
    system("cls");
    FILE* S1 = fopen(fname, "w");
    for (int i = 0; i < size; i++) {
        fprintf(S1, "|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%13d|\n", array[i].number, array[i].name, array[i].stages[0], array[i].stages[1], array[i].stages[2], array[i].stages[3], array[i].stages[4], array[i].penalty);
    };

}

void arr_print_data(cyclist* a, int size, int mode)
{
    if (mode == 0) {
        printf("\nÒàáëèöà äàííûõ\n");
        printf("|%2s|%20s|%5s|%5s|%5s|%5s|%5s|%5s|\n", "Íîìåð", "Èìÿ Ôàìèëèÿ", "Ýòàï1", "Ýòàï2", "Ýòàï3", "Ýòàï4", "Ýòàï5", "Øòðàôíûå î÷êè");
        for (int i = 0; i < size; i++) {
            printf("|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%13d|\n", a[i].number, a[i].name, a[i].stages[0], a[i].stages[1], a[i].stages[2], a[i].stages[3], a[i].stages[4], a[i].penalty);
        };
    }

    else {
        printf("\nÒàáëèöà äàííûõ\n");
        printf("|%2s|%20s|%5s|%5s|%5s|%5s|%5s|%7s|%5s|\n", "Íîìåð", "Èìÿ Ôàìèëèÿ", "Ýòàï1", "Ýòàï2", "Ýòàï3", "Ýòàï4", "Ýòàï5", "Ñðåäíåå", "Øòðàôíûå î÷êè");
        for (int i = 0; i < size; i++) {
            printf("|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%7.1f|%13d|\n", a[i].number, a[i].name, a[i].stages[0], a[i].stages[1], a[i].stages[2], a[i].stages[3], a[i].stages[4], ((a[i].stages[0] + a[i].stages[1] + a[i].stages[2] + a[i].stages[3] + a[i].stages[4]) / 5.), a[i].penalty);
        };
    }
}

void arr_print_results(cyclist* a, int size, int mode)
{
    if (mode == 0) {
        printf("\nÒàáëèöà ðåçóëüòàòîâ\n");
        printf("|%20s|%5s|%5s|\n", "Èìÿ Ôàìèëèÿ", "Îáùèå î÷êè", "Ìåñòî");
        for (int i = 0; i < size; i++) {
            printf("|%20s|%10d|%5d|\n", a[i].name, a[i].total, a[i].place);
        };
    }
    else {
        printf("\nÒàáëèöà äàííûõ\n");
        printf("|%2s|%20s|%5s|\n", "Íîìåð", "Èìÿ Ôàìèëèÿ", "Øòðàôíûå î÷êè");
        for (int i = 0; i < size; i++) {
            printf("|%5d|%20s|%13d|\n", a[i].number, a[i].name, a[i].penalty);
        }
    }
}

cyclist* arr_calc_res(cyclist* a, int size)
{
    for (int i = 0; i < size; i++)
        a[i].total = (a[i].stages[0] + a[i].stages[1] + a[i].stages[2] + a[i].stages[3] + a[i].stages[4]) - a[i].penalty;
    for (int i = 0; i < size; i++) {
        int r = 1;
        for (int j = 0; j < size; j++) {
            if (i != j && a[i].total < a[j].total)
                r += 1;
        }
        a[i].place = r;
    }
    return a;
}

cyclist* arr_search(cyclist* a, int size, int lowerbound, int upperbound, int* sz)
{
    int k = 0;
    cyclist* b = (cyclist*)malloc(size * sizeof(cyclist));
    for (int i = 0; i < size; i++) {
        if (a[i].penalty >= lowerbound && a[i].penalty <= upperbound) {
            b[k].number = a[i].number;
            strcpy(b[k].name, a[i].name);
            b[k].penalty = a[i].penalty;
            k++;
        }
    }
    *sz = k;
    b = (cyclist*)realloc(b, *sz * sizeof(cyclist));
    return b;
}

int arr_change(cyclist* a, int size, int pl_numb, int pl_st, int pl_val)
{
    int result;
    for (int i = 0; i < size; i++) {
        if (a[i].number == pl_numb) {
            pl_st > 0 && pl_st < 6 ? a[i].stages[pl_st - 1] = pl_val : false;
            pl_st == 6 ? a[i].penalty = pl_val : false;
            result = 1;
            break;
        }
        else {
            result = 0;
        }
    }
    return result;
}

int add_el(cyclist* a, int size, int nmb, char nm[20]) {
    strncpy(a[size - 1].name, nm, 20);
    (a + (size - 1))->number = nmb;
    for (int i = 0; i < 5; i++) {
        a[size - 1].stages[i] = 0;
    }
    a[size - 1].penalty = 0;
    return 1;
};

int el_swap(cyclist* a, int ind1, int ind2) {
    cyclist tmp;
    tmp = a[ind1];
    a[ind1] = a[ind2];
    a[ind2] = tmp;
}

int del_el(cyclist* a, int size, int nmb) {
    cyclist tmp; int k = 0;
    while (a[k].number != nmb)k++;
    el_swap(a, size - 1, k);
};

int comp(cyclist* a, cyclist* b)
{
    if (((b->stages[0] + b->stages[1] + b->stages[2] + b->stages[3] + b->stages[4]) / 5.) < ((a->stages[0] + a->stages[1] + a->stages[2] + a->stages[3] + a->stages[4]) / 5.)) {
        return -1;
    }
    else if (((b->stages[0] + b->stages[1] + b->stages[2] + b->stages[3] + b->stages[4]) / 5.) > ((a->stages[0] + a->stages[1] + a->stages[2] + a->stages[3] + a->stages[4]) / 5.)) {
        return 1;
    }
    else if (((b->stages[0] + b->stages[1] + b->stages[2] + b->stages[3] + b->stages[4]) / 5.) == ((a->stages[0] + a->stages[1] + a->stages[2] + a->stages[3] + a->stages[4]) / 5.)) {
        return 0;
    }
};
