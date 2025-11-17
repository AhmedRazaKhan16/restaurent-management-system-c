#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_MEALS 50
#define MAX_TABLES 20
#define MAX_ROOMS 15
#define MAX_ORDERS 100

// Structure definitions
typedef struct {
    char username[50];
    char password[50];
    int isAdmin;
} User;

typedef struct {
    int id;
    char name[50];
    float price;
    int available;
} Meal;

typedef struct {
    int tableNo;
    int isBooked;
    char bookedBy[50];
} Table;

typedef struct {
    int roomNo;
    int isBooked;
    char bookedBy[50];
} Room;

typedef struct {
    int orderId;
    char username[50];
    int mealId;
    char mealName[50];
    int quantity;
    float price;
    int tableNo;
    int roomNo;
    char date[20];
} Order;

// Global variables
User users[MAX_USERS];
Meal meals[MAX_MEALS];
Table tables[MAX_TABLES];
Room rooms[MAX_ROOMS];
Order orders[MAX_ORDERS];
int userCount = 0;
int mealCount = 0;
int tableCount = 0;
int roomCount = 0;
int orderCount = 0;
User currentUser;

// Function prototypes
void initializeSystem();
void saveData();
void loadData();
void mainMenu();
void login();
void registerUser();
void adminMenu();
void userMenu();
void manageMeals();
void viewSales();
void viewBookings();
void orderMeal();
void bookTable();
void bookRoom();
void viewBill();
void generateBill(char username[]);
int isRoomAvailable(int roomNo);
int isTableAvailable(int tableNo);

int main() {
    initializeSystem();
    loadData();
    mainMenu();
    return 0;
}

void initializeSystem() {
    // Initialize default admin
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin123");
    users[0].isAdmin = 1;
    userCount = 1;

    // Initialize some sample meals
    meals[0].id = 1; strcpy(meals[0].name, "Chicken Biryani"); meals[0].price = 250.0; meals[0].available = 1;
    meals[1].id = 2; strcpy(meals[1].name, "Butter Chicken"); meals[1].price = 350.0; meals[1].available = 1;
    meals[2].id = 3; strcpy(meals[2].name, "Paneer Tikka"); meals[2].price = 280.0; meals[2].available = 1;
    meals[3].id = 4; strcpy(meals[3].name, "Garlic Naan"); meals[3].price = 50.0; meals[3].available = 1;
    meals[4].id = 5; strcpy(meals[4].name, "Coke"); meals[4].price = 40.0; meals[4].available = 1;
    mealCount = 5;

    // Initialize tables
    for(int i = 0; i < MAX_TABLES; i++) {
        tables[i].tableNo = i + 1;
        tables[i].isBooked = 0;
        strcpy(tables[i].bookedBy, "");
    }
    tableCount = MAX_TABLES;

    // Initialize rooms
    for(int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNo = i + 1;
        rooms[i].isBooked = 0;
        strcpy(rooms[i].bookedBy, "");
    }
    roomCount = MAX_ROOMS;
}

void saveData() {
    FILE *fp;
    
    // Save users
    fp = fopen("users.csv", "w");
    for(int i = 0; i < userCount; i++) {
        fprintf(fp, "%s,%s,%d\n", users[i].username, users[i].password, users[i].isAdmin);
    }
    fclose(fp);

    // Save meals
    fp = fopen("meals.csv", "w");
    for(int i = 0; i < mealCount; i++) {
        fprintf(fp, "%d,%s,%.2f,%d\n", meals[i].id, meals[i].name, meals[i].price, meals[i].available);
    }
    fclose(fp);

    // Save tables
    fp = fopen("tables.csv", "w");
    for(int i = 0; i < tableCount; i++) {
        fprintf(fp, "%d,%d,%s\n", tables[i].tableNo, tables[i].isBooked, tables[i].bookedBy);
    }
    fclose(fp);

    // Save rooms
    fp = fopen("rooms.csv", "w");
    for(int i = 0; i < roomCount; i++) {
        fprintf(fp, "%d,%d,%s\n", rooms[i].roomNo, rooms[i].isBooked, rooms[i].bookedBy);
    }
    fclose(fp);

    // Save orders
    fp = fopen("orders.csv", "w");
    for(int i = 0; i < orderCount; i++) {
        fprintf(fp, "%d,%s,%d,%s,%d,%.2f,%d,%d,%s\n", 
                orders[i].orderId, orders[i].username, orders[i].mealId, 
                orders[i].mealName, orders[i].quantity, orders[i].price,
                orders[i].tableNo, orders[i].roomNo, orders[i].date);
    }
    fclose(fp);
}

