/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */

#include <ruby.h>
#include <vector>
#include <cuda-convolve.hpp>
#include <numo/narray.h>

extern VALUE numo_cDFloat;
extern VALUE numo_cSFloat;

template <typename T>
static VALUE
rb_ary_cuda_convolve(VALUE self, VALUE v, VALUE mode){
    long a_len;
    long v_len;
    long m = NUM2LONG(mode);

    std::vector<T> _a;
    std::vector<T> _v;
    std::vector<T> conv;

    if(CLASS_OF(self) == rb_cArray){
        a_len = RARRAY_LEN(self);
        v_len = RARRAY_LEN(v);
        _a = std::vector<T>(a_len);
        _v = std::vector<T>(v_len);
        for(long i = 0; i < a_len; i++)
            _a[i] = (T)NUM2DBL(rb_ary_entry(self, i));
        for(long i = 0; i < v_len; i++)
            _v[i] = (T)NUM2DBL(rb_ary_entry(v, i));
    }else if(CLASS_OF(self) == numo_cDFloat){
        a_len = NUM2LONG(rb_funcall(self, rb_intern("size"), 0));
        v_len = NUM2LONG(rb_funcall(v, rb_intern("size"), 0));
        _a = std::vector<T>(a_len);
        _v = std::vector<T>(v_len);
        memcpy(_a.data(), (T*)na_get_pointer(self), sizeof(T) * a_len);
        memcpy(_v.data(), (T*)na_get_pointer(v), sizeof(T) * v_len);
    }else{
        exit(EXIT_FAILURE);
    }

    if(m == 0)
        conv = convolve(_a, _v);
    else if(m == 1)
        conv = convolve_same(_a, _v);
    else if(m == 2)
        conv = convolve_valid(_a, _v);
    else
        exit(EXIT_FAILURE);

    VALUE c;
    if(CLASS_OF(self) == rb_cArray){
        c = rb_ary_new();
        for(long i = 0; i < conv.size(); i++)
            rb_ary_store(c, i, DBL2NUM((double)conv[i]));
    }else if(CLASS_OF(self) == numo_cDFloat){
        c = rb_funcall(numo_cDFloat, rb_intern("zeros"), 1, LONG2NUM(conv.size()));
        memcpy((T*)na_get_pointer(c), conv.data(), sizeof(T) * conv.size());
    }

    return c;
}

extern "C" {
    void Init_convolve(void){
        rb_define_private_method(rb_cArray, "gpu_convolve_float", rb_ary_cuda_convolve<float>, 2);
        rb_define_private_method(rb_cArray, "gpu_convolve_double", rb_ary_cuda_convolve<double>, 2);

        rb_define_private_method(numo_cSFloat, "gpu_convolve_float", rb_ary_cuda_convolve<float>, 2);
        rb_define_private_method(numo_cDFloat, "gpu_convolve_double", rb_ary_cuda_convolve<double>, 2);
    }
}
