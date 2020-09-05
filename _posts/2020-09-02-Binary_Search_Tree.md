---
layout: post
title: BST Implementation
published: true
date: {}
tags: data-structures
---

This post is going to discuss Binary Search Tree (BST) and present two implementations on BST in C++14, Array-Based and Linked-Node-Based.
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

Binary Search Tree (BST) is a sorted binary tree where the rule $$left node < root < right node$$ for every node in the tree satisfies (assuming node values are all unique in BST). 

### 1.1 Operations

### 1.1.1 Principle Operations

1. insert (recursive / iterative)
2. remove
3. searchByValue (recursive / iterative)
4. preOrder
5. inOrder
6. postOrder
7. levelOrder
8. getHeight
9. getRootNode / getRootValue

### 1.1.2 Auxiliary Operations

1. isEmpty
2. isBST
3. countNodes
4. visualizeBST
5. minValue
6. maxValue

### 1.1.3 Auxiliary Functions

1. isEqual
2. deepcopy
3. destroyTree
4. findMinimumNode / findMinimumIndex
5. printLevel
6. calcHeight
7. doublesize
8. reorganizeSubtree


### 1.2 Attributes

**Attribute 1:** At level i ($$i \geq 1$$), the most nodes it can have is $$2^{i-1}$$.

**Attribute 2:** For a BST, the depth is $$\lceil log_2(n+1) \rceil$$ or equivalently $$\lfloor log_2{n} \rfloor + 1$$. (n is the number of nodes in BST)

**Attribute 3:** At depth k ($$k \geq 0$$), the most nodes it can have is $$2^k - 1$$. (at root node, level i = 1, depth k = 0)

**Attribute 4:** For a complete BST containing n nodes, if we numbering nodes consecutively from left to right at every level, then it satisfies:

4.1) if $$index = 1$$, then root node, otherwise, its parent node index is $$\lfloor \frac{index}{2} \rfloor$$

4.2) if $$2 * index \leq n$$, the index of its left child is $$2 * index$$

4.3) if $$2 * index + 1 \leq n$$, the index of its right child is $$2 * index + 1$$

4.4) if $$index \neq 1$$ and $$index \% 2 == 1$$, current node is right child of its parent node

4.5) if $$index \neq 1$$ and $$index \% 2 == 0$$, current node is left child of its parent node

4.6) current node is at the level $$\lceil log_2{index} + 1 \rceil$$

**Attribute 5:** If we know the largest TreeNode id or index with non-initial value, we can calculate the height of BST by the formula:

$$ BST Height = \lfloor log_{2}{largest index} \rfloor + 1$$


### 1.3 Remove Node in BST

When removing a node in BST, it is mandatory to maintain the tree to be still BST-valid after deletion. There are 3 scenarios in this case:

#### Scenario 1. leaf node: The node to be deleted has no children.

*Linked TreeNodes Implementation:*

Simply remove the node from BST and set its parent's corresponding child pointer to nullptr.

*Array Implementation:*

Simply set the node index to initValue.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/imgs/bst-remove-case-1.png" alt="BST deletion case 1" width="250" >
</p>

#### Scenario 2. (partial) internal node: The node to be deleted has 1 child.

##### scenario 2.1: partial internal node has a left child

*Linked TreeNodes Implementation:*

Directly link the left child node to the parent of the removed node, then delete the node.

*Array Implementation:*

Replace the value at removed node index with its left child value, then re-organize its left subtree.

##### scenario 2.2: partial internal node has a right child

*Linked TreeNodes Implementation:*

Directly link the right child node to the parent of the reomved node, then delete the node.

*Array Implementation:*

Replace the value at removed node index with its right child value, then re-organize its right subtree.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/imgs/bst-remove-case-2.png" alt="BST deletion case 2" width="550" >
</p>


#### Scenario 3. (complete) internal node: The node to be deleted has 2 children.

**Step 1:** find the node with minimum value at the right subtree of the removed node.

**Step 2:** replace the value of the node to be removed with the minimum value

**Step 3:** remove the node with minimum value at the right subtree

**(Step 4:)** for array implementation, it also needs re-organization at the index with minimum value at the right subtree.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/imgs/bst-remove-case-3.png" alt="BST deletion case 3" width="800" >
</p>


### 1.4 BST Traversal

#### 1.4.1 pre-order traversal

visit current node -> visit left subtree -> visit right subtree.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/gifs/preorder.gif" alt="Pre-order traversal" width="400" >
</p>


*GIF source: Reference 10*

#### 1.4.2 in-order traversal

visit left subtree -> visit current node -> visit right subtree.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/gifs/inorder.gif" alt="In-order traversal" width="400" >
</p>

*GIF source: Reference 10*

#### 1.4.3 post-order traversal

visit left subtree -> visit right subtree -> visit current node.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/gifs/postorder.gif" alt="Post-order traversal" width="400" >
</p>

*GIF source: Reference 10*

#### 1.4.4 level-order traversal

visit nodes level by level from root to leaf nodes.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/imgs/levelorder.png" alt="Level-order traversal" width="400" >
</p>

---

## 2. Implementation: Array-based BST

Code directory: [/assets/2020-09-02-Binary_Trees/array_based/](https://github.com/Yixuan-Lee/yixuan-lee.github.io/tree/master/assets/2020-09-02-Binary_Trees/src/array_based)

In this implementation, an array is used to represent a pseudo-complete BST as shown below.

<p align="center">
<img src="/assets/2020-09-02-Binary_Trees/imgs/array-bst.png" width=500>
</p>

While instantiating an object of *ArrayBST*, we need to provide 

* the generic type *T* : indicate what type we want the BST to represent.
* the initial value : indicate what the initial value at each index in the array.
* the size : indicate the size of array we will initialize.

When inserting a value, if the appropriate index at which the value is going to insert exceeds the current array capacity, expansion on array and element-wise copy steps are performed automatically before the insertion.

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

For insertion and search operations, there are two approaches, recursive & iterative, which have been implemented.

For getHeight function, there also are two ways (recursive and calculate by formula above) to implement it. In the implementation, the recursive approach is used.

---

## Further Learning

As BST inserts and remove nodes, it is very easy for the BST to be unbalanced, resulting high time complexity on searching, inserting and remove. I found AVL Tree is self-balancing BST where the difference between heights of left and right subtrees cannot be more than one for all nodes. 

Next, I will implement the self-balancing feature on the current BST in another post.

---

## References

1. [Binary Search Tree GIF source](https://blog.penjee.com/5-gifs-to-understand-binary-search-tree/)

2. [Binary Search Tree Attributes](https://www.cnblogs.com/WindSun/p/10859055.html)

3. [Binary Search Tree Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)

4. [BST Removal Operation](http://www.algolist.net/Data_structures/Binary_search_tree/Removal)

5. [BST Removal Operation 2](https://helloacm.com/how-to-delete-a-node-from-a-binary-search-tree/)

6. [BST Insertion Operation](https://www.techiedelight.com/insertion-in-bst/)

7. [BST Level Order Traversal](https://www.techiedelight.com/level-order-traversal-binary-tree/)

8. [Calculate the height of BST](https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/)

9. [Draw a binary tree on console in C++](https://stackoverflow.com/questions/21128276/c-drawing-binary-tree-in-console-problems)

10. [Tree traversal GIF source](https://blog.csdn.net/weixin_45525272/article/details/105837185)

11. [BST Array Implementation remove operation](http://datastructuresinterview.blogspot.com/2012/12/delete-node-in-bst-using-arrays.html)

12. [BST Removal explanation in Java](http://www.java2novice.com/java-interview-programs/delete-node-binary-search-tree-bst/)


