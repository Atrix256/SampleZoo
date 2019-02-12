function MakeTests(file, sampleInfo, sampleType, subSampleType, indent)

    for functionIndex, functionName in ipairs(sampleInfo.Functions) do
        file:write(indent.."// ".. functionName.."\n")
        file:write(indent.."{\n")
        file:write(indent.."    std::vector<float> samples;\n")
        file:write(indent.."    "..functionName.."(samples, 16);\n")
        file:write(indent..'    FILE* file = fopen("output/samples/'..sampleType..'/'..subSampleType..'/'..functionName..'.txt", "w+b");\n')
        file:write(indent..'    fprintf(file, "'..functionName..' %zu samples\\r\\n  Discrepancy: %0f\\r\\n  Wrap: %0f\\r\\n\\r\\n",\n')
        file:write(indent..'        samples.size(),\n')
        file:write(indent..'        Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),\n')
        file:write(indent..'        Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)\n')
        file:write(indent..'    );\n')
        file:write(indent..'    fclose(file);\n')
        file:write(indent..'    Tests::_1d::Numberline::MakeNumberline("output/samples/'..sampleType..'/'..subSampleType..'/'..functionName..'.png", samples, 512);\n')
        file:write(indent.."}\n")
    end

end