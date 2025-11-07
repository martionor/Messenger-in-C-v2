:: Build C messenger(client) and server
:: Build C messenger (client) and server
@echo off

echo Building C Messenger Server...
gcc Messenger_server/*.c common/*.c -o server.exe -Wall -Wextra -pedantic -g
if %errorlevel% neq 0 pause

echo Building C Messenger Client...
gcc Messenger_client/*.c common/*.c -o messenger.exe -Wall -Wextra -pedantic -g
if %errorlevel% neq 0 pause

echo Build complete!
pause

:: Build Python client
pyinstaller --onefile --noconsole --name messenger_python --distpath . ./Python_client/main.py