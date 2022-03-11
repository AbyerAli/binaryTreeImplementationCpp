#include <iostream>

using namespace std;

class TreeNode {
private:
  int data;
  TreeNode *leftChild;
  TreeNode *rightChild;

public:
  TreeNode(int data) {
    this->data = data;
    leftChild = NULL;
    rightChild = NULL;
  }
  void setLeftChild(TreeNode *newTreeNode) { this->leftChild = newTreeNode; }
  TreeNode *getLeftChild() { return leftChild; }
  void setRightChild(TreeNode *newTreeNode) { this->rightChild = newTreeNode; }
  TreeNode *getRightChild() { return rightChild; }
  void setData(int data) { this->data = data; }
  int getData() { return data; }
};

class Node {
  TreeNode *treeNode;
  Node *next;

public:
  Node(TreeNode *treeNode) {
    this->treeNode = treeNode;
    next = NULL;
  }
  Node *getNext() { return next; }
  void setNext(Node *newNode) { this->next = newNode; }
  void setTreeNode(TreeNode *newTreeNode) { treeNode = newTreeNode; }
  TreeNode *getTreeNode() { return treeNode; }
};

class Queue {
  Node *top;
  Node *bottom;

public:
  Queue() {
    setTop(NULL);
    setBottom(NULL);
  }
  bool isEmpty() { return top == NULL; }
  void setTop(Node *newNode) { top = newNode; }
  Node *getTop() { return top; }
  void setBottom(Node *newNode) { bottom = newNode; }
  Node *getBottom() { return bottom; }
  void enqueue(TreeNode *newTreeNode) {
    Node *newNode = new Node(newTreeNode);
    if (isEmpty()) {
      setTop(newNode);
      setBottom(newNode);
    } else {
      getBottom()->setNext(newNode);
      setBottom(newNode);
    }
  }
  void dequeue() {
    if (isEmpty()) {
      cout << "Nothing to dequeue" << endl;
    } else {
      // !!
      Node *prevTop = getTop();
      setTop(getTop()->getNext());
      delete prevTop;
      prevTop = NULL;
      if (getTop() == NULL) {
        setBottom(NULL);
      }
    }
  }
  // for demo only
  void display() {
    Node *currentNode = getTop();
    while (currentNode != NULL) {
      cout << currentNode->getTreeNode()->getData() << endl;
      currentNode = currentNode->getNext();
    }
  }
};

class Tree {
  TreeNode *root;
  bool isEmpty() { return root == NULL; }
  void setRoot(TreeNode *newNode) { this->root = newNode; }
  TreeNode *getRoot() { return root; }
  bool deleteTreeNode(TreeNode *lastTreeNode, int data) {
    // Check if it's the root node that's to be removed.
    if (getRoot()->getData() == data) {
      if (getRoot()->getLeftChild() != NULL) {
        lastTreeNode->setLeftChild(getRoot()->getLeftChild());
      }
      if (getRoot()->getRightChild() != NULL) {
        lastTreeNode->setRightChild(getRoot()->getRightChild());
      }
      delete getRoot();
      setRoot(lastTreeNode);
      return true;
    }

    // find the node to remove and replace the  node with lastTreeNode.
    Queue queueObj;
    TreeNode *currentTreeNode;
    queueObj.enqueue(getRoot());
    while (!queueObj.isEmpty()) {
      currentTreeNode = queueObj.getTop()->getTreeNode();
      queueObj.dequeue();
      if (currentTreeNode->getLeftChild() != NULL) {
        // Check if this is the node that's to be removed
        if (currentTreeNode->getLeftChild()->getData() == data) {
          if (currentTreeNode->getLeftChild()->getLeftChild() != NULL) {
            lastTreeNode->setLeftChild(
                currentTreeNode->getLeftChild()->getLeftChild());
          }
          if (currentTreeNode->getLeftChild()->getRightChild() != NULL) {
            lastTreeNode->setRightChild(
                currentTreeNode->getLeftChild()->getRightChild());
          }
          delete currentTreeNode->getLeftChild();
          currentTreeNode->setLeftChild(NULL);
          currentTreeNode->setLeftChild(lastTreeNode);
          return true;
        }
        queueObj.enqueue(currentTreeNode->getLeftChild());
      }
      if (currentTreeNode->getRightChild() != NULL) {
        // Check if it's the node to be removed.
        if (currentTreeNode->getRightChild()->getData() == data) {
          if (currentTreeNode->getRightChild()->getLeftChild() != NULL) {
            lastTreeNode->setLeftChild(
                currentTreeNode->getRightChild()->getLeftChild());
          }
          if (currentTreeNode->getRightChild()->getRightChild() != NULL) {
            lastTreeNode->setRightChild(
                currentTreeNode->getRightChild()->getRightChild());
          }
          delete currentTreeNode->getRightChild();
          currentTreeNode->setRightChild(NULL);
          currentTreeNode->setRightChild(lastTreeNode);
          return true;
        }
        queueObj.enqueue(currentTreeNode->getRightChild());
      }
    }
    // Node was not found!
    return false;
  }

public:
  Tree() { setRoot(NULL); }
  void insertData(int data) {
    Queue queueObj;
    TreeNode *newTreeNode = new TreeNode(data);
    if (isEmpty()) {
      setRoot(newTreeNode);
    } else {
      queueObj.enqueue(getRoot());
      TreeNode *currentTreeNode;
      while (!queueObj.isEmpty()) {
        currentTreeNode = queueObj.getTop()->getTreeNode();
        queueObj.dequeue();

        if (currentTreeNode->getLeftChild() == NULL) {
          currentTreeNode->setLeftChild(newTreeNode);
          return;
        }
        queueObj.enqueue(currentTreeNode->getLeftChild());

        if (currentTreeNode->getRightChild() == NULL) {
          currentTreeNode->setRightChild(newTreeNode);
          return;
        }
        queueObj.enqueue(currentTreeNode->getRightChild());
      }
    }
  }
  void displayTree() {
    Queue queueObj;
    if (getRoot() == NULL) {
      cout << "Nothing to show!" << endl;
    } else {
      TreeNode *currentTreeNode;
      queueObj.enqueue(getRoot());
      while (!queueObj.isEmpty()) {
        currentTreeNode = queueObj.getTop()->getTreeNode();
        // cout << currentTreeNode->getData() << " --> ";
        cout << currentTreeNode->getData() << " ";
        queueObj.dequeue();
        if (currentTreeNode->getLeftChild() != NULL) {
          // cout << currentTreeNode->getLeftChild()->getData() << "l ";
          queueObj.enqueue(currentTreeNode->getLeftChild());
        }
        if (currentTreeNode->getRightChild() != NULL) {
          // cout << currentTreeNode->getRightChild()->getData() << "r ";
          queueObj.enqueue(currentTreeNode->getRightChild());
        }
        // cout << endl;
      }
    }
  }

