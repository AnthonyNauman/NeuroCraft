@echo off
setlocal
SET PROJ = "D:\projects\NeuroCraft"

pushd D:\projects\NeuroCraft
rmdir /s /q documentation
doxygen D:\projects\NeuroCraft\devops\docs\Doxyfile
start "" D:\projects\NeuroCraft\documentation\html\index.html
popd

