@echo off

set fname=masked.txt
set key1=%1%
set key2=%2%
set key3=%3%
echo +++++++++++++++++++++++++++++++++++++++++++++
echo Triple 3DES bookmark using decode test
echo file: '%fname%'
echo key1: '%key1%'; key2: '%key2%'; key3: '%key3%'
echo +++++++++++++++++++++++++++++++++++++++++++++
3des_io %fname% %key1%  %key2% %key3%
3des_io %fname%__res  qwe
echo ++++++++++++++++++++++++++++++++++++++++++++
echo try to find clear text fragments in %fname%__res__res file!!!
echo compare with %fname%!
del %fname%__res
