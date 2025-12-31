#pragma once

enum jobs
{
    chop,
    adventure,
    collect,
    shop,
    numberOfJobs,
};

class text_job
{
    text_job();
public:
    const static char jobs[numberOfJobs][21];
};
const static char jobs[numberOfJobs][21] =
{
    "Chopping",
    "Adventure",
    "Collecting",
    "Shop"
};