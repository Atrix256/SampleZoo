function MakeTests(file, sampleInfo, sampleType, subSampleType, indent)

    for functionIndex, functionName in ipairs(sampleInfo.Functions) do
        file:write(indent.."// ".. functionName.."\n")
        file:write(indent.."{\n")
        file:write(indent..'    Tests::_1d::Standard::Standard('..functionName..', "'..sampleType..'", "'..subSampleType..'", "'..functionName..'");\n')
        file:write(indent.."}\n")
    end

end