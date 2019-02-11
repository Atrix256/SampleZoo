function MakeTests(file, sampleInfo, indent)

    for functionIndex, functionName in ipairs(sampleInfo.Functions) do
        file:write(indent.."// ".. functionName.."\n")
        file:write(indent.."{\n")

        file:write(indent.."    std::vector<float> samples;\n")
        file:write(indent.."    "..functionName.."(samples, 16);\n")

        file:write(indent.."}\n")
    end

end