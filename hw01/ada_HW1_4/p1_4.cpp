#include "p1_4.h"
#include <vector>
#include <string>

bool compare_identical(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_fl_ver(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[A.size() - i - 1][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_fl_hori(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[i][A[0].size() - j - 1])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_rot180(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[A.size() - i - 1][A[0].size() - j - 1])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_rot90(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[j][A.size() - i - 1])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_rot270(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[A.size() - j - 1][i])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_rot90_ver(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_rot90_hori(std::vector<std::string> &A, std::vector<std::string> &B)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            if (A[i][j] != B[A.size() - j - 1][A[0].size() - i - 1])
            {
                return false;
            }
        }
    }
    return true;
}

bool compare_polyominoes(std::vector<std::string> &A, std::vector<std::string> &B)
{
    // identical
    // check flipping vertically
    // check flipping horizontally
    // check flipping twice === rotate 180 degree

    // for W == L
    // check rotate of 90 degree
    // check rotate of 270 degree
    // check 90 -> ver === 270 -> hori === ver -> 270 === hori -> 90
    // check 90 -> hori === 270 -> ver === hori -> 270 === ver -> 90
    if (A.size() != A[0].size())
        return compare_identical(A, B) || compare_fl_ver(A, B) || compare_fl_hori(A, B) || compare_rot180(A, B);
    else
        return compare_identical(A, B) || compare_fl_ver(A, B) || compare_fl_hori(A, B) || compare_rot180(A, B) || compare_rot90(A, B) || compare_rot270(A, B) || compare_rot90_ver(A, B) || compare_rot90_hori(A, B);
}
