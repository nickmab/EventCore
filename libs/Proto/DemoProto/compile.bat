set cwd=%cd%
cd %~dp0
call protoc --cpp_out=. *.proto
cd %cwd%