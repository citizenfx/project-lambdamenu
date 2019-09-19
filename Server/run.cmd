@echo off
copy /y bin\* L:\cfx-server-data\resources\[local]\lambda-menu
icecon -c "stop lambda-menu; start lambda-menu" localhost:30120 meowmeow