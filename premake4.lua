include 'premake'

make_solution 'chaiscript_example'

platforms { "native","x32", "x64" }

configuration 'vs*'
	buildoptions {
		'/bigobj',
		'-Zm150'
	}
configuration '*'

includedirs {
	'ChaiScript/include'
}

local function chaiscript_version()
	local function all_text(file)
    	local f = io.open(file, "rb")
    	local content = f:read("*all")
    	f:close()
    	return content
	end

	local text = all_text 'ChaiScript/include/chaiscript/chaiscript_defines.hpp'
	local version = ''
	for number in text:gmatch("version_%a+%s*=%s*(%d)") do
		if #version == 0 then
			version = number
		else
			version = version .. '.' .. number
		end
	end
	return version
end

make_shared_lib('chaiscript_stdlib',{
	'ChaiScript/src/chaiscript_stdlib.cpp'
})
use_standard('c++11')
targetname('chaiscript_stdlib-'..chaiscript_version())

make_console_app('chaiscript_example', {
	'src/*.*'
})
use_standard('c++11')
configuration 'windows'
	pchheader 'afxwin.h'
	pchsource 'src/afxwin.cpp'
configuration '*'

configuration 'linux'
	links 'dl'
configuration '*'

links 'chaiscript_stdlib'

run_target_after_build()
