#include <iostream>
#include <memory>


class NviBase
{
    public:
        virtual ~NviBase(){
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
        }
        void nvi_destroy(){
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
            if(_normal_termination){
                std::cerr << "---> Normal destruction, calling close" << std::endl;
                close();
            } else {
                std::cerr << "---> Abnormal destruction, calling closeHard" << std::endl;
                closeHard();
            }
        }
        virtual void closeHard(){
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
        }
        virtual void close(){
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
        }
        bool _normal_termination = false;
};

class NviDerived : public NviBase
{
    public:
        virtual ~NviDerived(){
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
            nvi_destroy();
        }
        virtual void closeHard(){
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
        }
        virtual void close(){
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
        }
};

void demo_normal()
{
    NviDerived nvi_derived;
    // do stuff
    nvi_derived._normal_termination = true;
}

void function_that_throws()
{
    throw std::runtime_error("OOPSIE");
}

void demo_abnormal()
{
    NviDerived nvi_derived;
    function_that_throws();
    nvi_derived._normal_termination = true;
}

void do_demos(){
    std::cerr << "Demo normal termination ============================" << std::endl;
    demo_normal();
    std::cerr << "Demo abnormal termination ============================" << std::endl;
    demo_abnormal();
}

void demo_smart_ptr(){
    std::shared_ptr<NviBase> nvi_derived = std::make_shared<NviDerived>();
    nvi_derived->_normal_termination = true;
}


int main(void){

    demo_smart_ptr();
    try{
        do_demos();
    } catch (...) {
        throw;
    }


    return 0;
}
