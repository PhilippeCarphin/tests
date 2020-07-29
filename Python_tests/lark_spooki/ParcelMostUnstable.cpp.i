// Macro expansion of OPTIONS_COLLECTION
((iceWaterPhase, "", ICEWATERPHASE_ENUM_t, 1, 0, "", "Switch to determine which phase to consider: ice and water, or, water only.\n  " "Supported types:[ STRING" "["  "WATER" "|" "BOTH"   "]" " ]\n  " "Ex: --iceWaterPhase BOTH\n"))
((delta,"", string, 0, 1, "300hPa", "Depth in pressure coordinates above the surface where to search for the most unstable parcel.  \n  " "Default: 300hPa\n" "Supported types:[ FLOAT[>0.0 to +infinity] +  STRING" "[mb|Pa|hPa|kPa]" " ]\n  " "Ex: --delta 500hPa"))
((temperaturePhaseSwitch, "", string, 0, 0, "", "Temperature at which to change from the ice phase to the water phase.\n  " "Mandatory if '--iceWaterPhase BOTH' is used. \n  " "Supported types [ FLOAT[-273.15 to 273.16] + STRING [C|K] ]\n  " "Ex: --temperaturePhaseSwitch -40C or --temperaturePhaseSwitch 268.15K\n"))
((increment, "", string, 0, 1, "1hPa", "Specify pressure increment between levels for the iterative calculation.\n  " "Supported types: [FLOAT [>0.0 to +infinity] + STRING [mb|Pa|hPa|kPa]]\n  " "Default: 1.0hPa\n  " "Ex: --increment 5.0mb\n"))

// Macro expansion of 
//    BEGIN_ADD_BASIC_OPTIONS(HighLevelOperation)
//        OPTIONS(OPTIONS_COLLECTION);
//        HIDDEN_OPTIONS(HIDDEN_OPTIONS_COLLECTION);
//    END
    void addBasicOptions() {
          for (::boost::log::record _boost_log_record_1131 = ((pst::spooki_logging::Instance()->_boost_severity_logger)). open_record((::boost::log::keywords::severity = (pst::log_severity_level::debug))); ! !_boost_log_record_1131;)
               ::boost::log::aux::make_record_pump(((pst::spooki_logging::Instance()->_boost_severity_logger)), _boost_log_record_1131).stream() << __PRETTY_FUNCTION__ << " : " << 1131 << "] " << std::endl;
     HighLevelOperation::addBasicOptions();
        OperationBase::addSpecificOptions()
               (
                    "iceWaterPhase" "" ,
                    po::value<ICEWATERPHASE_ENUM_t>() ,
                    "* \t" "Switch to determine which phase to consider: ice and water, or, water only.\n  " "Supported types:[ STRING" "[" "WATER" "|" "BOTH" "]" " ]\n  " "Ex: --iceWaterPhase BOTH\n" 
               )
               (
                     "delta" "" ,
                     po::value<string>()->default_value(
                          "300hPa",
                          (std::string("\"300hPa\""). find("::") != std::string::npos)
                               ? std::string("\"300hPa\"").substr(std::string("\"300hPa\""). find_last_of("::") + 1)
                               : (
                                    (std::string("\"300hPa\""). find("\"") != string::npos && (string("\"300hPa\""). find("\"") != std::string("\"300hPa\""). find_last_of("\"")))
                                        ? string("\"300hPa\""). substr(string("\"300hPa\""). find("\"") + 1, std::string("\"300hPa\""). find_last_of("\"") - 1 - string("\"300hPa\""). find("\""))
                                        : "\"300hPa\""
                                 )
                     ),
                     "  \t" "Depth in pressure coordinates above the surface where to search for the most unstable parcel.  \n  " "Default: 300hPa\n" "Supported types:[ FLOAT[>0.0 to +infinity] +  STRING" "[mb|Pa|hPa|kPa]" " ]\n  " "Ex: --delta 500hPa"
               )
               (
                     "temperaturePhaseSwitch" "" ,
                     po::value<string>() ,
                     "  \t" "Temperature at which to change from the ice phase to the water phase.\n  " "Mandatory if '--iceWaterPhase BOTH' is used. \n  " "Supported types [ FLOAT[-273.15 to 273.16] + STRING [C|K] ]\n  " "Ex: --temperaturePhaseSwitch -40C or --temperaturePhaseSwitch 268.15K\n"
               )
               (
                     "increment" "" ,
                     po::value<string>() ->default_value(
                          "1hPa",
                          (std::string("\"1hPa\""). find("::") != std::string::npos)
                               ? std::string("\"1hPa\""). substr(std::string("\"1hPa\""). find_last_of("::") + 1)
                               : (
                                    (std::string("\"1hPa\""). find("\"") != string::npos && (string("\"1hPa\""). find("\"") != std::string("\"1hPa\""). find_last_of("\"")))
                                          ? string("\"1hPa\""). substr(string("\"1hPa\""). find("\"") + 1, std::string("\"1hPa\""). find_last_of("\"") - 1 - string("\"1hPa\""). find("\""))
                                          : "\"1hPa\"")
                     ),
                     "  \t" "Specify pressure increment between levels for the iterative calculation.\n  " "Supported types: [FLOAT [>0.0 to +infinity] + STRING [mb|Pa|hPa|kPa]]\n  " "Default: 1.0hPa\n  " "Ex: --increment 5.0mb\n" )  ;
        OperationBase::addHiddenOptions() ( "algorithm" "" , po::value<string>() ->default_value("NEW", (std::string("\"NEW\""). find("::") != std::string::npos)? std::string("\"NEW\""). substr(std::string("\"NEW\""). find_last_of("::") + 1) : ((std::string("\"NEW\""). find("\"") != string::npos && (string("\"NEW\""). find("\"") != std::string("\"NEW\""). find_last_of("\"")))? string("\"NEW\""). substr(string("\"NEW\""). find("\"") + 1, std::string("\"NEW\""). find_last_of("\"") - 1 - string("\"NEW\""). find("\"")) : "\"NEW\"")) , "  \t" "Specify which method to use.\n  " "Supported types: [STRING [OLD|NEW]]\n  " "Default: NEW\n  " )  ;
    ; };


// Macro expansion of GET_PARAMETER_VALUES

        ICEWATERPHASE_ENUM_t iceWaterPhase;
        getParameterValue("iceWaterPhase", iceWaterPhase );
        string delta;
        getParameterValue("delta", delta );
        string temperaturePhaseSwitch = string();
        if(parameterExists("temperaturePhaseSwitch"))
        {
             getParameterValue("temperaturePhaseSwitch", temperaturePhaseSwitch );
        }
        string increment;
        getParameterValue("increment", increment );
        string algorithm;
        getParameterValue("algorithm", algorithm );  
