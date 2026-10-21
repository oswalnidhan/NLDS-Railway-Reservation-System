#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct searchName{
    char name;
    bool is_end;
    struct searchName *child;
    struct searchName *sibling;
};
struct searchName *root = NULL;

struct pque{
    int age;
    struct pque *next;
};
struct pque *start = NULL;

struct searchName* createNode(char ch){
    struct searchName *newNode = (struct searchName*)malloc(sizeof(struct searchName));
    newNode->name = ch;
    newNode->is_end = false;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

void addStation(char *station){
    if(root == NULL){
        root = createNode('\0');
    }
    struct searchName *curr = root;
    for(int i = 0; station[i] != '\0'; i++){
        char ch = station[i];
        if(curr->child == NULL) {
            curr->child = createNode(ch);
            curr = curr->child;
        }else{
            struct searchName *child = curr->child;
            struct searchName *prev = NULL;
            while (child != NULL && child->name != ch){
                prev = child;
                child = child->sibling;
            }
            if(child == NULL){
                prev->sibling = createNode(ch);
                curr = prev->sibling;
            }else{
                curr = child;
            }
        }
    }
    curr->is_end = true;
}

void initStations(){
    addStation("pune");
    addStation("mumbai");
    addStation("delhi");
    addStation("nagpur");
    addStation("patna");
}

void searchStation(){
    char station[100];
    printf("Enter station name to search: ");
    if(scanf("%99s", station) != 1){
        printf("Invalid input.\n");
        return;
    }
    if(root == NULL || root->child == NULL){
        printf("Station database is empty.\n");
        return;
    }
    struct searchName *curr = root->child;
    for(int i = 0; station[i] != '\0'; i++){
        while(curr != NULL && curr->name != station[i]){
            curr = curr->sibling;
        }
        if(curr == NULL) {
            printf("Station '%s' not found.\n", station);
            return;
        }
        if(station[i + 1] != '\0'){
            curr = curr->child;
        }
    }
    if(curr != NULL && curr->is_end){
        printf("Station '%s' found! Available for booking.\n", station);
    }else{
        printf("Station '%s' not found.\n", station);
    }
}

void lowerSeatAlloc(){
    int inage;
    printf("Enter your age = ");
    if(scanf("%d", &inage) != 1){
        printf("Invalid input!\n");
        return;
    }
    if(inage < 60){
        printf("Person under 60 cant ask for lower birth\n");
        printf("Lower birth is strictly reserved only for senior citizens\n");
        return;
    }
    struct pque *newnode = (struct pque*)malloc(sizeof(struct pque));
    if(newnode == NULL){
        printf("Failed to register your age!\n");
        printf("Please try again\n");
        return;
    }
    newnode->age = inage;
    newnode->next = NULL;
    if(start == NULL || inage > start->age){
        newnode->next = start;
        start = newnode;
    }else{
        struct pque *temp = start;
        while(temp->next != NULL && temp->next->age >= inage){
            temp = temp->next;
        }
        newnode->next = temp->next;
        temp->next = newnode;
    }
    printf("Lower berth requested successfully for age %d!\n", inage);
}

void checkQue(){
    if(start == NULL){
        printf("The queue is currently empty.\n");
        return;
    }
    int myAge;
    printf("Enter your age to check queue position: ");
    if(scanf("%d", &myAge) != 1){
        printf("Invalid input!\n");
        return;
    }
    struct pque *temp = start;
    int position = 1;
    bool found = false;
    while(temp != NULL){
        if (temp->age == myAge){
            printf("Your priority position in the queue is: %d\n", position);
            found = true;
            break;
        }
        position++;
        temp = temp->next;
    }
    if(!found){
        printf("No entry found for age %d in the priority queue.\n", myAge);
    }
}

int main() {
    initStations();
    int choice;
    do {
        printf("\n~~~MAIN MENU~~~\n");
        printf("1. Search Station Name\n2. Lower seat queue\n3. Check my Queue number\n4. Exit\n");
        printf("Enter your choice = ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }
        switch(choice){
            case 1:
                printf("Enter all letters in lowercase\n");
                searchStation();
                break;
            case 2:
                lowerSeatAlloc();
                break;
            case 3:
                checkQue();
                break;
            case 4:
                printf("Thank you for using this software!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    }while(choice != 4);
    return 0;
}


