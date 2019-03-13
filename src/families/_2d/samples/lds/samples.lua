sampleInfo = {
    CodeName="LDS",
    ShortName="LDS",
    LongName="Low Discrepancy Sequences",
    Description="Low discrepancy sequences",
    Functions= {
        { name = "NRooks", progressive = false, randomized = true, cache = false },
--[[        { name = "HammersleyWolfram2", progressive = false, randomized = false, cache = false },
        { name = "HammersleyWolfram3", progressive = false, randomized = false, cache = false },
        { name = "HammersleyWolfram5", progressive = false, randomized = false, cache = false },
        { name = "HammersleyWolfram2_1Bit", progressive = false, randomized = false, cache = false },
        { name = "HammersleyWolfram2_2Bits", progressive = false, randomized = false, cache = false },
        ]]
        { name = "HammersleyWikipedia2", progressive = false, randomized = false, cache = false },
        { name = "HammersleyWikipedia2Offset", progressive = false, randomized = false, cache = false },
--[[        { name = "HammersleyWikipedia3", progressive = false, randomized = false, cache = false },
        { name = "HammersleyWikipedia5", progressive = false, randomized = false, cache = false },
        ]]
        { name = "Sobol", progressive = true, randomized = false, cache = false },
        { name = "Halton_2_3_Zero", progressive = true, randomized = false, cache = false },
        { name = "Halton_2_3", progressive = true, randomized = false, cache = false },
        { name = "Halton_5_7", progressive = true, randomized = false, cache = false },
        { name = "Halton_13_9", progressive = true, randomized = false, cache = false },
    },
}