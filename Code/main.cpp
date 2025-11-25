#include "AVLTree.h"
#include <cctype>
#include <climits>
#include <iostream>
#include <string>

bool isValidName(const std::string &str) {
  if (str.empty())
    return false;
  for (char c : str) {
    if (!std::isalpha(c) && c != ' ' && c != '-') {
      return false;
    }
  }
  return true;
}

bool isValidCourse(const std::string &str) {
  if (str.empty())
    return false;
  for (char c : str) {
    if (!std::isalnum(c) && c != ' ' && c != '-' && c != '.') {
      return false;
    }
  }
  return true;
}

int getIntInput(const std::string &prompt, int min = INT_MIN,
                int max = INT_MAX) {
  int value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      if (value >= min && value <= max) {
        std::cin.ignore();
        return value;
      } else {
        std::cout << "Error: Value must be between " << min << " and " << max
                  << ". Please try again.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
      }
    } else {
      std::cout << "Error: Invalid input. Please enter a number.\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
}

float getFloatInput(const std::string &prompt, float min = 0.0f,
                    float max = 100.0f) {
  float value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      if (value >= min && value <= max) {
        std::cin.ignore();
        return value;
      } else {
        std::cout << "Error: Grade must be between " << min << " and " << max
                  << ". Please try again.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
      }
    } else {
      std::cout << "Error: Invalid input. Please enter a number.\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
}

std::string getStringInput(const std::string &prompt, bool isName = false) {
  std::string value;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, value);
    if (value.empty()) {
      std::cout << "Error: Input cannot be empty. Please try again.\n";
      continue;
    }
    if (isName && !isValidName(value)) {
      std::cout << "Error: Name can only contain letters, spaces, and hyphens. "
                   "Please try again.\n";
      continue;
    }
    if (!isName && !isValidCourse(value)) {
      std::cout << "Error: Course name can only contain letters, numbers, "
                   "spaces, and hyphens. Please try again.\n";
      continue;
    }
    return value;
  }
}

int main() {
  AVLTree tree;
  int choice;
  int student_ID;
  std::string name;
  std::string course;
  float grade;
  std::string filename;

  std::cin.ignore();

  while (true) {
    std::cout << "\nStudent Grade Monitoring System\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. Update Student Grade\n";
    std::cout << "3. Search Student\n";
    std::cout << "4. Delete Student\n";
    std::cout << "5. Display All Students\n";
    std::cout << "6. Save to File\n";
    std::cout << "7. Load from File\n";
    std::cout << "8. Exit\n";
    choice = getIntInput("Enter your choice: ", 1, 8);

    if (choice == 1) {
      student_ID = getIntInput("Enter Student ID: ", 1);

      std::string existingName = tree.getStudentName(student_ID);
      if (existingName.empty()) {
        name = getStringInput("Enter Name: ", true);
      } else {
        name = existingName;
        std::cout << "Student found: " << name << std::endl;
      }

      course = getStringInput("Enter Course: ", false);
      grade = getFloatInput("Enter Grade: ", 0.0f, 100.0f);

      if (tree.insert(student_ID, name, course, grade)) {
        std::cout << "Course added successfully.\n";
      } else {
        std::cout
            << "Error: Student ID already exists with a different name.\n";
      }
    } else if (choice == 2) {
      student_ID = getIntInput("Enter Student ID: ", 1);
      course = getStringInput("Enter Course: ", false);
      grade = getFloatInput("Enter new Grade: ", 0.0f, 100.0f);
      if (tree.update(student_ID, course, grade)) {
        std::cout << "Student updated successfully.\n";
      } else {
        std::cout << "Student not found.\n";
      }
    } else if (choice == 3) {
      student_ID = getIntInput("Enter Student ID: ", 1);
      tree.displayStudent(student_ID);
    } else if (choice == 4) {
      student_ID = getIntInput("Enter Student ID: ", 1);
      std::cout << "1. Delete entire student record\n";
      std::cout << "2. Delete one course\n";
      int deleteChoice = getIntInput("Enter choice: ", 1, 2);

      if (deleteChoice == 1) {
        tree.deleteAllCourses(student_ID);
        std::cout << "Student record deleted successfully.\n";
      } else {
        course = getStringInput("Enter Course: ", false);
        tree.deleteNode(student_ID, course);
        std::cout << "Course deleted successfully.\n";
      }
    } else if (choice == 5) {
      std::cout << "\nAll Students:\n";
      tree.display();
    } else if (choice == 6) {
      filename = getStringInput("Enter filename (with extension, e.g., data.csv): ", false);
      tree.saveToFile(filename);
      std::cout << "Data saved to file.\n";
    } else if (choice == 7) {
      filename = getStringInput("Enter filename (with extension, e.g., data.csv): ", false);
      tree.loadFromFile(filename);
      std::cout << "Data loaded from file.\n";
    } else if (choice == 8) {
      std::cout << "Exiting program. Goodbye!\n"; 
      break;
    }
  }

  return 0;
}
