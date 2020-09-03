---
layout: post
title: BST Implementation
published: true
date: 2020-09-02T00:00:00.000Z
tags: data-structures
---

This post is going to discuss Binary Search Tree (BST) and present two implementation on BST in C++14, Array-Based and Linked-Node-Based.
<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/gifs/binary-search-tree.gif" alt="Binary Search Tree animation" width="450" >
</p>

Keywords:

1. Data Structure
2. C++

Asset directory: [/assets/2020-09-02-Binary_Trees/](https://github.com/Yixuan-Lee/yixuan-lee.github.io/tree/master/assets/2020-09-02-Binary_Trees)

<!--more-->

---

## 1. Binary Search Trees (BST)

Binary Search Tree (BST) is a sorted binary tree where the rule $$left node \le root \le right node$$ for every node in the tree satisfies (assuming node values are all unique in BST). 

### 1.1 Operations

### 1.1.1 Principle Operations

1. insert
2. remove
3. searchByValue
4. preOrder
5. inOrder
6. postOrder
7. levelOrder
8. getHeight
9. getRoot

### 1.1.2 Auxiliary Operations

1. isEmpty
2. isBST
3. getParent
4. getLeftChild
5. getRightChild
6. countNodes
7. destroyTree

### 1.1.3 Auxiliary Functions

1. isEqual
2. deepcopy


### 1.2 Attributes

Attribute 1: At level i ($$i \geq 1$$), the most nodes it can have is $$2^{i-1}$$.

Attribute 2: For a BST, the depth is $$\lceil log_2(n+1) \rceil$$ or equivalently $$\lfloor log_2{n} \rfloor + 1$$. (n is the number of nodes in BST)

Attribute 3: At depth k ($$k \geq 0$$), the most nodes it can have is $$2^k - 1$$. (at root node, level i = 1, depth k = 0)

Attribute 4: For a complete BST containing n nodes, if we numbering nodes consecutively from left to right at every level, then it satisfies:

4.1) if $$index = 1$$, then root node, otherwise, its parent node index is $$\lfloor \frac{index}{2} \rfloor$$

4.2) if $$2 * index \leq n$$, the index of its left child is $$2 * index$$

4.3) if $$2 * index + 1 \leq n$$, the index of its right child is $$2 * index + 1$$

4.4) if $$index \neq 1$$ and $$index \% 2 == 1$$, current node is right child of its parent node

4.5) if $$index \neq 1$$ and $$index \% 2 == 0$$, current node is left child of its parent node

4.6) current node is at the level $$\lceil log_2{index} + 1 \rceil$$


### 1.3 Traversal





---

## 2. Implementation: Array-based BST

Code directory: [/assets/2020-09-02-Binary_Trees/array_based/](https://github.com/Yixuan-Lee/yixuan-lee.github.io/tree/master/assets/2020-09-02-Binary_Trees/src/array_based)

In this implementation, an array is used to represent a pseudo-complete BST as shown below.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/imgs/array-bst.png" width=500>
</p>



---

## 3. Implementation: Linked-Node-based BST

Code directory: [/assets/2020-09-02-Binary_Trees/linked_nodes_based/](https://github.com/Yixuan-Lee/yixuan-lee.github.io/tree/master/assets/2020-09-02-Binary_Trees/src/linked_treenodes_based)

In this implementation, each node is split into three parts:

1. left child pointer
2. data
3. right child pointer

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/imgs/linked-nodes-bst.png" width=200>
</p>

---

## Further Learning

---

## References

1. [Binary Search Tree GIF source](https://blog.penjee.com/5-gifs-to-understand-binary-search-tree/)

2. [Binary Search Tree Attributes](https://www.cnblogs.com/WindSun/p/10859055.html)

3. [Binary Search Tree Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)
