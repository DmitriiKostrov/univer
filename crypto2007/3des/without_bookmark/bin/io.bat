@echo off

set fname=%1%
set key1=%2%
set key2=%3%
set key3=%4%
echo +++++++++++++++++++++++++++++++++++++++++++++
echo Triple DES encode/decode test
echo file: '%fname%'
echo key1: '%key1%'; key2: '%key2%'; key3: '%key3%'
echo +++++++++++++++++++++++++++++++++++++++++++++
echo +++++start time = %time%
3des_io %fname% %key1%  %key2% %key3%
3des_io %fname%__res %key1%  %key2% %key3% qwe
echo +++++end time = %time%
echo ++++++++++++++++++++++++++++++++++++++++++++
comp /A /L %fname%__res__res %fname%
del %fname%__res
del %fname%__res__res
