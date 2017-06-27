@echo off

:: P:\emsdk\emsdk activate latest

set CXX=em++
set CC=emcc
set AR=emar
set CXXFLAGS=--std=gnu++14 -Wno-writable-strings

premake5 gmake

pushd Build
make verbose=1 -j2
popd

:: call emcc bin\lambdamenu.bc -o "bin\\lambdamenu.html" -s EMTERPRETIFY=1 -s NO_EXIT_RUNTIME=1 -s EMTERPRETIFY_FILE='Bin/data.binary' -s EMTERPRETIFY_ASYNC=1 -O2 -g --js-library lib.js --memory-init-file 1 -s EMTERPRETIFY_ADVISE=1 2>&1 > whitelist.tmp
:: cat whitelist.tmp | tr '\n' '\r' | sed 's/.*WHITELIST=.\(.*\)\'.*/\1/' > whitelist.txt
:: del whitelist.tmp

call emcc bin\lambdamenu.bc -o "bin\\lambdamenu.html" -s NO_EXIT_RUNTIME=1 -s TOTAL_MEMORY=41943040 -s EMTERPRETIFY_FILE='Bin/data.binary' -O2 -g --js-library lib.js --memory-init-file 1 -s EXPORTED_FUNCTIONS=['_main','_invoke_event_handler']
:: del whitelist.txt
