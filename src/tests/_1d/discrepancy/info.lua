info = {
    CodeName="Discrepancy",
    ShortName="Discrepancy",
    LongName="Discrepancy Test",
    Description="Calculate metrics about actual point density compared to expected point density if the points were uniformly spaced.",
    Functions= {
        "float CalculateDiscrepancy(const std::vector<float>& samples);",
        "float CalculateDiscrepancyWrapAround(const std::vector<float>& samples);",
    },
}