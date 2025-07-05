

CodeGen.chm : *.htm CodeGen.hhp CodeGen.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" CodeGen


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist CodeGen.chm del /F CodeGen.chm


Release/CodeGen.chm : CodeGen.chm
  copy $(MAKEDIR)\CodeGen.chm  $(MAKEDIR)\..\Release\CodeGen.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist CodeGen.chm del /F CodeGen.chm
  cd $(MAKEDIR)


Debug/CodeGen.chm : CodeGen.chm
  copy $(MAKEDIR)\CodeGen.chm  $(MAKEDIR)\..\Debug\CodeGen.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist CodeGen.chm del /F CodeGen.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/CodeGen.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/CodeGen.chm


