This is the code for the project #include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Task {
public:
    std::string title;
    std::string description;
};

class TaskManager {
private:
    std::vector<Task> tasks;

public:
    void addTask() {
        Task task;
        std::cout << "Enter task title: ";
        std::getline(std::cin, task.title);
        std::cout << "Enter task description: ";
        std::getline(std::cin, task.description);
        tasks.push_back(task);
        std::cout << "Task added successfully!\n";
    }

    void listTasks() {
        for (const auto& task : tasks) {
            std::cout << "Title: " << task.title << "\nDescription: " << task.description << "\n\n";
        }
    }

    void deleteTask() {
        std::string title;
        std::cout << "Enter the title of the task to delete: ";
        std::getline(std::cin, title);

        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                                   [&](const Task& task) { return task.title == title; }),
                    tasks.end());

        std::cout << "Task deleted successfully!\n";
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& task : tasks) {
            file << task.title << "," << task.description << "\n";
        }
        file.close();
        std::cout << "Tasks saved to file successfully!\n";
    }

    void loadFromFile(const std::string& filename) {
        tasks.clear();
        std::ifstream file(filename);
        Task task;
        while (getline(file, task.title, ',') && getline(file, task.description, '\n')) {
            tasks.push_back(task);
        }
        file.close();
        std::cout << "Tasks loaded from file successfully!\n";
    }
};

int main() {
    TaskManager taskManager;

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. List Tasks\n";
        std::cout << "3. Delete Task\n";
        std::cout << "4. Save Tasks to File\n";
        std::cout << "5. Load Tasks from File\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Clear newline character from the input buffer

        switch (choice) {
            case 1:
                taskManager.addTask();
                break;
            case 2:
                taskManager.listTasks();
                break;
            case 3:
                taskManager.deleteTask();
                break;
            case 4:
                taskManager.saveToFile("tasks.txt");
                break;
            case 5:
                taskManager.loadFromFile("tasks.txt");
                break;
            case 0:
                std::cout << "Exiting program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
