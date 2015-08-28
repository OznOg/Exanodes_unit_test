;
; Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
; reserved and protected by French, UK, U.S. and other countries' copyright laws.
; This file is part of Exanodes Unit test library and is subject to the terms
; and conditions defined in the LICENSE file which is present in the root
; directory of the project.
;

; Inno Setup script for the Seanodes unit test library
; Usage: iscc.exe unit_testing.iss

[Setup]
AppName=Seanodes unit testing library
AppVerName=Seanodes unit testing library
AppCopyright=Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights reserved and protected by French, UK, U.S. and other countries' copyright laws.
This file is part of Exanodes Unit test library and is subject to the terms
and conditions defined in the LICENSE file which is present in the root
directory of the project.
AppPublisher=Seanodes
AppPublisherURL=http://www.seanodes.com
DefaultDirName={pf}\Seanodes\unit_testing
DefaultGroupName=Seanodes
Compression=lzma
SolidCompression=yes
SourceDir="..\src\"
ArchitecturesInstallIn64BitMode=x64

OutputBaseFilename="seanodes-unittesting"
OutputDir=".."

ChangesEnvironment=yes
PrivilegesRequired=admin

[Files]
Source: "unit_testing.h"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "unit_testing.h"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "ut_build_template.c"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "ut_build_template.c"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "ut_build"; DestDir: "{app}"; Check: Is64BitInstallMode;
Source: "ut_build"; DestDir: "{app}"; Check: not Is64BitInstallMode;

