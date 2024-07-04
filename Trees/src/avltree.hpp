#pragma once

#include <cstdlib>
#include <memory>
#include <queue>  // Only for bfs travers
#include <vector> // Only for bfs travers

namespace tree {

// TODO: Add constructor with initializer list
template <typename VType> class AVL final {
private:
  // Node description
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

private:
  class Iterator final {
    // TODO: Should be bidirectional.
    //       Support all required methods.
    using iterator_category = std::forward_iterator_tag;
    using value_type = VType;
    using difference_type = std::ptrdiff_t;
    using pointer = VType *;
    using reference = VType &;

  public:
    explicit Iterator(std::shared_ptr<Node> node) : iterableNode(node) {}

    std::shared_ptr<Node> operator->() { return iterableNode; }

    bool operator==(const Iterator &other) const {
      return iterableNode == other.iterableNode;
    }

    bool operator!=(const Iterator &other) const {
      return iterableNode != other.iterableNode;
    }

    Iterator &operator++() {
      if (iterableNode->right != nullptr) {
        iterableNode = iterableNode->right;
        while (iterableNode->left != nullptr)
          iterableNode = iterableNode->left;

        return *this;
      } else {
        // TODO: Use one return statement by uniting all if statements
        //       in one if-elseif-else statement

        if (!iterableNode->parent.lock()) {
          iterableNode = iterableNode->parent.lock();
          return *this;
        }

        bool isLeftChild = iterableNode->parent.lock()->left == iterableNode;
        if (isLeftChild) {
          iterableNode = iterableNode->parent.lock();
          return *this;
        } else {
          // Node is right child case:
          iterableNode = iterableNode->parent.lock();
          while (iterableNode->parent.lock() &&
                 iterableNode != iterableNode->parent.lock()->left)
            iterableNode = iterableNode->parent.lock();

          iterableNode = iterableNode->parent.lock();
          return *this;
        }
      }
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

  private:
    std::shared_ptr<Node> iterableNode;
  };

public:
  // TODO: Memoization of left-most node is required
  Iterator begin() {
    std::shared_ptr<Node> curNode = root_;
    while (curNode->left)
      curNode = curNode->left;

    return Iterator(curNode);
  }

  Iterator end() { return Iterator(nullptr); }

public:
  // TODO: How to transfer argument to the following 3 functions
  Iterator find(VType target) {
    std::shared_ptr<Node> curNode = root_;
    while (curNode && curNode->value != target) {
      curNode = (curNode->value > target) ? curNode->left : curNode->right;
    }

    return Iterator{curNode};
  }

  Iterator lower_bound(VType target) {
    std::shared_ptr<Node> curNode = root_;
    std::shared_ptr<Node> res = nullptr;
    while (curNode) {
      if (curNode->value < target) {
        curNode = curNode->right;
      } else {
        res = curNode;
        curNode = curNode->left;
      }
    }

    return Iterator(res);
  }

  Iterator upper_bound(VType target) {
    std::shared_ptr<Node> curNode = root_;
    std::shared_ptr<Node> res = nullptr;
    while (curNode) {
      if (curNode->value <= target) {
        curNode = curNode->right;
      } else {
        res = curNode;
        curNode = curNode->left;
      }
    }

    return Iterator(res);
  }

  // TODO: Improve in terms of absence of elements in the tree the following
  // function;
  //       Use separate non-method function for this functionality;
  size_t getRangeQuerieCount(int first, int second) {
    if (first > second)
      std::swap(first, second);

    Iterator fi = lower_bound(first);
    Iterator si = upper_bound(second);

    // TODO: Improve Iterator to use std::distance
    size_t dist = 0;
    while (fi != si) {
      dist++;
      fi++;
    }

    return dist;
  }

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

    if (ldbh == -1 || rdbh == -1 || std::abs(ldbh - rdbh) > 1)
      return -1;

    return 1 + std::max(ldbh, rdbh);
  }

private:
  std::shared_ptr<Node> root_;
};

} // namespace tree