  bool upgrade(int key, int newValue) {

    Queue queueObj;
    TreeNode *currentTreeNode;
    queueObj.enqueue(getRoot());

    while (!queueObj.isEmpty()) {
      currentTreeNode = queueObj.getTop()->getTreeNode();
      queueObj.dequeue();
      if (currentTreeNode->getData() == key) {
        currentTreeNode->setData(newValue);
        return true;
      }
      if (currentTreeNode->getLeftChild() != NULL) {
        queueObj.enqueue(currentTreeNode->getLeftChild());
      }
      if (currentTreeNode->getRightChild() != NULL) {
        queueObj.enqueue(currentTreeNode->getRightChild());
      }
    }
    return false;
  }

  TreeNode *search(int key) {

    Queue queueObj;
    TreeNode *currentTreeNode;
    queueObj.enqueue(getRoot());

    while (!queueObj.isEmpty()) {
      currentTreeNode = queueObj.getTop()->getTreeNode();
      queueObj.dequeue();
      if (currentTreeNode->getData() == key) {
        return currentTreeNode;
      }
      if (currentTreeNode->getLeftChild() != NULL) {
        queueObj.enqueue(currentTreeNode->getLeftChild());
      }
      if (currentTreeNode->getRightChild() != NULL) {
        queueObj.enqueue(currentTreeNode->getRightChild());
      }
    }
    return NULL;
  }

  bool deleteNode(int data) {
    Queue queueObj;
    bool deleted;
    if (getRoot() == NULL) {
      cout << "nothing to remove! " << endl;
      return false;
    } else {
      TreeNode *currentTreeNode;
      queueObj.enqueue(getRoot());

      // First Find the first available node with both child equal to null then
      // replace it with node to be deleted.
      while (!queueObj.isEmpty()) {
        currentTreeNode = queueObj.getTop()->getTreeNode();
        queueObj.dequeue();

        if (currentTreeNode->getLeftChild() != NULL) {
          // Also check if it's the parent to the last Node
          if (currentTreeNode->getLeftChild()->getRightChild() == NULL &&
              currentTreeNode->getLeftChild()->getLeftChild() == NULL) {
            // also check if it's the node that needs to be removed
            if (currentTreeNode->getLeftChild()->getData() == data) {
              delete currentTreeNode->getLeftChild();
              deleted = true;
            } else {
              deleted = deleteTreeNode(currentTreeNode->getLeftChild(), data);
            }
            currentTreeNode->setLeftChild(NULL);
            return deleted;
          }
          queueObj.enqueue(currentTreeNode->getLeftChild());
        }
        if (currentTreeNode->getRightChild() != NULL) {
          // Also check if it's the parent to the last Node
          if (currentTreeNode->getRightChild()->getRightChild() == NULL &&
              currentTreeNode->getRightChild()->getLeftChild() == NULL) {
            // also check if it's the node that needs to be removed
            if (currentTreeNode->getRightChild()->getData() == data) {
              delete currentTreeNode->getRightChild();
              deleted = true;
            } else {
              deleted = deleteTreeNode(currentTreeNode->getRightChild(), data);
            }
            currentTreeNode->setRightChild(NULL);
            return deleted;
          }
          queueObj.enqueue(currentTreeNode->getRightChild());
        }
      }
    }
  }
};

int main() {

  Tree obj;
  obj.insertData(11);
  obj.insertData(22);
  obj.insertData(33);
  obj.insertData(44);
  obj.insertData(55);
  obj.insertData(66);
  obj.insertData(77);
  obj.insertData(88);
  obj.insertData(99);
  obj.insertData(36);
  obj.insertData(68);
  obj.insertData(93);
  obj.displayTree();

  // TreeNode *found = obj.search(11123131);
  // if(found == NULL) {
  //     cout << "not found!" << endl;
  // } else {
  //     cout << found->getData();
  // }

  // bool x = obj.deleteNode(89000);
  // if(x) {
  //     cout << "deleted" << endl;
  // } else {
  //     cout << "not found!" << endl;
  // }
  // // obj.displayTree();
}