void loadData() {
    FILE *fp;
    char line[200];
    
    // Load users
    fp = fopen("users.csv", "r");
    if(fp) {
        userCount = 0;
        while(fgets(line, sizeof(line), fp)) {
            sscanf(line, "%[^,],%[^,],%d", users[userCount].username, 
                   users[userCount].password, &users[userCount].isAdmin);
            userCount++;
        }
        fclose(fp);
    }

    // Load meals
    fp = fopen("meals.csv", "r");
    if(fp) {
        mealCount = 0;
        while(fgets(line, sizeof(line), fp)) {
            sscanf(line, "%d,%[^,],%f,%d", &meals[mealCount].id, meals[mealCount].name,
                   &meals[mealCount].price, &meals[mealCount].available);
            mealCount++;
        }
        fclose(fp);
    }

    // Load tables
    fp = fopen("tables.csv", "r");
    if(fp) {
        tableCount = 0;
        while(fgets(line, sizeof(line), fp)) {
            sscanf(line, "%d,%d,%[^,\n]", &tables[tableCount].tableNo,
                   &tables[tableCount].isBooked, tables[tableCount].bookedBy);
            tableCount++;
        }
        fclose(fp);
    }

    // Load rooms
    fp = fopen("rooms.csv", "r");
    if(fp) {
        roomCount = 0;
        while(fgets(line, sizeof(line), fp)) {
            sscanf(line, "%d,%d,%[^,\n]", &rooms[roomCount].roomNo,
                   &rooms[roomCount].isBooked, rooms[roomCount].bookedBy);
            roomCount++;
        }
        fclose(fp);
    }

    // Load orders
    fp = fopen("orders.csv", "r");
    if(fp) {
        orderCount = 0;
        while(fgets(line, sizeof(line), fp)) {
            sscanf(line, "%d,%[^,],%d,%[^,],%d,%f,%d,%d,%[^,\n]",
                   &orders[orderCount].orderId, orders[orderCount].username,
                   &orders[orderCount].mealId, orders[orderCount].mealName,
                   &orders[orderCount].quantity, &orders[orderCount].price,
                   &orders[orderCount].tableNo, &orders[orderCount].roomNo,
                   orders[orderCount].date);
            orderCount++;
        }
        fclose(fp);
    }
}

void mainMenu() {
    int choice;
    do {
        printf("\n=== ROYAL HOTEL MANAGEMENT SYSTEM ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: login(); break;
            case 2: registerUser(); break;
            case 3: 
                saveData();
                printf("Thank you for using our system!\n");
                exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
}

void login() {
    char username[50], password[50];
    int found = 0;
    
    printf("\n=== LOGIN ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0 && 
           strcmp(users[i].password, password) == 0) {
            currentUser = users[i];
            found = 1;
            printf("Login successful! Welcome %s\n", username);
            
            if(currentUser.isAdmin) {
                adminMenu();
            } else {
                userMenu();
            }
            break;
        }
    }
    
    if(!found) {
        printf("Invalid username or password!\n");
    }
}

void registerUser() {
    if(userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }
    
    printf("\n=== REGISTER ===\n");
    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    
    // Check if username already exists
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, users[userCount].username) == 0) {
            printf("Username already exists!\n");
            return;
        }
    }
    
    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    
    users[userCount].isAdmin = 0;
    userCount++;
    printf("Registration successful! You can now login.\n");
    saveData();
}

