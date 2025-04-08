#pragma once
#include "utils/uuid.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  /// @brief Location of an asset using its filepath and subpath
  struct AssetPath {
    /// @brief Construct empty AssetPath
    AssetPath() = default;
    /// @brief Construct AssetPath locating a file
    AssetPath(const stdf::path& file);
    /// @brief Construct AssetPath locating a subsection of a file
    AssetPath(const stdf::path& file, strview sub);
    /// @brief Construct AssetPath locating a subsection of a file
    AssetPath(strview path);

    /// @brief Split the subpath into tokens
    List<string> splitSubpath() const;
    /// @brief Apply subpath to a SerialNode
    SerialNode applySubpathToNode(const SerialNode& root) const;
    /// @brief Compare two AssetPaths
    auto operator<=>(const AssetPath& other) const = default;
    /// @brief Stream AssetPath
    friend ostream& operator<<(ostream& stream, const AssetPath& asset_path);

    /// @brief Filepath to located file
    stdf::path file;
    /// @brief Subpath in the located file
    string sub;
    /// @brief Optional root path (used e.g. for nicer stream output)
    Opt<stdf::path> debug_root; // for debugging
  };
  /// @brief Key to uniquely identify an asset (using an UUID or an AssetPath)
  using AssetKey = Variant<UUID, AssetPath>;
}