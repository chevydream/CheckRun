@echo off

set _CUR_DIR=%~dp0

if not exist "5.Դ��" goto END

chdir ./5.Դ��
rmdir /s /q Debug
rmdir /s /q Release
rmdir /s /q log

chdir ../7.��װ��
rmdir /s /q testPic
rmdir /s /q log

chdir ../
del /f /s *.ncb *.sbr *.plg *.positions *.ilk *.aps *.suo *.pdb *.user *.exp


:END
echo "Exit..."