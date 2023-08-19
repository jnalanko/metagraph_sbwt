#ifndef __DBG_SBWT_HPP__
#define __DBG_SBWT_HPP__

#include <iostream>
#include <exception>

#include "sequence_graph.hpp"
#include "SBWT.hh"
#include "SubsetMatrixRank.hh"

namespace mtg {
namespace graph {

class DBGSBWT : public DeBruijnGraph {

  typedef sbwt::SBWT<sbwt::SubsetMatrixRank<sdsl::bit_vector, sdsl::rank_support_v5<>>> plain_matrix_sbwt_t;

  public:
    DBGSBWT() {
        this->dbg = std::make_unique<plain_matrix_sbwt_t>();
    }
    virtual ~DBGSBWT() {}

    // Insert sequence to graph and invoke callback |on_insertion| for each new
    // node index augmenting the range [1,...,max_index], including those not
    // pointing to any real node in graph. That is, the callback is invoked for
    // all new real nodes and all new dummy node indexes allocated in graph.
    // In short: max_index[after] = max_index[before] + {num_invocations}.
    void add_sequence(std::string_view sequence,
                      const std::function<void(node_index)> &on_insertion = [](node_index) {}) {
        throw std::runtime_error("add_sequence not implemented for SBWT");
    }

    // Traverse graph mapping sequence to the graph nodes
    // and run callback for each node until the termination condition is satisfied
    void map_to_nodes(std::string_view sequence,
                      const std::function<void(node_index)> &callback,
                      const std::function<bool()> &terminate = [](){ return false; }) const {
        throw std::runtime_error("TODO");
    }

    // Traverse graph mapping sequence to the graph nodes
    // and run callback for each node until the termination condition is satisfied.
    // Guarantees that nodes are called in the same order as the input sequence.
    // In canonical mode, non-canonical k-mers are NOT mapped to canonical ones
    void map_to_nodes_sequentially(std::string_view sequence,
                                   const std::function<void(node_index)> &callback,
                                   const std::function<bool()> &terminate = [](){ return false; }) const {
        const char* seq = sequence.begin();
        for(int64_t node_id : this->dbg->streaming_search(seq)){
            callback(node_id);
        }
        terminate();
    }

    void call_nodes(const std::function<void(node_index)> &callback,
                    const std::function<bool()> &stop_early = [](){ return false; }) const {
        throw std::runtime_error("TODO");
    }

    void call_outgoing_kmers(node_index node,
                             const OutgoingEdgeCallback &callback) const {
        throw std::runtime_error("TODO");
    }

    void call_incoming_kmers(node_index node,
                             const IncomingEdgeCallback &callback) const {
        throw std::runtime_error("TODO");
    }

    // Traverse the outgoing edge
    node_index traverse(node_index node, char next_char) const {
        throw std::runtime_error("TODO");
    }

    // Traverse the incoming edge
    node_index traverse_back(node_index node, char prev_char) const {
        throw std::runtime_error("TODO");
    }

    // Given a node index, call the target nodes of all edges outgoing from it.
    void adjacent_outgoing_nodes(node_index node,
                                 const std::function<void(node_index)> &callback) const {
        throw std::runtime_error("TODO");
    }

    // Given a node index, call the source nodes of all edges incoming to it.
    void adjacent_incoming_nodes(node_index node,
                                 const std::function<void(node_index)> &callback) const {
        throw std::runtime_error("TODO");
    }

    size_t outdegree(node_index node) const { throw std::runtime_error("TODO"); }
    bool has_single_outgoing(node_index node) const { throw std::runtime_error("TODO"); }
    bool has_multiple_outgoing(node_index node) const { throw std::runtime_error("TODO"); }

    size_t indegree(node_index node) const { throw std::runtime_error("TODO");}
    bool has_no_incoming(node_index node) const { throw std::runtime_error("TODO"); }
    bool has_single_incoming(node_index node) const { throw std::runtime_error("TODO"); }

    node_index kmer_to_node(std::string_view kmer) const {
        throw std::runtime_error("TODO");
    }

    std::string get_node_sequence(node_index node) const {
        throw std::runtime_error("TODO");
    }

    size_t get_k() const { throw std::runtime_error("TODO"); }
    Mode get_mode() const { throw std::runtime_error("TODO");; }

    uint64_t num_nodes() const { throw std::runtime_error("TODO"); }
    uint64_t max_index() const { throw std::runtime_error("TODO"); }

    void serialize(std::ostream &out) const { throw std::runtime_error("TODO"); }
    void serialize(const std::string &filename) const { throw std::runtime_error("TODO");}

    bool load(std::istream &in){
        this->dbg->load(in);
        return true; // TODO: what is this return value for?
    }

    bool load(const std::string &filename){
        std::ifstream in(filename, std::ios::binary);
        return load(in);
    }

    std::string file_extension() const { throw std::runtime_error("TODO"); }

    bool operator==(const DeBruijnGraph &other) const {
        throw std::runtime_error("TODO");
    }

    const std::string& alphabet() const { throw std::runtime_error("TODO"); }

  private:
    std::unique_ptr<plain_matrix_sbwt_t> dbg;
};

} // namespace graph
} // namespace mtg

#endif // __DBG_HASH_FAST_HPP__