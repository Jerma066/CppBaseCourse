#pragma once

#include <memory>
#include <queue>  // Only for bfs travers
#include <vector> // Only for bfs travers

namespace tree {

template <typename VType> class AVL final {
private:
  struct Node final {
    Node(int val, std::weak_ptr<Node> prnt) : value(val), parent(prnt) {}

    int balanceFactor() {
      int lh = left ? left->height : -1;
      int rh = right ? right->height : -1;
      return rh - lh;
    }

    VType value;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    int height = 0;
  };

public:
  void insert(VType newVal) {
    auto newNode = std::make_shared<Node>(newVal, std::weak_ptr<Node>());
    insertNode(newNode);
  }

private:
  void insertNode(std::shared_ptr<Node> newNode) {
    // TODO: Maybe the following step shoub be wraped in function
    //       Or All steps should be moved as separetes function
    //       to insert function above
    // STEP 1: Inserting as in BST
    // Searching for the insert position
    std::shared_ptr<Node> curNode = root_;
    std::shared_ptr<Node> newParentNode = nullptr;
    while (curNode) {
      newParentNode = curNode;
      curNode =
          (newNode->value < curNode->value) ? curNode->left : curNode->right;
    }

    // Checking if such value already in tree
    if (newParentNode && (newParentNode->value == newNode->value))
      return;

    // Inserting node to the position
    newNode->parent = newParentNode;
    if (!newParentNode) {
      // Empty tree case
      root_ = newNode;
      return;
    } else if (newNode->value < newParentNode->value) {
      newParentNode->left = newNode;
    } else {
      newParentNode->right = newNode;
    }

    // STEP 2: Height calculating
    upStreamHeightRecalc(newNode);

    // STEP 3: Tree balancing
    rebalanceTree(newNode->parent.lock());
  }

  void upStreamHeightRecalc(std::shared_ptr<Node> startNode) {
    auto curNode = startNode;
    while (curNode && curNode->parent.lock()) {
      if (curNode->parent.lock()->height == curNode->height) {
        curNode->parent.lock()->height++;
      } else {
        break;
      }

      curNode = curNode->parent.lock();
    }
  }

  // TODO: Get rid of recursion
  void rebalanceTree(std::shared_ptr<Node> rotatedNode) {
    if (!rotatedNode)
      return;

    std::shared_ptr<Node> oldParent = rotatedNode->parent.lock();
    int bFactor = rotatedNode->balanceFactor();
    // TODO: Need comment
    // TODO: Use bool variables for complex if clauses
    if (bFactor > 1) {
      if (rotatedNode->right && rotatedNode->right->left &&
          (rotatedNode->right->left->left || rotatedNode->right->left->right)) {
        rightRotate(rotatedNode->right);
      }
      leftRotate(rotatedNode);
    } else if (bFactor < -1) {
      if (rotatedNode->left && rotatedNode->left->right &&
          (rotatedNode->left->right->left || rotatedNode->left->right->right)) {
        // TODO: Check the argument of leftRotate function
        leftRotate(rotatedNode->left);
      }
      rightRotate(rotatedNode);
    }

    // TODO: Use cycle instead of recursion
    rebalanceTree(oldParent);
  }

  /*
    bls - b left subtree
    als - a left subtree

      a                 b
     / \               / \
   als  b      =>    a     c
       / \          / \   / \
     bls  c       als bls
         / \
  */
  // Central Node is a; Right Child is b
  void leftRotate(std::shared_ptr<Node> centralNode) {
    if (!centralNode || !root_)
      return;

    std::shared_ptr<Node> rightChild = centralNode->right;
    std::shared_ptr<Node> parent = centralNode->parent.lock();

    // Nothing to rotate left
    if (!rightChild)
      return;

    // TODO: need comments
    if (centralNode == root_)
      root_ = rightChild;
    centralNode->parent = rightChild;
    centralNode->right = rightChild->left;

    if (rightChild->left)
      rightChild->left->parent = centralNode;
    rightChild->left = centralNode;
    rightChild->parent = parent;

    if (parent) {
      if (parent->left == centralNode)
        parent->left = rightChild;
      else
        parent->right = rightChild;
    }
  }

  void rightRotate(std::shared_ptr<Node> centralNode) {
    if (!centralNode || !root_)
      return;

    std::shared_ptr<Node> leftChild = centralNode->left;
    std::shared_ptr<Node> parent = centralNode->parent.lock();

    if (!leftChild)
      return;

    if (centralNode == root_)
      root_ = leftChild;
    centralNode->parent = leftChild;
    centralNode->left = leftChild->right;

    if (leftChild->right)
      leftChild->right->parent = centralNode;
    leftChild->right = centralNode;
    leftChild->parent = parent;

    if (parent) {
      if (parent->left == centralNode)
        parent->left = leftChild;
      else
        parent->right = leftChild;
    }
  }

public:
  std::vector<VType> getBfsTravers() {
    std::vector<VType> output;

    std::queue<std::shared_ptr<Node>> que;
    que.push(root_);

    while (!que.empty()) {
      auto curNode = que.front();
      que.pop();

      output.push_back(curNode->value);

      if (curNode->left)
        que.push(curNode->left);
      if (curNode->right)
        que.push(curNode->right);
    }

    return output;
  }

private:
  std::shared_ptr<Node> root_;
};

} // namespace tree
