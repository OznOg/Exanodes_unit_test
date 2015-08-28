#
# Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
# reserved and protected by French, UK, U.S. and other countries' copyright laws.
# This file is part of Exanodes Unit test library and is subject to the terms
# and conditions defined in the LICENSE file which is present in the root
# directory of the project.
#

%define name     seanodes-unittesting
%define version  1.0
%define release  1sea

Summary:         Seanodes unit testing library
Name:            %name
Version:         %version
Release:         %release
License:         PROPRIETARY
Group:           Development/Tools
URL:             http://www.seanodes.com
Source:          %{name}-%{version}.tar.gz
BuildRoot:       %{_tmppath}/%{name}-%{version}-%{release}-buildroot

%description
The Seanodes unit testing library allows you to write and execute unit tests for
any piece of software. Unit tests are essentials during software development; they
ensures you that the code you write works as you planned to.

Writing unit tests is an investment. Rigourous tests allows you to easily change
you code and add new features without worrying breaking the old ones or introducing
bugs. Any software part (library, module, algorithm, etc.) should be unit tested
before its integration within a product.

%package devel
Summary:         Devel files for the Seanodes unit testing library
Group:           Development/Tools

%description devel
This package contains the devel files for Seanodes unit testing library.
Any developer that wants to include this library into its software will need it.

%prep
%setup -q -n %{name}-%{version}

%build
%configure
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

# list the files for the binary package:
%files devel
%defattr(-,root,root)
%doc README COPYING ChangeLog
%{_includedir}/*.h
%{_bindir}/ut_build
%{_datadir}/unit_testing/ut_build_template.c

%changelog
