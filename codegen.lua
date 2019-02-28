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

print "=====Generating Code====="

local dotHHeader = "// Autogenerated by codegen.lua during premake process\n\n#pragma once\n\n"
local file

-- make ./build/codegen/codegen.h
file = io.open("./build/codegen/codegen.h", "w")
file:write(dotHHeader)
file:write('#define _CRT_SECURE_NO_WARNINGS // for stb\n\n')
file:write("#include <vector>\n\n")
file:write("using SampleGenerate_1d = void(*)(std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique);\n\n")
file:write("struct SampleGenerateInfo_1d\n{\n")
file:write("    SampleGenerate_1d function;\n")
file:write("    const char* cacheKey;\n")
file:write("    const char* sampleFamily;\n")
file:write("    const char* sampleType;\n")
file:write("    const char* name;\n")
file:write("    bool progressive;\n")
file:write("    bool randomized;\n")
file:write("};\n\n")
file:write("using Test_1d = void(*)(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix);\n\n")
file:write("#define countof(array) (sizeof(array) / sizeof(array[0]))\n\n");
file:write('#include "shared/datacache.h"\n')
file:write('#include "tests.h"\n')
file:write('#include "samples.h"\n')
file:write('#include "autotest.h"\n')
file:close()

-- gather the list of sample familiessampl
local sampleFamilies = scandir('cd ./src/families/ && ls -d ./*/ && cd ../..')

-- make ./build/codegen/samples.h
file = io.open("./build/codegen/samples.h", "w")
file:write(dotHHeader)
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file:write('#include "'..sampleFamily..'/samples/samples.h"\n')
end
file:close()

-- make ./build/codegen/X/samples/samples.h
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file = io.open("./build/codegen/"..sampleFamily.."/samples/samples.h", "w")
	file:write(dotHHeader)
	local sampleTypes = scandir('cd ./src/families/'..sampleFamily..'/samples/ && ls -d ./*/ && cd ../../..')
	for k2,v2 in pairs(sampleTypes) do
		local sampleType = string.sub(v2,3,-2)
		file:write('#include "'..sampleType..'/samples.h"\n')
	end

    file:write("\nnamespace "..sampleFamily.."\n{\n")
    file:write("    extern std::vector<std::vector<SampleGenerateInfo"..sampleFamily..">> sampleFunctions;\n")
    file:write("}\n")
	file:close()
end

-- make ./build/codegen/X/samples/samples.cpp
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file = io.open("./build/codegen/"..sampleFamily.."/samples/samples.cpp", "w")
	file:write(dotHHeader)
    file:write('#include "codegen.h"\n')
    file:write('#include "'..sampleFamily..'/samples/samples.h"\n')

    file:write("\nnamespace "..sampleFamily.."\n{\n")
    file:write("    std::vector<std::vector<SampleGenerateInfo"..sampleFamily..">> sampleFunctions =\n    {\n")
    local sampleTypes = scandir('cd ./src/families/'..sampleFamily..'/samples/ && ls -d ./*/ && cd ../../..')
    for k3, v3 in pairs(sampleTypes) do
        local sampleType = string.sub(v3,3,-2)
        dofile("./src/families/"..sampleFamily.."/samples/"..sampleType.."/samples.lua")
        file:write("        {\n")
        for functionIndex, functionInfo in ipairs(sampleInfo.Functions) do

            local cacheKey = sampleType.."::"..functionInfo.name;

            file:write("            { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {")
            if functionInfo.progressive then
                file:write("  DataCache::Instance().m_samples__1d.GetSamples_Progressive(");
            else
                file:write("  DataCache::Instance().m_samples__1d.GetSamples_NonProgressive(")
            end
            file:write("\""..cacheKey.."\", ")
            file:write(sampleFamily.."::Samples::"..sampleInfo.CodeName.."::"..functionInfo.name..", ")
            file:write("values, numValues, wantUnique, "..tostring(functionInfo.cache)..", "..tostring(functionInfo.randomized) .."); }, \""..cacheKey.."\", \""..sampleFamily.."\", \""..sampleType.."\", \""..functionInfo.name.."\", "..tostring(functionInfo.progressive)..", "..tostring(functionInfo.randomized).." },\n")
        end
        file:write("        },\n")
    end
    file:write("    };\n}\n")
	file:close()
end

-- make ./build/codegen/tests.h
file = io.open("./build/codegen/tests.h", "w")
file:write(dotHHeader)
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file:write('#include "'..sampleFamily..'/tests/tests.h"\n')
end
file:close()

