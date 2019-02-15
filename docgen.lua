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

-- Make toc.md

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
		file:write('['..sampleInfo.ShortName..'](src/samples/'..sampleFamily..'/'..sampleType..'/samples.md) - '..sampleInfo.Description..'  \n')
	end
end

file:write('## Tests\n\n')

for k,v in pairs(testTypes) do
    local testType = string.sub(v,3,-2)
    file:write('### '..testType..'\n\n')
    local subTestTypes = scandir('cd ./src/tests/'..testType..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)
        dofile("./src/tests/"..testType.."/"..subTestType.."/tests.lua")
        file:write('['..testInfo.ShortName..'](src/tests/'..testType..'/'..subTestType..'/tests.md) - '..testInfo.Description..'  \n')
    end
end

file:close()

-- make output/tests/X/Y/results.md

for k,v in pairs(testTypes) do
    local testType = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/tests/'..testType..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)
        dofile("./src/tests/"..testType.."/"..subTestType.."/tests.lua")
        file = io.open("./output/tests/"..testType.."/"..subTestType.."/results.md", "w")

        file:write("# Test Results\n tests done:\n")
        for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
            file:write("* "..testFunctionName.."\n")
        end

        for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
            file:write("## "..testFunctionName.."\n")

            local sampleTypes = scandir('cd ./src/samples/'..testType..'/ && ls -d ./*/ && cd ../../..')

            for k3,v3 in pairs(sampleTypes) do
                local sampleType = string.sub(v3,3,-2)
                dofile("./src/samples/"..testType.."/"..sampleType.."/samples.lua")

                file:write("### "..sampleInfo.LongName.."\n")

                for sampleFunctionIndex, sampleFunctionName in ipairs(sampleInfo.Functions) do
                    file:write("#### "..sampleFunctionName.."\n")
                end
            end
        end

        -- TODO: put results here!

        file:close()
    end
end
