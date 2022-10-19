#include <iostream>
#include "treeNode.h"

TreeNode::TreeNode(std::string cntt) : content{ cntt } {}

std::string TreeNode::getContent() const {
    return this->content;
}

TreeNode* TreeNode::getLeftChild() const {
    return this->leftChild;
}
TreeNode* TreeNode::getRightChild() const {
    return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode* lChild) {
    this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode* lChild, TreeNode* rChild) {
    this->leftChild = lChild;
    this->rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt) : TreeNode{ cntt } {}

bool OperatorNode::evaluate(const std::map<std::string, bool>& assignment) const {
    if (this->getContent() == "+") {
        return this->getLeftChild()->evaluate(assignment)
            || this->getRightChild()->evaluate(assignment);
    }
    else if (this->getContent() == "*") {
        return this->getLeftChild()->evaluate(assignment)
            && this->getRightChild()->evaluate(assignment);
    }
    else if (this->getContent() == "-") {
        return !this->getLeftChild()->evaluate(assignment);
    }
    return false; // or throw exception 
}

ConstantNode::ConstantNode(std::string cntt) : TreeNode{ cntt } {}

bool ConstantNode::evaluate(const std::map<std::string, bool>& assignment) const {
    if (this->getContent() == "1") {
        return true;
    }
    else if (this->getContent() == "0") {
        return false;
    }
    return false; // or throw exception 
}

VariableNode::VariableNode(std::string cntt) : TreeNode{ cntt } {}

bool VariableNode::evaluate(const std::map<std::string, bool>& assignment) const {
    if (!assignment.count(this->getContent())) {
        throw std::runtime_error("Error: incomplete assignment");
    }
     return assignment.at(this->getContent());
}


TreeNode::~TreeNode() {
    if (leftChild != nullptr)
        delete leftChild;
    if (rightChild != nullptr)
        delete rightChild;
}
