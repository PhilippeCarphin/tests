
namespace clibmingstats {

    std::string get_stats(){
        RawStats rs = raw_stats::get_raw_stats();
        std::ostringstream os;

        os << "Stats : average " << rs.average << std::endl
           << "        median  " << rs.median << std::endl;

        return os.string();
    }
}
