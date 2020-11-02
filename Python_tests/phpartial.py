import functools

def main():
    # Trying to understand how functools.partial might work under the hood
    five_inter = functools.partial(int, base=5)
    # My attempt at creating a bind, p_bind takes a function and args to fix and
    # returns a function that calls my_func with those arguments already set and
    # any arguments that are provided to the wrapped/bound function.
    two_printer = p_bind(my_func, base=2)
    two_printer(number='number', two='two')
    # I can do the same thing as with functools.partial
    three_inter = p_bind(int, base=3)
    # It works how I intended
    print(three_inter('111'))
    print(five_inter('111'))

def p_bind(function, *bound_args, **bound_kwargs):
    """ Returns a new function that is equivalent to initial function with
    argument values fixed.

    If f: (x,y) -> f(x,y), then bind(f, y=3) will be the function g: x -> f(x,3)
    """
    def new_func(*args, **kwargs):
        """ Add values already bound to arguments and call wrapped function with
        augmented arguments and kwargs """
        total_kwargs = {**bound_kwargs,**kwargs}
        total_args = bound_args + args
        return function(*total_args, **total_kwargs)
    return new_func

def my_func(**kwargs):
    print(f"MY_FUNC : kwargs = {kwargs}")

if __name__ == "__main__":
    main()
