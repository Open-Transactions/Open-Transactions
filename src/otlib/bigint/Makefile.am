noinst_LTLIBRARIES = libbigint.la

## For now we build locally and statically link to this library as a convenience library


bigint_headers_dir	=	$(top_srcdir)/include/bigint

bigint_headers		=	$(bigint_headers_dir)/BigInteger.hh		\
				$(bigint_headers_dir)/BigIntegerAlgorithms.hh	\
				$(bigint_headers_dir)/BigIntegerLibrary.hh	\
				$(bigint_headers_dir)/BigIntegerUtils.hh		\
				$(bigint_headers_dir)/BigUnsigned.hh		\
				$(bigint_headers_dir)/BigUnsignedInABase.hh	\
				$(bigint_headers_dir)/NumberlikeArray.hh

bigint_sources		=	BigInteger.cc			\
				BigIntegerAlgorithms.cc		\
				BigIntegerUtils.cc		\
				BigUnsigned.cc			\
				BigUnsignedInABase.cc


libbigint_la_SOURCES	=	$(bigint_sources) $(bigint_headers)
libbigint_la_CXXFLAGS	=	$(AM_CXXFLAGS) -I$(bigint_headers_dir)
libbigint_la_LDFLAGS	=	-static

