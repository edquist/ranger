//#include "condor_common.h" 
//#include "condor_snutils.h"
//#include "condor_debug.h"
//#include "condor_random_num.h"
// #include "stl_string_utils.h"

#include <limits>
#include <string>
#include <stdio.h>
#include <stdarg.h>

#define STL_STRING_UTILS_FIXBUF 500

static
int vformatstr_impl(std::string& s, bool concat, const char* format, va_list pargs) {
    char fixbuf[STL_STRING_UTILS_FIXBUF];
    const int fixlen = sizeof(fixbuf)/sizeof(fixbuf[0]);
	int n;
	va_list  args;

    // Attempt to write to fixed buffer.  condor_snutils.{h,cpp}
    // provides an implementation of vsnprintf() in windows, so this
    // logic works cross platform 
#if !defined(va_copy)
	n = vsnprintf(fixbuf, fixlen, format, pargs);    
#else
	va_copy(args, pargs);
	n = vsnprintf(fixbuf, fixlen, format, args);
	va_end(args);
#endif

    // In this case, fixed buffer was sufficient so we're done.
    // Return number of chars written.
    if (n < fixlen) {
		if (concat) {
			s.append(fixbuf, n);
		} else {
			s.assign(fixbuf, n);
		}
        return n;
    }

    // Otherwise, the fixed buffer was not large enough, but return from 
    // vsnprintf() tells us how much memory we need now.
    n += 1;
    char* varbuf = NULL;
    // Handle 'new' behavior mode of returning NULL or throwing exception
    try {
        varbuf = new char[n];
    } catch (...) {
        varbuf = NULL;
    }
	if (NULL == varbuf) { fprintf(stderr, "Failed to allocate char buffer of %d chars", n); }

    // re-print, using buffer of sufficient size
#if !defined(va_copy)
	int nn = vsnprintf(varbuf, n, format, pargs);
#else
	va_copy(args, pargs);
	int nn = vsnprintf(varbuf, n, format, args);
	va_end(args);
#endif

    // Sanity check.  This ought not to happen.  Ever.
    if (nn >= n) fprintf(stderr, "Insufficient buffer size (%d) for printing %d chars", n, nn);

    // safe to do string assignment
	if (concat) {
		s.append(varbuf, nn);
	} else {
		s.assign(varbuf, nn);
	}

    // clean up our allocated buffer
    delete[] varbuf;

    // return number of chars written
    return nn;
}

int vformatstr(std::string& s, const char* format, va_list pargs) {
	return vformatstr_impl(s, false, format, pargs);
}

int vformatstr_cat(std::string& s, const char* format, va_list pargs) {
	return vformatstr_impl(s, true, format, pargs);
}

int formatstr(std::string& s, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int r = vformatstr_impl(s, false, format, args);
    va_end(args);
    return r;
}

int formatstr_cat(std::string& s, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int r = vformatstr_impl(s, true, format, args);
    va_end(args);
    return r;
}

