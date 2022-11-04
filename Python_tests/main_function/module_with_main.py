#
# This demonstrates the value of having a main function instead of using putting
# the body of what would be said main() function directly in the if __name__ == "__main__":
# block.  Without the main() function, the variable 'i' becomes a global variable
# whose value is 6 after the for loop.
def useful_function(x):
    return x*x


if __name__ == "__main__":
    for i in range(7):
        print(useful_function(i))

    print(f"compute_val() -> {compute_val()}")
    print(f"i = {i} (It's a bad quirk of python: iteration variables keep existing after the for loop)")
