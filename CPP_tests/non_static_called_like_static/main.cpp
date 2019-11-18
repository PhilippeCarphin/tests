#include <iostream>
#include <memory>
#include <string>

template<typename ValueType>
class DefaultValueHolder
{
public:
    DefaultValueHolder() : _value(){}
    DefaultValueHolder(ValueType value) : _value(value){}
    ValueType operator()() const
        {
            return _value;
        }
private:
    ValueType _value;
};


template<typename KeyType, typename ValueType, typename ValueHolder=DefaultValueHolder<ValueType> >
class Mapper{
public:
    void set(const KeyType &key, const ValueType &value)
        {
            std::cout << __PRETTY_FUNCTION__ << " START" << std::endl;
            ValueHolder vh(value);
            set(key,vh);
            std::cout << __PRETTY_FUNCTION__ << " END" << std::endl;
        }
protected:
    void set(const KeyType &key, const ValueHolder & v)
        {
            std::cout << __PRETTY_FUNCTION__ << " START" << std::endl;
            std::cout << __PRETTY_FUNCTION__ << " END" << std::endl;
        }
};

class ProductHolder
{
public:
    ProductHolder();

    ProductHolder(const std::shared_ptr<int> & pds, bool isInput = true);

    std::shared_ptr<int> operator()() const;

    void clear();

    bool isInput() const;

private:
    std::shared_ptr<int> _pds;
    std::shared_ptr<int> _gds;
    bool _isInput;
};


int main(void)
{
    std::string k = "hello";
    int i = 1729;
    std::shared_ptr<int> v = std::make_shared<int>(i);
    ProductHolder ph(v);

    Mapper<std::string, std::shared_ptr<int>, ProductHolder>::set(k,ph);
    return 0;
}
