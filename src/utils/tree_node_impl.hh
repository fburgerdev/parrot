#pragma once

namespace Parrot {
  template<class T>
  TreeNode<T>::TreeNode(TreeNode<T>* parent)
    : _parent(parent) {
    if (_parent) {
      _parent->_children.insert(this);
    }
  }
  template<class T>
  TreeNode<T>::TreeNode(const TreeNode<T>&)
    : _parent(nullptr) {}
  template<class T>
  TreeNode<T>::TreeNode(TreeNode<T>&& other) noexcept
    : _parent(std::exchange(other._parent, nullptr)),
    _children(std::move(other._children)) {
    if (_parent) {
      _parent->_children.erase(&other);
      _parent->_children.insert(this);
    }
    for (TreeNode<T>* child : _children) {
      child->_parent = this;
    }
  }
  template<class T>
  TreeNode<T>::~TreeNode() {
    detach();
  }
  template<class T>
  TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>&) {
    return *this;
  }
  template<class T>
  TreeNode<T>& TreeNode<T>::operator=(TreeNode<T>&& other) noexcept {
    detach();
    _parent = std::exchange(other._parent, nullptr);
    _children = std::move(other._children);
    if (_parent) {
      _parent->_children.erase(&other);
      _parent->_children.insert(this);
    }
    for (TreeNode<T>* child : _children) {
      child->_parent = this;
    }
    return *this;
  }

  template<class T>
  bool TreeNode<T>::hasParent() const {
    return _parent;
  }
  template<class T>
  const T* TreeNode<T>::getParent() const {
    return dynamic_cast<const T*>(_parent);
  }
  template<class T>
  void TreeNode<T>::setParent(TreeNode<T>* parent) {
    if (_parent) {
      _parent->_children.erase(this);
    }
    if (parent) {
      parent->_children.insert(this);
    }
    _parent = parent;
  }

  template<class T>
  void TreeNode<T>::detach() {
    if (_parent) {
      _parent->_children.erase(this);
    }
    for (TreeNode<T>* child : _children) {
      child->_parent = nullptr;
    }
  }
}