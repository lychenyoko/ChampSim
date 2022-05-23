//
// Data Prefetching Championship Simulator 2
//
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "cache.h"
#include <map>
#include <set>
#include <cassert>
#include <set>
#include <utility>      // std::pair, std::make_pair
#include <iostream>
#include <algorithm>
#include <fstream>
#include <boost/algorithm/string.hpp>

unsigned int total_access;
unsigned int predictions;
unsigned int no_prediction;
unsigned int stream_end;
unsigned int no_translation;
unsigned int reuse;
uint64_t last_addr;
uint64_t stride;
uint64_t found;
uint64_t not_found;

#define PC_LOCALIZATION

uint64_t large_number = 0xffffffff;
uint64_t instr_id = 0xffffffff; // Would comment out this line later
extern string prefetch_file;
map<uint64_t, uint64_t> voyager_predictions;
extern map<uint64_t, uint64_t> va_ppa_mapping;

void CACHE::prefetcher_initialize() 
{
    printf("Voyager Prefetcher\n");

    total_access = 0;
    predictions = 0;
    no_prediction = 0;
    found = 0;
    not_found = 0;
    srand(0);

#ifdef PC_LOCALIZATION
    std::string filename ("/scratch/cluster/zshi17/ChampSim_prefetching/CRCRealOutput/voyager-pc/");
#else
    std::string filename ("/scratch/cluster/zshi17/ChampSim_prefetching/CRCRealOutput/voyager-global/");
#endif

	std::string inputString(prefetch_file);
	std::string delimiters("/.");
	std::vector<std::string> parts;
	boost::split(parts, inputString, boost::is_any_of(delimiters));
    filename += parts[5];
    filename += '.';
    filename += parts[6];
    filename += '.';
    filename += parts[7];
    filename += ".txt";
    cout << "oracle filename: " << filename << endl;
    std::ifstream infile;
    infile.open(filename, ios::in);
    uint64_t a, b;
    int cnt = 0;
    while (infile >> a >> b)
    {
        if(cnt < 10)
        {
            cout << a << " " << b << endl;
            cnt += 1;
        }
        voyager_predictions[a] = b;
    }
}

void CACHE::prefetcher_cache_operate(uint64_t addr, uint64_t ip, uint8_t cache_hit, uint8_t type, uint32_t metadata_in)
{
    // only look at cache miss stream

    /*
    if (type != LOAD || cache_hit)
        return;

    if(warmup_complete[cpu])
        total_access += 1;

    if (warmup_complete[cpu] && voyager_predictions.find(instr_id) != voyager_predictions.end())
    {
        found++;
        uint64_t pf_addr = voyager_predictions[instr_id];
        int ret = 0;

        ret = prefetch_line(pf_addr, true, metadata_in);

        if(ret == 1)
        {
            if(warmup_complete[cpu]) predictions++;
        }
    }
    else{
        if(warmup_complete[cpu]) not_found++;
    }
    */
}

void CACHE::prefetcher_cache_fill(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint32_t metadata_in)
{
}

void CACHE::prefetcher_cycle_operate() {}


void CACHE::prefetcher_final_stats()
{
    cout << "Prefetcher final stats" << endl;
    cout << "Triggers: " << total_access << endl;
    cout << "Predictions: " << predictions << endl;
    cout << "No predictions: " << no_prediction << endl;
    cout << "voyager prediction found: " << found << endl;
    cout << "voyager prediction not found: " << not_found << endl;
}


