#include <boost/python.hpp>

#include "TrivialEngine.h"

using namespace Trivial;

BOOST_PYTHON_MODULE(trivial)
{
    using namespace boost::python;
    def("app_instance", App::Instance, return_value_policy<manage_new_object>());
    
    class_<App, boost::noncopyable>("App", no_init)
        .def("configure", &App::configure)
        .def("run", &App::run)
    ;
}
