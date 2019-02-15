testInfo = {
    CodeName="Discrepancy",
    ShortName="Discrepancy",
    LongName="Discrepancy Test",
    Description="Calculate metrics about actual point density compared to expected point density if the points were uniformly spaced.",
    Functions= {
        "CalculateDiscrepancy",
        "CalculateDiscrepancyWrapAround",
    },
    AutoTestSampleCounts = {16, 32, 64},
    MakesImages = false,
    MakesImagePerSampleCount = false,
}