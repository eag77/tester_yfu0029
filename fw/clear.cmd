del *.xml
rmdir /s /q .vs
cd .\Debug
del *.d *.o *.mk Makefile  *.eep *.lss *.map *.srec *.elf
cd ..\Release
del *.d *.o *.mk Makefile  *.eep *.lss *.map *.srec *.elf
::pause
