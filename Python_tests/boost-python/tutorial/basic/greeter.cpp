#include <string>
#include <boost/python.hpp>


struct Greeter
{
  void set_greeting(std::string greeting){
    this->greeting = greeting;
  }
  std::string greet(){return this->greeting;}
  std::string greeting;
};


using namespace boost::python;

BOOST_PYTHON_MODULE(greet)
{
  class_<Greeter>("Greeter")
    .def("set_greeting", &Greeter::set_greeting)
    .def("greet", &Greeter::greet)
    ;
}
