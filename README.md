# Unit_test
Unit Testing lib used in Exanodes project.
Should be quite generic thus may be used in other projects.

This lib may seem redundant with already existant libs like boot tests or gtest, catch or else.

This is actually true, the explaination is that those libs were not available at the time the present one was created.

COMPILATION:

you may require autotools, nevertheless, the lib is supposed to be installed as a rpm.

BUILDING THE RPM:
install the rpmbuild software ('yum install -y rpmbuild' on RH or centos, 'urpmi -y rpm-build' on mageia or mandriva
once this is done, you may do:

$ ./autogen.sh
$ make dist # this should generate a seanodes-unittesting-1.0.tar.gz file
$ rpmbuild -ta seanodes-unittesting-1.0.tar.gz #this should create a ~/rpmbuild/RPMS/x86_64/seanodes-unittesting-devel-1.0-1sea.x86_64.rpm file

then install as root the ~/rpmbuild/RPMS/x86_64/seanodes-unittesting-devel-1.0-1sea.x86_64.rpm file
