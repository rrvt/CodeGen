

CodeGen.chm : *.htm CodeGen.hhp CodeGen.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" CodeGen


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist CodeGen.chm del /F CodeGen.chm


$(TgtFolder)/CodeGen.chm : CodeGen.chm
  copy $(MAKEDIR)\CodeGen.chm  $(MAKEDIR)\..\$(TgtFolder)\CodeGen.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist CodeGen.chm del /F CodeGen.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/CodeGen.chm


