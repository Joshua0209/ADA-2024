#include "p2_5.h"
#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int score;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int s) : score(s), left(nullptr), right(nullptr) {}
};

int getHeight(TreeNode *root)
{
    if (!root)
        return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

TreeNode *buildTree(const std::vector<int> &l, const std::vector<int> &r, const std::vector<int> &s, int node)
{
    if (node == 0)
    {
        return nullptr; // no child
    }

    // Create a new TreeNode with the score of the current node
    TreeNode *root = new TreeNode(s[node]);

    // Recursively construct the left and right subtrees
    root->left = buildTree(l, r, s, l[node]);
    root->right = buildTree(l, r, s, r[node]);

    return root;
}

void preOrder(TreeNode *root)
{
    if (!root)
        return;
    cout << root->score << " ";
    preOrder(root->left);
    preOrder(root->right);
}

TreeNode *makePerfect(TreeNode *root, int currentHeight, int targetHeight)
{
    if (currentHeight == targetHeight)
    {
        return root;
    }
    if (!root)
    {
        TreeNode *newNode = new TreeNode(0);
        newNode->left = makePerfect(newNode->left, currentHeight + 1, targetHeight);
        newNode->right = makePerfect(newNode->right, currentHeight + 1, targetHeight);
        return newNode;
    }
    root->left = makePerfect(root->left, currentHeight + 1, targetHeight);
    root->right = makePerfect(root->right, currentHeight + 1, targetHeight);
    return root;
}

long long recur_solve(TreeNode *now_1, TreeNode *now_2)
{
    if (now_1->left == nullptr || now_1->right == nullptr || now_2->left == nullptr || now_2->right == nullptr)
    {
        return now_1->score >= now_2->score ? now_1->score - now_2->score : now_2->score - now_1->score;
    }

    long long noSwap = recur_solve(now_1->left, now_2->left) + recur_solve(now_1->right, now_2->right);
    long long swap = recur_solve(now_1->left, now_2->right) + recur_solve(now_1->right, now_2->left);
    long long val = now_1->score >= now_2->score ? now_1->score - now_2->score : now_2->score - now_1->score;

    return min(noSwap, swap) + val;
}

long long solve(int N, int M,
                vector<int> l1, vector<int> r1, vector<int> s1,
                vector<int> l2, vector<int> r2, vector<int> s2)
{
    TreeNode *rootT1 = buildTree(l1, r1, s1, 1);
    TreeNode *rootT2 = buildTree(l2, r2, s2, 1);
    int height = max(getHeight(rootT1), getHeight(rootT2));
    makePerfect(rootT1, 0, height);
    makePerfect(rootT2, 0, height);
    // preOrder(rootT1);
    // cout << "\n";
    // preOrder(rootT2);
    // cout << "\n";

    return recur_solve(rootT1, rootT2);
}
