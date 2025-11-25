#include "AVLTree.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>


AVLTree::AVLTree() { root = nullptr; }

int AVLTree::getHeight(AVLNode *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->getHeight();
}

int AVLTree::getBalance(AVLNode *node) {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->getLeft()) - getHeight(node->getRight());
}

AVLNode *AVLTree::rotateRight(AVLNode *y) {
  AVLNode *x = y->getLeft();
  AVLNode *T2 = x->getRight();

  x->setRight(y);
  y->setLeft(T2);

  y->setHeight(1 + std::max(getHeight(y->getLeft()), getHeight(y->getRight())));
  x->setHeight(1 + std::max(getHeight(x->getLeft()), getHeight(x->getRight())));

  return x;
}

AVLNode *AVLTree::rotateLeft(AVLNode *x) {
  AVLNode *y = x->getRight();
  AVLNode *T2 = y->getLeft();

  y->setLeft(x);
  x->setRight(T2);

  x->setHeight(1 + std::max(getHeight(x->getLeft()), getHeight(x->getRight())));
  y->setHeight(1 + std::max(getHeight(y->getLeft()), getHeight(y->getRight())));

  return y;
}

AVLNode *AVLTree::FindMinNode(AVLNode *node) {
  AVLNode *current = node;
  while (current->getLeft() != nullptr) {
    current = current->getLeft();
  }
  return current;
}

void AVLTree::inorderTraversal(AVLNode *node) {
  if (node != nullptr) {
    inorderTraversal(node->getLeft());
    std::cout << "ID: " << node->getStudentID() << " Name: " << node->getName()
              << " Course: " << node->getCourse()
              << " Grade: " << node->getGrade() << " GPA: " << node->getGPA()
              << std::endl;
    inorderTraversal(node->getRight());
  }
}

int AVLTree::compareKeys(int id1, std::string course1, int id2,
                         std::string course2) {
  if (id1 < id2)
    return -1;
  if (id1 > id2)
    return 1;
  if (course1 < course2)
    return -1;
  if (course1 > course2)
    return 1;
  return 0;
}

AVLNode *AVLTree::insertHelper(AVLNode *node, int student_ID, std::string name,
                               std::string course, float grade, float GPA) {
  if (node == nullptr) {
    return new AVLNode(student_ID, name, course, grade, GPA);
  }

  int cmp =
      compareKeys(student_ID, course, node->getStudentID(), node->getCourse());

  if (cmp < 0) {
    node->setLeft(
        insertHelper(node->getLeft(), student_ID, name, course, grade, GPA));
  } else if (cmp > 0) {
    node->setRight(
        insertHelper(node->getRight(), student_ID, name, course, grade, GPA));
  } else {
    return node;
  }

  node->setHeight(
      1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));
  int balance = getBalance(node);

  if (balance > 1) {
    int cmpLeft =
        compareKeys(student_ID, course, node->getLeft()->getStudentID(),
                    node->getLeft()->getCourse());
    if (cmpLeft < 0) {
      return rotateRight(node);
    } else {
      node->setLeft(rotateLeft(node->getLeft()));
      return rotateRight(node);
    }
  }

  if (balance < -1) {
    int cmpRight =
        compareKeys(student_ID, course, node->getRight()->getStudentID(),
                    node->getRight()->getCourse());
    if (cmpRight > 0) {
      return rotateLeft(node);
    } else {
      node->setRight(rotateRight(node->getRight()));
      return rotateLeft(node);
    }
  }

  return node;
}

AVLNode *AVLTree::findStudentByID(AVLNode *node, int student_ID) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->getStudentID() == student_ID) {
    return node;
  }
  AVLNode *leftResult = findStudentByID(node->getLeft(), student_ID);
  if (leftResult != nullptr) {
    return leftResult;
  }
  return findStudentByID(node->getRight(), student_ID);
}

float AVLTree::gradeToGPA(float grade) {
  if (grade >= 90)
    return 4.0;
  if (grade >= 80)
    return 3.0;
  if (grade >= 70)
    return 2.0;
  if (grade >= 60)
    return 1.0;
  return 0.0;
}

void AVLTree::collectGrades(AVLNode *node, int student_ID, float &total,
                            int &count) {
  if (node == nullptr) {
    return;
  }
  collectGrades(node->getLeft(), student_ID, total, count);
  if (node->getStudentID() == student_ID) {
    total += gradeToGPA(node->getGrade());
    count++;
  }
  collectGrades(node->getRight(), student_ID, total, count);
}

float AVLTree::calculateGPA(int student_ID) {
  float total = 0;
  int count = 0;
  collectGrades(root, student_ID, total, count);
  if (count == 0) {
    return 0.0;
  }
  return total / count;
}

