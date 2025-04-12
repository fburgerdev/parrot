#pragma once

namespace Parrot {
  template<class T, usize N>
  Vec<T, N> MaterialNode::parseVec(const auto& node) {
    Vec<T, N> vec;
    for (usize n = 0; n < N; ++n) {
      vec.at(n) = T(node.at(n));
    }
    return vec;
  }
  template<class T, usize N, usize M>
  Mat<T, N, M> MaterialNode::parseMat(const auto& node) {
    Mat<T, N, M> mat;
    for (usize n = 0; n < N; ++n) {
      for (usize m = 0; m < M; ++m) {
        mat.at(n, m) = T(node.at(n).at(m));
      }
    }
    return mat;
  }
}