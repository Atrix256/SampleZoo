sampleInfo = {
    CodeName="LDS",
    ShortName="LDS",
    LongName="Low Discrepancy Sequences",
    Description="Low discrepancy sequences",
    Functions= {
        { name = "NRooks", progressive = false, randomized = true, cache = false },

        { name = "Sobol", progressive = true, randomized = false, cache = false },

        { name = "Halton_2_3_Zero", progressive = true, randomized = false, cache = false },
        { name = "Halton_2_3", progressive = true, randomized = false, cache = false },
        { name = "Halton_5_7", progressive = true, randomized = false, cache = false },
        { name = "Halton_13_9", progressive = true, randomized = false, cache = false },
    },
}