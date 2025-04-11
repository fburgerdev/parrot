#pragma once
#include "scene_config.hh"
#include "entity.hh"

namespace Parrot {
  class Scene;
  class Renderer;
  /// @brief Define a custom render pipeline for your Scene.
  using RenderFunc = Func<void(Renderer&, Scene&)>;

  /// @ingroup PublicAPI
  /// @brief Game world containing Entities in a hierarchy.
  class Scene : public Scriptable {
  public:
    /// @brief Construct a Scene based on a SceneConfig.
    /// @param config SceneConfig the Scene is created from
    /// @param parent Parent Scriptable used for propagating events
    /// @param asset_api For usage by the client in attached SceneScripts 
    Scene(const SceneConfig& config, Scriptable* parent, AssetAPI& asset_api);
    /// @note Explict move because of explicit destructor 
    Scene(Scene&&) = default;
    /// @note Manually remove all attached Scripts
    ~Scene();
    /// @note Explict move because of explicit destructor 
    Scene& operator=(Scene&&) = default;

    /// @brief Update all Entities, Components and Scripts in the Scene.
    /// @param delta_time Seconds elapsed since last update
    void update(float32 delta_time);

    /// @brief Get all Entities in the Scene holding a certain Component type.
    /// @tparam T Component type
    /// @return Pointers to the Entities holding a Component of type @c T
    template<class T>
    List<Entity*> queryEntities();
    /// @brief Get all Entities in the Scene holding a certain Component type.
    /// @tparam T Component type
    /// @return Pointers to the Entities holding a Component of type @c T
    template<class T>
    List<const Entity*> queryEntities() const;

    /// @brief Iterate overy only one Scriptable, @c root.
    /// @param func Callback function called for with @c root
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    /// @brief Iterate overy only one Scriptable, @c root.
    /// @param func Callback function called for with @c root
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    /// @brief Name of the Scene.
    string name;
    /// @brief Root Entity of the Scene where all Entities stem from.
    Entity root;
    /// @brief Optionally specify the render pipeline for the Scene.
    Opt<RenderFunc> render = std::nullopt;
  };
}
#include "scene_impl.hh"