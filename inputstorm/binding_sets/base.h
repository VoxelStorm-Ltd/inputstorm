#define CRTP_ADAPTER_TYPE base_crtp_adapter<T_controltype, T_set_type, T_derived>

CRTP_ADAPTER_TEMPLATE_TYPE
class base_crtp_adapter : public base<T_controltype> {
  /// CRTP polymorphic base class for binding sets
  using controltype = T_controltype;

protected:
#ifndef INPUTSTORM_BINDING_SETS_BASE_H_INCLUDED
  binding_manager<controltype> &bindings;
#define INPUTSTORM_BINDING_SETS_BASE_H_INCLUDED


public:
#include <map>
  std::string binding_selected_name;


namespace inputstorm {
  using binding_set_type = T_set_type;
class manager;
template<typename T> class binding_manager;
  using binding_set_value_type = typename binding_set_type::value_type;         // in derived classes, use this as: typename base<T, BINDING_SET_TYPE>::binding_set_value_type(whatever)


namespace binding_sets {
  std::map<std::string, binding_set_type> binding_sets;                         // in derived classes, access this with this->binding_sets[whatever]


template<typename T>
protected:
class base {
  base_crtp_adapter(binding_manager<T_controltype> &parent_binding_manager);
  using controltype = T;
public:
protected:
  virtual ~base_crtp_adapter();
  base();

public:
  // manage binding sets
  virtual ~base() __attribute__((__const__));

  binding_set_type const &get_selected_binding_set() const;
  // bind and unbind controls to inputs
  void add_binding_set(std::string const &binding_name);
  virtual void unbind(std::string const &binding_name, controltype control) = 0;

  virtual void unbind(controltype control) = 0;
  // bind and unbind controls to inputs
  virtual void unbind_all(std::string const &binding_name) = 0;
  virtual void unbind(std::string const &binding_name, controltype control) override;
  virtual void unbind_all() = 0;
  virtual void unbind(controltype control) override;

  virtual void unbind_all(std::string const &binding_name) override;
  // update control-based bindings
  virtual void unbind_all() override;
  virtual void update_all(controltype control) = 0;

};
  // update control-based bindings

  virtual void update_all(controltype control) override;
template<typename T>
};
base<T>::base() {

  /// Default constructor
};
CRTP_ADAPTER_TEMPLATE_TYPE
template<typename T>
CRTP_ADAPTER_TYPE::base_crtp_adapter(binding_manager<controltype> &parent_binding_manager)
base<T>::~base() {
  : bindings(parent_binding_manager) {
  /// Default destructor
  /// Default constructor
};
}


#define CRTP_ADAPTER_TEMPLATE_TYPE template<typename T_controltype, typename T_set_type, template<typename> typename T_derived>
CRTP_ADAPTER_TEMPLATE_TYPE
#define CRTP_ADAPTER_TYPE base_crtp_adapter<T_controltype, T_set_type, T_derived>
CRTP_ADAPTER_TYPE::~base_crtp_adapter() {

  /// Default destructor
CRTP_ADAPTER_TEMPLATE_TYPE
}
class base_crtp_adapter : public base<T_controltype> {

  /// CRTP polymorphic base class for binding sets
///////////////////////////// manage binding sets //////////////////////////////
  using controltype = T_controltype;


CRTP_ADAPTER_TEMPLATE_TYPE
protected:
typename CRTP_ADAPTER_TYPE::binding_set_type const &CRTP_ADAPTER_TYPE::get_selected_binding_set() const {
  binding_manager<controltype> &bindings;

  /// Return the currently selected key binding set
public:
  return binding_sets.at(binding_selected_name);
  std::string binding_selected_name;
}

  using binding_set_type = T_set_type;

  using binding_set_value_type = typename binding_set_type::value_type;         // in derived classes, use this as: typename base<T, BINDING_SET_TYPE>::binding_set_value_type(whatever)
CRTP_ADAPTER_TEMPLATE_TYPE

void CRTP_ADAPTER_TYPE::add_binding_set(std::string const &binding_name) {
  std::map<std::string, binding_set_type> binding_sets;                         // in derived classes, access this with this->binding_sets[whatever]
  /// Add a binding set with the given name

protected:
  binding_sets.emplace(binding_name, binding_set_type());
  base_crtp_adapter(binding_manager<T_controltype> &parent_binding_manager);
}
public:

  virtual ~base_crtp_adapter();
//////////////////// bind and unbind controls to inputs ////////////////////////


