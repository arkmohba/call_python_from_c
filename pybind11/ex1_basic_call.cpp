#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) { return i + j; }

struct Pet {
  Pet(const std::string &name) : name(name) {}
  void setName(const std::string &name_) { name = name_; }
  const std::string &getName() const { return name; }

  std::string name;
};


PYBIND11_MODULE(example, m) {
  m.doc() = "pybind11 example plugin"; // module docstring(optional)
  m.def("add", &add, "A function that adds two numbers");
  
  py::class_<Pet>(m, "Pet")
    .def(py::init<const std::string &>())  // コンストラクタ
    .def("setName", &Pet::setName)
    .def("getName", &Pet::getName);
}
