function MakeTests(file, sampleInfo, indent, namespace)

    for functionIndex, functionName in ipairs(sampleInfo.Functions) do
        file:write(indent.."// ".. functionName.."\n")
        file:write(indent.."{\n")

        file:write(indent.."    std::vector<float> samples;\n")
        file:write(indent.."    "..namespace.."::"..functionName.."(samples, 16);\n")

        file:write(indent.."}\n")
    end

end