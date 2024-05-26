#include <iostream>
#include <memory>
#include <pybind11/embed.h>

namespace py = pybind11;
using namespace py::literals;

struct Pet {
  Pet(const std::string &name) : name(std::make_shared<std::string>(name)) {}
  void setName(const std::string &name_) { *name = name_; }
  const std::string &getName() const { return *name; }

  std::shared_ptr<std::string> name;
};

PYBIND11_EMBEDDED_MODULE(cpp_module, m) {
  m.doc() = "pybind11 example plugin"; // module docstring(optional)

  py::class_<Pet>(m, "Pet")
      .def(py::init<const std::string &>()) // コンストラクタ
      .def("setName", &Pet::setName)
      .def("getName", &Pet::getName);
}

int main() {
  py::scoped_interpreter guard{};

  // auto cpp_mod = py::module_::import("cpp_module");
  auto pet = Pet("Shiro");
  std::cout << pet.getName() << std::endl;
  auto py_module = py::module_::import("ex4_call_class_method");
  py_module.attr("set_name")(pet, "Taro");
  std::cout << pet.getName() << std::endl;
}
