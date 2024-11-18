#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USB_SIZE 32 * 1024 // Dung lượng USB (32GB) chuyển sang MB

// Định nghĩa cấu trúc FileNode
struct FileNode {
    char name[100];           // Tên file
    int size;                 // Kích thước file (MB)
    char date[11];            // Ngày tạo file (yyyy-mm-dd)
    struct FileNode* next;    // Con trỏ đến node tiếp theo
};

// Hàm tạo một node mới
struct FileNode* createNode(const char* name, int size, const char* date) {
    struct FileNode* newNode = (struct FileNode*)malloc(sizeof(struct FileNode));
    strcpy(newNode->name, name);
    newNode->size = size;
    strcpy(newNode->date, date);
    newNode->next = NULL;
    return newNode;
}

// Hàm chèn file vào danh sách liên kết theo thứ tự thời gian
void insertFile(struct FileNode** head, const char* name, int size, const char* date) {
    struct FileNode* newNode = createNode(name, size, date);
    if (*head == NULL || strcmp((*head)->date, date) > 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct FileNode* current = *head;
        while (current->next != NULL && strcmp(current->next->date, date) <= 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Hàm tính tổng kích thước các file
int TinhTong(struct FileNode* head) {
    int tongSize = 0;
    while (head != NULL) {
        tongSize += head->size;
        head = head->next;
    }
    return tongSize;
}

// Hàm xóa file có kích thước nhỏ nhất
void XoaFileMin(struct FileNode** head) {
    if (*head == NULL) return;

    struct FileNode* current = *head;
    struct FileNode* prev = NULL;
    struct FileNode* min = current;
    struct FileNode* minPrev = NULL;

    while (current != NULL) {
        if (current->size < min->size) {
            min = current;
            minPrev = prev;
        }
        prev = current;
        current = current->next;
    }

    if (minPrev == NULL) { // Node nhỏ nhất là đầu danh sách
        *head = min->next;
    } else {
        minPrev->next = min->next;
    }
    free(min); // Giải phóng bộ nhớ
}

// Hàm sao lưu các file vào USB
void SaoLuuUSB(struct FileNode** head) {
    int tongSize = TinhTong(*head);
    while (tongSize > USB_SIZE) {
        XoaFileMin(head);
        tongSize = TinhTong(*head);
    }
}

// Hàm in danh sách các file
void printFile(struct FileNode* head) {
    while (head != NULL) {
        printf("File: %s, Size: %dMB, Date: %s\n", head->name, head->size, head->date);
        head = head->next;
    }
}

// Hàm chính
int main() {
    struct FileNode* head = NULL;

    // Thêm file vào danh sách
    insertFile(&head, "file1.txt", 500, "2024-11-02");
    insertFile(&head, "file2.txt", 200, "2024-11-05");
    insertFile(&head, "file3.txt", 100, "2024-10-28");
    insertFile(&head, "file4.txt", 800, "2024-11-10");

    printf("Danh sach cac file ban dau:\n");
    printFile(head);

    printf("\nTong kich thuoc cac file: %dMB\n", TinhTong(head));

    // Sao lưu các file vào USB
    printf("\nThuc hien sao luu vao USB (32GB):\n");
    SaoLuuUSB(&head);
    printFile(head);

    return 0;
}
