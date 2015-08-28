#!/bin/sh

export CFLAGS
export LDFLAGS

echo "Configuring Unit Tests for compilation"

# try to figure out where the sources are
srcdir=`dirname $0`
if [ ! -f $srcdir/autogen.sh ]; then
    echo "*** cannot find source directory"
    exit 2
fi

# generate autoconf files
cd $srcdir && \
aclocal && \
libtoolize --copy --force && \
autoheader && \
automake -a -c && \
autoconf || exit $?

if [ "$1" = "--noconfigure" ]; then
    exit 0;
fi

# configure with default options
$srcdir/configure "$@"
