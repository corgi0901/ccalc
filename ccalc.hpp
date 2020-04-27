#ifndef _CCALC_HPP_
#define _CCALC_HPP_

typedef enum {
	INVALID_INPUT = 100,
	ZERO_DIVIDE   = 200,
} ErrorCode;

//#define DEBUG

#ifdef DEBUG
#define DPRINT(s) (std::cout << s << std::endl);
#else
#define DPRINT(...)
#endif

#endif /* _CCALC_HPP_ */