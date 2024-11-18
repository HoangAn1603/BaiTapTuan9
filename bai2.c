#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc node
typedef struct Node {
    char word[50];           // Lưu từ
    int count;               // Đếm số lần xuất hiện của từ
    struct Node* next;       // Con trỏ tới node tiếp theo
} Node;

// Hàm tạo một node mới
Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->count = 1; // Ban đầu từ xuất hiện 1 lần
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm một từ vào danh sách (hoặc tăng đếm nếu từ đã tồn tại)
void ThemTu(Node** head, const char* word) {
    Node* current = *head;
    Node* prev = NULL;

    // Kiểm tra xem từ đã tồn tại chưa
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            current->count++; // Tăng đếm
            return;
        }
        prev = current;
        current = current->next;
    }

    // Nếu từ chưa tồn tại, thêm node mới vào cuối danh sách
    Node* newNode = createNode(word);
    if (*head == NULL) {
        *head = newNode; // Danh sách rỗng
    } else {
        prev->next = newNode;
    }
}

// Hàm tìm từ xuất hiện nhiều nhất
Node* TimTu(Node* head) {
    Node* mostFrequent = head;
    while (head != NULL) {
        if (head->count > mostFrequent->count) {
            mostFrequent = head;
        }
        head = head->next;
    }
    return mostFrequent;
}

// Hàm loại bỏ từ láy (từ giống nhau lặp lại trong cùng một từ)
void XoaTuLayGiongnhau(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        if (strlen(current->word) >= 2 && 
            current->word[0] == current->word[1]) { // Kiểm tra từ láy
            current->count--; // Giảm đếm
        }
        current = current->next;
    }
}

// Hàm đếm số từ vựng xuất hiện trong câu
int DemTu(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Hàm in danh sách các từ
void printWords(Node* head) {
    while (head != NULL) {
        printf("Tu: %s, So lan xuat hien: %d\n", head->word, head->count);
        head = head->next;
    }
}

// Hàm giải phóng bộ nhớ danh sách liên kết
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Hàm chính
int main() {
    Node* head = NULL;

    // Ví dụ câu: "xanh xanh đỏ đỏ tím tím vàng"
    char sentence[] = "xanh xanh do do tim tim vang vang";
    char* word = strtok(sentence, " ");

    // Tách các từ trong câu và thêm vào danh sách liên kết
    while (word != NULL) {
        ThemTu(&head, word);
        word = strtok(NULL, " ");
    }

    // In danh sách các từ ban đầu
    printf("Danh sach cac tu:\n");
    printWords(head);

    // Tìm từ xuất hiện nhiều nhất
    Node* mostFrequent = TimTu(head);
    printf("\nTu xuat hien nhieu nhat: %s (%d lan)\n", mostFrequent->word, mostFrequent->count);

    // Loại bỏ từ láy
    XoaTuLayGiongnhau(&head);
    printf("\nSau khi loai bo tu lay:\n");
    printWords(head);

    // Đếm số từ vựng
    int uniqueWordCount = DemTu(head);
    printf("\nSo tu: %d\n", uniqueWordCount);

    // Giải phóng bộ nhớ
    freeList(head);

    return 0;
}
