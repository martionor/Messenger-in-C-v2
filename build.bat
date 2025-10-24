gcc Messenger_server/*.c -o server.exe -Wall -Wextra -pedantic -g
gcc Messenger_client/*.c -o messenger.exe -Wall -Wextra -pedantic -g

:: Build Python client
pyinstaller --onefile --noconsole --name messenger_python --distpath . ./Python_client/main.py