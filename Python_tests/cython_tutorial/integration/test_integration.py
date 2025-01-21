import integration_py
import integration_slow
import integration_types
import integration_cdef
import integration_csin
import integration_csin_straight_c
import timeit

         #a  b   N
params = (0,100,10_000_000)

start = timeit.default_timer()
res = integration_py.integrate_f(*params)
end = timeit.default_timer()
print(f"Result integrate_py              = {res}")

time_python = end - start

start = timeit.default_timer()
res_py = integration_slow.integrate_f(*params)
end = timeit.default_timer()
print(f"Result integrate_slow            = {res_py}")

time_slow = end - start

start = timeit.default_timer()
res_types = integration_types.integrate_f(*params)
end = timeit.default_timer()
print(f"Result integrate_types           = {res_types}")

time_types = end - start

start = timeit.default_timer()
res_cdef = integration_cdef.integrate_f(*params)
end = timeit.default_timer()
print(f"Result integrate_cdef            = {res_cdef}")

time_cdef = end - start

start = timeit.default_timer()
res_csin = integration_csin.integrate_f(*params)
end = timeit.default_timer()
print(f"Result integrate_csin            = {res_csin}")

time_csin = end - start

start = timeit.default_timer()
res_straight_c = integration_csin_straight_c.integrate_f(*params)
end = timeit.default_timer()
time_csin_straight_c = end - start
print(f"Result integrate_csin_straight_c = {res_straight_c}")


print(f"time python          = {time_python:.4}")
print(f"time slow            = {time_slow:.4}")
print(f"time types           = {time_types:.4}")
print(f"time cdef            = {time_cdef:.4}")
print(f"time csin            = {time_csin:.4}")
print(f"time csin_straight_c = {time_csin_straight_c:.4}")

