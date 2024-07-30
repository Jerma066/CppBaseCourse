#pragma once

#include <memory>
#include <queue>  // Only for bfs travers
#include <vector> // Only for bfs travers

namespace tree {

template <typename VType> class AVL final {
private:
  struct Node final {
    Node(int value, std::weak_ptr<Node> parent)
        : value(value), parent(parent) {}

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
    // STEP 1: Inserting as in BST
    bool needRebalancing = insertNode(newNode);

    if (needRebalancing) {
      // STEP 2: Height calculating
      upStreamHeightRecalc(newNode);

      // STEP 3: Tree balancing
      rebalanceTree(newNode->parent.lock());
    }
  }

private:
  bool insertNode(std::shared_ptr<Node> newNode) {
    // Searching for the insert position
    std::shared_ptr<Node> curNode = root_;
    std::shared_ptr<Node> newParentNode = nullptr;
    while (curNode) {
      newParentNode = curNode;
      curNode =
          (newNode->value < curNode->value) ? curNode->left : curNode->right;
    }

    // Checking if Node can be inserted (such value already in tree)
    if (newParentNode && (newParentNode->value == newNode->value)) {
      // No insertion - no rebalancing required
      return false;
    }

    // Inserting node to the position
    newNode->parent = newParentNode;
    if (!newParentNode) {
      // Empty tree case - no rebalancing required
      root_ = newNode;
      return false;
    } else if (newNode->value < newParentNode->value) {
      newParentNode->left = newNode;
    } else {
      newParentNode->right = newNode;
    }

    // Rebalancing required
    return true;
  }

  void upStreamHeightRecalc(std::shared_ptr<Node> startNode) {
    // Recursion cycle
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

  void rebalanceTree(std::shared_ptr<Node> rotatedNode) {
    // TODO: Check if recursion cycle is required.
    // TODO: Check if heights should be recalculated.
    // Recursion cycle
    while (rotatedNode) {
      std::shared_ptr<Node> oldParent = rotatedNode->parent.lock();

      // Tree rotations are required only if balance factor modulo is greater
      // than 1
      int bFactor = rotatedNode->balanceFactor();
      if (bFactor > 1) {
        // Right sub-tree has greater height,
        // left or right-left rotation required
        bool needRightRotate =
            rotatedNode->left && rotatedNode->left->balanceFactor() < 0;
        if (needRightRotate) {
          rightRotate(rotatedNode->right);
        }
        leftRotate(rotatedNode);
      } else if (bFactor < -1) {
        // Left sub-tree has greater height
        // right or left-right rotation required
        bool needLeftRotate =
            rotatedNode->right && rotatedNode->right->balanceFactor() > 0;
        if (needLeftRotate) {
          leftRotate(rotatedNode->left);
        }
        rightRotate(rotatedNode);
      }

      rotatedNode = oldParent;
    }
  }

  /*
    Left rotation around a-node example:

         apt               apt
          |                 |
          a                 b
         / \               / \
       als  b      =>    a     c
           / \          / \   / \
         bls  c       als bls
             / \

      bls - b left subtree
      als - a left subtree
      apt - a parent
  */
  // Central Node is a; Right Child is b; Parent is apt
  void leftRotate(std::shared_ptr<Node> centralNode) {
    if (!centralNode || !root_)
      return;

    std::shared_ptr<Node> rightChild = centralNode->right;
    std::shared_ptr<Node> parent = centralNode->parent.lock();

    // Nothing to rotate left
    if (!rightChild)
      return;

    // Renewing root_ variable if required
    if (centralNode == root_) {
      root_ = rightChild;
    }

    // Binding nodes during rotation:
    /*
             a
            / \
        (same) bls

        The result is a-sub-tree, which will be denoted below as ast
    */
    centralNode->parent = rightChild;
    centralNode->right = rightChild->left;
    if (rightChild->left) {
      rightChild->left->parent = centralNode;
    }

    // Binding nodes during rotation:
    /*
          apt
           |
           b
          / \
        ast (same)

        The result is b-sub-tree, which will be denoted below as bst
    */
    rightChild->left = centralNode;
    rightChild->parent = parent;

    // Binding node during rotation:
    /*
         apt          apt
         /      OR      \
       bst              bst
    */
    if (parent) {
      if (parent->left == centralNode) {
        parent->left = rightChild;
      } else {
        parent->right = rightChild;
      }
    }
  }

  void rightRotate(std::shared_ptr<Node> centralNode) {
    // Same as leftRotate, but symmetrically
    if (!centralNode || !root_)
      return;

    std::shared_ptr<Node> leftChild = centralNode->left;
    std::shared_ptr<Node> parent = centralNode->parent.lock();

    if (!leftChild)
      return;

    if (centralNode == root_) {
      root_ = leftChild;
    }

    centralNode->parent = leftChild;
    centralNode->left = leftChild->right;
    if (leftChild->right) {
      leftChild->right->parent = centralNode;
    }

    leftChild->right = centralNode;
    leftChild->parent = parent;

    if (parent) {
      if (parent->left == centralNode) {
        parent->left = leftChild;
      } else {
        parent->right = leftChild;
      }
    }
  }

public:
  // Functionality required for tests
  std::vector<VType> getBfsTravers() {
    std::vector<VType> output;

    std::queue<std::shared_ptr<Node>> que;
    que.push(root_);

    while (!que.empty()) {
      auto curNode = que.front();
      que.pop();

      output.push_back(curNode->value);

      if (curNode->left) {
        que.push(curNode->left);
      }
      if (curNode->right) {
        que.push(curNode->right);
      }
    }

    return output;
  }

  // Heavy recursion function for checking the balance of the tree
  bool isBalanced() {
    if (!root_)
      return true;

    return dummyBruteHeight(root_) != -1;
  }

private:
  // Heavy recursion function for checking the balance of the tree
  bool dummyBruteHeight(std::shared_ptr<Node> curNode) {
    if (curNode)
      return 0;

    int ldbh = dummyBruteHeight(curNode->left);
    int rdbh = dummyBruteHeight(curNode->right);

    if (ldbh == -1 || rdbh == -1 || abs(ldbh - rdbh) > 1)
      return -1;

    return 1 + std::max(ldbh, rdbh);
  }

private:
  std::shared_ptr<Node> root_;
};

} // namespace tree
