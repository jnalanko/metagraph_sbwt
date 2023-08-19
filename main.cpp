#include "SBWT.hh"
#include "sbwt_dbg.hpp"
#include <string>
#include <chrono>

using namespace std;

vector<string> get_reads(const string& fastq_file){
    vector<string> reads;
    ifstream in(fastq_file);
    string line;
    int64_t line_mod4 = 0;

    while(getline(in, line)){
        if(line_mod4 == 1) reads.push_back(line);
        line_mod4 = (line_mod4 + 1) % 4;
    }

    return reads;
}

int64_t time_now_ms(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();;
}

int main(){
    mtg::graph::DBGSBWT dbg_sbwt;
    dbg_sbwt.load("coli3.sbwt");

    vector<string> reads = get_reads("/home/niklas/data/ERR434259_1_prefix.fastq");
    int64_t n_kmers_processed = 0;
    int64_t n_hits = 0;

    int64_t t0 = time_now_ms();
    for(auto S : reads){
        dbg_sbwt.map_to_nodes_sequentially(S, [&n_kmers_processed, &n_hits](int64_t node_id){
            n_kmers_processed++;
            n_hits += (node_id != -1);
        });
    }
    int64_t t1 = time_now_ms();

    int64_t elapsed_us = (t1-t0) * 1000;
    cout << (double) elapsed_us / n_kmers_processed << " us / k-mer" << endl;
    cout << "Hit rate: " << (double) n_hits / n_kmers_processed << endl;
}