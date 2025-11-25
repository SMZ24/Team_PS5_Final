#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <fstream>
#include <string>
#include <vector>


class AVLTree {
private:
  AVLNode *root;

protected:
  int getHeight(AVLNode *node);
  int getBalance(AVLNode *node);
  AVLNode *rotateLeft(AVLNode *x);
  AVLNode *rotateRight(AVLNode *y);
  AVLNode *FindMinNode(AVLNode *node);
  void inorderTraversal(AVLNode *node);
  int compareKeys(int id1, std::string course1, int id2, std::string course2);
  AVLNode *insertHelper(AVLNode *node, int student_ID, std::string name,
                        std::string course, float grade, float GPA);
  AVLNode *searchHelper(AVLNode *node, int student_ID, std::string course);
  AVLNode *deleteHelper(AVLNode *node, int student_ID, std::string course);
  void saveToFileHelper(AVLNode *node, std::ofstream &file);
  AVLNode *findStudentByID(AVLNode *node, int student_ID);
  float gradeToGPA(float grade);
  float calculateGPA(int student_ID);
  void collectGrades(AVLNode *node, int student_ID, float &total, int &count);
  void updateAllGPAs(AVLNode *node, int student_ID, float GPA);
  void collectAllNodes(AVLNode *node, std::vector<AVLNode *> &nodes);

public:
  AVLTree();
  bool insert(int student_ID, std::string name, std::string course,
              float grade);
  AVLNode *search(int student_ID, std::string course);
  bool update(int student_ID, std::string course, float grade);
  void deleteNode(int student_ID, std::string course);
  void deleteAllCourses(int student_ID);
  void display();
  void displayStudent(int student_ID);
  void saveToFile(std::string filename);
  void loadFromFile(std::string filename);
  std::string getStudentName(int student_ID);
  std::vector<AVLNode *> getAllCourses(int student_ID);
};

#endif
