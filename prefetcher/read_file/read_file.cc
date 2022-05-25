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
extern std::string prefetch_file;
std::map<uint64_t, uint64_t> preloaded_predictions;

void CACHE::prefetcher_initialize() 
{
    std::cout << NAME << " Read-File Based Prefetcher" << std::endl; 

    total_access = 0;
    predictions = 0;
    no_prediction = 0;
    found = 0;
    not_found = 0;
    srand(0);

// #ifdef PC_LOCALIZATION
//     std::string filename ("/scratch/cluster/zshi17/ChampSim_prefetching/CRCRealOutput/voyager-pc/");
// #else
//     std::string filename ("/scratch/cluster/zshi17/ChampSim_prefetching/CRCRealOutput/voyager-global/");
// #endif

	// std::string inputString(prefetch_file);
	// std::string delimiters("/.");
	// std::vector<std::string> parts;
	// boost::split(parts, inputString, boost::is_any_of(delimiters));
    // filename += parts[5];
    // filename += '.';
    // filename += parts[6];
    // filename += '.';
    // filename += parts[7];
    // filename += ".txt";

    std::cout << "prefetch filename: " << prefetch_file << std::endl;
    std::ifstream infile;
    infile.open(prefetch_file, std::ios::in);
    uint64_t instr_id, prefetch_addr;
    int cnt = 0;
    
    printf("Printing first 10 prefetch lines: \n");

    while (infile >> instr_id >> prefetch_addr)
    {
        if(cnt < 10)
        {
            std::cout << instr_id << " " << prefetch_addr << std::endl;
            cnt += 1;
        }
        preloaded_predictions[instr_id] = prefetch_addr;
    }

    // std::map<uint64_t, uint64_t>::iterator it;
    // for (it = preloaded_predictions.begin(); it != preloaded_predictions.end(); it++){
    //     std::cout << it->first << " " << it->second << std::endl;
    // }

}

uint32_t CACHE::prefetcher_cache_operate(uint64_t addr, uint64_t ip, uint64_t instr_id, uint8_t cache_hit, uint8_t type, uint32_t metadata_in)
{
    // only look at cache miss stream

    
    //if (type != LOAD || cache_hit)
    //    return;

    //if(warmup_complete[cpu])
    //    total_access += 1;

    //if (warmup_complete[cpu] && preloaded_predictions.find(instr_id) != preloaded_predictions.end())
    //{
    //    found++;
    //    uint64_t pf_addr = preloaded_predictions[instr_id];
    //    int ret = 0;

    //    ret = prefetch_line(pf_addr, true, metadata_in);

    //    if(ret == 1)
    //    {
    //        if(warmup_complete[cpu]) predictions++;
    //    }
    //}
    //else{
    //    if(warmup_complete[cpu]) not_found++;
    //}
    //

    if (preloaded_predictions.find(instr_id) != preloaded_predictions.end()){
        found++;
        uint64_t prefetch_addr = preloaded_predictions[instr_id];
        prefetch_line(prefetch_addr, true, metadata_in);
    }
    else{
        not_found++;    
    }
    
    return metadata_in; // use it as a placeholder
}

uint32_t CACHE::prefetcher_cache_fill(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint32_t metadata_in)
{
    return metadata_in;
}

void CACHE::prefetcher_cycle_operate() {}


void CACHE::prefetcher_final_stats()
{
    std::cout << "Prefetcher final stats" << std::endl;
    std::cout << "Triggers: " << total_access << std::endl;
    std::cout << "Predictions: " << predictions << std::endl;
    std::cout << "No predictions: " << no_prediction << std::endl;
    std::cout << "Read-file prediction found: " << found << std::endl;
    std::cout << "Read-file prediction not found: " << not_found << std::endl;
}


