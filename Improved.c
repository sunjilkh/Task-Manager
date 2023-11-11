#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    int id;
    char name[50];
    char description[100];
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
    int priority;
};

struct User {
    char username[50];
    char password[50];
    char phone[15];
};

struct Task tasks[100];
struct User users[10];
int numTasks = 0;
int numUsers = 0;
int loggedInUserIndex = -1;

int validateTimeOverlap(struct Task newTask) {
    for (int i = 0; i < numTasks; i++) {
        if ((newTask.start_hour * 60 + newTask.start_minute < tasks[i].end_hour * 60 + tasks[i].end_minute &&
             newTask.end_hour * 60 + newTask.end_minute > tasks[i].start_hour * 60 + tasks[i].start_minute) ||
            (newTask.start_hour * 60 + newTask.start_minute >= tasks[i].start_hour * 60 + tasks[i].start_minute &&
             newTask.end_hour * 60 + newTask.end_minute <= tasks[i].end_hour * 60 + tasks[i].end_minute)) {
            return 1;
        }
    }
    return 0;
}

void addUser(char username[50], char password[50], char phone[15]) {
    if (numUsers < 10) {
        for (int i = 0; i < numUsers; i++) {
            if (strcmp(users[i].username, username) == 0) {
                printf("Username already exists. User not added.\n\n");
                return;
            }
        }

        strcpy(users[numUsers].username, username);
        strcpy(users[numUsers].password, password);
        strcpy(users[numUsers].phone, phone);
        numUsers++;
        printf("User added successfully!\n\n");
    } else {
        printf("User limit reached. Cannot add more users.\n\n");
    }
}