void adminMenu() {
    int choice;
    do {
        printf("\n=== ADMIN PANEL ===\n");
        printf("1. Manage Meals\n");
        printf("2. View Sales Report\n");
        printf("3. View Bookings\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: manageMeals(); break;
            case 2: viewSales(); break;
            case 3: viewBookings(); break;
            case 4: printf("Logged out successfully!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 4);
}

void userMenu() {
    int choice;
    do {
        printf("\n=== USER PANEL ===\n");
        printf("1. Order Meal\n");
        printf("2. Book Table\n");
        printf("3. Book Room\n");
        printf("4. View My Bill\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: orderMeal(); break;
            case 2: bookTable(); break;
            case 3: bookRoom(); break;
            case 4: generateBill(currentUser.username); break;
            case 5: printf("Logged out successfully!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);
}

void manageMeals() {
    int choice;
    do {
        printf("\n=== MANAGE MEALS ===\n");
        printf("1. Add Meal\n");
        printf("2. View Meals\n");
        printf("3. Update Meal\n");
        printf("4. Delete Meal\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: {
                if(mealCount >= MAX_MEALS) {
                    printf("Meal limit reached!\n");
                    break;
                }
                printf("Enter meal name: ");
                scanf(" %[^\n]", meals[mealCount].name);
                printf("Enter price: ");
                scanf("%f", &meals[mealCount].price);
                meals[mealCount].id = mealCount + 1;
                meals[mealCount].available = 1;
                mealCount++;
                printf("Meal added successfully!\n");
                saveData();
                break;
            }
            case 2: {
                printf("\n=== AVAILABLE MEALS ===\n");
                printf("ID\tName\t\tPrice\n");
                for(int i = 0; i < mealCount; i++) {
                    if(meals[i].available) {
                        printf("%d\t%-15s\t%.2f\n", meals[i].id, meals[i].name, meals[i].price);
                    }
                }
                break;
            }
            case 3: {
                int id;
                printf("Enter meal ID to update: ");
                scanf("%d", &id);
                for(int i = 0; i < mealCount; i++) {
                    if(meals[i].id == id) {
                        printf("Enter new name: ");
                        scanf(" %[^\n]", meals[i].name);
                        printf("Enter new price: ");
                        scanf("%f", &meals[i].price);
                        printf("Meal updated successfully!\n");
                        saveData();
                        return;
                    }
                }
                printf("Meal not found!\n");
                break;
            }
            case 4: {
                int id;
                printf("Enter meal ID to delete: ");
                scanf("%d", &id);
                for(int i = 0; i < mealCount; i++) {
                    if(meals[i].id == id) {
                        meals[i].available = 0;
                        printf("Meal deleted successfully!\n");
                        saveData();
                        return;
                    }
                }
                printf("Meal not found!\n");
                break;
            }
        }
    } while(choice != 5);
}

void viewSales() {
    printf("\n=== SALES REPORT ===\n");
    float totalRevenue = 0;
    
    printf("OrderID\tUser\tMeal\tQty\tPrice\tTable\tRoom\tDate\n");
    for(int i = 0; i < orderCount; i++) {
        printf("%d\t%s\t%s\t%d\t%.2f\t%d\t%d\t%s\n",
               orders[i].orderId, orders[i].username, orders[i].mealName,
               orders[i].quantity, orders[i].price, orders[i].tableNo,
               orders[i].roomNo, orders[i].date);
        totalRevenue += orders[i].price * orders[i].quantity;
    }
    printf("\nTotal Revenue: %.2f\n", totalRevenue);
}

void viewBookings() {
    printf("\n=== TABLE BOOKINGS ===\n");
    printf("TableNo\tStatus\tBooked By\n");
    for(int i = 0; i < tableCount; i++) {
        printf("%d\t%s\t%s\n", tables[i].tableNo, 
               tables[i].isBooked ? "Booked" : "Available", 
               tables[i].bookedBy);
    }
    
    printf("\n=== ROOM BOOKINGS ===\n");
    printf("RoomNo\tStatus\tBooked By\n");
    for(int i = 0; i < roomCount; i++) {
        printf("%d\t%s\t%s\n", rooms[i].roomNo,
               rooms[i].isBooked ? "Booked" : "Available",
               rooms[i].bookedBy);
    }
}

void orderMeal() {
    int mealId, quantity, tableNo, roomNo;
    
    printf("\n=== ORDER MEAL ===\n");
    printf("Available Meals:\n");
    printf("ID\tName\t\tPrice\n");
    for(int i = 0; i < mealCount; i++) {
        if(meals[i].available) {
            printf("%d\t%-15s\t%.2f\n", meals[i].id, meals[i].name, meals[i].price);
        }
    }
    
    printf("Enter Meal ID: ");
    scanf("%d", &mealId);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);
    printf("Enter Table No (0 if none): ");
    scanf("%d", &tableNo);
    printf("Enter Room No (0 if none): ");
    scanf("%d", &roomNo);
    
    // Validate meal
    Meal *selectedMeal = NULL;
    for(int i = 0; i < mealCount; i++) {
        if(meals[i].id == mealId && meals[i].available) {
            selectedMeal = &meals[i];
            break;
        }
    }
    
    if(!selectedMeal) {
        printf("Invalid meal ID!\n");
        return;
    }
    
    // Validate table/room availability
    if(tableNo > 0 && !isTableAvailable(tableNo)) {
        printf("Table %d is not available!\n", tableNo);
        return;
    }
    
    if(roomNo > 0 && !isRoomAvailable(roomNo)) {
        printf("Room %d is not available!\n", roomNo);
        return;
    }
    
    // Create order
    orders[orderCount].orderId = orderCount + 1;
    strcpy(orders[orderCount].username, currentUser.username);
    orders[orderCount].mealId = mealId;
    strcpy(orders[orderCount].mealName, selectedMeal->name);
    orders[orderCount].quantity = quantity;
    orders[orderCount].price = selectedMeal->price;
    orders[orderCount].tableNo = tableNo;
    orders[orderCount].roomNo = roomNo;
    strcpy(orders[orderCount].date, "2024-01-01"); // You can implement date functionality
    
    orderCount++;
    printf("Order placed successfully!\n");
    saveData();
}

void bookTable() {
    int tableNo;
    
    printf("\n=== BOOK TABLE ===\n");
    printf("Available Tables:\n");
    for(int i = 0; i < tableCount; i++) {
        if(!tables[i].isBooked) {
            printf("Table %d\n", tables[i].tableNo);
        }
    }
    
    printf("Enter Table No to book: ");
    scanf("%d", &tableNo);
    
    if(!isTableAvailable(tableNo)) {
        printf("Table %d is not available!\n", tableNo);
        return;
    }
    
    // Book the table
    for(int i = 0; i < tableCount; i++) {
        if(tables[i].tableNo == tableNo) {
            tables[i].isBooked = 1;
            strcpy(tables[i].bookedBy, currentUser.username);
            break;
        }
    }
    
    printf("Table %d booked successfully!\n", tableNo);
    saveData();
}

void bookRoom() {
    int roomNo;
    
    printf("\n=== BOOK ROOM ===\n");
    printf("Available Rooms:\n");
    for(int i = 0; i < roomCount; i++) {
        if(!rooms[i].isBooked) {
            printf("Room %d\n", rooms[i].roomNo);
        }
    }
    
    printf("Enter Room No to book: ");
    scanf("%d", &roomNo);
    
    if(!isRoomAvailable(roomNo)) {
        printf("Room %d is not available!\n", roomNo);
        return;
    }
    
    // Book the room
    for(int i = 0; i < roomCount; i++) {
        if(rooms[i].roomNo == roomNo) {
            rooms[i].isBooked = 1;
            strcpy(rooms[i].bookedBy, currentUser.username);
            break;
        }
    }
    
    printf("Room %d booked successfully!\n", roomNo);
    saveData();
}

int isRoomAvailable(int roomNo) {
    for(int i = 0; i < roomCount; i++) {
        if(rooms[i].roomNo == roomNo) {
            return !rooms[i].isBooked;
        }
    }
    return 0;
}

int isTableAvailable(int tableNo) {
    for(int i = 0; i < tableCount; i++) {
        if(tables[i].tableNo == tableNo) {
            return !tables[i].isBooked;
        }
    }
    return 0;
}

void generateBill(char username[]) {
    printf("\n=== YOUR BILL ===\n");
    float total = 0;
    int hasOrders = 0;
    
    printf("OrderID\tMeal\tQty\tPrice\tTable\tRoom\n");
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].username, username) == 0) {
            printf("%d\t%s\t%d\t%.2f\t%d\t%d\n",
                   orders[i].orderId, orders[i].mealName, orders[i].quantity,
                   orders[i].price, orders[i].tableNo, orders[i].roomNo);
            total += orders[i].price * orders[i].quantity;
            hasOrders = 1;
        }
    }
    
    if(!hasOrders) {
        printf("No orders found!\n");
        return;
    }
    
    printf("\nTotal Amount: %.2f\n", total);
    printf("Thank you for your business!\n");
}