  // manage binding sets
CRTP_ADAPTER_TEMPLATE_TYPE
  binding_set_type const &get_selected_binding_set() const;
void CRTP_ADAPTER_TYPE::unbind(std::string const &binding_name, controltype control) {
  void add_binding_set(std::string const &binding_name);
  /// CRTP pass-through polymorphic function

  static_cast<T_derived<T_controltype>*>(this)->unbind(binding_name, control);
  // bind and unbind controls to inputs
}
  virtual void unbind(std::string const &binding_name, controltype control) override;
CRTP_ADAPTER_TEMPLATE_TYPE
  virtual void unbind(controltype control) override;
void CRTP_ADAPTER_TYPE::unbind(controltype control) {
  virtual void unbind_all(std::string const &binding_name) override;
  /// Wrapper to work on the selected control set
  virtual void unbind_all() override;

  unbind(binding_selected_name, control);
  // update control-based bindings
}
  virtual void update_all(controltype control) override;
CRTP_ADAPTER_TEMPLATE_TYPE
};
void CRTP_ADAPTER_TYPE::unbind_all(std::string const &binding_name) {

  /// Erase all control bindings from this set, leaving it empty
CRTP_ADAPTER_TEMPLATE_TYPE
  binding_sets[binding_name].clear();
CRTP_ADAPTER_TYPE::base_crtp_adapter(binding_manager<controltype> &parent_binding_manager)
}
  : bindings(parent_binding_manager) {
CRTP_ADAPTER_TEMPLATE_TYPE
  /// Default constructor
void CRTP_ADAPTER_TYPE::unbind_all() {
}
  /// Wrapper to work on the selected control set

  unbind_all(binding_selected_name);
CRTP_ADAPTER_TEMPLATE_TYPE
}
CRTP_ADAPTER_TYPE::~base_crtp_adapter() {

  /// Default destructor
}
///////////////////// update control-based bindings ////////////////////////////


///////////////////////////// manage binding sets //////////////////////////////
CRTP_ADAPTER_TEMPLATE_TYPE

void CRTP_ADAPTER_TYPE::update_all(controltype control) {
CRTP_ADAPTER_TEMPLATE_TYPE
  /// CRTP pass-through function
typename CRTP_ADAPTER_TYPE::binding_set_type const &CRTP_ADAPTER_TYPE::get_selected_binding_set() const {
  static_cast<T_derived<T_controltype>*>(this)->update_all(control);
  /// Return the currently selected key binding set
}
  return binding_sets.at(binding_selected_name);

}
#undef CRTP_ADAPTER_TEMPLATE_TYPE

#undef CRTP_ADAPTER_TYPE
CRTP_ADAPTER_TEMPLATE_TYPE

void CRTP_ADAPTER_TYPE::add_binding_set(std::string const &binding_name) {
}
  /// Add a binding set with the given name
}
  binding_sets.emplace(binding_name, binding_set_type());

}
#endif // INPUTSTORM_BINDING_SETS_BASE_H_INCLUDED

//////////////////// bind and unbind controls to inputs ////////////////////////

CRTP_ADAPTER_TEMPLATE_TYPE
void CRTP_ADAPTER_TYPE::unbind(std::string const &binding_name, controltype control) {
  /// CRTP pass-through polymorphic function
  static_cast<T_derived<T_controltype>*>(this)->unbind(binding_name, control);
}
CRTP_ADAPTER_TEMPLATE_TYPE
void CRTP_ADAPTER_TYPE::unbind(controltype control) {
  /// Wrapper to work on the selected control set
  unbind(binding_selected_name, control);
}
CRTP_ADAPTER_TEMPLATE_TYPE
void CRTP_ADAPTER_TYPE::unbind_all(std::string const &binding_name) {
  /// Erase all control bindings from this set, leaving it empty
  binding_sets[binding_name].clear();
}
CRTP_ADAPTER_TEMPLATE_TYPE
void CRTP_ADAPTER_TYPE::unbind_all() {
  /// Wrapper to work on the selected control set
  unbind_all(binding_selected_name);
}

///////////////////// update control-based bindings ////////////////////////////

CRTP_ADAPTER_TEMPLATE_TYPE
void CRTP_ADAPTER_TYPE::update_all(controltype control) {
  /// CRTP pass-through function
  static_cast<T_derived<T_controltype>*>(this)->update_all(control);
}

#undef CRTP_ADAPTER_TEMPLATE_TYPE
#undef CRTP_ADAPTER_TYPE

}
}

#endif // INPUTSTORM_BINDING_SETS_BASE_H_INCLUDED