bool AVLTree::insert(int student_ID, std::string name, std::string course,
                     float grade) {
  AVLNode *existing = findStudentByID(root, student_ID);
  if (existing != nullptr && existing->getName() != name) {
    return false;
  }
  float tempGPA = 0.0;
  root = insertHelper(root, student_ID, name, course, grade, tempGPA);
  float newGPA = calculateGPA(student_ID);
  updateAllGPAs(root, student_ID, newGPA);
  return true;
}

void AVLTree::updateAllGPAs(AVLNode *node, int student_ID, float GPA) {
  if (node == nullptr) {
    return;
  }
  updateAllGPAs(node->getLeft(), student_ID, GPA);
  if (node->getStudentID() == student_ID) {
    node->setGPA(GPA);
  }
  updateAllGPAs(node->getRight(), student_ID, GPA);
}

AVLNode *AVLTree::searchHelper(AVLNode *node, int student_ID,
                               std::string course) {
  if (node == nullptr) {
    return nullptr;
  }

  int cmp =
      compareKeys(student_ID, course, node->getStudentID(), node->getCourse());

  if (cmp == 0) {
    return node;
  }

  if (cmp < 0) {
    return searchHelper(node->getLeft(), student_ID, course);
  } else {
    return searchHelper(node->getRight(), student_ID, course);
  }
}

AVLNode *AVLTree::search(int student_ID, std::string course) {
  return searchHelper(root, student_ID, course);
}

bool AVLTree::update(int student_ID, std::string course, float grade) {
  AVLNode *nodeToUpdate = search(student_ID, course);
  if (nodeToUpdate != nullptr) {
    nodeToUpdate->setGrade(grade);
    float newGPA = calculateGPA(student_ID);
    updateAllGPAs(root, student_ID, newGPA);
    return true;
  } else {
    return false;
  }
}

AVLNode *AVLTree::deleteHelper(AVLNode *node, int student_ID,
                               std::string course) {
  if (node == nullptr) {
    return node;
  }

  int cmp =
      compareKeys(student_ID, course, node->getStudentID(), node->getCourse());

  if (cmp < 0) {
    node->setLeft(deleteHelper(node->getLeft(), student_ID, course));
  } else if (cmp > 0) {
    node->setRight(deleteHelper(node->getRight(), student_ID, course));
  } else {
    if (node->getLeft() == nullptr) {
      AVLNode *temp = node->getRight();
      delete node;
      return temp;
    }
    if (node->getRight() == nullptr) {
      AVLNode *temp = node->getLeft();
      delete node;
      return temp;
    }

    AVLNode *temp = FindMinNode(node->getRight());

    node->setStudentID(temp->getStudentID());
    node->setName(temp->getName());
    node->setCourse(temp->getCourse());
    node->setGrade(temp->getGrade());
    node->setGPA(temp->getGPA());

    node->setRight(deleteHelper(node->getRight(), temp->getStudentID(),
                                temp->getCourse()));
  }

  if (node == nullptr) {
    return node;
  }

  node->setHeight(
      1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));
  int balance = getBalance(node);

  if (balance > 1 && getBalance(node->getLeft()) >= 0) {
    return rotateRight(node);
  }

  if (balance > 1 && getBalance(node->getLeft()) < 0) {
    node->setLeft(rotateLeft(node->getLeft()));
    return rotateRight(node);
  }

  if (balance < -1 && getBalance(node->getRight()) <= 0) {
    return rotateLeft(node);
  }

  if (balance < -1 && getBalance(node->getRight()) > 0) {
    node->setRight(rotateRight(node->getRight()));
    return rotateLeft(node);
  }

  return node;
}

void AVLTree::deleteNode(int student_ID, std::string course) {
  root = deleteHelper(root, student_ID, course);
  float newGPA = calculateGPA(student_ID);
  updateAllGPAs(root, student_ID, newGPA);
}

void AVLTree::deleteAllCourses(int student_ID) {
  std::vector<AVLNode *> courses = getAllCourses(student_ID);
  for (size_t i = 0; i < courses.size(); i++) {
    root = deleteHelper(root, student_ID, courses[i]->getCourse());
  }
}

void AVLTree::collectAllNodes(AVLNode *node, std::vector<AVLNode *> &nodes) {
  if (node != nullptr) {
    collectAllNodes(node->getLeft(), nodes);
    nodes.push_back(node);
    collectAllNodes(node->getRight(), nodes);
  }
}

