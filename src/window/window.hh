#pragma once
#include "window_config.hh"
#include "window_event.hh"

#if defined(PARROT_GLFW)
#include "glfw/physical_window_glfw.hh"
namespace Parrot {
  using PhysicalWindow = GLFW::PhysicalWindow;
}
#endif

namespace Parrot {
  /// @ingroup PublicAPI
  /// @brief Graphics Window for displaying the game.
  class Window : public Scriptable {
  public:
    /// @brief Construct a Window based on a WindowConfig.
    /// @param config WindowConfig the Window is created from
    /// @param parent Parent Scriptable used for propagating events
    Window(const WindowConfig& config, Scriptable* parent = nullptr);
    /// @note Explict move because of explicit destructor 
    Window(Window&&) = default;
    /// @note Manually remove all attached Scripts
    ~Window();
    /// @note Explict move because of explicit destructor 
    Window& operator=(Window&&) = default;

    /// @brief Access the Window title.
    /// @return The title of the Window
    const string& getTitle();
    /// @brief Set the tray-icon of the Window.
    /// @param bytes The icon color buffer
    /// @param width The icon width
    /// @param height The icon height
    void setIcon(const uchar* bytes, uint width, uint height);

    /// @brief Is the Window still open.
    /// @return Whether the Window is open 
    bool isOpen() const;
    /// @brief Close the Window.
    void close();

    /// @param state 
    void setCursorState(CursorState state);
    /// @brief Get the relative (to the top left of the Window) cursor position.
    /// @return The coordinates in pixels
    Vec2<> getCursorCoords() const;

    /// @brief Bind the Window as a target for rendering commands.
    void bind();
    /// @brief Bind no Window as a target for rendering commands.
    void unbind();

    /// @brief Poll all Events targeting the Window since last poll.
    /// @return A list of all WindowEvents in order
    List<WindowEvent> pollEvents();
    /// @brief Swap the Window and Display buffer for displaying.
    void swapBuffers();

    /// @brief Do nothing.
    /// @param func Callback function called for every child Scriptable
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    /// @brief Do nothing.
    /// @param func Callback function called for every child Scriptable
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;
  private:
    string _title;
    uint _width = 0, _height = 0;
    CursorState _cursor = CursorState::NORMAL;
    PhysicalWindow _physical;
  };
}