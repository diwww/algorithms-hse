#include "fifo.h"

void fifo::info(bool f)
{
    event e;
    job j;

    if (f)
    {
        e = workload.front();
        j = e.getjob();
        out << "\tArrived: " << j << " at " << genTimer << " seconds" << std::endl;
    }
    else
    {
        e = printQueue.front();
        j = e.getjob();
        if (!printQueue.empty())
        {
            out << "\tServicing: " << j << " at " << genTimer << " seconds" << std::endl;
            latency += genTimer - e.arrival_time();
        }
    }
}

void fifo::simulate(string file)
{
    loadworkload(file);
    size_t total = workload.size();
    string outPath = file.substr(0, file.find('.')) + ".out";
    out.open(outPath);
    out << "FIFO Simulation\n\n";

    while (!workload.empty() || !printQueue.empty())
    {
        while (genTimer == workload.front().arrival_time())
        {
            info(true);
            printQueue.push(workload.front());
            workload.pop();

            // If first event appears in printQueue,
            // start print process immediately
            if (printQueue.size() == 1)
                info(false);
        }

        if (!printQueue.empty())
        {
            if (printTimer == printQueue.front().getjob().getnumpages() * seconds_per_page)
            {
                // Dequeue serviced event
                printQueue.pop();
                // Reset timer
                printTimer = 0;
                // Print info about next event
                info(false);
            }

            printTimer++;
        }

        genTimer++;
    }

    out << "\n\tTotal jobs: " << total << endl;
    out << "\tAggregate latency: " << latency << endl;
    out << "\tMean latency: " << latency / (double) total << endl;
}
