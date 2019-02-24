// In this file you can alter some settings of the library:
// 1) Specify the desired real and complex types by typedef'ing real_type and complex_type.
//    By default real_type is double and complex_type is std::complex<real_type>.
// 2) If the array class uses square brackets for element access operator, define
//    the macro __USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR

#ifndef __SIMPLE_FFT__FFT_SETTINGS_H__
#define __SIMPLE_FFT__FFT_SETTINGS_H__

#include <complex>

typedef double real_type;
typedef std::complex<real_type> complex_type;

//#ifndef __USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR
//#define __USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR
//#endif

#endif // __SIMPLE_FFT__FFT_SETTINGS_H__
