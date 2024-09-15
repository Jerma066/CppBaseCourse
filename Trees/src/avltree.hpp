#pragma once

#include <cstdlib>
#include <memory>
#include <queue>  // For bfs and lca
#include <vector> // Only for bfs travers

namespace tree {

// TODO: Add constructor with initializer list
// TODO: Add delete method
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

    void recalcHeight() {
      int leftSubTreeHeight = left ? left->height : -1;
      int rightSubTreeHeight = right ? right->height : -1;
      height = 1 + std::max(leftSubTreeHeight, rightSubTreeHeight);
    }

    void recalcSubTreeSize() {
      int leftStSize = left ? left->subTreeSize : 0;
      int rightStSize = right ? right->subTreeSize : 0;
      subTreeSize = 1 + leftStSize + rightStSize;
    }

    VType value;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    int height = 0;
    int subTreeSize = 1;
  };

public:
  class Iterator final {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = VType;
    using pointer = VType *;
    using reference = VType &;

  public:
    explicit Iterator(std::shared_ptr<Node> node) : iterableNode(node) {}

    std::shared_ptr<Node> operator->() { return iterableNode; }
    reference operator*() { return iterableNode->value; }

    bool operator==(const Iterator &other) const {
      return iterableNode == other.iterableNode;
    }

    bool operator!=(const Iterator &other) const {
      return iterableNode != other.iterableNode;
    }

    Iterator &operator++() {
      // Check if the right node is available
      if (iterableNode->right != nullptr) {
        iterableNode = iterableNode->right;
        while (iterableNode->left != nullptr)
          iterableNode = iterableNode->left;
      } else {
        // If iterableNode is the left child - iterate to the parent.
        // If it is the right child, iterate to the parent's parent (or further)
        // where it is the left child.
        while (iterableNode->parent.lock() &&
               iterableNode == iterableNode->parent.lock()->right)
          iterableNode = iterableNode->parent.lock();

        iterableNode = iterableNode->parent.lock();
      }

      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    // Same as operator++, but symmetrically
    Iterator operator--() {
      if (iterableNode->left != nullptr) {
        iterableNode = iterableNode->left;
        while (iterableNode->right != nullptr)
          iterableNode = iterableNode->right;
      } else {
        std::shared_ptr<Node> parent = iterableNode->parent.lock();
        while (parent != nullptr && iterableNode == parent->left) {
          iterableNode = parent;
          parent = iterableNode->parent.lock();
        }
        iterableNode = parent;
      }

      return *this;
    }

    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }

  private:
    std::shared_ptr<Node> iterableNode;
  };

public:
  Iterator begin() { return Iterator(first_); }
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

public:
  size_t size() {
    if (!root_)
      return 0;
    return root_->subTreeSize;
  }

  size_t getRangeQuerieCount(int first, int second) {
    if (first > second)
      std::swap(first, second);

    Iterator fi = lower_bound(first);
    Iterator si = upper_bound(second);

    return std::distance(fi, si);
  }

private:
  /**
   * @brief Counts the number of elements greater than the given element in the
   * allocated subtree.
   *
   * @params curElem - the given element; sbRoot - the root of allocated subtree
   * @return The number of greater elements in subtree.
   */
  int countGreaterElements(Iterator curElem, Iterator sbRoot) {
    int resCnt = 0;
    if (curElem == sbRoot)
      resCnt += curElem->right ? curElem->right->subTreeSize : 0;

    auto mainElemValue = curElem->value;
    while (curElem != sbRoot) {
      if (curElem->value >= mainElemValue) {
        resCnt += curElem->right ? curElem->right->subTreeSize : 0;
        if (curElem->value > mainElemValue)
          resCnt += 1;
      }
      curElem = Iterator(curElem->parent.lock());
    }

    return resCnt;
  }

  // TODO: Maybe it is beter to combine two functions into one
  // Same as countGreaterElements, but symmetrically
  int countLessElements(Iterator curElem, Iterator sbRoot) {
    int resCnt = 0;
    if (curElem == sbRoot)
      resCnt += curElem->left ? curElem->left->subTreeSize : 0;

    auto mainElemValue = curElem->value;
    while (curElem != sbRoot) {
      if (curElem->value <= mainElemValue) {
        resCnt += curElem->left ? curElem->left->subTreeSize : 0;
        if (curElem->value < mainElemValue)
          resCnt += 1;
      }
      curElem = Iterator(curElem->parent.lock());
    }

    return resCnt;
  }