std::vector<AVLNode *> AVLTree::getAllCourses(int student_ID) {
  std::vector<AVLNode *> result;
  std::vector<AVLNode *> allNodes;
  collectAllNodes(root, allNodes);
  for (size_t i = 0; i < allNodes.size(); i++) {
    if (allNodes[i]->getStudentID() == student_ID) {
      result.push_back(allNodes[i]);
    }
  }
  return result;
}

void AVLTree::displayStudent(int student_ID) {
  std::vector<AVLNode *> courses = getAllCourses(student_ID);
  if (courses.empty()) {
    std::cout << "\nStudent not found.\n\n";
    return;
  }

  std::cout << "\n" << std::string(80, '=') << "\n";
  std::cout << std::left << std::setw(8) << "ID" << std::setw(20) << "Name"
            << std::setw(15) << "Course" << std::setw(10) << "Grade"
            << std::setw(8) << "GPA" << "\n";
  std::cout << std::string(80, '-') << "\n";

  for (size_t i = 0; i < courses.size(); i++) {
    AVLNode *node = courses[i];
    if (i == 0) {
      std::cout << std::left << std::setw(8) << node->getStudentID()
                << std::setw(20) << node->getName() << std::setw(15)
                << node->getCourse() << std::setw(10) << std::fixed
                << std::setprecision(1) << node->getGrade() << std::setw(8)
                << std::fixed << std::setprecision(2) << node->getGPA() << "\n";
    } else {
      std::cout << std::left << std::setw(8) << "" << std::setw(20) << ""
                << std::setw(15) << node->getCourse() << std::setw(10)
                << std::fixed << std::setprecision(1) << node->getGrade()
                << std::setw(8) << "" << "\n";
    }
  }

  std::cout << std::string(80, '=') << "\n\n";
}

void AVLTree::display() {
  if (root == nullptr) {
    std::cout << "\nNo students found.\n\n";
    std::cout.flush();
    return;
  }

  std::vector<AVLNode *> nodes;
  collectAllNodes(root, nodes);

  std::cout << "\n" << std::string(80, '=') << "\n";
  std::cout << std::left << std::setw(8) << "ID" << std::setw(20) << "Name"
            << std::setw(15) << "Course" << std::setw(10) << "Grade"
            << std::setw(8) << "GPA" << "\n";
  std::cout << std::string(80, '-') << "\n";

  int currentID = -1;
  for (size_t i = 0; i < nodes.size(); i++) {
    AVLNode *node = nodes[i];

    if (node->getStudentID() != currentID) {
      if (currentID != -1) {
        std::cout << std::string(80, '-') << "\n";
      }
      currentID = node->getStudentID();
      std::cout << std::left << std::setw(8) << node->getStudentID()
                << std::setw(20) << node->getName() << std::setw(15)
                << node->getCourse() << std::setw(10) << std::fixed
                << std::setprecision(1) << node->getGrade() << std::setw(8)
                << std::fixed << std::setprecision(2) << node->getGPA() << "\n";
    } else {
      std::cout << std::left << std::setw(8) << "" << std::setw(20) << ""
                << std::setw(15) << node->getCourse() << std::setw(10)
                << std::fixed << std::setprecision(1) << node->getGrade()
                << std::setw(8) << "" << "\n";
    }
  }

  std::cout << std::string(80, '=') << "\n\n";
}

void AVLTree::saveToFileHelper(AVLNode *node, std::ofstream &file) {
  if (node == nullptr) {
    return;
  }
  saveToFileHelper(node->getLeft(), file);
  file << node->getStudentID() << "," << node->getName() << ","
       << node->getCourse() << "," << node->getGrade() << "," << node->getGPA()
       << std::endl;
  saveToFileHelper(node->getRight(), file);
}

void AVLTree::saveToFile(std::string filename) {
  std::ofstream file(filename);
  if (file.is_open()) {
    saveToFileHelper(root, file);
    file.close();
  }
}

void AVLTree::loadFromFile(std::string filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      if (line.empty()) {
        continue;
      }
      std::stringstream ss(line);
      std::string token;
      std::string tokens[5];
      int i = 0;
      while (std::getline(ss, token, ',')) {
        tokens[i] = token;
        i++;
      }
      if (i == 5) {
        int student_ID = std::stoi(tokens[0]);
        std::string name = tokens[1];
        std::string course = tokens[2];
        float grade = std::stof(tokens[3]);
        insert(student_ID, name, course, grade);
      }
    }
    file.close();
  }
}

std::string AVLTree::getStudentName(int student_ID) {
  AVLNode *node = findStudentByID(root, student_ID);
  if (node != nullptr) {
    return node->getName();
  }
  return "";
}
