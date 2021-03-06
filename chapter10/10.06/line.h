#ifndef __LINE_H__
#define __LINE_H__

#include <cassert>
#include <cmath>
#include <limits>

static const double epsilon = 1.e-10;

/** @brief A point represented as a pair of coordinates (x,y). */
struct point
{
    double x;
    double y;
};

/**
 * @brief Given two points A and B, returns (A-B).
 * @note Complexity: O(1) in both time and space.
 */
point operator-(const point& A, const point& B)
{
    return point{A.x - B.x, A.y - B.y};
}

/**
 * @brief Computes the dot product of two 2-vectors A and B.
 * @note Complexity: O(1) in both time and space.
 */
double operator*(const point& A, const point& B)
{
    return A.x * B.x + A.y * B.y;
}

/**
 * @brief Computes the distance between the origin (0,0) and a point A.
 * @note Complexity: O(1) in both time and space.
 */
double norm(const point& A)
{
    return std::sqrt(A * A);
}

/**
 * @brief Returns true if two points A and B are equal, false otherwise.
 * @note Complexity: O(1) in both time and space.
 */
bool operator==(const point& A, const point& B)
{
    return norm(B - A) < epsilon;
}

/**
 * @brief Returns true if two points A and B are distinct, false otherwise.
 * @note Complexity: O(1) in both time and space.
 */
bool operator!=(const point& A, const point& B)
{
    return !(A == B);
}

/** @brief A representation of a line through a pair of distinct points. */
class line
{
public:
    line(const point& __A, const point& __B) : A(__A), B(__B)
    {
        assert(A != B);
    }

    /**
     * @brief Computes the sine of the angle measured from the positive x
     *        axis to the line in the counterclockwise direction.
     * @note Complexity: O(1) in both time and space.
     */
    double sine() const
    {
        /* special case: line is (nearly) vertical */
        if (std::abs(A.x - B.x) < epsilon)
        {
            return 1.0;
        }
        else if (B.x > A.x)
        {
            return (B.y - A.y) / norm(B - A);
        }
        else
        {
            return (A.y - B.y) / norm(B - A);
        }
    }

    /**
     * @brief Computes the x-intercept value of the line.
     * @note Complexity: O(1) in both time and space.
     */
    double x_intercept() const
    {
        /* special case: line is (nearly) horizontal */
        if (std::abs(A.y - B.y) < epsilon)
        {
            return std::numeric_limits<double>::max();
        }

        double m = (B.x - A.x) / (B.y - A.y);
        return A.x - m * A.y;
    }

    /**
     * @brief Computes the y-intercept value of the line.
     * @note Complexity: O(1) in both time and space.
     */
    double y_intercept() const
    {
        /* special case: line is (nearly) vertical */
        if (std::abs(A.x - B.x) < epsilon)
        {
            return std::numeric_limits<double>::max();
        }

        double m = (B.y - A.y) / (B.x - A.x);
        return A.y - m * A.x;
    }

    /**
     * @brief Returns true if the line crosses a point C, false otherwise.
     * @note Complexity: O(1) in both time and space.
     */
    bool crosses(const point& C) const
    {
        /* if C lies "on top of" A or B */
        if (A == C || B == C)
        {
            return true;
        }

        double bc = norm(C - B);
        double ab = norm(B - A);

        /*
         * ||(B-A)*(C-B)| - |B-A||C-B|| / (|B-A||C-B|) = ||cos(t)|-1|,
         * where cos(t) is the angle between AB and BC; given that
         * C != A and C != B, this angle will be either 0 or pi if
         * C is along the line AB, and since cos(t) = +/-1 for t = 0/pi
         * respectively, C is on the line only if ||cos(t)|-1| < epsilon
         */
        return (std::abs(std::abs((B - A) * (C - B)) - ab * bc) <
                epsilon * ab * bc);
    }

    friend bool operator==(const line& r, const line& s);

private:
    point A;
    point B;
};

/**
 * @brief Returns true if r and s are the same line, false otherwise.
 * @note Complexity: O(1) in both time and space.
 */
bool operator==(const line& r, const line& s)
{
    return r.crosses(s.A) && r.crosses(s.B);
}

/**
 * @brief Returns true if r and s are distinct lines, false otherwise.
 * @note Complexity: O(1) in both time and space.
 */
bool operator!=(const line& r, const line& s)
{
    return !(r == s);
}

#endif /* __LINE_H__ */
