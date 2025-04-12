#pragma once
#include "stage.hh"
#include "asset/asset_manager.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
  /// @ingroup PublicAPI
  /// @brief Root of the engine and where the game loop is.
  class App : public Scriptable {
  public:
    /// @brief Construct an App using an AppConfig.
    /// @param app_path Path to the AppConfig to use
    App(const stdf::path& app_path);
    /// @note Copying is not implemented
    App(const App&) = delete;
    /// @note Explict move because of explicit copy delete
    App(App&&) = default;
    /// @note Manually remove all attached Scripts
    ~App();
    /// @note Copying is not implemented
    App& operator=(const App&) = delete;
    /// @note Explict move because of explicit copy delete
    App& operator=(App&&) = default;

    /// @brief Run the game loop until the game ends.
    /// @param timeout Seconds until force ending the game loop and returning 
    void run(seconds timeout = 0);

    /// @brief Iterate over every Stage as Scriptable.
    /// @param func Callback function called for every child Scriptable
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    /// @brief Iterate over every Stage as Scriptable.
    /// @param func Callback function called for every child Scriptable
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;
  private:
    string _name;
    Stage* _main_stage = nullptr;
    AssetManager _asset_manager;
  };
}