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
		file:write('['..sampleInfo.ShortName..'](output/samples/'..sampleFamily..'/'..sampleType..'/page.md) - '..sampleInfo.Description..'  \n')
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
        file:write('['..testInfo.ShortName..'](output/tests/'..testType..'/'..subTestType..'/page.md) - '..testInfo.Description..'  \n')
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

                if testInfo.MakesSampleTypeImages then
                    file:write("!["..sampleType.."](../../../samples/"..testType.."/"..sampleType.."/"..testFunctionName..".png)  \n")
                end

                for sampleFunctionIndex, sampleFunctionInfo in ipairs(sampleInfo.Functions) do
                    if testInfo.MakesIndividualImages then
                        file:write("#### "..sampleFunctionInfo.name.."\n")
                        file:write("!["..sampleFunctionInfo.name.."](../../../samples/"..testType.."/"..sampleType.."/"..testFunctionName.."_"..sampleFunctionInfo.name..".png)  \n")
                    end
                end
            end
        end

        file:close()
    end
end

-- combine output/tests/X/Y/results.md and src/tests/X/Y/tests.md into output/tests/X/Y/page.md
for k,v in pairs(testTypes) do
    local testType = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/tests/'..testType..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)

        dofile("./src/tests/"..testType.."/"..subTestType.."/tests.lua")

        local results = readAll("./output/tests/"..testType.."/"..subTestType.."/results.md")
        local testsPage = readAll("./src/tests/"..testType.."/"..subTestType.."/tests.md")
        file = io.open("./output/tests/"..testType.."/"..subTestType.."/page.md", "w")
        file:write("# "..testInfo.LongName.."\n")
        file:write(testsPage)
        file:write("\n")
        file:write(results)
        file:close()
    end
end

-- make output/samples/X/Y/results.md

for k,v in pairs(sampleFamilies) do
    local sampleFamily = string.sub(v,3,-2)
    local sampleTypes = scandir('cd ./src/samples/'..sampleFamily..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(sampleTypes) do
        local sampleType = string.sub(v2,3,-2)
        dofile("./src/samples/"..sampleFamily.."/"..sampleType.."/samples.lua")

        file = io.open("./output/samples/"..sampleFamily.."/"..sampleType.."/results.md", "w")

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

            local subTestTypes = scandir('cd ./src/tests/'..sampleFamily..'/ && ls -d ./*/ && cd ../../..')
            for k3,v3 in pairs(subTestTypes) do
                local subTestType = string.sub(v3,3,-2)
                dofile("./src/tests/"..sampleFamily.."/"..subTestType.."/tests.lua")
                if testInfo.MakesIndividualImages then
                    file:write("### "..testInfo.LongName.."\n")
                    for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
                        if testInfo.SamplePageShowsFunctionName then
                            file:write("#### "..testFunctionName.."\n")
                        end
                        file:write("!["..sampleFunctionInfo.name.."](../../../samples/"..sampleFamily.."/"..sampleType.."/"..testFunctionName.."_"..sampleFunctionInfo.name..".png)  \n")
                    end
                end
            end
        end

        -- write links to sample type images
        local subTestTypes = scandir('cd ./src/tests/'..sampleFamily..'/ && ls -d ./*/ && cd ../../..')
        for k3,v3 in pairs(subTestTypes) do
            local subTestType = string.sub(v3,3,-2)
            dofile("./src/tests/"..sampleFamily.."/"..subTestType.."/tests.lua")

            if testInfo.MakesSampleTypeImages then
                file:write("## "..testInfo.LongName.."\n")
                for testFunctionIndex, testFunctionName in ipairs(testInfo.Functions) do
                    file:write("### "..testFunctionName.."\n")
                    file:write("!["..sampleType.."](../../../samples/"..sampleFamily.."/"..sampleType.."/"..testFunctionName..".png)  \n")
                end
            end
        end

        file:close()
    end
end

-- combine output/samples/X/Y/results.md and src/samples/X/Y/samples.md into output/samples/X/Y/page.md
for k,v in pairs(sampleFamilies) do
    local sampleFamily = string.sub(v,3,-2)
    local sampleTypes = scandir('cd ./src/samples/'..sampleFamily..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(sampleTypes) do
        local sampleType = string.sub(v2,3,-2)

        dofile("./src/samples/"..sampleFamily.."/"..sampleType.."/samples.lua")

        local results = readAll("./output/samples/"..sampleFamily.."/"..sampleType.."/results.md")
        local testsPage = readAll("./src/samples/"..sampleFamily.."/"..sampleType.."/samples.md")
        file = io.open("./output/samples/"..sampleFamily.."/"..sampleType.."/page.md", "w")
        file:write("# "..sampleInfo.LongName.."\n")
        file:write(testsPage)
        file:write("\n")
        file:write(results)
        file:close()
    end
end