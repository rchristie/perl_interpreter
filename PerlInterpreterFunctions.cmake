
FUNCTION( GET_SHARED_PERL_EXECUTABLES _SHARED_PERL_EXECUTABLES )
	# Get all perl exectuables that are in CMISS_ROOT/ARCH_DIR/bin/perl/VERSION/
	SET( ${_SHARED_PERL_EXECUTABLES} ${SHARED_PERL_EXECUTABLES} PARENT_SCOPE )
ENDFUNCTION( GET_SHARED_PERL_EXECUTABLES _SHARED_PERL_EXECUTABLES )

