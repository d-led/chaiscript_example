include 'premake'

make_solution 'chaiscript_example'

platforms { "native","x32", "x64" }

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
targetname('chaiscript_stdlib-'..chaiscript_version())
configuration 'vs*'
	buildoptions '/bigobj'
configuration '*'

make_console_app('chaiscript_example', {
	'src/test.cpp'
})
links 'chaiscript_stdlib'

use_standard('c++11')
run_target_after_build()
