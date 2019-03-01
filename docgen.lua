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

function readAll(file)
    local f = assert(io.open(file, "rb"))
    local content = f:read("*all")
    f:close()
    return content
end

print "=====Generating Documentation====="

local sampleFamilies = scandir('cd ./src/families/ && ls -d ./*/ && cd ../..')

-- Make toc.md

local file = io.open("./toc.md", "w")

file:write('# Table of Contents\n\n')

for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file:write('## '..sampleFamily..'\n\n')
	file:write('### Samples\n\n')
	local sampleTypes = scandir('cd ./src/families/'..sampleFamily..'/samples/ && ls -d ./*/ && cd ../../..')
	for k2,v2 in pairs(sampleTypes) do
		local sampleType = string.sub(v2,3,-2)
		dofile("./src/families/"..sampleFamily.."/samples/"..sampleType.."/samples.lua")
		file:write('['..sampleInfo.ShortName..'](output/'..sampleFamily..'/samples/'..sampleType..'/page.md) - '..sampleInfo.Description..'  \n')
	end
	file:write('### Tests\n\n')
    local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)
        dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")
        file:write('['..testInfo.ShortName..'](output/'..sampleFamily..'/tests/'..subTestType..'/page.md) - '..testInfo.Description..'  \n')
    end	
end

file:close()

-- make output/X/tests/Y/results.md

for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)
        dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")
        file = io.open("./output/"..sampleFamily.."/tests/"..subTestType.."/results.md", "w")

        file:write("# Test Results\n tests done:\n")
        for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
            file:write("* "..testFunctionName.."\n")
        end

        for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
            file:write("## "..testFunctionName.."\n")

            local sampleTypes = scandir('cd ./src/families/'..sampleFamily..'/samples/ && ls -d ./*/ && cd ../../..')

            for k3,v3 in pairs(sampleTypes) do
                local sampleType = string.sub(v3,3,-2)
                dofile("./src/families/"..sampleFamily.."/samples/"..sampleType.."/samples.lua")

                file:write("### "..sampleInfo.LongName.."\n")

                if testInfo.MakesSampleTypeImages then
                    file:write("!["..sampleType.."](../../../"..sampleFamily.."/samples/"..sampleType.."/"..testFunctionName..".png)  \n")
                end

                for sampleFunctionIndex, sampleFunctionInfo in ipairs(sampleInfo.Functions) do
                    if testInfo.MakesIndividualImages then
                        file:write("#### "..sampleFunctionInfo.name.."\n")
                        file:write("!["..sampleFunctionInfo.name.."](../../../"..sampleFamily.."/samples/"..sampleType.."/"..testFunctionName.."_"..sampleFunctionInfo.name..".png)  \n")
                    end
                end
            end
        end

        file:close()
    end
end

-- combine output/X/tests/Y/results.md and src/families/X/tests/Y/tests.md into output/X/tests/Y/page.md
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)

        dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")

        local results = readAll("./output/"..sampleFamily.."/tests/"..subTestType.."/results.md")
        local testsPage = readAll("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.md")
        file = io.open("./output/"..sampleFamily.."/tests/"..subTestType.."/page.md", "w")
        file:write("# "..testInfo.LongName.."\n")
        file:write("Source Code: [/src/families/"..sampleFamily.."/tests/"..subTestType.."/](../../../../src/families/"..sampleFamily.."/tests/"..subTestType.."/)\n\n")
        file:write(testsPage)
        file:write("\n")
        file:write(results)
        file:close()
    end
end

-- make output/X/samples/Y/results.md

for k,v in pairs(sampleFamilies) do
    local sampleFamily = string.sub(v,3,-2)
    local sampleTypes = scandir('cd ./src/families/'..sampleFamily..'/samples/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(sampleTypes) do
        local sampleType = string.sub(v2,3,-2)
        dofile("./src/families/"..sampleFamily.."/samples/"..sampleType.."/samples.lua")

        file = io.open("./output/"..sampleFamily.."/samples/"..sampleType.."/results.md", "w")

        file:write("# Test Results\n samples tested:\n")
        for sampleFunctionIndex, sampleFunctionInfo in ipairs(sampleInfo.Functions) do
            file:write("* "..sampleFunctionInfo.name.. " (")
            if sampleFunctionInfo.progressive then
                file:write("Progressive, ")
            else
                file:write("Not Progressive, ")
            end
            if sampleFunctionInfo.randomized then
                file:write("Randomized)\n")
            else
                file:write("Not Randomized)\n")
            end
        end

        for sampleFunctionIndex, sampleFunctionInfo in ipairs(sampleInfo.Functions) do
            file:write("## "..sampleFunctionInfo.name.."\n")

            local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
            for k3,v3 in pairs(subTestTypes) do
                local subTestType = string.sub(v3,3,-2)
                dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")
                if testInfo.MakesIndividualImages then
                    file:write("### "..testInfo.LongName.."\n")
                    for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
                        if testInfo.SamplePageShowsFunctionName then
                            file:write("#### "..testFunctionName.."\n")
                        end
                        file:write("!["..sampleFunctionInfo.name.."](../../../"..sampleFamily.."/samples/"..sampleType.."/"..testFunctionName.."_"..sampleFunctionInfo.name..".png)  \n")
                    end
                end
            end
        end

        -- write links to sample type images
        local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
        for k3,v3 in pairs(subTestTypes) do
            local subTestType = string.sub(v3,3,-2)
            dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")

            if testInfo.MakesSampleTypeImages then
                file:write("## "..testInfo.LongName.."\n")
                for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
                    file:write("### "..testFunctionName.."\n")
                    file:write("!["..sampleType.."](../../../"..sampleFamily.."/samples/"..sampleType.."/"..testFunctionName..".png)  \n")
                end
            end
        end

        file:close()
    end
end

-- combine output/X/samples/Y/results.md and src/families/X/samples/Y/samples.md into output/X/samples/Y/page.md
for k,v in pairs(sampleFamilies) do
    local sampleFamily = string.sub(v,3,-2)
    local sampleTypes = scandir('cd ./src/families/'..sampleFamily..'/samples/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(sampleTypes) do
        local sampleType = string.sub(v2,3,-2)

        dofile("./src/families/"..sampleFamily.."/samples/"..sampleType.."/samples.lua")

        local results = readAll("./output/"..sampleFamily.."/samples/"..sampleType.."/results.md")
        local testsPage = readAll("./src/families/"..sampleFamily.."/samples/"..sampleType.."/samples.md")
        file = io.open("./output/"..sampleFamily.."/samples/"..sampleType.."/page.md", "w")
        file:write("# "..sampleInfo.LongName.."\n")
        file:write("Source Code: [src/families/"..sampleFamily.."/samples/"..sampleType.."/](../../../../src/families/"..sampleFamily.."/samples/"..sampleType.."/)\n\n")
        file:write(testsPage)
        file:write("\n")
        file:write(results)
        file:close()
    end
end

-- combine readme.raw.md and toc.md into readme.md
local readmeRaw = readAll("readme.raw.md")
local TOC = readAll("toc.md")
local result = string.gsub(readmeRaw, "TOCTOC", TOC)
file = io.open("./readme.md", "w")
file:write(result)
file:close()
