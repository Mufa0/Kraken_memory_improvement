#include "kraken_headers.hpp"
#include "krakendb.hpp"
#include "krakenutil.hpp"
#include "quickfile.hpp"
#include "seqreader.hpp"

const size_t DEF_WORK_UNIT_SIZE = 500000;

using namespace std;
using namespace kraken;

void parse_command_line(int argc, char **argv);
void usage(int exit_code=EX_USAGE);



int Num_threads = 1;
string DB_filename, Index_filename, Nodes_filename;
bool Quick_mode = false;
bool Fastq_input = false;
bool Print_classified = false;
bool Print_unclassified = false;
bool Print_kraken = true;
bool Populate_memory = false;
bool Only_classified_kraken_output = false;
uint32_t Minimum_hit_count = 1;
map<uint32_t, uint32_t> Parent_map;
KrakenDB Database;
string Classified_output_file, Unclassified_output_file, Kraken_output_file;
ostream *Classified_output;
ostream *Unclassified_output;
ostream *Kraken_output;
size_t Work_unit_size = DEF_WORK_UNIT_SIZE;

uint64_t total_classified = 0;
uint64_t total_sequences = 0;
uint64_t total_bases = 0;

int main(int argc, char **argv) {
  #ifdef _OPENMP
  omp_set_num_threads(1);
  #endif

  parse_command_line(argc, argv);
  if (! Nodes_filename.empty())
    Parent_map = build_parent_map(Nodes_filename);

  if (Populate_memory)
    cerr << "Loading database... ";

  QuickFile db_file;
  db_file.open_file(DB_filename);
  if (Populate_memory)
    db_file.load_file();
  Database = KrakenDB(db_file.ptr());
  KmerScanner::set_k(Database.get_k());

  QuickFile idx_file;
  idx_file.open_file(Index_filename);
  if (Populate_memory)
    idx_file.load_file();
  KrakenDBIndex db_index(idx_file.ptr());
  Database.set_index(&db_index);

  for (int i = 0; i < sizeof(Database.get_pair_ptr());++i){
      fprintf(stderr, "%d\n", Database.get_pair_ptr()[i]);
  }

  return 0;
}
void parse_command_line(int argc, char **argv) {
  int opt;
  long long sig;
  DB_filename = argv[1];
  Index_filename = argv[2];

}

void usage(int exit_code) {

  exit(exit_code);
}
