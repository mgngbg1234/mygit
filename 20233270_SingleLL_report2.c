#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    char name[50];
    char phone[20];
    struct Contact* next;
} Contact;

Contact* addContact(Contact* head, const char* name, const char* phone) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;

    if (head == NULL) {
        return newContact;
    }

    Contact* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newContact;
    return head;
}

Contact* deleteContact(Contact* head, const char* name) {
    Contact* current = head;
    Contact* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                Contact* temp = head;
                head = head->next;
                free(temp);
            } else {
                prev->next = current->next;
                free(current);
            }
            printf("'%s' 연락처 삭제 완료\n", name);
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("'%s' 연락처를 찾을 수 없습니다\n", name);
    return head;
}

void searchContact(Contact* head, const char* name) {
    Contact* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("'%s' 연락처를 찾을 수 없습니다\n", name);
}

void printContacts(Contact* head) {
    Contact* current = head;
    printf("전화번호부 목록:\n");
    while (current != NULL) {
        printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
        current = current->next;
    }
}

void freeList(Contact* head) {
    Contact* current = head;
    while (current != NULL) {
        Contact* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Contact* phonebook = NULL;

    phonebook = addContact(phonebook, "Alice", "010-1234-5678");
    phonebook = addContact(phonebook, "Bob", "010-2345-6789");
    phonebook = addContact(phonebook, "Charlie", "010-3456-7890");

    printContacts(phonebook);

    printf("\n[검색] 이름: Bob\n");
    searchContact(phonebook, "Bob");

    printf("\n[삭제] 이름: Alice\n");
    phonebook = deleteContact(phonebook, "Alice");

    printf("\n[전체 출력]\n");
    printContacts(phonebook);

    freeList(phonebook);
    return 0;
}
