@echo off

set fname=%1%
set key1=%2%
set key2=%3%
set key3=%4%
set key4=%5%
set key5=%6%
set key6=%7%
echo +++++++++++++++++++++++++++++++++++++++++++++
echo Triple DES gamma encode/decode test
echo file: '%fname%'
echo 1st key set: '%key1%'; '%key2%'; '%key3%'
echo 2nd key set: '%key4%'; '%key5%'; '%key6%'
echo +++++++++++++++++++++++++++++++++++++++++++++
echo +++++start time = %time%
echo crypt using 1st key set
3des_gamma %fname% %key1%  %key2% %key3%
echo crypt using 2nd key set
3des_gamma %fname%__res %key4%  %key5% %key6%
echo crypt using 1st key set
3des_gamma %fname%__res__res %key1%  %key2% %key3% 
echo crypt using 2nd key set
3des_gamma %fname%__res__res__res %key4%  %key5% %key6% 
echo +++++end time = %time%
echo ++++++++++++++++++++++++++++++++++++++++++++
comp /A /L %fname%__res__res__res__res %fname%
del %fname%__res
del %fname%__res__res
del %fname%__res__res__res
del %fname%__res__res__res__res
