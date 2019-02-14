function scandir(command)
    local i, t, popen = 0, {}, io.popen
    local pfile = popen(command)
    for filename in pfile:lines() do
        i = i + 1
        t[i] = filename
    end
    pfile:close()
    return t
end

print "=====Generating Documentation====="

local sampleFamilies = scandir('cd ./src/samples/ && ls -d ./*/ && cd ../..')
local testTypes = scandir('cd ./src/tests/ && ls -d ./*/ && cd ../..')

local file = io.open("./toc.md", "w")

file:write('# Table of Contents\n\n')

file:write('## Samples\n\n')

for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file:write('### '..sampleFamily..'\n\n')
	local sampleTypes = scandir('cd ./src/samples/'..sampleFamily..'/ && ls -d ./*/ && cd ../../..')
	for k2,v2 in pairs(sampleTypes) do
		local sampleType = string.sub(v2,3,-2)
		dofile("./src/samples/"..sampleFamily.."/"..sampleType.."/samples.lua")
		file:write('['..info.ShortName..'](src/samples/'..sampleFamily..'/'..sampleType..'/samples.md) - '..info.Description..'  \n')
	end
end

file:write('## Tests\n\n')

for k,v in pairs(testTypes) do
    local testType = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/tests/'..testType..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)
        dofile("./src/tests/"..testType.."/"..subTestType.."/tests.lua")
        file:write('['..info.ShortName..'](src/tests/'..testType..'/'..subTestType..'/tests.md) - '..info.Description..'  \n')
    end
end

file:close()