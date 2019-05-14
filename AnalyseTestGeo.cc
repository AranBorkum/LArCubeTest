#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "TFile.h"
#include "TTree.h"

int main(int argc, char** argv) {

  int opt;
  extern char *optarg;
  extern int   optopt;

  const char * InFileName = "";
  const char * TreeName   = "";

  int nEvent = -1;

  while ( (opt = getopt(argc, argv, "i:o:t:n:")) != -1 ) {
    switch ( opt ) {
    case 'i':
      InFileName = optarg;
      break;
    case 't':
      TreeName   = optarg;
      break;
    case 'n':
      nEvent     = atoi(optarg);
      break;
    case '?':
      std::cerr << "Unknown option: " << char(optopt) << "!" << std::endl;
    }
  }

  TFile f(InFileName, "READ");
  TTree *t = (TTree*) f.Get(TreeName);

  std::vector<int>    * GenParticlePDG    = NULL;
  std::vector<int>    * GenParticleID     = NULL;
  std::vector<int>    * GenParticleMother = NULL;
  std::vector<double> * GenParticleStartX = NULL;  
  std::vector<double> * GenParticleStartY = NULL; 
  std::vector<double> * GenParticleStartZ = NULL; 
  std::vector<double> * GenParticleEnergy = NULL; 
  std::vector<double> * GenParticleStartT = NULL; 
  std::vector<double> * GenParticleEndX   = NULL; 
  std::vector<double> * GenParticleEndY   = NULL; 
  std::vector<double> * GenParticleEndZ   = NULL; 
  std::vector<double> * GenParticleEndE   = NULL; 
  std::vector<double> * GenParticleEndT   = NULL; 

  t->SetBranchAddress("GenParticlePDG"   , &GenParticlePDG   );
  t->SetBranchAddress("GenParticleID"    , &GenParticleID    );
  t->SetBranchAddress("GenParticleMother", &GenParticleMother);
  t->SetBranchAddress("GenParticleStartX", &GenParticleStartX);
  t->SetBranchAddress("GenParticleStartY", &GenParticleStartY);
  t->SetBranchAddress("GenParticleStartZ", &GenParticleStartZ);
  t->SetBranchAddress("GenParticleEnergy", &GenParticleEnergy);
  t->SetBranchAddress("GenParticleStartT", &GenParticleStartT);
  t->SetBranchAddress("GenParticleEndX"  , &GenParticleEndX  );
  t->SetBranchAddress("GenParticleEndY"  , &GenParticleEndY  );
  t->SetBranchAddress("GenParticleEndZ"  , &GenParticleEndZ  );
  t->SetBranchAddress("GenParticleEndE"  , &GenParticleEndE  );
  t->SetBranchAddress("GenParticleEndT"  , &GenParticleEndT  );

  for (int i=0; i<t->GetEntries(); ++i) {

    t->GetEntry(i);
    std::cout << "EVENT " << i << std::endl;
    for (int it=0; it<GenParticlePDG->size(); ++it) {
      
      std::cout << (*GenParticleID)[it] << "\t" << (*GenParticleStartT)[it] << std::endl;

    }
  }
}
