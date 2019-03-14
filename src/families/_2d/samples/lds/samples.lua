sampleInfo = {
    CodeName="LDS",
    ShortName="LDS",
    LongName="Low Discrepancy Sequences",
    Description="Low discrepancy sequences",
    Functions= {
        { name = "NRooks", progressive = false, randomized = true, cache = false },

        { name = "HammersleyA2NoOffset", progressive = false, randomized = false, cache = false },
        { name = "HammersleyA2", progressive = false, randomized = false, cache = false },
        { name = "HammersleyA3", progressive = false, randomized = false, cache = false },
        { name = "HammersleyA5", progressive = false, randomized = false, cache = false },

        { name = "HammersleyB2", progressive = false, randomized = false, cache = false },
        { name = "HammersleyB3", progressive = false, randomized = false, cache = false },
        { name = "HammersleyB5", progressive = false, randomized = false, cache = false },

        { name = "HammersleyB2_1Bit", progressive = false, randomized = false, cache = false },
        { name = "HammersleyB2_2Bit", progressive = false, randomized = false, cache = false },
        { name = "HammersleyB2_3Bit", progressive = false, randomized = false, cache = false },

        { name = "Sobol", progressive = true, randomized = false, cache = false },

        { name = "Halton_2_3_Zero", progressive = true, randomized = false, cache = false },
        { name = "Halton_2_3", progressive = true, randomized = false, cache = false },
        { name = "Halton_5_7", progressive = true, randomized = false, cache = false },
        { name = "Halton_13_9", progressive = true, randomized = false, cache = false },
    },
}