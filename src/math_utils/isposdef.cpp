/**
 * @file isposdef.cpp
 * 
 * @brief 实现对于矩阵正定的判断
 */

#include "balta_toolkit/balta_toolkit.hpp"
#include <Eigen/Dense>

namespace balta_toolkit::math_utils{
    
bool isposdef(const double* matrix, const int row){
    using namespace Eigen;
    if (!matrix || row <= 0) return false;

    // Map 列主序矩阵（零拷贝）
    Map<const Matrix<double, Dynamic, Dynamic, ColMajor>> A(matrix, row, row);

    // 检查是否存在 NaN/Inf
    if (!A.allFinite()) return false;

    // 数值对称化（防止上游微小非对称导致 LLT 失败）
    MatrixXd S = 0.5 * (A + A.transpose());

    // 使用 Cholesky (LLT) 判断是否正定
    LLT<MatrixXd> llt(S);
    if (llt.info() == Success)
        return true;

    // 如果想允许“半正定”通过，可改用 LDLT 并检查最小特征值
    // LDLT<MatrixXd> ldlt(S);
    // auto diag = ldlt.vectorD();
    // return (diag.minCoeff() > -1e-12);

    return false;
}

}