int validateUser(char username[50], char password[50]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void guestLogin() {
    loggedInUserIndex = -2;
    printf("Guest login successful!\n\n");
}

void addTask(char name[50], char description[100]) {
    int priority;
    if (numTasks < 100) {
        struct Task task;
        task.id = numTasks + 1;
        strcpy(task.name, name);
        strcpy(task.description, description);

        printf("Enter start time (hour:minute): ");
        scanf("%d:%d", &task.start_hour, &task.start_minute);

        printf("Enter end time (hour:minute): ");
        scanf("%d:%d", &task.end_hour, &task.end_minute);

        if (task.start_hour < 0 || task.start_hour > 23 || task.start_minute < 0 || task.start_minute > 59 ||
            task.end_hour < 0 || task.end_hour > 23 || task.end_minute < 0 || task.end_minute > 59) {
            printf("Invalid time. Task not added.\n");
            return;
        }

        if (validateTimeOverlap(task)) {
                        system("cls");
            printf("Time overlap detected. Task not added.\n");
            return;
        }

        printf("Enter task priority (1: Low, 2: Medium, 3: High): ");
        scanf("%d", &priority);

        if (priority < 1 || priority > 3) {
                    system("cls");
                printf("Invalid priority. Task not added.\n");
            return;
        }

        task.priority = priority;
        tasks[numTasks] = task;
        numTasks++;

        printf("Task added successfully!\n");
    } else {
                    system("cls");
        printf("Task manager is full. Cannot add more tasks.\n");
    }
}

void listTasks() {
    if (numTasks == 0) {
        printf("No tasks found.\n");
        return;
    }

    for (int i = 0; i < numTasks - 1; i++) {
        for (int j = i + 1; j < numTasks; j++) {
            if (tasks[i].priority < tasks[j].priority) {
                struct Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
    system("cls");
    printf("Task List:\n");
    for (int i = 0; i < numTasks; i++) {
        printf("ID: %d\n", tasks[i].id);
        printf("Name: %s\n", tasks[i].name);
        printf("Description: %s\n", tasks[i].description);
        printf("Start Time: %02d:%02d\n", tasks[i].start_hour, tasks[i].start_minute);
        printf("End Time: %02d:%02d\n", tasks[i].end_hour, tasks[i].end_minute);
        printf("Priority: %d\n", tasks[i].priority);
        printf("\n");
    }
}

void searchTasksByName(char searchName[50]) {
    int found = 0;
    printf("Tasks with the name '%s':\n", searchName);
    for (int i = 0; i < numTasks; i++) {
        if (strcmp(tasks[i].name, searchName) == 0) {
            printf("ID: %d\n", tasks[i].id);
            printf("Name: %s\n", tasks[i].name);
            printf("Description: %s\n", tasks[i].description);
            printf("Start Time: %02d:%02d\n", tasks[i].start_hour, tasks[i].start_minute);
            printf("End Time: %02d:%02d\n", tasks[i].end_hour, tasks[i].end_minute);
            printf("Priority: %d\n", tasks[i].priority);
            printf("\n");
            found = 1;
        }
    }
    if (found == 0) {
        printf("No tasks with the name '%s' found.\n", searchName);
    }
}

void deleteTaskByName(char deleteName[50]) {
    int found = 0;
    for (int i = 0; i < numTasks; i++) {
        if (strcmp(tasks[i].name, deleteName) == 0) {
            found = 1;
            for (int j = i; j < numTasks - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            numTasks--;
            printf("Task '%s' deleted successfully!\n", deleteName);
            break;
        }
    }
    if (found == 0) {
        printf("No tasks with the name '%s' found.\n", deleteName);
    }
}

void displayLastActivity() {
    if (numTasks == 0) {
        printf("No tasks found. No last activity to display.\n");
        return;
    }

    struct Task lastTask = tasks[numTasks - 1];
    printf("Last Activity:\n");
    printf("Name: %s\n", lastTask.name);
    printf("Description: %s\n", lastTask.description);
    printf("Start Time: %02d:%02d\n", lastTask.start_hour, lastTask.start_minute);
    printf("End Time: %02d:%02d\n", lastTask.end_hour, lastTask.end_minute);
    printf("Priority: %d\n", lastTask.priority);
}

int main() {
    int choice;
    char taskName[50];
    char taskDescription[100];
    char username[50];
    char password[50];
    char phone[15];
    char searchName[50];
    char deleteName[50];

    while (1) {
        if (loggedInUserIndex == -1) {
            printf("User Management Menu:\n");
            printf("1. Add User\n");
            printf("2. User Login\n");
            printf("3. Guest Login\n");
        } else {
            printf("\nTask Manager Menu (Logged in as %s):\n", loggedInUserIndex == -2 ? "Guest" : users[loggedInUserIndex].username);
            printf("4. Add Task\n");
            printf("5. List Tasks\n");
            printf("6. Search Tasks by Name\n");
            printf("7. Delete Task by Name\n");
            printf("8. Display Last Activity\n");
            printf("9. Logout\n");
        }
        printf("10. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a new username: ");
                scanf("%s", username);
                printf("Enter a new password: ");
                scanf("%s", password);
                printf("Enter the phone number: ");
                scanf("%s", phone);
                system("cls");
                addUser(username, password, phone);
                break;
            case 2:
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", password);
                system("cls");
                loggedInUserIndex = validateUser(username, password);
                if (loggedInUserIndex != -1) {
                    printf("Login successful!\n");
                } else {
                    printf("Invalid username or password.\n");
                }
                break;
            case 3:
                system("cls");
                guestLogin();
                break;
            case 4:
                if (loggedInUserIndex != -1) {
                    printf("Enter task name: ");
                    scanf("%s", taskName);
                    printf("Enter task description: ");
                    getchar();
                    fgets(taskDescription, sizeof(taskDescription), stdin);
                    taskDescription[strlen(taskDescription) - 1] = '\0';
                    addTask(taskName, taskDescription);
                } else {
                    printf("You need to log in to add a task.\n\n");
                }
                break;
            case 5:
                system("cls");
                if (loggedInUserIndex != -1) {
                    listTasks();
                } else {
                    printf("You need to log in to list tasks.\n\n");
                }
                break;
            case 6:
                if (loggedInUserIndex != -1) {
                    printf("Enter the name to search for: ");
                    scanf("%s", searchName);
                    system("cls");
                    searchTasksByName(searchName);
                } else {
                    system("cls");
                    printf("You need to log in to search for tasks.\n\n");
                }
                break;
            case 7:
                if (loggedInUserIndex != -1) {
                    printf("Enter the name of the task to delete: ");
                    scanf("%s", deleteName);
                    system("cls");
                    deleteTaskByName(deleteName);
                } else {
                    system("cls");
                    printf("You need to log in to search for tasks.\n\n");
                }
                break;
            case 8:
                system("cls");
                if (loggedInUserIndex != -1) {
                    displayLastActivity();
                } else {
                    printf("You need to log in to display the last activity.\n");
                }
                break;
            case 9:
                system("cls");
                loggedInUserIndex = -1;
                printf("Logged out successfully!\n");
                break;
            case 10:
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n\n");
                printf("                                        Thanks For Using our product!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                exit(0);
            default:
                system("cls");
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
