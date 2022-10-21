#ifndef TNODE_H
#define TNODE_H

#include <sstream>
#include <iostream>
#include <string>
#include <map>

class TreeNode {
    std::string content;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;
protected:
    TreeNode* getLeftChild() const;
    TreeNode* getRightChild() const;
public:
    TreeNode(std::string cntt);
    std::string getContent() const;
    virtual bool evaluate(const std::map<std::string, bool>& assignment) const = 0;
    void updateLeftChild(TreeNode* lChild); 
    void updateChildren(TreeNode* lChild, TreeNode* rChild);
    virtual ~TreeNode();

};

class OperatorNode : public TreeNode {
public:
    OperatorNode(std::string cntt);
    bool evaluate(const std::map<std::string, bool>& assignment) const override;
};

class ConstantNode : public TreeNode {
public:
    ConstantNode(std::string cntt);
    bool evaluate(const std::map<std::string, bool>& assignment) const override;
};

class VariableNode : public TreeNode {
public:
    VariableNode(std::string cntt);
    bool evaluate(const std::map<std::string, bool>& assignment) const override;
};

#endif

