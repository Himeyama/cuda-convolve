/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */

#include <ruby.h>
#include <vector>
#include <cuda-convolve.hpp>

template <typename T>
static VALUE
rb_ary_cuda_convolve(VALUE self, VALUE v, VALUE mode){
    long a_len = RARRAY_LEN(self);
    long v_len = RARRAY_LEN(v);
    long m = NUM2LONG(mode);

    std::vector<T> _a(a_len);
    std::vector<T> _v(v_len);
    std::vector<T> conv;

    for(long i = 0; i < a_len; i++)
        _a[i] = (T)NUM2DBL(rb_ary_entry(self, i));
    for(long i = 0; i < v_len; i++)
        _v[i] = (T)NUM2DBL(rb_ary_entry(v, i));

    if(m == 0)
        conv = convolve(_a, _v);
    else if(m == 1)
        conv = convolve_same(_a, _v);
    else if(m == 2)
        conv = convolve_valid(_a, _v);
    else
        exit(1);

    VALUE c = rb_ary_new();
    for(long i = 0; i < conv.size(); i++)
        rb_ary_store(c, i, DBL2NUM((double)conv[i]));

    return c;
}

extern "C" {
    void Init_convolve(void){
        rb_define_private_method(rb_cArray, "gpu_convolve_float", rb_ary_cuda_convolve<float>, 2);
        rb_define_private_method(rb_cArray, "gpu_convolve_double", rb_ary_cuda_convolve<double>, 2);
    }
}