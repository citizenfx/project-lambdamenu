dofile('emscripten.lua')

solution 'lm-sv'
	configurations { 'Release' }

	toolset 'emscripten'

	location 'Build/'

	project 'lambdamenu'
		targetdir 'Bin/'
		objdir 'Obj/'
		kind 'ConsoleApp'
		targetextension '.bc'
		language 'C++'
		files { '../EnhancedReborn/**.h', '../EnhancedReborn/**.cpp', '../EnhancedReborn/**.c', '../Server/Source/**.cpp', '../Server/Include/**.h' }

		removefiles { '../**/database_sqlite.cpp', '../**/sqlite3.c' }

		includedirs { '../Server/Include/' }

		defines { 'SERVER_SIDED' }

		optimize 'On'

		--linkoptions '-s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1 -s EMTERPRETIFY_WHITELIST=@whitelist.txt -O2 -g --js-library lib.js --memory-init-file 0'