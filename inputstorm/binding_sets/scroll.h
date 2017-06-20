#ifndef INPUTSTORM_BINDING_SETS_SCROLL_H_INCLUDED
#define INPUTSTORM_BINDING_SETS_SCROLL_H_INCLUDED

#include "base.h"
#include "inputstorm/input/scroll.h"
#ifndef NDEBUG
  #include <iostream>
#endif // NDEBUG

namespace inputstorm::binding_sets {

#define BINDING_SET_TYPE boost::bimap<boost::bimaps::unordered_multiset_of<T>, boost::bimaps::unordered_multiset_of<input::scroll::direction>>
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, scroll>

template<typename T>
class scroll : public BASE_TYPE {
  using controltype = T;

  input::scroll &parent_scroll;

public:
  scroll(binding_manager<controltype> &parent_binding_manager,
         input::scroll &this_parent_scroll);
  ~scroll();

  // bind and unbind controls to inputs
  virtual void unbind(std::string const &binding_name, controltype control) override final;
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type

  void bind(std::string const &binding_name,
            controltype control,
            input::scroll::direction direction);
  void bind(controltype control,
            input::scroll::direction direction);

  // update control-based bindings
  virtual void update_all(controltype control) override final;
};

template<typename T>
scroll<T>::scroll(binding_manager<controltype> &parent_binding_manager,
                  input::scroll &this_parent_scroll)
  : BASE_TYPE(parent_binding_manager),
    parent_scroll(this_parent_scroll) {
  /// Default constructor
}

template<typename T>
scroll<T>::~scroll() {
  /// Default destructor
}

//////////////////// bind and unbind controls to inputs ////////////////////////

template<typename T>
void scroll<T>::unbind(std::string const &binding_name,
                       controltype control) {
  /// Erase a control binding from an input scroll relationship
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Unbinding scroll for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto &binding_set(this->binding_sets[binding_name]);
  binding_set.left.erase(control);                                              // clear the current associations with that control
  update_all(control);                                                          // update all scroll functions, because they're not separable into components
}

template<typename T>
void scroll<T>::bind(std::string const &binding_name,
                     controltype control,
                     input::scroll::direction direction) {
  /// Apply a new control binding to an input scroll relationship
  #ifdef DEBUG_INPUTSTORM
    std::stringstream ss;
    ss << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
                                                << " in set " << binding_name
                                                << ", scroll direction " << static_cast<unsigned int>(direction)
                                                << " (" << parent_scroll.get_name(direction) << ")";
  #endif // DEBUG_INPUTSTORM
  auto &binding_set(this->binding_sets[binding_name]);
  binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, direction));
  update_all(control);                                                          // update all scroll functions, because they're not separable into components
}
template<typename T>
void scroll<T>::bind(controltype control,
                     input::scroll::direction direction) {
  /// Wrapper to work on the selected control set
  bind(this->binding_selected_name, control, direction);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void scroll<T>::update_all(controltype control) {
  /// Update scroll bindings for this control
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating all scroll bindings for control " << static_cast<unsigned int>(control) << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto const &binding_set(this->get_selected_binding_set());                    // scroll bindings are shared with keyboard bindings
  auto const &binding_range(binding_set.left.equal_range(control));
  if(binding_range.first != binding_range.second) {                             // skip empty ranges so we only perform this when called on the specified control
    // it doesn't matter which scroll binding is being set, we have to collect them all for a single function
    std::vector<controltype> conts_up;                                          // generate a vector of controls per direction
    std::vector<controltype> conts_down;
    std::vector<controltype> conts_left;
    std::vector<controltype> conts_right;
    for(auto const &this_direction : input::scroll::direction()) {
      auto const &control_range(binding_set.right.equal_range(this_direction)); // find all controls (and hence functions) that apply to this direction
      for(auto const &this_control : boost::make_iterator_range(control_range.first, control_range.second)) {
        switch(this_direction) {
        case input::scroll::direction::UP:
          conts_up.emplace_back(this_control.second);
          break;
        case input::scroll::direction::DOWN:
          conts_down.emplace_back(this_control.second);
          break;
        case input::scroll::direction::LEFT:
          conts_left.emplace_back(this_control.second);
          break;
        case input::scroll::direction::RIGHT:
          conts_right.emplace_back(this_control.second);
          break;
        case input::scroll::direction::END:
          #ifndef NDEBUG
            std::cout << "InputStorm: WARNING: requested control bind for the END marker of scroll direction, this shouldn't happen in release." << std::endl;
          #endif // NDEBUG
          break;
        }
      }
    }
    // sort and unique the controls
    std::sort(conts_up.begin(), conts_up.end());
    auto const &conts_up_new_end(std::unique(conts_up.begin(), conts_up.end())); // this should be faster to do once than to use a set to insert
    conts_up.resize(std::distance(conts_up.begin(), conts_up_new_end));
    std::sort(conts_down.begin(), conts_down.end());
    auto const &conts_down_new_end(std::unique(conts_down.begin(), conts_down.end()));
    conts_down.resize(std::distance(conts_down.begin(), conts_down_new_end));
    std::sort(conts_left.begin(), conts_left.end());
    auto const &conts_left_new_end(std::unique(conts_left.begin(), conts_left.end()));
    conts_left.resize(std::distance(conts_left.begin(), conts_left_new_end));
    std::sort(conts_right.begin(), conts_right.end());
    auto const &conts_right_new_end(std::unique(conts_right.begin(), conts_right.end()));
    conts_right.resize(std::distance(conts_right.begin(), conts_right_new_end));
    // build a library of functions for each direction
    std::vector<std::function<void()>> funcs_up;
    std::vector<std::function<void()>> funcs_down;
    std::vector<std::function<void()>> funcs_left;
    std::vector<std::function<void()>> funcs_right;
    for(auto const &this_control : conts_up) {
      auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
      if(this_func.press) {
        funcs_up.emplace_back(this_func.press);
      }
    }
    for(auto const &this_control : conts_down) {
      auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
      if(this_func.press) {
        funcs_down.emplace_back(this_func.press);
      }
    }
    for(auto const &this_control : conts_left) {
      auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
      if(this_func.press) {
        funcs_left.emplace_back(this_func.press);
      }
    }
    for(auto const &this_control : conts_right) {
      auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
      if(this_func.press) {
        funcs_right.emplace_back(this_func.press);
      }
    }
    #ifdef DEBUG_INPUTSTORM
      std::cout << "InputStorm: DEBUG: Combining " << funcs_up.size() << "U + "
                                                   << funcs_down.size() << "D + "
                                                   << funcs_left.size() << "L + "
                                                   << funcs_right.size() << "R + "
                                                   << " functions for scroll" << std::endl;
    #endif // DEBUG_INPUTSTORM
    parent_scroll.bind([funcs_up, funcs_down, funcs_left, funcs_right](vec2d const &offset_in){ // copy, don't reference, or these will go out of scope
      // create a special adapter function to activate the up, down, left and right scroll functions a specified number of times
      vec2d offset(offset_in);
      while(offset.y < -0.5) {
        for(auto const &it : funcs_down) {
          it();
        }
        ++offset.y;
      }
      while(offset.y > 0.5) {
        for(auto const &it : funcs_up) {
          it();
        }
        --offset.y;
      }
      while(offset.x < -0.5) {
        for(auto const &it : funcs_right) {
          it();
        }
        ++offset.x;
      }
      while(offset.x > 0.5) {
        for(auto const &it : funcs_left) {
          it();
        }
        --offset.x;
      }
    });
  }
}

#undef BINDING_SET_TYPE
#undef BASE_TYPE

}

#endif // INPUTSTORM_BINDING_SETS_SCROLL_H_INCLUDED
