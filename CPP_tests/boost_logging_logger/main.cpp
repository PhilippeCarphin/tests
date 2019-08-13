

// TUTORIAL https://www.boost.org/doc/libs/1_63_0/libs/log/doc/html/log/tutorial/sources.html

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

/*
 * The above macro expands to this :
 *
 * struct my_logger {
 *     typedef src::logger_mt logger_type;
 *     enum registration_line_t { registration_line = 11 };
 *     static const char* registration_file() {
 *         return "/tmp/tests/CPP_tests/boost_logging_logger/main.cpp";
 *     }
 *     static logger_type construct_logger();
 *     static inline logger_type& get() {
 *         return ::boost::log::sources::aux::logger_singleton< my_logger >::get();
 *     }
 * };
 *
 * inline my_logger::logger_type my_logger::construct_logger(){
 *     return logger_type();
 * }
 */
int main(int, char*[])
{
    src::logger_mt& my_logger_instance = my_logger::get();

    /*
     * logging::record rec = my_logger_instance.open_record();
     * if(rec)
     * {
     *     logging::record_ostream my_record_ostream{rec};
     *     my_record_ostream << "Hello World by hand";
     *     my_record_ostream.flush();
     *     my_logger_instance.push_record(boost::move(rec));
     * }
     */

    BOOST_LOG(my_logger_instance) << "Hello World";
    BOOST_LOG(my_logger::get()) << "Hello World";

    BOOST_LOG_SEV(my_logger_instance, boost::log::trivial::info) << "What's up";
    BOOST_LOG_SEV(my_logger::get(), boost::log::trivial::info) << "What's up different";

    return 0;
}
