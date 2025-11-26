#include <stdio.h>
#include <string.h>
#define MAX 999

// NGUYEN MAU HAM
int isEmpty(char s[]);
int findEmployeeIndex(char id[]);
void addEmployee();
void updateEmployee();
void deleteEmpId();
void showEmployees();
void searchEmployeeByName();
void sortEmployeesBySalary();
void menu();

int i, j, k, n; // KHAI BAO BIEN TOAN CUC

struct Employee {      // Struct luu thong tin nhan vien
    char empId[20];
    char name[50];
    char position[20];
    double baseSalary;
    int workDay;
};

struct TimeSheet {    // Struct cham cong
    char logId[20];
    char empId[20];
    char date[20];
    char status[10];
};

struct Employee employees[MAX];
int empCount = 0;

int isEmpty(char s[]) {      // H?M KI?M TRA CHU?I R?NG
    if (s == NULL) return 1;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && s[i] != '\t' &&
            s[i] != '\n' && s[i] != '\r')
            return 0;
    }
    return 1;
}

int findEmployeeIndex(char id[]) {    // T?M NH?N VI?N THEO M?
    for (i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empId, id) == 0)
            return i;
    }
    return -1;
}

int main() {
    menu();
    return 0;
}

//         MENU CH?NH
void menu() {
    int choice;

    do {
        printf("\n+----------------------------------------------------------+\n");
        printf("|          Danh sach quan ly nhan vien va cham cong        |\n");
        printf("+----------------------------------------------------------+\n");
        printf("|1. Them moi nhan vien                                     |\n");
        printf("|2. Cap nhat ho so nhan vien                               |\n");
        printf("|3. Sa thai / Xoa nhan vien                                |\n");
        printf("|4. Hien thi danh sach nhan vien                           |\n");
        printf("|5. Tra cuu nhan vien theo ten                             |\n");
        printf("|6. Sap xep danh sach                                      |\n");
        printf("|7. Cham cong                                              |\n");
        printf("|8. Xem Bang Cong                                          |\n");
        printf("|9. Thoat                                                  |\n");
        printf("+----------------------------------------------------------+\n");
        printf("Nhap lua chon: ");

        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: updateEmployee(); break;
            case 3: deleteEmpId(); break;
            case 4: showEmployees(); break;
            case 5: searchEmployeeByName(); break;
            case 6: sortEmployeesBySalary(); break;
            case 9: printf("Thoat chuong trinh!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }

    } while (choice != 9);
}
// CASE 1: THEM NHAN VIEN
void addEmployee() {

    // Kiem tra danh sach da day chua
    if (empCount >= MAX) {
        printf("Danh sach nhan vien da day!\n");
        return;
    }

    struct Employee employee;
    char temp[200];

    // Nhap ma nhan vien
    while (1) {
        printf("Nhap ma nhan vien: ");
        if (fgets(employee.empId, sizeof(employee.empId), stdin) == NULL) {
            printf("Loi nhap! Thu lai.\n");
            continue;
        }
        employee.empId[strcspn(employee.empId, "\n")] = '\0';

        if (isEmpty(employee.empId)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        if (findEmployeeIndex(employee.empId) != -1) {
            printf("Ma nhan vien da ton tai!\n");
            continue;
        }
        break;
    }

    // Nhap ten nhan vien
    while (1) {
        printf("Nhap ten nhan vien: ");
        if (fgets(employee.name, sizeof(employee.name), stdin) == NULL) {
            printf("Loi nhap!\n"); 
            continue;
        }
        employee.name[strcspn(employee.name, "\n")] = '\0';

        if (isEmpty(employee.name)) {
            printf("Ten khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap chuc vu
    while (1) {
        printf("Nhap chuc vu: ");
        if (fgets(employee.position, sizeof(employee.position), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        employee.position[strcspn(employee.position, "\n")] = '\0';

        if (isEmpty(employee.position)) {
            printf("Chuc vu khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap luong co ban
    while (1) {
        printf("Nhap luong co ban: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Luong khong duoc de trong!\n");
            continue;
        }

        if (sscanf(temp, "%lf", &employee.baseSalary) != 1 || employee.baseSalary <= 0) {
            printf("Nhap sai! Vui long nhap so duong.\n");
            continue;
        }
        break;
    }

    // Nhap ngay cong - OPTION A/B
    while (1) {
        printf("Nhap ngay cong (Chon A mac dinh = 0 hoac B tu 1->31 ngay trong thang): ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';

        // Kiem tra enter trong
        if (isEmpty(temp)) {
            printf("Ngay cong khong duoc bo trong vui long chon option A/B\n");
            continue;
        }

        // Option A mac dinh = 0
        if (temp[0] == 'A' || temp[0] == 'a') {
            employee.workDay = 0;
            break;
        }

        // Option B nhap ngay cong tu 1->31
        if (temp[0] == 'B' || temp[0] == 'b') {
            while (1) {
                printf("Nhap so ngay cong (1 -> 31): ");

                if (fgets(temp, sizeof(temp), stdin) == NULL) {
                    printf("Loi nhap!\n");
                    continue;
                }
                temp[strcspn(temp, "\n")] = '\0';

                if (isEmpty(temp)) {
                    printf("Khong duoc bo trong ngay cong, vui long nhap lai\n");
                    continue;
                }

                if (sscanf(temp, "%d", &employee.workDay) != 1 || employee.workDay <= 0) {
                    printf("Nhap sai, ngay cong phai la so duong\n");
                    continue;
                }

                if (employee.workDay > 31) {
                    printf("Nhap sai, ngay cong phai tu 1 den 31\n");
                    continue;
                }

                break;
            }
            break;
        }

        // Nhap truc tiep so ngay cong (khong chon A/B)
        int workDayTmp;
        if (sscanf(temp, "%d", &workDayTmp) == 1) {
            if (workDayTmp < 0) {
                printf("Nhap sai, ngay cong phai la so duong\n");
                continue;
            }
            if (workDayTmp > 31) {
                printf("Nhap sai, ngay cong phai tu 1 den 31\n");
                continue;
            }
            employee.workDay = workDayTmp;
            break;
        }

        printf("Lua chon khong hop le! Nhan A/B hoac nhap so.\n");
    }

    employees[empCount++] = employee;
    printf("Them nhan vien thanh cong!\n");
}

// CASE 2: Cap nhat nhan vien
void updateEmployee() {
    char id[20];
    char temp[200];
    int index;
	if (empCount == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }
    
    while (1) {
        printf("Nhap ma nhan vien can cap nhat: ");

        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (isEmpty(id)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        index = findEmployeeIndex(id);
        if (index == -1) {
            printf("Khong tim thay ma '%s'. Vui long nhap lai!\n", id);
            continue;
        }
        break;
    }

    // Nhap ten moi
    while (1) {
        printf("Nhap ten moi: ");
        if (fgets(employees[index].name, sizeof(employees[index].name), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        employees[index].name[strcspn(employees[index].name, "\n")] = '\0';

        if (isEmpty(employees[index].name)) {
            printf("Ten khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap chuc vu moi
    while (1) {
        printf("Nhap chuc vu moi: ");
        if (fgets(employees[index].position, sizeof(employees[index].position), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        employees[index].position[strcspn(employees[index].position, "\n")] = '\0';

        if (isEmpty(employees[index].position)) {
            printf("Chuc vu khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap luong moi
    while (1) {
        printf("Nhap luong co ban moi: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }

        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Luong khong duoc de trong!\n");
            continue;
        }

        if (sscanf(temp, "%lf", &employees[index].baseSalary) != 1 ||
            employees[index].baseSalary <= 0) {
            printf("Nhap sai! Vui long nhap so duong.\n");
            continue;
        }
        break;
    }

    // Nhap ngay cong moi
    while (1) {
        printf("Nhap ngay cong moi: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }

        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Ngay cong khong duoc de trong!\n");
            continue;
        }

        if (sscanf(temp, "%d", &employees[index].workDay) != 1 ||
            employees[index].workDay < 0) {
            printf("Nhap sai! Vui long nhap so nguyen.\n");
            continue;
        }
        break;
    }

    printf("Cap nhat ho so thanh cong!\n");
}

// CASE 3: Xoa nhan vien
void deleteEmpId() {
    char id[20];
    int index;

    // Nhap ma nhan vien can xoa
    while (1) {
        printf("Nhap ma nhan vien can xoa: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (isEmpty(id)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        index = findEmployeeIndex(id);
        if (index == -1) {
            printf("Khong tim thay nhan vien co ma %s!\n", id);
            return;  // neu khong tim thay thi thoat ham
        }
        break;
    }

    // Xoa nhan vien
    for (i = index; i < empCount - 1; i++) {
        employees[i] = employees[i + 1];
    }
    empCount--;

    printf("Xoa nhan vien %s thanh cong!\n", id);
}

void showEmployees() {      // CASE 4: Hien thi danh sach

    if (empCount == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }

    printf("STT | Ma NV      | Ten                      | Chuc vu            | Luong     | Ngay cong\n");
    printf("----+------------+--------------------------+--------------------+-----------+----------\n");

    for (i = 0; i < empCount; i++) {
        printf("%3d | %-10s | %-24s | %-18s | %9.2f | %8d\n", i + 1,
            employees[i].empId,
            employees[i].name,
            employees[i].position,
            employees[i].baseSalary,
            employees[i].workDay
        );
    }
}

// ham hien thi
void printEmployee(struct Employee employees) {
    printf("Ma NV: %-10s | Ten: %-20s | Chuc vu: %-15s | Luong: %8.2f | Ngay cong: %d\n",
        employees.empId, employees.name, employees.position, employees.baseSalary, employees.workDay);
}

// Case 5: Tra cuu
void searchEmployeeByName() {
    char searchName[50];
    
    if (empCount == 0) {
        printf("Danh sach nhan vien dang rong! Khong the tra cuu.\n");
        return;
    }

    while (1) {
        printf("Nhap ten nhan vien can tra cuu: ");
        if (fgets(searchName, sizeof(searchName), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        searchName[strcspn(searchName, "\n")] = '\0';

        if (isEmpty(searchName)) {
            printf("Ten tim kiem khong duoc de trong!\n");
            continue;
        }
        break;
    }
    
    // In thong bao ngay truoc khi hien thi ket qua
    printf("Da tim thay nhan vien ten %s.\n", searchName);
    printf("---- Ket qua tim kiem ----\n");

    int found = 0;

    for (i = 0; i < empCount; i++) {
        if (strstr(employees[i].name, searchName) != NULL) {
            printEmployee(employees[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Khong tim thay nhan vien nao co ten '%s'!\n", searchName);
    }
}
// CASE 6: Sap xep danh sach theo luong co ban
void sortEmployeesBySalary() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien dang trong!\n");
        return;
    }
    char choice[10];
    // Chon kieu sap xep
    while (1) {
        printf("Chon kieu sap xep (1.Tang, 2.Giam): ");

        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }

        choice[strcspn(choice, "\n")] = '\0';

        if (isEmpty(choice)) {
            printf("Lua chon khong duoc de trong!\n");
            continue;
        }

        if (choice[0] == '1' || choice[0] == '2') {
            break;
        }

        printf("Lua chon khong hop le. Vui long nhap 1 hoac 2.\n");
    }

    // Bubble Sort
    for (i = 0; i < empCount - 1; i++) {
        for (j = 0; j < empCount - i - 1; j++) {

            int condition = 0;

            if (choice[0] == '1') {   // Tang
                condition = employees[j].baseSalary > employees[j + 1].baseSalary;
            } else {                  // Gi?m
                condition = employees[j].baseSalary < employees[j + 1].baseSalary;
            }

            if (condition) {
                struct Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    printf("\n---- Danh sach sau khi sap xep ----\n");
    showEmployees();
    printf("\nSap xep thanh cong!\n");
}


