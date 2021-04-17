

CodeGenII.chm : *.htm CodeGenII.hhp CodeGenII.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" CodeGenII


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F CodeGenII.chm


Release/CodeGenII.chm : CodeGenII.chm
  copy $(MAKEDIR)\CodeGenII.chm  $(MAKEDIR)\..\Release\CodeGenII.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del CodeGenII.chm
  cd $(MAKEDIR)


Debug/CodeGenII.chm : CodeGenII.chm
  copy $(MAKEDIR)\CodeGenII.chm  $(MAKEDIR)\..\Debug\CodeGenII.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del CodeGenII.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/CodeGenII.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/CodeGenII.chm


