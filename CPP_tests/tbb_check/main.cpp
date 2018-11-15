#include <iostream>
#include <tbb/tbb_stddef.h>
#include <tbb/parallel_for.h>

void do_individual_element(size_t i, float f)
{
  std::cout << "array element " << i << " = " << f << std::endl;
}

void parallel_for_with_lambda(size_t n, float *my_floats)
{
  // On passe à parallel_for :
  // - Un blocked_range que TBB va subdiviser et distribuer
  // - Une fonction qui prend un blocked_range et fait du travail sur ce range
  //   (en pratique ça sera une subdivision du range total faite automatiquement
  //   par TBB.)
parallel_for(tbb::blocked_range<size_t>(0,n),
             [&my_floats](tbb::blocked_range<size_t> &r)
             {
               float *a = my_floats;
               for(size_t i = r.begin(); i != r.end(); ++i){
                 do_individual_element(i, a[i]);
               }
             });
}


/********************************************************************************
 * Name        : ArrayPrinter {
 * Description : Functor for use with Intel TBB
 * Arguments   : my_array : pointer to array to operate on
 * Operation   : Print each array element in a range
 *******************************************************************************/
class ArrayPrinter {
  /*
   * array to operate on
   */
  float *const my_array;
public:
  /*
   * This class is like a function, you pass data to operate on in the
   * constructor, and TBB is going to use this operation to operate on
   * subdivisions of the total range
   */
  void operator()(const tbb::blocked_range<size_t> &r) const
  {
    float *a = my_array;
    for(size_t i = r.begin(); i != r.end(); ++i){
      do_individual_element(i, a[i]);
    }
  }
  /* Data to operate on */
  ArrayPrinter( float array[] ):
    my_array(array)
  {
  }
};

void parallel_for_with_object(size_t n, float *my_floats)
{
  parallel_for(tbb::blocked_range<size_t>(0,n), ArrayPrinter(my_floats));
}

int main(int argc, char *argv[])
{
  std::cout << "TBB_INTERFACE_VERSION : " << TBB_INTERFACE_VERSION << std::endl
            << "TBB_INTERFACE_VERSION_MAJOR : " << TBB_INTERFACE_VERSION_MAJOR << std::endl
            << "TBB_COMPATIBLE_INTERFACE_VERSION : " << TBB_COMPATIBLE_INTERFACE_VERSION << std::endl;

  float my_floats[] = {
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
                       1.111, 2.222, 3.333, 4.444,
  };
  size_t n = sizeof(my_floats)/sizeof(float);

  parallel_for_with_object(n, my_floats);

  std::cout << std::endl << "================================================================================" << std::endl << std::endl;

  parallel_for_with_lambda(n, my_floats);
}
