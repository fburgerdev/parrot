#pragma once
#include "common.hh"

namespace Parrot {
  /// @brief Node in a tree data-structure.
  /// @tparam T Derived type 
  template<class T>
  class TreeNode {
  public:
    /// @todo Assert that tree is non-cyclic
    TreeNode(TreeNode<T>* parent = nullptr);
    TreeNode(const TreeNode<T>&);
    TreeNode(TreeNode<T>&& other) noexcept;
    virtual ~TreeNode();
    TreeNode<T>& operator=(const TreeNode<T>&);
    TreeNode<T>& operator=(TreeNode<T>&& other) noexcept;

    bool hasParent() const;
    const T* getParent() const;
    /// @todo Assert that tree is non-cyclic
    void setParent(TreeNode<T>* parent);
  private:
    void detach();

    TreeNode<T>* _parent;
    HashSet<TreeNode<T>*> _children;
  };
}
#include "tree_node_impl.hh"