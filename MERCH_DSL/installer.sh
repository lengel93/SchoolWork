 #!/bin/sh

make python

sudo ./pyinstaller.py --onefile testingMain.py progInfo.py ParserV2Parser.py ParserV2Listener.py ParserV2Lexer.py operations.py

make clean

cp ./dist/testingMain $PWD

sudo chown $USER -R ./build ./dist

rm -rf ./build ./dist
