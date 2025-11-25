#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>

class AVLNode {
private:
    int student_ID;
    std::string name;
    std::string course;
    float grade;
    float GPA;
    int height;
    AVLNode* left;
    AVLNode* right;

public:
    AVLNode(int student_ID, std::string name, std::string course, float grade, float GPA);
    
    int getStudentID();
    std::string getName();
    std::string getCourse();
    float getGrade();
    float getGPA();
    int getHeight();
    
    void setStudentID(int id);
    void setName(std::string n);
    void setCourse(std::string c);
    void setGrade(float g);
    void setGPA(float gp);
    void setHeight(int h);
    
    AVLNode* getLeft();
    void setLeft(AVLNode* l);
    AVLNode* getRight();
    void setRight(AVLNode* r);
};

#endif
