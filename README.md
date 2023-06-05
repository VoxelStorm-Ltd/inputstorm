# InputStorm
C++ callback-based unified input handling library working with GLFW, by [VoxelStorm](https://github.com/VoxelStorm-Ltd).

Includes support for keyboard, mouse, joystick / gamepad, and VR controllers.

Used in the game [sphereFACE](https://sphereface.com).  Provided without support, and with limited documentation, in the hope it will be useful to someone.

## Dependencies
- [VectorStorm](https://github.com/Armchair-Software/vectorstorm) vector maths library by VoxelStorm / Armchair Software
- GLFW
- GLEW (probably a false dependency that can be removed)
- Boost:
  - `<boost/bimap.hpp>`
  - `<boost/bimap/unordered_multiset_of.hpp>`
  - `<boost/range/iterator_range.hpp>`

### Input classes:
```cpp
namespace input {
class key;
class cursor;
class mousebutton;
class scroll;
class joystick;
class text;
}
```

### Example usage
This example demonstrates the default control setup used in the game [sphereFACE](https://sphereface.com).
```cpp
  inputstorm::manager input;
  inputstorm::binding_manager<controltype> bindings;                            // input binding manager

  enum class controltype {
    MENU,
    FIRST = MENU,
    MENU_SELECT,
    PAUSE,
    FULLSCREEN,
    CAMERA_LEFT,
    CAMERA_RIGHT,
    CAMERA_UP,
    CAMERA_DOWN,
    CAMERA_SNAP,
    CAMERA_SNAP_ENABLE,
    CAMERA_SNAP_DISABLE,
    PLAYER_SHIP_ACCELERATE,
    PLAYER_SHIP_DECELERATE,
    PLAYER_SHIP_ROTATE_LEFT,
    PLAYER_SHIP_ROTATE_RIGHT,
    PLAYER_SHIP_FIRE,
    PLAYER_SHIP_SECONDARY_FIRE,
    PLAYER_SHIP_SELECT_WEAPON_NEXT,
    PLAYER_SHIP_SELECT_WEAPON_PREV,
    PLAYER_SHIP_SELECT_WEAPON_0,
    PLAYER_SHIP_SELECT_WEAPON_1,
    PLAYER_SHIP_SELECT_WEAPON_2,
    PLAYER_SHIP_SELECT_WEAPON_3,
    PLAYER_SHIP_SELECT_WEAPON_4,
    PLAYER_SHIP_SELECT_WEAPON_5,
    PLAYER_SHIP_SELECT_WEAPON_6,
    PLAYER_SHIP_SELECT_WEAPON_7,
    PLAYER_SHIP_SELECT_WEAPON_8,
    PLAYER_SHIP_SELECT_WEAPON_9,
    PLAYER_SHIP_DESTROY,
    END,                                                                        // special end marker
    LAST = END - 1                                                              // special last element marker
  };

  std::shared_ptr<inputstorm::binding_sets::key<            controltype>> key;
  std::shared_ptr<inputstorm::binding_sets::mousebutton<    controltype>> mousebutton;
  std::shared_ptr<inputstorm::binding_sets::scroll<         controltype>> scroll;
  std::shared_ptr<inputstorm::binding_sets::joystick_button<controltype>> joystick_button;
  std::shared_ptr<inputstorm::binding_sets::joystick_axis<  controltype>> joystick_axis;
  std::shared_ptr<vrstorm::binding_sets::controller_button< controltype>> vr_controller_button;
  std::shared_ptr<vrstorm::binding_sets::controller_axis<   controltype>> vr_controller_axis;

  std::string const key_binding_default_name{                 "DEFAULT"};
  std::string const mousebutton_binding_default_name{         "DEFAULT"};
  std::string const scroll_binding_default_name{              "DEFAULT"};
  std::string const joystick_binding_default_name_xbox{       "DEFAULT XBOX"};
  std::string const joystick_binding_default_name_playstation{"DEFAULT PLAYSTATION"};
  std::string const vr_controller_binding_default_name{       "DEFAULT"};

  key.reset(                 new inputstorm::binding_sets::key<            controltype>(bindings, input.key));
  mousebutton.reset(         new inputstorm::binding_sets::mousebutton<    controltype>(bindings, input.mousebutton));
  scroll.reset(              new inputstorm::binding_sets::scroll<         controltype>(bindings, input.scroll));
  joystick_button.reset(     new inputstorm::binding_sets::joystick_button<controltype>(bindings, input.joystick));
  joystick_axis.reset(       new inputstorm::binding_sets::joystick_axis<  controltype>(bindings, input.joystick));
  vr_controller_button.reset(new vrstorm::binding_sets::controller_button< controltype>(bindings, vr.input_controller));
  vr_controller_axis.reset(  new vrstorm::binding_sets::controller_axis<   controltype>(bindings, vr.input_controller));

  bindings.binding_sets_digital.emplace_back(key);
  bindings.binding_sets_digital.emplace_back(mousebutton);
  bindings.binding_sets_digital.emplace_back(scroll);
  bindings.binding_sets_digital.emplace_back(joystick_button);
  bindings.binding_sets_analogue.emplace_back(joystick_axis);
  bindings.binding_sets_digital.emplace_back(vr_controller_button);
  bindings.binding_sets_analogue.emplace_back(vr_controller_axis);

  key->binding_selected_name                  = key_binding_default_name;
  mousebutton->binding_selected_name          = key_binding_default_name;
  scroll->binding_selected_name               = key_binding_default_name;
  joystick_button->binding_selected_name      = joystick_binding_default_name;
  joystick_axis->binding_selected_name        = joystick_binding_default_name;
  vr_controller_button->binding_selected_name = vr_controller_binding_default_name;
  vr_controller_axis->binding_selected_name   = vr_controller_binding_default_name;

  key->add_binding_set(                 key_binding_default_name);
  mousebutton->add_binding_set(         key_binding_default_name);
  scroll->add_binding_set(              key_binding_default_name);
  joystick_button->add_binding_set(     joystick_binding_default_name_xbox);
  joystick_button->add_binding_set(     joystick_binding_default_name_playstation);
  joystick_axis->add_binding_set(       joystick_binding_default_name_xbox);
  joystick_axis->add_binding_set(       joystick_binding_default_name_playstation);
  vr_controller_button->add_binding_set(vr_controller_binding_default_name);
  vr_controller_axis->add_binding_set(  vr_controller_binding_default_name);

  // set up the general control bindings
  key->unbind_all(key_binding_default_name);                                    // clear it in case it was loaded from a settings file
  //key->bind(key_binding_default_name, controltype::SKIP_TRANSITION,                    GLFW_KEY_UNKNOWN);
  key->bind(key_binding_default_name, controltype::MENU,                               GLFW_KEY_ESCAPE);
  key->bind(key_binding_default_name, controltype::MENU_SELECT,                        GLFW_KEY_ENTER);
  key->bind(key_binding_default_name, controltype::PAUSE,                              GLFW_KEY_PAUSE);
  key->bind(key_binding_default_name, controltype::FULLSCREEN,                         GLFW_KEY_F11);
  // remainder of the general controls outside of the high score menu
  key->bind(key_binding_default_name, controltype::CAMERA_LEFT,                        GLFW_KEY_Q);
  key->bind(key_binding_default_name, controltype::CAMERA_RIGHT,                       GLFW_KEY_E);
  key->bind(key_binding_default_name, controltype::CAMERA_SNAP,                        GLFW_KEY_X);
  //key->bind(key_binding_default_name, controltype::CAMERA_SNAP_ENABLE,                GLFW_KEY_X);
  //key->bind(key_binding_default_name, controltype::CAMERA_SNAP_DISABLE,               GLFW_KEY_X);
  // set up the ship controls
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_ACCELERATE,             GLFW_KEY_W);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_ACCELERATE,             GLFW_KEY_UP);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_DECELERATE,             GLFW_KEY_S);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_DECELERATE,             GLFW_KEY_DOWN);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_ROTATE_LEFT,            GLFW_KEY_A);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_ROTATE_LEFT,            GLFW_KEY_LEFT);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_ROTATE_RIGHT,           GLFW_KEY_D);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_ROTATE_RIGHT,           GLFW_KEY_RIGHT);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_FIRE,                   GLFW_KEY_SPACE);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_FIRE,                   GLFW_KEY_RIGHT_CONTROL);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SECONDARY_FIRE,         GLFW_KEY_LEFT_CONTROL);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_NEXT,     GLFW_KEY_TAB);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_NEXT,     GLFW_KEY_EQUAL);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_PREV,     GLFW_KEY_TAB, inputstorm::input::key::modtype::SHIFT);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_PREV,     GLFW_KEY_MINUS);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_0,        GLFW_KEY_1);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_1,        GLFW_KEY_2);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_2,        GLFW_KEY_3);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_3,        GLFW_KEY_4);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_4,        GLFW_KEY_5);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_5,        GLFW_KEY_6);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_6,        GLFW_KEY_7);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_7,        GLFW_KEY_8);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_8,        GLFW_KEY_9);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_9,        GLFW_KEY_0);
  key->bind(key_binding_default_name, controltype::PLAYER_SHIP_DESTROY,                GLFW_KEY_BACKSPACE);

  // mouse
  mousebutton->unbind_all(key_binding_default_name);                            // clear it in case it was loaded from a settings file
  mousebutton->bind(key_binding_default_name, controltype::PLAYER_SHIP_FIRE,           GLFW_MOUSE_BUTTON_1);
  mousebutton->bind(key_binding_default_name, controltype::PLAYER_SHIP_SECONDARY_FIRE, GLFW_MOUSE_BUTTON_2);
  mousebutton->bind(key_binding_default_name, controltype::CAMERA_SNAP,                GLFW_MOUSE_BUTTON_3);

  // scroll
  scroll->unbind_all(key_binding_default_name);                                 // clear it in case it was loaded from a settings file
  scroll->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_NEXT, inputstorm::input::scroll::direction::UP);
  scroll->bind(key_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_PREV, inputstorm::input::scroll::direction::DOWN);

  // controller: xbox
  float constexpr const deadzone = 0.2f;
  joystick_axis->unbind_all(joystick_binding_default_name_xbox);                // clear it in case it was loaded from a settings file
  joystick_button->unbind_all(joystick_binding_default_name_xbox);              // clear it in case it was loaded from a settings file

  // controller: xbox axes
  joystick_axis->bind(joystick_binding_default_name_xbox, controltype::PLAYER_SHIP_ROTATE_RIGHT,   selected_joystick_id, 0, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_xbox, controltype::PLAYER_SHIP_ACCELERATE,     selected_joystick_id, 1, true,  -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_xbox, controltype::PLAYER_SHIP_SECONDARY_FIRE, selected_joystick_id, 2, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_xbox, controltype::CAMERA_RIGHT,               selected_joystick_id, 3, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_xbox, controltype::CAMERA_UP,                  selected_joystick_id, 4, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_xbox, controltype::PLAYER_SHIP_FIRE,           selected_joystick_id, 5, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);

  // controller: xbox buttons
  joystick_button->bind(joystick_binding_default_name_xbox, controltype::MENU_SELECT,                    selected_joystick_id, 0); // A
  joystick_button->bind(joystick_binding_default_name_xbox, controltype::PLAYER_SHIP_SELECT_WEAPON_PREV, selected_joystick_id, 4); // left shoulder
  joystick_button->bind(joystick_binding_default_name_xbox, controltype::PLAYER_SHIP_SELECT_WEAPON_NEXT, selected_joystick_id, 5); // right shoulder
  joystick_button->bind(joystick_binding_default_name_xbox, controltype::PAUSE,                          selected_joystick_id, 6); // back (xbox)
  joystick_button->bind(joystick_binding_default_name_xbox, controltype::MENU,                           selected_joystick_id, 7); // start (xbox)
  joystick_button->bind(joystick_binding_default_name_xbox, controltype::PLAYER_SHIP_DECELERATE,         selected_joystick_id, 9); // left stick in
  joystick_button->bind(joystick_binding_default_name_xbox, controltype::CAMERA_SNAP,                    selected_joystick_id, 10); // right stick in

  // controller: playstation axes
  joystick_axis->unbind_all(joystick_binding_default_name_playstation);       // clear it in case it was loaded from a settings file
  joystick_axis->bind(joystick_binding_default_name_playstation, controltype::PLAYER_SHIP_ROTATE_RIGHT,   selected_joystick_id, 0, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_playstation, controltype::PLAYER_SHIP_ACCELERATE,     selected_joystick_id, 1, true,  -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_playstation, controltype::CAMERA_RIGHT,               selected_joystick_id, 2, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_playstation, controltype::CAMERA_UP,                  selected_joystick_id, 3, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_playstation, controltype::PLAYER_SHIP_FIRE,           selected_joystick_id, 4, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);
  joystick_axis->bind(joystick_binding_default_name_playstation, controltype::PLAYER_SHIP_SECONDARY_FIRE, selected_joystick_id, 5, false, -deadzone, deadzone, -1.0f, 1.0f, 0.0f);

  // controller: playstation buttons:
  joystick_button->unbind_all(joystick_binding_default_name_playstation);     // clear it in case it was loaded from a settings file
  joystick_button->bind(joystick_binding_default_name_playstation, controltype::MENU_SELECT,                    selected_joystick_id, 0); // X (cross)
  joystick_button->bind(joystick_binding_default_name_playstation, controltype::PLAYER_SHIP_SELECT_WEAPON_PREV, selected_joystick_id, 4); // left shoulder
  joystick_button->bind(joystick_binding_default_name_playstation, controltype::PLAYER_SHIP_SELECT_WEAPON_NEXT, selected_joystick_id, 5); // right shoulder
  joystick_button->bind(joystick_binding_default_name_playstation, controltype::PAUSE,                          selected_joystick_id, 6); // select (playstation)
  joystick_button->bind(joystick_binding_default_name_playstation, controltype::MENU,                           selected_joystick_id, 7); // start (playstation)
  joystick_button->bind(joystick_binding_default_name_playstation, controltype::PLAYER_SHIP_DECELERATE,         selected_joystick_id, 9); // left stick in
  joystick_button->bind(joystick_binding_default_name_playstation, controltype::CAMERA_SNAP,                    selected_joystick_id, 10); // right stick in

  // VR controller axes:
  using vc = vrstorm::input::controller;
  float constexpr const vr_deadzone = 0.0f;
  float constexpr const vr_saturation = 0.85f;
  vr_controller_axis->unbind_all(vr_controller_binding_default_name);           // clear it in case it was loaded from a settings file
  vr_controller_axis->bind(vr_controller_binding_default_name, controltype::CAMERA_RIGHT,             vc::hand_type::RIGHT, 0, vc::axis_direction_type::X, false, -vr_deadzone, vr_deadzone, -vr_saturation, vr_saturation, 0.0f); // trackpad
  vr_controller_axis->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_ACCELERATE,   vc::hand_type::LEFT,  0, vc::axis_direction_type::Y, false, -vr_deadzone, vr_deadzone, -vr_saturation, vr_saturation, 0.0f); // trackpad
  vr_controller_axis->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_ROTATE_RIGHT, vc::hand_type::LEFT,  0, vc::axis_direction_type::X, false, -vr_deadzone, vr_deadzone, -vr_saturation, vr_saturation, 0.0f); // trackpad
  //vr_controller_axis->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_ACCELERATE,   vc::hand_type::LEFT,  1, vc::axis_direction_type::X, false, -vr_deadzone, vr_deadzone, -vr_saturation, vr_saturation, 0.0f); // trigger

  // VR controller buttons:
  vr_controller_button->unbind_all(vr_controller_binding_default_name);         // clear it in case it was loaded from a settings file
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::MENU,                           vc::hand_type::RIGHT, 1); // menu
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::MENU,                           vc::hand_type::LEFT,  1); // menu
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_FIRE,               vc::hand_type::RIGHT, 33); // trigger
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_FIRE,               vc::hand_type::LEFT,  33); // trigger
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_SECONDARY_FIRE,     vc::hand_type::RIGHT, 32); // touchpad
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_SECONDARY_FIRE,     vc::hand_type::LEFT,  32); // touchpad
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_NEXT, vc::hand_type::RIGHT, 2); // grip
  vr_controller_button->bind(vr_controller_binding_default_name, controltype::PLAYER_SHIP_SELECT_WEAPON_PREV, vc::hand_type::LEFT,  2); // grip

```

### Special usage
```cpp
inputstorm::manager input;
input.joystick.draw_binding_graphs();
```

#### Binding for text input (high score screen example)
```cpp
    input.text.bind([](char32_t c){
      // user has entered the text character c
      //...
    });
    
    input.key.reset();  // disable any keyboard controls that may be bound to other actions, to avoid them interfering with typing
    input.key.bind(GLFW_KEY_UP,        inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, letter_increment);
    input.key.bind(GLFW_KEY_DOWN,      inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, letter_decrement);
    input.key.bind(GLFW_KEY_RIGHT,     inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, letter_advance);
    input.key.bind(GLFW_KEY_SPACE,     inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, letter_advance);
    input.key.bind(GLFW_KEY_LEFT,      inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, letter_backspace);
    input.key.bind(GLFW_KEY_BACKSPACE, inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, letter_backspace);
    input.key.bind(GLFW_KEY_ESCAPE,    inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, [this]{
      // return to main menu
      // ...
    });
    input.key.bind(GLFW_KEY_ENTER,     inputstorm::input::key::actiontype::PRESS, inputstorm::input::key::modtype::NONE, [this]{
      // submit high score
      // ...
    });
```


Full documentation TODO, pull requests welcome.