-- make ./build/codegen/autotest.h
file = io.open("./build/codegen/autotest.h", "w")
file:write(dotHHeader)
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file:write('#include "'..sampleFamily..'/tests/autotest.h"\n')
end
file:write("\ninline void AutoTest()\n{\n")
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file:write('    '..sampleFamily..'::Tests::AutoTest();\n')
end
file:write("};\n")
file:close()

-- make ./build/codegen/X/tests/tests.h
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file = io.open("./build/codegen/"..sampleFamily.."/tests/tests.h", "w")
	file:write(dotHHeader)
	local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
	for k2,v2 in pairs(subTestTypes) do
		local subTestType = string.sub(v2,3,-2)
		file:write('#include "'..subTestType..'/tests.h"\n')
	end
	file:close()
end

-- make ./build/codegen/X/tests/Y/tests.h
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do

        local subTestType = string.sub(v2,3,-2)

        file = io.open("./build/codegen/"..sampleFamily.."/tests/"..subTestType.."/tests.h", "w")
        file:write(dotHHeader)

        dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")

        file:write("namespace "..sampleFamily.."\n{\n    namespace Tests\n    {\n        namespace "..testInfo.CodeName.."\n        {\n")

        for functionIndex, functionName in ipairs(testInfo.Functions) do
            file:write("            void "..functionName.."(const std::vector<std::vector<SampleGenerateInfo_1d>>&, const char* testName, const char* fileNamePrefix);\n")
        end

        file:write("        };\n    };\n};\n")
    end
end

-- make ./build/codegen/X/tests/autotest.h
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)

    file = io.open("./build/codegen/"..sampleFamily.."/tests/autotest.h", "w")
    file:write(dotHHeader)

    local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)
        file:write('#include "'..subTestType..'/autotest.h"\n')
    end

    file:write("\nnamespace "..sampleFamily.."\n{\n    namespace Tests\n    {\n")
    file:write("        inline void AutoTest()\n        {\n")

    local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do
        local subTestType = string.sub(v2,3,-2)
        dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")
        file:write("            "..testInfo.CodeName.."::AutoTest();\n")
    end

    file:write("        };\n    };\n};\n")

    file:close()
end

-- make ./build/codegen/X/tests/Y/autotest.h
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/families/'..sampleFamily..'/tests/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do

        local subTestType = string.sub(v2,3,-2)

        dofile("./src/families/"..sampleFamily.."/tests/"..subTestType.."/tests.lua")

        file = io.open("./build/codegen/"..sampleFamily.."/tests/"..subTestType.."/autotest.h", "w")
        file:write(dotHHeader)

        file:write("namespace "..sampleFamily.."\n{\n    namespace Tests\n    {\n        namespace "..testInfo.CodeName.."\n        {\n")

        file:write("            inline void AutoTest()\n            {\n")

        for functionIndex, functionName in ipairs(testInfo.Functions) do
            file:write("                "..functionName.."("..sampleFamily.."::sampleFunctions, \""..functionName.."\", \"\");\n")
        end

        file:write("            }\n")
        file:write("        };\n    };\n};\n")

        os.mkdir("./output/"..sampleFamily.."/tests/"..subTestType.."/")
    end
end

-- make ./build/codegen/X/samples/Y/samples.h
for k,v in pairs(sampleFamilies) do
    local sampleFamily = string.sub(v,3,-2)
    local sampleTypes = scandir('cd ./src/families/'..sampleFamily..'/samples/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(sampleTypes) do

        local sampleType = string.sub(v2,3,-2)

        file = io.open("./build/codegen/"..sampleFamily.."/samples/"..sampleType.."/samples.h", "w")
        file:write(dotHHeader)

        dofile("./src/families/"..sampleFamily.."/samples/"..sampleType.."/samples.lua")

        file:write("namespace "..sampleFamily.."\n{\n    namespace Samples\n    {\n        namespace "..sampleInfo.CodeName.."\n        {\n")

        for functionIndex, functionInfo in ipairs(sampleInfo.Functions) do
            file:write("            void "..functionInfo.name.."(std::vector<float>& values, size_t numValues, std::mt19937& rng);\n")
        end

        file:write("        };\n    };\n};\n")

        -- also make output/samples/X/Y/
        os.mkdir("./output/"..sampleFamily.."/samples/"..sampleType.."/")
    end

    os.mkdir("./datacache/")
end
