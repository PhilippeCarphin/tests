

// TUTORIAL https://www.boost.org/doc/libs/1_63_0/libs/log/doc/html/log/tutorial/sources.html

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger_struct, src::logger_mt)

int main(int, char*[])
{
    src::logger_mt& my_logger_instance = my_logger_struct::get();

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

    return 0;
}
