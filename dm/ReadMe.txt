

Options:
\dm:<model filename>
\ds:<script file>

Examples:
dm.exe \dm:test.dm \ds:cpp.ds \o:test.h
dm.exe \dm:test.dm \ds:cs.ds \o:test.cs
dm.exe \dm:test.dm \ds:fs.ds \o:test.fs

Since we will have 'pretty standard' c++, c# and f# templates, we can 'embed' those ds files and just reference them:

dm.exe \dm:test.dm \lang:c++ \o:test.h
dm.exe \dm:test.dm \lang:c# \o:test.cs
dm.exe \dm:test.dm \lang:f# \o:test.fs
