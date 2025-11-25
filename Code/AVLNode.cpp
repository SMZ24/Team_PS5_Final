#include "AVLNode.h"

AVLNode::AVLNode(int student_ID, std::string name, std::string course, float grade, float GPA) {
    this->student_ID = student_ID;
    this->name = name;
    this->course = course;
    this->grade = grade;
    this->GPA = GPA;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}

int AVLNode::getStudentID() {
    return student_ID;
}

std::string AVLNode::getName() {
    return name;
}

std::string AVLNode::getCourse() {
    return course;
}

float AVLNode::getGrade() {
    return grade;
}

float AVLNode::getGPA() {
    return GPA;
}

int AVLNode::getHeight() {
    return height;
}

void AVLNode::setStudentID(int id) {
    student_ID = id;
}

void AVLNode::setName(std::string n) {
    name = n;
}

void AVLNode::setCourse(std::string c) {
    course = c;
}

void AVLNode::setGrade(float g) {
    grade = g;
}

void AVLNode::setGPA(float gp) {
    GPA = gp;
}

void AVLNode::setHeight(int h) {
    height = h;
}

AVLNode* AVLNode::getLeft() {
    return left;
}

void AVLNode::setLeft(AVLNode* l) {
    left = l;
}

AVLNode* AVLNode::getRight() {
    return right;
}

void AVLNode::setRight(AVLNode* r) {
    right = r;
}


