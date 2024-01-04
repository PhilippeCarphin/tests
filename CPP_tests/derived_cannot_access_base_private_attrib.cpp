#include <iostream>
/*
 * This test shows that private attributes of a base class are not accessible
 * in the derived class and also,
 */
class Base {

    public:
        int getPrivateAttrib(){ return base_private_attrib;}
        void setPrivateAttrib(int n){base_private_attrib = n;}

        virtual ~Base(){std::cout << "Destructor of BASE" << std::endl;}
        virtual void do_stuff(){ std::cout << "Doig stuff base" << std::endl; }
        virtual void do_other_stuff(){ std::cout << "Doig other stuff base" << std::endl; }

    private:
        int base_private_attrib;
};

class Derived : public Base {
    public:
    void show_base_attrib(){
        // This causes error at compilation
        // base_private_attrib = 4;
        // std::cout << "private attrib in base is " << base_private_attrib << std::endl;

        setPrivateAttrib(8);
        std::cout << "private attrib in base is " << getPrivateAttrib() << std::endl;
    }

    virtual void do_stuff(){ std::cout << "Doig stuff derived" << std::endl; }
    virtual void do_other_stuff(){ std::cout << "Doig other stuff derived" << std::endl; }
};

int main(void){
    Derived d;

    d.show_base_attrib();
    d.do_stuff();

    Base *b_ptr = new Derived;
    b_ptr->do_stuff();
    b_ptr->do_other_stuff();
    delete b_ptr;
}
