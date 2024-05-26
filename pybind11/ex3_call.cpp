#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;
using namespace py::literals;

PYBIND11_EMBEDDED_MODULE(cpp_module, m) { m.attr("a") = 1; }

int main() {
  py::scoped_interpreter guard{};

  auto py_module = py::module_::import("ex3_call");

  pybind11::dict locals =
      py::dict("fmt"_a = "{} + {} = {}", **py_module.attr("__dict__"));
  assert(locals["a"].cast<int>() == 1);
  assert(locals["b"].cast<int>() == 2);

  py::exec(R"(
        c = a + b
        message = fmt.format(a, b, c)
    )",
           py::globals(), locals);

  assert(locals["c"].cast<int>() == 3);
  assert(locals["message"].cast<std::string>() == "1 + 2 = 3");

  std::cout << locals["c"].cast<int>() << std::endl
            << locals["message"].cast<std::string>() << std::endl;
}
