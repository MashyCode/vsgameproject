
ECHO Y | DEL . >: NUL  

REM Delete Garbage Files
del *.aps
del *.ilk
del *.map
del *.ncb
del *.opt
del *.plg
del *.pbi
del *.pbo
del *.pbt
del *.pdb
del *.tmp
del *._xe
del *.old
del *.xml
del *.user
del *.cd


attrib -h -a *.ncb
del *.ncb

REM Delete hidden archived garbage files, first changing their attributes.
attrib -h -a *.gid
del *.gid

REM Optional: Delete Visual Studio Solution user options, which can be useful to keep.
attrib -h -a *.suo
del *.suo

REM Delete Garbage Directories
del enc_temp_folder\*.*
rmdir enc_temp_folder

ECHO Y | del DEBUG\*.*
ECHO Y | rmdir DEBUG
ECHO Y | del RELEASE\*.*
ECHO Y | rmdir RELEASE

REM Optional: delete the executables that the project has written to root.
del *.exe

ECHO Y | del _UpgradeReport_Files\*.*
rmdir _UpgradeReport_Files