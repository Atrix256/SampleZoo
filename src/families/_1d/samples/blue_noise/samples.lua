sampleInfo = {
    CodeName="BlueNoise",
    ShortName="Blue Noise",
    LongName="Blue Noise Sequences",
    Description="Randomized sequences that have only high frequency content",
    Functions= {
        { name = "BestCandidate", progressive = true, randomized = true, cache = true },
        { name = "BestCandidate5", progressive = true, randomized = true, cache = true },
        { name = "BestCandidate10", progressive = true, randomized = true, cache = true },
        { name = "BestCandidateRefined", progressive = true, randomized = true, cache = true }, -- it sort of is progressive, sort of not. it's too computationally expensive to treat as non progressive for eg integration :P
    },
}