public:
  int fastGetRangeQuerieCount(int first, int second) {
    if (first > second)
      std::swap(first, second);

    Iterator fi = lower_bound(first);
    Iterator si = lower_bound(second);

    if (fi == end()) {
      return 0;
    } else if (si == end()) {
      int greaterThanFiCnt = countGreaterElements(fi, end());
      return greaterThanFiCnt + 1;
    }

    Iterator lca = getLowestCommonAncestor(fi, si);

    int lessThanFiCnt = countLessElements(fi, lca);
    if (first > fi->value)
      lessThanFiCnt += 1;

    int greaterThanSiCnt = countGreaterElements(si, lca);
    if (second < si->value)
      greaterThanSiCnt += 1;

    return lca->subTreeSize - lessThanFiCnt - greaterThanSiCnt;
  }

  void insert(VType newVal) {
    auto newNode = std::make_shared<Node>(newVal, std::weak_ptr<Node>());
    // STEP 1: Inserting as in BST
    bool needRebalancing = insertNode(newNode);

    // STEP 2: Height calculating
    upStreamNodesParametersRecalc(newNode);

    if (needRebalancing) {
      // STEP 3: Tree balancing
      rebalanceTree(newNode->parent.lock());

      // STEP 4: Update lowest elem for begin() method
      recalcFirstElem();
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
      first_ = newNode;
      return false;
    } else if (newNode->value < newParentNode->value) {
      newParentNode->left = newNode;
    } else {
      newParentNode->right = newNode;
    }

    // Rebalancing required
    return true;
  }

  void upStreamNodesParametersRecalc(std::shared_ptr<Node> startNode) {
    auto curNode = startNode;
    while (curNode && curNode->parent.lock()) {
      curNode->parent.lock()->subTreeSize++;
      curNode = curNode->parent.lock();
    }

    curNode = startNode;
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

    // Height update: First step is a-node, second step is b-node
    centralNode->recalcHeight();
    rightChild->recalcHeight();

    // Size update: First step is a-node, second step is b-node
    centralNode->recalcSubTreeSize();
    rightChild->recalcSubTreeSize();
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

    centralNode->recalcHeight();
    leftChild->recalcHeight();

    centralNode->recalcSubTreeSize();
    leftChild->recalcSubTreeSize();
  }

  void recalcFirstElem() {
    std::shared_ptr<Node> curNode = root_;
    while (curNode->left)
      curNode = curNode->left;

    first_ = std::move(curNode);
  }

  // TOOD: Optimize LCA; 2*O(log(n)) memory usage
  Iterator getLowestCommonAncestor(Iterator lhs, Iterator rhs) {
    // Collecting pathes to root
    std::vector<Iterator> lhsPathToRoot;
    Iterator rootIter = Iterator(root_);
    while (lhs != rootIter) {
      lhsPathToRoot.push_back(lhs);
      lhs = Iterator(lhs->parent.lock());
    }
    lhsPathToRoot.push_back(rootIter);

    std::vector<Iterator> rhsPathToRoot;
    while (rhs != rootIter) {
      rhsPathToRoot.push_back(rhs);
      rhs = Iterator(rhs->parent.lock());
    }
    rhsPathToRoot.push_back(rootIter);

    // Obtaining LCA
    Iterator res(nullptr);
    while (!lhsPathToRoot.empty() && !rhsPathToRoot.empty()) {
      if (lhsPathToRoot.back() == rhsPathToRoot.back()) {
        res = lhsPathToRoot.back();
        lhsPathToRoot.pop_back();
        rhsPathToRoot.pop_back();
      } else {
        break;
      }
    }

    return res;
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
  std::shared_ptr<Node> first_;
};

} // namespace tree
