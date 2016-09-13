@echo off

set _CUR_DIR=%~dp0

if not exist "5.源码" goto END

chdir ./5.源码
rmdir /s /q Debug
rmdir /s /q Release
rmdir /s /q log

chdir ../7.安装盘
rmdir /s /q testPic
rmdir /s /q log

chdir ../
del /f /s *.ncb *.sbr *.plg *.positions *.ilk *.aps *.suo *.pdb *.user *.exp


:END
echo "Exit..."